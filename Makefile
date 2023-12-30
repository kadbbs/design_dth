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
main:	dht11.c front.c display.c main.c
	gcc -o main dht11.c front.c  display.c main.c -lwiringPi -g -Wall
