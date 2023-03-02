#pragma once
#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <istream>

class Face
{
private:
	std::vector<int> vertexIndices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;

public:
	Face(std::istream& issLine)
	{
		vertexIndices = { 0,0,0 };
		normalIndices = { 0,0,0 };
		textureIndices = { 0,0,0 };

		char c;
		for (int i = 0; i < 3; i++)
		{
			issLine >> std::ws >> vertexIndices.at(i) >> std::ws;
			if (issLine.peek() != '/')
			{
				continue;
			}
			issLine >> c >> std::ws;
			if (issLine.peek() == '/')
			{
				issLine >> c >> std::ws >> normalIndices.at(i);
				continue;
			}
			else
			{
				issLine >> textureIndices.at(i);
			}
			if (issLine.peek() != '/')
			{
				continue;
			}
			issLine >> c >> normalIndices.at(i);
		}
	}

	const int Face::GetVertexIndex(int index)
	{
		return vertexIndices[index];
	}

	const int Face::GetNormalIndex(int index)
	{
		return normalIndices[index];
	}

	const int Face::GetTextureIndex(int index)
	{
		return textureIndices[index];
	}
};