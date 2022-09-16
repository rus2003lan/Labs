#include "table.h"

char *find_compose(Table *table, char *key1, char *key2) {
	int index2 = hash(table->size2, key2);
	KS2 *ptr = *(table->ks2 + index2);
	while (ptr != NULL) {
		if (strcmp(key2, ptr->key) == 0) break;
		ptr = ptr->next;
	}
	if(ptr == NULL) {
		free(key1);
		free(key2);
		return NULL;
	}
	int index1 = -1;
	for (int i = 0; i < table->n1; i++) {
		if (strcmp(key1, (table->ks1 + i)->key) == 0) {
			index1 = i;
			break;
		}
	}
	if (index1 < 0) {
		free(key1);
		free(key2);
		return NULL;
	}
	if (ptr->info == (table->ks1 + index1)->info) {
		int len = strlen(ptr->info->info) + 1;
		char *copy = (char *) malloc(sizeof(char) * len);
		memcpy(copy, ptr->info->info, len * sizeof(char));
		free(key1);
		free(key2);
		return copy;
	}
	free(key1);
	free(key2);
	return NULL;
}

Table *create(int size1, int size2) {
	Table *table = (Table *) calloc(1, sizeof(Table));
	table->size1 = size1;
	table->size2 = size2;
	KS1 *ks1 = (KS1 *) calloc(size1, sizeof(KS1));
	KS2 **ks2 = (KS2 **) calloc(size2, sizeof(KS2 *));
	table->ks1 = ks1;
	table->ks2 = ks2;
	return table;
}

void free_str(char *info, char *key1, char *key2, char *par) {
	free(info);
	free(key1);
	free(key2);
	free(par);
}

int add(Table *table, char *info, char *key1, char *key2, char *par) {
	if (table->size1 == table->n1) {     // проверка на наличие места
		free_str(info, key1, key2, par);
		return 1;
	}
	int place = -1;
	int flag = 0;
	if (table->n1 == 0 && strcmp(par, "") == 0) {
		flag = 1;
		place = 0;
	}
	for (int i = 0; i < table->n1; i++) {  //вставка не первого элемента
		if (strcmp(key1, (table->ks1 + i)->key) == 0) {
			free_str(info, key1, key2, par);
			return 2;
		}
		if (place < 0 && strcmp(par, (table->ks1 + i)->par) < 0) place = i; //куда вставить
		if (place < 0 && (i == table->n1 - 1)) place = i + 1;               //вставка в конец
		if (strcmp(par, "") == 0 || flag == 0 && strcmp(par, (table->ks1 + i)->key) == 0) flag = 1;
	}
	if (flag == 0) {
		free_str(info, key1, key2, par);
		return 3;
	}
	int index = hash(table->size2, key2);
	if (*(table->ks2 + index) == NULL) { // вставка если первый элемент списка NULL
		KS2 *new_ks2 = (KS2 *) calloc(1, sizeof(KS2));
		*(table->ks2 + index) = new_ks2;
		Item *item = (Item *) calloc(1, sizeof(Item));
		item->info = info;
		item->key1 = key1;
		item->key2 = key2;
		item->ind1 = place;
		item->p2 = *(table->ks2 + index);
		(*(table->ks2 + index))->key = key2;
		(*(table->ks2 + index))->info = item;
		(*(table->ks2 + index))->next = NULL; 
		for (int n1 = table->n1; n1 > place; n1--) {
			(table->ks1 + n1)->key = (table->ks1 + n1 - 1)->key;
			(table->ks1 + n1)->par = (table->ks1 + n1 - 1)->par;
			(table->ks1 + n1)->info = (table->ks1 + n1 - 1)->info;
			(table->ks1 + n1)->info->ind1 = n1;
		}
		(table->ks1 + place)->key = key1;
		(table->ks1 + place)->par = par;
		(table->ks1 + place)->info = item;
		++(table->n1);
		return 0;
	}
	KS2 *ptr = *(table->ks2 + index);
	if (strcmp(key2, ptr->key) == 0) { //проверка первого ключа
		free_str(info, key1, key2, par);
		return 2;
	}
	while (ptr->next != NULL) {    //проверка остальных ключей
		if (strcmp(key2, ptr->next->key) == 0) {
			free_str(info, key1, key2, par);
			return 2;
		}
		ptr = ptr->next;
	}
	for (int n1 = table->n1; n1 > place; n1--) {
		(table->ks1 + n1)->key = (table->ks1 + n1 - 1)->key;
		(table->ks1 + n1)->par = (table->ks1 + n1 - 1)->par;
		(table->ks1 + n1)->info = (table->ks1 + n1 - 1)->info;
		(table->ks1 + n1)->info->ind1 = n1;
	}
	Item *item = (Item *) calloc(1, sizeof(Item));
	item->info = info;
	item->key1 = key1;
	item->key2 = key2;
	item->ind1 = place;
	(table->ks1 + place)->key = key1;
	(table->ks1 + place)->par = par;
	(table->ks1 + place)->info = item;
	table->n1++;
	KS2 *new_ks2 = (KS2 *) calloc(1, sizeof(KS2));
	ptr->next = new_ks2;
	ptr->next->key = key2;
	ptr->next->info = item;
	ptr->next->info->p2 = (void *) ptr->next;
	ptr->next->next = NULL;
	return 0;
}

int delete_compose(Table *table, char *key1, char *key2) {
	int len = strlen(key1) + 1;
	char *copy = (char *) malloc(sizeof(char) * len);
	memcpy(copy, key1, len * sizeof(char));
	char *check = find_compose(table, key1, key2);
	if (check == NULL) {
		free(copy);
		return 1;
	}
	free(check);
	int check_del = delete_ks1(table, copy);
	return check_del;
}


void erasing(Table *table) {
	for(int i = 0; i < table->size2; i++) {
		KS2 *ptr = *(table->ks2 + i);
		KS2 *tmp = NULL;
		if(ptr == NULL) continue;
		while(ptr != NULL) {
			tmp = ptr;
			ptr = ptr->next;
			free(tmp->info->info);
			free(tmp->info->key1);
			free(tmp->info->key2);
			free((table->ks1 + (tmp->info->ind1))->par);
			free(tmp->info);
			free(tmp);
		}
	}
	free(table->ks2);
	free(table->ks1);
	free(table);
}

void show(Table *table) {
	for(int i = 0; i < table->n1; i++) {
		char *info = (table->ks1 + i)->info->info;
		char *key1 = (table->ks1 + i)->key;
		char *key2 = (table->ks1 + i)->info->key2;
		char *par = (table->ks1 + i)->par;
		printf("Info: %s  Key1: %s  Key2: %s  Parent: %s\n", info, key1, key2, par);
	}
}