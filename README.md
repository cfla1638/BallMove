# BallMove

**简介**：参考《Qt学习之路2》完成的一个小项目。

**功能**：实现了实心球的运动。

考虑的因素有：

1. 用户给予的加速度
2. 重力
3. 摩擦力
4. 空气阻力

**细节：**

该项目模拟了一个半径0.04米的实心钢铁球，其密度为 7850 kg / m^3^ 。

重力加速度为 9.8 m/s^2^ 。 

静摩擦系数为 0.3。

空气阻力使用公式：F = 1/2 * CρSv^2^ ，其中C取0.3，ρ取1.293，S取 3.14 * 0.04^2^ 。

尺寸换算：1m = 250px。



项目使用QGraphicsScene + QGraphicsItem + QGraphicsView 完成。

**编译**:

cd /目录

qmake -project

make



Detail： https://cfla1638.github.io/2022/08/21/BallMove-%E5%9F%BA%E4%BA%8EQt%E7%9A%84GUI%E5%B0%8F%E9%A1%B9%E7%9B%AE/ 