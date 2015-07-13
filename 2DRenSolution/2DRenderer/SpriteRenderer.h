#pragma once
#include "ShaderProgram.h"

class SpriteRenderer
{
public:
    SpriteRenderer( ShaderProgram* shader );
    void DrawSprite(glm::vec2& pos, glm::vec2& size = glm::vec2(10,10), float rotation = 0.f);
    void SetProjectionMatrix( glm::mat4& projection );

private:
    void InitRenderData();

private:
    ShaderProgram* shader;
    GLuint VAO;
};
