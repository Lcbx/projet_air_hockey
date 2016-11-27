#version 420

layout(binding=0) uniform sampler2D diffuseTex;

varying vec2 texCoord;

//ajout du parametre colorIn pour les couleurs de la table
uniform vec4 colorIn;

out vec4 color;

void main()
{
	//note : le canal alpha controle l'application des textures
    color = colorIn + colorIn.a * texture2D(diffuseTex, texCoord.st);
}