#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
/*
Shiv Patel
*/
typedef struct node {
	char str[32];
	unsigned count;
	struct node* next;
}node;

typedef struct hashtable {
	unsigned size;
	node** table;
}hashtable;

void init_table(struct hashtable* T, unsigned size);
void add_to_table(struct hashtable* T, char* str);
void show_table(struct hashtable* T);
unsigned long hash(char *str);
void free_table(struct hashtable* T);

int main() {
	hashtable h; 
	hashtable *hp = &h;
	int size;
	scanf("%d", &size);
	
	init_table(hp, size);
	char word[32];
	while(!feof(stdin)) {
		scanf("%s\n", word);
		add_to_table(hp, word);
	
	}
	show_table(hp);
	free_table(hp);
	
	
	return 0;
}
void init_table(struct hashtable* T, unsigned size) {
	T->size = size;
	T->table = (node**)calloc(size, sizeof(node*));
	
	
	
}

void add_to_table(struct hashtable* T, char* str) {

	for(int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
	
	int h = hash(str) % (T->size);
	
	//printf("%s %d %p\n", str, h, (T->table) + h);
	
	node* current = *((T->table) + h);
	
	if(current == 0) {
		current = (node*)malloc(sizeof(node));
		current->count = 1;
		strcpy(current->str, str);
		*((T->table) + h) = current;
		//printf("(1): %s %d %p %d\n", current->str, h, current, current->count);
	}
	else {
		for(;;) {
			if(strcmp(current->str, str) == 0) {
				(current->count)++;
				//printf("(2): %s %d %p %d\n", current->str, h, current, current->count);
				break;
			}
			else if(current->next == 0) {
				current = (node*)malloc(sizeof(node));
				current->count = 1;
				strcpy(current->str, str);
				current->next = *((T->table) + h);
				*((T->table) + h) = current;
				//printf("(3): %s %d %p %d\n", current->str, h, current, current->count);
				break;
			}
			else {
				current = current->next;
				//printf("(4):\n");
			}
		}
	}

	
	
}

void show_table(struct hashtable* T) {
	node* current;
	for(int i = 0; i < T->size; i++) {
		current = *((T->table) + i);
		while(current != 0) {
			printf("%d %s\n", current->count, current->str);
			current = current->next;
		}
	}
	
}

unsigned long hash(char *str)
  {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; 

    return hash;
  }
  
void free_table(struct hashtable* T) {
	node* current;
	node* next;
	for(int i = 0; i < T->size; i++) {
		current = *((T->table) + i);
		while(current != 0) {
			next = current->next;
			free(current);
			current = next;
		}
	}
	free(T->table);
}

