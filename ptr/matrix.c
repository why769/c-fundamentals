/*
 * ptr/matrix.c — 2026-10-26 练习A3（课程116/117节配套）
 * 数组指针收二维数组；两种等价调用姿势。
 * ① arr传参其实就是第一行数组的地址（退化），&arr[0]本义即首行地址：同类型同值，故两种调用都行
 * ② a 与 &a[0] 类型相同：int(*)[4]；真正不同的是 &a：int(*)[3][4]
 * ③ a+1 / &a[0]+1 跨16字节（一行=4个int）；&a+1 跨48字节（整个3x4）
 * 注：类型里的4与循环上界y冗余，真实项目用 #define COL 4 让二者同源
 */
#include <stdio.h>

void print_matrix(int (*arr)[4], int x, int y)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int arr[3][4] = { {1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6} };
    print_matrix(arr, 3, 4);        /* 数组名退化为首行地址 */
    print_matrix(&arr[0], 3, 4);    /* 本义即首行地址，与上行等价 */
    return 0;
}
