#include <stdio.h>
#include <stdlib.h>

#include "DoubleLinkedList.h"

List * InitList() {
	List * list = NULL;

	//생성
	list = (List *)malloc(sizeof(List));
	if(list == NULL) {
		printf("fail malloc\n");
		return NULL;
	}
	//초기화
	list->head = NULL;
	list->tail = NULL;
	list->cur = NULL;

	return list;

}

Node * AddNode(List * list, int data) {
	Node * newNode = NULL;
	newNode = (Node*) malloc(sizeof(Node));
	if(newNode == 0) {
		return NULL;
	}

	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	if(list->head == NULL) {
		list->head = newNode;
		list->cur = list->head;
	}
	else {
		list->cur->next = newNode;
		newNode->prev = list->cur;
		list->cur = newNode;
	}
	list->tail = newNode;
	return newNode;

}

Node * SearchNode(List * list, int word) {

	Node * pos = NULL;
	pos = list->head;

	while(pos!=NULL && (pos->data != word)) {
		pos = pos->next;
	}

	if(pos == NULL)
		return NULL;
	else
		return pos;
}

Node * FirstNode(List * list) {
	if(list->head == NULL) {
		return NULL;
	}
	list->cur = list->head;
	return list->head;
}

Node * NextNode(List * list) {
	Node * temp = NULL;
	if(list->head == NULL) {
		return NULL;
	}
	temp = list->cur->next;
	list->cur = list->cur->next;
	return temp;
}

Node * LastNode(List * list) {
	if(list->head == NULL) {
		return NULL;
	}
	list->cur = list->tail;
	return list->tail;
}
Node * ReverseNextNode(List * list) {
	Node * temp = NULL;
	if(list->head == NULL) {
		return NULL;
	}
	temp = list->cur->prev;
	list->cur = list->cur->prev;
	return temp;
}

void DeleteList(List * list) {
	Node *pos = NULL;
	Node *temp = NULL;

	if(list == NULL)
		return;

	pos = list->head;

	while(pos != NULL) {
		temp = pos;
		pos = pos->next;
		free(temp);
	}
	if(list != NULL)
		free(list);
}

//단순 연결 리스트 특정 데이터 삭제
int DeleteNode(List *list, int data)
{
	Node* prev = NULL;
	Node* next = NULL;
	Node* pos = NULL;
	pos = list->head;
	prev = list->head;
	next = pos->next;

	while(pos != NULL && (data != pos->data) ) {
		prev = pos;
		pos = pos->next;
	}
	if(pos == NULL)
		return 0;  
	prev->next = pos->next;
	if(pos->next) {
		pos->next->prev = pos->prev;
	}
	if(pos == list->head) {
		list->head = pos->next;
	}
	if(pos == list->tail) {
		list->tail= pos->prev;
	} 
	free(pos);
	pos=NULL;
	return 1;
}

