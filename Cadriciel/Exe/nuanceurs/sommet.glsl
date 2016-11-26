#version 420

uniform mat4 modelViewProjection;
//uniform mat4 matrModel;
//uniform mat4 matrVisu;
//uniform mat4 matrProj;




layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoordIn;
//layout (location = 2) in vec3 normalIn;

//(varying)On communique les varaiables interpolées du nanceur de sommet vers le nuanceur de fragement 
varying vec2 texCoord;

/////////////////////////////////////////////////////////////////

/*out Attribs {
   vec3 lumier;
   vec3 normale;
   vec3 obsVec;
} AttribsOut;*/

out vec4 couleur;

void main( void )
{  
   
   // transformation standard du sommet
   //gl_position est la sortie standard du nanceur de sommet
    gl_Position = modelViewProjection * vec4(position, 1.0);
    //position de sommet par rapport au repere de la camera.
     //vec3 pos = vec3( modelViewProjection  * vec4(position, 1.0) ); 
    //la normal normalise de chaque sommet.
    //vec3 N = normalize(normalIn);
    //direction de la lumiere.
    //vec3 L = normalize(vec3( (LightSource[0].position ).xyz - pos ));
    //la position de l observateur 
    //vec3 O = normalize(-pos);
    
    // l affectation des valeurs de sorties.
    //AttribsOut.obsVec = normalize(-pos);  
    //AttribsOut.normale =N;
    //AttribsOut.lumier = L;
    //AttribsOut.couleur =Color ;
    		
	//couleur = vec4(diffuse, 1.0);
   // envoie de la texture au nuanceur de fragment.
    texCoord = texCoordIn;
   
}
