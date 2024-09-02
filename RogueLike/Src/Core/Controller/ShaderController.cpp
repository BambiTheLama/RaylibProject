#include "ShaderController.h"


std::map<std::string, Shader> ShaderController::shaders;
std::string ShaderController::dirPath = "";

ShaderController::ShaderController(std::string pathVertex, std::string pathFragment)
{
	std::string path = pathVertex + pathFragment;
	auto search = shaders.find(path);
	if (search != shaders.end())
	{
		shader = search->second;
		return;
	}
	shader = LoadShader(std::string(dirPath + pathVertex).c_str(), std::string(dirPath + pathFragment).c_str());
	if (shader.id < 0)
	{
		UnloadShader(shader);
		return;
	}
	shaders.insert({ path, shader });
}

ShaderController::ShaderController(std::string pathFragment)
{
	auto search = shaders.find(pathFragment);
	if (search != shaders.end())
	{
		shader = search->second;
		return;
	}
	shader = LoadShader(0, std::string(dirPath + pathFragment).c_str());
	if (shader.id < 0)
	{
		UnloadShader(shader);
		return;
	}
	shaders.insert({ pathFragment, shader });
}

ShaderController::~ShaderController()
{

}

Shader ShaderController::getShader()
{
	return shader;
}

void ShaderController::setValue(const char* name, float value)
{
	SetShaderValue(shader, GetShaderLocation(shader, name), &value, SHADER_UNIFORM_FLOAT);
}

void ShaderController::setValue(const char* name, Texture2D texture)
{
	SetShaderValueTexture(shader, GetShaderLocation(shader, name), texture);
}

void ShaderController::clearShaders()
{
	for (auto s: shaders)
	{
		UnloadShader(s.second);
	}
	shaders.clear();
}

void ShaderController::setUpShader(std::string dirPath)
{
	ShaderController::dirPath = dirPath;
}