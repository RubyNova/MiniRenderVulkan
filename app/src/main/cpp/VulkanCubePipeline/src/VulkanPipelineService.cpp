#include <android/log.h>
#include "../include/VulkanPipelineService.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "../../ThirdParty/stb/stb_image.h"

void VulkanPipelineService::initVoxelData(android_app* app) {
    Json::Value root;
    auto path = "Resources/VoxelModels/Test.json";
    auto json = FileLoadingService::readFile(app, path);

    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

    builder["collectComments"] = true;
    Json::String errs;

    if (!reader->parse(json.data(), json.data() + json.size(), &root, &errs)) {
        throw std::runtime_error(errs);
    }

    Json::Value array = root["vectorValues"];

    //BUG: if you uncomment any of these, you'll see it fall over
    for (size_t i = 0; i < array.size(); i++) {
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians((90.0f + 180.0f)), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));



        //BUG: if this line is uncommented, it seems to align correctly? I'm guessing I screwed something up elsewhere.
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat() + 20, array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat() - 20, array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat() - 20, array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat() + 20, array[static_cast<int>(i)][2].asFloat())));

        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat() + 40, array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat() - 40, array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat() - 40, array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat() + 40, array[static_cast<int>(i)][2].asFloat())));

        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat() + 60, array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat() - 60, array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat() - 60, array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat() + 60, array[static_cast<int>(i)][2].asFloat())));

        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat() + 80, array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat() - 80, array[static_cast<int>(i)][1].asFloat(), array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat() - 80, array[static_cast<int>(i)][2].asFloat())));
        _transformData.emplace_back(glm::translate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(array[static_cast<int>(i)][0].asFloat(), array[static_cast<int>(i)][1].asFloat() + 80, array[static_cast<int>(i)][2].asFloat())));

    }

    _voxelInstanceCount = _transformData.size();

    std::cout << "Detected " << _voxelInstanceCount << " voxels. This will result in " << _voxelInstanceCount * _vertices.size() << " unique vertices, " << _voxelInstanceCount * _indices.size() << " indices, and " << _voxelInstanceCount * (_indices.size() / 3) << " faces in the world." << std::endl;
}

