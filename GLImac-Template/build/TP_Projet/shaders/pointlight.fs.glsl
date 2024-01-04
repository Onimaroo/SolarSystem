#version 330 core

in vec3 vPosition_vs; // Position du sommet
in vec3 vNormal_vs; // Normale du sommet
in vec2 vTexCoords; // Coordonnées de texture du sommet


out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(vec3 position_vs, vec3 normal_vs){
	
	vec3 w0 = normalize(-position_vs);
	vec3 wi = normalize(uLightPos_vs - vPosition_vs);
	vec3 halfVector = (w0 + wi) / 2;
    float d = distance(vPosition_vs, uLightPos_vs);

	return (uLightIntensity / (d * d)) * ( uKd * ( dot(wi, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}


void main() {
    fFragColor = blinnPhong(vPosition_vs, normalize(vNormal_vs));
}