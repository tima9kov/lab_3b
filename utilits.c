#include "utilits.h"
#include "hash_table.h"
#include <stdio.h>

void print_menu()
{
	printf("\n0 - exit, 1 - add element, 2 - delete element,3 - search, 4 - print table\n");
}	

int select_action(int choice)
{
	int condition = 0;
	printf("Your choice . . . ");
	while (1 != scanf("%d", &choice) || choice > 4 || choice < 0) {
		rewind(stdin);
		printf("\x1b[31mIncorrect input, try again\x1b[0m");
	}
	return choice;
}

int get_key(key_t k) {
	printf("Input key ");
	while (1 != scanf("%d", &k)) {
		rewind(stdin);
		printf("\x1b[31mIncorrect input, try again\x1b[0m");
	}
	return k;
}

Type get_line()
{
	int len = 1;
	Type str = (Type)malloc(len);
	char c;	
	printf("input string: ");
	rewind(stdin);
	while ((c = getchar()) != '\n') {
		str[len - 1] = c;
		len++;
		str = (char*)realloc(str, len);
	}
	str[len - 1] = '\0';
	printf("%s (%d symbols)\n", str, len - 1);
	return str;
}

Type get_line_f(FILE* f) //f - óêàçàòåëü íà ñòðóêòóðó ôàéë
{
	int len = 1;
	Type str = (Type)malloc(len);
	char c;
		
	//printf("input string: ");
	//rewind(stdin);
	//êàê îáíîâèòü áóôåð ôàéëà
	fread(&c, 1, 1, f);//÷òåíèå èç ôàéëà f 1øò ðàçì 1 â ñ
	while (c != '\0') {
		str[len - 1] = c;
		len++;
		str = (char*)realloc(str, len);
		fread(&c, 1, 1, f);
	}
	str[len - 1] = '\0';
	//printf("%s (%d symbols)\n", str, len - 1);
	return str;
}

int get_size() {
	int size = 0;
	printf("Input table size ... ");
	while (1 != scanf("%d", &size)) {
		rewind(stdin);
		printf("\x1b[31mIncorrect input, try again ... \x1b[0m");
	}
	return size;
}

int get_size_f(FILE* f) {
	int result = 0;
	int bytes = fread(&result, sizeof(int), 1, f); //÷èòàåì èç ôàéëà ðàçìåð òàáëèöû â áèíàðíîì âèäå â ïåðåìåííóþ result
	//ìîæíî áûëî áû ïðîâåðèòü. ÷òî êîë-âî áàéò = 4
	return result;
}

void not_found()
{
	printf("\n\x1b[31m not found \x1b[0m\n");
}

void show_element(key_t key)
{
	printf("\n\x1b[32mElement was found     Index: %3d	 Info: %10s    \x1b[0m\n", vector[key].key, vector[key].info);
}

void duplicated_key()
{
	printf("\n\x1b[31m The key already exists \x1b[0m\n");
}

void full_table()
{
	printf("\n\x1b[31m The table is full \x1b[0m\n");
}
