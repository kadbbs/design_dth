all: dht run

dht: dht11.c
	gcc -o dht dht11.c  -lwiringPi -g
display:
	 gcc -o display display.c -lwiringPi -g
run:
	sudo ./dht 7
scp:
	scp ./* bbs@10.42.0.1:/home/bbs/code/dht11
