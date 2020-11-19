#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Map::Map(const std::string &fileName)
{
	ifstream file(fileName);

	if (file.is_open())
	{
		string line;

		while (std::getline(file, line))
		{

			this->fields.push_back(line);

			// Set the proper width
			unsigned int newLineSize = static_cast<unsigned int>(line.size());
			if (newLineSize > this->width)
				this->width = newLineSize;
		}
		file.close();
	}
}

Map::Field Map::getField(const int x, const int y) const
{
	if (!this->isFieldExist(x, y))
	{
		throw Map::WrongIndexException("Field at the provided indicies is not exist in the map!");
	}

	Field field = ' ';

	if (static_cast<int>(this->fields[y].size()) > x)
	{
		field = this->fields[y].at(x);
	}

	return field;
}

Map::FieldType Map::getFieldType(const char &value) const
{
	return static_cast<Map::FieldType>(value);
}

Map::FieldType Map::getFieldType(const int x, const int y) const
{
	Field field = this->getField(x, y);
	return getFieldType(field);
}

bool Map::isFieldExist(const int x, const int y) const
{
	bool isExist = true;

	if (y < 0 || y >= this->getHeight() || x < 0 || x >= this->getWidth())
	{
		isExist = false;
	}

	return isExist;
}

bool Map::isFieldFree(const int x, const int y) const
{
	return this->getFieldType(x, y) == Map::Free;
}
