#version 440

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec2 inScreenCoords ;

layout (location = 0) out vec4 outColor;

layout (binding = 0) uniform sampler2D u_FinishedFrame;

uniform bool  isHorizontal;
//uniform ivec2 xScreenRes;
//uniform vec2 xDirection;

const float weights[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
	vec2 off = 1.0 / textureSize(u_FinishedFrame, 0);
	if (isHorizontal) {
		off = off * vec2(1, 0);
	} else {
		off = off * vec2(0, 1);
	}
	vec4 result = texture(u_FinishedFrame, inUV) * weights[0];
	for(int i = 1; i < 5; i++) {
		result += texture(u_FinishedFrame, inUV + off * i) * weights[i];
		result += texture(u_FinishedFrame, inUV - off * i) * weights[i];
	}
	outColor = vec4(result.rgb, 1);
}