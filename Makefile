all:
	g++ timeCutter.cpp -o timeCutter


install:
	g++ timeCutter.cpp -o timeCutter
	sudo cp -f timeCutter /etc/init.d/timeCutter
	sudo cp -f timeCutter.conf /root/.timeCutter.conf
	cd /etc/init.d/
	sudo update-rc.d timeCutter defaults 90

uninstall:
	cd  /etc/init.d/
	sudo update-rc.d -f timeCutter remove
	sudo rm timeCutter
	sudo rm /root/.timeCutter.conf
