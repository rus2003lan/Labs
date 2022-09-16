#include "table.h"

char *find_ks1(Table *table, char *key) {
	for (int i = 0; i < table->n1; i++) {
		if (strcmp(key, (table->ks1 + i)->key) == 0) {
			int len = strlen((table->ks1 + i)->info->info) + 1;
			char *copy = (char *) malloc(sizeof(char) * len);
			memcpy(copy, (table->ks1 + i)->info->info, len * sizeof(char));
			free(key);
			return copy;
		}
	}
	free(key);
	return NULL;
}

Table *find_by_par(Table *table, char *par) {  
	Table *new_table = (Table *) calloc(1, sizeof(Table));
	KS1 *new_ks1 = (KS1 *) calloc(table->size1, sizeof(KS1));
	new_table->ks1 = new_ks1;
	new_table->size1 = table->size1;
	int len_par = strlen(par) + 1;
	int len_key1, len_key2, len_info;
	char *new_key1, *new_key2, *new_par, *new_info;
	for (int i = 0; i < table->n1; i++) {
		if (strcmp(par, (table->ks1 + i)->par) == 0) {
			Item *new_item = (Item *) calloc(1, sizeof(Item));
			len_key1 = strlen((table->ks1 + i)->key) + 1;
			len_key2 = strlen((table->ks1 + i)->info->key2) + 1;
			len_info = strlen((table->ks1 + i)->info->info) + 1;
			char *new_key1 = (char *) malloc(sizeof(char) * len_key1);
			char *new_key2 = (char *) malloc(sizeof(char) * len_key2);
			char *new_par = (char *) malloc(sizeof(char) * len_par);
			char *new_info = (char *) malloc(sizeof(char) * len_info);
			(new_table->ks1 + new_table->n1)->info = new_item;
			memcpy(new_key1, (table->ks1 + i)->key, len_key1 * sizeof(char));
			memcpy(new_key2, (table->ks1 + i)->info->key2, len_key2 * sizeof(char));
			memcpy(new_par, par, len_par * sizeof(char));
			memcpy(new_info, (table->ks1 + i)->info->info, len_info * sizeof(char));
			(new_table->ks1 + new_table->n1)->key = new_key1;
			(new_table->ks1 + new_table->n1)->info->key2 = new_key2;
			(new_table->ks1 + new_table->n1)->par = new_par; 
			(new_table->ks1 + new_table->n1)->info->info = new_info;
			new_table->n1++;
		}
	}
	free(par);
	if (new_table->n1 != 0) return new_table;
	else {
		free(new_ks1);
		free(new_table);
		return NULL;
	}
}

int delete_ks1(Table *table, char *key) {
	int index1 = -1;
	for (int i = 0; i < table->n1; i++) {
		if (strcmp(key, (table->ks1 + i)->par) == 0) {
			free(key);
			return 2;
		}
		if (index1 < 0 && strcmp(key, (table->ks1 + i)->key) == 0) {
			index1 = i;
		}
	}
	if (index1 < 0) {
		free(key);
		return 1;
	}
	int index2 = hash(table->size2, (table->ks1 + index1)->info->key2);
	KS2 *ptr = *(table->ks2 + index2);
	KS2 *tmp;
	if (ptr == (table->ks1 + index1)->info->p2) {
		tmp = ptr;
		*(table->ks2 + index2) = NULL;
	}
	else {
		while ((void *) ptr->next != (table->ks1 + index1)->info->p2) {
			ptr = ptr->next;
		}
		tmp = ptr->next;
		ptr->next = ptr->next->next;
	}
	free(tmp->info->info);
	free(tmp->info->key1);
	free(tmp->info->key2);
	free(tmp->info);
	free(tmp);
	free((table->ks1 + index1)->par);
	for (index1; index1 < table->n1 - 1; index1++) {
		(table->ks1 + index1)->key = (table->ks1 + index1 + 1)->key;
		(table->ks1 + index1)->par = (table->ks1 + index1 + 1)->par;
		(table->ks1 + index1)->info = (table->ks1 + index1 + 1)->info;
		(table->ks1 + index1)->info->ind1 = index1;
	}
	--table->n1;
	free(key);
	return 0;
}

void simple_erasing(Table *table) {
	for (int i = 0; i < table->n1; i++) {
		free((table->ks1 + i)->key);
		free((table->ks1 + i)->par);
		free((table->ks1 + i)->info->key2);
		free((table->ks1 + i)->info->info);
		free((table->ks1 + i)->info);
	}
	free(table->ks1);
	free(table);
}