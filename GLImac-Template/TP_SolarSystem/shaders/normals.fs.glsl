#version 330 core

in vec3 vPosition_vs; // Position du sommet
in vec3 vNormal_vs; // Normale du sommet
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

void main() {
    fFragColor = normalize(vNormal_vs);
}