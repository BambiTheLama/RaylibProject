#include "TextureController.h"
#include <fstream>

std::map<std::string, Texture2D> TextureController::textures;
nlohmann::json TextureController::texturesData;
std::string TextureController::dirPath = "";

TextureController::TextureController(std::string path)
{
	loadTexture(path);
	const char* cpath = path.c_str();
	if (texturesData.contains(cpath))
	{
		this->frames = texturesData[cpath]["NumberOfFrames"];
		frameSize.x = texturesData[cpath]["FrameSize"][0];
		frameSize.y = texturesData[cpath]["FrameSize"][1];
		if (texturesData[cpath].contains("Frames"))
		{
			for (auto e : texturesData[cpath]["Frames"])
			{
				AnimationData data;
				if (e.contains("Start"))
					data.start = e["Start"];
				if (e.contains("End"))
					data.end = e["End"];
				if (e.contains("Name"))
					animations.insert({ e["Name"], data });
				//puts(e.dump(2).c_str());

			}
			//for (auto e : animations)
			//	puts(e.first.c_str());

		}
	}
	else
	{
		this->frames = 1;
		frameSize.x = texture.width;
		frameSize.y = texture.height;
	}

}

TextureController::~TextureController()
{

}

void TextureController::draw(Rectangle pos,bool flipVertical,bool flipHorizontal, int frame, Vector2 rotationPoint, float angle, Color color)
{
	Rectangle sourse = { 0.0f,0.0f,frameSize.x,frameSize.y };
	frame %= frames;
	sourse.x = sourse.width * frame;
	if (flipHorizontal)
		sourse.height = -sourse.height;
	if (flipVertical)
		sourse.width = -sourse.width;
	DrawTexturePro(texture, sourse, pos, rotationPoint, angle, color);
}

void TextureController::drawTile(Rectangle pos, float startX, float startY, float repetW, float repetH,Color c)
{
	Rectangle sourse = { startX,startY,(float)(repetW * texture.width),(float)(repetH * texture.height) };
	DrawTexturePro(texture, sourse, pos, { 0.0f,0.0f }, 0.0f, c);
}

int TextureController::getFrames(std::string animationName)
{
	if (!animations.contains(animationName))
		return getFrames();
	AnimationData animationData = animations.at(animationName);
	return animationData.end - animationData.start;
}

int TextureController::getFrame(std::string animationName, int frame)
{
	if (!animations.contains(animationName))
		return frame % getFrames();
	AnimationData animationData = animations.at(animationName);
	int frames = animationData.end - animationData.start;
	return animationData.start + frame % frames;
}

void TextureController::loadTexture(std::string path)
{
	auto search = textures.find(path);
	if (search != textures.end())
	{
		texture = search->second;
		return;
	}
	texture = LoadTexture(std::string(dirPath + path).c_str());
	if (texture.id < 0)
	{
		UnloadTexture(texture);
		return;
	}
	textures.insert({ path, texture });
}

void TextureController::clearTextures()
{
	for (auto t : textures)
	{
		UnloadTexture(t.second);
	}
	textures.clear();
	texturesData.clear();
}
void TextureController::setUpTexture(std::string dirPath)
{
	std::ifstream reader(std::string(dirPath + "Textures.json"));
	TextureController::dirPath = dirPath;
	if (!reader.is_open())
		return;
	reader >> texturesData;
	reader.close();
}