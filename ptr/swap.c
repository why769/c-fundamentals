/*
 * ptr/swap.c — 2026-10-26 练习A1（对应课程115-117/127节期间）
 * 要点：想在函数里改调用者的变量，必须传地址；传值版(bad_swap)交换的是副本，出函数即销毁。
 * 编译：VS工程 或 gcc ptr/swap.c -o swap
 */
#include <stdio.h>

void my_swap(int* x, int* y)
{
    int temp = 0;
    temp = *x;
    *x = *y;
    *y = temp;
}

void bad_swap(int x, int y)   /* 传值版：注定失败 */
{
    int t = x; x = y; y = t;  /* 形参出了函数会销毁，无法传递到主函数 */
}

int main(void)
{
    int a = 0;
    int b = 0;
    if (scanf_s("%d%d", &a, &b) != 2) {   /* 输入返回值必须检查：嵌入式代码纪律 */
        printf("input error\n");
        return 1;
    }
    bad_swap(a, b);
    printf("after bad_swap : %d %d\n", a, b);   /* 期望：不变 */
    my_swap(&a, &b);
    printf("after my_swap  : %d %d\n", a, b);   /* 期望：交换 */
    return 0;
}
