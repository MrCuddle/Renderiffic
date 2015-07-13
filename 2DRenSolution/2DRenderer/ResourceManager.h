#pragma once

#include <map>
#include <string>

#include <GL/glew.h>

#include "ShaderProgram.h"

class ResourceManager
{
public:
    static std::string shaderFolder;
    static std::string currentShaderName;
    static std::map<std::string, ShaderProgram> Shaders;
    static void SetShaderFolderPath(std::string path);
    static ShaderProgram LoadShader(const std::string& vShader, const std::string& fShader, const std::string& name);
    static ShaderProgram* GetShader(const std::string& name);
    static void RegisterShader(const std::string& name);

private:
    ResourceManager();
};