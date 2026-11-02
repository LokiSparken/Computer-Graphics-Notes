主 windows 系统，给移动硬盘装 ubuntu 系统后的引导处理

U盘启动盘，往移动硬盘装好 ubuntu 后，不重启，在启动器里装 boot-repair，将 grub 引导修复到 ubuntu 安装过程中设置的 efi 分区。然后重启拔掉U盘启动盘，不拔移动硬盘，通过硬盘的引导回 windows 系统，用 desk genius 把 windows EFI 下的 ubuntu 引导删掉（左侧选中EFI，在右侧浏览文件里面右键删除）。这样不插移动硬盘的时候就正常直接启动 windows，插着的时候就通过 grub 选择双系统。



# References
1. ubuntu 安装过程 https://blog.csdn.net/2301_81212168/article/details/134896613
2. ubuntu 磁盘分区 https://www.bilibili.com/opus/654221624823775232
3. boot-repair https://www.cnblogs.com/litifeng/p/10505031.html#:~:text=3%E3%80%81%E6%89%A7%E8%A1%8C%E4%BB%A5%E4%B8%8B%E5%87%A0%E6%AD%A5%EF%BC%8C%E5%AE%89%E8%A3%85boot-repair%EF%BC%9A%20sudo%20add-apt-repository%20ppa%3Ayannubuntu%2Fboot-%20repair%20sudo%20apt%20-,apt%20-%20get%20install%20-y%20boot-repair%204%E3%80%81%E8%BF%90%E8%A1%8C%EF%BC%9A%20boot-repair
4. 在 DiskGenius 中删除 Ubuntu 引导文件 https://zhuanlan.zhihu.com/p/1892196131485758983


