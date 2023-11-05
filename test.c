#include<stdio.h>
#include<stdlib.h>

void Insertsort(int* array, int length) {    //插入排序
	int temp,j;
	
	for (int i = 1; i < length; i++) {
		if (array[i] < array[i - 1]) {
			temp = array[i];
			j = i-1;
			//array[i] = array[i-1];
			while (j >= 1 && temp < array[j]) {
				array[j+1] = array[j];
				j--;
			}
			array[j+1] = temp;
		}
	}
}

int main()
{
	int a[11] = {5,1,5,6,3,1,0,4,8,9,7};
	for(int i = 1; i <= 10; i++)
		printf("%d ", a[i]);
	Insertsort(a, 11);
	printf("\n");
	for(int i = 1; i <= 10; i++)
		printf("%d ", a[i]);
	return 0;
}