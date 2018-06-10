#include "TextureManager.h"

TextureManager::TextureManager()
{
	addResource(TextureName::Test, "res/texture/Test.png");
	addResource(TextureName::RightArrow, "res/texture/RightArrow.png");
	addResource(TextureName::LeftArrow, "res/texture/LeftArrow.png");
}
