/*
*	RPN Calculator - Static Stack version
*		Duarte Barbosa
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 80
#define LINE_SIZE 128

int stack[SIZE] = {0}, *base = stack + 1, *top = stack, under_or_overflow; 	/* base points to the base of stack + 1 (prevention for underflows) */
char line[LINE_SIZE];

void push(int i){
	if(top == (base + SIZE)) {
		printf("Stack Overflow.\n");
		under_or_overflow = 1;
	}
	else {
		top++;
		*top = i;
	}
}

void pop(void){
	if(top == base) {
		printf("Stack Underflow.\n");
		under_or_overflow = 1;
	}
	else
		top--;
}

int main(){

	int input, eof, insuf_args = 1;
	int *previous;
	char *token;

	printf("RPN Calculator - Enter the expression to evaluate or Ctrl-D (EOF) to quit.\n");

prompt:
	for(; fgets(line, LINE_SIZE, stdin)!= NULL; insuf_args = 1, top = stack) {
		line[strlen(line) - 1] = '\0';
		token = strtok (line, " " "\t");
		if(token == NULL) {
			continue;
		}

		previous = top;

		eof = sscanf(token, "%d", &input);	/* eof = 1 means there was a number in the token */

		if(eof)
			push(input);
		else{
			printf("Weird Arguments!\n");
			goto prompt;
		}

		while ((token = strtok (NULL, " " "\t")) != NULL) {
			eof = sscanf(token, "%d", &input);

			if(eof){
				insuf_args = 0;
				previous = top;
				push(input);
			}
			else{
				if (!(strcmp (token, "+")))
					*previous += *top;
				else if (!(strcmp (token, "-")))
					*previous -= *top;
				else if (!(strcmp (token, "*")))
					*previous *= *top;
				else if (!(strcmp (token, "/"))){
					if(*top)
						*previous /= *top;
					else{
						printf("Division by Zero!\n");
						goto prompt;
					}
				}
				else{
					printf("Wrong Operand!\n");
					goto prompt;
				}
				pop();
				if(previous != base)
					previous--;
			}
		}

		if(insuf_args)
			printf("Insuficient Arguments!\n");
		else if(previous != base || top != previous)
			printf("Missing Operands!\n");
		else if(under_or_overflow){
			under_or_overflow = 0;
			goto prompt;
		}
		else
			printf("Result : %d\n", *previous);
	}

	return 0;
}
