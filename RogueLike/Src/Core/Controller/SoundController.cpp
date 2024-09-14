#include "SoundController.h"
#include <fstream>

std::map<std::string, Sound> SoundController::sounds;
nlohmann::json SoundController::data;
std::string SoundController::dirPath = "";
float SoundController::globalVolume = 1.0f;

SoundController::SoundController(std::string path)
{
	loadSound(path);
}

SoundController::~SoundController()
{
}

void SoundController::play()
{
	SetSoundVolume(sound, globalVolume * volume);
	SetSoundPan(sound, 0.0f);
	PlaySound(sound);
}

void SoundController::loadSound(std::string path)
{
	readData(path);
	auto search = sounds.find(dirPath + path);
	if (search != sounds.end())
	{
		sound = search->second;
		return;
	}
	sound = LoadSound(std::string(dirPath + path).c_str());
	sounds.insert({ path, sound });
}

void SoundController::clearSounds()
{
	for (auto s : sounds)
	{
		UnloadSound(s.second);
	}
	sounds.clear();
}

void SoundController::setUpSounds(std::string dirPath)
{
	SoundController::dirPath = dirPath;
	std::ifstream reader(std::string(dirPath + "Sounds.json"));
	if (!reader.is_open())
		return;
	reader >> data;
	reader.close();
}

void SoundController::readData(std::string name)
{
	if (!data.contains(name))
		return;
	if(data[name].contains("Volume"))
		volume = data[name]["Volume"];
}
