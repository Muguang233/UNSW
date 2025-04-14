// Implementation of the Counter ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Counter.h"

struct counter {
	struct node *head;
};
struct node {
	char character[MAX_CHARACTER_LEN + 1];
	int freq;
	struct node *left;
	struct node *right;
};
Counter CounterNew(void) {
	Counter c = malloc(sizeof(struct counter));
	if(c == NULL){
		return NULL;
	}
	c->head = NULL;
	return c;
}
struct node *newNode(char *character){
	struct node *new = malloc(sizeof(struct node));
	if(new == NULL){
		return NULL;
	}
	strcpy(new->character, character);
	new->freq = 1;
	new->left = NULL;
	new->right = NULL;
	return new;
}
void freeTree(struct node *node){
	if(node == NULL){
		return;
	}
	freeTree(node->left);
	freeTree(node->right);
	free(node);
}
void CounterFree(Counter c) {
	if(c == NULL){
		return;
	}
	freeTree(c->head);
	free(c);
}
struct node *counterInsert(struct node *node, char *character){
	if(node == NULL){
		struct node *new = newNode(character);
		return new;
	}
	int result = strcmp(node->character,character);
	if(result == 0){
		node->freq++;
	}else if(result > 0){
		node->left = counterInsert(node->left, character);
	}else{
		node->right = counterInsert(node->right, character);
	}
	return node;
}

void CounterAdd(Counter c, char *character) {
	c->head = counterInsert(c->head, character);
}
int numItemsCount(struct node *node){
	if(node == NULL){
		return 0;
	}
	return 1 + numItemsCount(node->left) + numItemsCount(node->right);
}
int CounterNumItems(Counter c) {
	return numItemsCount(c->head);
}

int CounterGet(Counter c, char *character) {
	struct node *curr = c->head;
	while(curr != NULL){
		int r = strcmp(curr->character, character);
		if(r == 0){
			return curr->freq;
		}else if(r > 0){
			curr = curr->left;
		}else{
			curr = curr->right;
		}
	}
	return 0;
}
void itemCopy(struct node *node, struct item *item, int *i){
	if(node == NULL){
		return;
	}
	itemCopy(node->left, item, i);
	strcpy(item[*i].character, node->character);
	item[*i].freq = node->freq;
	(*i) += 1;
	itemCopy(node->right, item, i);
}

struct item *CounterItems(Counter c, int *numItems) {
	*numItems = numItemsCount(c->head);
	if(*numItems == 0){
		return NULL;
	}
	struct item *itemList = malloc(*numItems * sizeof(struct item));
	if(itemList == NULL){
		return NULL;
	}
	int index = 0;
	int *pi = &index;
	itemCopy(c->head, itemList, pi);
	return itemList;
}

