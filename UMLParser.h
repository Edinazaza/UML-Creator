#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>

class ParserUML
{
public:
	ParserUML() = default;

	std::vector<std::string> getVariables(const std::string& filename);
	std::vector<std::string> getMethod(const std::string& filename);
	std::string getClassName(const std::string& filename);

private:
	std::string class_name_;
	std::vector<std::string> variables_;
	std::vector<std::string> methods_;

	std::string getFileTxt(const std::string& filename);
	std::string getSubStr(const std::string& str, const std::string& sub_str);
};