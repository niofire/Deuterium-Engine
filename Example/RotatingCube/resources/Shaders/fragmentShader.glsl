#version 330
varying mediump vec2 v_texcoord;

uniform sampler2D texture_sampler;


void main ()
{
	vec4 color	= texture2D(texture_sampler,vec2(v_texcoord.x,1.0-v_texcoord.y));
	gl_FragColor = color;
}