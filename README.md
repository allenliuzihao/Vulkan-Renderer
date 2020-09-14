# Vulkan_First_Project
Vulkan project from the tutorial at: https://vulkan-tutorial.com/, with some experimentations.

## Triangle

Getting this triangle on screen involves several concepts in Vulkan, including surface, swapchain, renderpass, framebuffers, fences and semaphores, index and vertex buffers, push constants and descriptor sets.

### Resizable Window

Baremetal swapchain resize by detecting window changes and then recreate swapchain with new extent.

![small](triangle_resize_small.png)
![large](triangle_resize_large.png)


### Index Buffer Draw

![rectangle](rectangle.png)


### Descriptor Sets and Push Constants

For this milestone I added descriptor sets support for view and projection matrices, and push constant for model update so that the rectangle can spin around. 

![descriptor_set_push_constant_1](descriptor_set_push_constant_1.png)
![descriptor_set_push_constant_2](descriptor_set_push_constant_2.png)
