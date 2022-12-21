#ifndef UTILS_H
#define UTILS_H

#include "pch.hpp"

//==================== utility functions ===================================
std::string findTouchScreenEvent();
std::string findKbdEvent();
std::vector<std::string> splitString(const std::string& s,
	const std::string& delimiter);
int replaceAll(std::string& s, const std::string& del,
	const std::string& repl);
void removeSpaces(std::string& s);
std::string execCommand(const std::string& cmd);



#endif
