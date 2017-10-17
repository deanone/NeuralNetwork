/*!
*PropertiesParser.cpp: implementation of the PropertiesParser class.
*/

#include "stdafx.h"
/*!
* project specific required inclusions
*/
#include "PropertiesParser.h"

#include <fstream>
#include <sstream>

/*!
* Constructor. Initializes the parser parsing the properties file and
* reading all properties in the \c propMap.
*
* @param propertiesFilename the filename of the properties file.
*/
PropertiesParser::PropertiesParser(std::string propertiesFilename)
{
	addPropertiesFile(propertiesFilename);
}

/*!
* Destructor. Destroys the map object propMap of the class and frees the corresponding memory.
*/
PropertiesParser::~PropertiesParser()
{
	propMap.clear();
}

/*!
* Parses a properties file and reads all properties in the \c propMap.
* It may be used consecutively to parse multiple properties files.
*
* @param propertiesFilename the filename of the properties file.
*/
void PropertiesParser::addPropertiesFile(std::string propertiesFilename)
{
	std::ifstream propertiesFileStream;
	propertiesFileStream.open(propertiesFilename.c_str());
	std::string line;
	if (propertiesFileStream.good())
	{
		while (propertiesFileStream.eof() == false)
		{
			line.clear();
			getline(propertiesFileStream, line);
			if (line.length() > 0 && line[0] != '#')	/*! line is not a comment line*/
			{
				std::string propertyName;
				std::string propertyValue;
				std::stringstream ss(line);
				char c;//c used to eat the '=' character
				ss >> propertyName >> c >> propertyValue;
				propMap[propertyName] = propertyValue;
			}
		}
	}
	propertiesFileStream.close();
}

/*!
* Checks if a property exists.
*
* @param propertyName the name of the property to be checked.
* @return \c true if property exists, \c false otherwise.
*/
bool PropertiesParser::propertyExists(std::string propertyName)
{
	return (!(propMap.find(propertyName) == propMap.end()));
}

/*!
* Returns the string value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return a string value for the property.
*/
std::string PropertiesParser::GetPropertyAsString(std::string propertyName)
{
	return propMap[propertyName];
}

/*!
* Returns the integer value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return an integer value for the property.
*/
int PropertiesParser::GetPropertyAsInt(std::string propertyName)
{
	int propertyValue;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

/*!
* Returns the boolean value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return a boolean value for the property.
*/
bool PropertiesParser::GetPropertyAsBool(std::string propertyName)
{
	bool propertyValue;
	propertyValue = (propMap[propertyName] == "true");
	return propertyValue;
}

/*!
* Returns the float value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return a float value for the property.
*/
float PropertiesParser::GetPropertyAsFloat(std::string propertyName)
{
	float propertyValue;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

/*!
* Returns the double value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return a double value for the property.
*/
double PropertiesParser::GetPropertyAsDouble(std::string propertyName)
{
	double propertyValue;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

/*!
* Returns the string value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return a string value for the property.
*/
std::string PropertiesParser::GetPropertyAsStringOrDefaultTo(std::string propertyName, std::string defaultPropertyValue)
{
	if (propertyExists(propertyName))
		return GetPropertyAsString(propertyName);
	else
		return defaultPropertyValue;
}

/*!
* Returns the integer value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return an integer value for the property.
*/
int PropertiesParser::GetPropertyAsIntOrDefaultTo(std::string propertyName, int defaultPropertyValue)
{
	if (propertyExists(propertyName))
		return GetPropertyAsInt(propertyName);
	else
		return defaultPropertyValue;
}

/*!
* Returns the boolean value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return a boolean value for the property.
*/
bool PropertiesParser::GetPropertyAsBoolOrDefaultTo(std::string propertyName, bool defaultPropertyValue)
{
	if (propertyExists(propertyName))
		return GetPropertyAsBool(propertyName);
	else
		return defaultPropertyValue;
}

/*!
* Returns the float value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return a float value for the property.
*/
float PropertiesParser::GetPropertyAsFloatOrDefaultTo(std::string propertyName, float defaultPropertyValue)
{
	if (propertyExists(propertyName))
		return GetPropertyAsFloat(propertyName);
	else
		return defaultPropertyValue;
}

/*!
* Returns the double value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return a double value for the property.
*/
double PropertiesParser::GetPropertyAsDoubleOrDefaultTo(std::string propertyName, double defaultPropertyValue)
{
	if (propertyExists(propertyName))
		return GetPropertyAsDouble(propertyName);
	else
		return defaultPropertyValue;
}