#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

struct huffmantree_single {                         //����������������
    int weight;
    struct huffmantree_single * lchild;
    struct huffmantree_single * rchild;
}huffmantree;
typedef struct huffmantree_single * HuffmanTree;

struct TreeStack_single {                           //����һ�����������͵������ջ���ͣ��Ա�ѡȡ������С��Ҷ�ڵ�ϲ�
    HuffmanTree t;
    struct TreeStack_single *next;
}stack;
typedef struct TreeStack_single * Stack;


void InitNode(HuffmanTree t, int weight);       //�Ը��ڵ���г�ʼ��
void InsertStack(Stack s, HuffmanTree t);       //��һ���ڵ�ѹ��ջ��,ջ���ݽڵ��Ȩֵ��С�������򣬱�֤ջ��Ԫ��ȨֵΪ��С
int CreateStack(Stack s);                       //ѹ������
HuffmanTree DeleteMinStack(Stack s);            //�׳�ջ��Ԫ�غ��еĽڵ�
void midorder(HuffmanTree t);                   //����������ڶ����������ڵ�ʱ���
void BuildTree(int n, Stack s);                 //������������
void PrintStack(Stack s);                       //���ջ��Ԫ��


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

    if(s->next == NULL) {                     //��ջΪ��ʱ��ֱ�ӽ���ѹ�����
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
        printf("���ǿ�ջ������ѹ�����ݣ�");
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
    printf("\n��ӡջ:\n");

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

    printf("������ڵ����:\n");
    scanf("%d", &n);

    printf("����������:\n");

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
    int n;                  //�ڵ����

    HuffmanTree t;
    Stack s;

    s = InitStack();            //��ʼ��ջ(ͷ��㲻�洢��)
    n = CreateStack(s);         //����ջ����ѹ������
    PrintStack(s);              //���ջ������
    BuildTree(n, s);            //�����������

    t = DeleteMinStack(s);      //�õ�ջ��ΨһԪ�أ���������ɵĹ�������
    printf("���ڵ�Ϊ��%d\n\n", t->weight);

    printf("�Թ�����ɵĹ��������������������");
    midorder(t);
}
