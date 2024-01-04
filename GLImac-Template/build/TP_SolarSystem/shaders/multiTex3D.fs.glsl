#version 330 core

in vec3 vPosition_vs; // Position du sommet
in vec3 vNormal_vs; // Normale du sommet
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform sampler2D uFirstTexture;
uniform sampler2D uSecondTexture;

void main() {
    vec4 first_texture = texture(uFirstTexture, vTexCoords);
    vec4 second_texture = texture(uSecondTexture, vTexCoords);

    fFragColor = normalize(vNormal_vs);
    fFragColor = first_texture.xyz + second_texture.xyz;
}