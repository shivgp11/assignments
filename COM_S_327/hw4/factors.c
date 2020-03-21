#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
	Author: Shiv Patel
*/
unsigned* build_factors(unsigned N);
void show_array(unsigned* A);
unsigned* build_common(unsigned* A, unsigned* B);
int main() {
	printf("Enter two integers M and N: ");
	int pa, pb;
	scanf("%d %d", &pa, &pb);
	unsigned* a = build_factors(pa);
	unsigned* b = build_factors(pb);
	printf("%d has factors: ", pa); 
	show_array(a);
	printf("%d has factors: ", pb);
	show_array(b);
	unsigned* c = build_common(a,b);
	printf("%d and %d share factors: ", pa, pb);
	show_array(c);
	free(a);
	free(b);
	free(c);
}

unsigned* build_factors(unsigned N) {
	
	unsigned n = N;
	unsigned count = 0;
	unsigned* factors = (unsigned*)malloc(256 * sizeof(unsigned));
	
	if(N == 1 || N == 0) {
		factors = NULL;
		return factors;
	}
	
	while(n % 2 == 0) {
		factors[count] = 2;
		count++;
		n = n/2;
	}
	for(int i = 3; i <= sqrt(n); i = i + 2) {
		while(n%i == 0) {
			factors[count] = i;
			count++;
			n = n/i;
		}
	}
	
	if(n > 2) {
		factors[count] = n;
		count++;
		n = n/n;
	}
	factors[count] = 0;
	count++;
	
	factors = (unsigned*)realloc(factors, count * sizeof(unsigned));
	
	return factors;

}
 void show_array(unsigned* A) {
	 if(A == NULL) {
		
	 }
	for(;;) {
		if(*(A + 1) == 0) {
			printf("%d\n", *A);
			break;
		}
		else {
			printf("%d, ", *A);
			A++;
		}
	}
	
 }
 unsigned* build_common(unsigned* A, unsigned* B) {
	unsigned* cf = (unsigned*)malloc(256*sizeof(unsigned));
	int i = 0;
	int j = 0;
	int count = 0;
	for(;;) {
		if(*A == 0 || *B == 0) {
			break;
		}
		if(*A == *B) {
			*cf = *A;
			cf++;
			A++;
			B++;
			count++;
		}
		else if(*A < *B) {
			A++;
		}
		else {
			B++;
		}
	}

	*cf = 0;
	count++;
	cf = cf - (count - 1);
	cf = (unsigned*)realloc(cf, count * sizeof(unsigned));
	return cf;
 }
	

