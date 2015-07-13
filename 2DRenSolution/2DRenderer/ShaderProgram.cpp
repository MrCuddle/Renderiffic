#include "ShaderProgram.h"
#include "ResourceManager.h"
#include <glm/gtc/type_ptr.hpp>

bool ShaderProgram::LoadShader( std::string vsPath, std::string fsPath )
{
    Shader vertexShader, fragmentShader;
    vertexShader.loadShader( vsPath, GL_VERTEX_SHADER );
    fragmentShader.loadShader( fsPath, GL_FRAGMENT_SHADER );
    programID = glCreateProgram();
    glAttachShader( programID, vertexShader.getID() );
    glAttachShader( programID, fragmentShader.getID() );
    glLinkProgram( programID );
    vertexShader.deleteShader();
    fragmentShader.deleteShader();
    return true;
}
void ShaderProgram::Use()
{
    if( !programInUse )
        ResourceManager::RegisterShader( programName );
}

GLuint ShaderProgram::GetID()
{
    return programID;
}

void ShaderProgram::SetProgramInUse( bool val ){ programInUse = val; }
void ShaderProgram::SetProgramName( const std::string& val ) { programName = val; }

void ShaderProgram::SetFloat( const string& name, float value )
{
    this->Use();
    glUniform1f( glGetUniformLocation( this->programID, name.c_str() ), value );
}

void ShaderProgram::SetInteger( const string& name, int value )
{
    this->Use();
    glUniform1i( glGetUniformLocation( this->programID, name.c_str() ), value );
}

void ShaderProgram::SetVector2f( const string& name, float xValue, float yValue )
{
    this->Use();
    glUniform2f( glGetUniformLocation( this->programID, name.c_str() ), xValue, yValue );
}

void ShaderProgram::SetVector2f( const string& name, glm::vec2& value )
{
    this->Use();
    glUniform2f( glGetUniformLocation( this->programID, name.c_str() ), value.x, value.y );
}

void ShaderProgram::SetVector3f( const string& name, float xValue, float yValue, float zValue )
{
    this->Use();
    glUniform3f( glGetUniformLocation( this->programID, name.c_str() ), xValue, yValue, zValue );
}

void ShaderProgram::SetVector3f( const string& name, glm::vec3& value )
{
    this->Use();
    glUniform3f( glGetUniformLocation( this->programID, name.c_str() ), value.x, value.y, value.z );
}

void ShaderProgram::SetVector4f( const string& name, float xValue, float yValue, float zValue, float wValue )
{
    this->Use();
    glUniform4f( glGetUniformLocation( this->programID, name.c_str() ), xValue, yValue, zValue, wValue );
}

void ShaderProgram::SetVector4f( const string& name, glm::vec4& value )
{
    this->Use();
    glUniform4f( glGetUniformLocation( this->programID, name.c_str() ), value.x, value.y, value.z, value.w );
}

void ShaderProgram::SetMatrix4( const string& name, glm::mat4x4& value )
{
    this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->programID, name.c_str()), 1, false, glm::value_ptr(value));
}