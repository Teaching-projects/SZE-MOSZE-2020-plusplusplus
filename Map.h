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
	unsigned int width = 0;

public:
	/**
	 * @enum Type of Map fields
	*/
	enum FieldType : char
	{
		Free = ' ',
		Wall = '#'
	};

	Map(){};
	explicit Map(const std::string &fileName);

	// TODO: Documentation
	FieldType getFieldType(const int x, const int y) const;
	FieldType getFieldType(const char &value) const;
	Field getField(const int x, const int y) const;
	Fields getFields() const { return fields; }
	int getWidth() const { return width; };
	int getHeight() const { return fields.size(); };
	bool isFieldExist(const int x, const int y) const;
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