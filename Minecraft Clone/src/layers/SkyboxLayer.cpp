#include "pch.h"
#include "SkyboxLayer.h"
#include "Window.h"
#include "toolbox.h"

unsigned int skybox_indices[] =
{
    //font
    0, 1, 2,
    2, 3, 0,
    // right
    1, 5, 6,
    6, 2, 1,
    // back
    7, 6, 5,
    5, 4, 7,
    // left
    4, 0, 3,
    3, 7, 4,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // top
    3, 2, 6,
    6, 7, 3
};

float skybox_vertices[] =
{
    //front
    -1.0, -1.0,  1.0,
     1.0, -1.0,  1.0,
     1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0,
    // back
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,
    -1.0,  1.0, -1.0
};

void SkyboxLayer::onCreate()
{
    camera = PerspectiveCamera(70.f, Settings::window_width / (float)Settings::window_height, glm::vec3(0, 0, 0));
    camera.setViewRange(0.1, 32 * 16);
    sensitivity = 0.05, camera_speed = 10;
    m_window->setMousePos(m_window->getSize() / glm::vec2(2));

    VertexBufferPtr element_vbo = ResourceManager::getVertexBuffer("skybox_ebo");
    VertexBufferPtr vbo = ResourceManager::getVertexBuffer("skybox_vbo");
    element_vbo->init(skybox_indices, sizeof(skybox_indices), GL_ELEMENT_ARRAY_BUFFER);
    vbo->init(skybox_vertices, sizeof(skybox_vertices));
    skybox_mesh = ResourceManager::getVertexArray("skybox_vao");
    skybox_mesh->bind();
    element_vbo->bind();
    skybox_mesh->push<float>(*vbo.get(), 3, 0);
    skybox_mesh->unbind();
    element_vbo->unbind();

    skybox_shader = ResourceManager::getShader("skybox_shader");
    skybox_shader->init("res/shaders/skybox_vertex.glsl", "res/shaders/skybox_fragment.glsl");

    skybox_cubemap = ResourceManager::getTexture3D("skybox_texture");
    skybox_cubemap->init({
        "res/tex/skyboxes/my_skybox/Top.png",
        "res/tex/skyboxes/my_skybox/Bottom.png",
        "res/tex/skyboxes/my_skybox/Side.png",
        "res/tex/skyboxes/my_skybox/Side.png",
        "res/tex/skyboxes/my_skybox/Side.png",
        "res/tex/skyboxes/my_skybox/Side.png"
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
    glDepthMask(GL_FALSE);

    glm::mat4 proj = camera.getProjectionMatrix() * glm::mat4(glm::mat3(camera.getViewMatrix()));

    skybox_shader->use();
    skybox_shader->setUniformMatrix4("pv", proj);
    skybox_cubemap->bind();
    skybox_mesh->bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    skybox_mesh->unbind();
    skybox_cubemap->unbind();

    glDepthMask(GL_TRUE);
}