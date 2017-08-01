#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 6

void* showData(void *data);
int mydata[6] = {10,11,12,13,14,15};
 
int main()
{
	pthread_t thread_t;
	int state;
	int i;
	
	printf("\nCreate Thread \n");
    // 쓰레드를 생성한다. 
	if(pthread_create(&thread_t, 0, showData, 0) < 0)
    {
       	perror("thread create error:");
       	exit(0);
    }
 
	pthread_join(thread_t, NULL);
	
	printf("Final\n");

    return 0;
}

void* showData(void *data) 
{
	int i;
	
  	printf("\nShow All List Data\n");
	for(i=0;i<DATA_SIZE;i++) {
       printf("mydata[%d] : %d\n", i, mydata[i]);
    }
	return 0;
}
