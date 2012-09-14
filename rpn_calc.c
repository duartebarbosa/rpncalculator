/* RPN Calculator - Static Stack based version - rpn_calc.c dsrb@Skywalker IST-TP LEIC n.º 65893  - 2010 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 80
#define max_line_size 128

int stack[SIZE] = {0}, *top = stack, *p1 = stack, flag_over_under; 	/* top points to the top of stack */
char line[max_line_size];

void push(int i){
	p1++;

	if(p1 == (top + SIZE)) {
		printf("Stack Overflow.\n");
		flag_over_under = 1;
	}
	*p1 = i;
}

void pop(void){
	*p1 = 0;
	if(p1 == top) {
		printf("Stack Underflow.\n");
		flag_over_under = 1;
	}
	p1--;
}

int main(){

	int input, eof, flag = 1;
	int * p2;
	char *corte;

	top++;

	printf("RPN Calculator - Enter the expression to evaluate or Ctrl-D (EOF) to quit.\n");

prompt:
	for(; fgets(line, max_line_size, stdin)!= NULL; flag = 1, p1 = stack) {
		line[strlen(line) - 1] = '\0';
		corte = strtok (line, " " "\t");
		if(corte == NULL) {
			continue;
		}

		p2 = p1;

		eof = sscanf(corte, "%d", &input);

		if(eof)
			push(input);
		else{
			printf("Weird Arguments!\n");
			goto prompt;
		}

		while ((corte = strtok (NULL, " " "\t")) != NULL) {
			eof = sscanf(corte, "%d", &input);

			if(eof){
				flag = 0;
				p2 = p1;
				push(input);
			}
			else{
				if (!(strcmp (corte, "+")))
					*p2 += *p1;
				else if (!(strcmp (corte, "-")))
					*p2 -= *p1;
				else if (!(strcmp (corte, "*")))
					*p2 *= *p1;
				else if (!(strcmp (corte, "/"))){
					if(*p1)
						*p2 /= *p1;
					else{
						printf("Division by Zero!\n");
						goto prompt;
					}
				}
				else{
					printf("Kernel Panic!\n");
					goto prompt;
				}
				pop();
				if(p2 != top)
					p2--;
			}
		}

		if(flag)
			printf("Insuficient Arguments!\n");
		else if(p2 != top || p1 != p2)
			printf("Missing Operands!\n");
		else if(flag_over_under)
			goto prompt;
		else
			printf("Result : %d\n", *p2);
	}

	return 0;
}
