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
    
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    if(!checkExtensionsSupport(glfwExtensions, glfwExtensionCount)){
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
    
    vk::InstanceCreateInfo instanceInfo({}, &appInfo, numLayers, enabledLayerNames, glfwExtensionCount, glfwExtensions);
    instance = vk::createInstanceUnique(instanceInfo);
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

bool Renderer::checkExtensionsSupport(const char** glfwExtensions, uint32_t glfwExtensionCount){
    std::vector<vk::ExtensionProperties> extensions = vk::enumerateInstanceExtensionProperties();
    std::unordered_set<std::string> supportedExtensions;
    for(const auto & extension : extensions){
        supportedExtensions.insert(extension.extensionName);
    }
    
    for(uint32_t i = 0; i < glfwExtensionCount; ++i){
        if(supportedExtensions.find(glfwExtensions[i]) == supportedExtensions.end()){
            return false;
        }
    }
    
    return true;
}
