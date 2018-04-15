#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

namespace FileIO
{
	bool readText(vector<string>& file, string path);
	bool readEntity(sf::VertexArray& vertices, sf::Vector2u textureSize, string path);
}