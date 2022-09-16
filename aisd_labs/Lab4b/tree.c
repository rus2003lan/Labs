#include "tree.h"

void erase(Tree *tree) {
    if (tree->par != NULL) { // если пэрент NULL, то попали в елист, очищать не надо
        erase(tree->left);
        erase(tree->right);
        free(tree);
    }
}

Tree *create_elist(){
    Tree *elist = (Tree *) calloc(1, sizeof(Tree));
    elist->color = 1;
    elist->right = elist->left = elist->par = NULL;
    return elist;
}

Tree *create_tree(unsigned int key, unsigned int info) {
    Tree *new_tree = (Tree *) calloc(1, sizeof(Tree));
    new_tree->key = key;
    new_tree->info = info;
    new_tree->color = 0;
    return new_tree;
}

unsigned int add(Tree **tree, unsigned int info, unsigned int key, int *flag) {
    Tree *ptr = *tree;
    Tree *parent = NULL;
    Tree *new_tree;
    Tree *elist;
    Tree *tmp;
    if((*tree) != NULL) elist = (*tree)->par;
    else elist = create_elist();
    if (ptr == NULL) { // пустое дерево красим в черный
        new_tree = create_tree(key, info);
        new_tree->left = elist;
        new_tree->right = elist;
        new_tree->par = elist;
        new_tree->color = 1;
        *tree = new_tree;
        return info;
    }
    while (ptr != elist) { //после этого цикла в parent либо влево либо вправо цепляется наш айтем
        parent = ptr;
        if (key < ptr->key) ptr = ptr->left;
        else if (key > ptr->key) ptr = ptr->right;
        else {
            *flag = 1;
            unsigned int tmp = ptr->info;
            ptr->info = info;
            return tmp;
        }
    }
    new_tree = create_tree(key, info);
    new_tree->left = elist;
    new_tree->right = elist;
    if (key < parent->key) {
        parent->left = new_tree;
        new_tree->par = parent;
    }
    else {
        parent->right = new_tree;
        new_tree->par = parent;
    }                            // обычная часть закончена, вставлен красный айтем
    (*tree) = balance(new_tree);
    (*tree)->color = 1;
    return info;
}

Tree *balance(Tree *x) {
    Tree *p1;
    Tree *p2;
    Tree *pp;
    while (x->par->color == 0) {
        p1 = x->par;
        pp = x->par->par;
        if (p1 == pp->right) p2 = pp->left;
        else p2 = pp->right;
        if (p2->color == 0) { // случай 1
            p2->color = 1;
            p1->color = 1;
            pp->color = 0;
            if (pp->par->par == NULL) {
                x = pp;
                break;
            }
            x = pp;
        }
        else if (p2->color == 1) {
            if (p1 == pp->left && x == p1->right) {
                x = p1;
                left_rotate(x);
                p1 = x->par;
            }
            else if (p1 == pp->right && x == p1->left) {
                x = p1;
                right_rotate(x);
                p1 = x->par;
            }
            p1->color = 1;
            pp->color = 0;
            if (x == p1->right) {
                left_rotate(pp);
            }
            else {
                right_rotate(pp);
            }
            break;
        }
    }
    while (x->par->par != NULL) x = x->par;
    return x;
}

Tree *left_rotate(Tree *tree) {
    Tree *child = tree->right;
    Tree *left_child = child->left;
    Tree *tmp = tree->par;
    child->left = tree;
    tree->par = child;
    tree->right = left_child;
    if (left_child->left != NULL) left_child->par = tree; // если это елист
    child->par = tmp;
    if (tmp->left != NULL && tmp->left == tree) tmp->left = child;
    else if (tmp->left != NULL && tmp->right == tree) tmp->right = child;
    return child;
}

Tree *right_rotate(Tree *tree) {
    Tree *child = tree->left;
    Tree *right_child = child->right;
    Tree *tmp = tree->par;
    child->right = tree;
    tree->par = child;
    tree->left = right_child;
    if (right_child->left != NULL) right_child->par = tree;
    child->par = tmp;
    if (tmp->left != NULL && tmp->left == tree) tmp->left = child;
    else if (tmp->left != NULL && tmp->right == tree) tmp->right = child;
    return child;
}

