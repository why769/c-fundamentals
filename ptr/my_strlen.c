/*
 * ptr/my_strlen.c — 2026-10-26 练习A2（课程115/127节配套）
 * 要求：全程禁下标[]，只用 *s 与 s++；与 string.h 的 strlen 对拍（含空串）。
 * 纪律：纯函数的返回值必须被使用——裸调用 my_strlen(x); 是空转，review必圈。
 */
#include <stdio.h>
#include <string.h>

size_t my_strlen(const char* s)
{
    size_t x = 0;
    while (*s != '\0')
    {
        x++;
        s++;
    }
    return x;
}

int main(void)
{
    const char* t1 = "abcde";
    const char* t2 = "";          /* 空串：期望 0 0 */
    const char* t3 = "embed CAN";
    printf("%zu %zu\n", my_strlen(t1), strlen(t1));
    printf("%zu %zu\n", my_strlen(t2), strlen(t2));
    printf("%zu %zu\n", my_strlen(t3), strlen(t3));
    return 0;
}
