#ifndef GENERIC_FUNC_H
#define GENERIC_FUNC_H

/*!
* GenericFunc.h : interface of the gnfnc namespace.
*/

#include <string>

namespace gnfnc
{
	std::string GetExecutablePath();
	std::string GetExecutablePathAndMatchItWithFilename(std::string filename);
	int CountNumberOfLinesInFile(std::string filename);
}

#endif	//!GENERIC_FUNC_H