bool VulkanPipelineService::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : _validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (std::strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

void VulkanPipelineService::createInstance() {
    if (_enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "CubePipeline";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "MiniRenderVulkan";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkDebugReportCallbackCreateInfoEXT debugCreateInfo;

    if (_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
        createInfo.ppEnabledLayerNames = _validationLayers.data();

        debugCreateInfo = getDebugMessengerCreateInfo();
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    std::vector<const char*> instanceExtensions;
    instanceExtensions.push_back("VK_KHR_surface");
    instanceExtensions.push_back("VK_KHR_android_surface");



    uint32_t vkExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);

    std::vector<VkExtensionProperties> vkExtensions(vkExtensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, vkExtensions.data());

    __android_log_print(ANDROID_LOG_DEBUG, "Available VK Extensions:",
                        "No usage and required_pros");
    for (const auto& extension : vkExtensions) {

        __android_log_print(ANDROID_LOG_DEBUG, extension.extensionName,
                            "No usage and required_pros");
    }

    std::cout << std::endl;

    bool extensionsFound = true;
    bool extensionFound = false;

    for (size_t i = 0; i < instanceExtensions.size(); i++) {
        extensionFound = false;

        for (const auto& extension : vkExtensions) {
            if (std::string(extension.extensionName) != instanceExtensions[i]) {
                continue;
            }
            extensionFound = true;
        }

        if (!extensionFound) {
            extensionsFound = false;
            break;
        }
    }

    if (extensionsFound) {
        __android_log_print(ANDROID_LOG_DEBUG, "Required extensions for Android rendering found!",
                            "No usage and required_pros");
    }
    else {
        throw std::runtime_error("Unable to find extensions required by Android! Aborting.");
    }

    std::vector<const char*> extensions(instanceExtensions);

    if (_enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    //VkResult result = vkCreateInstance(&createInfo, nullptr, &_instance);

    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void VulkanPipelineService::setupDebugMessenger() {
    if (!_enableValidationLayers) {
        return;
    }

    VkDebugReportCallbackCreateInfoEXT createInfo = getDebugMessengerCreateInfo();

    VkResult fuck = createDebugUtilsMessengerEXTViaProcAddress(_instance, &createInfo, nullptr, &_debugMessenger);
    if (fuck != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

QueueFamilyIndices VulkanPipelineService::findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices _indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            _indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, _surface, &presentSupport);

        if (presentSupport) {
            _indices.presentFamily = i;
        }

        i++;
    }

    return _indices;
}

SwapChainSupportDetails VulkanPipelineService::querySwapChainSupport(VkPhysicalDevice device) {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, _surface, &details.capabilities);

    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

bool VulkanPipelineService::checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(_deviceExtensions.begin(), _deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

int32_t VulkanPipelineService::rateDeviceSuitability(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    
    int score = 0;

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000;
    }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // We require certain families to exist, which are contained in a struct. -1 is assigned if its not useable.
    QueueFamilyIndices _indices = findQueueFamilies(device);

    //check its a valid device at all.
    if (!_indices.isComplete() || !checkDeviceExtensionSupport(device) || querySwapChainSupport(device).presentModes.empty() || !deviceFeatures.geometryShader || !deviceFeatures.samplerAnisotropy) {
        score = INVALID_PHYISCAL_VK_DEVICE;
    }

    return score;
}

void VulkanPipelineService::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto& device : devices) {
        int score = rateDeviceSuitability(device);
        if (score == INVALID_PHYISCAL_VK_DEVICE) {
            continue;
        }

        candidates.insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0) {
        _physicalDevice = candidates.rbegin()->second;
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(_physicalDevice, &properties);
        std::cout << "Chosen Device: " << properties.deviceName << std::endl;
    }
    else {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void VulkanPipelineService::createLogicalDevice() {
    QueueFamilyIndices _indices = findQueueFamilies(_physicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { _indices.graphicsFamily.value(), _indices.presentFamily.value() };

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(_deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = _deviceExtensions.data();

    if (_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
        createInfo.ppEnabledLayerNames = _validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_logicalDevice) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical device!");
    }

    vkGetDeviceQueue(_logicalDevice, _indices.graphicsFamily.value(), 0, &_graphicsQueue);
    vkGetDeviceQueue(_logicalDevice, _indices.presentFamily.value(), 0, &_presentQueue);
}

void VulkanPipelineService::createSurface() {
    VkAndroidSurfaceCreateInfoKHR createInfo{
            .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            .pNext = nullptr,
            .flags = 0,
            .window = _app->window
    };

    if (vkCreateAndroidSurfaceKHR(_instance, &createInfo, nullptr, &_surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

VkSurfaceFormatKHR VulkanPipelineService::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR VulkanPipelineService::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanPipelineService::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
    if(capabilities.currentTransform & VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR ||
       capabilities.currentTransform & VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR) {
        VkExtent2D returnExtents{};
        returnExtents.height = capabilities.currentExtent.width;
        returnExtents.width = capabilities.currentExtent.height;
        _width = returnExtents.width;
        _height = returnExtents.height;
        return returnExtents;
    }

    _width = capabilities.currentExtent.width;
    _height = capabilities.currentExtent.height;
    return capabilities.currentExtent;
}

void VulkanPipelineService::createSwapChain() {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(_physicalDevice);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = _surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices _indices = findQueueFamilies(_physicalDevice);
    uint32_t queueFamilyIndices[] = { _indices.graphicsFamily.value(), _indices.presentFamily.value() };

    if (_indices.graphicsFamily != _indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(_logicalDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(_logicalDevice, swapChain, &imageCount, nullptr);
    _swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(_logicalDevice, swapChain, &imageCount, _swapChainImages.data());

    _swapChainImageFormat = surfaceFormat.format;
    _swapChainExtent = extent;
}

VkImageView VulkanPipelineService::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) {
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    VkImageView imageView;
    if (vkCreateImageView(_logicalDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture image view!");
    }

    return imageView;
}

void VulkanPipelineService::createImageViews() {
    _swapChainImageViews.resize(_swapChainImages.size());

    for (size_t i = 0; i < _swapChainImages.size(); i++) {
        _swapChainImageViews[i] = createImageView(_swapChainImages[i], _swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
    }
}

void VulkanPipelineService::createRenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = _swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentDescription depthAttachment{};
    depthAttachment.format = findDepthFormat();
    depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthAttachmentRef{};
    depthAttachmentRef.attachment = 1;
    depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    subpass.pDepthStencilAttachment = &depthAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(_logicalDevice, &renderPassInfo, nullptr, &_renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }
}

void VulkanPipelineService::createDescriptorSetLayout() {
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

    VkDescriptorSetLayoutBinding samplerLayoutBinding{};
    samplerLayoutBinding.binding = 1;
    samplerLayoutBinding.descriptorCount = 1;
    samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerLayoutBinding.pImmutableSamplers = nullptr;
    samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    
    VkDescriptorSetLayoutBinding transformUboLayoutBinding{};
    transformUboLayoutBinding.binding = 2;
    transformUboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    transformUboLayoutBinding.descriptorCount = 1;
    transformUboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    transformUboLayoutBinding.pImmutableSamplers = nullptr; // Optional

    VkDescriptorSetLayoutBinding lightPosUboLayoutBinding{};
    lightPosUboLayoutBinding.binding = 3;
    lightPosUboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    lightPosUboLayoutBinding.descriptorCount = 1;
    lightPosUboLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    lightPosUboLayoutBinding.pImmutableSamplers = nullptr; // Optional

    std::array<VkDescriptorSetLayoutBinding, 4> bindings = {uboLayoutBinding, samplerLayoutBinding, transformUboLayoutBinding, lightPosUboLayoutBinding };

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    if (vkCreateDescriptorSetLayout(_logicalDevice, &layoutInfo, nullptr, &_descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

VkShaderModule VulkanPipelineService::createShaderModule(const std::vector<char>& spirvBytecode) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = spirvBytecode.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(spirvBytecode.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(_logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

void VulkanPipelineService::createGraphicsPipeline() {
    std::vector<char> vertShader = FileLoadingService::readFile(_app, "Resources/Shaders/vert.spv");
    std::vector<char> fragShader = FileLoadingService::readFile(_app, "Resources/Shaders/frag.spv");
    VkShaderModule vertShaderModule = createShaderModule(vertShader);
    VkShaderModule fragShaderModule = createShaderModule(fragShader);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    //this describes to Vulkan how to pass data to the vertex shader.
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)_swapChainExtent.width;
    viewport.height = (float)_swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    _ubo = { glm::lookAt(glm::vec3(40.0f, 40.0f, 56.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::perspective(glm::radians(90.0f), (float)_width / (float)_height, 0.1f, 65565.0f) };
    _ubo.proj[1][1] *= -1;
    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = _swapChainExtent;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f; // Optional
    rasterizer.depthBiasClamp = 0.0f; // Optional
    rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f; // Optional
    multisampling.pSampleMask = nullptr; // Optional
    multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
    multisampling.alphaToOneEnable = VK_FALSE; // Optional

    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable = VK_TRUE;
    depthStencil.depthWriteEnable = VK_TRUE;
    depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
    depthStencil.depthBoundsTestEnable = VK_FALSE;
    depthStencil.stencilTestEnable = VK_FALSE;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &_descriptorSetLayout;

    if (vkCreatePipelineLayout(_logicalDevice, &pipelineLayoutInfo, nullptr, &_pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = &depthStencil; // Optional
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = nullptr; // Optional
    pipelineInfo.layout = _pipelineLayout;
    pipelineInfo.renderPass = _renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
    pipelineInfo.basePipelineIndex = -1; // Optional

    if (vkCreateGraphicsPipelines(_logicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    vkDestroyShaderModule(_logicalDevice, fragShaderModule, nullptr);
    vkDestroyShaderModule(_logicalDevice, vertShaderModule, nullptr);
}

void VulkanPipelineService::createFrameBuffers() {
    _swapChainFramebuffers.resize(_swapChainImageViews.size());

    for (size_t i = 0; i < _swapChainImageViews.size(); i++) {
        std::array<VkImageView, 2> attachments = {
            _swapChainImageViews[i],
            _depthImageView
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = _renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = _swapChainExtent.width;
        framebufferInfo.height = _swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(_logicalDevice, &framebufferInfo, nullptr, &_swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

VkFormat VulkanPipelineService::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
    for (VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(_physicalDevice, format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            return format;
        }
        else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    throw std::runtime_error("failed to find supported format!");
}

VkFormat VulkanPipelineService::findDepthFormat() {
    return findSupportedFormat(
        { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
}

bool VulkanPipelineService::hasStencilComponent(VkFormat format) {
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

void VulkanPipelineService::createDepthResources() {
    VkFormat depthFormat = findDepthFormat();
    createImage(_swapChainExtent.width, _swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _depthImage, _depthImageMemory);
    _depthImageView = createImageView(_depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}

void VulkanPipelineService::createCommandPool() {
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(_physicalDevice);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    poolInfo.flags = 0; // Optional

    if (vkCreateCommandPool(_logicalDevice, &poolInfo, nullptr, &_commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void VulkanPipelineService::createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) {
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = usage;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateImage(_logicalDevice, &imageInfo, nullptr, &image) != VK_SUCCESS) {
        throw std::runtime_error("failed to create image!");
    }

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(_logicalDevice, image, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(_logicalDevice, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate image memory!");
    }

    vkBindImageMemory(_logicalDevice, image, imageMemory, 0);
}

void VulkanPipelineService::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(
        commandBuffer,
        sourceStage, destinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
        );

    endSingleTimeCommands(commandBuffer);
}

void VulkanPipelineService::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = { 0, 0, 0 };
    region.imageExtent = {
        width,
        height,
        1
    };

    vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    endSingleTimeCommands(commandBuffer);
}

void VulkanPipelineService::createTextureImage() {
    int texWidth, texHeight, texChannels;


    // Read the file:

    AAsset* file = AAssetManager_open(_app->activity->assetManager,
                                      "Resources/Textures/texture.png", AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);
    stbi_uc* fileContent = new unsigned char[fileLength];

    AAsset_read(file, fileContent, fileLength);
    AAsset_close(file);

    uint32_t imgWidth, imgHeight, n;
    unsigned char* pixels = stbi_load_from_memory(
            fileContent, fileLength, reinterpret_cast<int*>(&texWidth),
            reinterpret_cast<int*>(&texHeight), reinterpret_cast<int*>(&n), 4);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    assert(n == 4);
    if (!pixels) {
        throw std::runtime_error("failed to load texture image! Reason: " + std::string(stbi_failure_reason()));
    }

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(_logicalDevice, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vkUnmapMemory(_logicalDevice, stagingBufferMemory);

    stbi_image_free(pixels);

    createImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _textureImage, _textureImageMemory);

    transitionImageLayout(_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(stagingBuffer, _textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    transitionImageLayout(_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vkDestroyBuffer(_logicalDevice, stagingBuffer, nullptr);
    vkFreeMemory(_logicalDevice, stagingBufferMemory, nullptr);
}

void VulkanPipelineService::createTextureImageView() {
    _textureImageView = createImageView(_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
}

void VulkanPipelineService::createTextureSampler() {
    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = 16.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;


    if (vkCreateSampler(_logicalDevice, &samplerInfo, nullptr, &_textureSampler) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture sampler!");
    }
}

uint32_t VulkanPipelineService::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void VulkanPipelineService::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory, void* data) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(_logicalDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(_logicalDevice, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(_logicalDevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    if (data != nullptr)
    {
        void* mapped;
        vkMapMemory(_logicalDevice, bufferMemory, 0, size, 0, &mapped);
        memcpy(mapped, data, size);
        // If host coherency hasn't been requested, do a manual flush to make writes visible
        if ((properties & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0)
        {
            VkMappedMemoryRange mappedRange = mappedMemoryRange();
            mappedRange.memory = bufferMemory;
            mappedRange.offset = 0;
            mappedRange.size = size;
            vkFlushMappedMemoryRanges(_logicalDevice, 1, &mappedRange);
        }
        vkUnmapMemory(_logicalDevice, bufferMemory);
    }

    vkBindBufferMemory(_logicalDevice, buffer, bufferMemory, 0);
}

VkCommandBuffer VulkanPipelineService::beginSingleTimeCommands()
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = _commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(_logicalDevice, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void VulkanPipelineService::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
    vkEndCommandBuffer(commandBuffer);
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(_graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(_graphicsQueue);

    vkFreeCommandBuffers(_logicalDevice, _commandPool, 1, &commandBuffer);
}


void VulkanPipelineService::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    endSingleTimeCommands(commandBuffer);
}

void VulkanPipelineService::createVertexBuffer() {
    VkDeviceSize bufferSize = sizeof(_vertices[0]) * _vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(_logicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, _vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(_logicalDevice, stagingBufferMemory);

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _vertexBuffer, _vertexBufferMemory);

    copyBuffer(stagingBuffer, _vertexBuffer, bufferSize);

    vkDestroyBuffer(_logicalDevice, stagingBuffer, nullptr);
    vkFreeMemory(_logicalDevice, stagingBufferMemory, nullptr);
}

void VulkanPipelineService::createIndexBuffer() {
    VkDeviceSize bufferSize = sizeof(_indices[0]) * _indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(_logicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, _indices.data(), (size_t)bufferSize);
    vkUnmapMemory(_logicalDevice, stagingBufferMemory);

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _indexBuffer, _indexBufferMemory);

    copyBuffer(stagingBuffer, _indexBuffer, bufferSize);

    vkDestroyBuffer(_logicalDevice, stagingBuffer, nullptr);
    vkFreeMemory(_logicalDevice, stagingBufferMemory, nullptr);
}

void VulkanPipelineService::createUniformBuffers() {
    VkDeviceSize cameraBufferSize = sizeof(CameraBufferObject);

    _cameraBuffers.resize(_swapChainImages.size());
    _cameraBuffersMemory.resize(_swapChainImages.size());

    for (size_t i = 0; i < _swapChainImages.size(); i++) {
        createBuffer(cameraBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _cameraBuffers[i], _cameraBuffersMemory[i]);
    }

    _transformBuffers.resize(_swapChainImages.size());
    _transformBuffersMemory.resize(_swapChainImages.size());
    VkPhysicalDeviceProperties props{};
    vkGetPhysicalDeviceProperties(_physicalDevice, &props);

    size_t minUboAlignment = props.limits.minUniformBufferOffsetAlignment;
    _dynamicAlignment = sizeof(glm::mat4);

    if (minUboAlignment > 0) {
        _dynamicAlignment = (_dynamicAlignment + minUboAlignment - 1) & ~(minUboAlignment - 1);
    }

    VkDeviceSize transformBufferSize = _voxelInstanceCount * _dynamicAlignment;


    glm::mat4* temp = (glm::mat4*)alignedAlloc(transformBufferSize, _dynamicAlignment);

    uint32_t dim = static_cast<uint32_t>(pow(_transformData.size(), (1.0f / 3.0f)));
    glm::vec3 offset(5.0f);

    for (uint32_t x = 0; x < dim; x++)
    {
        for (uint32_t y = 0; y < dim; y++)
        {
            for (uint32_t z = 0; z < dim; z++)
            {
                uint32_t index = x * dim * dim + y * dim + z;
                auto fuck = *(glm::mat4*)(((uint64_t)temp + (index * _dynamicAlignment)));
                // Aligned offset
                *(glm::mat4*)(((uint64_t)temp + (index * _dynamicAlignment))) = _transformData[index];
            }
        }
    }

    for (size_t i = 0; i < _swapChainImages.size(); i++) {
        createBuffer(transformBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, _transformBuffers[i], _transformBuffersMemory[i], temp);
    }

    VkDeviceSize lightPosBufferSize = sizeof(glm::vec3);

    _lightPosBuffers.resize(_swapChainImages.size());
    _lightPosBuffersMemory.resize(_swapChainImages.size());

    for (size_t i = 0; i < _swapChainImages.size(); i++) {
        createBuffer(lightPosBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _lightPosBuffers[i], _lightPosBuffersMemory[i]);
    }
}

void VulkanPipelineService::createDescriptorPool() {
    std::array<VkDescriptorPoolSize, 4> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(_swapChainImages.size());
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(_swapChainImages.size());
    poolSizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    poolSizes[2].descriptorCount = static_cast<uint32_t>(_swapChainImages.size());
    poolSizes[3].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[3].descriptorCount = static_cast<uint32_t>(_swapChainImages.size());

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(_swapChainImages.size());

    if (vkCreateDescriptorPool(_logicalDevice, &poolInfo, nullptr, &_descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void VulkanPipelineService::createDescriptorSets() {
    std::vector<VkDescriptorSetLayout> layouts(_swapChainImages.size(), _descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = _descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(_swapChainImages.size());
    allocInfo.pSetLayouts = layouts.data();

    _descriptorSets.resize(_swapChainImages.size());
    if (vkAllocateDescriptorSets(_logicalDevice, &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < _swapChainImages.size(); i++) {
        VkDescriptorBufferInfo cameraBufferInfo{};
        cameraBufferInfo.buffer = _cameraBuffers[i];
        cameraBufferInfo.offset = 0;
        cameraBufferInfo.range = sizeof(CameraBufferObject);

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = _textureImageView;
        imageInfo.sampler = _textureSampler;

        VkDescriptorBufferInfo transformBufferInfo{};
        transformBufferInfo.buffer = _transformBuffers[i];
        transformBufferInfo.offset = 0;
        transformBufferInfo.range = sizeof(glm::mat4);

        VkDescriptorBufferInfo lightPosBufferInfo{};
        lightPosBufferInfo.buffer = _lightPosBuffers[i];
        lightPosBufferInfo.offset = 0;
        lightPosBufferInfo.range = sizeof(glm::vec3);

        std::array<VkWriteDescriptorSet, 4> descriptorWrites{};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = _descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &cameraBufferInfo;
        descriptorWrites[0].pImageInfo = nullptr; // Optional
        descriptorWrites[0].pTexelBufferView = nullptr; // Optional

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = _descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;

        descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[2].dstSet = _descriptorSets[i];
        descriptorWrites[2].dstBinding = 2;
        descriptorWrites[2].dstArrayElement = 0;
        descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        descriptorWrites[2].descriptorCount = 1;
        descriptorWrites[2].pBufferInfo = &transformBufferInfo;
        descriptorWrites[2].pImageInfo = nullptr; // Optional
        descriptorWrites[2].pTexelBufferView = nullptr; // Optional

        descriptorWrites[3].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[3].dstSet = _descriptorSets[i];
        descriptorWrites[3].dstBinding = 3;
        descriptorWrites[3].dstArrayElement = 0;
        descriptorWrites[3].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[3].descriptorCount = 1;
        descriptorWrites[3].pBufferInfo = &lightPosBufferInfo;
        descriptorWrites[3].pImageInfo = nullptr; // Optional
        descriptorWrites[3].pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(_logicalDevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
}

void VulkanPipelineService::createCommandBuffers() {
    _commandBuffers.resize(_swapChainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = _commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)_commandBuffers.size();

    if (vkAllocateCommandBuffers(_logicalDevice, &allocInfo, _commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }

    for (size_t i = 0; i < _commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(_commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = _renderPass;
        renderPassInfo.framebuffer = _swapChainFramebuffers[i];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = _swapChainExtent;

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
        clearValues[1].depthStencil = { 1.0f, 0 };

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicsPipeline);

        VkBuffer vertexBuffers[] = { _vertexBuffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(_commandBuffers[i], 0, 1, vertexBuffers, offsets);

        vkCmdBindIndexBuffer(_commandBuffers[i], _indexBuffer, 0, VK_INDEX_TYPE_UINT16);



        for (size_t j = 0; j < _voxelInstanceCount; j++) {
            uint32_t dynamicOffset = j * static_cast<uint32_t>(_dynamicAlignment);
            vkCmdBindDescriptorSets(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 0, 1, &_descriptorSets[i], 1, &dynamicOffset);
            vkCmdDrawIndexed(_commandBuffers[i], static_cast<uint32_t>(_indices.size()), 1, 0, 0, 0);
        }



        vkCmdEndRenderPass(_commandBuffers[i]);

        if (vkEndCommandBuffer(_commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}

void VulkanPipelineService::createSyncObjects() {
    _imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    _renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    _inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    _imagesInFlight.resize(_swapChainImages.size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        if (vkCreateSemaphore(_logicalDevice, &semaphoreInfo, nullptr, &_imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(_logicalDevice, &semaphoreInfo, nullptr, &_renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(_logicalDevice, &fenceInfo, nullptr, &_inFlightFences[i]) != VK_SUCCESS) {

            throw std::runtime_error("Failed to create synchronisation objects for a frame!");
        }
    }

}

void VulkanPipelineService::cleanupSwapChain() {
    vkDestroyImageView(_logicalDevice, _depthImageView, nullptr);
    vkDestroyImage(_logicalDevice, _depthImage, nullptr);
    vkFreeMemory(_logicalDevice, _depthImageMemory, nullptr);
    
    for (auto framebuffer : _swapChainFramebuffers) {
        vkDestroyFramebuffer(_logicalDevice, framebuffer, nullptr);
    }
    
    vkFreeCommandBuffers(_logicalDevice, _commandPool, static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());

    vkDestroyPipeline(_logicalDevice, _graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(_logicalDevice, _pipelineLayout, nullptr);
    vkDestroyRenderPass(_logicalDevice, _renderPass, nullptr);

    for (auto imageView : _swapChainImageViews) {
        vkDestroyImageView(_logicalDevice, imageView, nullptr);
    }

    vkDestroySwapchainKHR(_logicalDevice, swapChain, nullptr);

    for (size_t i = 0; i < _swapChainImages.size(); i++) {
        vkDestroyBuffer(_logicalDevice, _cameraBuffers[i], nullptr);
        vkFreeMemory(_logicalDevice, _cameraBuffersMemory[i], nullptr);
        vkDestroyBuffer(_logicalDevice, _transformBuffers[i], nullptr);
        vkFreeMemory(_logicalDevice, _transformBuffersMemory[i], nullptr);
        vkDestroyBuffer(_logicalDevice, _lightPosBuffers[i], nullptr);
        vkFreeMemory(_logicalDevice, _lightPosBuffersMemory[i], nullptr);
    }

    vkDestroyDescriptorPool(_logicalDevice, _descriptorPool, nullptr);
}

void VulkanPipelineService::recreateSwapChain() {
    vkDeviceWaitIdle(_logicalDevice);

    cleanupSwapChain();

    createSwapChain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline();
    createDepthResources();
    createFrameBuffers();
    createUniformBuffers();
    createDescriptorPool();
    createDescriptorSets();
    createCommandBuffers();
}

void VulkanPipelineService::initVulkan(android_app* app) {
    _app = app;
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    createImageViews();
    createRenderPass();
    createDescriptorSetLayout();
    createGraphicsPipeline();
    createCommandPool();
    createDepthResources();
    createFrameBuffers();
    createTextureImage();
    createTextureImageView();
    createTextureSampler();
    createVertexBuffer();
    createIndexBuffer();
    createUniformBuffers();
    createDescriptorPool();
    createDescriptorSets();
    createCommandBuffers();
    createSyncObjects();
    _initialised = true;
}

void VulkanPipelineService::updateCameraUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();
    static auto previousTime = std::chrono::high_resolution_clock::now();
    static std::chrono::duration<float, std::chrono::seconds::period> delta;
    auto currentTime = std::chrono::high_resolution_clock::now();
    delta = currentTime - previousTime;
    float time = delta.count();

    //should be 12, 12, 20
    _ubo.view = glm::rotate(_ubo.view, time * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //glm::lookAt(glm::vec3(40.0f, 40.0f, 56.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    _ubo.proj = glm::perspective(glm::radians(90.0f), _swapChainExtent.width / (float)_swapChainExtent.height, 0.1f, 65565.0f);
    _ubo.proj[1][1] *= -1;
    void* data;
    vkMapMemory(_logicalDevice, _cameraBuffersMemory[currentImage], 0, sizeof(_ubo), 0, &data);
    memcpy(data, &_ubo, sizeof(_ubo));
    vkUnmapMemory(_logicalDevice, _cameraBuffersMemory[currentImage]);

    previousTime = std::chrono::high_resolution_clock::now();
}

void VulkanPipelineService::updateTransformUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();
    static auto previousTime = std::chrono::high_resolution_clock::now();
    static std::chrono::duration<float, std::chrono::seconds::period> delta;
    auto currentTime = std::chrono::high_resolution_clock::now();
    delta = currentTime - previousTime;
    float time = delta.count();
    //for (size_t j = 0; j < _transformData.size(); j++)
    //{
    //    _transformData[j] = glm::rotate(_transformData[j], time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //}

    //_transformData[5] = glm::rotate(_transformData[5], time * glm::radians(0.2f), glm::vec3(0.0f, 0.0f, 1.0f));

    uint32_t transformCollectionSize = sizeof(glm::mat4) * static_cast<uint32_t>(_transformData.size());
    void* data;
    vkMapMemory(_logicalDevice, _transformBuffersMemory[currentImage], 0, transformCollectionSize, 0, &data);
    memcpy(data, _transformData.data(), transformCollectionSize);
    vkUnmapMemory(_logicalDevice, _transformBuffersMemory[currentImage]);

    previousTime = std::chrono::high_resolution_clock::now();
}

void VulkanPipelineService::updateLightPosUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    //12, 12, 20
    //_transformData[0] = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::vec3 lightPos(4.0f, 4.0f, 4.0f);
    uint32_t transformCollectionSize = sizeof(glm::vec3);
    void* data;
    vkMapMemory(_logicalDevice, _lightPosBuffersMemory[currentImage], 0, transformCollectionSize, 0, &data);
    memcpy(data, &lightPos, transformCollectionSize);
    vkUnmapMemory(_logicalDevice, _lightPosBuffersMemory[currentImage]);
}

void VulkanPipelineService::drawFrame() {
    vkWaitForFences(_logicalDevice, 1, &_inFlightFences[_currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(_logicalDevice, swapChain, UINT64_MAX, _imageAvailableSemaphores[_currentFrame], VK_NULL_HANDLE, &imageIndex);

    bool reset = false;

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _frameBufferResized) {
        reset = true;
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }


    if (_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(_logicalDevice, 1, &_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }

    _imagesInFlight[imageIndex] = _inFlightFences[_currentFrame];

    updateCameraUniformBuffer(imageIndex);
    //updateTransformUniformBuffer(imageIndex);
    //updateDynamicUniformBuffer(imageIndex);
    updateLightPosUniformBuffer(imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { _imageAvailableSemaphores[_currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &_commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = { _renderFinishedSemaphores[_currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(_logicalDevice, 1, &_inFlightFences[_currentFrame]);

    if (vkQueueSubmit(_graphicsQueue, 1, &submitInfo, _inFlightFences[_currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { swapChain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(_presentQueue, &presentInfo);

    _currentFrame = (_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

    if (reset) {
        _frameBufferResized = false;
        recreateSwapChain();
    }
}

void VulkanPipelineService::mainLoop() {
/*    while (!glfwWindowShouldClose(_window.get())) {
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(_logicalDevice);*/
}

void VulkanPipelineService::cleanup() {
    _initialised = false;
    cleanupSwapChain();

    vkDestroySampler(_logicalDevice, _textureSampler, nullptr);
    vkDestroyImageView(_logicalDevice, _textureImageView, nullptr);

    vkDestroyImage(_logicalDevice, _textureImage, nullptr);
    vkFreeMemory(_logicalDevice, _textureImageMemory, nullptr);

    vkDestroyDescriptorSetLayout(_logicalDevice, _descriptorSetLayout, nullptr);

    vkDestroyBuffer(_logicalDevice, _vertexBuffer, nullptr);
    vkFreeMemory(_logicalDevice, _vertexBufferMemory, nullptr);

    vkDestroyBuffer(_logicalDevice, _indexBuffer, nullptr);
    vkFreeMemory(_logicalDevice, _indexBufferMemory, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(_logicalDevice, _renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(_logicalDevice, _imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(_logicalDevice, _inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(_logicalDevice, _commandPool, nullptr);

    vkDestroyDevice(_logicalDevice, nullptr);

    if (_enableValidationLayers) {
        destroyDebugUtilsMessengerEXTViaProcAddress(_instance, _debugMessenger, nullptr);
    }

    vkDestroySurfaceKHR(_instance, _surface, nullptr);
    vkDestroyInstance(_instance, nullptr);
}

VulkanPipelineService::VulkanPipelineService() noexcept : _app(nullptr),  _debugMessenger(VK_NULL_HANDLE), _instance(VK_NULL_HANDLE), _physicalDevice(VK_NULL_HANDLE) {

}

void VulkanPipelineService::launch() {
/*    initVoxelData();
    initVulkan();
    mainLoop();
    cleanup();*/
}
