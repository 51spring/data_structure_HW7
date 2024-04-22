#include<stdio.h> 
#include<stdlib.h> // malloc, free 함수를 사용 

typedef struct Node 
{ 
	int key;
	struct Node* link;
} listNode; // listNode 구조체 정의. key값과 다음 노드를 가리키는 노드 구조체 포인터 link를 가짐

typedef struct Head 
{
	struct Node* first;
} headNode; // headNode 구조체 정의. 첫번째 노드를 가리키는 노드 구조체 포인터 first를 가짐


/* 함수 리스트 */
headNode* initialize(headNode* h); // headNode 초기화 함수
int freeList(headNode* h); // 리스트 메모리 해제 함수

int insertFirst(headNode* h, int key); // 리스트 첫번째에 노드 추가 함수
int insertNode(headNode* h, int key); // 리스트가 오름차순이 되도록 노드 추가 함수
int insertLast(headNode* h, int key); // 리스트 마지막에 노드 추가 함수
 
int deleteFirst(headNode* h); // 리스트 첫번째 노드 삭제 함수
int deleteNode(headNode* h, int key); // 리스트에서 입력한 key값을 가진 노드 삭제 함수
int deleteLast(headNode* h); // 리스트 마지막 노드 삭제 함수
int invertList(headNode* h); // 리스트를 역순으로 재배치하는 함수

void printList(headNode* h); // 리스트 출력 함수

int main()
{
	char command; // 사용자로부터 입력받을 명령어
	int key; // 사용자로부터 입력받을 key값 (int)
	headNode* headnode=NULL; // headNode 포인터 변수 headnode 선언 및 초기화
	printf("2021041002 오원석\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) 
		{
		case 'z': case 'Z': // z나 Z를 입력받으면 headnode 초기화
			headnode = initialize(headnode); 
			break;
		case 'p': case 'P': // p나 P를 입력받으면 리스트 출력
			printList(headnode); 
			break;
		case 'i': case 'I': // i나 I를 입력받으면 key값을 입력받아 리스트에 노드 추가
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // d나 D를 입력받으면 key값을 입력받아 리스트에서 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // n나 N를 입력받으면 key값을 입력받아 리스트 마지막에 노드 추가
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // e나 E를 입력받으면 리스트 마지막 노드 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F': // f나 F를 입력받으면 key값을 입력받아 리스트 첫번째에 노드 추가
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // t나 T를 입력받으면 리스트 첫번째 노드 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // r나 R을 입력받으면 리스트 역순으로 재배치
			invertList(headnode);
			break;
		case 'q': case 'Q': // q나 Q를 입력받으면 프로그램 종료
			freeList(headnode);
			break;
		default: // 그 외의 문자를 입력받으면 에러 메시지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q나 Q를 입력받으면 프로그램 종료

	return 1;
}

headNode* initialize(headNode* h) // headNode 초기화 함수
{  
	if(h != NULL) // headNode가 NULL이 아니면, freelist를 호출하여 할당된 메모리 모두 해제
		freeList(h);

	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode의 메모리 할당
	temp->first = NULL; // headNode의 first를 NULL로 초기화
	return temp;
} 

int freeList(headNode* h) // 리스트 메모리 해제 함수
{
	listNode* p = h->first; // headnode의 첫번째 노드를 가리키는 포인터 p 선언 및 초기화

	listNode* prev = NULL; // 이전 노드를 가리키는 포인터 prev 선언 및 초기화
	while(p != NULL) // p가 NULL이 아닐 때까지 p를 이동하며 메모리 해제
	{ 
		prev = p;  
		p = p->link; // p를 다음 노드로 이동
		free(prev); // prev가 가리키는 노드 메모리 해제
	}
	free(h); // headnode 메모리 해제
	return 0;
}

int insertFirst(headNode* h, int key) // 리스트 첫번째에 노드 추가 함수
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
	node->key = key; // 새로운 노드의 key값을 입력받은 key값으로 초기화

	node->link = h->first; // 새로운 노드의 link를 headnode의 첫번째 노드로 초기화
	h->first = node; // headnode의 첫번째 노드를 새로운 노드로 초기화

	return 0;
}

int insertNode(headNode* h, int key) // 리스트가 오름차순이 되도록 노드 추가 함수
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
	node->key = key; // 새로운 노드의 key값을 입력받은 key값으로 초기화

	if(h->first == NULL || h->first->key > key) // headnode의 첫번째 노드가 NULL이거나 첫번째 노드의 key값이 입력받은 key값보다 크면
	{ 
		node->link = h->first; // 새로운 노드의 link를 headnode의 첫번째 노드로 초기화
		h->first = node; // headnode의 첫번째 노드를 새로운 노드로 초기화
	} 
	else 
	{ // 그 외의 경우
		listNode* current = h->first; // 첫번째 노드를 가리키는 포인터 current 선언 및 초기화
		while(current->link != NULL && current->link->key < key) { // current의 link가 NULL이 아니고 current의 link의 key값이 입력받은 key값보다 작을 때까지
			current = current->link; // current를 다음 노드로 이동
		}
		node->link = current->link; // 새로운 노드의 link를 current의 link로 초기화
		current->link = node; // current의 link를 새로운 노드로 초기화
	}
	return 0;
} 

