---
title: Introduction
audience: field engineers, clients
type: first_page
homepage: true
---

## 正文开始之前(必看)

&#160; &#160; &#160; &#160;Vulkan作为一个新API，她有很多概念还没有一个准确统一的翻译，比如image，view，semaphore，barrier，fence，queue。这些词汇很简单，但是如果直接使用它的汉译，就很傻很晦涩，比如说显存中的图片，你会说这是啥玩意，说显存中的image，就好很多。所以这个教程很多概念我会直接使用英文单词，有些中午也会用括号展示英文，写的很Chinglish希望大家原谅。

&#160; &#160; &#160; &#160;本教程是一个非常基础的Vulkan教程，并教不了什么东西，也就是帮大家克服一下对新概念的恐惧。对于有openGL/directX基础的同学，本教程可以帮你迅速掌握vulkan的一些概念，同时和自己的图形学知识相衔接。vulkan相比openGL，非常复杂，因为把以前由驱动负责的工作都交给开发者完成了，相信这个大家在看这篇教程之前就已经知道了。如果没有glfw来帮我处理各平台之间的差异，画个三角都需要超过2k行代码，而且还会宏无数，有了glfw之后，画三角形的代码会被大幅缩减，但也有8、9百行，而同样功能的openGL代码也就2百行。对于编程的新手来说，一次写将近千行代码其实是个挑战，所以第一次画三角形的代码我拆的很散。而且相比openGL至多一下午就能画出三角形不同，对于新人，也许需要3~4天，或者更久。这个教程，会从非常简单的base code开始，一点一点扩充，后一节的代码建立在前一节的基础上。我希望每一节代码都能亲自敲一下，特别是新手。Copy的和自己亲自打的，感觉到底是不一样。

&#160; &#160; &#160; &#160;这篇教程，我希望你有下列准备：

- 支持vulkan的显卡(N卡开普勒及以上，A卡GCN架构，I卡HD4000以上(HD3000的vulkan驱动貌似只有linux版本))
- c++开发经验(我会大量使用STL，而且我不会赘述STL相关的东西；我也希望你有能力自己解决各种依赖)
- 支持c++14的编译器(虽然我应该只用了c++11的特性)
- 有自己习惯的开发工具(我不希望把这个教程局限在某种IDE/Editor和构建工具上)
- 最好有图形学开发经验，比如openGL或者direct3D
- 在提问题之前看一下提问的智慧(起码我不希望我看到的问题是代码编译不过或者索要源码这样的)

&#160; &#160; &#160; &#160;vulkan虽然非常冗长，复杂。但是，写起来麻烦，维护起来容易，因为所有东西都由开发者显示指定了，并不会发生什么不可预料的行为。vulkan在一出生时，就考虑到了openGL开发难以纠错和调试的问题，因此创造了层(layer)的概念。在[lunarG SDK](https://www.lunarg.com/vulkan-sdk/)中，在很早版本就提供了tracer和replayer，而在高版本的SDK中，更是直接提供了可视化的tracer。vulkan作为优先处理高性能图像的API，自然是需要满足游戏引擎的很多需求，因此vulkan和HLSL的相性其实特别好。在教程正文结束后，我也会追加HLSL以及调试的内容，敬请期待。
