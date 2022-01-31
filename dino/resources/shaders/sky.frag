uniform vec2 sunPosition;
uniform float groundLevel;
uniform sampler2D texture;

varying in vec2 vertexPosition;

void main() {

    float sunRadius = 75;
    float nightCoefficient = 0.6;

    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    if (sunPosition.y > groundLevel) {
        color = color * nightCoefficient;
    } else {
        // color = vec4((0.6 + color.x) * 1.2, color.y * 0.8, color.z * 0.8, color.w);
    }

    if (sunPosition.y < groundLevel-12) {
        float dx = sunPosition.x - gl_FragCoord.x;
        float dy = sunPosition.y - gl_FragCoord.y;
        float dist = sqrt(dx*dx + dy*dy);

        float sunCoeff = max(min(1.0, sunRadius / dist), 0.1);
        float texCoeff = 1.0 - sunCoeff;

        vec3 sun = vec3(1.0, 0.5, 0.1) * sunCoeff;
        vec3 tex = vec3(color) * texCoeff;

        if (dist < sunRadius) {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }

        color = vec4(sun + tex, color.w);
        // color = vec4(1920 / dist, 1920/dist, 1920/dist, 1.0);

    }

    gl_FragColor = color;
}