int insertLast(headNode* h, int key) // 리스트 마지막에 노드 추가 함수
{
    listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
    node->key = key; // 새로운 노드의 key값을 입력받은 값으로 초기화
    node->link = NULL; // 새로운 노드의 link를 NULL로 초기화

    if(h->first == NULL)  
        h->first = node; // headnode의 첫번째 노드가 NULL이면 새로운 노드를 headnode의 첫번째 노드로 초기화
	else 
	{
        listNode* current = h->first; // 현재 노드를 가리키는 포인터 current 선언 및 초기화 
        while(current->link != NULL) 
		{
            current = current->link; // current link가 NULL이 아닐 때까지 current를 다음 노드로 이동
        }
        current->link = node; // current의 link를 새로운 노드로 초기화
    }
    return 0;
}


int deleteFirst(headNode* h) // 리스트 첫번째 노드 삭제 함수
{
	if(h->first == NULL) // headnode의 첫번째 노드가 NULL이면 -1 반환
		return -1; 

	listNode* node = h->first; // headnode의 첫번째 노드를 가리키는 포인터 node 선언 및 초기화
	h->first = node->link; // headnode의 첫번째 노드를 node의 link로 초기화
	free(node); // node 메모리 해제
	return 0;
}

int deleteNode(headNode* h, int key) // 리스트에서 입력한 key값을 가진 노드 삭제 함수
{
	if(h->first == NULL) // headnode의 첫번째 노드가 NULL이면 -1 반환
		return -1;

	listNode* node = h->first; // headnode의 첫번째 노드를 가리키는 포인터 node 선언 및 초기화
	listNode* prev = NULL; // 이전 노드를 가리키는 포인터 prev 선언 및 초기화

	while(node != NULL && node->key != key) // node가 NULL이 아니고 node의 key값이 입력받은 key값과 같지 않을 때까지
	{
		prev = node; // prev를 node로 초기화
		node = node->link; // node를 다음 노드로 이동
	}

	if(node == NULL) // node가 NULL이면 -1 반환
		return -1;

	if(prev == NULL) // prev가 NULL이면
		h->first = node->link; // headnode의 첫번째 노드를 node의 link로 초기화
	else 
		prev->link = node->link; // 그 외의 경우 prev의 link를 node의 link로 초기화

	free(node); // node 메모리 해제
	return 0;
}

int deleteLast(headNode* h) // 리스트 마지막 노드 삭제 함수
{
	if(h->first == NULL) // headnode의 첫번째 노드가 NULL이면 -1 반환
		return -1;

	listNode* node = h->first; // headnode의 첫번째 노드를 가리키는 포인터 node 선언 및 초기화
	listNode* prev = NULL; // 이전 노드를 가리키는 포인터 prev 선언 및 초기화

	while(node->link != NULL) // node의 link가 NULL이 아닐 때까지
	{
		prev = node; // prev를 node로 초기화
		node = node->link; // node를 다음 노드로 이동
	}

	if(prev == NULL) // prev가 NULL이면
		h->first = NULL; // headnode의 첫번째 노드를 NULL로 초기화
	else 
		prev->link = NULL; // 그 외의 경우 prev의 link를 NULL로 초기화

	free(node); // node 메모리 해제
	return 0;
}


int invertList(headNode* h) // 리스트를 역순으로 재배치하는 함수
{
    if(h->first == NULL) 
        return -1;

    listNode* prev = NULL; // 이전 노드를 가리키는 포인터 prev 선언 및 초기화
    listNode* current = h->first; // 현재 노드를 가리키는 포인터 current 선언 및 초기화
    listNode* next = NULL; // 다음 노드를 가리키는 포인터 next 선언 및 초기화

    while(current != NULL) // current가 NULL이 아닐 때까지 반복
	{ 
        next = current->link; // next를 current의 link로 초기화
        current->link = prev; // current의 link를 prev로 초기화
        prev = current; // prev를 current로 초기화
        current = next; // current를 next로 초기화
    }

    h->first = prev; // headnode의 첫번째 노드를 prev로 초기화
    return 0;
}

void printList(headNode* h) // 리스트 출력 함수
{
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) // headnode가 NULL이면 출력할 것이 없다는 메시지 출력 
	{
		printf("출력할 리스트가 없음\n");
		return;
	}
	p = h->first; // headnode의 첫번째 노드를 가리키는 포인터 p 선언 및 초기화
	while(p != NULL) // p가 NULL이 아닐 때까지 리스트 출력
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; // p를 다음 노드로 이동
		i++;
	}

	printf("  items = %d\n", i);
}

