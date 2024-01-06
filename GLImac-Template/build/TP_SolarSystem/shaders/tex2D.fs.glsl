#version 330 core

in vec2 vFragCoordinates;

out vec4 fFragCoordinates;

void main() {
    fFragCoordinates = vec4(vFragCoordinates, 0, 0);
}