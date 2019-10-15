#include "GlowApp.hh"

#include <glow/common/log.hh>

#include <typed-geometry/tg-std.hh>

#include <glow/common/scoped_gl.hh>
#include <glow/common/str_utils.hh>
#include <glow/objects/Program.hh>
#include <glow/objects/Shader.hh>
#include <glow/objects/VertexArray.hh>

#include <glow-extras/geometry/Cube.hh>

void GlowApp::init()
{
    GlfwApp::init(); // call to base!

    mShader = glow::Program::createFromFile(glow::util::pathOf(__FILE__) + "/shader");
    mCube = glow::geometry::Cube<>().generate();

    getCamera()->setLookAt({2, 5, 4}, {0, 0, 0});
}

void GlowApp::render(float elapsedSeconds)
{
    mRuntime += elapsedSeconds;

    GLOW_SCOPED(clearColor, tg::color3(0.3f));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLOW_SCOPED(enable, GL_DEPTH_TEST);

    auto const view = getCamera()->getViewMatrix();
    auto const proj = getCamera()->getProjectionMatrix();

    auto shader = mShader->use();
    shader["uRuntime"] = mRuntime;
    shader["uView"] = view;
    shader["uProj"] = proj;
    shader["uModel"] = tg::rotation_around(tg::dir3::pos_y, 100_deg * mRuntime);

    mCube->bind().draw();
}
