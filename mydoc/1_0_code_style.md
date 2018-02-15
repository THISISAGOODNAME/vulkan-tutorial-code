---
title: 编码规范
last_updated: February 13, 2018
summary: "本教程使用的编码规范"
---

## 引言

&nbsp; &nbsp; &nbsp; &nbsp;编码规范/编码风格在实际开发，特别是团队开发中非常重要，良好且统一的编码风格，可以在review代码时更加高效，实际开发和维护更有效率。如果你是新手，希望能尽快学习某种编码风格，你一定会受益的。

## vulkan

&nbsp; &nbsp; &nbsp; &nbsp;既然是vulkan教程，那么把vulkan API的使用规范提前吧

- 使用C风格的vulkan API
- 结构体使用`Vk`开头，采用驼峰命名法
- 函数使用`vk`开头，采用驼峰命名法
- 常量使用`VK_`开头，全部字母大写，用`_`分隔单词

{{site.data.alerts.note}}vulkan也提供了C++风格的接口(vulkan.hpp)，但是我个人看众多库，没有一个使用vulkan的c++风格接口，为了大众化，我也使用C风格的接口(PS:openGL的C++风格接口也没什么人用，都在用c风格的接口，即便是openGL DSA，真心羡慕C#和webgl，上下文管理更清晰){{site.data.alerts.end}}

## 命名规范

&nbsp; &nbsp; &nbsp; &nbsp;本命名规范大部分来自于[Unreal coding standard](https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/)，但是没有`F`、`A`、`U`那些东西，很多我可能在这个教程中并没有用到(比如枚举和模板)

- 类、结构体、全局函数，使用驼峰命名法，首字母大写
- 结构体变量、函数，使用驼峰命名法，首字母小写
- 类属性，使用驼峰命名法，以`m`开头，比如`mFoo`,`mBar`
- 类方法，使用驼峰命名法，首字母小写
- 常量、宏，全部字母大写，用`_`分隔单词
- 常量优先使用`const`而非宏的方式声明
- 模板，使用驼峰命名法，以`T`开头，比如`TTemplateFoo`
- 枚举值，使用驼峰命名法，以`E`开头，比如`EEnumBar`
- 全局变量，使用驼峰命名法，以`g`开头，比如`gGlobalFoo`
- 布尔型变量，使用驼峰命名法，以`b`开头，比如`bBollBar`
- 指针变量，使用驼峰命名法，以`p`开头，比如`pPtrFoo`

## 代码风格

- 代码块左花括号`{`写在新行，不写在行尾
- 在switch语句中不使用`{}`
- 慎用`auto`关键字
- 循环，优先使用Range Based For
- 为了减少误导，在本教程中，不会使用C++ Lambda表达式
- 优先使用STL而不是自己的算法，少用指针
- 指针置空和比较均使用`nullptr`而非`NULL`
- 使用`std::runtime_error`报错，使用`try catch`处理错误，尽量手工处理错误而不让程序崩溃
- 给容器赋值/取值时，使用`vec.data()`不使用`&vec`
- 枚举必然在`E`开头的命名空间中(Strongly-Typed Enums)
- 自增运算符`++`，只用在循环中做控制流，如果在`while`中，单独一行
- 对循环和函数中不变量使用`const`修饰
- 使用智能指针管理变量

{{site.data.alerts.tip}}给初学者一个建议，根据情况选取最合适的容器，不要一味的使用vector和map{{site.data.alerts.end}}

{{site.data.alerts.note}}本教程不使用智能指针，所有对象均手工管理内存，实际开发中可以使用智能指针降低内存管理的负担，但是vulkan对象生命周期比较特殊，释放顺序出错会直接导致程序崩溃，建议vulkan部分暂时手工管理，也可以参考[Vulkan Cookbook](https://www.packtpub.com/game-development/vulkan-cookbook)实现的VulkanDestoryer来更智能的释放vulkan对象{{site.data.alerts.end}}

## shader规范

&nbsp; &nbsp; &nbsp; &nbsp;shader规范我就随便一写，我其实也没用，不过真的开发的话可以参考一下。这个规范是我在公司总结的，自己想的，所以很不成熟，也希望大家可以一起讨论。

### GLSL规范

- 常量、宏，全部字母大写，用`_`分隔单词
- 减少全局变量的使用，全局变量使用驼峰命名法，以`G`开头
- uniform变量，使用驼峰命名法，以`u`开头
- 函数，使用驼峰命名法，首字母小写
- 对于函数，优先使用返回值，少用`inout`修改参数
- 对于桌面平台的GLSL，建议在版本号后加上`core`

&nbsp; &nbsp; &nbsp; &nbsp;对于SM3以下的feature level，只存在vertex shader和fragment shader(pixel shader)

- attribute变量，使用驼峰命名法，以`a`开头
- varying变量，使用驼峰命名法，以`v`开头

&nbsp; &nbsp; &nbsp; &nbsp;对于SM4及以上的feature level，在必选的vertex shader和fragment shader，还有可选的geometry shader，tessellation shader和compute shader，取消attribute/varying改为in/out关键字，用法如下

- `in/out`关键字在支持location必须指明存储位置
- 在支持ubo的平台尽可能使用ubo
- `in/out`变量能表示着色器之间传递的顺序

&nbsp; &nbsp; &nbsp; &nbsp;解释一下，我一般将应用程序记为`a`，顶点着色器记为`v`，片元着色器记为`f`，几何着色器记为`g`，细分着色器记为`tse`和`tsc`，计算着色器记为`cs`。用`<起点>2<终点>`作为变量前缀，比如

- `a2vFoo`表示应用程序向顶点着色器传递数据
- `v2fBar`表示顶点着色器向片元着色器传递数据
- `v2tseFoo`表示顶点着色器向细分计算着色传递数据
- `v2tsCFoo`表示顶点着色器向细分控制着色传递数据
- `g2fBar`表示几何着色器向片元着色器传递数据
- `a2gFoo`表示顶点着色器向几何着色器传递数据