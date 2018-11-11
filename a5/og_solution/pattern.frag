#version 130

uniform float uKa, uKd, uKs;		// coefficients of each type of lighting
uniform float uS0, uT0;
uniform vec3  uColor;			    // object color
uniform vec3  uSpecularColor;		// light color
uniform float uShininess;		    // specular exponent
uniform float uSize;

in  vec2  vST;			// texture coords
in  vec3  vN;			// normal vector
in  vec3  vL;			// vector from point to light
in  vec3  vE;			// vector from point to eye


void
main( )
{
	vec3 Normal 	= normalize(vN);
	vec3 Light 		= normalize(vL);
	vec3 Eye 		= normalize(vE);
	vec3 myColor 	= uColor;

	// fragment "effect processing" here
	if( uS0-uSize/2. <= vST.s && vST.s <= uS0+uSize/2. &&
        uT0-uSize/2. <= vST.t && vST.t <= uT0+uSize/2. )
    {
        myColor = vec3( 1., 0., 0. );
    }

	// set ambient color
	vec3 ambient = uKa * myColor;

	// only do diffuse if the light can see the point
	float d = max( dot(Normal,Light), 0. );
	vec3 diffuse = uKd * d * myColor;

	// only do specular if the light can see the point
	float s = 0.;
	if( dot(Normal,Light) > 0. )
	{
		vec3 ref = normalize(  reflect( -Light, Normal )  );
		s = pow( max( dot(Eye,ref),0. ), uShininess );
	}
	vec3 specular = uKs * s * uSpecularColor;

	// set final fragment color based on sum of all lighting
	gl_FragColor = vec4( ambient + diffuse + specular,  1. );
}