#include "hash_table.h"
#include <stdio.h>
#include "utilits.h"
#include <string.h>

key_t hash_function(key_t key, int capacity)
{
	return key % capacity;
}

void init_table(int capacity)
{
	vector = (Item*)malloc(capacity * sizeof(Item));
	for (int i = 0; i < capacity; i++)
	{
		vector[i].busy = 0;
		vector[i].key = 0;
		vector[i].info = NULL;
		vector[i].size = 0;
	}
}

//поиск элемента в таблице
//Результат: -1 - нет искомого элемента
int search(key_t k, int capacity)
{
	int start = 0, i = 0, h = 1; //start - исходная позиция таблицы, h - шаг перемешивания
	start = i = hash_function(k, capacity);
	
	while (vector[i].busy >= 0) //позиция занята
	{
		if (vector[i].busy > 0 && vector[i].key == k)
			return i;
		i = (i + h) % capacity;
		//вернулись в исходную позицию
		if (i == start)
			break;
	}
	return -1;
}

//Результат: 0 - если элемент включен в таблицу
//			-1 - если в таблице есть элемент с заданным ключом  
//			-2 - если в таблице нет свободного места
int insert(key_t k, int capacity, FILE *f )//если передан null - с файлом не работаем
{
	int start = 0, i = 0, h = 1; //start - исходная позиция таблицы, h - шаг перемешивания
	start = i = hash_function(k, capacity);

		while (vector[i].busy > 0) //позиция занята
		{
			if (vector[i].key == k)
				return -1;
			i = (i + h) % capacity;

			//вернулись в исходную позицию
			if (i == start)
				return -2;
		}	
	//если ок, то занесение нового элемента
	vector[i].key = k;
	vector[i].busy = 1;

	if (f != NULL) {
		get_line_f(i, f);
	}
	else {
		get_line(i);
	}
	return 0;
}

// пометить запись как удаленную, т.к. нельзя перемешивать после физ. удаления записей.
int delete_element(key_t k, int capacity) {   
	int i;
	i = search(k, capacity);
	if (i > 0) {
		vector[i].info = NULL;
		vector[i].busy = -1;
		free(vector[i].info);
		i = 0;
	}
	return i;
}

void print_table(int capacity)
{
	int i;
	system("cls");
	printf("KEY	 busy	      INFO\n");
	for (i = 0; i < capacity; i++)
	{
		printf("\n%3d	%3d	  %10s ", vector[i].key, vector[i].busy, vector[i].info);
	}
}
