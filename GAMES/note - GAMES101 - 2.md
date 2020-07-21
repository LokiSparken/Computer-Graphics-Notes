
# Lecture 19 Cameras, Lenses and Light Fields
* 图形学的两种合成（synthesis）成像方式：光栅化、光线追踪。
* 捕捉（capture）成像方式：把物理世界中存在的东西变成图像（相机拍照片）。
* Image = synthesis + capture
* 目前成像技术的研究
  * 在微小时间内能看到的光的传播，研究光在空间中传播的过程：`Transient Imaging`
  * `Imaging` 本身在计算摄影学 Computational Photography 中研究得更多。
## 相机 Cameras
### **小孔成像**
* 原因：光沿直线传播，假设小孔在物体中心，物体上部的光向下通过小孔，下部的光向上通过小孔，因此在成像平面中产生倒影。
* 针孔摄像机 Pinhole camera
### 快门 shutter：控制光能否进入相机内，且在多少时间内可以进入。
### 传感器 sensor：其上一点记录 irradiance 。
* 所以它不能过滤特定方向上的光，也就没办法直接用传感器来拍摄。（不过现在有巨巨正在研究，说不定以后就可以了（
### 针孔相机成像过程 Pinhole Image Formation
* 用针孔相机原理做光线追踪，没有景深、虚化的效果。
### **视场 Field Of View (FOV)**：相机能看到的视野范围
* $\Join$ 相似三角形：高度 h 、到对顶点焦距 f 、对顶点角度 FOV
  $$ FOV = 2\ arctan\ (\frac{h}{2f}) $$
* 不同的视场决定了不同的视野，和传感器大小、焦距都有关。
* 通常以 $35mm-format\ film（36\times24mm）$ 的传感器大小作为基准，再取各种长短的焦距，来定义相机的视野大小。
  * 如 $17mm$ ，同传感器大小标准下，焦距短，FOV大（104°），因此是广角镜头。
  * $50mm$ 普通，47°。
  * $200mm$ telephoto lens 长焦/远摄镜头，12°。
  * 对于手机而言，一般 $28mm$ 焦距，但手机中实际传感器大小很小，只是给出了等效到 $35mm$ 标准的焦距以供参考。
### **曝光 Exposure（H）**
$$ Exposure = Time \times Irradiance $$
$$ H = T + E $$
* $Time（T）：$即 Exposure Time，由快门 shutter 控制。
* $Irradiance（E）：$传感器上单位面积接收到的光的能量，由透镜光圈大小 lens aperture 和焦距 focal lenth 决定。
* 因此相机与渲染不同，关注的不是单位时间的能量，而是曝光时间中所接收到的所有能量总和。
* Exposure controls in photography
  * Aperture size：光圈是仿生设计，类似人的瞳孔。在相机中光圈大小可以通过 f-stop 控制，最大与镜头大小相同。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img83.png) &nbsp;</br>
  如图以 F 数控制。  
  F-number（F-stop），记作FN或F/N。非正式理解：光圈直径的逆（倒数）。
  * Shutter speed：快门开放的时间长短。快门速度越快，曝光时间越短。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img84.png) &nbsp;</br>
  如第一张图，千分之一秒。  
  快门首先起到调节曝光度的作用。另外，由于快门的开启和关闭必然有一过程，其会造成`运动模糊Motion Blur`。即快门开启过程中，物体运动了一段距离，传感器取均值后产生的模糊效果。  
  运动模糊能给人眼体现速度，用于呈现更逼真的视觉效果。还可以起到一定反走样的效果。  
  当物体的运动速度和快门速度接近时，产生 `Rolling Shutter` 问题，结果图像上物体扭曲，因为物体不同时间处于不同位置并分别被记录下来。
  * ISO gain（感光度）：在这里可以暂时简单地认为，对接收到的光能量以某比例放大。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img85.png) &nbsp;</br>
  比如将一幅很暗的图乘上ISO值，提升曝光度，使其变亮。在这过程中，不仅光能量信号被放大了，其中影响噪声的量也被放大了。所以通常不应调整该值。
  * 综合：增大几倍F数，即光圈直径减小，就可以相应增大几倍快门暴露时间提高曝光度，但形成的结果不是完全相同，因为两者分别会影响景深DOF和运动模糊。  
