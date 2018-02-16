---
title: 开发环境搭建
last_updated: February 16, 2018
summary: "开发环境搭建"
---

&#160; &#160; &#160; &#160;本教程用到的库并不多，一共有如下：

- [LunarG Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)(win/linux)
- [MoltenVK](https://moltengl.com/moltenvk/)(mac)
- [GLFW](http://www.glfw.org/)
- [GLM](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
- [tinyobjloader](https://github.com/syoyo/tinyobjloader/blob/master/tiny_obj_loader.h)

> 相信有openGL开发经验的同学对上面大部分库都很熟悉了，而vulkan SDK除了提供类似openGL Function loader的功能，还提供错误验证，帧调试等功能

{{site.data.alerts.note}}Mac上的vulkan SDK MoltenVK，并不能使用LunarG的Validation layers(虽然官方blog已经声明会在之后的版本中加入LunarG Validation layers的支持，但是截止到本文写作时的版本(0.19)，moltenVK还不支持LunarG Validation layers。){{site.data.alerts.end}}

## Windows

&nbsp; &nbsp; &nbsp; &nbsp;略

## Linux

&nbsp; &nbsp; &nbsp; &nbsp;略

## Mac

&nbsp; &nbsp; &nbsp; &nbsp;略