/*
 * struct/align_quiz.c — 2026-10-28 练习C（对齐预测对账）
 * 手算推导（模数=各自最大成员）：
 *   A {char c; int i; char d;} : c@0, pad1-3, i@4-7, d@8, pad9-11 -> 12
 *   B {char c; char d; int i;} : c@0, d@1, pad2-3, i@4-7          -> 8
 *   C {int i; char c; char d;} : i@0-3, c@4, d@5, pad6-7           -> 8
 *   D {char c; struct A a;}    : 模数=max(1, align(A)=4); c@0, pad1-3, a@4-15 -> 16
 * 面试加分：A/B/C 成员相同顺序不同 -> 12/8/8，成员排序影响sizeof（小成员扎堆省RAM）
 */
#include <stdio.h>
struct A { char c; int i; char d; };
struct B { char c; char d; int i; };
struct C { int i; char c; char d; };
struct D { char c; struct A a; };
int main(void)
{
    printf("A=%zu B=%zu C=%zu D=%zu\n",
        sizeof(struct A), sizeof(struct B), sizeof(struct C), sizeof(struct D));
    return 0;
}
