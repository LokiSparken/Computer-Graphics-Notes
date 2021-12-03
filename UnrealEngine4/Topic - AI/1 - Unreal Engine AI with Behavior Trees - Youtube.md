> # [Unreal Engine AI with Behavior Trees](https://www.youtube.com/watch?v=iY1jnFvHgbE&feature=push-sd&attr_tag=r1gz4fVZqk6jt7CQ%3A6)

## 基本概念
* BehaviorTree 的使用：AIController.RunBehaviorTree()
* 结点类型
  * Composites 复合
    * Sequence：顺序执行所有子项，直到某个子项返回 failed，其右侧子项不会再被执行
    * Selector：仅执行第一个 successed 子项（用于决策）
  * Decorators 修饰：即 Conditions 判断条件，控制子树切换
  * Services 服务：按指定 frequency 执行，一般可用于间隔更新 blackboard 值，或判断某情况后更新 blackboard 值等
  * Tasks 任务：具体执行事件。更新 blackboard 值（如位置信息）、`调用角色内封装好的行为`，`最后返回 success/failed`。
* 执行优先级
  * $\downarrow$
  * 同层分支 $\rightarrow$
* Blackboard：只用于存储数据
  * KeyType KeyName KeyValue
  * 应用于 BehaviorTree
* AI Perception Component
  * 听觉/视觉等感官
  * add to AI Controller
* Environment Query System
  * AITask.RunEQS()

## Further References
1. [UE4 行为树详解](https://zhuanlan.zhihu.com/p/143298443) | 知乎 ksun
