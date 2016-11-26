#version 420

layout(binding=0) uniform sampler2D diffuseTex;

varying vec2 texCoord;
//in vec4 couleur;
out vec4 color;

uniform   vec3 Kemission;
uniform   vec3 Kambient;
uniform   vec3 Kdiffuse;
uniform   vec3 Kspeculaire;
uniform   float kshininess;

// Définition des paramètres des sources de lumière
   vec4 LightAmbient = vec4(0.2,0.2,0.2,1.0);
   /*vec4 diffuse;
   vec4 specular;
   vec4 position;
   vec3 spotDirection;
   float spotExponent;
   float spotCutoff;            // ([0.0,90.0] ou 180.0)
   float constantAttenuation;
   float linearAttenuation;
   float quadraticAttenuation;*/




// Définition des paramètres globaux du modèle de lumière
vec4 LightModelAmbient = vec4(0.0,0.0,0.0,0.0);       // couleur ambiante
//uniform bool localViewer;   // observateur local ou à l'infini?
//uniform bool twoSide;       // éclairage sur les deux côtés ou un seul?



   // partie 1: illumination
uniform int typeIllumination;     // // 0:toutes les sortes de la lumière sont activées, 1:Ambiante, 2:DirectionnellePhong , 3: spot,


/////////////////////////////////////////////////////////////////

/*in Attribs {
   vec4 couleur;
   vec3 lumier;
   vec3 normale;
   vec3 obsVec;

} AttribsIn;*/



/*float calculerSpot( in vec3 spotDir, in vec3 L )
{
   float exposantC  = LightSource[0].spotExponent;
   float CosAngleGama =  dot(L,spotDir); 
   float CosAngleOuverture = cos(radians(LightSource[0].spotCutoff)); 
   float CosAngleIner  = CosAngleOuverture;
   float CosAngleOuter = pow (CosAngleOuverture,(1.01+(exposantC/2)));
   float Ispot ;
                  		 
				   if (CosAngleGama > CosAngleOuverture )
					    Ispot = clamp(pow(CosAngleGama,exposantC),0.0,1.0);
					  else 
					    Ispot = 0.0 ;*/
					    
   //return(Ispot );
   
//}

vec4 calculerDirectionnelle( in vec3 L, in vec3 N, in vec3 O )
{
     // calcul de la compostante ambiante
     vec4 coul = vec4(Kemission,1.0)+ vec4(Kambient,1.0) * LightModelAmbient; 
     coul += vec4(Kambient,1.0)* LightAmbient; 

      
      //float NdotL = max( 0.0, dot( N,L) );
	  // calcul de la composante diffuse
	        //coul += FrontMaterial.diffuse * LightSource[0].diffuse * NdotL;
	  // calcul de la composante speculaire 
	              //float NdotHV ;
					   //NdotHV = max( 0.0, dot( normalize( L + O), N)  );
				  
	              //if ( NdotHV == 0.0 )
					   //coul +=  0.0;
				 //else 
					   //coul +=  FrontMaterial.specular * LightSource[0].specular * (pow( NdotHV, FrontMaterial.shininess ));    
 return( coul );
}


void main(void)
{
   
	  //vec3 N = normalize(AttribsIn.normale);
	  //vec3 L = normalize(AttribsIn.lumier );
	  //vec3 O = normalize(AttribsIn.obsVec);
	  //vec3 DS = normalize(-LightSource[0].spotDirection);
	  
	  //vec4 couleurDepart = calculerDirectionnelle( L,N, O )*calculerSpot(DS,L);
	  vec4 couleurTex = texture2D(diffuseTex,texCoord);
	  
	 
       //si le type d illumination est ambiant	
			 if (typeIllumination == 0) // lumière ambiante
			{
		
	
				//vec4 coul = vec4(Kdiffuse,1.0);
				vec4 coul = vec4(Kemission,1.0)+ vec4(Kambient,1.0) * LightModelAmbient; 
				coul += vec4(Kambient,1.0)* LightAmbient;
				color = clamp(coul*couleurTex,0.0,1.0);
			}
			
			 //if (typeIllumination == 1) // lumière directionnelle
					 //color = clamp((calculerDirectionnelle( L,N, O )*couleurTex),0.0,1.0);
   
			 //if (typeIllumination == 2)
				//color = clamp(calculerSpot(DS,L)* AttribsIn.couleur,0.0,1.0);// les spots
			 
			 //else  //toutes les sortes de la lumière sont activées
				//color = clamp(couleurDepart* couleurTex,0.0,1.0);
          
   

    //color = vec4(0.5, 0.5, 0.5, 1.0);
    //color = vec4(couleurTex);
}
