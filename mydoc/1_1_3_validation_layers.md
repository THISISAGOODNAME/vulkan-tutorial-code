---
title: Validation layers
last_updated: February 17, 2018
summary: "vulkan验证层可以有效的帮助你追踪错误"
---

## 为什么需要验证层

&#160; &#160; &#160; &#160;vulkan API的设计思想，就是最小化驱动开销。不过这也导致了只靠驱动提供的错误信息非常的有限。即便很小的错误都有可能导致程序的崩溃，或者渲染错误。vulkan要求开发者显式指定所有需要的参数，但也导致了开发者如果遗漏了某个参数，就会非常棘手。

&#160; &#160; &#160; &#160;vulkan驱动虽然不能很好的纠错，但不代表vulkan不行。vulkan引入了一个非常巧妙的机制来解决这个问题，就是验证层(validation layers)。验证层在驱动和API调用之间进行额外的操作，来提供额外的功能：

- 检查参数使用是否合乎规范，防止误用
- 追踪资源创建和释放，防止内存泄漏
- 检查资源是否线程安全
- 记录vulkan调用，以及每次调用的输入和输出
- 记录vulkan调用，用来性能分析和回放

&#160; &#160; &#160; &#160;下面是一个加了参数诊断信息的`vkCreateInstance`函数。

```c++
VkResult vkCreateInstance(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* instance) {

    if (pCreateInfo == nullptr || instance == nullptr) {
        log("Null pointer passed to required parameter!");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    return real_vkCreateInstance(pCreateInfo, pAllocator, instance);
}
```

&#160; &#160; &#160; &#160;可以在debug模式下启用验证层，而在release模式下关闭验证层。这样既能在开发时得到有用的错误信息，也能让用户在运行时获得最佳性能。

&#160; &#160; &#160; &#160;vulkan驱动没有内建验证层，但是LunarG Vulkan SDK中提供了一个，它还是[开源的](https://github.com/LunarG/VulkanTools/tree/master/layers)。使用验证层可以帮助开发者防止在不同驱动上有不同的表现。

{{site.data.alerts.note}}在vulkan API驱动的实现上，AN又犯了openGL驱动时代的毛病，N卡的驱动宽松，差个参数什么的都给你过了，而A卡驱动就相对严格。I卡。。。I卡的官方驱动。。。挺搞笑的，如果使用I卡，个人推荐你在Linux上使用mesa3D的开源驱动。Android vulkan驱动整体也是相对严格的那种。{{site.data.alerts.end}}

&#160; &#160; &#160; &#160;在过去版本的LunarG SDk中，验证层有两种：instance 和 device。实例层只检查Global的错误，而设备层只检查和某个VkDevice相关的错误。设备层最近被标注为被废弃了，就是说以后实例层可以追踪所有vulkan调用。不过文档还是建议为了兼容性依旧使用设备层(I卡vulkan驱动比AN的vulkan驱动支持的vulkan小版本总是差着几十个版本号)

## 启用验证层

&#160; &#160; &#160; &#160;我们启用vulkan SDK提供的标准诊断层，也就是`VK_LAYER_LUNARG_standard_validation`。我之前提到了vulkan验证层的众多功能，其实每个功能都是单独的验证层。而`VK_LAYER_LUNARG_standard_validation`就是LunarG vulkan SDK中提供所有验证层的集合。

&#160; &#160; &#160; &#160;首先创建一个常量用来表示是否开启验证层，`NDEBUG`宏表示release。

```c++
const int WIDTH = 800;
const int HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
```

{{site.data.alerts.warning}}如果使用mac开发，使用MoltenVK SDK，则不能使用LunarG SDK的验证层。MoltenVK有自己的验证层，官方blog也表示未来可能会引入LunarG的验证层支持，但是现在，如果在mac上开发，请关闭验证层。{{site.data.alerts.warning}}

&#160; &#160; &#160; &#160;接下来创建一个`checkValidationLayerSupport`函数，用来检查可用的层。

```c++
bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    return false;
}
```

