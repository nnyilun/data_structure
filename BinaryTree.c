/*

    Auther: JiangYilun
    Created date: 2022/04/01
    Last update: 2022/04/11
    Description: Binary tree
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define NOEXIST -1
#define OVERFLOW -2
#define MEM_ERR -3

typedef int elemtype;

typedef struct BinaryTreeNode{
    elemtype data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
}BTNode;

typedef BTNode* queue_elemtype;
const int QueueSize = 100;
typedef struct Queue{
    queue_elemtype *base;
    int front;
    int tail;
}queue;

queue* _InitQueue(){
    queue *q = (queue *)malloc(sizeof(queue));
    if(!q) exit(MEM_ERR);
    q->base = (queue_elemtype *)malloc(sizeof(queue_elemtype) * QueueSize);
    if(!q->base) exit(MEM_ERR);
    q->front = 0;
    q->tail = 0;
    return q;
}
void _push_back_queue(queue *q, queue_elemtype value){
    if(q->front == (q->tail + 1) % QueueSize){
        printf("Queue is full!\n");
        exit(OVERFLOW);
    }
    q->base[q->tail] = value;
    q->tail = (q->tail + 1) % QueueSize;
}
queue_elemtype _front_queue(queue *q){
    return q->base[q->front];
}
queue_elemtype _pop_queue(queue *q){
    queue_elemtype t = q->base[q->front];
    q->front = (q->front + 1) % QueueSize;
    return t;
}
int _queue_size(queue *q){
    return (q->tail - q->front + QueueSize) % QueueSize;
}
int _queue_isEmpty(queue *q){
    return q->front == q->tail;
}
void _destroy_queue(queue **q){
    free((*(*q)).base);
    (*q)->front = 0;
    (*q)->tail = 0;
    free(*q);
}

struct QueueFunctions{
    queue* (*InitQueue)(void);
    void (*push)(queue *s, queue_elemtype value);
    queue_elemtype (*front)(queue *s);
    queue_elemtype (*pop)(queue *s);
    int (*size)(queue *q);
    int (*isEmpty)(queue *s);
    void (*destroy)(queue **s);
}queueFunc = {
    _InitQueue,
    _push_back_queue,
    _front_queue,
    _pop_queue,
    _queue_size,
    _queue_isEmpty,
    _destroy_queue
};

typedef BTNode* stack_elemtype;
const int StackSize = 100;
typedef struct Stack{
    stack_elemtype *base;
    int top;
}stack;

stack* _InitStack(){
    stack *s = (stack *)malloc(sizeof(stack));
    if(!s) exit(MEM_ERR);
    s->base = (stack_elemtype *)malloc(sizeof(stack_elemtype) * StackSize);
    if(!s->base) exit(MEM_ERR);
    s->top = 0;
    return s;
}
void _push_stack(stack *s, stack_elemtype value){
    if(s->top == StackSize){
        printf("Stack is full!\n");
        exit(OVERFLOW);
    }
    s->base[s->top++] = value;
}
stack_elemtype _top_stack(stack *s){
    return s->base[s->top - 1];
}
stack_elemtype _pop_stack(stack *s){
    return s->base[--s->top];
}
int _stack_isEmpty(stack *s){
    return s->top == 0;
}
void _destroy_stack(stack **s){
    free((*s)->base);
    (*s)->top = 0;
    free(*s);
}

struct StackFunctions{
    stack* (*InitStack)(void);
    void (*push)(stack *q, stack_elemtype value);
    stack_elemtype (*top)(stack *q);
    stack_elemtype (*pop)(stack *q);
    int (*isEmpty)(stack *q);
    void (*destroy)(stack **q);
}stackFunc = {
    _InitStack,
    _push_stack,
    _top_stack,
    _pop_stack,
    _stack_isEmpty,
    _destroy_stack
};

// ------implementtation------
// ----build tree----
BTNode* buildTreeRoot(elemtype data);
void insertNodeinOrder(BTNode **root, elemtype data);
BTNode* buildBinaryTree_fromInput(elemtype(*getData)(void));
BTNode* buildTree_fromDLRandLDR(elemtype *DLRarr, elemtype *DLRtail, elemtype *LDRarr, elemtype *LDRtail);
BTNode* buildTree_fromDLRandLDR_2(elemtype *DLRarr, elemtype *LDRarr, int a1, int b1, int a2, int b2);
BTNode* buildTree_fromLRDandLDR(elemtype *LRDarr, elemtype *LRDtail, elemtype *LDRarr, elemtype *LDRtail);

// ----print tree----
void prettyPrint(BTNode *root, void(*print)(elemtype*));
void preorderTraversal(BTNode *root, void(*print)(elemtype*));
void preorderTraversal_recursion(BTNode *root, void(*print)(elemtype*));
void inorderTraversal(BTNode *root, void(*print)(elemtype*));
void inorderTraversal_recursion(BTNode *root, void(*print)(elemtype*));
void postorderTraversal(BTNode *root, void(*print)(elemtype*));
void postorderTraversal_recursion(BTNode *root, void(*print)(elemtype*));
void Traversal_template(BTNode *root, void(*print)(elemtype*), int order);
void levelorderTraversal(BTNode *root, void(*print)(elemtype*));
void preorderTraversal_method2(BTNode *root, void(*print)(elemtype*));

// ----some functions / get properties----
void mirrorTree(BTNode *root);
int getDepth(BTNode *root);
int getWidth(BTNode *root);
int getNodeNum(BTNode *root);
int getNodeNumInKthFloor(BTNode *root, int k);
int getNodeNumInKthFloor_recursion(BTNode *root, int k);
int getLeafNodeNum(BTNode *root);
int isSameStructure(BTNode *root1, BTNode *root2);
BTNode* getLCA(BTNode *root, BTNode *p, BTNode *q);
int maxDistance(BTNode *root);
int isCompleteTree(BTNode *root);

// ------implementtation------
// ----build tree----
BTNode* buildTreeRoot(elemtype data){
    BTNode *root = (BTNode*)malloc(sizeof(BTNode));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void insertNodeinOrder(BTNode **root, elemtype data){
    if(!root) *root = buildTreeRoot(data);
    else{
        if((*root)->data > data) insertNodeinOrder(&(*root)->right, data);
        else insertNodeinOrder(&(*root)->left, data);
    }
}

BTNode* buildBinaryTree_fromInput(elemtype(*getData)(void)){
    BTNode *p = NULL;
    elemtype data = getData();
    if(data != 0){
        p = (BTNode*)malloc(sizeof(BTNode));
        p->data = data;
        p->left = buildBinaryTree_fromInput(getData);
        p->right = buildBinaryTree_fromInput(getData);
    }
    return p;
}

BTNode* buildTree_fromDLRandLDR(elemtype *DLRarr, elemtype *DLRtail, elemtype *LDRarr, elemtype *LDRtail){
    if(DLRarr > DLRtail || LDRarr > LDRtail) return NULL;
    BTNode *p = (BTNode*)malloc(sizeof(BTNode));
    p->data = *DLRarr;
    int mid = 0;
    for(elemtype* begin = LDRarr, *end = LDRtail; begin <= end && *begin != p->data; ++begin, ++mid);
    p->left = buildTree_fromDLRandLDR(DLRarr + 1, DLRarr + mid, LDRarr, LDRarr + mid - 1);
    p->right = buildTree_fromDLRandLDR(DLRarr + mid + 1, DLRtail, LDRarr + mid + 1, LDRtail);
    return p;
}

BTNode* buildTree_fromDLRandLDR_2(elemtype *DLRarr, elemtype *LDRarr, int a1, int b1, int a2, int b2){
    if(a1 > b1 || a2 > b2)return NULL;
    BTNode *p = (BTNode*)malloc(sizeof(BTNode));
    p->data = DLRarr[a1];
    int mid = a2;
    for(; mid <= b2 && LDRarr[mid] != DLRarr[a1]; ++mid);
    p->left = buildTree_fromDLRandLDR_2(DLRarr, LDRarr, a1 + 1, a1 + (mid - a2), a2, mid - 1);
    p->right = buildTree_fromDLRandLDR_2(DLRarr, LDRarr, a1 + (mid - a2 + 1), b1, mid + 1, b2);
    return p;
}

BTNode* buildTree_fromLRDandLDR(elemtype *LRDarr, elemtype *LRDtail, elemtype *LDRarr, elemtype *LDRtail){
    if(LRDarr > LRDtail || LDRarr > LDRtail) return NULL;
    BTNode *p = (BTNode*)malloc(sizeof(BTNode));
    p->data = *LRDtail;
    int mid = 0;
    for(elemtype* begin = LDRarr, *end = LDRtail; begin <= end && *begin != p->data; ++begin, ++mid);
    p->left = buildTree_fromLRDandLDR(LRDarr, LRDarr + mid - 1, LDRarr, LDRarr + mid - 1);
    p->right = buildTree_fromLRDandLDR(LRDarr + mid, LRDtail - 1, LDRarr + mid + 1, LDRtail);
    return p;
}

// ----print tree----
void prettyPrint(BTNode *root, void(*print)(elemtype*)){
    printf("--------\n");
    if(!root) {
        printf("NULL\n--------\n");
        return;
    }

    //-1┌ -2─ -3┴ -4┐ -5┘ -6└
    int _depth = getDepth(root), _width = getWidth(root), _nodeNum = getNodeNum(root);
    printf("depth: %d, width: %d, nodeNum: %d\n", _depth, _width, _nodeNum);

    int width = _depth * 4 - 1, height = _depth * 2 - 1;
    int **map = (int**)malloc(sizeof(int*) * height);
    for(int i = 0; i < height; ++i) map[i] = (int*)calloc(width, sizeof(int));
    BTNode **_node = (BTNode**)malloc(sizeof(BTNode*) * _nodeNum + 1);
    int front = 0, tail = 0, size = 1;
    _node[tail++] = root;
    map[0][width / 2] = 1;
    for(int row = 1, interval = width / (size * 2), t_tail = tail, pos = -1; row < height; row += 2, size *= 2, pos = -1){
        t_tail = tail;
        interval = width / (size * 4);
        for(int i = 1; i <= size && front < t_tail; ++i){
            if(_node[front]->left || _node[front]->right){
                int mid = pos + 2 * (interval + 1);
                map[row][mid] = -3;
                pos += interval + 1;
                if(_node[front]->left){
                    map[row][pos] = -1;
                    map[row + 1][pos] = 1;
                    _node[tail++] = _node[front]->left;   
                }
                else{
                    map[row][mid] = -6;
                }
                pos += 2 * (interval + 1);
                if(_node[front]->right){
                    map[row][pos] = -4;
                    map[row + 1][pos] = 1;
                    _node[tail++] = _node[front]->right;
                }
                else{
                    map[row][mid] = -5;
                }
                pos += interval + 1;
            }else pos += 4* (interval + 1);
            ++front;
        }
        for(int j = 0, flag = 0; j < width; ++j){
            if(map[row][j] == -1 || map[row][j] == -6) flag = 1;
            else if(map[row][j] == -4 || map[row][j] == -5)flag = 0;
            if(flag == 1 && map[row][j] == 0) map[row][j] = -2;
        }
    }
    
    for(int i = 0, cnt = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            if(map[i][j] == 1) print(&_node[cnt++]->data);
            else if(map[i][j] == -1) printf("┌");
            else if(map[i][j] == -2) printf("─");
            else if(map[i][j] == -3) printf("┴");
            else if(map[i][j] == -4) printf("┐");
            else if(map[i][j] == -5) printf("┘");
            else if(map[i][j] == -6) printf("└");
            else printf(" ");
            // printf("%4d", map[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < height; ++i) free(map[i]);
    free(map);
    free(_node);
    printf("--------\n");
}

void preorderTraversal(BTNode *root, void(*print)(elemtype*)){
    if(!root) return;
    stack *s = stackFunc.InitStack();
    BTNode *p = root;
    while(p || !stackFunc.isEmpty(s)){
        if(p){
            stackFunc.push(s, p);
            print(&p->data);printf(" ");
            p = p->left;
        }else{
            p = stackFunc.pop(s);
            p = p->right;
        }
    }
    stackFunc.destroy(&s);
}

void preorderTraversal_recursion(BTNode *root, void(*print)(elemtype*)){
    if(!root) return;
    print(&root->data);printf(" ");
    preorderTraversal_recursion(root->left, print);
    preorderTraversal_recursion(root->right, print);
}

void inorderTraversal(BTNode *root, void(*print)(elemtype*)){
    if(!root) return;
    stack *s = stackFunc.InitStack();
    BTNode *p = root;
    while(p || !stackFunc.isEmpty(s)){
        if(p){
            stackFunc.push(s, p);
            p = p->left;
        }else{
            p = stackFunc.pop(s);
            print(&p->data);printf(" ");
            p = p->right;
        }
    }
    stackFunc.destroy(&s);
}

void inorderTraversal_recursion(BTNode *root, void(*print)(elemtype*)){
    if(!root) return;
    inorderTraversal_recursion(root->left, print);
    print(&root->data);printf(" ");
    inorderTraversal_recursion(root->right, print);
}

void postorderTraversal(BTNode *root, void(*print)(elemtype*)){
    if(!root) return;
    stack *s = stackFunc.InitStack();
    BTNode *p = root, *tmp;
    while(p || !stackFunc.isEmpty(s)){
        if(p){
            if(p->right)stackFunc.push(s, p);
            stackFunc.push(s, p);
            p = p->left;
        }
        else{
            p = stackFunc.pop(s);
            if(p->right && p == stackFunc.top(s)){
                p = p->right;
            }
            else{
                print(&p->data);printf(" ");
                p = NULL;
            }
        }
    }
    stackFunc.destroy(&s);
}

void postorderTraversal_recursion(BTNode *root, void(*print)(elemtype*)){
    if(!root) return;
    postorderTraversal_recursion(root->left, print);
    postorderTraversal_recursion(root->right, print);
    print(&root->data);printf(" ");
}

void Traversal_template(BTNode *root, void(*print)(elemtype*), int order){
    /* 
        此方法仅仅需要改变输出位置即可实现三种非递归遍历，
        而上面的非递归遍历方法的后序遍历，相较于前序和中序，改动较大。
    */

    if(!root) return;
    stack *s = stackFunc.InitStack();
    BTNode *last_visit = root, *pre = root;
    while(pre || !stackFunc.isEmpty(s)){
        while(pre){     //不断往左节点跳跃，并且将沿途节点入栈
            if(order == 1) {print(&pre->data);printf(" ");}    //前序
            stackFunc.push(s, pre);
            pre = pre->left;        //每个节点在此处被第一次访问
        }

        pre = stackFunc.top(s);     //每个节点在次数被第二、三次访问
        if(pre->right != last_visit){       //右孩子未被访问，那么访问右孩子
            if(order == 2) {print(&pre->data);printf(" ");}    //中序
            pre = pre->right;
            if(!pre) last_visit = NULL; //右孩子为空，使下一循环直接取栈顶，并在下一次循环出栈该节点
        }
        else{       //右孩子已经被访问，那么该节点的左右子树都已经处理完毕，可以将该节点出栈
            if(order == 3) {print(&pre->data);printf(" ");}    //后序
            stackFunc.pop(s);
            last_visit = pre;
            pre = NULL;     //使下一循环直接取栈顶
        }
    }
    stackFunc.destroy(&s);
}

