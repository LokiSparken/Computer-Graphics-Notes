> # [Hero AI – Gameplay Abilities Meet Behavior Trees](https://www.bilibili.com/video/BV12E41147eb)

* 每个命令一棵单独行为树 -> 降低复杂度，便于在迭代时不影响其它命令
* Gameplay Tags：蓝图化的 C++ 枚举整型
* Plugin - Gameplay Ability
* open source: git @DaedalicEntertainment ue4-orders-abilities

## 单个执行命令
* 命令执行步骤
  * （外部判断角色状态决定是否执行命令？）
  * set blackboard values：如把需要移动的 destination location 设置到 blackboard 中供 behavior tree 获取
  * assign & start behavior tree
  * 执行 tasks
* 命令要素

    要素 | 描述
    :---|:---
    Order Preview | 如技能范围预览
    Target Type | 如对攻击命令，其对象为可攻击物体；移动命令为需要移动到的 Location
    Group Execution Type | 可执行该命令的对象
    Order Process Policy | 处理策略，是否可以取消该命令等
    Source Required Tags | 对可执行该命令对象的标签筛选
    Target Required Tags | 对目标物体的标签筛选
    Get Required Range | 
    Get Target Score | 
    Is Auto Order | 
    Are Auto Orders Allowed | 
    Issue Order | 
    Order Canceled | 