* 应用
  * 高速摄影：用很短的快门时间，很大的光圈拍。如子弹穿物。
  * 延迟摄影（拉丝）：用很小的光圈，很长的快门时间。如拍远处的飞机起飞或着陆。

## 透镜 Lenses
* 科普时间
  * 现在的相机一般都是用多层透镜组构成。
  * 实际的透镜可能一面凸一面平，无法把光聚集到一点。
* CG中研究的透镜：理想薄透镜Ideal Thin Lens，不考虑透镜厚度。
  * 平行光射入，产生焦点。
  * 同理，经过焦点的光必被透镜散射成平行光形成图像。
  * CG中的假设：薄的棱镜可以任意改变焦距。（现在的相机中通过不同透镜的组合来做到这一点。）
### **透镜相关物理规律**
* 平行光聚到焦点，过焦点的光变成平行光出射。
* 对称性：穿过透镜中心的光不发生改变。
* The Thin Lens Equation 
  * 定义物距 $z_o$ 、像距 $z_i$ 、焦距 $f$。
  * 则有
  $$ \frac{1}{f} = \frac{1}{z_i} + \frac{1}{z_o} $$
  * 推导过程（高斯透镜理论）
  </br>&nbsp;![](note%20-%20image/GAMES101/img86.png) &nbsp;</br>
  ① 列出两对相似三角形的相似比
  $$     \left\{
    \begin{aligned}
        \frac{h_o}{z_o-f} = \frac{h_i}{f} \\
      \frac{h_o}{f} = \frac{h_i}{z_i-f}
    \end{aligned}
    \right. $$
  ② 变换易得
  $$ \frac{h_o}{h_i} = \frac{z_o-f}{f} = \frac{f}{z_i-f} $$
  ③ 展开消去即可得等式。（该等式也称为 Gauss Thin Lens Equation）
### **Defocus Blur**
* Circle of Confusion（CoC，弥散圆）
  </br>&nbsp;![](note%20-%20image/GAMES101/img87.png) &nbsp;</br>
  * 物体在实际成像面（感光面）上投影出的圆形范围
  * 这个范围中得到的内容不止有通过透镜而来的光，还有在同侧前方的光，也投影到相应位置。
  * CoC的计算：同样使用相似三角形
  $$ \frac{C}{A} = \frac{d'}{z_i} = \frac{|z_s-z_i|}{z_i} $$
* 光圈越大，期望效果越模糊。
* F-Number 正式定义
  * The f-number of a lens is defined as the focal length divided by the diameter of the aperture. 即 
    $$FN = \frac{f}{d_{lens}}$$
* 因此计算CoC时的光圈大小 $A$ 可用 $\frac{f}{N}$ 来计算。
### **光线追踪景深效果的一种设定方案**
![](note%20-%20image/GAMES101/img88.png)
* 确定成像面大小Sensor、透镜焦距、光圈大小。
* 确定物体面Subject plane离光圈的物距 $z_o$
  * 根据薄透镜公式求出成像面Sensor到光圈的像距 $z_i$
* `渲染过程`
  * $x'$ 为遍历到的成像面上一个像素
  * 由于光线穿过透镜中心不会改变方向，因此将 $x'$ 与透镜中心相连，求出在物体面上的聚焦点 $x'''$，那么从出发像素点 $x'$ 往透镜上任意一点 $x''$ 发射的光线，都会聚焦到 $x'''$处。
  * 因此要渲染的像素 radiance 就是各个 $x''$ 到 $x'''$ 方向的光线作出的贡献。
### **景深Depth of Filed**
* 光圈大小会使部分画面内容模糊，但在focal plane上总是清晰的。因此光圈大小其实是影响模糊的范围。
* 景深：场景中一定深度范围的内容，在成像面附近形成一段区域，这块区域的 CoC 认为足够小，可以不被人眼察觉它是模糊的。即场景中成像清晰的一段范围。
* 用景深的最近、最远处，分别发射光线穿过透镜的上下边缘作计算。（ppt p61）

## 光场 Light Field / Lumigraph（in Lecture 20）
### **全光函数 The plenoptic function**
* 用全光函数描述人眼看到的所有内容（各个方向的光）
* 人在一场景中往各方向看，由球极坐标可表示任意方向。定义往任意方向看到的结果为函数
  $$ P(\theta, \phi) $$
* 引入影响光线颜色的波长
  $$ P(\theta, \phi, \lambda) $$
* 再引入各方向上不同时刻的状态
  $$ P(\theta, \phi, \lambda, t) $$
  * 男神：这就是电影！
* 设人的位置也可以任意移动
  $$ P(\theta, \phi, \lambda, t, V_X, V_Y, V_Z) $$
  * 男神：这就是全息！
* 总结：在任意位置，任意时刻，往任意方向观察到的不同颜色。可以用这七个维度衡量视觉世界。
* 从全光函数中提取部分信息来表示更复杂的光，光场就是全光函数的一部分。

### **光场 Light Field**
* 光线的定义
  * 给出起点 $(V_X, V_Y, V_Z)$ 、方向 $(\theta, \phi)$
  * 两点一线（视作二维位置），知道大致走向（正负，二维走向）
* 物体表面的定义
  * 把物体视作在包围盒中，那么人眼看到的某点光状态，就是该点往人眼方向发射的光的状态
* 光场：记录物体表面的`任意位置`往`任意方向`发射的光的强度。
  * 二维位置：三维物体的表面展开是在二维空间中的，类似纹理映射
  * 二维方向：$\theta、\phi$
  * 在任意视点，往任意方向观察物体，都可以从已记录的四维光场信息中提取相应的结果。
  * 由于`将光场信息记录在物体外的某包围盒上`，使用时不涉及对物体本身的几何等特性考虑，简化了问题。
  * 限制：视点应在包围盒外。
* 信息记录（`光场的参数化`）
  * 用一个表面上的点及方向来确定参数
  * 定义两个平行平面，分别取两个面上的点 $(u, v)、(s, t)$ 来确定一个方向。因此记录信息时只要`组合遍历两个面上所有点`即可！
* 设面 $(u, v)$ ，面 $(s, t)$ 为近场景面
  * 定 $(u, v)$ 看向 $\forall (s, t)$ ：即针孔成像。将每个 $(u, v)$ 往任意 $(s, t)$ 的观察结果综合到一起即光场。
    * Stanford camera array SIGGRAPH2012 相机矩阵的钞能力
    * 事后可以任意对焦
  * 反之：可以理解为将成像结果中一个像素的 Irradiance 分解为了各个方向上的 Radiance [Lecture 20 - 29:50]
    * 把各方向的光通过微小的透镜改变方向（像素用透镜替换），将不同方向的光分解到微透镜后的不同区域 [参考苍蝇复眼]

### **光场照相机 Light Field Camera**
* The Lytro Light Field Camera
  * Ren Ng 
  * 微透镜原理
  * 支持后期重新聚焦
* 光场照相机
  * 像素用微透镜替换，感光元件后移
  * 把各方向照射到原像素位置的光再分解到各个方向，感光元件记录下一块区域的信息
* 光场照片还原
  * 直接取每块区域的底部边缘一条光线方向的结果，也可取中心、取顶部边缘
  * 通过取的光线方向不同，可以达到虚拟移动相机的目的，实现重新变焦
  * 实际上重新变焦只要在记录的光场信息中按照计算结果查询所需的光线，各区域可以是不同的位置
* 总结：光场照相机记录了当时进入相机的所有信息，包括位置和方向，所以可以通过这些信息重新变焦。
* 缺陷
  * 因为用了一坨像素区域来记录原来只需要一个像素的信息，所以对分辨率要求高了，成本高
  * 微透镜只是简化模型，实际工艺要求很高
  * 提升分辨率，会丢失更多的位置信息，所以又是一个 trade off （from 弹幕：现代取舍入门

# Lecture 20 Color and Perception
## **Physical Basis of Color**
* 不同波长的光有不同的折射率。
* 图形学关注可见光光谱范围：400nm~700nm
* 谱功率密度 Spectral Power Distribution （SPD）
  * 光线在不同波长的强度分布
  * 线性可加

## **Perception - Biological Basis of Color**
* 颜色是人的感知，不是物理上的光的属性。
* 视网膜上的感光细胞 Retinal Photoreceptor Cells
  * 包含感知`光线强度`的`视杆细胞`（Rod cells），可得灰度图
  * `视锥细胞`（Cone cells）较少，感知`颜色`
* 视锥细胞内部又分为 `S`、`M`、`L` 细胞  
  
  ![](note%20-%20image/GAMES101/img89.png)
  * `S` 对短波、高频光敏感，`L` 对长波、低频光敏感
  * 不同的人三种细胞分布差异很大

### 三色视觉理论 Tristimulus theory of color
* 对人眼，给定 SPD $S(\lambda)$ ，有  
  $$S = \int_\lambda s(\lambda)r_S(\lambda) d\lambda$$  
  $$M = \int_\lambda s(\lambda)r_M(\lambda) d\lambda$$
  $$L = \int_\lambda s(\lambda)r_L(\lambda) d\lambda$$ 
  * 将光在不同波长上的分布 $S(\lambda)$ 及三种细胞对不同波长的响应度（敏感度），那么把各个波长的感知结果（即二者之积）积分求和，就是最终结果
  * 同色异谱现象 Metamerism：不同的 SPD 会产生相近或相同的 XYZ ，即同色但光谱能量分布不同的光 metamers 。
### 调色 Color Reproduction / Matching
* 给定某色，用不同的颜色混合得到某色的过程
* 电脑中的 `加色系统 Additive Color`：R+G+B 255 最终变白色（减色系统变黑色）
* ① 从混色往目标色调整 ② 给目标色加上一定色值（相当于减色系统）往混色靠拢
### CIE RGB Color Matching Experiment
* 给出如何通过单色光调出一个颜色
  
  ![](note%20-%20image/GAMES101/img90.png)
  * 给出每种波长结果，分别需要多少单色光进行组合，每一条单色光曲线为光谱匹配曲线
  * 上图结果都是对单个波长，相当于乘以 $1$ 。考虑到实际情况下光在不同波长上的强度 SPD ，为了`匹配任意 SPD 的光`，就再乘上该分布，得到实际需要的各单色光的量，并考虑到各波长上的贡献，积分求和
    $$R_{CIE RGB} = \int_\lambda s(\lambda)r(\lambda) d\lambda$$  
    $$G_{CIE RGB} = \int_\lambda s(\lambda)g(\lambda) d\lambda$$
    $$B_{CIE RGB} = \int_\lambda s(\lambda)b(\lambda) d\lambda$$ 
    * 注意与响应积分的形式略像但含义不同
    * 这就是通常所说的RGB系统
### 颜色空间 Color Spaces
* 标准颜色空间 Standardized Color Spaces（sRGB）
  * 广泛应用在各式成像设备
  * `色域 gamut` 有限
* CIE XYZ系统
  
  ![](note%20-%20image/GAMES101/img91.png)
  * CIE XYZ color matching functions 非实验所得颜色匹配系统，为人造曲线，当然所给出的信息与实验所得的相同
  * 具有很好的理论性质，直观，色域极大
  * 其中 $\overrightarrow{y}$ 覆盖了 400nm~700nm ，分布又比较对称，匹配后的 $Y$ 可一定程度上表示亮度
* 色域 gamut：一个颜色空间所有可能表示的颜色
  * 因为颜色的三个分量要全可视化将呈现到三维空间，不利于观察
  * 因此将根据 CIE XYZ 系统匹配所得的 $X、Y、Z$ 归一化
    $$ x = \frac{X}{X+Y+Z} $$
    $$ y = \frac{Y}{X+Y+Z} $$
    $$ z = \frac{Z}{X+Y+Z} $$
  * 由于 $x+y+z=1$ ，改变其中两个量就能获知第三个量
  * 通常固定亮度 $Y$ ，改变 $x、y$ 的值，获得色域图

    ![](note%20-%20image/GAMES101/img92.png)
    * 中心混合最重处为白色（加色系统），边缘为单色
* 不同的颜色空间表示能力不同
  * sRGB只能表示上图色域范围内的一部分
* HSV Color Space （Hue色调-Saturation饱和度-Value/Lightness亮度，Photoshop）
  * 用作颜色拾取器 color picker
  
  ![](note%20-%20image/GAMES101/img93.png)
  * 色调：不同的颜色
  * 饱和度：更接近白色还是更接近单色
  * 亮度：偏黑还是偏单色
* CIE LAB Space
  * L 轴表示亮度 W-B，a 轴表示 R-G，b轴表示 B-Y
  * 认为任意两个轴的极限两端为互补色（柯南赤壁案！！！）
    * 看某图中心，切全白，可以出互补色图
    * 切灰度图，互补色会给灰度图染色！！！卧槽卧槽姿势++！！！
* **颜色是感知，是相对的，所以感知结果很容易受旁边颜色的影响。**

  ![](note%20-%20image/GAMES101/img94.png)
  ![](note%20-%20image/GAMES101/img95.png)
  ![](note%20-%20image/GAMES101/img96.png)
* CMYK（Cyan品蓝，Magenta品红，Yellow黄色，Key黑色）
  
  ![](note%20-%20image/GAMES101/img97.png)
  * 一种减色系统
  * 多用于打印机，越混越黑
  * 为啥能混黑还要黑：考虑实际应用的成本，黑色用得多，但CMY三色成本比黑的高，用混黑很亏（
## 题外
* High Dynamic Range（HDR，高动态范围图像）
  * 比白色更亮的东西
* Gamma 校正

# Lecture 21 Animation

# Lecture 22 Animation Cont.


# Experiment
## 环境配置
* Windows10 + vscode + wsl(ubuntu 18.04LTS)
* 主机和WSL数据交换
  * `cp -a /mnt/f/balabala /home/balabala`
* opencv在windows下解压再塞进去会报错，保险起见放进去再解压
* 作业压缩包解压出来文件夹带中文会乱码
  * 删除乱码名文件夹
    * `ls -i`获取文件夹数字ID
    * `find . -inum <numid> -exec rm {} -rf \;` 或 `find ./ -inum <numid> -print -exec rm {} -rf \;`
  * 直接Windows摸到`C:\Users\<username>\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu18.04onWindows_79rhkp1fndgsc\LocalState\rootfs\home\balabala`去解压hhhhh然鹅发现WSL里并不改变（……怕了怕了把状态还原回去了
  * Windows下生成的zip文件中编码GBK/GB2312等，在Linux下默认解压用UTF-8所以会乱码。可以`unzip -O CP936 xxx.zip`。但是会生成很XX的文件夹名。
  * ……作业还是在windows里解压好把文件夹拉进去安全
* 编译
  * 在main.cpp目录下
  * `mkdir build`
  * `cd build`
  * `cmake ..`
  * `make`编译
  * `./Transformation`可执行文件名，在CMakeLists.txt中可修改
## HW1
* 框架里main函数里的两个输入给出的zNear, zFar是正，由于看向-z轴所以应该改为负数。
* 绕任意轴旋转敲罗德里格斯的时候注意对偶矩阵
## HW2
* `std::transform(l, r, res, op)`
  * 将`(l, r)`范围内的每个元素作为`op`的第一参数调用`op`，结果存入`res`开头的范围内
  * `op`：函数指针、函数对象或lambda表达式
* MSAA
  * 维护四倍大小的sample_frame_buf和sample_depth_buf
  * 四个采样点采样完根据四个采样色值resolve该像素点的颜色
## HW5
* primary ray生成
  * https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
  * 主要是根据设定的像素平面比例，确定视线看向的点在实际成像面上是什么
    * 遍历像素 `x: [0, width-1], y: [0, height-1]`
    * 取到像素中心 `+0.5`
    * 转化到 `[0, 1]`，分别除以 `width` 和 `height`
    * 考虑视线 `(0, 0)` 看向成像面中心，所以 `*2-1` 转化到 `[-1, 1]`
    * 然后分别 `*scale` 、 `*scale*AspectRatio` 拉伸
  * 注意点
    * 图片原点(0, 0)于左上角，成像空间原点在图片中心，y值取负
* 射线与三角网格相交
  * 虽然学的时候感觉分解成与平面相交，再判交点是否在三角形内感觉很友好
  * 事实证明写代码的时候不用推导，数学就是代码简化之光啊（……

## FAQ
### HW3
* bump mapping 部分的 h(u,v)=texture_color(u,v).norm, 其中 u,v 是 tex_coords, w,h 是 texture 的宽度与高度  
* rasterizer.cpp 中 v = t.toVector4()  
* get_projection_matrix 中的 eye_fov 应该被转化为弧度制  
* bump 与 displacement 中修改后的 normal 仍需要 normalize  
* 可能用到的 eigen 方法：norm(), normalized(), cwiseProduct()  
* 实现 h(u+1/w,v) 的时候要写成 h(u+1.0/w,v)  
* 正规的凹凸纹理应该是只有一维参量的灰度图，而本课程为了框架使用的简便性而使用了一张 RGB 图作为凹凸纹理的贴图，因此需要指定一种规则将彩色投影到灰度，而我只是「恰好」选择了 norm 而已。为了确保你们的结果与我一致，我才要求你们都使用 norm 作为计算方法。
* bump mapping & displacement mapping 的计算的推导日后将会在光线追踪部分详细介绍，目前请按照注释实现。

# More
* B样条 www.bilibili.com/video/av66548502
* GTC GPU Technology Conference Nvidia 
  * DLSS 2.0：无损精度和消耗放大图片 知乎文刀秋二
  * RTXGI 全局光照 https://developer.nvidia.com/rtxgi
* YLQ's way of learning things
  * WHY, WHAT, then HOW
  * 为什么学、这啥玩意、如何运作
* 十个渲染最真实的人物模型
  * https://cgelves.com/10-most-realistic-human-3d-models-that-will-wow-you/
## 相关论文
* 头发材质Kajiya-Kay Model：SIGGRAPH 1989 *Rendering fur with three dimensinal textures.*
* 头发材质Marschner Model：SIGGRAPH 2003 *Light Scattering from Human Hair Fibers.*

</br></br>
> # The End
</br></br>

# 备用

</br>&nbsp;![] &nbsp;</br>

$\leqslant \geqslant \forall$

$$ \mathop{\Join}\limits_{i\ \theta\ j} $$

$$\begin{aligned} L_s &=  \\ &=  \end{aligned}$$


$$
    \left\{
    \begin{aligned}
        x' & = x + t_x \\
        y' & = y + t_y 
    \end{aligned}
    \right.
$$

$$
    
    \left(
    \begin{matrix}
        x' \\
        y'
    \end{matrix}
    \right)
$$

<!-- 图片示例 -->
![][<tag>]
[<tag>]:<BASE64STR>

<!-- 题注 -->
一个题注[1]$^{[1]}$

[1]:cannotaddspace失败的题注示例

* 为了自动生成的目录格式，设置EOL的换行符号改成了\n，原auto
  * 不同系统换行符制定不同

    系统 | 换行符
    :---:|:---:
    Windows|\n\r
    Unix|\n
    Mac|\r

光线与长方体求交
* 考虑三维光线与二维平面矩形求交点  
  设在 $xOy$ 平面上作平面矩形，令其 $z=k$ ， $x \in [x_0, x_1]$ ， $y \in [y_0, y_1]$  
  由光线（空间直线）参数形式可知
  $$ \overrightarrow{P(t)} = \overrightarrow{a} + t\cdot \overrightarrow{b}$$
  拆分到三维
  $$ \left\{\begin{aligned} x_t &=& x_a+t\cdot x_b \\ y_t &=& y_a+t\cdot y_b \\ z_t &=& z_a+t\cdot z_b \end{aligned}\right.$$
  其中已令 $z_t = k$ ，可得参数 $t=\frac{k-z_a}{z_b}$  
  将 $t$ 代入上两式求得 $x_t、y_t$  
  最后检验是否分别在 $[x_0,x_1]、[y_0,y_1]$ 范围内

三角函数积分公式  
∫sin x dx = -cos x + C  
∫ cos x dx = sin x + C  
∫tan x dx = ln |sec x | + C  
∫cot x dx = ln |sin x | + C  
∫sec x dx = ln |sec x + tan x | + C  
∫csc x dx = ln |csc x – cot x | + C  
∫sin ²x dx =1/2x -1/4 sin 2x + C  
∫ cos ²x dx = 1/2+1/4 sin 2x + C  
∫ tan²x dx =tanx -x+ C  
∫ cot ²x dx =-cot x-x+ C  
∫ sec ²x dx =tanx + C  
∫ csc ²x dx =-cot x+ C  
∫arcsin x dx = xarcsin x+√（1-x²）+C  
∫arccosx dx = xarccos x-√（1-x²）+C  
∫arctan x dx = xarctan x-1/2ln（1+x²）+C  
∫arc cot x dx =xarccot x+1/2ln（1+x²）+C  
∫arcsec xdx =xarcsec x-ln│x+√（x²-1）│+C  
∫arccsc x dx =xarccsc x+ln│x+√（x²-1）│+C  