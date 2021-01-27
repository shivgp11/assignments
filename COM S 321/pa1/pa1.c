// Name: Shiv Patel
// Netid: shivgp11

#include <stdio.h>
#include <stdlib.h>

void fill(int** addr, size_t length);
void print_arr(int** addr, size_t length);
int findSortedPos(int** addr, int val, int final);
void shiftRight(int** addr, int p, int pos);
void insertSortedPos(int** addr, int pos);
void insertionSort(int** addr, int length); 

int main() {
	int* arr = 0;
	int** addr = &arr;
	fill(addr, 10);
	print_arr(addr, 10);
	insertionSort(addr, 10);
	print_arr(addr, 10);
	
}

void fill(int** addr, size_t length) {
	*addr = (int*)malloc(sizeof(int) * length);
	int num = length - 1;
	for(int i = 0; i < length; i++) {
		*(*addr + i) = num;
		num--;
	}
}

void insertionSort(int** addr, int length) {
	for(int i = 1; i < length; i++) {
		insertSortedPos(addr, i);
	}
}

void insertSortedPos(int** addr, int pos) {
	int val = *(*addr + pos);	
	int p = findSortedPos(addr, val, pos);
	shiftRight(addr, p, pos);
	*(*addr + p) = val;
}

int findSortedPos(int** addr, int val, int pos) {
	for(int i = 0; i < pos; i++) {
		if(*(*addr + i) >= val) {
			return i;
		}
	}
}

void shiftRight(int** addr, int p, int pos) {
	for(int i = pos - 1; i >= p; i--) {
		*(*addr + i + 1) = *(*addr + i);
	}
}

void print_arr(int** addr, size_t length) {
	for(int i = 0; i < length; i++) {
		printf("%d ", *(*addr + i));
	}
	printf("\n");
}






