#version 130

// outputs
out  vec3  vN;			// normal vector
out  vec3  vL;			// vector from point to light
out  vec3  vE;			// vector from point to eye
out  vec2  vST;			// texture coords

// gifts from the heavens
uniform float	uTime;	// "Time", from Animate( )

// constants for wavy stuff
const float PI = 	3.14159265;
const float AMP = 	0.2;		// amplitude
const float W = 	2.;		// frequency

// define light position
vec3 LightPosition = vec3(  6., 5., 1. );

void
main( )
{ 
	// get vertex coordinates
	vec3 vert = gl_Vertex.xyz;

	// map vertex to model
	vec4 ECposition = gl_ModelViewMatrix * vec4( vert, 1. );

	vN = normalize( gl_NormalMatrix * gl_Normal );	// normal vector
	vL = LightPosition - ECposition.xyz;			/* vector from the point
													to the light position */
	vE = vec3( 0., 0., 0. ) - ECposition.xyz;		/* vector from the point
													to the eye position */
	
	

	// vertex shader stuff
	vert.y = vert.y + sin(2 * PI * uTime);
	vert.x = vert.x * cos(2 * PI * uTime);
	vert.z = vert.z + tan(PI * uTime) * AMP;

	// get projected vertex position
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// send it
	gl_Position = gl_ModelViewProjectionMatrix * vec4( vert, 1. );
}