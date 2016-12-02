#version 420

///////////////////////////////////////////////////////////////////////////////
// @file fragment.glsl
// @author Medaoud Ikram
// @date 2016-11-15
// @version 1.0
//
// 
///////////////////////////////////////////////////////////////////////////////

uniform mat4 modelViewProjection;
layout(binding=0) uniform sampler2D diffuseTex;

varying vec2 texCoord;
//luc
//ajout du parametre colorIn pour les couleurs de la table
uniform vec4 colorIn;

//in vec4 couleur;
out vec4 color;

uniform   vec3 Kemission;
uniform   vec3 Kambient;
uniform   vec3 Kdiffuse;
uniform   vec3 Kspeculaire;
uniform   float Kshininess;

// Définition des paramètres des sources de lumière
   vec4 LightSourceAmbient = vec4(0.2,0.2,0.2,0.2);
   vec4 LightSourceDiffuse = vec4(1.0,1.0,1.0,1.0);
   vec4 LightSourceSpecular = vec4(1.0,1.0,1.0,1.0);
   
//Définition de paramètres de spot
   vec3 spotDirection1 = vec3(-0.15, 0.0, -1.0);
   vec3 spotDirection2 = vec3(0.15, 0.0, -1.0);
   float spotExponent =128.0;
   // angle d'ouverture de spot delta
   float spotCutoff =4;            // ([0.0,90.0] ou 180.0)




// Définition des paramètres globaux du modèle de lumière
vec4 LightModelAmbient = vec4(0.2,0.2,0.2, 1.0);       // couleur ambiante


   // partie 1: illumination
uniform int lumiereAmbiante =1;
uniform int lumiereDirectionnelle =1;
uniform int lumiereSpot =1;
/////////////////////////////////////////////////////////////////

in Attribs {
   vec3 lumiereDir;
   vec3 normale;
   vec3 obsVec;
   vec3 Lspot;

} AttribsIn;



float calculerSpot( in vec3 spotDir, in vec3 L )
{
   //Gama est l'angle entre le rayon lumineu et  la direction du spot  
   //float CosAngleGama1 =  dot(-L,spotDir1); 
   float CosAngleGama =  dot(-L,spotDir); 
   float CosAngleOuverture = cos(radians(spotCutoff)); 
   float Ispot ;
                  		 
				   if (CosAngleGama >= CosAngleOuverture )//|| CosAngleGama2 >= CosAngleOuverture)//&& CosAngleGama2 > CosAngleOuverture)
					    Ispot = clamp(pow(CosAngleGama,spotExponent),0.0,1.0);
				   else 
					    Ispot = 0;
					    
   return(Ispot );
   
}

vec4 calculerReflexion( in vec3 L, in vec3 N, in vec3 O )
{
     // calcul de la compostante ambiante
     //vec4 coul = vec4(Kemission,1.0)+ (vec4(Kambient,1.0) * LightModelAmbient); 
     vec4 coul = vec4(Kambient,1.0)* LightSourceAmbient; 

      // calcul de la composante diffuse
      //calcul de l'angle entre la normale et la direction de la lumière
	 float NdotL = max( 0.0, dot( N,L) );
	 coul += vec4(Kdiffuse, 1.0) * LightSourceDiffuse * NdotL;
	 
	  // calcul de la composante speculaire 
	  float NdotHV ;
	  vec3 R = normalize(reflect( -L, N )); 
	  NdotHV = max( 0.0, dot( N,normalize( O - L)));
	  NdotHV = max( 0.0, normalize(dot( R,O)));
	      if ( NdotHV == 0.0 )
			coul +=  0.0;
		  else 
			coul +=  (vec4(Kspeculaire, 1.0) * LightSourceSpecular * (pow( NdotHV, Kshininess )));   
			 
 return( coul );
}


void main(void)
{
	  vec4 couleurTable ;
	  couleurTable = colorIn;
	  vec3 N = normalize(AttribsIn.normale);
	  vec3 L = normalize(AttribsIn.lumiereDir);
	  vec3 Lspot = normalize(AttribsIn.Lspot);
	  vec3 O = normalize(AttribsIn.obsVec);
	  vec3 DS1 = normalize(spotDirection1);
	  vec3 DS2 = normalize(spotDirection2);
	  vec4 couleurTex = texture2D(diffuseTex,texCoord);
	  vec4 coulAmbiante = vec4(Kemission,1.0)+ (vec4(Kambient,1.0) * LightModelAmbient); 
	  vec4 coul = vec4 (0,0,0,0);
       //si le type d illumination est ambiant	
       if( (lumiereAmbiante!=0) || (lumiereDirectionnelle!=0) || (lumiereSpot!=0))
       {
			 if (lumiereAmbiante!=0) // lumière ambiante
					{
						coul = coulAmbiante;
						couleurTable= 0.2*colorIn;
					}

				
			
			 if (lumiereDirectionnelle!=0) // lumière directionnelle
			 	 {
					coul += calculerReflexion( L,N, O);
					couleurTable = colorIn;
			 	 }
   
			  
			 if (lumiereSpot!=0) //spot
			 {
				coul = ( calculerReflexion( Lspot,N, O))*(calculerSpot(DS1,Lspot)+calculerSpot(DS2,Lspot));
				//( calculerReflexion( Lspot,N, O) );
				couleurTable = colorIn*0.8;
				if (lumiereAmbiante!=0)
				{
					coul = coulAmbiante + ( calculerReflexion( L,N, O))*(calculerSpot(DS1,Lspot)+calculerSpot(DS2,Lspot));
					couleurTable = 0.2*colorIn;
				}
				if (lumiereDirectionnelle!=0)
				{
					coul = calculerReflexion( L,N, O) + ( calculerReflexion( Lspot,N, O))*(calculerSpot(DS1,Lspot)+calculerSpot(DS2,Lspot));
					couleurTable = colorIn;
					
				}
				
			 }

		
		} 
			else
			{
				couleurTable = vec4 (0,0,0,0);
				color=vec4(0,0,0,0);
			}
          
      color = clamp((couleurTable + coul*couleurTex),0.0,1.0);

}
