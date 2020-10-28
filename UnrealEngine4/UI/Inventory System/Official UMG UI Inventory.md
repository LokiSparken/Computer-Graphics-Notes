# UMG UI Inventory
* https://www.bilibili.com/video/BV1ft41147AA

## 02
* 使用 FirstPerson 项目模板
* 截取一些缩略图用来当背包中的小图标
  * 本教程项目的大小最好是 32x32
  * 缩略图放到 `Content/Textures`
* 创建 Content/UMG - Widget Blueprint - GameHUD 主游戏 HUD、InventorySlot 个人背包
* 为人物创建变量
  * float HealthValue, EnergyValue, MoodValue;
* FirstPersonHUD
  * 用于绘制十字准线
  * 创建变量 bool ShowCrosshairs;
  * p2 12:26

## 03 Intro to UMG & Player condition setup

## 04 Inventory Menu Layout
* 打开 InventorySlot - Designer
* 删除 `Canvas（绝对布局） - child of another widget blueprint`
* 添加 `Button` 到 InventorySlot，添加 Image 到 Button
  * Image
    * Horizontal/Vertical Alignment 占满
    * Brush - Image 应用图片或绑定到函数
* `Image - Brush - Image Bind 函数 - GetInventoryImage`
  * 添加变量 `Texture 2D` PickupImage;
  * Get PickupImage -> **`Make Brush from Texture`** -> Return Value
* Button - details
  * Style - Normal - Tint - 背包格默认颜色
  * Style - Hovered - Tint - 背包格鼠标悬停颜色
  * Behavior - 取消 Is Enabled，创建 Bind 函数 InventoryCheck()：Get Pickup Image -> Is Valid -> Return Value
* Event Graph - 选中 Button - Events - On Clicked 创建事件
  * P4 11:04

## 05 

## 06

## 07

## 08
