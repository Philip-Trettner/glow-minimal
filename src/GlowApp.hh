#pragma once

#include <glow/fwd.hh>

#include <glow-extras/glfw/GlfwApp.hh>

class GlowApp : public glow::glfw::GlfwApp
{
private:
    glow::SharedProgram mShader;
    glow::SharedVertexArray mCube;

    float mRuntime = 0.0f;

protected:
    void init() override;
    void render(float elapsedSeconds) override;
};
