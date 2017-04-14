/* Joey Nelson
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

bool debug = false;

typedef struct{
	int size;
	int top;
	char* darr;
} stack;

void initializeStack(stack* sp){

	sp->top = -1;
	sp->size = 2;
	sp->darr = (char*)malloc(sizeof(char) * sp->size);
}

bool isEmpty(stack* sp){
	
	bool empty = false;
	
	if(sp->top == -1)
		empty = true;

	return empty;	
}

void push(stack* sp, char a){

	if(debug == true)
		printf("\npushing %c onto stack\n");
	
	void growArray(stack* sp);
	
	sp->top = sp->top + 1;
	
	if(sp->top == sp->size)
		growArray(sp);

	sp->darr[sp->top] = a;
}

void pop(stack* sp, char a){

	if(debug == true)
		printf("\npopping %c from stack\n", a);

	sp->top = sp->top - 1;
}

char topElement(stack* sp){

	char a;
	a = sp->darr[sp->top];	

	return a;
}

void stackReset(stack* sp){

	sp->size = 2;
	sp->top = -1;
	free(sp->darr);
	sp->darr = (char*)malloc(sizeof(char) * sp->size);
}

void growArray(stack* sp){

	if(debug == true)
		printf("\narray grew from size %i to %i. %i values were copied\n", sp->size, sp->size + 2, sp->size);

	sp->size = sp->size + 2;
	char* temp = (char*)malloc(sizeof(char) * sp->size);

	int i;
	for(i = 0; i < sp->size; i++)
		temp[i] = sp->darr[i];

	free(sp->darr);
	sp->darr = temp;
}

void missing(char a, int i){

	printf("\n");
	
	int j;
	for(j = 0; j < i; j++)
		printf("  ");

	printf("^ missing %c\n\n", a);
}

void expecting(char a, int i){

	printf("\n");

	int j;
	for(j = 0; j < i; j++)
		printf("  ");

	printf("^ expecting ");
	
	switch(a){
	
		case '(' :
			printf("%c\n\n", ')');
			break;
		case '{' :
			printf("%c\n\n", '}');
			break;
		case '[' :
			printf("%c\n\n", ']');
			break;
		case '<' :
			printf("%c\n\n", '>');
			break;

	}
}

void endMissing(char a, int i){

	printf("\n");

	int j;
	for(j = 0; j < i; j++)
		printf("  ");

	printf("^ missing ");
	
	switch(a){
	
		case '(' :
			printf("%c\n\n", ')');
			break;
		case '{' :
			printf("%c\n\n", '}');
			break;
		case '[' :
			printf("%c\n\n", ']');
			break;
		case '<' :
			printf("%c\n\n", '>');
			break;

	}

}

int main(int argc, char** argv){
	
	int i;
	for(i = 0; i < argc; i++)
		if(argv[i][0] == '-' && argv[i][1] == 'd' && argv[i][2] == '\0')
			debug = true;

	stack st;
	stack* sp;
	sp = &st;
	
	initializeStack(sp);
	
	int x;
	int y;
	int j;

	printf("Type in a line of input. Type q or Q to quit\n");

	char temp[300];
	fgets(temp, 300, stdin);
	int len = strlen(temp);

	char* buffer;
	for(i = 0; i < len; i++){
	
		if(temp[i] == '\n')
			buffer[i] = '\0';
		else
			buffer[i] = temp[i];
	}

	int flag = 0;
	x = 0;
	y = 0;

	while(strcmp(buffer, "q") != 0 && strcmp(buffer, "Q") != 0){

	for(i = 0; i < len; i++){
	
		char a = buffer[i];

		if(flag == 1)
			break;

		switch(a){

			case '(' :
				push(sp, a);
				break;
			case '{' :
				push(sp, a);
				break;
			case '[' :
				push(sp, a);
				break;
			case '<' :
				push(sp, a);
				break;
			case ')' :
				if(topElement(sp) == '(')
					pop(sp, '(');
				else if(isEmpty(sp) == true){
					x = 1;
					y = i;
					flag = 1;
					break;
				}
				else{
					x = 2;
					y = i;
					flag = 1;
					break;
				}	
				break;
			case '}' :
				if(topElement(sp) == '{')
					pop(sp, '{');
				else if(isEmpty(sp) == true){
					x = 3;
					y = i;
					flag = 1;
					break;
				}
				else{
					x = 4;
					y = i;
					flag = 1;
					break;
				}
				break;
			case ']' :
				if(topElement(sp) == '[')
					pop(sp, '[');
				else if(isEmpty(sp) == true){
					x = 5;
					y = i;
					flag = 1;
					break;
				}
				else{
					x = 6;
					y = i;
					flag = 1;
					break;
				}
				break;
			case '>' :
				if(topElement(sp) == '<')
					pop(sp, '<');
				else if(isEmpty(sp) == true){
					x = 7;
					y = i;
					flag = 1;
					break;
				}
				else{
					x = 8;
					y = i;
					flag = 1;
					break;
				}
				break;
		}		
	}	
		printf("\n");

		for(j = 0; j < len; j++)
			printf("%c ", buffer[j]);
		if(x == 1)
			missing('(', y);
		if(x == 2)
			expecting(topElement(sp), y);
		if(x == 3)
			missing('{', y);
		if(x == 4)
			expecting(topElement(sp), y);
		if(x == 5)
			missing('[', y);
		if(x == 6)
			expecting(topElement(sp), y);
		if(x == 7)
			missing('<', y);
		if(x == 8)
			expecting(topElement(sp), y);

		if(isEmpty(sp) == true && flag == 0)
			printf("\nThe expression is balanced\n\n");

		else if(isEmpty(sp) == false && flag == 0)
			endMissing(topElement(sp), i);
			
		stackReset(sp);

		flag = 0;
		x = 0;
		
		fgets(temp, 300, stdin);
		len = strlen(temp);

		for(i = 0; i < len; i++){
	
			if(temp[i] == '\n')
				buffer[i] = '\0';
			else
				buffer[i] = temp[i];
		}

	}
			
	return 0;
}
