#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tree {
	int color;
	unsigned int key;
	unsigned int info;
	struct Tree *par;
	struct Tree *left;
	struct Tree *right;
} Tree;

void menu();
void erase(Tree *tree);
void show(Tree *tree, int space);
unsigned int add(Tree **tree, unsigned int info, unsigned int key, int *flag);
int delete(Tree **tree, unsigned int key);
int round_tree(Tree *tree, unsigned int min_key, unsigned int max_key);
Tree *find_tree(Tree *tree, unsigned int key);
void loading_from_file(Tree **tree, FILE *file);
Tree *special_find(Tree *tree, unsigned int min_key);
int get_unint(unsigned int *number);
int getint(int *number);
int stdin_clear();
int getunint_from_file(FILE *file, unsigned int *number);
int timing();
Tree *left_rotate(Tree *tree);
Tree *right_rotate(Tree *tree);
Tree *create_tree(unsigned int key, unsigned int info);
Tree *create_elist();
Tree *balance(Tree *tree);
Tree *delete_balance(Tree *tree);