#include <stdio.h>
#include <stdlib.h>

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(int x, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(int x, SearchTree T);
SearchTree Delete(int x, SearchTree T);
int Retrieve(Position p);

struct TreeNode {
    int data;
    SearchTree left;
    SearchTree right;
};

SearchTree Init() {
    SearchTree T;
    T = malloc(sizeof(struct TreeNode));
    T->left = NULL;
    T->right = NULL;
    return T;
}

SearchTree MakeEmpty(SearchTree T) {
    if(T != NULL) {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
    return NULL;
}

Position Find(int x, SearchTree T) {
    if(T == NULL) {
        return NULL;
    }
    if(x < T->data) {
        return Find(x, T->left);
    } else if(x > T->data){
        return Find(x, T->right);
    } else {
        return T;
    }
}

Position FindMin(SearchTree T) {
    if(T != NULL) {
        while(T->left != NULL) {
            T = T->left;
        }
    }
    return T;
//    if(T == NULL) {
//        return NULL;
//    }else if(T->left == NULL) {
//        return T;
//    } else {
//        return FindMin(T->left);
//    }
}

Position FindMax(SearchTree T) {
    if(T != NULL) {
        while(T->right != NULL) {
            T = T->right;
        }
    }
    return T;
}

SearchTree Insert(int x, SearchTree T) {
    if(T == NULL) {
        T = malloc(sizeof(struct TreeNode));
        if((T == NULL)) {
            printf("out of space!!!");
        } else {
            T->data = x;
            T->left = NULL;
            T->right = NULL;
        }
    } else if (x < T->data) {
        T->left = Insert(x, T->left);
    } else if (x > T->data) {
        T->right = Insert(x, T->right);
    }
    return T;
}

SearchTree Delete(int x, SearchTree T) {
    Position tmp;
    if(T == NULL) {
        printf("data not found\n");
    } else if (x < T->data) {
        T->left = Delete(x, T->left);
    } else if (x > T->data) {
        T->right = Delete(x, T->right);
    } else if (T->left && T->right) {
        tmp = FindMin(T->right);
        T->data = tmp->data;
        T->right = Delete(T->data, T->right);
    } else {
        tmp = T;
        if(T->left == NULL) {
            T = T->right;
        } else if(T->right == NULL) {
            T = T->left;
        }
        free(tmp);
    }
    return T;
}

int Retrieve(Position p) {
    return p->data;
}

int main()
{
    int a[10] = {5, 3, 1, 7, 4, 2, 8, 0, 9, 6};
    SearchTree T;
    T = Init();
    T->data = a[0];

    for(int i = 1; i < 10; i++) {
        Insert(a[i], T);
    }

    printf("最小值：%d\n", Retrieve(FindMin(T)));
    printf("最大值：%d\n", Retrieve(FindMax(T)));

    printf("删除0和9之后\n");
    Delete(0, T);
    Delete(9, T);

    printf("最小值：%d\n", Retrieve(FindMin(T)));
    printf("最大值：%d\n", Retrieve(FindMax(T)));
}
