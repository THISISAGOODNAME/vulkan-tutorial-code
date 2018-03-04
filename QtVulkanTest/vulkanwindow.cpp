#include "vulkanwindow.h"

QVulkanWindowRenderer *VulkanWindow::createRenderer()
{
    return new VulkanRenderer(this, true);
}
