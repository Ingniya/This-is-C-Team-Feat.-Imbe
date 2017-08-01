
typedef struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct List {
	Node * head;
	Node * tail;
	Node * cur;
} List;

List * InitList();
Node * AddNode(List * list, int data);
int DeleteNode(List * list, int word);
Node * SearchNode(List * list, int word);
void DeleteList(List * list);
Node * FirstNode(List * list);
Node * NextNode(List * list);

Node * LastNode(List * list);
Node * ReverseNextNode(List * list);