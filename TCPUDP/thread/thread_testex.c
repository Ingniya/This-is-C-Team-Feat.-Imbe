#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 6

void *showdata(void *data);

int mydata[6] = {10, 11, 12, 13, 14, 15};

int main()
{
	pthread_t thread_t;
	int state;
	int i;
	
	printf("\nCreate Thread\n");
	
	if(pthread_create(&thread_t, 0, showdata, 0) < 0)
	{
		perror("Thread Create Error!");
		exit(0);
	}
	
	pthread_join(thread_t, NULL);
	
	printf("Final\n");
	
	return 0;
	
}

void *showdata(void *data)
{
	int i;
	
	printf("\nShow All List Data\n");
	
	for(i=0; i<DATA_SIZE; i++)
	{
		printf("Mydata[%d] : %d\n", i, mydata[i]);
	}
	return 0;
}