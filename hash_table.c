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

//ïîèñê ýëåìåíòà â òàáëèöå
//Ðåçóëüòàò: -1 - íåò èñêîìîãî ýëåìåíòà
int search(key_t k, int capacity)
{
	int start = 0, i = 0, h = 1; //start - èñõîäíàÿ ïîçèöèÿ òàáëèöû, h - øàã ïåðåìåøèâàíèÿ
	start = i = hash_function(k, capacity);
	
	while (vector[i].busy >= 0) //ïîçèöèÿ çàíÿòà
	{
		if (vector[i].busy > 0 && vector[i].key == k)
			return i;
		i = (i + h) % capacity;
		//âåðíóëèñü â èñõîäíóþ ïîçèöèþ
		if (i == start)
			break;
	}
	return -1;
}

//Ðåçóëüòàò: 0 - åñëè ýëåìåíò âêëþ÷åí â òàáëèöó
//			-1 - åñëè â òàáëèöå åñòü ýëåìåíò ñ çàäàííûì êëþ÷îì  
//			-2 - åñëè â òàáëèöå íåò ñâîáîäíîãî ìåñòà
int insert(key_t k, int capacity, Type useful_line)//åñëè ïåðåäàí null - ñ ôàéëîì íå ðàáîòàåì
{
	int start = 0, i = 0, h = 1; //start - èñõîäíàÿ ïîçèöèÿ òàáëèöû, h - øàã ïåðåìåøèâàíèÿ
	start = i = hash_function(k, capacity);

		while (vector[i].busy > 0) //ïîçèöèÿ çàíÿòà
		{
			if (vector[i].key == k)
				return -1;
			i = (i + h) % capacity;

			//âåðíóëèñü â èñõîäíóþ ïîçèöèþ
			if (i == start)
				return -2;
		}	
	//åñëè îê, òî çàíåñåíèå íîâîãî ýëåìåíòà
	vector[i].key = k;
	vector[i].busy = 1;
        vector[i].info = useful_line; // Now this pointer belongs to a table structure
	return 0;
}

// ïîìåòèòü çàïèñü êàê óäàëåííóþ, ò.ê. íåëüçÿ ïåðåìåøèâàòü ïîñëå ôèç. óäàëåíèÿ çàïèñåé.
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
