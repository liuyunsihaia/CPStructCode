#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

struct huffmantree_single {                         //创建哈夫曼树类型
    int weight;
    struct huffmantree_single * lchild;
    struct huffmantree_single * rchild;
}huffmantree;
typedef struct huffmantree_single * HuffmanTree;

struct TreeStack_single {                           //创建一个哈夫曼类型的排序的栈类型，以便选取两个最小的叶节点合并
    HuffmanTree t;
    struct TreeStack_single *next;
}stack;
typedef struct TreeStack_single * Stack;


void InitNode(HuffmanTree t, int weight);       //对根节点进行初始化
void InsertStack(Stack s, HuffmanTree t);       //将一个节点压入栈中,栈根据节点的权值从小到大排序，保证栈顶元素权值为最小
int CreateStack(Stack s);                       //压入数据
HuffmanTree DeleteMinStack(Stack s);            //抛出栈顶元素含有的节点
void midorder(HuffmanTree t);                   //中序遍历，第二次遇到根节点时输出
void BuildTree(int n, Stack s);                 //构建哈夫曼树
void PrintStack(Stack s);                       //输出栈中元素


void InitNode(HuffmanTree t, int weight) {
    if(t == NULL) {
        printf("out of space");
    }
    t->weight = weight;
    t->lchild = NULL;
    t->rchild = NULL;
}

Stack InitStack() {                         //
    Stack s;
    s = (Stack)malloc(sizeof(stack));
    s->next = NULL;
    return s;
}

void InsertStack(Stack s, HuffmanTree t) {
    Stack tmp, tp;
    tmp = s;
    tp = (Stack)malloc(sizeof(stack));
    tp->t = t;

    if(s->next == NULL) {                     //当栈为空时，直接进行压入操作
        tp->next = NULL;
        s->next = tp;
        return ;
    }

    if(t->weight < tmp->next->t->weight) {
        tp->next = tmp->next;
        tmp->next = tp;

        return ;
    } else {
        while(tmp->next != NULL && t->weight > tmp->next->t->weight) {
            tmp = tmp->next;
        }
        tp->next = tmp->next;
        tmp->next = tp;
        return ;
    }
}

HuffmanTree DeleteMinStack(Stack s) {
    Stack tmp;
    HuffmanTree tempt;

    if(s->next == NULL) {
        printf("这是空栈，请先压入数据！");
    }

    tmp = s->next;
    tempt = tmp->t;
    s->next = tmp->next;
    free(tmp);

    return tempt;
}

void midorder(HuffmanTree t){
    if (t != NULL) {
        midorder(t->lchild);
        printf("%d ", t->weight);
        midorder(t->rchild);
    }
}

void BuildTree(int n, Stack s) {
    for(int i = 1; i < n; i++) {
        HuffmanTree tmp;

        tmp = (HuffmanTree)malloc(sizeof(huffmantree));
        tmp->lchild = DeleteMinStack(s);
        tmp->rchild = DeleteMinStack(s);

        tmp->weight = tmp->lchild->weight + tmp->rchild->weight;
        InsertStack(s, tmp);
    }
}

void PrintStack(Stack s) {
    printf("\n打印栈:\n");

    Stack tmp;
    tmp = s->next;
    while(tmp != NULL) {
        printf("%d  ", tmp->t->weight);
        tmp = tmp->next;
    }

    printf("\n\n");
}

int CreateStack(Stack s) {
    int n;
    int a[MAXSIZE];
    HuffmanTree t;

    printf("请输入节点个数:\n");
    scanf("%d", &n);

    printf("请输入数据:\n");

    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        t = (HuffmanTree)malloc(sizeof(huffmantree));
        InitNode(t,a[i]);
        InsertStack(s, t);
    }
    return n;
}

int main()
{
    int n;                  //节点个数

    HuffmanTree t;
    Stack s;

    s = InitStack();            //初始化栈(头结点不存储树)
    n = CreateStack(s);         //创建栈，并压入数据
    PrintStack(s);              //输出栈中数据
    BuildTree(n, s);            //构造哈夫曼树

    t = DeleteMinStack(s);      //得到栈中唯一元素，即构造完成的哈夫曼树
    printf("根节点为：%d\n\n", t->weight);

    printf("对构造完成的哈夫曼树进行中序遍历：");
    midorder(t);
}
