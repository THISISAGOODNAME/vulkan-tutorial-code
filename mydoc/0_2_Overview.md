---
title: Overview
last_updated: February 15, 2018
summary: "vulkan起源，画三角的步骤，vulkan API的样子"
---

## vulkan的起源

&#160; &#160; &#160; &#160;vulkan的前辈openGL有几个问题：

- 不同厂商兼容性不一样(可能N卡能跑A卡就跑不了，都能跑同样的代码也可能显示出来不一样)
- 驱动性能差(浪费CPU时间，不支持多线程)
- 难以查错
- 开发工具链比较简陋

&#160; &#160; &#160; &#160;vulkan的出现，就是为了解决上述的问题。而且vulkan还吸收了openCL，将openGL 4.3引入的计算着色器进一步发展。就是说，vulkan和dx，metal一样，即是图形API，也是计算API，在静等AI和AR技术的高潮期到来。

## vulkan画三角形的步骤

&#160; &#160; &#160; &#160;我接下来要简述vulkan绘制三角形的各个步骤，这只是个概览，每个步骤在对应章节都会详细阐述。

### 1 - Instance and physical device selection

&#160; &#160; &#160; &#160;Vulkan程序需要创建一个[VkInstance](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkInstance.html)来启用vulkan API.在创建Instance时你需要准确的描述你的应用程序的一些属性，以及你需要使用的各种API。在创建Instance之后，你需要查询硬件对vulkan的支持，并选择一个或者多个[VkPhysicalDevices](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDevice.html)。 你会查询各种硬件参数，比如显存和显卡兼容性，来选取最理想的设备。举个例子，相比集显，咱们更喜欢独显(除了个别搞笑的亮机卡，不过那些支不支持vulkan都不好说呢，就我了解，N家亮机卡能支持vulkan的好像就开普勒架构的GT730还有GT1030)。

### 2 - Logical device and queue families

&#160; &#160; &#160; &#160;在决定使用哪块显卡之后，你需要创建一个[VkDevice](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkDevice.html) (logical device)，在创建过程中你还要更详细的描述你用到的硬件特性([VkPhysicalDeviceFeatures](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDeviceFeatures.html))，比如multi viewport rendering(该特性VR渲染非常有用)和64位浮点支持(科学计算和HDR都需要)。你还需要制定你要使用的queue families。 大部分Vulkan操作， 比如绘制命令和内存/显存操作, 都需要通过提交到[VkQueue](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkQueue.html)之后异步执行。 Queue是从queue family分配的， 每个queue family中的Queue只支持某个特定集合的操作。举个例子，对于显卡，执行图形渲染、并行计算和内存交换可能是不同的queue family。在选择physical device时queue family的支持也是重要的参考之一。只支持科学计算不支持图形渲染的显卡有可能存在(事实上绘图相关的queue family是vulkan的扩张而非核心功能)，但是这年头支持vulkan但不支持绘图的设备，其实也不多。

### 3 - Window surface and swap chain

&#160; &#160; &#160; &#160;除非你不想显示图形(比如你只想离屏渲染)，不然你还是需要创建一个窗口来显示的。你可以用各个平台native的API(win32,xlib,xcb,mir,wayland)，或者[GLFW](http://www.glfw.org/)、[SDL](https://www.libsdl.org/)。在本教程中，使用GLFW。

&#160; &#160; &#160; &#160;如果真的想渲染到一个窗口，还需要两样东西: window surface (`VkSurfaceKHR`) 和 swap chain (`VkSwapChainKHR`)。注意 `KHR` 后缀，有openGL开发经验的同学可能清楚，这个后缀表示一个KHR扩展。Vulkan API 是平台无关的， 所以需要一个标准化的 WSI (Window System Interface) 扩展来和窗口系统进行交互。Surface是一个window渲染目标的抽象，创建时需要一个native窗口的句柄(和openGL完全一样)。幸运的是，GLFW内建的跨平台的方法来帮我们解决平台间的差异。

Swap chain是渲染一系列渲染目标(render target)的集合。他本来是保证我们渲染的image和屏幕上显示的image不是同一个(openGL双缓冲模型，目的是减少渲染时屏幕闪烁)。但是除了经典的双缓冲模型，Vulkan引入了更高级的交换方式，来解决双缓冲模型解决起来比较费劲的东西(比如垂直同步)。在创建Swap chain的章节我们会更详细的进行讨论。

### 4 - Image views and framebuffers

&#160; &#160; &#160; &#160;在从swap chain获得image之后，我们应该绘制它。为了绘制image，我们需要把这个image用 [VkImageView](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkImageView.html) 或者 [VkFramebuffer](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkFramebuffer.html)进行包装。 Image view 指向被使用的 image , 而 framebuffer 指向被使用的 image view， color，在着色或者进行深度/模板测试时都用得到。Swap chain中可能存在很多iamge，每个都需要创建image view还有framebuffer。在渲染时，我们需要选择正确的image进行绘制。

### 5 - Render passes

&#160; &#160; &#160; &#160;对于有图形开发经验的同学，Render pass应该用了很多次了，任何高级渲染技术，都不会少于两个Render pass。而Bloom甚至需要5个Render pass。

&#160; &#160; &#160; &#160;在画三角形的程序中，我们只需要一个image作为color target。

### 6 - Graphics pipeline

