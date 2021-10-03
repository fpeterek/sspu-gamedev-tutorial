#version 400

uniform vec2 sunPosition;
uniform float groundLevel;
uniform vec3 sunColor;
uniform sampler2D texture;

layout(location=0) in fragPosition;

void main() {

    float sunRadius = 50;
    float nightCoefficient = 0.6;

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 color = (gl_Color * pixel);

    if (sunPosition.y > groundLevel) {
        color = color * nightCoefficient;
    }

    if (sunPosition.y < groundLevel-12) {
        float dx = sunPosition.x - fragPosition.x;
        float dy = sunPosition.y - fragPosition.y;
        float dist = sqrt(dx*dx + dy*dy);

    }

    gl_FragColor = color;
}
