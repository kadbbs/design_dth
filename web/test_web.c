#include "web.h"
#include "server.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int data;
void *fun(){
	web();
}


int main(){

	pthread_t tid;
	pthread_create(&tid,NULL,fun,NULL);
	server();
	web();






}
