#ifndef ASSETIMPORTER_H
#define ASSETIMPORTER_H
#include<SFML/Graphics.hpp>
enum AssetType
{
	CHARACTER,
	ENEMY,
	ITEM,
};
class AssetImporter
{

public:
	AssetImporter();
	virtual ~AssetImporter();

	sf::Texture ImportTexture(std::string AssetName, AssetType Type);

private:

};

#endif
