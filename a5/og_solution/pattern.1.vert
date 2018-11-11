#version 130

uniform float	uTime;		// "Time", from Animate( )
out vec2 vST;       		// texture coords
out vec3 vN;        		// normal vector
out vec3 vL;        		// vector from point to light
out vec3 vE;        		// vector from point to eye

const float PI = 	3.14159265;
const float AMP = 	0.2;		// amplitude
const float W = 	2.;		// frequency

const vec3 LIGHTPOSITION = vec3(5., 5., 0.);

void
main( )
{ 
	vST = gl_MultiTexCoord0.st;
	vec3 vert = gl_Vertex.xyz;
	vec4 ECposition = gl_ModelViewMatrix * gl_Vertex;

	// lighting stuff
    vN = normalize(gl_NormalMatrix * gl_Normal);        // normal vector
    vL = LIGHTPOSITION - ECposition.xyz;                // vector from point to light pos
    vE = vec3(0., 0., 0.) - ECposition.xyz;            // vector from point to eye pos

	vert.x = 3.; //something fun of your own design
	vert.y = 2.; //something fun of your own design
	vert.z = 5.; //something fun of your own design

	gl_Position = gl_ModelViewProjectionMatrix * vec4( vert, 1. );
}