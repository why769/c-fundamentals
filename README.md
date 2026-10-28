# c-fundamentals

面向 MCU 嵌入式岗位的 C 语言练习仓库（北方民族大学 · 电子信息工程 · 2028届）
配套：《嵌入式学习计划_2026-10修订版》阶段0 ｜ 一练习一 commit

## 这是什么

只学嵌入式面试高频的 C 知识点：指针 → 结构体 → 位运算 → 函数指针。
不学文件操作等 MCU 低频内容（取舍理由见计划文档）。

## 目录

| 目录 | 内容 | 状态 |
|---|---|---|
| ptr/ | 指针：swap、遍历、my_strlen/my_strcpy、二级指针 | ✅ swap/my_strlen/matrix；strcpy/反转/qsort 挂即时触发队列 |
| struct/ | 结构体、对齐、pack(1)、组包解包 | ✅ frame_size(满分格子图)/frame_passing(传值vs指针+crc彩蛋)/align_quiz |
| bit/ | 位操作四件套宏、位段提取 | 待开始 |
| fp/ | 函数指针、回调、状态机表 | 待开始 |

## 怎么跑

```bash
gcc ptr/swap.c -o swap && ./swap     # Windows 下用 MinGW 或 VS Code + gcc
```

## 踩坑记录（面试素材库）

### 2026-10-25 STM32 调试链点亮（F407 + ST-Link V2）

**现象链**：设备零枚举 → 描述符请求失败 → 仿真器只枚举hub无子设备 → SWD连接报 `Unable to get core ID`

**排查二分**：
1. 零枚举且无报错设备 = 数据线不通（纯充电线）——换线；
2. `Device Descriptor Request Failed` = 数据线通但握手坏——重插/换口；
3. 普中免驱仿真器 PWR/RUN 亮、CNT 灭，主机侧仅枚举 WCH hub 无功能子设备 = 其内部 USB 功能侧损坏（已走换新）；
4. ST-Link 能读电压(3.17V)但读不到 core ID = SWCLK 没进 MCU——板子 J4 丝印顺序为 `3V3|DIO|GND|CLK`，4P 杜邦头插错孔位使 CLK 悬空；改点对点单线后连通。

**结果**：`Device ID 0x413 / Cortex-M4 / SWD 950kHz`，Flash 读验证向量表完好。

**教训**：
- 先物理层后协议层：线→口→设备→线序，逐层二分；
- 错误码语义是二分锚点："安静的零"≠"描述符失败"≠"有电压无core ID"；
- 灯语即遥测：PWR=供电、CNT=主机通信、RUN=目标链路。

## C阶段毕业（2026-10-28，提前3天）

- 入库练习：ptr/swap、ptr/my_strlen、ptr/matrix、struct/frame_size（对齐格子图手算满分）、struct/frame_passing（传值vs指针+异或校验彩蛋）、struct/align_quiz
- 已看课程：115–127、118–122、155–158
- 毕业理念：C只学到够用；缺口挂"即时触发队列"，在STM32里用到哪个补哪个
- 下一站：10.29 STM32 W1 点灯（主线：普中HAL库版视频+攻略）

## TODO

- [ ] 10.29 W1：CubeMX/普中HAL例程点灯 → 建 project-f407-daq 仓库迁入
- [ ] W2 微课：fp状态机（EXTI事件版）；W3：字符串三件套+预处理；W4：帧组包解包
