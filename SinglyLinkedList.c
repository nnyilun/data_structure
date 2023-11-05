/*

    Auther: JiangYilun
    Created date: 2022/03/16
    Last update: 2022/03/29
    Description: Singly linked with head node written in c language.
        The head node does not store data.
        The subscript of this linked list starts from 0.

    Members:
        elemtype data;      // stored data
        struct SinglyLinkedNode *next;  // a pointer to the next node

    Functions: All functions are integrated into the structure named SLFunc.
    
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR -1
#define NOEXIST -2
#define OVERFLOW -3
#define MEM_ERR -4
typedef int status;

typedef int elemtype;

typedef struct SinglyLinkedNode{
    elemtype data;
    struct SinglyLinkedNode *next;
}SLNode;

status _InitSinglyLinkedList(SLNode **Head);
status _CreateSinglyLinkedList(SLNode *Head, size_t n);
status _CreateSinglyLinkedList_withArray_fromHead(SLNode *Head, elemtype *arr, size_t n);
status _CreateSinglyLinkedList_withArray_fromTail(SLNode *Head, elemtype *arr, size_t n);
status _ListInsertBefore(SLNode *Head, int position, elemtype e);
status _deleteElem_byPos(SLNode *Head, int position);
status _deleteElem_byValue(SLNode *Head, elemtype e);
status _deleteElem_byPoint(SLNode *pNode);
status _LocateElem_byPos(SLNode* Head, int position, elemtype* e);
status _LocateElem_byValue(SLNode* Head, int *position, elemtype e);
status _getElemPoint_byPos(SLNode* Head, int position, SLNode** pNode);
status _getElemPoint_byValue(SLNode* Head, elemtype e, SLNode** pNode);
int _length(SLNode *Head);
int _isEmpty(SLNode *Head);
status _reverseList_method1(SLNode *Head);
status _reverseList_method2(SLNode *Head);
status _reverseList_recursion(SLNode *Head);
status _DestroyList(SLNode *Head);
status _ClearList(SLNode *Head);
status _find_intersection_node_method1(SLNode *Head1, SLNode *Head2, SLNode **point);
status _find_intersection_node_method2(SLNode *Head1, SLNode *Head2, SLNode **point);
status _find_intersection_node_method3(SLNode *Head1, SLNode *Head2, SLNode **point);
status _find_circle_node(SLNode *Head, SLNode **point);
status _delete_duplicate_data_method1(SLNode *Head);
status _delete_duplicate_data_method2(SLNode *Head);
status _delete_zero_element(SLNode *Head);
void _swap_node(SLNode **front, SLNode **pre, SLNode **back);
status _bubble_sort(SLNode *Head, int(*compare)(elemtype, elemtype));
status _insertion_sort(SLNode *Head, int(*compare)(elemtype, elemtype));
status _find_midpoint(SLNode *Head, SLNode **mid);
status _find_point_from_buttom(SLNode *Head, int pos, SLNode **found_point);
status _delete_point_from_buttom(SLNode *Head, int pos);
status _delete_duplicate_data_without_reserve(SLNode *Head);
status _merge_ascending_to_ascending(SLNode *Head1, SLNode *Head2, SLNode *result);
status _merge_ascending_to_descending(SLNode *Head1, SLNode *Head2, SLNode *result);
status _Josephus_problem_lossy(SLNode *Head, int n);
status _Josephus_problem_nolossy_method1(SLNode *Head, int n, SLNode **result);
status _Josephus_problem_nolossy_method2(SLNode *Head, int n, SLNode **result);
status _isSymmetrical(SLNode *Head);

void printList(SLNode *Head);

struct SinglyLinkedListFunctions{
    status (*InitList)(SLNode**);
    status (*CreateList)(SLNode*, size_t);
    status (*CreateList_withArray_fromHead)(SLNode*, elemtype*, size_t);
    status (*CreateList_withArray_fromTail)(SLNode*, elemtype*, size_t);
    status (*ListInsertBefore)(SLNode*, int, elemtype);
    status (*deleteElem_byPos)(SLNode*, int);
    status (*deleteElem_byValue)(SLNode*, elemtype);
    status (*deleteElem_byPoint)(SLNode*);
    status (*LocateElem_byPos)(SLNode*, int, elemtype*);
    status (*LocateElem_byValue)(SLNode*, int*, elemtype);
    status (*getElemPoint_byPos)(SLNode*, int, SLNode**);
    status (*getElemPoint_byValue)(SLNode*, elemtype, SLNode**);
    int (*length)(SLNode*);
    int (*isEmpty)(SLNode*);
    status (*reverse_method1)(SLNode*);
    status (*reverse_method2)(SLNode*);
    status (*reverse_recursion)(SLNode*);
    status (*DestroyList)(SLNode*);
    status (*ClearList)(SLNode*);
    status (*find_intersection_node_method1)(SLNode*, SLNode*, SLNode**);
    status (*find_intersection_node_method2)(SLNode*, SLNode*, SLNode**);
    status (*find_intersection_node_method3)(SLNode*, SLNode*, SLNode**);
    status (*find_circle_node)(SLNode*, SLNode**);
    status (*delete_duplicate_data_method1)(SLNode *);
    status (*delete_duplicate_data_method2)(SLNode *);
    status (*delete_zero_element)(SLNode *);
    status (*bubble_sort)(SLNode *, int(*compare)(elemtype, elemtype));
    status (*insertion_sort)(SLNode *, int(*compare)(elemtype, elemtype));
    status (*find_midpoint)(SLNode *, SLNode **);
    status (*find_point_from_buttom)(SLNode *, int, SLNode**);
    status (*delete_point_from_buttom)(SLNode *, int);
    status (*delete_duplicate_data_without_reserve)(SLNode *);
    status (*merge_ascending_to_ascending)(SLNode *, SLNode *, SLNode *);
    status (*merge_ascending_to_descending)(SLNode *, SLNode *, SLNode *);
    status (*Josephus_problem_lossy)(SLNode *, int);
    status (*Josephus_problem_nolossy_method1)(SLNode *, int, SLNode **);
    status (*Josephus_problem_nolossy_method2)(SLNode *, int, SLNode **);
    status (*isSymmetrical)(SLNode *);
}SLFunc = {
    _InitSinglyLinkedList, _CreateSinglyLinkedList, 
    _CreateSinglyLinkedList_withArray_fromHead, _CreateSinglyLinkedList_withArray_fromTail,
    _ListInsertBefore, _deleteElem_byPos, _deleteElem_byValue, _deleteElem_byPoint,
    _LocateElem_byPos, _LocateElem_byValue,
    _getElemPoint_byPos, _getElemPoint_byValue,
    _length, _isEmpty,
    _reverseList_method1, _reverseList_method2, _reverseList_recursion,
    _DestroyList, _ClearList,
    _find_intersection_node_method1, _find_intersection_node_method2, _find_intersection_node_method3,
    _find_circle_node, _delete_duplicate_data_method1, _delete_duplicate_data_method2,
    _delete_zero_element,
    _bubble_sort, _insertion_sort,
    _find_midpoint,
    _find_point_from_buttom, _delete_point_from_buttom,
    _delete_duplicate_data_without_reserve,
    _merge_ascending_to_ascending, _merge_ascending_to_descending,
    _Josephus_problem_lossy, _Josephus_problem_nolossy_method1, _Josephus_problem_nolossy_method2,
    _isSymmetrical
};

status _InitSinglyLinkedList(SLNode **Head){
    SLNode *tmp = (SLNode*)malloc(sizeof(SLNode));
    if(!tmp) exit(MEM_ERR);

    *Head = tmp;
    tmp->data = 0;
    tmp->next = NULL;
    return SUCCESS;
}

status _CreateSinglyLinkedList(SLNode *Head, size_t n){
    SLNode *p = Head;
    for(int i = 0; i < n; ++i){
        SLNode *tmp = (SLNode*)malloc(sizeof(SLNode));
        if(!tmp) exit(MEM_ERR);
        p->next = tmp;
        tmp->data = 0;
        p = tmp;
    }
    p->next = NULL;
    return SUCCESS;
}

status _CreateSinglyLinkedList_withArray_fromHead(SLNode *Head, elemtype *arr, size_t n){
    for(int i = 0; i < n; ++i){
        SLNode *tmp = (SLNode*)malloc(sizeof(SLNode));
        if(!tmp) exit(MEM_ERR);
        tmp->next = Head->next;
        tmp->data = arr[i];
        Head->next = tmp;
    }
    return SUCCESS;
}

status _CreateSinglyLinkedList_withArray_fromTail(SLNode *Head, elemtype *arr, size_t n){
    SLNode *p = Head;
    while(p->next) p = p->next;
    for(int i = 0; i < n; ++i){
        SLNode *tmp = (SLNode*)malloc(sizeof(SLNode));
        if(!tmp) exit(MEM_ERR);
        p->next = tmp;
        tmp->data = arr[i];
        p = tmp;
    }
    p->next = NULL;
    return SUCCESS;
}

status _ListInsertBefore(SLNode *Head, int position, elemtype e){
    if(position < 0)return OVERFLOW;
    int cnt = 0;
    SLNode *p = Head->next;
    while(p && cnt < position - 1){
        ++cnt;
        p = p->next;
    }

    if(!p || cnt > position - 1)return NOEXIST;

    SLNode *tmp = (SLNode*)malloc(sizeof(SLNode));
    tmp->data = e;
    tmp->next = p->next;
    p->next = tmp;
    return SUCCESS;
}

status _deleteElem_byPos(SLNode *Head, int position){
    if(position < 0)return OVERFLOW;
    int cnt = 0;
    SLNode *p = Head->next;
    while(p->next && cnt < position - 1){
        ++cnt;
        p = p->next;
    }

    if(!p->next || cnt > position - 1)return NOEXIST;

    SLNode *tmp = p->next;
    p->next = p->next->next;
    free(tmp);
    return SUCCESS;
}

status _deleteElem_byValue(SLNode *Head, elemtype e){
    SLNode *p = Head;
    while(p->next && p->next->data != e){
        p = p->next;
    }

    if(!p->next) return NOEXIST;

    SLNode *tmp = p->next;
    p->next = p->next->next;
    free(tmp);
    return SUCCESS;
}

status _deleteElem_byPoint(SLNode *pNode){
    if(!pNode) return NOEXIST;

    pNode->data = pNode->next->data;
    SLNode *tmp = pNode->next;
    pNode->next = pNode->next->next;
    free(tmp);
    return SUCCESS;
}

status _LocateElem_byPos(SLNode* Head, int position, elemtype* e){
    if(position < 0)return OVERFLOW;
    int cnt = 0;
    SLNode *p = Head->next;
    while(p && cnt < position){
        ++cnt;
        p = p->next;
    }
    
    if(!p || cnt > position)return NOEXIST;

    *e = p->data;
    return SUCCESS;
}

status _LocateElem_byValue(SLNode* Head, int *position, elemtype e){
    int cnt = 0;
    SLNode *p = Head->next;
    while(p && p->data != e){
        ++cnt;
        p = p->next;
    }

    if(!p) return NOEXIST;
    
    *position = cnt;
    return SUCCESS;
}

status _getElemPoint_byPos(SLNode* Head, int position, SLNode** pNode){
    if(position < 0)return OVERFLOW;
    int cnt = 0;
    SLNode *p = Head->next;
    while(p && cnt < position){
        ++cnt;
        p = p->next;
    }

    if(!p || cnt > position)return NOEXIST;

    *pNode = p;
    return NOEXIST;
}

status _getElemPoint_byValue(SLNode* Head, elemtype e, SLNode** pNode){
    SLNode *p = Head->next;
    while(p && p->data != e){
        p = p->next;
    }

    if(!p) return NOEXIST;

    *pNode = p;
    return SUCCESS;
}

int _length(SLNode *Head){
    int cnt = 0;
    SLNode *p = Head->next;
    while(p){
        ++cnt;
        p = p->next;
    }
    return cnt;
}

int _isEmpty(SLNode *Head){
    return Head->next == NULL;
}

status _reverseList_method1(SLNode *Head){
    // insert the node from the head
    SLNode *p = Head->next, *q = p->next;
    while(q){
        p->next = q->next;
        q->next = Head->next;
        Head->next = q;
        q = p->next;
    }
    return SUCCESS;
}

status _reverseList_method2(SLNode *Head){
    // reverse each node of the single-linked list one by one, 
    // and then point the head node to the original tail.
    if(!Head || !Head->next || !Head->next->next)return SUCCESS;
    SLNode *p = NULL, *q = Head->next, *r = NULL;
    while(q){
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }
    Head->next = p;
    return SUCCESS;
}

status _reverseList_recursion(SLNode *Head){
    // reverse the list recursively
    if(!Head->next || !Head->next->next) return SUCCESS;

    SLNode *p = Head->next, *q = p->next;
    p->next = NULL;
    Head->next = q;
    _reverseList_recursion(Head);
    q->next = p;
}

status _DestroyList(SLNode *Head){
    SLNode *tmp = Head->next;
    while(tmp){
        SLNode *_ = tmp;
        tmp = tmp->next;
        free(_);
    }
    Head->next = NULL;
    return SUCCESS;
}

status _ClearList(SLNode *Head){
    SLNode *tmp = Head->next;
    while(tmp){
        tmp->data = 0;
        tmp = tmp->next;
    }
    return SUCCESS;
}

status _find_intersection_node_method1(SLNode *Head1, SLNode *Head2, SLNode **point){
    int cnt1 = 0, cnt2 = 0;
    SLNode *p1 = Head1->next, *p2 = Head2->next;
    while(p1 || p2){
        if(p1){
            p1 = p1->next;
            ++cnt1;
        }
        if(p2){
            p2 = p2->next;
            ++cnt2;
        }
    }
    p1 = Head1->next;
    p2 = Head2->next;
    if(cnt1 > cnt2){
        for(int i = 0; i < cnt1 - cnt2; ++i, p1 = p1->next);
    }
    else if(cnt2 > cnt1){
        for(int i = 0; i < cnt2 - cnt1; ++i, p2 = p2->next);
    }
    while(p1 && p2){
        if(p1 == p2){
            *point = p1;
            return SUCCESS;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    *point = NULL;
    return NOEXIST;
}

status _find_intersection_node_method2(SLNode *Head1, SLNode *Head2, SLNode **point){
    int flag = 0;
    SLNode *p1 = Head1, *p2 = Head2;
    while(p1 && p2){
        p1 = p1->next;
        p2 = p2->next;
        if(flag == 0){
            if(!p1){
                p1 = Head2;
                flag = 1;
            }
            else if(!p2){
                p2 = Head1;
                flag = 2;
            }
        }
    }
    if(flag == 1){
        p2 = Head1;
    }
    else if(flag == 2){
        p1 = Head2;
    }
    while(p1 && p2){
        if(p1 == p2){
            *point = p1;
            return SUCCESS;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    *point = NULL;
    return NOEXIST;
}

status _find_intersection_node_method3(SLNode *Head1, SLNode *Head2, SLNode **point){
    if(!Head1)return NOEXIST;
    SLNode *p = Head2->next;
    while(p){
        if(Head1 == p){
            *point = Head1;
            return SUCCESS;
        }
        p = p->next;
    }
    _find_intersection_node_method3(Head1->next, Head2, point);
}

status _find_circle_node(SLNode *Head, SLNode **point){
    if(!Head || !Head->next || !Head->next->next){
        *point = NULL;
        return NOEXIST;
    }
    SLNode *p = Head->next, *q = p;
    while(p && q){
        p = p->next;
        q = q->next->next;
        if(!p || !q){
            *point = NULL;
            return NOEXIST;
        }
        if(p == q)break;
    }
    p = Head->next;
    while(p && q){
        if(p == q){
            *point = q;
            return SUCCESS;
        }
        p = p->next;
        q = q->next;
    }
}

status _delete_duplicate_data_method1(SLNode *Head){
    SLNode *p = Head->next;
    while(p && p->next){
        if(p->data == p->next->data){
            SLNode *tmp = p->next;
            p->next = p->next->next;
            free(tmp);
            continue;
        }
        p = p->next;
    }
    return SUCCESS;
}

status _delete_duplicate_data_method2(SLNode *Head){
    // Try recursion, but can't handle 0 at the head node
    status _delete_duplicate_data_method2_subFunc(SLNode *f);
    return _delete_duplicate_data_method2_subFunc(Head->next);
}

status _delete_duplicate_data_method2_subFunc(SLNode *f){
    if(!f)return SUCCESS;
    SLNode *p = f;
    if (f->next != NULL)
    {
        if (f->data == f->next->data)
        { 
            SLNode *tmp = f->next;
            f->next = f->next->next;
            free(tmp);
            _delete_duplicate_data_method2_subFunc(f);
        }
        else 
        {
            _delete_duplicate_data_method2_subFunc(f->next);
        }
    }
}

status _delete_zero_element(SLNode *Head){
    SLNode *p = Head, *q = Head->next;
    while(q){
        if(q->data == 0){
            p->next = q->next;
            free(q);
            q = p->next;
        }
        else{
            p = q;
            q = q->next;
        }
    }
    return SUCCESS;
}

void _swap_node(SLNode **front, SLNode **pre, SLNode **back){
    // Only adjacent elements can be swapped
    (*pre)->next  = (*back)->next;
    (*back)->next = *pre;
    (*front)->next = *back;
}

status _bubble_sort(SLNode *Head, int(*compare)(elemtype, elemtype)){
    int len = _length(Head);
    for(int i = 0; i < len - 1; ++i){
        int isSwaped = 0;
        SLNode *p = Head, *q = p->next, *r = q->next;
        for(int j = 0; j < len - i - 1; ++j){
            if(compare(q->data, r->data) > 0){
                _swap_node(&p, &q, &r);
                isSwaped = 1;
            }
            p = p->next;
            q = p->next;
            r = q->next;
        }
        if(isSwaped == 0) break;
    }
    return SUCCESS;
}

status _insertion_sort(SLNode *Head, int(*compare)(elemtype, elemtype)){
    if(!Head || !Head->next) return SUCCESS;
    SLNode *p = Head->next->next;
    Head->next->next = NULL;
    while(p){
        SLNode *pre = Head, *q = p->next;
        while(pre->next && compare(p->data, pre->next->data) > 0) pre = pre->next;
        p->next = pre->next;
        pre->next = p;
        p = q;
    }
    return SUCCESS;
}

status _find_midpoint(SLNode *Head, SLNode **mid){
    if(!Head || !Head->next){
        *mid = Head->next;
        return SUCCESS;
    }

    SLNode *fast = Head->next, *slow = Head->next;
    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    *mid = slow;
    return SUCCESS;
}

status _find_point_from_buttom(SLNode *Head, int pos, SLNode **found_point){
    int cnt = 0;
    SLNode *fast = Head->next, *slow = fast;
    while(fast->next && cnt < pos){
        fast = fast->next;
        ++cnt;
    }
    if(!fast->next && cnt < pos){
        *found_point = NULL;
        return NOEXIST;
    }
    while(fast->next){
        fast = fast->next;
        slow = slow->next;
    }
    *found_point = slow;
    return SUCCESS;
}

status _delete_point_from_buttom(SLNode *Head, int pos){
    int cnt = 0;
    SLNode *fast = Head->next, *slow = fast;
    while(fast->next && cnt < pos + 1){
        fast = fast->next;
        ++cnt;
    }
    if(!fast->next && cnt < pos + 1){
        return NOEXIST;
    }
    while(fast->next){
        fast = fast->next;
        slow = slow->next;
    }
    SLNode *tmp = slow->next;
    slow->next = tmp->next;
    free(tmp);
    return SUCCESS;
}

status _delete_duplicate_data_without_reserve(SLNode *Head){
    if(!Head->next || !Head->next->next)return SUCCESS;
    SLNode *p = Head, *q = Head->next;
    elemtype preValue = q->data;
    while(p->next && q->next){
        if(q->next->data != preValue){
            preValue = q->next->data;
            p = p->next;
            q = p->next;
        }
        else{
            do{
                p->next = q->next;
                free(q);
                q = p->next;
            }while(q && q->data == preValue);
            if(q) preValue = q->data;
        } 
    }
    return SUCCESS;
}

status _merge_ascending_to_ascending(SLNode *Head1, SLNode *Head2, SLNode *result){
    SLNode *p1 = Head1->next, *p2 = Head2->next;
    SLNode *newHead = result;
    while(p1 && p2){
        if(p1->data <= p2->data){
            newHead->next = p1;
            p1 = p1->next;
        }
        else{
            newHead->next = p2;
            p2 = p2->next;
        }
        newHead = newHead->next;
    }
    if(!p1){
        newHead->next = p2;
    }
    else{
        newHead->next = p1;
    }
    Head1->next = NULL;
    Head2->next = NULL;
    return SUCCESS;
}

status _merge_ascending_to_descending(SLNode *Head1, SLNode *Head2, SLNode *result){
    SLNode *p1 = Head1->next, *p2 = Head2->next, *tmp = NULL;
    while(p1 && p2){
        if(p1->data <= p2->data){
            tmp = p1->next;
            p1->next = result->next;
            result->next = p1;
            p1 = tmp;
        }
        else{
            tmp = p2->next;
            p2->next = result->next;
            result->next = p2;
            p2 = tmp;
        }
    }
    while(p1){
        tmp = p1->next;
        p1->next = result->next;
        result->next = p1;
        p1 = tmp;
    }
    while(p2){
        tmp = p2->next;
        p2->next = result->next;
        result->next = p2;
        p2 = tmp;
    }
    Head1->next = NULL;
    Head2->next = NULL;
    return SUCCESS;
}

status _Josephus_problem_lossy(SLNode *Head, int n){
    if (!Head || !Head->next) return SUCCESS;
    SLNode* p = Head->next;

    while (p->next) {
        p = p->next;
    }
    p->next = Head->next;
    Head->next = p;

    while (Head->next != Head->next->next) {
        for (int i = 1; i < n; ++i) {
            Head->next = Head->next->next;
        }
        SLNode* tmp = Head->next->next;
        Head->next->next = tmp->next;
        free(tmp);
    }
    
    Head->next->next = NULL;
    return SUCCESS;
}

status _Josephus_problem_nolossy_method1(SLNode *Head, int n, SLNode **result){
    if (!Head || !Head->next) return SUCCESS;
    SLNode *p = Head->next, *tail = NULL;

    int sum = 0;
    while (p->next) {
        p = p->next;
        ++sum;
    }
    ++sum;
    p->next = Head->next;
    tail = p;

    p = Head->next;
    int _ = 0;
    while (sum > 1) {
        if(*((int*)p + 1) == 0){
            ++_;
            if(_ == n){
                *((int*)p + 1) = 1;
                --sum;
                _ = 0;
            }
        }
        p = p->next;
    }

    tail->next = NULL;
    p = Head->next;
    while(p){
        if(*((int*)p + 1)) *((int*)p + 1) = 0;
        else *result = p;
        p = p->next;
    }

    return SUCCESS;
}

status _Josephus_problem_nolossy_method2(SLNode *Head, int n, SLNode **result){
    if (!Head || !Head->next) return SUCCESS;
    
    int cnt = _length(Head), p = 0;
    for(int i = 2; i <= cnt; ++i){
        p = (p + n) % i;
    }
    SLNode *pre = Head->next;
    while(p > 0){
        pre = pre->next;
        --p;
    }
    *result = pre;
    return SUCCESS;
}

status _isSymmetrical(SLNode *Head){
    SLNode *mid = NULL, *fast = Head, *slow = Head;
    if(!Head || !Head->next) return SUCCESS;

    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    mid = slow;

    _reverseList_method1(mid);
    
    int flag = FALSE;
    SLNode *p = mid->next, *q = Head->next;
    while(p){
        if(p->data != q->data){
            flag = FALSE;
            break;
        }
        else{
            flag = TRUE;
        }
        p = p->next;
        q = q->next;
    }

    _reverseList_method1(mid);
    return flag;
}

void printList(SLNode *Head){
    printf("------------\n");
    SLNode *tmp = Head->next;
    while(tmp){
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n------------\n");
}

int cmp(elemtype a, elemtype b){
    return a - b ;
}

int main(){
    int a[8] = {1,2,3,2,2,3,2,1};
    SLNode *head1;
    SLFunc.InitList(&head1);
    SLFunc.CreateList_withArray_fromTail(head1, a, 8);
    printList(head1);
    printf("%d\n", SLFunc.isSymmetrical(head1));
    printList(head1);
    return 0;
}