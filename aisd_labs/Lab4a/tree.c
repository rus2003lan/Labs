#include "tree.h"

void erase(Tree *tree) {
	if (tree != NULL) {
		free(tree->info);
		erase(tree->left);
		erase(tree->right);
		free(tree);
	}
}

int add(Tree **tree, char *info, unsigned int key) {
	Tree *ptr = *(tree);
	Tree *par = NULL;
	Tree *new_tree;
	if (ptr == NULL) {
		new_tree = (Tree *) calloc(1, sizeof(Tree));
		*(tree) = new_tree;
		(*tree)->key = key;
		(*tree)->info = info;
		return 0;
	}
	while (ptr != NULL) {
		par = ptr;
		if (key < ptr->key) ptr = ptr->left;
		else if (key > ptr->key) ptr = ptr->right;
		else return 1;
	}
	new_tree = (Tree *) calloc(1, sizeof(Tree));
	if (key < par->key) {
		par->left = new_tree;
		par->left->key = key;
		par->left->info = info;
		par->left->par = par;
	}
	else {
		par->right = new_tree;
		par->right->key = key;
		par->right->info = info;
		par->right->par = par;
	}
	return 0;
}

int delete(Tree **tree, unsigned int key) {
	Tree *findtree = find_tree(*tree, key);
	if (findtree == NULL) return 1;
	if (findtree->par == NULL) { // удаление корня
		free(findtree->info);
		findtree->info = NULL;
		if (findtree->left == NULL || findtree->right == NULL) {
			if (findtree->left == NULL && findtree->right == NULL) *tree = NULL;
			else if (findtree->left == NULL) {
				findtree->right->par = NULL;
				*tree = findtree->right;
			}
			else {
				findtree->left->par = NULL;
				*tree = findtree->left;
			}
			free(findtree);
			return 0;
		}
	}
	if (findtree->left == NULL && findtree->right == NULL) {
		free(findtree->info);
		if (findtree->par->left == findtree) findtree->par->left = NULL;
		else findtree->par->right = NULL;
		free(findtree);
		return 0;
	}
	else if (findtree->left == NULL) {
		findtree->right->par = findtree->par;
		if (findtree->par->right == findtree) findtree->par->right = findtree->right;
		else findtree->par->left = findtree->right;
		free(findtree->info);
		free(findtree);
		return 0;
	}
	else if (findtree->right == NULL) {
		findtree->left->par = findtree->par;
		if (findtree->par->right == findtree) findtree->par->right = findtree->left;
		else findtree->par->left = findtree->left;
		free(findtree->info);
		free(findtree);
		return 0;
	}
	Tree *tmp = findtree; //во временной тот, что хотим удалить
	findtree = findtree->right;
	if (tmp->info != NULL) free(tmp->info); // на случай, если уже очищена инфа корня
	if (findtree->left == NULL) { //правый не имеет детей либо только правый
		tmp->info = findtree->info;
		tmp->key = findtree->key;
		tmp->right = findtree->right;
		if (findtree->right != NULL) findtree->right->par = tmp;
		free(findtree);
		return 0;
	}
	while(findtree->left != NULL) findtree = findtree->left; // жертва
	if (findtree == tmp->right) findtree = findtree->left;
	tmp->info = findtree->info;
	tmp->key = findtree->key;
	if (findtree->right == NULL) {
		findtree->par->left = NULL;
	}
	else {
		findtree->par->left = findtree->right;
		findtree->right->par = findtree->par;
	}
	free(findtree);
	return 0;
}

int round_tree(Tree *tree, unsigned int min_key) {
	if (tree != NULL) {
		round_tree(tree->right, min_key);
		if (tree->key > min_key) printf("%u ", tree->key);
		else return 0;
		round_tree(tree->left, min_key);
	}
}

Tree *find_tree(Tree *tree, unsigned int key) {
	Tree *ptr = tree;
	while (ptr != NULL) {
		if (key == ptr->key) return ptr;
		else if (key < ptr->key) ptr = ptr->left;
		else ptr = ptr->right;
	}
	return NULL;
}

Tree *special_find(Tree *tree, unsigned int max_key) {
	Tree *ptr = tree;
	Tree *candidate = NULL;
	if (ptr == NULL) return NULL;
	while (ptr != NULL) {
		if (ptr->key > max_key) {
			if (ptr->left == NULL) return candidate;
			ptr = ptr->left;
		}
		else if (ptr->key < max_key) {
			if (ptr->right == NULL) return ptr;
			candidate = ptr;
			ptr = ptr->right;
		}
		else return ptr;
	}
	return ptr;
}

void show(Tree *tree, int space) {
	if (tree != NULL) {
		space += 10;
		show(tree->right, space);
		printf("\n");
		for (int i = 0; i < space - 10; i++) printf(" ");
		printf("%u", tree->key);
		show(tree->left, space);
	}
}

void loading_from_file(Tree **tree, FILE *file) {
	unsigned int key;
	char *info;
	int check;
	while(1) {
		check = getunint_from_file(file, &key);
		if (check == 1) break;
		info = get_str_from_file(file);
		if (info == NULL) break;
		check = add(tree, info, key);
		if (check == 1) free(info);
	}
}

int timing() {
	Tree *root = NULL;
	unsigned int n = 10, key[10000], k, cnt = 1000000, i, m, index = 0;
	clock_t first, last;
	srand(time(NULL));
	char *info = "a";
	while (n-- > 0) {
		for(i = 0; i < 10000; ++i) {
			key[i] = rand() * rand();
		}
		for (i = 0; i < cnt; ) {
			k = rand() * rand();
			char *copy = (char *) malloc(sizeof(char) * 2);
			memcpy(copy, info, 2 * sizeof(char));
			if (add(&root, copy, k) == 0) {
				//if (i % (cnt / 100) == 0) printf("%u\n", i / (cnt / 100));
				++i;
			}
			else free(copy);
		}
		m = 0;
		first = clock();
		for(i = 0; i < 10000; ++i) {
			if (find_tree(root, key[i]) != NULL) {
				++m;
			}
		}
		last = clock();
		printf("%u items was found\n", m);
		printf("test #%u, number of nodes = %u, time = %lu\n", 10 - n, (10 - n) * cnt, last - first);
	}
	erase(root);
	return 1;
}