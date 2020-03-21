typedef struct node {
		char rank;
		char suit;
		struct node* next;
}node;

node* coveredTable[7]; 
node* uncoveredTable[7]; 
node* stockStack;
node* wasteStack;

node* clubsFoundation;
node* diamondsFoundation;
node* heartsFoundation;
node* spadesFoundation;
