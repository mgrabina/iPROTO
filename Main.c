#include <stdio.h>
#include <stdlib.h>

void main(){
	int c;
	printf("Welcome to our exercises. Please select an option: 1 \n");
	c = getchar();
	switch(c){
		case '1':
				break; 
		default:
				printf("Error. Closing app.\n");
				exit(0);
	}
	return 0;
}