/*

    Auther: JiangYilun
    Created date: 2022/03/02
    Last update: 2022/03/29
    Description: Sequence list written in C language.
        Subscript starts at 0.
        The default initialization is 4 size, unless an array of a specific size is passed in or the user set the specified size.
        When the capacity required for inserting data is larger than the current capacity, realloc() will be used to double the capacity.

    Members:
        char this[0];       //pointer to itself
        elemtype* data;     //a pointer to a space where data is stored
        size_t size;        //used size
        size_t capacity;    //the space occupied by the data domain

    Functions: All functions are integrated into the structure named SqFunc.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 4
#define SUCCESS 0
#define ERROR -1
#define NOEXIST -2
#define OVERFLOW -3
#define MEM_ERR -4
typedef int status;

typedef int elemtype;

typedef struct SequenceList {
    // char this[0];       //pointer to itself
    elemtype *data;
    size_t size;        //used size
    size_t capacity;    //capacity of occupied memory space
}SqList;

status _InitList(SqList *L);
status _CreateList(SqList *L, size_t n);
status _CreateList_withArray(SqList *L, elemtype *arr, size_t length);
status _ListInsertBefore(SqList *L, int position, elemtype *e);
int _LocateElem(SqList *L, elemtype *e);
status _DeleteElem_byPos(SqList *L, int position, elemtype *e);
status _DeleteElem_byValue(SqList *L, elemtype *e);
status _isEmpty(SqList *L);
int _length(SqList *L);
int _getCapacity(SqList *L);
status _destroyList(SqList *L);
status _clearList(SqList *L);
status _delete_duplicate_data(SqList *L);
status _delete_zero_element(SqList *L);
status _bubble_sort(SqList *L, int(*compare)(elemtype, elemtype));
status _insertion_sort(SqList *L, int(*compare)(elemtype, elemtype));
status _selection_sort(SqList *L, int(*compare)(elemtype, elemtype));
int _pattern_matching_BF(SqList *L, SqList *sub);

void printList(SqList* L);

// all function to operate the sequence list
struct SequenceListFunctions{
    status (*InitList)(struct SequenceList*);
    status (*CreateList)(struct SequenceList*, size_t);
    status (*CreateList_withArray)(struct SequenceList*, elemtype*, size_t);
    status (*ListInsertBefore)(struct SequenceList*, int, elemtype*);
    int (*LocateElem)(struct SequenceList*, elemtype*);
    status (*DeleteElem_byPos)(struct SequenceList*, int, elemtype*);
    status (*DeleteElem_byValue)(struct SequenceList*, elemtype*);
    status (*isEmpty)(struct SequenceList*);
    int (*length)(struct SequenceList*);
    int (*getCapacity)(struct SequenceList*);
    status (*destroyList)(struct SequenceList*);
    status (*clearList)(struct SequenceList*);
    status (*delete_duplicate_data)(SqList *);
    status (*delete_zero_element)(SqList *);
    status (*bubble_sort)(SqList *, int(*)(elemtype, elemtype));
    status (*insertion_sort)(SqList *, int(*)(elemtype, elemtype));
    status (*selection_sort)(SqList *, int(*)(elemtype, elemtype));
    int (*pattern_matching_BF)(SqList *, SqList *);
}SqFunc = {
    _InitList, _CreateList, _CreateList_withArray,
    _ListInsertBefore, _LocateElem, _DeleteElem_byPos, _DeleteElem_byValue,
    _isEmpty, _length, _getCapacity, 
    _destroyList, _clearList,
    _delete_duplicate_data, _delete_zero_element,
    _bubble_sort, _insertion_sort, _selection_sort,
    _pattern_matching_BF
};

status _InitList(SqList* L) {
    L->data = (elemtype*)malloc(sizeof(elemtype) * DEFAULT_CAPACITY);
    if (L->data == NULL) exit(MEM_ERR);
    L->size = 0;
    L->capacity = DEFAULT_CAPACITY;
    return SUCCESS;
}

status _CreateList(SqList* L, size_t n) {
    if(n < 0)return OVERFLOW;// size_t type can only be non-negative, so this line of judgement is unnecessary.
    L->capacity = n > DEFAULT_CAPACITY ? n : DEFAULT_CAPACITY;
    elemtype* tmp = (elemtype*)realloc(L->data, sizeof(elemtype) * L->capacity);
    if (!tmp) exit(MEM_ERR);
    L->data = tmp;
    return SUCCESS;
}

status _CreateList_withArray(SqList* L, elemtype* arr, size_t length) {
    if(length < 0)return OVERFLOW;// size_t type can only be non-negative, so this line of judgement is unnecessary.
    size_t max_size = length > DEFAULT_CAPACITY ? length : DEFAULT_CAPACITY;
    L->capacity = max_size;
    L->size = length;
    elemtype* tmp = (elemtype*)realloc(L->data, sizeof(elemtype) * L->capacity);
    if (!tmp) exit(MEM_ERR);
    L->data = tmp;

    for (size_t i = 0; i < length; ++i) {
        L->data[i] = arr[i];
    }
    return SUCCESS;
}

status _ListInsertBefore(SqList* L, int position, elemtype* e) {
    if (position < 0 || (position >= L->size && L->size != 0)) return OVERFLOW;
    if (L->size + 1 > L->capacity) {
        L->capacity *= 2;
        elemtype* tmp = (elemtype*)realloc(L->data, sizeof(elemtype) * L->capacity);
        if (!tmp) exit(MEM_ERR);
        L->data = tmp;
    }

    for (int i = L->size - 1; i > position; --i) {
        L->data[i] = L->data[i - 1];
    }
    L->data[position] = *e;
    ++L->size;
    return SUCCESS;
}

int _LocateElem(SqList* L, elemtype* e) {
    for (int i = 0; i < L->size; ++i) {
        if (L->data[i] == *e)return i;
    }
    return NOEXIST;
}

status _DeleteElem_byPos(SqList* L, int position, elemtype* e) {
    if (position < 0 || position >= L->size)return OVERFLOW;

    *e = L->data[position];
    for (int i = position; i < L->size - 1; ++i) {
        L->data[i] = L->data[i + 1];
    }

    --L->size;
    if (L->size <= L->capacity / 2 && L->capacity / 2 > DEFAULT_CAPACITY) {
        L->capacity /= 2;
        elemtype* tmp = (elemtype*)realloc(L->data, sizeof(elemtype) * L->capacity);
        if (!tmp) exit(MEM_ERR);
        L->data = tmp;
    }

    return SUCCESS;
}

status _DeleteElem_byValue(SqList* L, elemtype* e) {
    int isExist = 0;
    for (int i = 0; i < L->size; ++i) {
        if (L->data[i] == *e) {
            isExist = 1;
            for (int j = i; j < L->size - 1; ++j) {
                L->data[j] = L->data[j + 1];
            }
            break;
        }
    }

    if (!isExist) return NOEXIST;

    --L->size;
    if (L->size <= L->capacity / 2) {
        L->capacity /= 2;
        elemtype* tmp = (elemtype*)realloc(L->data, sizeof(elemtype) * L->capacity);
        if (!tmp) exit(MEM_ERR);
        L->data = tmp;
    }

    return SUCCESS;
}

status _isEmpty(SqList* L) {
    return L->size == 0;
}

int _length(SqList* L) {
    return L->size;
}

int _getCapacity(SqList* L) {
    return L->capacity;
}

status _destroyList(SqList* L) {
    free(L->data);
    L->size = 0;
    L->capacity = DEFAULT_CAPACITY;
    elemtype* tmp = (elemtype*)malloc(sizeof(elemtype) * L->capacity);
    if (!tmp) exit(MEM_ERR);
    L->data = tmp;
    return SUCCESS;
}

status _clearList(SqList* L) {
    for (int i = 0; i < L->size; ++i) {
        L->data[i] = 0;
    }
    return SUCCESS;
}

status _delete_duplicate_data(SqList *L){
    int j = 0, cnt = 0;
    for(int i = 0; i < L->size; ++i){
        elemtype value = L->data[i];
        for(j = j + 1;j < L->size && L->data[j] == L->data[i]; ++j)++cnt;
        L->data[i + 1] = L->data[j];
    }
    L->size -= cnt;

    if (L->size <= L->capacity / 2) {
        L->capacity /= 2;
        elemtype* tmp = (elemtype*)realloc(L->data, sizeof(elemtype) * L->capacity);
        if (!tmp) exit(MEM_ERR);
        L->data = tmp;
    }

    return SUCCESS;
}

status _delete_zero_element(SqList *L){
    int j = 0, cnt = 0;
    for(int i = 0; i < L->size; ++i){
        elemtype value = L->data[i];
        for(j = j + 1;j < L->size && L->data[j] == 0; ++j)++cnt;
        L->data[i + 1] = L->data[j];
    }
    L->size -= cnt;

    if (L->size <= L->capacity / 2) {
        L->capacity /= 2;
        elemtype* tmp = (elemtype*)realloc(L->data, sizeof(elemtype) * L->capacity);
        if (!tmp) exit(MEM_ERR);
        L->data = tmp;
    }

    elemtype _ = 0;
    _DeleteElem_byValue(L, &_);
    return SUCCESS;
}

status _bubble_sort(SqList *L, int(*compare)(elemtype, elemtype)){
    for(int i = 0; i < L->size - 1; ++i){
        int isSwapped = 0;
        for(int j = 0; j < L->size - 1 - i; ++j){
            if(compare(L->data[j], L->data[j+1]) > 0){
                elemtype tmp = L->data[j];
                L->data[j] = L->data[j+1];
                L->data[j+1] = tmp;
                isSwapped = 1;
            }
        }
        if(isSwapped == 0)break;
    }
    return SUCCESS;
}

status _insertion_sort(SqList *L, int(*compare)(elemtype, elemtype)){
    for(int i = 0; i < L->size; ++i){
        int j = i - 1;
        elemtype value = L->data[i];
        for(; j >= 0 && compare(value, L->data[j]) < 0; --j){
            L->data[j+1] = L->data[j];
        }
        L->data[j+1] = value;
    }
    return SUCCESS;
}

status _selection_sort(SqList *L, int(*compare)(elemtype, elemtype)){
    for(int i = 0; i < L->size - 1; ++i){
        int min = i;
        for(int j = i + 1; j < L->size; ++j){
            if(compare(L->data[j], L->data[min]) < 0)min = j;
        }
        if(min != i){
            elemtype tmp = L->data[i];
            L->data[i] = L->data[min];
            L->data[min] = tmp;
        }
    }
    return SUCCESS;
}

int _pattern_matching_BF(SqList *L, SqList *sub){
    int i = 0, j = 0;
    while(i < L->size && j < sub->size){
        if(L->data[i] == sub->data[j]){
            ++j;++i;
        }
        else{
            i = i - j + 1;
            j = 0;
        }
    }
    return j >= sub->size ? (i - j) : NOEXIST; 
}

void printList(SqList* L){
    printf("------------\n");
    for(int i = 0; i < L->size; ++i){
        printf("%d ", L->data[i]);
    }
    printf("\n------------\n");
}

int cmp(int a, int b){
    return a - b;
}

int main() {
    SqList test1, test2;
    SqFunc.InitList(&test1);SqFunc.InitList(&test2);

    elemtype a[20] = {0,0,0,1,1,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0};
    elemtype b[5] = {0,0,0,0,1};
    SqFunc.CreateList_withArray(&test1, a, 20);
    SqFunc.CreateList_withArray(&test2, b, 5);

    printf("%d\n", SqFunc.pattern_matching_BF(&test1, &test2));

    return 0;
}