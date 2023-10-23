#include "AssetImporter.h"

AssetImporter::AssetImporter()
{
}

AssetImporter::~AssetImporter()
{
}

sf::Texture AssetImporter::ImportTexture(std::string AssetName, AssetType Type)
{
	std::string texturePath = "Assets/";
	const std::string extension = ".png";
	sf::Texture texture;
	switch (Type)
	{
	case CHARACTER:texturePath += "Character/";break;
	case ENEMY:break;
	case ITEM:break;
	case ROOM:texturePath += "Room/"; break;
	default:break;
	}
	texture.loadFromFile(texturePath + AssetName + extension);
	return texture;
}



