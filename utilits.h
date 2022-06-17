#pragma once
typedef unsigned int key_t;
#include "hash_table.h"

enum choice
{
	EXIT,
	ADD_ELEMENT,
	DELETE_ELEMENT,
	FIND_ELEMENT,
	SHOW_TABLE
};

Type get_line();
Type get_line_f(FILE* f);
int get_size();
int get_size_f(FILE* f);
int select_action(int choice);
int get_key(key_t k);
void init_table(int capacity);
void show_element(key_t key);
void not_found();
void duplicated_key();
void full_table();
