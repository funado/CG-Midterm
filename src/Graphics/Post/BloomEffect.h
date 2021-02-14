#pragma once

#include "Graphics/Post/PostEffect.h"

class BloomEffect : public PostEffect
{
public:
	//Initializes framebuffer
	//Overrides post effect Init
	void Init(unsigned width, unsigned height) override;

	//Applies the effect to this buffer
	//passes the previous framebuffer with the texture to apply as parameter
	void ApplyEffect(PostEffect* buffer) override;

	//Getters
	float GetIntensity() const;

	//Setters
	void SetIntensity(float intensity);

	//Getters
	float GetThreshold() const;

	//Setters
	void SetThreshold(float threshold);

	void SetBloomUniform(std::string uniform, float number);
private:
	float _intensity = 0.5f;
	float _threshold = 0.05f;
};