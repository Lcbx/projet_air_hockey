#version 420

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
   
   
   //vec4 position;
   vec3 spotDirection1 = vec3(-0.3, 0.0, 0.6);
   vec3 spotDirection2 = vec3(0.3, 0.0, 0.6);
   float spotExponent =20.0;
   // angle d'ouverture de spot delta
   float spotCutoff =10;            // ([0.0,90.0] ou 180.0)
   //float constantAttenuation;
   //float linearAttenuation;
   //float quadraticAttenuation;




// Définition des paramètres globaux du modèle de lumière
vec4 LightModelAmbient = vec4(0.2,0.2,0.2, 1.0);       // couleur ambiante
//uniform bool localViewer;   // observateur local ou à l'infini?
//uniform bool twoSide;       // éclairage sur les deux côtés ou un seul?



   // partie 1: illumination
uniform int typeIllumination;     // // 0:toutes les sortes de la lumière sont activées, 1:Ambiante, 2:DirectionnellePhong , 3: spot,


/////////////////////////////////////////////////////////////////

in Attribs {
   vec3 lumiereDir;
   vec3 lumiereSpotPos;
   vec3 normale;
   vec3 obsVec;

} AttribsIn;



float calculerSpot( in vec3 spotDir1, in vec3 spotDir2, in vec3 L )
{
   //Gama est l'angle entre le rayon lumineu et  la direction du spot  
   float CosAngleGama1 =  dot(-L,spotDir1); 
   float CosAngleGama2 =  dot(-L,spotDir2); 
   float CosAngleOuverture = cos(radians(spotCutoff)); 
   //float CosAngleIner  = CosAngleOuverture;
   //float CosAngleOuter = pow (CosAngleOuverture,(1.01+(spotExponent/2)));
   float Ispot ;
                  		 
				   if (CosAngleGama1 >= CosAngleOuverture || CosAngleGama2 >= CosAngleOuverture)//&& CosAngleGama2 > CosAngleOuverture)
					    Ispot = clamp(pow(CosAngleGama1+CosAngleGama2,spotExponent),0.0,1.0);
				   else 
					    Ispot = 0.4 ;
					    
   return(Ispot );
   
}

vec4 calculerDirectionnelle( in vec3 L, in vec3 N, in vec3 O )
{
     // calcul de la compostante ambiante
     vec4 coul = vec4(Kemission,1.0)+ (vec4(Kambient,1.0) * LightModelAmbient); 
     coul += vec4(Kambient,1.0)* LightSourceAmbient; 

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
   
	  vec3 N = normalize(AttribsIn.normale);
	  vec3 L = normalize(AttribsIn.lumiereDir);
	  vec3 O = normalize(AttribsIn.obsVec);
	  vec3 LSP= normalize(AttribsIn.lumiereSpotPos);
	  vec3 DS1 = normalize(spotDirection1);
	  vec3 DS2 = normalize(spotDirection2);
	  //vec4 couleurDepart = calculerDirectionnelle( L,N, O )*calculerSpot(DS,L);
	  vec4 couleurTex = texture2D(diffuseTex,texCoord);
	  
	 
       //si le type d illumination est ambiant	
			 if (typeIllumination == 0) // lumière ambiante
			{
				//vec4 coul = vec4(Kdiffuse,1.0);
				vec4 coul = vec4(Kemission,1.0)+ vec4(Kambient,1.0) * LightModelAmbient; 
				color = clamp(coul*couleurTex,0.0,1.0);
			}
			
			 if (typeIllumination == 1) // lumière directionnelle
					 color = clamp((calculerDirectionnelle( L,N, O)*couleurTex),0.0,1.0);
   
			 if (typeIllumination == 2) //spot
				color = clamp(calculerSpot(DS1,DS2, LSP)*couleurTex,0.0,1.0);
			 
			 //else  //toutes les sortes de la lumière sont activées
				//color = clamp(couleurDepart* couleurTex,0.0,1.0);
          
   
    //color = vec4(couleurTex);

//luc
//note : le canal alpha controle l'application des textures
      //else color = colorIn + colorIn.a * texture2D(diffuseTex, texCoord.st);
      color = colorIn + color;

}