void levelorderTraversal(BTNode *root, void(*print)(elemtype*)){
    if(!root) return;
    queue *q = _InitQueue();
    queueFunc.push(q, root);
    while(!queueFunc.isEmpty(q)){
        BTNode *tmp = queueFunc.pop(q);
        print(&tmp->data);printf(" ");
        if(tmp->left) queueFunc.push(q, tmp->left);
        if(tmp->right) queueFunc.push(q, tmp->right);
    }
    queueFunc.destroy(&q);
}

void preorderTraversal_method2(BTNode *root, void(*print)(elemtype*)){
    /*
        只有当节点有右孩子时，入栈右孩子
        这样子可以减少栈的空间开销，也可以减少同一节点的访问次数，降低时间开销。
    */
    if(!root) return;
    stack *s = stackFunc.InitStack();
    stackFunc.push(s, NULL);    //小技巧：直接将一个空节点入栈，这样直接用pre即可判断栈是否为空
    BTNode *pre = root;
    while(pre){
        print(&pre->data);printf(" ");
        if(pre->right) stackFunc.push(s, pre->right);   //如果有右孩子，就入栈右孩子
        if(pre->left) pre = pre->left;
        else pre = stackFunc.pop(s);
    }
    stackFunc.destroy(&s);
}

// ----some functions / get properties----
void mirrorTree(BTNode *root){
    if(!root)return;
    BTNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    mirrorTree(root->left);
    mirrorTree(root->right);
}

