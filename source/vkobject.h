/*
 * vkobject.h
 *
 *  Created on: 2021年7月10日
 *      Author: calvin.fong
 */

#ifndef VKOBJECT_H_
#define VKOBJECT_H_

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#define Clamp(x, minValue, maxValue)	((x)>(minValue))?((x)<(maxValue)?(x):(maxValue)):(minValue)

// Should use built-in in C++17
template <typename T>
class optional
{
public:
	optional() : m_hasValue(false), m_value((T)0) {}
	~optional() {}

	bool	has_value() 		{ return m_hasValue; }
	T& value() &				{ return m_value; }
	const T& value() const& { return m_value; }

	optional<T>& operator= (const T& rhs)	{ m_value = rhs; m_hasValue = true; }
	const bool operator!= (const optional<T>& rhs)	{ return (rhs.value()!=m_value); }

private:
	bool	m_hasValue;
	T		m_value;
};

struct QueueFamilyIndices {
	optional<uint32_t> graphicsFamily;
	optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class VKObject {
public:
	void run();

private:
	GLFWwindow*		m_window;

	VkDevice 		m_device;
	VkInstance 		m_instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR	m_surface;

	VkQueue			m_graphicsQueue;
	VkQueue			m_presentQueue;

	VkCommandPool						m_commandPool;
	std::vector<VkCommandBuffer>	m_commandBuffers;

	VkPhysicalDevice	m_physicalDevice = VK_NULL_HANDLE;

	VkSwapchainKHR		m_swapChain;
	VkRenderPass 		m_renderPass;
	VkPipelineLayout	m_pipelineLayout;
	VkPipeline 			m_graphicsPipeline;

	VkFormat				m_swapChainImageFormat;
	VkExtent2D			m_swapChainExtent;

	std::vector<VkImage>			m_swapChainImages;
	std::vector<VkImageView>	m_swapChainImageViews;
	std::vector<VkFramebuffer>	m_swapChainFramebuffers;
	std::vector<VkSemaphore>	m_imageAvailableSemaphores;
	std::vector<VkSemaphore>	m_renderFinishedSemaphores;
	std::vector<VkFence>			m_inFlightFences;
	std::vector<VkFence>			m_imagesInFlight;

	size_t 							m_currentFrame = 0;

	void initWindow(uint32_t width, uint32_t height);
	void initVulkan();
	void mainLoop();
	void cleanup();

	void createInstance();
	void setupDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createSyncObjects();

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	void drawFrame();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	static std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);
};

inline void VKObject::run()
{
	initWindow(800, 600);
	initVulkan();
	mainLoop();
	cleanup();
}

inline void VKObject::initWindow(uint32_t width, uint32_t height)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
}


inline void VKObject::initVulkan()
{
	createInstance();
	setupDebugMessenger();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();
	createSwapChain();
	createImageViews();
	createRenderPass();
	createGraphicsPipeline();
	createFramebuffers();
	createCommandPool();
	createCommandBuffers();
	createSyncObjects();
}

#endif /* VKOBJECT_H_ */
