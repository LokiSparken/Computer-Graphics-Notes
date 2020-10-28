# 五花畅 背包教程
* https://www.bilibili.com/video/BV1kK411P7CT

## 创建背包组件
* 创建 Content/InventorySystem
* 创建结构体 Structure - S_Item 存放物品属性
  * FName ItemName;
  * bool CanStacking;
  * int ItemNumber;
  * `Text Discription;`
  * `Texture 2D Icon;`
  * `StaticMesh Mesh;`  丢到场景中后的模型
* 创建组件 `Actor Component - InventoryComponent`
  * int InventorySize;  // 背包最大容量
  * S_Item ItemList[];  // 物品列表
  * S_Item EmptyItem;
* 初始化背包
  * 用 EmptyItem 把 ItemList 循环初始化填满
* 背包添加物品 AddItem(S_Item objective)
  * 检查是否可堆叠 CanStacking ，遍历背包中已有物品查看是否已存在，存在叠上去
  * 查是否有空格子
* 背包删除物品 RemoveItem
  * 自己想逻辑
* 背包物品丢到世界中 ThrowItem
* 背包物品交换格子 SwapItem
* `应用背包组件`
  * Character add InventoryComponent
  * 使用时 `GetOwner`，为适应非人形体类型，cast to pawn，如仓库
  * 31：50

## 完善背包组件，创建主 UI

## 创建背包 UI

## 背包拖拽功能

