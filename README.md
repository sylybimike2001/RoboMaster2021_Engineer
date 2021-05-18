# 工程任务

## 1、摄像头分配

### 一号摄像头：１５０度广角摄像头，采集图像大小720,480

说明：

（1）类名：V4L2Capture

（2）传参方式：作为引用传递到对应run函数中

（3）功能：检测高处矿石，划定ROI区域，在区域中检测是否有闪光灯，判定２／４号矿石即将掉落

###　二号摄像头：１２０度广角１０８０Ｐ，６０ＦＰＳ，采集图像大小

说明：

(1)类名：VideoCapture

(2)传参方式:在对应类的init函数中初始化，不参与main函数

(3)功能：检测近处黑色挡板中心点，进行精确对位。小资源岛对位。

### 三、四号摄像头：１２０度广角７２０ｐ，３０ＦＰＳ，采集图像大小

说明：

(1)类名：VideoCapture

(2)传参方式:在对应类的init函数中初始化，不参与main函数

(3)功能：双目观测障碍块中心

## 2、任务（按紧急程度排序）

开局大资源岛功能：

（１）大资源岛闪光灯识别

（２）ＵＩ互通（告诉操作手哪个矿石即将掉落）

（３）返回中心点（高处黄色矿石返回中心点完成）

（４）黑色挡板识别，返回中心点

（５）自动退出对位模式

（６）**收发信息**

小资源岛功能：

（１）自动对位白色矿石(完成，距离：30+-5cm，水平方向视野局限）

（２）**收发信息**

障碍块功能：

（１）识别视觉标签

（２）能看到完整四个角点的时候给操作手信号（ＵＩ互通）

（３）返回中心点

（４）自动退出对位

（５）收发信息


