#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

typedef struct node {
	struct node* out;
	int in;
}node;

node* vars[9];

int main() {
	
	int total, src, dest;
	char assign, help;
	char arrow[2];
	
	//scanning number of nodes
	scanf("%d\n", &total);
	//array of node pointers from 0 to N
	node** nodes = (node**)calloc(total, sizeof(node*));
	//filling up node pointer array with node pointers
	for(int i = 0; i < total; i++) {
		nodes[i] = (node*)calloc(1, sizeof(node));
	}
	while(!feof(stdin)) {
		scanf("%c", &assign);
		scanf("%c", &help);
		scanf("%d", &src);
		fgets(arrow, 3, stdin);
		scanf("%d\n", &dest);
		if(assign == 'V') {
			if (src < 1 || src > 9) {
				fprintf(stderr, "Variable number must be between 1 and 9\n");
				return 0;
			}				 
			if(dest < 0 || dest > total) {
				fprintf(stderr, "Node index must be between 1 and %d\n", total);
				return 0;
			
			}
			//decrease ref count of destination
			if(vars[src - 1] != 0) {
				vars[src - 1]->in--;
			}
			//link and increase ref count 
			if(dest == 0) {
				vars[src - 1] = 0;
			}
			else {
				(nodes[dest - 1]->in)++;
				vars[src - 1] = nodes[dest - 1];
			}
		}
		if (assign == 'L') {
			if(src < 1 || src > total || dest < 0 || dest > total) {
				fprintf(stderr, "Node index must be between 1 and %d\n", total);
				return 0;
			}
			if(nodes[src - 1]->out != 0) {
				(nodes[src - 1]->out)->in--;
			}
			if(dest == 0) {
				nodes[src - 1]->out = 0;
			}
			else {
				(nodes[dest - 1]->in)++;
				nodes[src - 1]->out = nodes[dest - 1];
			}
		}
	}
	//printing
	for(int i = 0; i < total; i++) {
		if(nodes[i]->in > 0) {
			printf("Node %d has %d incoming pointers\n", i + 1, nodes[i]->in);
		}
	}
	
	return 1;
}
