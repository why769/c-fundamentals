/*
 * struct/frame_passing.c — 2026-10-28 练习B（课程158集配套）
 * 结构体传参两姿势：要改原对象→传指针；只读→传值(或const指针)。
 */
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint16_t head;
    uint8_t  id;
    uint8_t  len;
    uint8_t  data[8];
    uint8_t  crc;
} frame_t;

/* 问1：fill为什么必须传指针？
   答：它要改调用者的帧；传值只能改副本，出函数改动就丢（my_swap同款道理）。 */
void fill_frame(frame_t* p, uint8_t id, const uint8_t* data, uint8_t len)
{
    p->head = 0xAA55;
    p->id = id;
    if (len > 8)
    {
        len = 8;                 /* 截断防越界 */
    }
    p->len = len;
    for (uint8_t i = 0; i < len; i++)
    {
        p->data[i] = data[i];
    }
    /* crc = id^len^data 异或和（设计选择：head不参与校验，
       将来若要保护head，在此补一行 p->crc ^= ... 即可） */
    p->crc = 0;
    p->crc ^= p->id;
    p->crc ^= p->len;
    for (uint8_t i = 0; i < len; i++)
    {
        p->crc ^= p->data[i];
    }
}

/* 问2：print传值错不错？
   答：不算错——只读场景传值天然保护原对象不被函数改（写 const frame_t f 更佳），
   代价是一次14字节栈拷贝。工程红线：print类函数不许有副作用。 */
void print_frame(frame_t f)      /* 传值：f是副本，点号访问 */
{
    f.id = 99;                   /* 改的是副本 */
    printf("head=%04X id=%u len=%u crc=%u data=", f.head, f.id, f.len, f.crc);
    for (uint8_t i = 0; i < f.len; i++)
        printf("%02X ", f.data[i]);
    printf("\n");
}

int main(void)
{
    frame_t f;
    const uint8_t payload[4] = { 0x11, 0x22, 0x33, 0x44 };
    fill_frame(&f, 7, payload, 4);

    /* 问3：传值拷贝发生在哪、几字节？
       答：print_frame(f) 调用瞬间，整对象 sizeof(frame_t)=14 字节 memcpy 进栈帧；
       所以函数里 f.id=99 只动副本，main 里 f.id 仍是 7。 */
    print_frame(f);                  /* 传对象本身，不传地址 */
    printf("main里,id=%u\n", f.id);  /* 期望7 */
    return 0;
}
