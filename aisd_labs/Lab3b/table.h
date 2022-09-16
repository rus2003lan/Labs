#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct KeySpace {
	char *key;
	int info_offset;
	char *par;
} KS;

typedef struct Table {
	FILE *info_file;
	char *name;
	KS *ks;
	int size;
	int now_size;
} Table;

Table *create(FILE *, char *);
Table *find_by_par(Table *, char *);
char *find_ks(Table *, char *);
int add(Table *, char *, char *, char *);
int delete(Table *, char *);
void show();
void menu();
void erasing(Table *);
int getint(int *);
int stdin_clear();
char *get_str();
void upload_to_file(Table *, FILE *);
void loading_from_file(Table *, FILE *);
char *get_ks_name(char *);
char *get_info_name(char *);