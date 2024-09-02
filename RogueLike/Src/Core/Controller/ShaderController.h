#pragma once
#include "raylib.hpp"
#include <string>
#include <map>

class ShaderController
{
	static std::map<std::string, Shader> shaders;
	static std::string dirPath;
	Shader shader;
public:
	ShaderController(std::string pathVertex, std::string pathFragment);

	ShaderController(std::string pathFragment = "");

	~ShaderController();

	Shader getShader();

	void setValue(const char* name, float value);

	friend class Engine;

private:

	static void clearShaders();

	static void setUpShader(std::string dirPath);

};

