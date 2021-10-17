varying out vec2 vertexPosition;

void main() {
    gl_FrontColor = gl_Color;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vertexPosition = vec2(gl_Position);

    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}


/*
#version 410

layout(location=0) in vec3 position;
layout(location=1) in vec4 color;
layout(location=2) in vec2 textureCoord;

uniform mat4 transform;

out vec3 vertexColor;
out vec2 vertexPosition;
out vec2 vertexTexCoord;

void main() {
    // transform the vertex position
    gl_Position = transform * vec4(position,  1.0);

    vertexColor = vec3(color);
    vertexPosition = vec2(gl_Position.x, gl_Position.y);
    vertexTexCoord = textureCoord;
}
*/
