#pragma once
#include <iostream>
#include <vector>

class Map
{
public:
	typedef char Field;
	typedef std::string FieldRow;
	typedef std::vector<FieldRow> Fields;

private:
	Fields fields;
	unsigned int width;

public:
	/**
	 * @enum Possible type of Map fields
	*/
	enum FieldType : char
	{
		Free = ' ',
		Wall = '#'
	};

	/**
	 * Map constructor.
	 * It creates an empty Map object.
	 */
	Map() : width(0){};

	/**
	 * Map constructor.
	 * It creates a Map object from the given parameters.
	 * @param mapfilename Name of the file of the map.
	 */
	explicit Map(const std::string &fileName);

	/**
	 * Get the type of the field at the given position.
	 * @param x The horizontal position (index) on the map.
	 * @param y The vertical position (index) on the map.
	 * @return Map::FieldType The type of the field.
	 */
	FieldType getFieldType(const int x, const int y) const;

	/**
	 * Get the type of the field at the given position.
	 * @param value The character representation value of a field.
	 * @return Map::FieldType The type of the field.
	 */
	FieldType getFieldType(const char &value) const;

	/**
	 * Get the field at the given position.
	 * @param x The horizontal position (index) on the map.
	 * @param y The vertical position (index) on the map.
	 * @return Map::Field The type of the field.
	 * @throw Map::WrongIndexException When the field at the given position is not exist
	 */
	Field getField(const int x, const int y) const;

	/**
	 * Get the fields of the map.
	 * @param x The horizontal position (index) on the map.
	 * @param y The vertical position (index) on the map.
	 * @return Map::Fields The type of the field.
	 */
	Fields getFields() const { return fields; }

	/**
	 * Get the width of the map.
	 * @return int The width of the map.
	 */
	int getWidth() const { return width; };

	/**
	 * Get the height of the map.
	 * @return int The height of the map.
	 */
	int getHeight() const { return fields.size(); };

	/**
	 * Check whether the field at the given position is exist or not.
	 * @param x The horizontal position (index) on the map.
	 * @param y The vertical position (index) on the map.
	 * @return int The height of the map.
	 */
	bool isFieldExist(const int x, const int y) const;

	/**
	 * Check whether the field at the given position is free or not.
	 * @param x The horizontal position (index) on the map.
	 * @param y The vertical position (index) on the map.
	 * @return int The height of the map.
	 */
	bool isFieldFree(const int x, const int y) const;

	/**
	 * @class WrongIndexException
	 *
	 * @brief Wrong Index exception to be called on retrieving a field by wrong index(es)
	*/
	class WrongIndexException : virtual public std::runtime_error
	{
	public:
		/**
		 * Constructor which takes a description as parameter.
		 * @param description Description of wrong index error.
		*/
		explicit WrongIndexException(const std::string &description) : std::runtime_error("Wrong index: " + description) {}
	};
};