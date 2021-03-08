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

	std::vector<std::string> getVariables(std::ifstream& source, size_t count);
	std::vector<std::string> getMethod(std::ifstream& source, size_t count);
	std::string getClassName(std::ifstream& source, size_t count);

private:
	std::string class_name_;
	std::vector<std::string> variables_;
	std::vector<std::string> methods_;

	std::string getFileTxt(const std::string& filename);
	std::string getSubStr(const std::string& str, const std::string& sub_str, size_t count);
};

System::String^ parse_custom_classes();
std::string parse_text_from_box(System::String^ source);