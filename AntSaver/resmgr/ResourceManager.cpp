#include "ResourceManager.h"

ResourceManager::ResourceManager() {}

const ResourceManager& ResourceManager::get()
{
	static ResourceManager manager;
	return manager;
}

const sf::Texture& ResourceManager::getTexture(TextureName name) const
{
	return textures.get(name);
}

const sf::SoundBuffer& ResourceManager::getSound(SoundName name) const
{
	return sounds.get(name);
}

const sf::Font& ResourceManager::getFont(FontName name) const
{
	return fonts.get(name);
}
