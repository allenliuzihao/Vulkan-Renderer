#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

// this shader runs in a subpass of a render pass
// subpass might have multiple references to render pass attachments
// the location = i here means fragment shader would output color
// to subpass's ith reference to render pass's color attachments.
layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

void main(){
    outColor = texture(texSampler, fragTexCoord);
}
