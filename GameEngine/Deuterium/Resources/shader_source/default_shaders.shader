	<shader>
		name	=	"myShader"
		type	=	{"fragment","vertex"} //one or the other
		
		<uniform_buffer>
		vec3 someValue;
		mat4x4 model_view_proj;
		<uniform_buffer\>
		
		<texture>
		uniform sampler2D pTextureSampler;
			<sampler_state>
			..
			...
			..
			..
			<sampler_state\>
		<texture\>
		
		<semantic>
		v_tecoord 	: 	TEXCOORD0;
		position	:	POSITION0;
		model_view_proj	: MODEL_VIEW_PROJ;
		<semantic\>
		
		<source>
			#version 330
			varying mediump vec2 v_texcoord;

			uniform sampler2D texture_sampler;


			void main ()
			{
				vec4 color	= texture2D(texture_sampler,vec2(v_texcoord.x,1.0-v_texcoord.y));
				gl_FragColor = color;
			}
		<source\>
	<shader\>