#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>  
#include <vector>
#include <string>
using namespace std;

#define CONFIG_FILE "/root/.timeCutter.conf"

vector< pair<int,int> > accessTime;

int getTimeAsMinutes(string time)
{
	int hh = 0;
	int mm = 0;
	sscanf(time.c_str(),"%d %*c %d ",&hh,&mm);
	return hh*60+mm;
}

int readSettings(){
	FILE *fin = 0;
	fin = fopen(CONFIG_FILE,"r");
	//6:00 - 9:00
	char* t1 = new char[1024];
	char* t2 = new char[1024];
	while( fscanf(fin,"%s %*s %s",t1,t2) != EOF  )
	{
		int tt1 = getTimeAsMinutes(t1);
		int tt2 =  getTimeAsMinutes(t2);
		if( tt1 < tt2 ){
			accessTime.push_back( make_pair( tt1,tt2) );
		} else {
			accessTime.push_back( make_pair( tt1, 24*60 ) );
			accessTime.push_back( make_pair( 0, tt2 ) );
		}
	}
	fclose(fin);
}
	
int main(){
	readSettings();
	time_t rawtime;
	struct tm * currentTime;
	 
	while(true){
		time ( &rawtime );
		currentTime = localtime ( &rawtime );
		bool access = false;
		int currentTimeAsMinutes = currentTime->tm_hour*60 + currentTime->tm_min;

		for(int i = 0; i < (int)accessTime.size(); i++)
			if( accessTime[i].first <= currentTimeAsMinutes && currentTimeAsMinutes <= accessTime[i].second  ) 
				access = true;

		if( accessTime.size() == 0 ) 
			return -1;
			
		sleep(5);
		if( !access ) break;
	}
	system ("poweroff");
	return 0;
}