&#160; &#160; &#160; &#160;获得所有层之后，检查是否`validationLayers`里的所有元素都包含在`availableLayers`之中。如果使用`strcmp`还需要添加`<cstring>`头文件。

```c++
for (const char* layerName : validationLayers) {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayers) {
        if (strcmp(layerName, layerProperties.layerName) == 0) {
            layerFound = true;
            break;
        }
    }

    if (!layerFound) {
        return false;
    }
}

return true;
```

&#160; &#160; &#160; &#160;在`createInstance`调用`checkValidationLayerSupport`:

```c++
void createInstance() {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    ...
}
```

&#160; &#160; &#160; &#160;修改`VkInstanceCreateInfo`结构，来启用验证层：

```c++
if (enableValidationLayers) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
} else {
    createInfo.enabledLayerCount = 0;
}
```

&#160; &#160; &#160; &#160;运行程序，如果错误了，`vkCreateInstance`会返回`VK_ERROR_LAYER_NOT_PRESENT`错误。这时候就考虑更新显卡驱动，重新安装vulkan SDK比较靠谱。

## Message callback

&#160; &#160; &#160; &#160;虽然你启用了验证层，但是你可能发现，然并卵。因为验证层还需要向程序返回信息的方法。为了接收这些信息，我们需要创建一个回调函数(使用`VK_EXT_debug_report`扩展，和`GL_ARB_debug_output`扩展类似)。

&#160; &#160; &#160; &#160;首先创建`getRequiredExtensions`函数，判断验证层是否开启，然后返回需要扩展的数组。

```c++
std::vector<const char*> getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }

    return extensions;
}
```

&#160; &#160; &#160; &#160;GLFW提供的扩展是一直需要的，但是debug report扩展是按需开启的。`VK_EXT_DEBUG_REPORT_EXTENSION_NAME`宏和`VK_EXT_debug_report`字符串是等价的，但是使用宏可以编写时提供代码提示，编译时检查内容是否存在，来防止一些码字错误。

&#160; &#160; &#160; &#160;在`createInstance`函数中调用该函数:

```c++
auto extensions = getRequiredExtensions();
createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
createInfo.ppEnabledExtensionNames = extensions.data();
```

&#160; &#160; &#160; &#160;运行程序，确保没有`VK_ERROR_EXTENSION_NOT_PRESENT`错误。

&#160; &#160; &#160; &#160;接下来编写回调函数。给类添加一个静态函数成员`debugCallback`，其定义和函数指针`PFN_vkDebugReportCallbackEXT`相同。`VKAPI_ATTR` 和 `VKAPI_CALL`用来确保vulkan调用时有正确的函数签名。

```c++
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objType,
    uint64_t obj,
    size_t location,
    int32_t code,
    const char* layerPrefix,
    const char* msg,
    void* userData) {

    std::cerr << "validation layer: " << msg << std::endl;

    return VK_FALSE;
}
```

{{site.data.alerts.note}}你可能会问，错误信息直接输出到console不就得了，为何还要使用如此复杂的回调机制。对于某些平台，比如嵌入式设备，输出到console并不方便。在移动开发中，你可能更愿意输出到日志，或者直接在屏幕上显示。创建回调这个机制给了开发者者显示错误信息的自由。{{site.data.alerts.end}}

&#160; &#160; &#160; &#160;第一个参数指定的错误信息的类型，可以是下列几种情况或者情况的组合：

- `VK_DEBUG_REPORT_INFORMATION_BIT_EXT`
- `VK_DEBUG_REPORT_WARNING_BIT_EXT`
- `VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT`
- `VK_DEBUG_REPORT_ERROR_BIT_EXT`
- `VK_DEBUG_REPORT_DEBUG_BIT_EXT`

&#160; &#160; &#160; &#160;`objType`表示信息的类型。举个例子，如果`obj`是`VkPhysicalDevice`类型的，那`objType`就是`VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT`。所有vulkan内置类型都可以用`uint64_t`代替。`msg`参数就是错误信息。`userData`可以额外附带一些由开发者提供的内容。

