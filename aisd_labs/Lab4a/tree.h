#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tree {
	unsigned int key;
	char *info;
	struct Tree *par;
	struct Tree *left;
	struct Tree *right;
} Tree;

void menu();
void erase(Tree *);
void show(Tree *, int);
int add(Tree **, char *, unsigned int);
int delete(Tree **, unsigned int);
int round_tree(Tree *, unsigned int);
Tree *find_tree(Tree *, unsigned int);
Tree *special_find(Tree *, unsigned int);
void loading_from_file(Tree **, FILE *);
char *get_str();
int get_unint(unsigned int *);
int getint(int *);
int stdin_clear();
char *get_str_from_file(FILE *);
int getunint_from_file(FILE *, unsigned int *);
int timing();