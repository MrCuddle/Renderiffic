#include "SpriteRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
SpriteRenderer::SpriteRenderer( ShaderProgram* shader )
{
    this->shader = shader;
    InitRenderData();
}

void SpriteRenderer::InitRenderData()
{
    GLuint VBO;
    GLfloat vertices[] =
    {
        0.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(glm::vec2& pos, glm::vec2& size, float rotation)
{
    this->shader->Use();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0,0,1));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    this->shader->SetMatrix4("model", model);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRenderer::SetProjectionMatrix( glm::mat4& projection )
{
    this->shader->SetMatrix4("projection", projection);
}
