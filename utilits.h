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

void get_line(int);
int get_size();
int select_action(int choice);
int get_key(key_t k);
void init_table(int capacity);
void show_element(key_t key);
void not_found();
void duplicated_key();
void full_table();