int delete(Tree **tree, unsigned int key) {
    Tree *findtree = find_tree(*tree, key);
    if (findtree == NULL) return 1;
    Tree *elist = (*tree)->par;
    Tree *parent;
    if (findtree->par == elist) { // удаление корня
        if (findtree->left == elist || findtree->right == elist) {
            if (findtree->left == elist && findtree->right == elist) {
                free(elist);
                free(findtree);
                *tree = NULL;
                return 0;
            }
            else if (findtree->right == elist) {
                findtree->left->par = elist;
                *tree = findtree->left;
            }
            else if (findtree->left == elist) {
                findtree->right->par = elist;
                *tree = findtree->right;
            }
            free(findtree);
            (*tree)->color = 1;
            return 0;
        }
    }
    if (findtree->left == elist && findtree->right == elist) {
        if (findtree->par->left == findtree) findtree->par->left = elist;
        else findtree->par->right = elist;
        if (findtree->color == 1) {
            elist->par = findtree->par;
            parent = delete_balance(elist);
            elist->par = NULL;
            while(parent->par->par != NULL) parent = parent->par;
            (*tree) = parent;
        }
        free(findtree);
        return 0;
    }
    else if (findtree->right == elist) {
        findtree->info = findtree->left->info;
        findtree->key = findtree->left->key;
        free(findtree->left);
        findtree->left = elist;
        return 0;
    }
    else if (findtree->left == elist) {
        findtree->info = findtree->right->info;
        findtree->key = findtree->right->key;
        free(findtree->right);
        findtree->right = elist;
        return 0;
    }
    Tree *tmp = findtree; //во временной тот, что хотим удалить
    findtree = findtree->right;
    if (findtree->left == elist) {
        tmp->info = findtree->info;
        tmp->key = findtree->key;
        tmp->right = findtree->right;
        if (findtree->right != elist) findtree->right->par = findtree->par;
        if (findtree->color == 1) {
            elist->par = findtree->par;
            parent = delete_balance(findtree->right);
            elist->par = NULL;
            while(parent->par->par != NULL) parent = parent->par;
            (*tree) = parent;
        }
        free(findtree);
        return 0;
    }
    while(findtree->left != elist) findtree = findtree->left; // жертва
    if (findtree == tmp->right) findtree = findtree->left;
    tmp->info = findtree->info;
    tmp->key = findtree->key;;
    if (findtree->right != elist) findtree->right->par = findtree->par;
    findtree->par->left = findtree->right;
    if (findtree->color == 1) {
        elist->par = findtree->par;
        parent = delete_balance(findtree->right);
        elist->par = NULL;
        while(parent->par->par != NULL) parent = parent->par;
        (*tree) = parent;
    }
    free(findtree);
    return 0;
}

Tree *delete_balance(Tree *x) {
    Tree *s;
    while (x->par->right != NULL && x->color == 1) {
        if (x == x->par->left) {
            s = x->par->right;
            if (s->color == 0) {
                s->color = 1;
                x->par->color = 0;
                left_rotate(x->par);
                s = x->par->right;
            }
            if (s->right->color == 1 && s->left->color == 1) {
                s->color = 0;
                x = x->par;
            }
            else {
                if (s->right->color == 1) {
                    s->left->color = 1;
                    s->color = 0;
                    right_rotate(s);
                    s = x->par->right;
                }
                s->color = x->par->color;
                x->par->color = 1;
                s->right->color = 1;
                left_rotate(x->par);
                x->color = 1;
                return x->par;
            }
        } else {
            s = x->par->left;
            if (s->color == 0) {
                s->color = 1;
                x->par->color = 0;
                right_rotate(x->par);
                s = x->par->left;
            }
            if (s->right->color == 1 && s->left->color == 1) {
                s->color = 0;
                x = x->par;
            } else {
                if (s->left->color == 1) {
                    s->right->color = 1;
                    s->color = 0;
                    left_rotate(s);
                    s = x->par->left;
                }
                s->color = x->par->color;
                x->par->color = 1;
                s->left->color = 1;
                right_rotate(x->par);
                x->color = 1;
                return x->par;
            }
        }
    }
    x->color = 1;
    return x;
}

int round_tree(Tree *tree, unsigned int min_key, unsigned int max_key) {
    if (min_key > max_key) return 1;
    if (tree == NULL) return 0;
    if (tree->par != NULL) { //проверка на елист
        round_tree(tree->right, min_key, max_key);
        if (tree->key < min_key || tree->key > max_key) printf("%u ", tree->key);
        round_tree(tree->left, min_key, max_key);
    }
}

Tree *find_tree(Tree *tree, unsigned int key) {
    Tree *ptr = tree;
    if (ptr == NULL) return NULL;
    while (ptr->par != NULL) {
        if (key == ptr->key) return ptr;
        else if (key < ptr->key) ptr = ptr->left;
        else ptr = ptr->right;
    }
    return NULL;
}

Tree *special_find(Tree *tree, unsigned int min_key) {
    if (tree == NULL) return NULL;
    Tree *elist = tree->par;
    Tree *ptr = tree;
    Tree *candidate = NULL;
    if (ptr == NULL) return NULL;
    while (1) {
        if (ptr->key <= min_key) {
            if (ptr->right == elist) return candidate;
            ptr = ptr->right;
        }
        else if (ptr->key > min_key) {
            if (ptr->left == elist) return ptr;
            candidate = ptr;
            ptr = ptr->left;
        }
    }
    return ptr;
}

void show(Tree *tree, int space) {
    if (tree != NULL && tree->par != NULL) {
        space += 10;
        show(tree->right, space);
        printf("\n");
        for (int i = 0; i < space - 10; i++) printf(" ");
        printf("%u", tree->key);
        if (tree->color == 1) printf(" B");
        else if (tree->color == 0) printf(" R");
        show(tree->left, space);
    }
}

void loading_from_file(Tree **tree, FILE *file) {
    unsigned int key;
    unsigned int info;
    int flag = 0;
    int check;
    while(1) {
        check = getunint_from_file(file, &key);
        if (check == 1) break;
        check = getunint_from_file(file, &info);
        if (check == 1) break;
        add(tree, info, key, &flag);
    }
}

int timing() {
    Tree *root = NULL;
    int flag = 0;
    unsigned int n = 10, key[10000], k, cnt = 1000000, i, m, index = 0;
    clock_t first, last;
    srand(time(NULL));
    while (n-- > 0) {
        for(i = 0; i < 10000; ++i) {
            key[i] = rand() * rand();
        }
        for (i = 0; i < cnt; ) {
            k = rand() * rand();
            add(&root, 1, k, &flag);
            if (flag == 0) {
                //if (i % (cnt / 100) == 0) printf("%u\n", i / (cnt / 100));
                ++i;
            }
            else flag = 0;
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