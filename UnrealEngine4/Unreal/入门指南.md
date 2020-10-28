# 给开发者的虚幻引擎入门指南
* 这是入门指南吗？
* 这是劝退指南。
* 这是神技安利合集。:)
* Sjoerd de Jong 好帅！！！

## 课程简介

## 世界构建入门
### 简介与原理
* UE 以关卡为工作流中心
* 
### 图解
### 建议
* 关卡组织
  * World Outliner 管理关键场景资源：EditorBillboardScale 放大图标
  * Groups
  * Layers
  * Selection tools
* Groups
  * Ctrl+G 选中物体成组
  * Ctrl+Shift+G 暂时禁用但保留组
  * Shift+G 取消组
  * 注意：不改变世界大纲 Outliner、物体渲染方式
* Layers
  * Window - Layers 打开标签页（Outliner 旁边）
  * 把物体加入不同的选择集 selection sets，便于同时选中
* Selection tools
  * 善用物体右键 - Select
  * Ctrl+B 到内容浏览器，右键 SM 可 Select 所有匹配的物体
  * Window - `Statistics` 草，又是好东西！
* 平移、旋转、缩放的对齐工具
* Ctrl+拖动物体
  * 【？】直接拖不是也移动吗……06:56 我他妈这也能看不懂的吗？
  * 点选物体时容易误移，可以把平移网格变很大
* Shadows/Collision 不需要时关闭，提升性能
* Landscape
  * LOD Distance 略增加一点，节省性能
  * `Collision Mip Level = 1 生成精度较低碰撞`，对平坦地形节省性能
  * 可选中单个组件进行设定：地形 - Manage
  * `远离地面时去掉平铺痕迹：11:13`
  * `层之间的硬混合：12:04`
* Foliage 植被
  * 关 Shadow 提性能
  * 减小渲染 Range
  * `远离时使植物渐渐沉入地表：15:33`
  * `斜坡上的草`

## 渲染入门

## 动画入门


## 引擎架构入门

## 编程入门

## 蓝图入门

## 角色入门

## 材质入门

