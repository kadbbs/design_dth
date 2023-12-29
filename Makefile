all: dht run

dht: dht11.c
	gcc -o dht dht11.c  -lwiringPi -g
display:
	 gcc -o display display.c -lwiringPi -g
run:
	sudo ./dht 7
scp:
	scp ./* bbs@192.168.143.100:/home/bbs/code/desgin_12_25
main:
	gcc -o mian dht11.c front.c display.c main.c -lwiringPi -g
