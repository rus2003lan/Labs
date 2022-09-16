#include "table.h"

void menu() {
	while (1) {
		printf("Input name of file:\n");
		char *name = get_str();
		char *ks_name = get_ks_name(name);
		char *info_name = get_info_name(name);
		FILE *ks_file = fopen(ks_name, "r+b");
		FILE *info_file = fopen(info_name, "r+b");
		Table *table;
		if (ks_file != NULL) {
			table = create(info_file, name);
			loading_from_file(table, ks_file);
			fclose(ks_file);
		}
		else { //файл пустой, создаем новый
			info_file = fopen(info_name, "w+b");
			int size;
			printf("Input size of Table:\n");
			int check_size = getint(&size);
			if (check_size == 1 || size < 0) {
				fclose(ks_file);
				free(ks_name);
				free(info_name);
				printf("Error, ");
				continue;
			}
			fwrite(&size, sizeof(int), 1, info_file);
			table = create(info_file, name);
		}
		int alternative;
		int check;
		int flag = 0;
		while (flag == 0) {
			printf("Choose an alternative:\n 1)Add 2)Find 3)Delete 4)Show 5)Exit\n");
			check = getint(&alternative);
			if (check == 0) {
				if (alternative == 1) {
					printf("Input key:\n");
					char *key = get_str();
					printf("Input parent:\n");
					char *par = get_str();
					printf("Input info:\n");
					char *info = get_str();
					int check_add = add(table, info, key, par);
					free(info);
					if (check_add == 0) {
						printf("Insert was successful!\n");
						continue;
					}
					else if (check_add == 1) {
						free(par);
					    free(key);
						printf("Table is full\n");
						continue;
					}
					else if (check_add == 2) {
						free(par);
						free(key);
						printf("Cannot insert, keys match\n");
						continue;
					}
					else if (check_add == 3) {
						free(par);
						free(key);
						printf("No such parent\n");
						continue;
					}
				}
				else if (alternative == 2) {
					while(1) {
						printf("Search by:\n 1)Key 2)Parent key 3)Quit\n");
						int find;
						char *information;
						int check_find = getint(&find);
						if (check_find == -1) {
							flag = 1;
							break;
						}
						else if (check_find == 1 || find > 3 || find < 0) {
							printf("Error, ");
							continue;
						}
						else if (find == 1) {
							printf("Input key:\n");
							char *key = get_str();
							information = find_ks(table, key);
							free(key);
							if (information == NULL) {
								printf("Element not found\n");
								continue;
							}
							else {
								printf("Info: %s\n", information);
								free(information);
								continue;
							}
						}
						else if (find == 2) {
							printf("Input parent:\n");
							char *par = get_str();
							Table *new_table = find_by_par(table, par);
							free(par);
							if (new_table == NULL) {
								printf("Element not found\n");
								continue;
							}
							else {
								show(new_table);
								erasing(new_table);
								continue;
							}
						}
						else if (find == 3) break;
					}
				}
				else if (alternative == 3) {
					while(1) {
						printf("Delete by:\n 1)Key 2)Quit\n");
						int alt_delete;
						int check_delete = getint(&alt_delete);
						if (check_delete == -1) {
							flag = 1;
							break;
						}
						else if (check_delete == 1 || alt_delete > 2 || alt_delete < 0) {
							printf("Error, ");
							continue;
						}
						else if (alt_delete == 1) {
							printf("Input key:\n");
							char *key = get_str();
							check_delete = delete(table, key);
							free(key);
							if (check_delete == 2) {
								printf("Element is a parent of another\n");
								continue;
							}
							else if (check_delete == 1) {
								printf("Element not found\n");
								continue;
							}
							else if (check_delete == 0) {
								printf("Item removed successfully!\n");
								break;
							}
						}
						else if (alt_delete == 2) break;
					}
				}
				else if (alternative == 4) show(table);
				else if (alternative == 5) break;
				else if (alternative > 5 || alternative < 1) {
					continue;
				}
			}
			else if (check == 1) printf("Please, repeat unput\n");
			else {
				flag = 1;
				break;
			}	
		}
	ks_file = fopen(ks_name, "wb");
	upload_to_file(table, ks_file);
	fclose(ks_file);
	fclose(info_file);
	erasing(table);
	free(ks_name);
	free(info_name);
	break;
	}
}

char *get_str() {
    char buf[81] = {0};  // BUFSIZ - константа для длины буфера
    char *res = NULL;
    unsigned int len = 0;
    unsigned int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            unsigned int chunk_len = strlen(buf);
            unsigned int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

int getint(int *number) {
	int check1 = scanf("%d", number);
	int check2 = stdin_clear();
	if (check1 == -1) return -1;
	else if (check1 == 0 || check2 == 1) return 1;
	else return 0;
}

int stdin_clear() {
	char tmp;
	int i = 0;
	while (scanf("%1[^\n]", &tmp) == 1) i++;
	if(i != 0) return 1;
	scanf("%*c");
	return 0;
}

char *get_ks_name(char *name) {
	int name_len = strlen(name);
	char *ks = "_ks";
	int len_ks = strlen(ks) + 1;
	char *ks_name = (char *) malloc(sizeof(char) * (name_len + len_ks));
	memcpy(ks_name, name, sizeof(char) * name_len);
	memcpy(ks_name + name_len, ks, sizeof(char) * len_ks);
	return ks_name;
}

char *get_info_name(char *name) {
	int name_len = strlen(name);
	char *info = "_info";
	int len_info = strlen(info) + 1;
	char *info_name = (char *) malloc(sizeof(char) * (name_len + len_info));
	memcpy(info_name, name, sizeof(char) * name_len);
	memcpy(info_name + name_len, info, sizeof(char) * len_info);
	return info_name;
}