#ifndef ASSETIMPORTER_H
#define ASSETIMPORTER_H
#include<SFML/Graphics.hpp>
class AssetImporter
{
public:
	enum AssetType
	{
		CHARACTER,
		ENEMY,
		ITEM,
	};
public:
	AssetImporter();
	virtual ~AssetImporter();

	sf::Texture ImportTexture(std::string AssetName, AssetType Type);

private:

};

#endif
