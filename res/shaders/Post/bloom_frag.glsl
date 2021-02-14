#version 420

layout (location = 0) in vec2 inUV;

vec4 bloomResult;
out vec4 fragColor;
vec4 blurResult;

layout (binding = 0) uniform sampler2D u_FinishedFrame;
layout (binding = 30) uniform sampler3D u_TexColorGrade;

uniform float u_Threshold;
uniform float u_Intensity;
uniform bool  isHorizontal;

uniform bool useBloom = false;

const float weights[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
    vec4 textureColor = texture(u_FinishedFrame, inUV);
    // convert rgb to grayscale/brightness
    float brightness = dot( textureColor.rgb , vec3( 0.2126 , 0.7152 , 0.0722 ) );
    if ( brightness > u_Threshold ) bloomResult = vec4( u_Intensity * textureColor.rgb , 1.0 );
    else bloomResult = vec4( 0.0 , 0.0 , 0.0 , 1.0 );

    vec2 off = 1.0 / textureSize(u_FinishedFrame, 0);
	if (isHorizontal) {
		off = off * vec2(1, 0);
	} else {
		off = off * vec2(0, 1);
	}
	vec4 result = bloomResult * weights[0];
	for(int i = 1; i < 5; i++) {
		result += texture(u_FinishedFrame, inUV + off * i) * weights[i];
		result += texture(u_FinishedFrame, inUV - off * i) * weights[i];
	}
	blurResult = vec4(result.rgb, 1);

    if(useBloom)
    {
    fragColor = bloomResult + blurResult;
    }
    else
    {
        fragColor = textureColor;
    }
}