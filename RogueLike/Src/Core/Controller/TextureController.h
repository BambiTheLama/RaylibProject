#pragma once
#include "raylib.hpp"
#include <map>
#include <string>
#include "json.hpp"


struct AnimationData {
	int start = 0, end = 0;
};

class TextureController
{
	static std::map<std::string, Texture2D> textures;
	static nlohmann::json texturesData;
	static std::string dirPath;
	std::map<std::string, AnimationData> animations;
	Texture2D texture;
	int frames = 1;
	Vector2 frameSize = { 1,1 };
public:
	TextureController(std::string path="");

	~TextureController();

	void draw(Rectangle pos, bool flipVertical = false, bool flipHorizontal = false, int frame = 0, Vector2 rotationPoint = { 0.0f,0.0f }, float angle = 0, Color color = WHITE);

	void drawTile(Rectangle pos, float startX, float startY, float repetW, float repetH);

	int getFrames() { return frames; }

	int getFrames(std::string animationName);

	int getFrame(std::string animationName, int frame);

	Texture getTexture() { return texture; }

	friend class Engine;

private:

	void loadTexture(std::string path);

	static void clearTextures();

	static void setUpTexture(std::string dirPath);
};
