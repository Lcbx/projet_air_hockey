#version 420

uniform mat4 modelViewProjection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoordIn;

varying vec2 texCoord;

void main()
{
    gl_Position = modelViewProjection * vec4(position, 1.0);
    texCoord = texCoordIn;
}