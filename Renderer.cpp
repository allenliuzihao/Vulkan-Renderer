#include "Renderer.hpp"

void Renderer::init(){
    try {
        createInstance();

    }
    catch (vk::SystemError &err){
        std::cerr << "vk::SystemError: " << err.what() << std::endl;
        exit(-1);
    }
    catch (std::exception &err){
        std::cerr << "std::exception: " << err.what() << std::endl;
        exit(-1);
    }
    catch (...){
        std::cerr << "unknown error\n";
        exit(-1);
    }
}

void Renderer::cleanUp(){
    
}

void Renderer::createInstance(){
    vk::ApplicationInfo appInfo("Vulkan Renderer", VK_MAKE_VERSION(1, 0, 0),
                                "No Engine", VK_MAKE_VERSION(1, 0, 0),
                                VK_API_VERSION_1_2);
    
    std::vector<const char*> requiredExtensions = getRequiredExtensions();
    if(!checkExtensionsSupport(requiredExtensions)){
        throw std::runtime_error("failed to create instance: not all requested extensions supported.");
    }
    
    if(enableValidationLayers && !checkValidationLayerSupport()){
        throw std::runtime_error("validation layers requested, but not available!");
    }
    
    uint32_t numLayers = 0;
    const char*const* enabledLayerNames = {};
    if(enableValidationLayers){
        numLayers = static_cast<uint32_t>(validationLayers.size());
        enabledLayerNames = validationLayers.data();
    }
    
    vk::InstanceCreateInfo instanceInfo({}, &appInfo, numLayers, enabledLayerNames, static_cast<uint32_t>(requiredExtensions.size()), requiredExtensions.data());
    instance = vk::createInstanceUnique(instanceInfo);
}

std::vector<const char*> Renderer::getRequiredExtensions(){
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

bool Renderer::checkValidationLayerSupport(){
    std::vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();
    return std::all_of(validationLayers.begin(), validationLayers.end(), [&availableLayers](const char* requiredLayer) {
        return std::find_if(availableLayers.begin(), availableLayers.end(), [&requiredLayer](vk::LayerProperties const & availableLayer){
            return strcmp(availableLayer.layerName, requiredLayer) == 0;
        }) != availableLayers.end();
    });
}

bool Renderer::checkExtensionsSupport(const std::vector<const char*> & requiredExtensions){
    std::vector<vk::ExtensionProperties> availableExtensions = vk::enumerateInstanceExtensionProperties();
    
    return std::all_of(requiredExtensions.begin(), requiredExtensions.end(), [&availableExtensions](const char* requiredExtension) {
        return std::find_if(availableExtensions.begin(), availableExtensions.end(), [&requiredExtension](vk::ExtensionProperties const & availableExtension){
            return strcmp(availableExtension.extensionName, requiredExtension) == 0;
        }) != availableExtensions.end();
    });
}

// adapted from https://github.com/KhronosGroup/Vulkan-Hpp/blob/master/samples/EnableValidationWithCallback/EnableValidationWithCallback.cpp
static VKAPI_ATTR VkBool32 VKAPI_CALL debugMessageFunc(VkDebugUtilsMessageSeverityFlagBitsEXT       messageSeverity,
                                                       VkDebugUtilsMessageTypeFlagsEXT              messageTypes,
                                                       VkDebugUtilsMessengerCallbackDataEXT const * pCallbackData,
                                                       void* pUserData){
    std::string message;
    message += vk::to_string( static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>( messageSeverity ) ) + ": " +
               vk::to_string( static_cast<vk::DebugUtilsMessageTypeFlagsEXT>( messageTypes ) ) + ":\n";
    message += std::string( "\t" ) + "messageIDName   = <" + pCallbackData->pMessageIdName + ">\n";
    message += std::string( "\t" ) + "messageIdNumber = " + std::to_string( pCallbackData->messageIdNumber ) + "\n";
    message += std::string( "\t" ) + "message         = <" + pCallbackData->pMessage + ">\n";
    if ( 0 < pCallbackData->queueLabelCount )
    {
        message += std::string( "\t" ) + "Queue Labels:\n";
        for ( uint8_t i = 0; i < pCallbackData->queueLabelCount; i++ )
        {
            message += std::string( "\t\t" ) + "labelName = <" + pCallbackData->pQueueLabels[i].pLabelName + ">\n";
        }
    }
    if ( 0 < pCallbackData->cmdBufLabelCount )
    {
        message += std::string( "\t" ) + "CommandBuffer Labels:\n";
        for ( uint8_t i = 0; i < pCallbackData->cmdBufLabelCount; i++ )
        {
            message += std::string( "\t\t" ) + "labelName = <" + pCallbackData->pCmdBufLabels[i].pLabelName + ">\n";
        }
    }
    if ( 0 < pCallbackData->objectCount )
    {
        for (uint8_t i = 0; i < pCallbackData->objectCount; i++ )
        {
            message += std::string( "\t" ) + "Object " + std::to_string( i ) + "\n";
            message += std::string( "\t\t" ) + "objectType   = " + vk::to_string( static_cast<vk::ObjectType>( pCallbackData->pObjects[i].objectType ) ) + "\n";
            message += std::string( "\t\t" ) + "objectHandle = " + std::to_string( pCallbackData->pObjects[i].objectHandle ) + "\n";
            if (pCallbackData->pObjects[i].pObjectName )
            {
                message += std::string( "\t\t" ) + "objectName   = <" + pCallbackData->pObjects[i].pObjectName + ">\n";
            }
        }
    }

    std::cout << message << std::endl;
        
    return VK_FALSE;
}
