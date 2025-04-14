// Implementation of the Huffman module

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Counter.h"
#include "File.h"
#include "character.h"
#include "huffman.h"

struct List {
	struct huffmanTree *tree;
	struct List *next;
};
struct List *newList(struct huffmanTree *tree) {
	struct List *new = malloc(sizeof(struct List));
	if (new == NULL) {
		return NULL;
	}
	new->tree = tree;
	new->next = NULL;
	return new;
}

// Task 1
void decode(struct huffmanTree *tree, char *encoding, char *outputFilename) {
	struct file *output = FileOpenToWrite(outputFilename);
	struct huffmanTree *curr = tree;
	for (int i = 0; encoding[i] != '\0'; i++) {
		if (encoding[i] == '0') {
			curr = curr->left;
		} else if (encoding[i] == '1') {
			curr = curr->right;
		}
		if (curr->left == NULL && curr->right == NULL &&
		    curr->character != NULL) {
			FileWrite(output, curr->character);
			curr = tree;
		}
	}
	FileClose(output);
}
//new huffmantree node creation
struct huffmanTree *newTree(char *character, int freq) {
	struct huffmanTree *new = malloc(sizeof(struct huffmanTree));
	if (new == NULL) {
		return NULL;
	}
	if (character != NULL) {
		new->character = strdup(character);
	} else {
		new->character = NULL;
	}
	new->freq = freq;
	new->left = NULL;
	new->right = NULL;
	return new;
}
// Task 3
struct huffmanTree *createHuffmanTree(char *inputFilename) {
	Counter c = CounterNew();
	if (c == NULL) {
		return NULL;
	}
	struct file *input = FileOpenToRead(inputFilename);
	char character[MAX_CHARACTER_LEN + 1];
	while (FileReadCharacter(input, character)) {
		CounterAdd(c, character);
	}
	FileClose(input);
	int numItems = 0;
	struct item *item = CounterItems(c, &numItems);
	struct List *head = malloc(sizeof(struct List));
	if (head == NULL) {
		return NULL;
	}
	head->next = NULL;
	for (int i = 0; i < numItems; i++) {
		struct huffmanTree *tree = newTree(item[i].character, item[i].freq);
		struct List *list = newList(tree);
		if (head->next == NULL || head->next->tree->freq >= item[i].freq) {
			list->next = head->next;
			head->next = list;
		} else {
			struct List *curr = head->next;
			while (curr->next != NULL &&
			       curr->next->tree->freq < item[i].freq) {
				curr = curr->next;
			}
			list->next = curr->next;
			curr->next = list;
		}
	}
	while (head->next != NULL && head->next->next != NULL) {
		struct List *min1 = head->next;
		struct List *min2 = head->next->next;
		int sum = min1->tree->freq + min2->tree->freq;
		struct huffmanTree *new = newTree("", sum);

		new->left = min1->tree;
		new->right = min2->tree;
		head->next = min2->next;
		free(min1);
		free(min2);

		if (head->next == NULL || head->next->tree->freq >= new->freq) {
			struct List *newListnode = newList(new);
			newListnode->next = head->next;
			head->next = newListnode;
		} else {
			struct List *curr = head->next;
			while (curr->next != NULL && curr->next->tree->freq < new->freq) {
				curr = curr->next;
			}
			struct List *newListnode = newList(new);
			newListnode->next = curr->next;
			curr->next = newListnode;
		}
	}
	struct huffmanTree *headTree = head->next->tree;
	free(head->next);
	free(head);
	free(item);
	CounterFree(c);
	return headTree;
}

// Task 4
char *encode(struct huffmanTree *tree, char *inputFilename) {
	return NULL;
}
