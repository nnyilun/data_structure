#include <stdio.h>
#include <stdlib.h>

#define LINK 0
#define THREAD 1

typedef int elemtype;

typedef struct TBNode {
    elemtype data;
    struct TBNode *lchild;
    struct TBNode *rchild;
    int leftThread, rightThread;
}TBNode;

TBNode* buildThreadedBinaryTree_fromInput();
void buildThreaded(TBNode *root);
void InThreading(TBNode *root, TBNode **prior);

TBNode* getFirst(TBNode *root);
void InOrderTraverseThread(TBNode *Head);

TBNode* buildThreadedBinaryTree_fromInput(){
    elemtype tmp;
    TBNode *p = NULL;
    scanf("%d", &tmp);
    if(tmp != 0){
        p = (TBNode*)malloc(sizeof(TBNode));
        p->data = tmp;
        p->lchild = buildThreadedBinaryTree_fromInput();
        p->rchild = buildThreadedBinaryTree_fromInput();
        p->leftThread = LINK;
        p->rightThread = LINK;
    }
    return p;
}

void buildThreaded(TBNode *root){
    if(!root)return;
    TBNode *pre = NULL;
    InThreading(root, &pre);
    pre->rchild = NULL;
    pre->rightThread = THREAD;
}

void InThreading(TBNode *root, TBNode **prior){
    if(!root) return;
    InThreading(root->lchild, prior);
    if(!root->lchild){
        root->lchild = *prior;
        root->leftThread = THREAD;
    }
    if(!root->rchild && (*prior)){
        (*prior)->rchild = root;
        (*prior)->rightThread = THREAD;
    }
    *prior = root;
    InThreading(root->rchild, prior);
}

TBNode* getFirst(TBNode *root){
    while(root->leftThread == LINK) root = root->lchild;
    return root;
}

void InOrderTraverseThread(TBNode *root){
    
}

int main(){
    TBNode *root = buildThreadedBinaryTree_fromInput();

    TBNode *pre = NULL, *t = NULL;
    buildThreaded(&root, t, &pre);

    InOrderTraverseThread(root);
    return 0;
}