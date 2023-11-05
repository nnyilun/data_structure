#include <stdio.h>
#include <stdlib.h>

/*

哈希函数：

    直接定值法：以key的某个线性函数为哈希地址 Hash(key) = a * key + b

    除留余数法：Hash(key) = key mod p  为质数时冲突较少

    数字分析法

    平方取中法

    折叠法

    随机数法：Hash(key) = random(key)  random为伪随机函数

处理冲突：

    开放寻址法：

        线性探测法：在冲突位置后的空位放入元素 H1 = (Hash(key) + 1) mod p 

        二次探测法：避免堆积。H1 = (Hash(key) +- di) mod m。m为哈希表长度，m要求是某个4k+3的质数。di为q^i

    链地址法：用链表将冲突值串起来，可以插在表头，也可以插在表尾

    再哈希法：再设立一个哈希函数，冲突时使用另一个函数

    公共溢出区法：设置一个公共溢出的区域

*/

int Hash(int n);

int main(){

    return 0;
}