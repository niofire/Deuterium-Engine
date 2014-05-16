#version 330
attribute vec3 position0;
attribute vec2 texcoord0;

uniform mat4 world_view_proj;
uniform mat4 model_world_proj;
uniform mat4 projection_mat;

varying vec2 v_texcoord;


void main()
{
	v_texcoord = texcoord0;
	gl_Position = projection_mat * world_view_proj * model_world_proj * vec4(position0,1);
}