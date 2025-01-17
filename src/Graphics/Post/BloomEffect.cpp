#include "BloomEffect.h"

void BloomEffect::Init(unsigned width, unsigned height)
{
    int index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);

    //Loads the shaders
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/bloom_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
}

void BloomEffect::ApplyEffect(PostEffect* buffer)
{
    BindShader(0);
    _shaders[0]->SetUniform("u_Intensity", _intensity);
    _shaders[0]->SetUniform("u_Threshold", _threshold);
    _shaders[0]->SetUniform("isHorizontal", (int)true);

    buffer->BindColorAsTexture(0, 0, 0);

    _buffers[0]->RenderToFSQ();

    buffer->UnbindTexture(0);

    UnbindShader();
}

float BloomEffect::GetIntensity() const
{
    return _intensity;
}
void BloomEffect::SetIntensity(float intensity)
{
    _intensity = intensity;
}

float BloomEffect::GetThreshold() const
{
    return _threshold;
}

void BloomEffect::SetThreshold(float threshold)
{
    _threshold = threshold;
}

void BloomEffect::SetBloomUniform(std::string uniform, float number)
{
    _shaders[0]->SetUniform(uniform, number);
}
