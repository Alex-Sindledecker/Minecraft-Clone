#include "pch.h"
#include "SkyboxLayer.h"
#include "Window.h"

float mesh_vertices[] = 
{
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

void SkyboxLayer::onCreate()
{
    camera = PerspectiveCamera(70.f, Settings::window_width / (float)Settings::window_height, glm::vec3(0, 0, 0));
    camera.setViewRange(0.1, 32 * 16);
    sensitivity = 0.05, camera_speed = 10;
    m_window->setMousePos(m_window->getSize() / glm::vec2(2));

    VertexBufferPtr vbo = ResourceManager::getVertexBuffer("skybox_vbo");
    vbo->init(mesh_vertices, sizeof(mesh_vertices));

    skybox_mesh = ResourceManager::getVertexArray("skybox_vao");
    skybox_mesh->bind();
    skybox_mesh->push<float>(*vbo.get(), 3, 0);
    skybox_mesh->unbind();

    skybox_shader = ResourceManager::getShader("skybox_shader");
    skybox_shader->init("res/shaders/skybox_vertex.glsl", "res/shaders/skybox_fragment.glsl");

    skybox_cubemap = ResourceManager::getTexture3D("skybox_texture");
    skybox_cubemap->init({ 
            "res/tex/skyboxes/skybox/top.jpg",
            "res/tex/skyboxes/skybox/bottom.jpg",
            "res/tex/skyboxes/skybox/left.jpg",
            "res/tex/skyboxes/skybox/right.jpg",
            "res/tex/skyboxes/skybox/front.jpg",
            "res/tex/skyboxes/skybox/back.jpg"
    });
}

void SkyboxLayer::onUpdate(float dt)
{
    glm::vec2 middle = m_window->getSize() / glm::vec2(2);
    glm::vec2 delta_mouse_pos = m_window->getMousePos() - middle;
    m_window->setMousePos(middle);

    camera.lookVertically(delta_mouse_pos.y * sensitivity);
    camera.lookHorizontally(delta_mouse_pos.x * sensitivity);

    camera.computeDirectionVectors();
    if (m_window->isKeyPressed(GLFW_KEY_W))
        camera.move(camera.getViewDirection() * camera_speed * dt);
    if (m_window->isKeyPressed(GLFW_KEY_A))
        camera.move(camera.getRight() * -camera_speed * dt);
    if (m_window->isKeyPressed(GLFW_KEY_S))
        camera.move(-camera.getViewDirection() * camera_speed * dt);
    if (m_window->isKeyPressed(GLFW_KEY_D))
        camera.move(camera.getRight() * camera_speed * dt);

    std::string title = "X: " + std::to_string(camera.getPosition().x) + ", Y: " + std::to_string(camera.getPosition().y) + ", Z: " + std::to_string(camera.getPosition().z);
    m_window->setTitle((title + ", FPS: " + std::to_string(1 / dt)).c_str());
}

void SkyboxLayer::onRender()
{
    skybox_shader->use();
    skybox_shader->setUniformMatrix4("pv", 
        camera.getProjectionMatrix() *
        glm::mat4(glm::mat3(camera.getViewMatrix()))
    );
    skybox_cubemap->bind();
    skybox_mesh->bind();
    glDepthMask(GL_FALSE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    skybox_mesh->unbind();
    skybox_cubemap->unbind();
}