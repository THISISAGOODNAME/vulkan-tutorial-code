---
title: Base code
last_updated: February 16, 2018
summary: "检验你依赖添加是否正确的时候到了"
---

## 基本结构

&#160; &#160; &#160; &#160;首先完成最基本的程序结构。

```c++
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <functional>

class HelloTriangleApplication {
public:
    void run() {
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initVulkan() {

    }

    void mainLoop() {

    }

    void cleanup() {

    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

&#160; &#160; &#160; &#160;这就是程序最基本的结构了，之后就要在这个架子的基础上，将几个空函数补完。

## 使用GLFW创建窗口

&#160; &#160; &#160; &#160;如果vulkan只用来离屏渲染或者科学计算，不创建窗口也没什么问题，但是，相信大家还是更想学vulkan作为图形API的部分，对吧。首先，将第一行`#include <vulkan/vulkan.h>`替换为如下代码：

```c++
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
```

&#160; &#160; &#160; &#160;这样GLFW可以添加自己需要的宏并自动帮你添加Vulkan头文件。接下来添加一个`initWindow`方法，并在`run`函数中进行调用。

```c++
void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

private:
    void initWindow() {

    }
```

&#160; &#160; &#160; &#160;接下来完成`initWindow`函数，如果你以前用过GLFW，这部分可能会比较熟悉。首先应该调用`glfwInit()`，来初始化GLFW库。GLFW一开始是openGL上下文管理器，所以接下来应该阻止GLFW创建openGL上下文。

```c++
glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
```

&#160; &#160; &#160; &#160;我们先禁用窗口缩放，因为窗口缩放涉及很复杂的逻辑，我们会在比较靠后的章节再讨论。

```c++
glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
```

&#160; &#160; &#160; &#160;之后就准备创建真的window了，先给类添加一个私有变量`GLFWwindow* mWindow`，然后在`initWindow`中用如下方法初始化窗口：

```c++
mWindow = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
```

&#160; &#160; &#160; &#160;该函数前三个参数用来表示窗口的宽，高和标题。第四个参数可以指定在某个显示器上显示窗口。最后一个参数只和openGL有关。

&#160; &#160; &#160; &#160;对于经常使用的宽、高这样的变量，使用常量而不是硬编码到函数中是一个好习惯。添加宽度高度常量并修改窗口创建的函数:

```c++
const int WIDTH = 800;
const int HEIGHT = 600;

mWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
```

&#160; &#160; &#160; &#160;现在，你的`initWindow`应该是下面这个样子：

```c++
void initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    mWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}
```

&#160; &#160; &#160; &#160;对于一个应用程序，我们希望他一直运行，知道发生错误或者主动关闭(一般叫主循环或者主事件循环)，所以需要修改`mainLoop`函数如下：

```c++
void mainLoop() {
    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();
    }
}
```

&#160; &#160; &#160; &#160;在程序关闭时，释放掉资源是个好习惯，修改`cleanup`函数如下:

```c++
void cleanup() {
    glfwDestroyWindow(mWindow);

    glfwTerminate();
}
```

> 有C++开发经验的同学可以使用智能指针来简化资源释放的过程。

&#160; &#160; &#160; &#160;现在运行程序，如果看到一个空白窗口，窗口标题为`vulkan`，那么恭喜你，运行成功。
