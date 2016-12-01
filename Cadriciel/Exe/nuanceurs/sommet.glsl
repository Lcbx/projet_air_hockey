#version 420

///////////////////////////////////////////////////////////////////////////////
// @file sommet.glsl
// @author Medaoud Ikram
// @date 2016-11-15
// @version 1.0
//
// 
///////////////////////////////////////////////////////////////////////////////

uniform mat4 modelViewProjection;
uniform mat4 matrModel;
uniform mat4 matrVisu;
uniform mat4 matrProj;



// les locations des variables d'entréées au nuanceur de sommet
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoordIn;
layout (location = 2) in vec3 normalIn;

//(varying)On communique les varaiables interpolées du nanceur de sommet vers le nuanceur de fragement 
varying vec2 texCoord;

// la position de la source lumineuse
vec4 lightSourcePosition = vec4 (0.0, 0.0, 0.5, 0.0);
/////////////////////////////////////////////////////////////////

// structure contient tous les variables qui sortent du nuanceur de sommet
out Attribs {
   vec3 lumiereDir;
   vec3 normale;
   vec3 obsVec;
} AttribsOut;

out vec4 couleur;

void main( void )
{  
   
   // transformation standard du sommet
   
   //gl_position est la sortie standard du nanceur de sommet
    gl_Position = modelViewProjection * vec4(position, 1.0);
    
    
    //position de sommet par rapport au repere de la camera.
     vec3 pos = normalize(vec3( matrVisu * matrModel* vec4(position, 1.0) )); 
     
     
    //la normal normalisé d'un sommet.
	  vec3 N = vec3(normalize(transpose (inverse(matrVisu * matrModel ))* vec4(normalIn, 1.0)));
	  
	 
	 //La direction de la lumière 
	 vec3 L = normalize(vec3(matrVisu* lightSourcePosition) - pos.xyz);
	 
    
    //la position de l'observateur (ou la caméra)
     vec3 O = normalize(-pos);
    
    // l'affectation des valeurs de sorties.
    AttribsOut.obsVec = O;  
    AttribsOut.normale =N;
    AttribsOut.lumiereDir = L;
 
   // envoie de la texture au nuanceur de fragment.
    texCoord = texCoordIn;
   
}
