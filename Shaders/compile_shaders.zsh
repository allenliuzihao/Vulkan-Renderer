export VULKAN_SDK="/Users/zihaoliu/Desktop/After Grad/learning/Vulkan_API/VulkanSDK"

"$VULKAN_SDK"/macOS/bin/glslangValidator -V shader.vert
"$VULKAN_SDK"/macOS/bin/glslangValidator -V shader.frag

"$VULKAN_SDK"/macOS/bin/glslangValidator -o second_vert.spv -V second.vert
"$VULKAN_SDK"/macOS/bin/glslangValidator -o second_frag.spv -V second.frag
