/*

    Auther: JiangYilun
    Created date: 2022/03/30
    Last update: 2022/03/30
    Description: BF & KMP

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BF(char *S, char *T){
    int i = 0, j = 0, str_len = strlen(S), sub_len = strlen(T); 
    while(i < str_len && j < sub_len){
        if(S[i] == T[j]){
            ++i;
            ++j;
        }
        else{
            i -= j - 1;
            j = 0;
        }
    }
    return j >= sub_len ? (i - j) : -1;
}

//KMP
int* get_next(char *T){
    int *next = (int *)malloc(sizeof(int) * strlen(T));
    int i = 0, j = -1;
    next[0] = -1;
    while(i < strlen(T) - 1){
        if(j == -1 || T[i] == T[j]){
            ++i;
            ++j;
            next[i] = j;
        }
        else{   
            j = next[j];
        }
        printf("%d %d\n", i, j);
    }
    return next;
}

//KMP match
int KMP(char *S, char *T){
    int i = 0, j = 0, str_len = strlen(S), sub_len = strlen(T); 
    int *next = get_next(T);
    for(int k = 0; k < sub_len; ++k){
        printf("%d ", next[k]);
    }
    printf("\n");

    while(i < str_len && j < sub_len){
        if(j == -1 || S[i] == T[j]){
            ++i;
            ++j;
        }
        else{
            j = next[j];
        }
        printf("%d %d\n", i, j);
    }
    return j >= sub_len ? (i - j) : -1;
}

int main(){
    char *MainStr = "ababcabababc";
    char *SubStr = "10010010010";
    printf("%d\n", KMP(MainStr, SubStr));

    // printf("pos: %d\n", BF(MainStr, SubStr));

    return 0;
}