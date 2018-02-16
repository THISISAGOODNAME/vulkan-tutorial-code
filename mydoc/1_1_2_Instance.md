---
title: Instance
last_updated: February 16, 2018
summary: "第一步"
---

## 创建instance(实例)

&#160; &#160; &#160; &#160;使用Vulkan的第一步，就是创建一个`instance` 。instance连通vulkan库还有你自己的应用程序的桥梁。而创建instance的过程中，还需要向驱动汇报一些你自己的应用程序的参数，来帮驱动更好的进行优化。

&#160; &#160; &#160; &#160;首先创建`createInstance`函数，并且在`initVulkan`中调用:

```c++
void initVulkan() {
    createInstance();
}
```

&#160; &#160; &#160; &#160;然后创建私有变量`mInstance`:

```c++
private:
    VkInstance mInstance;
```

&#160; &#160; &#160; &#160;接下来创建一个用来描述应用信息的结构([VkApplicationInfo](https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkApplicationInfo.html))，这个严格来说是可选的，但是描述一下应用可以让驱动更好的进行优化。比如你用了某知名图形引擎，而这个引擎恰好有些怪癖，那这步驱动就能提前做好准备：

```c++
VkApplicationInfo appInfo = {};
appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
appInfo.pApplicationName = "Hello Triangle";
appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
appInfo.pEngineName = "No Engine";
appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
appInfo.apiVersion = VK_API_VERSION_1_0;
```

&#160; &#160; &#160; &#160;每个vulkan结构都需要显示的指明`sType`，虽然有些麻烦，但是会大大减少运行时出错的概率。每个vulkan结构都有`pNext`属性，在以后可以指向某个扩展。在本教程中，该属性均为`nullptr`(也就是不显示指定)。

&#160; &#160; &#160; &#160;接下来创建表示instance创建信息的结构体，这个结构体就不是可选的了。这个结构体用来告诉驱动我们需要使用那些global extensions还有validation layers。Global表示这些扩展全局通用，而非某些device专用，你现在看了可能一头雾水，但是看了后续章节之后，应该会好很多。 

```c++
VkInstanceCreateInfo createInfo = {};
createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
createInfo.pApplicationInfo = &appInfo;
```

&#160; &#160; &#160; &#160;这两个属性顾名思义，接下来两个属性其实也不难理解，就是描述vulkan的global extensions。在序言中已经提到，vulkan是一个平台无关的API。所以各平台原生窗口系统相关的部分，就要依靠扩展来实现(其实openGL也是这样，glx,wgl,cgl,NSopenGL,egl)。不过，GLFW已经内建了方法，帮我们处理这个复杂的情况。

```c++
uint32_t glfwExtensionCount = 0;
const char** glfwExtensions;

glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

createInfo.enabledExtensionCount = glfwExtensionCount;
createInfo.ppEnabledExtensionNames = glfwExtensions;
```

&#160; &#160; &#160; &#160;VkApplicationInfo还有两个参数和validation layers相关，我们在下一个章节会详细讨论，在这把他们置空就可以了。

```c++
createInfo.enabledLayerCount = 0;
```

> 在开始创建一个空结构体时已经将所有属性置空了。

&#160; &#160; &#160; &#160;到此为止，创建instance所需的所有信息都已经准备完毕了，可以调用`vkCreateInstance`函数来创建instance了：

```c++
VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
```

&#160; &#160; &#160; &#160;这个函数有三个参数，三个参数都是指针：

1. 指向创建信息的指针
2. 指向自定义分配器回调函数(custom allocator callbacks)的指针，在本教程中分配器参数永远为`nullptr`
3. 指向要存储的对象

&#160; &#160; &#160; &#160;基本上所有vulkan函数都有一个`VkResult`类型的返回值，要么是`VK_SUCCESS`，要么是具体的错误码，我们不太关心具体错误码是什么，所以可以用如下方法来简单的检查是否创建成功：

```c++
if (vkCreateInstance(&createInfo, nullptr, &mInstance) != VK_SUCCESS) {
    throw std::runtime_error("failed to create instance!");
}
```

## 检测扩展支持情况

&#160; &#160; &#160; &#160;我们使用了glfw提供的方法来检查vulkan全局扩展的支持，不过，我还是提一下手工检查扩展的方法。

```c++
uint32_t extensionCount = 0;
vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

std::vector<VkExtensionProperties> extensions(extensionCount);
vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

std::cout << "available extensions:" << std::endl;

for (const auto& extension : extensions) {
    std::cout << "\t" << extension.extensionName << std::endl;
}
```

&#160; &#160; &#160; &#160;`vkEnumerateInstanceExtensionProperties`用来检查vk instance级别扩展的支持情况。我前面提过，使用的c风格的vulkan接口，c语言中并没有动态数组，所以使用这样巧妙的方法，先检查扩展的数量，在创建指定大小的数组。

## 销毁资源

&#160; &#160; &#160; &#160;`VkInstance`对象销毁需要使用`vkDestroyInstance`方法，修改`cleanup`函数如下：

```c++
void cleanup() {
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
}
```

> vulkan所以的create和destroy函数，都有一个可选的allocator callbacks，在本教程中，我会完全忽略这个参数(设置为`nullptr`)
