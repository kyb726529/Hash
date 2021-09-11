#include "stddef.h"
#include <stdlib.h>    // malloc, free �Լ��� ����� ��� ����
#include <stdio.h>//fprintf ���
#include <malloc.h>
#define TABLE_SIZE 7
//������ Ű�� ���� ü�̴��ؽ� ������ ���� ������ ���� ����ü ����
typedef struct {
	int key;
}element;

struct list {//��� ���ִ� ����..?
	element item;
	struct list* link;//���� ������..? ����ü ���� list�� �ּҸ� ����Ű�� ����?!
};
struct list* hash_table[TABLE_SIZE];//list ��� ����ü�� ����Ű�� �����͹迭..?

int hash_fuction(int key) {//�������� �ּҷ� ��ȯ
	return key % TABLE_SIZE;//�����Լ�
}
void hash_chain_add(element item, struct list* ht[]) {//���� �߰� �Լ��� item�̶� ht[]�� �Ű������� ����!(�������������)
	//item : ������ ���̳�!
	int hash_value = hash_fuction(item.key);//��ȯ�� �ּҰ��� hash_value�� ����
	struct list* ptr;//�����뵵?
	struct list* node_before = NULL;//�����뵵?
	struct list* node = ht[hash_value];//������̺��� ������ ���� �ּҹ�° �迭(��Ŷ?)
	for (; node; node_before = node, node = node->link) {//�������ϱ�..
		if (node->item.key == item.key) {//������ ���� �̹� �ؽ������̺� �ִٸ�..
			fprintf(stderr, "�̹� Ž��Ű�� ����Ǿ�����");
			return;
		}
	}
	ptr = (struct list*)malloc(sizeof(struct list));//�����Ҵ� ���Ѱ�..?
	ptr->item = item;//�ϴ� ptr�� ����ü listŸ��, �� ����ü�� ������� item�� ��item�� �ִ� ���ε�..!
	ptr->link = NULL;//����ü ������� link�� ����Ű�� ���� ����,�ٵ� link�� �ڽ��� ����Ű�°� �ƴϾ�?
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
			fprintf(stderr, "Ž�� %d ����\n", item.key);
			return;
		}
	}
	printf("Ű�� ã�� ����");
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
	printf("git");
	return 0;
}