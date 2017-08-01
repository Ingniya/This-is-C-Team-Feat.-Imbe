#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

#define DATA_SIZE 6

List *pMyList = NULL;

void *showdata(void *);
void *deldata(void *);

int main()
{
	pthread_t thread_t0, thread_t1;
	
	int state, i;
	
	Node *pnode;
	
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
	
	return 0;
	
}


void *deldata(void *data)
{
	int i;
	
	sleep(1.5);
	
	for(i=0; i<(DATA_SIZE/2); i++)
	{
		DeleteNode(pMyList, i);
		
		printf("Deleted %d\n", i);
		
		sleep(1.5);
	}
	
	return 0;
}



void *showdata(void *data)
{
	int cnt = 0, i;
	
	Node *pnode;
	
	
	for(cnt=0; cnt<5; cnt++)
	{
		printf("\nShow All List Date : %d\n", cnt);
		pnode = FirstNode(pMyList);
		
		i = 0 ;
		
		printf("%d Data : %d \n", i, pnode->data);
		
		while((pnode = NextNode(pMyList)) != NULL)
		{
			i++;
			
			printf("%d Data : %d\n", i, pnode->data);
		}
		sleep(1);
	}
	return 0;
}
