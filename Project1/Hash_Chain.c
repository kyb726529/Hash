#include "stddef.h"
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일
#include <stdio.h>//fprintf 사용
#include <malloc.h>
#define TABLE_SIZE 7
//정수형 키에 대한 체이닝해싱 구현을 위해 다음과 같은 구조체 선언
typedef struct {
	int key;
}element;

struct list {//얘는 왜있는 거지..?
	element item;
	struct list* link;//무슨 뜻이지..? 구조체 변수 list의 주소를 가르키는 변수?!
};
struct list* hash_table[TABLE_SIZE];//list 노드 구조체를 가리키는 포인터배열..?

int hash_fuction(int key) {//나머지를 주소로 반환
	return key % TABLE_SIZE;//제산함수
}
void hash_chain_add(element item, struct list* ht[]) {//원래 추가 함수에 item이랑 ht[]가 매개변수로 들어갔엄!(선형조사법에서)
	//item : 삽입할 값이네!
	int hash_value = hash_fuction(item.key);//반환된 주소값을 hash_value에 넣음
	struct list* ptr;//무슨용도?
	struct list* node_before = NULL;//무슨용도?
	struct list* node = ht[hash_value];//헤시테이블에서 삽입할 값의 주소번째 배열(버킷?)
	for (; node; node_before = node, node = node->link) {//무슨뜻일까..
		if (node->item.key == item.key) {//삽입할 값이 이미 해시테테이블에 있다면..
			fprintf(stderr, "이미 탐색키가 저장되어있음");
			return;
		}
	}
	ptr = (struct list*)malloc(sizeof(struct list));//동적할당 왜한거..?
	ptr->item = item;//일단 ptr은 구조체 list타입, 그 구조체의 멤버변수 item에 값item을 넣는 것인듯..!
	ptr->link = NULL;//구조체 멤버변수 link가 가르키는 것은 없어,근데 link는 자신을 가르키는거 아니야?
	if (node_before)
		node_before->link = ptr;
	else
		ht[hash_value] = ptr;
}
void hash_chain_search(element item, struct list* ht[]) {
	struct list* node;
	int hash_value = hash_fuction(item.key);
	for (node = ht[hash_value]; node; node = node->link) {
		if (node->item.key == item.key) {
			fprintf(stderr, "탐색 %d 성공\n", item.key);
			return;
		}
	}
	printf("키를 찾지 못함");
}
void hash_chain_print(struct list* ht[]) {
	struct list* node;
	printf("\n===============\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[%d]->", i);
		for (node = ht[i]; node; node = node->link) {
			printf("%d->", node->item.key);
		}
		printf("\n");
	}
	printf("\n===============\n");
}
#define SIZE 5

int main(void) {
	int data[SIZE] = { 8,1,9,6,13 };
	element e;
	for (int i = 0; i < SIZE; i++) {
		e.key = data[i];
		hash_chain_add(e, hash_table);
		hash_chain_print(hash_table);
	}
	for (int i = 0; i < SIZE; i++) {
		e.key = data[i];
		hash_chain_search(e, hash_table);
	}
	return 0;
}