#include <stdio.h>

struct window {
	unsigned int xlow;
	unsigned int ylow;
	unsigned int xhigh;
	unsigned int yhigh;
	char wch;
};

void fill_line(struct window W[], unsigned int Wsize, unsigned int x1, unsigned int x2, unsigned int y, char line[]);

unsigned fill_windows(struct window W[], unsigned wmax);

int main(){
	
	unsigned int xlow,ylow,xhigh,yhigh, windows;
	char j;
	scanf("%u",&xlow ); 
	scanf("%c", &j);
	scanf("%u", &ylow);
	scanf("%c", &j);
	scanf("%u", &xhigh);
	scanf("%c", &j);
	scanf("%u", &yhigh);
	scanf("%u", &windows);
	
	
	struct window W[windows];
	
	fill_windows(W, windows);
	
	for(unsigned i = ylow; i <= yhigh; i++) {
		char line[(xhigh - xlow) + 1];
		fill_line(W, windows, xlow, xhigh, i, line);
	}
	
	
	
	
	return 0;
} 

void fill_line(struct window W[], unsigned Wsize, unsigned x1, unsigned x2, unsigned y, char line[]){
	
	
	for(int i = 0; i <= x2 - x1; i++) {
		line[i] = ' ';
	}
	unsigned xincriment = x1;
	for(int i = 0; i <= x2 - x1; i++) {
		for(int j = 0; j < Wsize; j++) {
			if(W[j].ylow <= y && W[j].yhigh >= y) {
				if(W[j].xlow <= xincriment && W[j].xhigh >= xincriment) {
					line[i] = W[j].wch;
				}
			}
		}
		xincriment++;
	}
	
	// for(int i = 0; i <= x2 - x1; i++) {
		// for(int j = 0; j < Wsize; j++) {
			// if(W[j].ylow <= y && W[j].yhigh >= y) {
				// if(i >= x1 && i <= x2 && i >= W[j].xlow && i <= W[j].xhigh) {
					// line[i] = W[j].wch;
				// }
			// }
		// }
	// }
	
	
	printf("%s\n", line);
	
}
unsigned fill_windows(struct window W[], unsigned wmax) {
	unsigned int xlow,ylow,xhigh,yhigh;
	char c;
	char j = ' ';
	
	for( unsigned int i = 0; i < wmax; i++) {
		
		scanf("%u",&xlow ); 
		scanf("%c", &j);
		scanf("%u", &ylow);
		scanf("%c", &j);
		scanf("%u", &xhigh);
		scanf("%c", &j);
		scanf("%u", &yhigh);
		scanf("%c", &j);
		scanf("%c", &c);
		
		W[i].xlow = xlow;
		W[i].ylow = ylow;
		W[i].xhigh = xhigh;
		W[i].yhigh = yhigh;
		W[i].wch = c;
		
	}
	return wmax;
}