int getDepth(BTNode *root){
    int left = root->left ? getDepth(root->left) : 0, right = root->right ? getDepth(root->right) : 0;
    return root == NULL ? 0 : (1 + (left > right ? left : right));
}

int getWidth(BTNode *root){
    if(!root)return 0;
    int width = 1;
    queue *q = queueFunc.InitQueue();
    queueFunc.push(q, root);
    while(!queueFunc.isEmpty(q)){
        int size = queueFunc.size(q);
        width = width > size ? width : size;
        while(size--){
            BTNode *tmp = queueFunc.pop(q);
            if(tmp->left) queueFunc.push(q, tmp->left);
            if(tmp->right) queueFunc.push(q, tmp->right);
        }
    }
    queueFunc.destroy(&q);
    return width;
}

int getNodeNum(BTNode *root){
    return root == NULL ? 0 : 1 + getNodeNum(root->left) + getNodeNum(root->right);
}

int getNodeNumInKthFloor(BTNode *root, int k){
    if(!root)return 0;
    if(k > getDepth(root)) return OVERFLOW;
    int floor = 1, size = 1;
    queue *q = queueFunc.InitQueue();
    queueFunc.push(q, root);
    for(floor = 1, size = 1; floor != k && !queueFunc.isEmpty(q); ++floor, size = queueFunc.size(q)){
        while(size--){
            BTNode *tmp = queueFunc.pop(q);
            if(tmp->left) queueFunc.push(q, tmp->left);
            if(tmp->right) queueFunc.push(q, tmp->right);
        }
    }
    queueFunc.destroy(&q);
    return size;
}

