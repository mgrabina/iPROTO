#include <stdio.h>
#include <stdlib.h>

int main(){
	int c;
	printf("Welcome to our exercises. Please select an option: {1} \n");
	c = getchar();
	switch(c){
		case '1': printf("- Interproccess comunication -\n");
				
				break; 
		default:
				printf("Error. Closing app.\n");
				exit(0);
	}
	return 0;
}