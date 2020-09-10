#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;

// framebuffer with index 0 is written to with the outcolor
// the first framebuffer
// in stereographic applications, multiple output ports can be
// specified for each image view as separate framebuffers
// so fragment shader can output to two frames at a time.
layout(location = 0) out vec4 outColor;

void main(){
    outColor = vec4(fragColor, 1.0);
}
