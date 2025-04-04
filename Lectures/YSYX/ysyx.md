> # 一生一芯
> 项目主页：https://ysyx.oscc.cc/
> 第六期笔记

目录
<!-- TOC -->

- [> # 一生一芯](#--%E4%B8%80%E7%94%9F%E4%B8%80%E8%8A%AF)
- [预学习阶段](#%E9%A2%84%E5%AD%A6%E4%B9%A0%E9%98%B6%E6%AE%B5)
    - [概览 | 如何科学地提问](#%E6%A6%82%E8%A7%88--%E5%A6%82%E4%BD%95%E7%A7%91%E5%AD%A6%E5%9C%B0%E6%8F%90%E9%97%AE)
        - [从计算机发展史看处理器芯片](#%E4%BB%8E%E8%AE%A1%E7%AE%97%E6%9C%BA%E5%8F%91%E5%B1%95%E5%8F%B2%E7%9C%8B%E5%A4%84%E7%90%86%E5%99%A8%E8%8A%AF%E7%89%87)
        - [一生一芯项目的目的](#%E4%B8%80%E7%94%9F%E4%B8%80%E8%8A%AF%E9%A1%B9%E7%9B%AE%E7%9A%84%E7%9B%AE%E7%9A%84)
    - [Linux系统安装和基本使用](#linux%E7%B3%BB%E7%BB%9F%E5%AE%89%E8%A3%85%E5%92%8C%E5%9F%BA%E6%9C%AC%E4%BD%BF%E7%94%A8)
    - [计算机系统的状态机模型](#%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F%E7%9A%84%E7%8A%B6%E6%80%81%E6%9C%BA%E6%A8%A1%E5%9E%8B)
    - [复习C语言](#%E5%A4%8D%E4%B9%A0c%E8%AF%AD%E8%A8%80)
    - [程序的执行和模拟器](#%E7%A8%8B%E5%BA%8F%E7%9A%84%E6%89%A7%E8%A1%8C%E5%92%8C%E6%A8%A1%E6%8B%9F%E5%99%A8)
    - [搭建verilator仿真环境](#%E6%90%AD%E5%BB%BAverilator%E4%BB%BF%E7%9C%9F%E7%8E%AF%E5%A2%83)
    - [数字电路基础实验](#%E6%95%B0%E5%AD%97%E7%94%B5%E8%B7%AF%E5%9F%BA%E7%A1%80%E5%AE%9E%E9%AA%8C)
    - [完成PA1](#%E5%AE%8C%E6%88%90pa1)
- [基础阶段](#%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5)
    - [支持RV32IM的NEMU](#%E6%94%AF%E6%8C%81rv32im%E7%9A%84nemu)
    - [程序的机器级表示（上）](#%E7%A8%8B%E5%BA%8F%E7%9A%84%E6%9C%BA%E5%99%A8%E7%BA%A7%E8%A1%A8%E7%A4%BA%E4%B8%8A)
    - [程序的机器级表示（下）](#%E7%A8%8B%E5%BA%8F%E7%9A%84%E6%9C%BA%E5%99%A8%E7%BA%A7%E8%A1%A8%E7%A4%BA%E4%B8%8B)
    - [用RTL实现最简单的处理器](#%E7%94%A8rtl%E5%AE%9E%E7%8E%B0%E6%9C%80%E7%AE%80%E5%8D%95%E7%9A%84%E5%A4%84%E7%90%86%E5%99%A8)
    - [AM运行时环境](#am%E8%BF%90%E8%A1%8C%E6%97%B6%E7%8E%AF%E5%A2%83)
    - [工具和基础设施](#%E5%B7%A5%E5%85%B7%E5%92%8C%E5%9F%BA%E7%A1%80%E8%AE%BE%E6%96%BD)
    - [支持RV32E的单周期NPC](#%E6%94%AF%E6%8C%81rv32e%E7%9A%84%E5%8D%95%E5%91%A8%E6%9C%9Fnpc)
    - [ELF文件和链接](#elf%E6%96%87%E4%BB%B6%E5%92%8C%E9%93%BE%E6%8E%A5)
    - [设备和输入输出](#%E8%AE%BE%E5%A4%87%E5%92%8C%E8%BE%93%E5%85%A5%E8%BE%93%E5%87%BA)
    - [调试技巧](#%E8%B0%83%E8%AF%95%E6%8A%80%E5%B7%A7)
    - [异常处理和 RT-Thread](#%E5%BC%82%E5%B8%B8%E5%A4%84%E7%90%86%E5%92%8C-rt-thread)
    - [总线](#%E6%80%BB%E7%BA%BF)
    - [SoC计算机系统（上）](#soc%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F%E4%B8%8A)
    - [SoC计算机系统（下）](#soc%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F%E4%B8%8B)
    - [性能优化和简易缓存](#%E6%80%A7%E8%83%BD%E4%BC%98%E5%8C%96%E5%92%8C%E7%AE%80%E6%98%93%E7%BC%93%E5%AD%98)
    - [流水线处理器](#%E6%B5%81%E6%B0%B4%E7%BA%BF%E5%A4%84%E7%90%86%E5%99%A8)
- [进阶阶段](#%E8%BF%9B%E9%98%B6%E9%98%B6%E6%AE%B5)

<!-- /TOC -->

# 预学习阶段
## 1. 概览 | 如何科学地提问
### 从计算机发展史看处理器芯片
1. 摩尔定律：集成电路上晶体管数目每18-24个月增加一倍（导致年轴上晶体管Transistor数量指数级增长）。但单核性能Single-Thread Performance瓶颈，受频率Frequency（MHz）和功耗Typical Power（Watts）制约。单块芯片上因功耗影响，导致所有晶体管不能全部同时工作。其中关闭的晶体管称为暗硅问题。
2. Intel处理器架构演进过程中的设计问题：
    * 新功能要兼容每一代的旧功能
    * 处理不周全导致安全漏洞问题的案例：2018年“熔断”和“幽灵”
3. *A New Golden Age for Computer Architecture*. David Patterson, John Hennessy.
4. 注意：
   1. 硬件需要软件的支持才能发挥作用。所以处理器芯片设计不止是RTL（Register Tranfer Level）开发，而是计算机系统软硬件协同设计。
   2. 复杂系统都是迭代演进的。处理器由单周期->多周期->流水线->超标量->乱序执行。
      1. 《系统设计黄金法则：简单之美》包云岗
      2. KISS法则：Keep It Simple, Stupid
### 一生一芯项目的目的
1. 电路设计的本质：实例化（晶体管/门电路/模块/部件等）和连线（连接引脚）。但现代大型处理器的复杂性肯定不能用原始方法，需要引进代码模拟（于是有了RTL开发）、项目管理等。
2. 问题：
   1. 上一页的RTL代码用于供CPU访问若干设备寄存器，它有问题吗？（00:50:38）（00:55:00解答）
   2. 如何编写一个打印Hello的C程序放到你的CPU上运行？
   3. 你写的流水线CPU具体在哪些地方比单周期CPU快多少？
   4. CPU仿真过了1e8周期后出错，如何快速调试？
3. 以上问题说明处理器芯片设计包含很多软件问题。处理器芯片离开软件就没用，而且HDL（Hardware Description Language硬件描述语言）和RTL代码虽然描述的是硬件，但在开发过程中还是作为软件看待，项目过程里也需要软件开发相关的技术去管理/维护/测试/评估/优化。
4. 一生一芯项目的目的：
   1. 重新认识芯片设计
      * 如何评价一款处理器芯片？正确性（基本）、对软件的支持度（只能跑排序程序还是能跑一个操作系统）、微结构复杂度（单周期、流水线、cache、分支预测……）、PPA（性能Performance - IPC，主频；功耗Power - 暗硅问题、面积Area - 不能超过流片面积预算）、可配置性、代码可读性/可维护性
      * 如何科学兼顾多个维度，尽可能做好处理器？
   2. 认识软硬件全系统、理解科学的安排规划和优化方法、掌握工具技能解决工程问题
5. 杂谈
   1. 知识局部性：时间局部性（遇到一个知识点时，最近很可能还会遇到它）、空间局部性（学习一个知识点时，也会了解到附近的知识点）
   2. 逆否命题：时间局部性（不了解一个知识点时，说明最近没有学习它）、空间局部性（不了解一个知识点时，说明也没有学习与它相关的内容）
   3. 咱就是说把经验性总结说得一本正经是吧，虽然确实经常有这种体验就是了
   4. 哦，原来是被伸手党折腾的

## 2. Linux系统安装和基本使用

## 3. 计算机系统的状态机模型

## 4. 复习C语言

## 5. 程序的执行和模拟器

## 6. 搭建verilator仿真环境

## 7. 数字电路基础实验

## 8. 完成PA1

# 基础阶段
## 9. 支持RV32IM的NEMU

## 10. 程序的机器级表示（上）

## 11. 程序的机器级表示（下）

## 12. 用RTL实现最简单的处理器

## 13. AM运行时环境

## 14. 工具和基础设施

## 15. 支持RV32E的单周期NPC

## 16. ELF文件和链接

## 17. 设备和输入输出

## 18. 调试技巧

## 19. 异常处理和 RT-Thread

## 20. 总线

## 21. SoC计算机系统（上）

## 22. SoC计算机系统（下）

## 23. 性能优化和简易缓存

## 24. 流水线处理器

# 进阶阶段

