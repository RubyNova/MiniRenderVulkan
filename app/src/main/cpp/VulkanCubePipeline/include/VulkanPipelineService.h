#ifndef VULKANPIPELINESERVICE_H
#define VULKANPIPELINESERVICE_H

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>
#include <stdio.h>
#include <stdlib.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "../../ThirdParty/glm/glm/glm.hpp"
#include "../../ThirdParty/glm/glm/gtc/quaternion.hpp"
#include "../../ThirdParty/glm/glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <android_native_app_glue.h>
#include "../../ThirdParty/jsoncpp/include/json/json.h"

#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "FileLoadingService.h"
#include "Vertex.h"
#include "CameraBufferObject.h"

inline VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

class VulkanPipelineService {
private:
    android_app* _app;
	CameraBufferObject _ubo{ glm::lookAt(glm::vec3(40.0f, 40.0f, 56.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::perspective(glm::radians(90.0f), _swapChainExtent.width / (float)_swapChainExtent.height, 0.1f, 65565.0f) };
	const uint32_t _width = 3120 / 2; //TODO: Fix this for my actual screen
	const uint32_t _height = 1440 / 2;
	static inline const int32_t INVALID_PHYISCAL_VK_DEVICE = -1;
	static inline const int32_t MAX_FRAMES_IN_FLIGHT = 2;
	size_t _voxelInstanceCount = 0;
	size_t _currentFrame = 0;
	size_t _dynamicAlignment = 0;

	bool _frameBufferResized = false;
	bool _initialised = false;

	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debugMessenger;
	VkPhysicalDevice _physicalDevice;
	VkDevice _logicalDevice;

	VkQueue _graphicsQueue;
	VkQueue _presentQueue;

	VkSurfaceKHR _surface;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> _swapChainImages;
	VkFormat _swapChainImageFormat;
	VkExtent2D _swapChainExtent;

	std::vector<VkImageView> _swapChainImageViews;

	VkRenderPass _renderPass;
	VkDescriptorSetLayout _descriptorSetLayout;
	VkDescriptorPool _descriptorPool;
	std::vector<VkDescriptorSet> _descriptorSets;
	VkPipelineLayout _pipelineLayout;
	VkPipeline _graphicsPipeline;

	std::vector<VkFramebuffer> _swapChainFramebuffers;

	VkCommandPool _commandPool;

	std::vector<VkCommandBuffer> _commandBuffers;

	std::vector<VkSemaphore> _imageAvailableSemaphores;
	std::vector<VkSemaphore> _renderFinishedSemaphores;
	std::vector<VkFence> _inFlightFences;
	std::vector<VkFence> _imagesInFlight;

	VkBuffer _vertexBuffer;
	VkDeviceMemory _vertexBufferMemory;

	VkBuffer _indexBuffer;
	VkDeviceMemory _indexBufferMemory;

	std::vector<VkBuffer> _cameraBuffers;
	std::vector<VkDeviceMemory> _cameraBuffersMemory;

	std::vector<VkBuffer> _transformBuffers;
	std::vector<VkDeviceMemory> _transformBuffersMemory;

	std::vector<VkBuffer> _lightPosBuffers;
	std::vector<VkDeviceMemory> _lightPosBuffersMemory;

	VkImage _textureImage;
	VkDeviceMemory _textureImageMemory;

	VkImageView _textureImageView;
	VkSampler _textureSampler;

	VkImage _depthImage;
	VkDeviceMemory _depthImageMemory;
	VkImageView _depthImageView;

	const std::vector<const char*> _validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> _deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const glm::vec3 v[8] = {
			{ +0.5f, +0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ -0.5f, +0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{ -0.5f, +0.5f, +0.5f },
			{ -0.5f, -0.5f, +0.5f },
	};

	const glm::vec2 vTexture[20] = {
		{ +1.0f, +1.0f },
		{ +0.0f, +0.0f },
		{ +0.0f, +1.0f },
		{ +1.0f, +0.0f },
	};

	const glm::vec3 vNormal[6] = {
		{ +0.0f, +1.0f, +0.0f },
		{ +0.0f, +0.0f, +1.0f },
		{ -1.0f, +0.0f, +0.0f },
		{ +0.0f, -1.0f, +0.0f },
		{ +1.0f, +0.0f, +0.0f },
		{ +0.0f, +0.0f, -1.0f },
	};

	const std::vector<Vertex> _vertices = {
		{ v[4], { +0.0f, +0.0f, +0.0f }, vTexture[0], vNormal[0] },
		{ v[2], { +0.0f, +0.0f, +0.0f }, vTexture[1], vNormal[0] },
		{ v[0], { +0.0f, +0.0f, +0.0f }, vTexture[2], vNormal[0] },
	    { v[6], { +0.0f, +0.0f, +0.0f }, vTexture[3], vNormal[0] }, //3

		{ v[2], { +0.0f, +0.0f, +0.0f }, vTexture[0], vNormal[1] },
		{ v[7], { +0.0f, +0.0f, +0.0f }, vTexture[1], vNormal[1] },
		{ v[3], { +0.0f, +0.0f, +0.0f }, vTexture[2], vNormal[1] },
	    { v[6], { +0.0f, +0.0f, +0.0f }, vTexture[3], vNormal[1] }, //7

		{ v[6], { +0.0f, +0.0f, +0.0f }, vTexture[1], vNormal[2] },
		{ v[5], { +0.0f, +0.0f, +0.0f }, vTexture[0], vNormal[2] },
		{ v[7], { +0.0f, +0.0f, +0.0f }, vTexture[3], vNormal[2] },
		{ v[4], { +0.0f, +0.0f, +0.0f }, vTexture[2], vNormal[2] }, //11

		{ v[1], { +0.0f, +0.0f, +0.0f }, vTexture[0], vNormal[3] },
		{ v[7], { +0.0f, +0.0f, +0.0f }, vTexture[1], vNormal[3] },
		{ v[5], { +0.0f, +0.0f, +0.0f }, vTexture[2], vNormal[3] },
	    { v[3], { +0.0f, +0.0f, +0.0f }, vTexture[3], vNormal[3] }, //15

		{ v[0], { +0.0f, +0.0f, +0.0f }, vTexture[0], vNormal[4] },
		{ v[3], { +0.0f, +0.0f, +0.0f }, vTexture[1], vNormal[4] },
		{ v[1], { +0.0f, +0.0f, +0.0f }, vTexture[2], vNormal[4] },
	    { v[2], { +0.0f, +0.0f, +0.0f }, vTexture[3], vNormal[4] }, //19

		{ v[4], { +0.0f, +0.0f, +0.0f }, vTexture[0], vNormal[5] },
		{ v[1], { +0.0f, +0.0f, +0.0f }, vTexture[1], vNormal[5] },
		{ v[5], { +0.0f, +0.0f, +0.0f }, vTexture[2], vNormal[5] },
		{ v[0], { +0.0f, +0.0f, +0.0f }, vTexture[3], vNormal[5] },
	};

	const std::vector<uint16_t> _indices = {
		0, 1, 2, 0, 3, 1,
		4, 5, 6, 4, 7, 5,
		8, 9, 10, 8, 11, 9,
		12, 13, 14, 12, 15, 13,
		16, 17, 18, 16, 19, 17,
		20, 21, 22, 20, 23, 21
	};
	//std::vector<glm::mat4> _transformData = {
	//	glm::identity<glm::mat4>(),
	//	glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 1.0f, 0.0f))
	//};

	std::vector<glm::mat4> _transformData;

#ifdef NDEBUG
	const bool _enableValidationLayers = false;
#else
	const bool _enableValidationLayers = true;
#endif

	static VkResult createDebugUtilsMessengerEXTViaProcAddress(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	static void destroyDebugUtilsMessengerEXTViaProcAddress(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

	static VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo() {
		VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;
		return createInfo;
	}

/*	static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<VulkanPipelineService*>(glfwGetWindowUserPointer(window));
		app->_frameBufferResized = true;
	}*/

    inline VkMappedMemoryRange mappedMemoryRange()
    {
        VkMappedMemoryRange mappedMemoryRange{};
        mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        return mappedMemoryRange;
    }

	void* alignedAlloc(size_t size, size_t alignment) {
		void* data = nullptr;
#if defined(_MSC_VER) || defined(__MINGW32__)
		data = _aligned_malloc(size, alignment);
#else
		int res = posix_memalign(&data, alignment, size);
		if (res != 0)
			data = nullptr;
#endif
		return data;
	}

	bool checkValidationLayerSupport();
	void createInstance();
	void setupDebugMessenger();

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	int32_t rateDeviceSuitability(VkPhysicalDevice device);

	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSurface();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	void createSwapChain();

	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void createImageViews();

	void createRenderPass();

	void createDescriptorSetLayout();

	VkShaderModule createShaderModule(const std::vector<char>& spirvBytecode);
	void createGraphicsPipeline();

	void createFrameBuffers();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();
	bool hasStencilComponent(VkFormat format);
	void createDepthResources();

	void createCommandPool();

	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void createTextureImage();

	void createTextureImageView();

	void createTextureSampler();

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory, void* data = nullptr);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createVertexBuffer();

	void createIndexBuffer();

	void createUniformBuffers();

	void createDescriptorPool();

	void createDescriptorSets();

	void createCommandBuffers();

	void createSyncObjects();

	void cleanupSwapChain();

	void recreateSwapChain();

	void updateCameraUniformBuffer(uint32_t currentImage);
	void updateTransformUniformBuffer(uint32_t currentImage);
	void updateLightPosUniformBuffer(uint32_t currentImage);
	void drawFrame();

	void mainLoop();



public:
	VulkanPipelineService(android_app* app) noexcept;

    void initVoxelData();
    void initVulkan();
    void cleanup();

	void launch();
};

#endif // !VULKANPIPELINESERVICE_H
