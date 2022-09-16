#include "table.h"

void menu() {
	while (1) {
		int size1;
		printf("Input size of Keyspace 1:\n");
		int check_size = getint(&size1);
		if (check_size == -1) break;
		else if (check_size == 1 || size1 < 0) {
			printf("Error, ");
			continue;
		}
		int size2;
		printf("Input size of Keyspace 2:\n");
		check_size = getint(&size2);
		if (check_size == -1) break;
		else if (check_size == 1 || size2 < 0) {
			printf("Error, ");
			continue;
		}
		Table *table = create(size1, size2);
		int alternative;
		int check;
		int flag = 0;
		while (flag == 0) {
			printf("Choose an alternative:\n 1)Add 2)Find 3)Delete 4)Show 5)Exit\n");
			check = getint(&alternative);
			if (check == 0) {
				if (alternative == 1) {
					printf("Input key1:\n");
					char *key1 = get_str();
					printf("Input key2:\n");
					char *key2 = get_str();
					printf("Input parent:\n");
					char *par = get_str();
					printf("Input info:\n");
					char *info = get_str();
					int check_add = add(table, info, key1, key2, par);
					if (check_add == 0) {
						printf("Insert was successful!\n");
						continue;
					}
					else if (check_add == 1) {
						printf("Table is full\n");
						continue;
					}
					else if (check_add == 2) {
						printf("Cannot insert, keys match\n");
						continue;
					}
					else if (check_add == 3) {
						printf("No such parent\n");
						continue;
					}
				}
				else if (alternative == 2) {
					while(1) {
						printf("Search by:\n 1)Keyspace1 2)Keyspace2 3)Parent key 4)Composite key 5)Quit\n");
						int find;
						char *information;
						int check_find = getint(&find);
						if (check_find == -1) {
							flag = 1;
							break;
						}
						else if (check_find == 1 || find > 5 || find < 0) {
							printf("Error, ");
							continue;
						}
						else if (find == 1) {
							printf("Input key:\n");
							information = find_ks1(table, get_str());
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
							printf("Input key:\n");
							information = find_ks2(table, get_str());
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
						else if (find == 3) {
							printf("Input parent:\n");
							Table *new_table = find_by_par(table, get_str());
							if (new_table == NULL) {
								printf("Element not found\n");
								continue;
							}
							else {
								show(new_table);
								simple_erasing(new_table);
								continue;
							}
						}
						else if (find == 4) {
							printf("Input key1:\n");
							char *key1 = get_str();
							printf("Input key2:\n");
							char *key2 = get_str();
							information = find_compose(table, key1, key2);
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
						else if (find == 5) break;
					}
				}
				else if (alternative == 3) {
					while(1) {
						printf("Delete by:\n 1)Key1 2)Key2 3)Composite key 4)Quit\n");
						int delete;
						int check_delete = getint(&delete);
						if (check_delete == -1) {
							flag = 1;
							break;
						}
						else if (check_delete == 1 || delete > 4 || delete < 0) {
							printf("Error, ");
							continue;
						}
						else if (delete == 1 || delete == 2) {
							printf("Input key%d:\n", delete);
							if(delete == 1) check_delete = delete_ks1(table, get_str());
							else check_delete = delete_ks2(table, get_str());
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
						else if (delete == 3) {
							printf("Input key1:\n");
							char *key1 = get_str();
							printf("Input key2:\n");
							char *key2 = get_str();
							check_delete = delete_compose(table, key1, key2);
							if (check_delete == 2) {
								printf("Element is a parent of another\n");
								continue;
							}
							else if (check_delete == 1) {
								printf("Element not found\n");
								continue;
							}
							else {
								printf("Item removed successfully!\n");
								break;
							}
						}
						else if (delete == 4) break;
					}
				}
				else if (alternative == 4) show2(table);
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
	erasing(table);
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