#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
* 换算关系
* 250px = 1m
* 设定
* 小球为钢铁材质
* 直径    8厘米
* 密度    7850 kg/m3
* 体积    0.0002680
* 质量    2.1038
*
* 地面的静摩擦系数  0.3
* 摩擦力产生的加速度 2.94 m/s2 = 735 px/s2
*
* 空气阻力      F = 0.00097440 * V2  风阻系数取 0.3
*/

const int FRAME_RATE = 120;         // 帧率：120帧  帧率过低时碰撞会穿透地面
const int BALL_SIZE = 20;           // 球的直径：20px

// 400 对应 112 重力
// 3000 对应 2450 重力
const int X_SPEED = 1500;           // 左右键给球的加速度
const int Y_SPEED = 3000;           // 上下键给球的加速度

const int FRICTION = 735;           // 摩擦力大小
const int FRICTION_SENSITIVITY = 2;         // 摩擦力敏感度，当速度的值大于此值时，小球受摩擦力

// 112 对应1.75 米的人
// 2450 对应 8cm 的实心球
const int GRAVITY = 2450;           // 重力大小
const double M = 2.1038;            // 小球质量

enum Directions{xAxis, yAxis};      // x, y轴方向
enum Force{User, Gravity, Friction, AirResistance};         // 力的四个维度，用户给出的力，重力，摩擦力，空气阻力

#endif // CONSTANTS_H
