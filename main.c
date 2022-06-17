//Девятков Т.И Б20-В02
//
//Вариант 5 
//Написать программу для работы с перемешанной таблицей, использующей перемешивание сложением, по запросам оператора.
//Перемешанная таблица организована вектором; каждый элемент таблицы имеет следующую структуру :
//struct Item {
//	int busy;		/* признак занятости элемента*/
//	int key;		/* ключ элемента				*/
//	char* info;	/* указатель на информацию	
//};
//
//Максимальный размер таблицы ограничен(для задания максимального размера таблицы использовать константу – например, const int SIZE = ...;).
//Для доступа к элементам таблицы использовать двойное хеширование.
//Предусмотреть следующие операции :
//-	включение нового элемента в таблицу при условии, что в таблице не может быть двух элементов с одинаковыми ключами; если при включении нового
//элемента возникает такая ситуация, на экран должно быть выведено сообщение об ошибке;
//-	удаление из таблицы элемента, заданного своим ключом;
//-	поиск элемента по заданному ключу.Результатом поиска должен быть новый элемент таблицы, содержащий найденный элемент.Если заданный элемент в
//таблице отсутствует, вывести на экран сообщение об ошибке;
//-	вывод содержимого таблицы на экран.
//Разработать два варианта программы :
//a)	и сама таблица, и информация, относящаяся к элементу таблицы, хранятся в основной памяти;
//b)	и сама таблица, и информация, относящаяся к элементу таблицы, хранятся во внешней памяти(используется двоичный файл произвольного доступа).
//Все операции выполняются с таблицей, размещенной в основной памяти.Таблица считывается из файла(или создается в первый раз) в начале сеанса работы 
//и записывается в файл в конце сеанса работы.Информация, относящаяся к элементу таблицы, записывается в файл сразу же при выполнении операции включения
//в таблицу.Имя файла вводится по запросу из программы.

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "hash_table.h"
#include "utilits.h"

FILE* prepare_arg_file(char** file_name) {
	int len = 1;
	*file_name = (char*)malloc(len);
	char c;

	//rewind(stdin);
	//как обновить буфер файла
	printf("Input file name or emty line for entering from keyboard . . . ");
	while ((c = getchar()) != '\n') {
		(*file_name)[len - 1] = c;
		len++;
		*file_name = (char*)realloc(*file_name, len);
	}
	(*file_name)[len - 1] = '\0';
	return fopen(*file_name, "rb");
}

void save_and_close_file(FILE* f, char* file_name) {
	char c = '\0';
	int empty = 0;
	//имя файла можно достать из структуры файл
	if (f != NULL) {
		fclose(f);
	}
	f = fopen(file_name, "wb"); //если захочется обнаркоматься написать бэкап файла
	fwrite(&capacity, sizeof(int), 1, f);
	for (int i = 0; i < capacity; i++) {
		if (vector[i].info != NULL) {
			fwrite(&vector[i].key, sizeof(int), 1, f);
			fwrite(&vector[i].busy, sizeof(int), 1, f);
			fwrite(vector[i].info, sizeof(char), vector[i].size, f);
		}
		else {
			fwrite(&empty, sizeof(int), 1, f);
			fwrite(&empty, sizeof(int), 1, f);
			fwrite(&c, 1, 1, f);
		}
	}
	fclose(f);
}

int main()
{	
	capacity = 5;//структуру создавать - для слабаков
	int choice = 0, availability = 0;
	key_t key = 0;
	//инициализация файла
	char* file_name = NULL;
	FILE* f = prepare_arg_file(&file_name);
	
	if (file_name[0] == 0) {
		printf("File name is empty, reading from keyboard.");
	}
	else {
		if (f == NULL) {
			printf("File not found. Reading from keyboard.");
		}
	}

	if (f != NULL) {
		capacity = get_size_f(f);
	}
	else {
		capacity = get_size();
	}
	if (capacity == 0) {
		printf("No NULL table");
		return -1;
	}
	
	init_table(capacity);
	if (f != NULL) {
		for(int i = 0; i < capacity; i++)
		insert(i, capacity, f);
	}

	do {
		print_menu();
		choice = select_action(choice);
		//system("pause");
		if (choice == EXIT)
			break;
		if (choice == ADD_ELEMENT)
		{
			key = get_key(key);

			availability = insert(key, capacity, f);
				if (availability == -1)
					duplicated_key();
				if (availability == -2)
					full_table();
		}
		if (choice == DELETE_ELEMENT)
		{
			key = get_key(key);

			availability =  delete_element(key, capacity);
			if (availability == -1) {
				not_found();
			}
			else
				printf("deleted");
		}
		if (choice == FIND_ELEMENT)
		{
			key = get_key(key);
			availability = search(key, capacity);
			if (availability == -1) {
				not_found();
			}
			else
				show_element(availability);
		}
		if (choice == SHOW_TABLE)
		{
			print_table(capacity);
		}
	} while (choice != 0);
	
	save_and_close_file(f, file_name);
	free(vector->info);
	free(vector);

	system("pause");
	return 0;
}