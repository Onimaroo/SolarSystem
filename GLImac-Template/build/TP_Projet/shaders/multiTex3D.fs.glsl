#version 330 core

in vec3 vPosition_vs; // Position du sommet
in vec3 vNormal_vs; // Normale du sommet
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

void main() {
    vec4 texture_earth = texture(uEarthTexture, vTexCoords);
    vec4 texture_cloud = texture(uCloudTexture, vTexCoords);

    fFragColor = normalize(vNormal_vs);
    fFragColor = texture_earth.xyz + texture_cloud.xyz;
}