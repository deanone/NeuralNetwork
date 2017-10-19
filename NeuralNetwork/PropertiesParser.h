/*!
* PropertiesParser.h : interface of the PropertiesParser class.
* Using this class one can read a properties file which contains values in the following form:
* [propertyName] = [propertyValue]
*/

#ifndef PROPERTIES_PARSER_H
#define PROPERTIES_PARSER_H

#include <string>
#include <map>

class PropertiesParser
{
	/*!A map containing property names as keys and property values as values.*/
	std::map<std::string, std::string> propMap;

public:
	PropertiesParser(std::string propertiesFilename);
	~PropertiesParser();

	void AddPropertiesFile(std::string propertiesFilename);
	bool PropertyExists(std::string propertyName);
	std::string GetPropertyAsString(std::string propertyName);
	int GetPropertyAsInt(std::string propertyName);
	bool GetPropertyAsBool(std::string propertyName);
	float GetPropertyAsFloat(std::string propertyName);
	double GetPropertyAsDouble(std::string propertyName);
	std::string GetPropertyAsStringOrDefaultTo(std::string propertyName, std::string defaultPropertyValue);
	int GetPropertyAsIntOrDefaultTo(std::string propertyName, int defaultPropertyValue);
	bool GetPropertyAsBoolOrDefaultTo(std::string propertyName, bool defaultPropertyValue);
	float GetPropertyAsFloatOrDefaultTo(std::string propertyName, float defaultPropertyValue);
	double GetPropertyAsDoubleOrDefaultTo(std::string propertyName, double defaultPropertyValue);
};

#endif	//!PROPERTIES_PARSER_H