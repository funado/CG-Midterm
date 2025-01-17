#pragma once

#include "Graphics/Post/PostEffect.h"

class GaussianBlur : public PostEffect
{
public:
	//Initializes framebuffer
	//Overrides post effect Init
	void Init(unsigned width, unsigned height) override;

	//Applies the effect to this buffer
	//passes the previous framebuffer with the texture to apply as parameter
	void ApplyEffect(PostEffect* buffer) override;

	void ApplyEffect2(PostEffect* buffer) override;

	//Getters
	float GetIntensity() const;

	//Setters
	void SetIntensity(float intensity);
private:
	float _intensity = 1.0f;
	float _threshold = 0.1f;

	std::vector<GaussianBlur> blurPass;
};