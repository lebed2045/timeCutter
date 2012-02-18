all:
	g++ timeCutter.cpp -o timeCutter


install: timeCutter
	sudo cp -f timeCutter /etc/init.d/timeCutter
	sudo cp -f timeCutter.conf /root/.timeCutter.conf
	cd /etc/init.d/
	sudo update-rc.d timeCutter defaults 90

timeCutter: timeCutter.cpp
	g++ timeCutter.cpp -o timeCutter

uninstall:
	cd  /etc/init.d/
	sudo update-rc.d -f timeCutter remove
	sudo rm timeCutter
	sudo rm /root/.timeCutter.conf
