#include "ResourceManager.h"

std::map<std::string, ShaderProgram> ResourceManager::Shaders;
std::string ResourceManager::shaderFolder = "";
std::string ResourceManager::currentShaderName = "NONE";

void ResourceManager::SetShaderFolderPath(std::string path)
{
    shaderFolder = path;
}

ShaderProgram ResourceManager::LoadShader(const std::string& vShader, const std::string& fShader, const std::string& name)
{
    ShaderProgram program;
    if(!program.LoadShader(shaderFolder + vShader,shaderFolder + fShader))
    {
        cout << "ResourceManager::LoadShader call failed with parameters " << shaderFolder + vShader << " " << shaderFolder + fShader << " " << name << std::endl;
    }
    program.SetProgramName(name);
    Shaders[name] = program;
    return Shaders[name];
}

ShaderProgram* ResourceManager::GetShader(const std::string& name)
{
    return &Shaders[name];
}

void ResourceManager::RegisterShader(const std::string& name)
{
    if(Shaders.count(currentShaderName))
    {
        Shaders[currentShaderName].SetProgramInUse(false);
    }
    glUseProgram(Shaders[name].GetID());
    Shaders[name].SetProgramInUse( true );
    currentShaderName = name;
}