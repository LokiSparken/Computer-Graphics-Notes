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
  * `GetController -> Cast to PlayerController`
* 创建丢出时 Spawn 的物体类 - Actor
  * StaticMesh Component;
  * 构造函数中 Set Static Mesh 为物品属性结构体 S_Item 的 StaticMesh Mesh
  * 选个默认 Mesh 勾选 `simulate physics`
  * Collision Presets 可自定义
    * `WorldStatic` 防止穿地表模 Block
    * WorldDynamic 物体间是否能碰撞 Block 撞
    * Pawn 物体和角色是否能碰撞

## 创建主 UI
* 创建 WBP_Main，设点 Text 在屏幕中心
* Create、Add to viewport，设置传入 ItemInfo 
  * 有名字时显示，否则不显示：对 Text 绑定时分支设 Return Value
* 添加按键拾取、丢弃

## 创建背包 UI
* 创建 WBP_ItemSlot
  * 设计窗口右上角尺寸用 Custom 自定义
  * 添加 Canvas Panel - Overlay
    * 添加 Canvas Panel - Overlay - Image，大小 (60, 60)
    * 添加 Canvas Panel - Overlay - Text 
  * 添加 Canvas Panel - Border 用 actionbar_frame_numbers_T2 图标并调 Color and Opacity, 大小 (100, 100)
  * Event Graph
    * 新建 S_Item Iteminfo;
* 创建 WBP_Bag
  * 添加 `Wrap Box` 整个背包 UI 板块，Text 放背包名
  * Event Graph - `Get Owning Player（客户端获取控制器，GetPlayerPawn 仅单机有效） -> GetControlledPawn -> GetComponentsByClass(InventoryComponent)[0]`
  * Event Graph - `UpdateItemList() - Wrap Box -> Clear Children -> for -> Create WBP_ItemSlot Widget -> WarpBox.AddChild`
* InventoryComponent
  * SetInventoryUIVisibility() 控制背包 UI 可见性
  * 获取角色输入，更改 bool InventoryVisible;
  * 控制 UI 的显示与隐藏 `Set Visibility(Hiden)`
  * 控制鼠标的显示与隐藏 `Set show mouse cursor`
  * 设置玩家输入类型 `Set Input Mode Game Only/Game and UI(aim UI)`

## 背包拖拽功能

