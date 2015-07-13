#pragma once
#include <gl/glew.h>
#include "Shader.h"
#include <string>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
    bool LoadShader( std::string vsPath, std::string fsPath );
    void Use();
    GLuint GetID();
    void SetProgramInUse( bool val );
    void SetProgramName( const std::string& val );

    void SetFloat( const string& name, float value );
    void SetInteger( const string& name, int value );
    void SetVector2f( const string& name, float xValue, float yValue );
    void SetVector2f( const string& name, glm::vec2& value );
    void SetVector3f( const string& name, float xValue, float yValue, float zValue );
    void SetVector3f( const string& name, glm::vec3& value );
    void SetVector4f( const string& name, float xValue, float yValue, float zValue, float wValue );
    void SetVector4f( const string& name, glm::vec4& value );
    void SetMatrix4( const string& name, glm::mat4x4& value );

private:
    GLuint programID;
    bool programInUse = false;
    std::string programName;

};