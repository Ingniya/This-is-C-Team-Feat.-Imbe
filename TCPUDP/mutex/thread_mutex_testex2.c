#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

#define DATA_SIZE 10

pthread_mutex_t mutex;

List *pMyList = NULL;

void *showdata(void *);
void *deldata(void *);

int main()
{
	pthread_t thread_t0, thread_t1;
	
	int state, i;
	
	Node *pnode;
	
	state = pthread_mutex_init(&mutex, NULL);
	
	if(state != 0)
	{
		perror("Fail to Init Mutex!!");
		exit(1);
	}
	
	
	printf("We need a List at First!!\n");
	
	pMyList = InitList();
	
	if(pMyList == 0)
		return -1;
	
	printf("\nInsert Data and Make a node for List 0~9\n");
	
	for(i=0; i<DATA_SIZE; i++)
		AddNode(pMyList,i);
	
	if(pthread_create(&thread_t0, NULL, showdata, 0) < 0)
	{
		perror("Thread0 Create Error!!");
		exit(1);
	}
	
	if(pthread_create(&thread_t1, NULL, deldata, 0) < 0)
	{
		perror("Thread1 Create Error!!");
		exit(1);
	}
	pthread_join(thread_t0, NULL);
	pthread_join(thread_t1, NULL);
	
	printf("Final\n");
	DeleteList(pMyList);
	pthread_mutex_destroy(&mutex);
	
	return 0;
	
}


void *deldata(void *data)
{
	int i;
	
	sleep(2);
	
	for(i=0; i<(DATA_SIZE/2); i++)
	{
		pthread_mutex_lock(&mutex);
		DeleteNode(pMyList, i);
		
		printf("Deleted %d\n", i);
		
		pthread_mutex_unlock(&mutex);
		
		sleep(1);
	}
	
	return 0;
}



void *showdata(void *data)
{
	int cnt = 0, i;
	
	Node *pnode;
	
	
	for(cnt=0; cnt<DATA_SIZE; cnt++)
	{
		printf("\nShow All List Date : %d\n", cnt);
		
		pthread_mutex_lock(&mutex);
		
		pnode = FirstNode(pMyList);
		
		i = 0 ;
		
		printf("%d Data : %d \n", i, pnode->data);
		
		while((pnode = NextNode(pMyList)) != NULL)
		{
			i++;
			
			printf("%d Data : %d\n", i, pnode->data);
		}
		
		pthread_mutex_unlock(&mutex);
		
		sleep(2);
	}
	return 0;
}