&#160; &#160; &#160; &#160;Vulkan中通过创建[VkPipeline](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPipeline.html)对象来创建graphics pipeline。它用来描述显卡各个渲染阶段的参数(用过dx的应该熟悉一些，在vulkan里，它也是可配置的了)。比如viewport的长宽、如何使用深度缓冲，或者用[VkShaderModule](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkShaderModule.html)详细的描述可编程阶段的各个属性。

&#160; &#160; &#160; &#160;vulkan和其他图形API有个显著区别，就是的几乎所有配置都需要提前创建。即便是更换一个shader或者改变定点参数的布局(vertex layout)，你都需要完全从新graphics pipeline创建一个graphics pipeline。这也意味着你需要创建大量的`VkPipeline`对象，来覆盖你渲染过程中的各种graphics pipeline变化。只有改变viewport或者改变clear color不需要重新生成graphics pipeline。

&#160; &#160; &#160; &#160;因为渲染管线各阶段都提前准备了，而不是运行时靠驱动判断。驱动可以更好的执行优化。而且在review代码时，也能更清楚打发现作者的意图。

### 7 - Command pools and command buffers

&#160; &#160; &#160; &#160;前文中已经提到了，vulkan中的各种操作，都需要靠提交到一个命令队列(queue)的方式进行异步执行。而在提交到命令队列之前，需要在[VkCommandBuffer](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkCommandBuffer.html)进行记录。命令缓冲和一个[VkCommandPool](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkCommandPool.html)关联，而`VkCommandPool`又和queue family关联。即便只画一个简单的三角形，我们也需要生成如下的command buffer：

1. Begin the render pass
2. Bind the graphics pipeline
3. Draw 3 vertices
4. End the render pass

&#160; &#160; &#160; &#160;因为framebuffer中的image又swap chain决定，每个可能的iamge都需要一个command buffer，这就需要创建大量的command buffer。也可以没帧重新生成command buffer，但是效率会低一些。

### 8 - Main loop

&#160; &#160; &#160; &#160;在command buffer准备好了之后，主循环就简单多了。我们先使用`vkAcquireNextImageKHR`方法得到一个image。然后选择合适的command buffer再使用[vkQueueSubmit](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkQueueSubmit.html)执行。最好，使用`vkQueuePresentKHR`方法想swap chain传递我们准备在屏幕上显示的image。

&#160; &#160; &#160; &#160;提交到命令队列的命令是异步的。但是运行是有顺序的，而保证运行顺序，就是开发者的工作了。vulkan提供了用来同步的对象，比如semaphore。依靠此对象，可以判断iamge是还在显示过程中，还是已经显示完整。

### 总结

&#160; &#160; &#160; &#160;总而言之，画三角需要如下的步骤：

1. 创建 VkInstance
2. 创建 VkPhysicalDevice
3. 创建 VkDevice 以及 VkQueue
4. 创建 window, window surface 以及 swap chain
5. 使用 VkImageView 包装swap chain中的images
6. 创建 render pass
7. 创建 framebuffers
8. 创建 graphics pipeline
9. 为每个可能用到的image创建command buffer，并记录draw commands
10. 通过获取image，向image绘制，提交到swap chain的方式来绘制一帧

## vulkan API

### 理解vulkan代码

&#160; &#160; &#160; &#160;我们在本教程中使用c风格的vulkan代码。也就是说将引用`vulkan.h`。所有的函数使用`vk`前缀，所有对象使用`Vk`前缀，多有常量使用`VK_`前缀。

&#160; &#160; &#160; &#160;vulkan创建对象的代码都是如下结构：

```c++
VkXXXCreateInfo createInfo = {};
createInfo.sType = VK_STRUCTURE_TYPE_XXX_CREATE_INFO;
createInfo.pNext = nullptr;
createInfo.foo = ...;
createInfo.bar = ...;

VkXXX object;
if (vkCreateXXX(&createInfo, nullptr, &object) != VK_SUCCESS) {
    std::cerr << "failed to create object" << std::endl;
    return false;
}
```

&#160; &#160; &#160; &#160;创建对象时，很多属性需要显示指定，比如`sType`表示createInfo的类型，而`pNext`可以指向一个扩展类型，在本教程中，`pNext`只会是`nullptr`。创建或销毁vulkan对象的方法可以有一个[VkAllocationCallbacks](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkAllocationCallbacks.html)参数，来让你自己控制驱动分配内存时的结构，在本教程中，该参数只会是`nullptr`。几乎所有vulkan方法都有返回值，返回`VK_SUCCESS`或一个错误码，来表示函数运行错误

### Validation layers

&#160; &#160; &#160; &#160;vulkan作为高性能API，为了降低驱动开销，只提供了非常有限的错误检查。驱动会经常崩溃，而不是返回错误信息，或者，显示异常。

&#160; &#160; &#160; &#160;vulkan创建了层的概念，在你的代码和驱动之间，可以创建很多层，用来处理错误，或者记录API调用进行各种分析。每个开发者都可以变现他们自己的验证层，但是为了简单，本教程将之间使用LunarG vulkan SDK提供的Validation layers。

&#160; &#160; &#160; &#160;因为vulkan API每步操作都需要显示指定，vulkan相比openGL和direct3D，能获得更多更有价值的错误信息。