&#160; &#160; &#160; &#160;回调的返回值表示验证层是否发现异常。如果返回值是true，函数调用就会中止，然后报一个`VK_ERROR_VALIDATION_FAILED_EXT`错误。一般这是用来检测验证层可用性的，在自己的程序里，返回值总是`VK_FALSE`。

&#160; &#160; &#160; &#160;现在需要在vulkan中启用这个回调函数。正如前文所说，vulkan需要开发者自己负责很多事。就算回调函数句柄的构造和销毁，也需要开发者自己负责。在类中添加一个成员：

```c++
VkDebugReportCallbackEXT mCallback;
```

&#160; &#160; &#160; &#160;添加一个`setupDebugCallback`函数，在`initVulkan`中调用(需要在`createInstance`调用之后调用)：

```c++
void initVulkan() {
    createInstance();
    setupDebugCallback();
}

void setupDebugCallback() {
    if (!enableValidationLayers) return;

}
```

&#160; &#160; &#160; &#160;接下来就实现`setupDebugCallback`函数，首先需要描述一下回调的相关信息：

```c++
VkDebugReportCallbackCreateInfoEXT createInfo = {};
createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
createInfo.pfnCallback = debugCallback;
```

&#160; &#160; &#160; &#160;`flags`可以过滤你需要的信息。`pfnCallback`指针指向具体使用的回调函数。`pUserData`是一个可选配置，对应回调函数的最后一个参数`userData`。

&#160; &#160; &#160; &#160;这个结构要传给`vkCreateDebugReportCallbackEXT`来创建`VkDebugReportCallbackEXT`对象。不过，这个函数是一个扩展。用过openGL扩展的同学应该都有印象，这个函数是不能直接调用的。而且需要使用`vkGetInstanceProcAddr`查找该扩展对应的函数指针。我创建了一个全局的辅助函数完成此功能：

```c++
VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
    auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pCallback);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}
```

&#160; &#160; &#160; &#160;如果扩展不存在`vkGetInstanceProcAddr`会返回`nullptr`。现在继续实现`setupDebugCallback`方法：

```c++
if (CreateDebugReportCallbackEXT(mInstance, &createInfo, nullptr, &mCallback) != VK_SUCCESS) {
    throw std::runtime_error("failed to set up debug callback!");
}
```

&#160; &#160; &#160; &#160;第三个参数是可选的分配器，这也是我最后一次解说这个概念了。以后看见`nullptr`，就去看看文档，看看是不是`pAllocator`。运行程序在关闭，你会看到如下错误：

![validation_layer_test.png](images/validation_layer_test.png)

&#160; &#160; &#160; &#160;验证层报了个错误，回调没销毁。不过，验证层已经生效了。接下来就释放回调函数。`VkDebugReportCallbackEXT`对象需要调用`vkDestroyDebugReportCallbackEXT`函数来进行销毁。创建另一个全局辅助函数`DestroyDebugReportCallbackEXT`:

```c++
void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
    if (func != nullptr) {
        func(instance, callback, pAllocator);
    }
}
```

&#160; &#160; &#160; &#160;接着在`cleanup`函数中清理回调函数:

```c++
void cleanup() {
    DestroyDebugReportCallbackEXT(mInstance, callback, nullptr);
    vkDestroyInstance(mInstance, nullptr);

    glfwDestroyWindow(mWindow);

    glfwTerminate();
}
```

&#160; &#160; &#160; &#160;现在运行程序再关闭，错误信息消失了。调试程序时，可以在回调函数中打一个断点，然后在程序的调用栈中，可以看是哪个函数调用出错了。

## 配置验证层的功能

&#160; &#160; &#160; &#160;相比`VkDebugReportCallbackCreateInfoEXT`，LunarG的验证层还有很多可选的配置。打开SDK安装目录下的Config文件夹，打开`vk_layer_settings.txt`，里面有如何配置自己验证层的相信说明。然后，把这个文件扔到可执行文件目录下，验证层的配置就生效了。
