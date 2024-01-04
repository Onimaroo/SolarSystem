#version 330 core

in vec3 vPosition_vs; // Position du sommet
in vec3 vNormal_vs; // Normale du sommet
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
    vec4 texture = texture(uTexture, vTexCoords);
    fFragColor = normalize(vNormal_vs);
    fFragColor = texture.xyz;
}