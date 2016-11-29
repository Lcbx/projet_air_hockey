#version 420

uniform mat4 modelViewProjection;
//uniform mat4 matrModel;
//uniform mat4 matrVisu;
//uniform mat4 matrProj;




layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoordIn;
layout (location = 2) in vec3 normalIn;

//(varying)On communique les varaiables interpolées du nanceur de sommet vers le nuanceur de fragement 
varying vec2 texCoord;

vec4 lightSourcePosition = vec4 (0.0, 0.0, 10.0, 0.0);
vec4 lightSourceSpot = vec4 (0.0, 0.0, -1.0, 0.0);
/////////////////////////////////////////////////////////////////

out Attribs {
   vec3 lumiereDir;
   vec3 lumiereSpotPos;
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
     //vec3 pos = vec3( matrModel*matrVisu* vec4(position, 1.0) ); 
     vec3 pos = vec3(gl_Position);
    //la normal normalise de chaque sommet.
    //vec3 N = normalize(transpose (inverse(matrModel*matrVisu) )* normalIn);
    vec3 N = normalize(normalIn);
    //direction de la lumiere. le vecteur entre le vertex (point de rebond)et la position de la lumière 
	 vec3 L = normalize(vec3( lightSourcePosition.xyz) - pos);
	 vec3 LSP = normalize(vec3(lightSourceSpot.xyz) - pos);
     //vec3 L = vec3(0.5,0.5,0.5);
    
    //la position de l'observateur (ou la caméra)
     vec3 O = normalize(-pos);
    
    // l'affectation des valeurs de sorties.
    AttribsOut.obsVec = normalize(-pos);  
    AttribsOut.normale =N;
    AttribsOut.lumiereDir = L;
    AttribsOut.lumiereSpotPos =LSP;
 
   // envoie de la texture au nuanceur de fragment.
    texCoord = texCoordIn;
   
}
