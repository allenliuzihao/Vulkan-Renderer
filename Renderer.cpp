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
    std::vector<vk::LayerProperties> layers = vk::enumerateInstanceLayerProperties();
    std::unordered_set<std::string> supportedLayers;
    for(const auto & layer : layers){
        supportedLayers.insert(layer.layerName);
    }
    
    for(const auto & layerName : validationLayers){
        if(supportedLayers.find(layerName) == supportedLayers.end()){
            return false;
        }
    }
    
    return true;
}

bool Renderer::checkExtensionsSupport(const std::vector<const char*> & requiredExtensions){
    std::vector<vk::ExtensionProperties> extensions = vk::enumerateInstanceExtensionProperties();
    std::unordered_set<std::string> supportedExtensions;
    for(const auto & extension : extensions){
        supportedExtensions.insert(extension.extensionName);
    }
    
    for(const auto & requiredExtension : requiredExtensions){
        if(supportedExtensions.find(requiredExtension) == supportedExtensions.end()){
            return false;
        }
    }
    
    return true;
}
