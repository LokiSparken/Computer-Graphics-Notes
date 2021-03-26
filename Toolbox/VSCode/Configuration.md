一些无关紧要的记录。

# C++ 编译
* MinGW 的 bits/stdc++.h 用不了：检测到 #include 错误。请更新 includePath。
  * 默认优先用 MSVC，WSL g++，所以改 cpp configuration
  * 编译文件处控制窗口 configuration 打开 cpp properties
    * `compilerPath` 改成 MinGW 的
    * `intelliSenseMode` 改成相匹配的模式（C/C++ 插件设置里看所有选项）
* Tips
  * 环境变量不生效重启窗口