int getNodeNumInKthFloor_recursion(BTNode *root, int k){
    if(!root) return 0;
    if(k == 1) return 1;
    return getNodeNumInKthFloor_recursion(root->left, k - 1) + getNodeNumInKthFloor_recursion(root->right, k - 1);
}

int getLeafNodeNum(BTNode *root){
    return root == NULL ? 0 : (root->left == NULL && root->right == NULL ? 1 : getLeafNodeNum(root->left) + getLeafNodeNum(root->right));
}

int isSameStructure(BTNode *root1, BTNode *root2){
    if(!root1 && !root2)return TRUE;
    if(root1 && !root2 || !root1 && root2)return FALSE;
    return isSameStructure(root1->left, root2->left) && isSameStructure(root1->right, root2->right);
}

BTNode* getLCA(BTNode *root, BTNode *p, BTNode *q){
    if(!root) return NULL;
    if(root == p || root == q)return root;

    BTNode *l = getLCA(root->left, p, q);
    BTNode *r = getLCA(root->right, p, q);

    if(l && r)return root;
    return l ? l : r;
}

int _maxDistance(BTNode *root, int *maxlen){
    if(!root) return 0;
    int left_len = _maxDistance(root->left, maxlen);
    int right_len = _maxDistance(root->right, maxlen);
    int pre_len = 1 + (left_len > right_len ? left_len : right_len);
    if(left_len + right_len + 1 > *maxlen){
        *maxlen = left_len + right_len + 1;
    }
    return pre_len;
}

