#include "SoundController.h"

std::map<std::string, Sound> SoundController::sounds;
nlohmann::json SoundController::data;
std::string SoundController::dirPath = "";

SoundController::SoundController(std::string path)
{
	loadSound(path);
}

SoundController::~SoundController()
{
}

void SoundController::play()
{
	SetSoundVolume(sound, 0.2f);
	PlaySound(sound);
}

void SoundController::loadSound(std::string path)
{
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
}
