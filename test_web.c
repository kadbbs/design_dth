#include "web.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

uint32 data;
void *fun(){
	while(1){
	data++;

	sleep(1);
	printf("data:%ld\n",data);
	}
	return NULL;
}


int main(){

	data=0;
	pthread_t tid;
	pthread_create(&tid,NULL,fun,NULL);
	
	web();






}
