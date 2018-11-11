#version 130

// variables from the heavens
uniform float uKa, uKd, uKs;		// coefficients of each type of lighting
uniform float uS0, uT0;				// home coordinates; bounding box for pattern
uniform vec3  uColor;			    // object color
uniform vec3  uSpecularColor;		// light color
uniform float uShininess;		    // specular exponent
uniform float uSize;
uniform float uTime;

// my wavy vars
const float PI = 	3.14159265;
const float AMP = 	1.0;		// amplitude
const float W = 	2.;		// frequency

// input vars
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
	/* using: 
	-	vertex coordinates 	(vST) == <s, t>
	-	home coordinates (uS0, uT0)
	-	static size (uSize)
	*/
	//if( uS0-uSize/2. <= vST.s && vST.s <= uS0+uSize/2. &&
    //    uT0-uSize/2. <= vST.t && vST.t <= uT0+uSize/2. )
	float waviness = W * PI * uTime;
	/*if (
		(vST.t < vST.s * sin(waviness) && 
		 vST.s >= vST.t * sin(waviness) &&
		 vST.s >= vST.s * cos(waviness)
		 ) ||
		 (
		 vST.t >= vST.s * cos(waviness) &&
		 vST.s <= vST.t * sin(waviness) &&
		 vST.s <= vST.s * sin(waviness)
		 )
		)
		*/
	float waveX = sin(W * PI * vST.s);
	float waveY = tan(W * PI * vST.t);
	if (vST.s < waveX + uSize && vST.t >= waveY)
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