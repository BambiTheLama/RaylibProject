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
	static float globalVolume;
	float volume = 1.0f;
	Sound sound;
public:
	SoundController(std::string path = "");

	~SoundController();

	void play(float leftProcent = 0.5f);

	static void setGlobalVolume(float gv) { globalVolume = gv; }

	friend class Engine;

private:

	void loadSound(std::string path);

	static void clearSounds();

	static void setUpSounds(std::string dirPath);

	void readData(std::string name);
};

