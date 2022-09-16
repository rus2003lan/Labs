#include "table.h"

Table *create(FILE *info_file, char *name) {
	Table *table = (Table *) calloc(1, sizeof(Table));
	table->info_file = info_file;
	table->name = name;
	fseek(info_file, 0, SEEK_SET);
	fread(&(table->size), sizeof(int), 1, info_file);
	KS *ks = (KS *) calloc(table->size, sizeof(KS));
	table->ks = ks;
	return table;
}

void erasing(Table *table) {
	KS *ptr;
	for(int i = 0; i < table->now_size; i++) {
		ptr = table->ks + i;
		free(ptr->par);
		free(ptr->key);
	}
	free(table->ks);
	free(table->name);
	free(table);
}

char *find_ks(Table *table, char *key) {
	for (int i = 0; i < table->now_size; i++) {
		if (strcmp(key, (table->ks + i)->key) == 0) {
			int len;
			fseek(table->info_file, (table->ks + i)->info_offset, SEEK_SET); //учз на нужной точке
			fread(&len, sizeof(int), 1, table->info_file);
			char *info = (char *) malloc(sizeof(char) * len);
			fread(info, sizeof(char), len, table->info_file);
			return info;
		}
	}
	return NULL;
}

Table *find_by_par(Table *table, char *par) {  
	Table *new_table = (Table *) calloc(1, sizeof(Table));
	KS *new_ks = (KS *) calloc(table->size, sizeof(KS));
	new_table->ks = new_ks;
	new_table->size = table->size;
	new_table->info_file = table->info_file;
	int len_name = strlen(table->name) + 1;
	char *new_name = (char *) malloc(sizeof(char) * len_name);
	memcpy(new_name, table->name, sizeof(char) * len_name);
	new_table->name = new_name;
	int len_par = strlen(par) + 1;
	int len_key;
	for (int i = 0; i < table->now_size; i++) {
		if (strcmp(par, (table->ks + i)->par) == 0) {
			len_key = strlen((table->ks + i)->key) + 1;
			char *new_key = (char *) malloc(sizeof(char) * len_key);
			char *new_par = (char *) malloc(sizeof(char) * len_par);
			memcpy(new_key, (table->ks + i)->key, len_key * sizeof(char));
			memcpy(new_par, par, len_par * sizeof(char));
			(new_table->ks + new_table->now_size)->key = new_key;
			(new_table->ks + new_table->now_size)->par = new_par; 
			(new_table->ks + new_table->now_size)->info_offset = (table->ks + i)->info_offset;
			++new_table->now_size;
		}
	}
	if (new_table->now_size != 0) return new_table;
	else {
		free(new_ks);
		free(new_table);
		free(new_name);
		return NULL;
	}
}

int add(Table *table, char *info, char *key, char *par) {
	if (table->size == table->now_size) return 1;  // проверка на наличие места
	int place = -1;
	int flag = 0;
	if (table->now_size == 0 && strcmp(par, "") == 0) {
		flag = 1;
		place = 0;
	}
	for (int i = 0; i < table->now_size; i++) {
		if (strcmp(key, (table->ks + i)->key) == 0) return 2;
		if (place < 0 && strcmp(par, (table->ks + i)->par) < 0) place = i; //куда вставить
		if (place < 0 && (i == table->now_size - 1)) place = i + 1;               //вставка в конец
		if (strcmp(par, "") == 0 || flag == 0 && strcmp(par, (table->ks + i)->key) == 0) flag = 1;
	}
	if (flag == 0) return 3;
	for (int n = table->now_size; n > place; n--) {
		(table->ks + n)->key = (table->ks + n - 1)->key;
		(table->ks + n)->par = (table->ks + n - 1)->par;
		(table->ks + n)->info_offset = (table->ks + n - 1)->info_offset;
	}
	fseek(table->info_file, 0, SEEK_END);
	(table->ks +place)->info_offset = ftell(table->info_file);
	int len = strlen(info) + 1;
	fwrite(&len, sizeof(int), 1, table->info_file);
	fwrite(info, sizeof(char), len, table->info_file);
	(table->ks + place)->key = key;
	(table->ks + place)->par = par;
	++table->now_size;
	return 0;
}

int delete(Table *table, char *key) {
	int index = -1;
	for (int i = 0; i < table->now_size; i++) {
		if (strcmp(key, (table->ks + i)->par) == 0) return 2;
		if (index < 0 && strcmp(key, (table->ks + i)->key) == 0) index = i;
	}
	if (index < 0) return 1;
	free((table->ks + index)->key);
	free((table->ks + index)->par);
	for (index; index < table->now_size - 1; index++) {
		(table->ks + index)->key = (table->ks + index + 1)->key;
		(table->ks + index)->par = (table->ks + index + 1)->par;
		(table->ks + index)->info_offset = (table->ks + index + 1)->info_offset;
	}
	--table->now_size;
	return 0;
}

void show(Table *table) {
	int len;
	for(int i = 0; i < table->now_size; i++) {
		fseek(table->info_file, (table->ks + i)->info_offset, SEEK_SET); //учз на нужной точке
		fread(&len, sizeof(int), 1, table->info_file);
		char *info = (char *) malloc(sizeof(char) * len);
		fread(info, sizeof(char), len, table->info_file);
		char *key = (table->ks + i)->key;
		char *par = (table->ks + i)->par;
		printf("Info: %s  Key: %s Parent: %s\n", info, key, par);
		free(info);
	}
}

void upload_to_file(Table *table, FILE *ks_file) {
	fwrite(&(table->now_size), sizeof(int), 1, ks_file);
	int len_key;
	int len_par;
	for(int i = 0; i < table->now_size; i++) {
		len_key = strlen((table->ks + i)->key) + 1;
		fwrite(&len_key, sizeof(int), 1, ks_file);
		fwrite((table->ks + i)->key, sizeof(char), len_key, ks_file);
		len_par = strlen((table->ks + i)->par) + 1;
		fwrite(&len_par, sizeof(int), 1, ks_file);
		fwrite((table->ks + i)->par, sizeof(char), len_par, ks_file);
		fwrite(&(table->ks + i)->info_offset, sizeof(int), 1, ks_file);
	}
}

void loading_from_file(Table *table, FILE *ks_file) {
	int now_size;
	fseek(ks_file, 0, SEEK_SET);
	fread(&now_size, sizeof(int), 1, ks_file);
	table->now_size = now_size;
	int len_key;
	int len_par;
	for (int i = 0; i < now_size; i++) {
		fread(&len_key, sizeof(int), 1, ks_file);
		char *key = (char *) malloc(sizeof(char) * len_key);
		(table->ks + i)->key = key;
		fread((table->ks + i)->key, sizeof(char), len_key, ks_file);
		fread(&len_par, sizeof(int), 1, ks_file);
		char *par = (char *) malloc(sizeof(char) * len_par);
		(table->ks + i)->par = par;
		fread((table->ks + i)->par, sizeof(char), len_par, ks_file);
		fread(&((table->ks + i)->info_offset), sizeof(int), 1, ks_file);
	}
}