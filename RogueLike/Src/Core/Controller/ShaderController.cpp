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

void ShaderController::clearShaders()
{
	for (auto s: shaders)
	{
		UnloadShader(s.second);
	}
	shaders.clear();
}

void ShaderController::setUpTexture(std::string dirPath)
{
	ShaderController::dirPath = dirPath;
}