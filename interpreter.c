#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int display(char *instr_arr)
{
	printf("\e[1;1H\e[2J");
	int i=0;
	while(instr_arr[i] != '\0')
	{
		printf("%c",instr_arr[i]);
		i++;
	}
	printf("\n");
	return 0;
}

int fill(FILE *ptr, char *arr, int len)
{
	char ch;
	int i=0;
	while ((ch = fgetc(ptr)) != EOF && i<len) //the len parameter is necessary to prevent buffer overflows
	{
		if(strchr("><.,+-[]",ch) != NULL)
		{
			arr[i]=ch;
			i++;
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	FILE *fp;
	fp = fopen(argv[1],"r");
	if (fp == NULL)
	{
		printf("File is not available \n");
		return 0;
	}
	int size=107;
	char *instr = malloc(size);
	fill(fp, instr, size);
	display(instr);
	char tape[30000] = {0};
	char *ptr = &tape[0];
	char bracket[64]; //stack to put the left bracket positions in
	int bstack_top=0; //top of the stack above
	int i;
	for(i=0; i<size; i++)
	{
		//printf("i=%d instr=%c *ptr=%d ptr=%d \n",i,instr[i],*ptr, ptr);
		//sleep(1);
		//display(instr, i);
		switch(instr[i])
		{
			case '>':
				ptr++;
				break;
			case '<':
				ptr--;
				break;
			case '+':
				++*ptr;
				break;
			case '-':
				--*ptr;
				break;
			case '.':
				putchar(*ptr);
				break;
			case ',':
				*ptr=getchar();
				break;
			case '[':
				bracket[bstack_top]=i;
				bstack_top++;
				break;
			case ']':
				if(*ptr != 0)
				{
					i=bracket[bstack_top-1];
				}
				else
				{
					bstack_top--;
				}
				break;
		}
	}
	printf("\n");
	return 0;
}
