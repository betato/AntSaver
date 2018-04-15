#include "FileLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace FileIO
{
	bool readText(vector<string>& file, string path)
	{
		string line;
		ifstream fileStream(path);
		if (fileStream.is_open())
		{
			while (getline(fileStream, line))
			{
				file.push_back(line);
			}
			fileStream.close();
			return true;
		}
		return false;
	}
	
	bool readEntity(sf::VertexArray& vertices, sf::Vector2u textureSize, string path)
	{
		std::vector<std::string> fileText;
		if (!FileIO::readText(fileText, path))
		{
			return false;
		}

		vertices.clear();

		int i = 0;
		vector<string>::iterator it;
		for (it = fileText.begin(); it < fileText.end(); it++)
		{
			char begin = it->at(0);
			std::string str = it->erase(0, 1);
			istringstream iss(str);

			float x, y;
			char sep;
			iss >> x;
			iss >> sep;
			iss >> y;
			if (begin == 'v')
			{
				// Vertex
				vertices.append(sf::Vector2f(x, y));
			}
			else if (begin == 't')
			{
				// Texture
				vertices[i].texCoords = sf::Vector2f(x * textureSize.x, y * textureSize.y);
				i++;
			}
		}

		return true;
	}
}
