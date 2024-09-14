#pragma once
#include <string>
#include "json.hpp"
#include <map>
#include "raylib.h"
class SoundController
{
	static std::map<std::string, Sound> sounds;
	static nlohmann::json data;
	static std::string dirPath;
	Sound sound;
public:
	SoundController(std::string path = "");

	~SoundController();

	void play();

	friend class Engine;

private:

	void loadSound(std::string path);

	static void clearSounds();

	static void setUpSounds(std::string dirPath);
};

