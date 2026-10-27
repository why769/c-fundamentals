/*
 * struct/frame_size.c — 2026-10-27 练习A（课程155-158集配套）
 * 手算格子图（模数=最大成员=uint16_t=2）：
 *   字节号: 0  1  2  3  4  5  6  7  8  9  10 11 12 13
 *          [head ][id][len][data ............][crc][PAD]
 *   偏移: head=0 id=2 len=3 data=4 crc=12；raw=13 -> 补到2的倍数 -> sizeof=14
 *   pack(1): 无填充 -> sizeof=13；偏移不变（本结构内部无填充，pack只砍尾部PAD）
 * 三问：
 *  ① 为什么默认对齐？性能：对齐访问单总线周期完成，非对齐可能拆两次访问；
 *     硬件：部分ARM核/外设/DMA要求对齐，非对齐直接fault或静默错数据。
 *  ② 协议包为什么pack(1)？上线字节流必须与内存布局逐字节一致：默认填充字节值
 *     不确定（栈垃圾上线圈），且两端编译器/pack设置不同则填充不同->解帧错位；
 *     pack(1)使布局唯一确定。
 *  ③ pack代价？成员可能落歪地址：x86变慢（拆两次总线周期），某些ARM核直接fault；
 *     纪律：只pack要上线的协议结构体，其余保持默认对齐。
 */
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint16_t head;   /* 帧头 0xAA55 */
    uint8_t  id;
    uint8_t  len;
    uint8_t  data[8];
    uint8_t  crc;
} frame_t;

#pragma pack(push, 1)     /* push：把当前设置存档；1：新模数=1 */
typedef struct
{
    uint16_t head;
    uint8_t  id;
    uint8_t  len;
    uint8_t  data[8];
    uint8_t  crc;
} frame_packed_t;         /* 闭合+起名；pop在闭合之后 */
#pragma pack(pop)         /* pop：恢复存档，不污染别的代码 */

int main(void)
{
    printf("%zu\n", sizeof(frame_t));
    printf("head;%zu\n", offsetof(frame_t, head));
    printf("id;%zu\n", offsetof(frame_t, id));
    printf("len;%zu\n", offsetof(frame_t, len));
    printf("data;%zu\n", offsetof(frame_t, data));
    printf("crc;%zu\n", offsetof(frame_t, crc));

    printf("pack %zu\n", sizeof(frame_packed_t));
    printf("pack head;%zu\n", offsetof(frame_packed_t, head));
    printf("pack id;%zu\n", offsetof(frame_packed_t, id));
    printf("pack len;%zu\n", offsetof(frame_packed_t, len));
    printf("pack data;%zu\n", offsetof(frame_packed_t, data));
    printf("pack crc;%zu\n", offsetof(frame_packed_t, crc));
    return 0;
}