int maxDistance(BTNode *root){
    int len = 0;
    _maxDistance(root, &len);
    return len;
}

int isCompleteTree(BTNode *root){
    if(!root) return TRUE;
    queue *q = queueFunc.InitQueue();
    queueFunc.push(q, root);
    BTNode *node = root;
    while(node){
        queueFunc.push(q, node->left);
        queueFunc.push(q, node->right);
        queueFunc.pop(q);
        node = queueFunc.front(q);
    }
    while(!queueFunc.isEmpty(q)){
        if(queueFunc.pop(q)){
            queueFunc.destroy(&q);
            return FALSE;
        }
    }
    return TRUE;
}

elemtype input(){
    elemtype t;
    scanf("%d", &t);
    return t;
}
void output(elemtype *t){
    printf("%d", *t);
}

int main(){
    //1 2 3 4 0 0 5 0 0 6 0 0 7 8 0 0 9 0 0
    /*
                1
               /  \
              2    7
             / \  / \
            3   68   9
           / \
          4   5
    */
    // --DLR--
    // 1 2 3 4 5 6 7 8 9
    // --LDR--
    // 4 3 5 2 6 1 8 7 9 
    // --LRD--
    // 4 5 3 6 2 8 9 7 1

    //1 2 3 7 0 0 8 0 0 0 4 5 0 0 6 0 0
    /*
                1
               / \
              2   4
             /   / \
            3   5   6
           / \
          7   8
    */
    // --DLR--
    // 1 2 3 7 8 4 5 6 
    // --LDR--
    // 7 3 8 2 1 5 4 6   
    // --LRD--
    // 7 8 3 2 5 6 4 1 

    //1 2 4 7 0 0 8 0 0 3 0 0 3 5 9 0 0 3 0 0 6 1 0 0 2 0 0
    /*
                  1
               /     \
              2       3
            /  \    /   \
           4    3   5    6
          / \      / \  / \
         7   8    9  3  1 2
    */
    // --DLR--
    // 1 2 4 7 8 3 3 5 9 3 6 1 2 
    // --LDR--
    // 7 4 8 2 3 1 9 5 3 3 1 6 2 
    // --LRD--
    // 7 8 4 3 2 9 3 5 1 2 6 3 1

    elemtype DLR[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, LDR[] = {4, 3, 5, 2, 6, 1, 8, 7, 9};
    BTNode *root = buildTree_fromDLRandLDR_2(DLR, LDR, 0, 8, 0, 8);
    // BTNode *root = buildBinaryTree_fromInput(input);
    prettyPrint(root, output);
    // printf("isCompleteTree:%d\n", isCompleteTree(root));
    // Traversal_template(root, output, 1);
    // printf("\n");
    // Traversal_template(root, output, 2);
    // printf("\n");
    // Traversal_template(root, output, 3);
    // printf("\n");
    // preorderTraversal_method2(root, output);
    // printf("\n");
    // printf("%d\n", getNodeNumInKthFloor_recursion(root, 5));
    return 0;
}

