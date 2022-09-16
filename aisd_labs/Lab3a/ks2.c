#include "table.h"

int hash(int size2, char *key) {
	char tmp = 0;
	while(*key) {
		tmp = tmp ^ *(key);
		++key;
	}
	return tmp % size2;
}

char *find_ks2(Table *table, char *key) {
	int index = hash(table->size2, key);
	KS2 *ptr = *(table->ks2 + index);
	while (ptr != NULL) {
		if (strcmp(key, ptr->key) == 0) {
			int len = strlen(ptr->info->info) + 1;
			char *copy = (char *) malloc(sizeof(char) * len);
			memcpy(copy, ptr->info->info, len * sizeof(char));
			free(key);
			return copy;
		}
		ptr = ptr->next;
	}
	free(key);
	return NULL;
}

int delete_ks2(Table *table, char *key) {
	int index2 = hash(table->size2, key);
	int index1;
	KS2 *ptr = *(table->ks2 + index2);
	if (ptr != NULL) {
		if (strcmp(key, ptr->key) == 0) {
			index1 = ptr->info->ind1;
			for (int i = 0; i < table->n1; i++) {
				if (strcmp(ptr->info->key1, (table->ks1 + i)->par) == 0) {
					free(key);
					return 2;
				}
			}
			*(table->ks2 + index2) = ptr->next;
			free(ptr->info->info);
			free(ptr->info->key1);
			free(ptr->info->key2);
			free(ptr->info);
			free((table->ks1 + index1)->par);
			free(ptr);
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
	}
	else {
		free(key);
		return 1;
	}
	while (ptr->next != NULL) {
		if (strcmp(key, ptr->next->key) == 0) {
			KS2 *tmp = ptr->next;
			ptr->next = ptr->next->next;
			index1 = tmp->info->ind1;
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
		ptr = ptr->next;
	}
	free(key);
	return 1;
}

void show2(Table *table) {
	for(int i = 0; i < table->size2; i++) {
		KS2 *ptr = *(table->ks2 + i);
		if(ptr != NULL) printf("Hash: %d\n", i);
		int number = 0;
		while (ptr != NULL) {
			char *key1 = ptr->info->key1;
			char *key2 = ptr->key;
			char *par = (table->ks1 + (ptr->info->ind1))->par;
			char *info = ptr->info->info;
			printf("\tNumber: %d  Info: %s  Key1: %s  Key2: %s  Parent: %s\n", number, info, key1, key2, par);
			ptr = ptr->next;
			++number;
		}
	}
}