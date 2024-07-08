#include "TextureController.h"
#include <fstream>

std::map<std::string, Texture2D> TextureController::textures;
nlohmann::json TextureController::texturesData;
std::string TextureController::dirPath = "";

TextureController::TextureController(std::string path)
{
	const char* cpath = path.c_str();
	if (texturesData.contains(cpath))
	{
		this->framesInW = texturesData[cpath][0];
		this->framesInH = texturesData[cpath][1];
	}
	loadTexture(path);
}

TextureController::~TextureController()
{

}

void TextureController::draw(Rectangle pos,bool flipVertical,bool flipHorizontal, int frame, Vector2 rotationPoint, float angle, Color color)
{
	Rectangle sourse = { 0.0f,0.0f,(float)texture.width / framesInW,(float)texture.height / framesInH };
	sourse.x = sourse.width  * (frame % framesInW);
	sourse.y = sourse.height * ((frame / framesInW) % framesInH);
	if (flipHorizontal)
		sourse.height = -sourse.height;
	if (flipVertical)
		sourse.width = -sourse.width;
	DrawTexturePro(texture, sourse, pos, rotationPoint, angle, color);
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