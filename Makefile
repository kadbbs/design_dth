all: main run

dht: dht11.c
	gcc -o dht dht11.c  -lwiringPi -g
display:
	 gcc -o display display.c -lwiringPi -g
run:
	sudo ./main 7
scp:
	scp -r ./.git ./* bbs@10.222.20.103:/home/bbs/code/design_12_25
	#scp ./* bbs@192.168.143.100:/home/bbs/code/desgin_12_25
scp_book:
	scp -r ./.git ./* bbs@10.222.20.110:/home/bbs/code/design_12_25
	#scp ./* bbs@192.168.143.100:/home/bbs/code/desgin_12_25
scp_book_loacl:
	scp -r ./.git ./* bbs@10.42.0.1:/home/bbs/code/web_dht_led
	#scp ./* bbs@192.168.143.100:/home/bbs/code/desgin_12_25
scp_r:
	scp -r ./.git ./* pi@10.42.0.79:/home/pi/code/design_r
	
main:	dht11.c font.c display.c main.c send_data.c
	gcc -o main dht11.c font.c  display.c send_data.c main.c -lwiringPi -g -lpthread
t_m:
	gcc -o test_web test_web.c web.c -lwebsockets -lpthread -I /usr/local/include

