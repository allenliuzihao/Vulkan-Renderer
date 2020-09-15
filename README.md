# Vulkan_First_Project
Vulkan project from the tutorial at: https://vulkan-tutorial.com/, with some experimentations.

## Triangle

Getting this triangle on screen involves several concepts in Vulkan, including surface, swapchain, renderpass, framebuffers, fences and semaphores, index and vertex buffers, push constants and descriptor sets, and texture mapping.

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


### Texture mapping

I added functionaltiy to: 1) load images from CPU buffer to GPU texture memory while handling image layout transitions, 2) pass texture image as descriptors and descriptor sets to graphics pipeline for shader read, 3) create texture sampler to sample textures from the fragment shader. 

![texture1](images/texture1.png)
![texture2](images/texture2.png)
