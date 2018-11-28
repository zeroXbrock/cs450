#version 130

// variables from the heavens
uniform float uKa, uKd, uKs;		// coefficients of each type of lighting
uniform float uS0, uT0;				// home coordinates; bounding box for pattern
uniform vec3  uColor;			    // object color
uniform vec3  uSpecularColor;		// light color
uniform float uShininess;		    // specular exponent
uniform float uTime;
uniform int uAnimateFragment;		// to animate or not to animate...

// my wavy vars
const float PI = 	3.14159265;
const float AMP = 	1.0;		// amplitude
const float W = 	2.;		// frequency

// input vars
in  vec2  vST;			// texture coords
in  vec3  vN;			// normal vector
in  vec3  vL;			// vector from point to light
in  vec3  vE;			// vector from point to eye

// stores last known time value; hold state on freeze
float lastTime;

void
main( )
{
	// update time while animation enabled
	if (uAnimateFragment == 1)
		lastTime = uTime;
	else
		lastTime = 0.5;

	vec3 Normal 	= normalize(vN);
	vec3 Light 		= normalize(vL);
	vec3 Eye 		= normalize(vE);
	vec3 myColor 	= uColor;

	// fragment effect processing here
	float waves = sin(lastTime * PI);
	float cwaves = cos(lastTime * PI);

	if (vST.t < sin(W * (vST.s * waves * 2))){
        myColor = vec3( 1., waves/2, 0. );
	}
	else{
		myColor = vec3( uColor.x, uColor.y, waves/2);
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