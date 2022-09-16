#include "tree.h"

void menu() {
	while (1) {
		int alternative;
		int check;
		int flag = 0;
		Tree *tree = NULL;
		while (flag == 0) {
			printf("Choose an alternative:\n 1)Download tree 2)Add 3)Find 4)Show 5)Delete 6)Round 7)Exit 8)Timing\n");
			check = getint(&alternative);
			if (check == 0) {
				if (alternative == 1) {
					FILE *file = fopen("file.txt","r");
					if (file != NULL) {
						loading_from_file(&tree, file);
						printf("Upload was successful!\n");
						fclose(file);
						continue;
					}
					else {
						printf("No such file\n");
						continue;
					}
				}
				else if (alternative == 2) {
					printf("Input key:\n");
					unsigned int key;
					while (get_unint(&key) != 0) printf("Please, repeat unput key:\n");
					printf("Input info:\n");
					unsigned int info;
					while (get_unint(&info) != 0) printf("Please, repeat unput key:\n");
					int add_flag = 0;
					unsigned int old_info = add(&tree, info, key, &add_flag);
					if (add_flag == 0) {
						printf("Insert was successful!\n");
						continue;
					}
					else {
						printf("Old info: %u\n", old_info);
						continue;
					}
				}
				else if (alternative == 3) {
					while(1) {
						printf("Search:\n 1)Normal 2)Special 3)Quit\n");
						int find;
						Tree *information;
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
							unsigned int key;
							while (get_unint(&key) != 0) printf("Please, repeat unput key:\n");
							information = find_tree(tree, key);
							if (information == NULL) {
								printf("Element not found\n");
								continue;
							}
							else {
								printf("Info: %u\n", information->info);
								continue;
							}
						}
						else if (find == 2) {
							printf("Input min key:\n");
							unsigned int min_key;
							while (get_unint(&min_key) != 0) printf("Please, repeat unput min key:\n");
							information = special_find(tree, min_key);
							if (information == NULL) {
								printf("Element not found\n");
								continue;
							}
							else {
								printf("Info: %u\nKey: %u\n", information->info, information->key);
								continue;
							}
						}
						else if (find == 3) break;
					}
				}
				else if (alternative == 4) {
					printf("Tree:\n");
					show(tree, 0);
					printf("\n\n");
				}
				else if (alternative == 5) {
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
							unsigned int key;
							while (get_unint(&key) != 0) printf("Please, repeat unput key:\n");
							check_delete = delete(&tree, key);
							if (check_delete == 1) {
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
				else if (alternative == 6) {
					unsigned int min_key;
					unsigned int max_key;
					int round_check;
					printf("Input min key:\n");
					while (get_unint(&min_key) != 0) printf("Please, repeat unput min key:\n");
					printf("Input max key:\n");
					while (get_unint(&max_key) != 0) printf("Please, repeat unput max key:\n");
					round_check = round_tree(tree, min_key, max_key);
					if (round_check == 1) printf("Error, min_key > max_key");
					printf("\n");
					continue;
				}
				else if (alternative == 7) break;
				else if (alternative == 8) {
					timing();
					break;
				}
				else if (alternative > 8 || alternative < 1) {
					continue;
				}
			}
			else if (check == 1) printf("Please, repeat unput\n");
			else {
				flag = 1;
				break;
			}	
		}
	if (tree != NULL) {
		Tree *elist = tree->par;
		erase(tree);
		free(elist);
	}
	break;
	}
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

int get_unint(unsigned int *number) {
	int check1 = scanf("%u", number);
	int check2 = stdin_clear();
	if (check1 == -1) return -1;
	else if (check1 == 0 || check2 == 1) return 1;
	if (number < 0) return 2;
	else return 0;
}

int getunint_from_file(FILE *file, unsigned int *number) {
	int check = fscanf(file, "%u", number);
	if (check < 0) return 1;
	char tmp;
	fscanf(file, "%c", &tmp);
	return 0;
}