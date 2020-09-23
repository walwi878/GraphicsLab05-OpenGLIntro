#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main()
{
	// Output color = color of the texture at the specified UV
    vec4 colorRGBA = texture( myTextureSampler, UV );
	//set output - at the moment only rgb
    color = colorRGBA.rgb;
   
    //output the texture coordinates
	//color =  vec3(UV.x, UV.y, 0.0);
    
    //output coloured texture
    //color = colorRGBA.rgb + vec3(0.4, 0.0,0.0);
}
