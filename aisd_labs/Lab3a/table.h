#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
	char *info;
	char *key1;
	char *key2;
	int ind1;
	void *p2;
} Item;

typedef struct KeySpace1 {
	char *key;
	char *par;
	Item *info;
} KS1;

typedef struct KeySpace2 {
	char *key;
	Item *info;
	struct KeySpace2 *next;
} KS2;

typedef struct Table {
	KS1 *ks1;
	KS2 **ks2; //чтобы первый элемент списка не отличался от других(выделением памяти)
	int size1;
	int size2;
	int n1;
} Table;

Table *create(int, int);
void show(Table *);
int add(Table *, char *, char *, char *, char *);
int delete_compose(Table *, char *, char *);
void erasing(Table *);
char *find_ks2(Table *, char *);
int delete_ks2(Table *, char *);
int hash(int, char *);
char *find_ks1(Table *, char *);
int delete_ks1(Table *, char *);
Table *find_by_par(Table *, char *);
char *get_str();
void free_str(char *, char *, char *, char *);
void menu();
int getint(int *);
int stdin_clear();
char *find_compose(Table *, char *, char *);
void simple_erasing(Table *);
void show2(Table *);