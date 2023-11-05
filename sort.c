#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int elemtype;

int _compare(elemtype *a, elemtype *b){
    return *(int*)a - *(int*)b;
}

void insert_sort(elemtype *begin, elemtype *end, int step, int(*compare)(elemtype*, elemtype*)){
    elemtype t = 0, *j = NULL;
    for(elemtype *i = begin; i != end; ++i){
        t = *i;
        for(j = i - step; j >= begin && compare(&t, j) < 0; *(j + step) = *j, j -= step);
        *(j + step) = t;
    }
}

// O(n^1.25)
void shell_sort(elemtype *begin, elemtype *end, int(*compare)(elemtype*, elemtype*)){
    int step = (begin - end) / 2;
    // TODO
}

void quicksort(elemtype *begin, elemtype *end, int(*compare)(elemtype*, elemtype*)){
    if(begin > end)return;
    elemtype pivot = *begin, *left = begin, *right = end, tmp = 0;
    while(left <= right){
        while(compare(left, &pivot) < 0) left++;
        while(compare(right, &pivot) > 0) right--;
        if(left <= right){
            tmp = *left;
            *left = *right;
            *right = tmp;
            left++;
            right--;
        }
    }
    quicksort(begin, right, compare);
    quicksort(left, end, compare);
}


// bug
void quicksort2(elemtype arr[], int low, int high){
    if(low >= high) return;
    elemtype pivot = arr[low];
    int left = low, right = high;
    while(left < right){
        while(left < right && arr[left] <= pivot) ++left;
        arr[right] = arr[left];
        while(left < right && arr[right] >= pivot) --right;
        arr[left] = arr[right]; 
    }
    arr[left] = pivot;
    for(int i = 0; i < 10; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    quicksort2(arr, low, right);
    quicksort2(arr, left, high);
}

void HeapAdjust(int arr[], int begin, int end){
    int current = begin, child = begin * 2 + 1;
    while(current <= child){

    }
}

void HeapSort(int arr[], int begin, int end){

}

// void Merge(int arr[], int )

void merge_sort(int arr[], int begin, int end){

}

int main(){
    elemtype arr[10] = {6, 2, 4, 1, 6, 9, 5, 8, 3 ,7};
    for(int i = 0; i < 10; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    // insert_sort(arr, arr + 10, 1, _compare);
    quicksort2(arr, 0, 9);
    for(int i = 0; i < 10; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    // int n, arr[100000 + 10];
    // scanf("%d", &n);
    // for(int i = 0; i < n; ++i){
    //     scanf("%d", &arr[i]);
    // }
    // quicksort(arr, arr + n - 1, _compare);
    // for(int i = 0; i < n; ++i){
    //     printf("%d ", arr[i]);
    // }
}