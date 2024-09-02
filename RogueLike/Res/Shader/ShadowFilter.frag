#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float zoom;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    vec4 texel = texture(texture0, fragTexCoord);
	if(texel.a>=0.01)
	{
		texel = vec4(0.0f);
	    int sampleRadius = 4;
		vec2 pixelSize = (zoom * 5) / textureSize(texture0, 0);
		for(int y = -sampleRadius; y <= sampleRadius; y++)
		{
			for(int x = -sampleRadius; x <= sampleRadius; x++)
			{
				texel += texture(texture0, fragTexCoord.xy + vec2(x, y) * pixelSize);
			}    
		}
		texel /= pow((sampleRadius * 2 + 1), 2);
	}

    finalColor = texel * colDiffuse;

}