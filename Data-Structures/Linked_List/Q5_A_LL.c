//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
// 음? 이거 정의부랑 선언부 인자 달라도 됨? 된대용
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

/*
	frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList) 작성
	하나의 링크드 리스트를 정확히 반으로 쪼갭니다!
	요소가 홀수 개면, 남는 놈은 앞쪽으로 감
*/

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
	    printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// 요소 하나씩 옮기는 방식
void frontBackSplitLinkedList_insert(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	// 사이즈가 짝수면 사이즈 반만큼 순회 돈다
	// 사이즈가 홀수면 사이즈 반 + 1 만큼 순회 돈다
	// 메인에서 remove로 원본, 프론트, 백 전부 날려주니까 원본 보존 신경 안 써도 됨
	// 근데 남겨두는 게 정석이긴 해용
	
	ListNode *cur = ll->head;
	int size = ll->size;
	int half = (size + 1) / 2;

	for (int i = 0; i < size; i++) {
		if (i < half) {
			insertNode(resultFrontList, resultFrontList->size, cur->item);
		}
		else {
			insertNode(resultBackList, resultBackList->size, cur->item);
		}
		cur = cur->next;
	}
}

// 노드 중간에서 끊는 방식
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	// 빈 리스트일때
	if (ll == NULL || ll->size == 0) {
        resultFrontList->head = NULL;
        resultFrontList->size = 0;
        resultBackList->head = NULL;
        resultBackList->size = 0;
        if (ll != NULL) ll->size = 0; // ll->head는 이미 NULL
        return;
    }
	
	ListNode *cur = ll->head;
	int half = (ll->size + 1) / 2;

	// 앞리스트 헤드 연결
	resultFrontList->head = ll->head;

	for (int index = 1; index < half; index++) {
		cur = cur->next;
	}

	// 다음 노드를 뒷리스트 헤드에 연결
	resultBackList->head = cur->next;
	// 뒤 날림
	cur->next = NULL;

	// 사이즈 갱신
	resultFrontList->size = half;
	resultBackList->size = ll->size - half;

	ll->head = NULL;
	ll->size = 0;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
