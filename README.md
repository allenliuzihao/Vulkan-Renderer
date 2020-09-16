# Vulkan_First_Project

A simple vulkan project adapted from: https://vulkan-tutorial.com/, with some of my own experimentations. The program runs on macOS 10.15.6 with 2.7 GHz Quad-Core Intel Core i5 CPU processor, 8GB 1600 MHz DDR3 memory, and Intel Iris Pro 1536 MB integrated GPU.

## Triangle

Getting this triangle on screen involves several concepts in Vulkan, including surface, swapchain, renderpass, framebuffers, fences and semaphores, index and vertex buffers, push constants and descriptor sets, texture mapping, and depth testing.

### Resizable Window

Baremetal swapchain resize by detecting window changes and then recreate swapchain with new extent.

![small](images/triangle_resize_small.png)
![large](images/triangle_resize_large.png)


### Index Buffer Draw

![rectangle](images/rectangle.png)


### Descriptor Sets and Push Constants

For this milestone I added descriptor sets support for view and projection matrices, and push constant for model update so that the rectangle can spin around. 

![descriptor_set_push_constant_1](images/descriptor_set_push_constant_1.png)
![descriptor_set_push_constant_2](images/descriptor_set_push_constant_2.png)


### Texture Mapping

I added functionaltiy to: 1) load images from CPU buffer to GPU texture memory while handling image layout transitions, 2) pass texture image as descriptors and descriptor sets to graphics pipeline for shader read, 3) create texture sampler to sample textures from the fragment shader. 

![texture1](images/texture1.png)
![texture2](images/texture2.png)
![texture3](images/texture3.png)


### Depth Testing

Depth buffering is added to enable the perception of depth to the scene.  Fortunately, depth testing in Vulkan can be enabled through creating and adding depth attachment at the renderpass and enabling depth testing in the graphics pipeline. In addition, the depth buffer needs to be created on GPU for sure. 

![depth_buffer](images/depth_buffer.png)

