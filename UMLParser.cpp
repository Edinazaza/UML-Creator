#include <algorithm>
#include "UMLParser.h"

std::string ParserUML::getSubStr(const std::string& str, const std::string& sub_str, size_t count)
{
	auto start_teg = str.find('<' + std::to_string(count) + sub_str + '>');
	auto finish_teg = str.find("</" + std::to_string(count) + sub_str + '>');
	std::string substr = str.substr(start_teg + sub_str.size() + 3, finish_teg - start_teg - sub_str.size() - 3);
	return substr;
}

std::string ParserUML::getFileTxt(const std::string& filename)
{
	std::ifstream ifs(filename);
	std::string s;
	if (ifs.is_open())
	{
		s.assign((std::istreambuf_iterator<char>(ifs.rdbuf())), std::istreambuf_iterator<char>());
		ifs.close();
	}
	return s;
}

std::vector<std::string> ParserUML::getVariables(const std::string& filename, size_t count)
{
	variables_.clear();
	std::string data = getFileTxt(filename);
	std::string need_data = getSubStr(data, "variables", count);
	auto teg = need_data.find('\n');
	while (teg != std::string::npos)
	{
		if (need_data.substr(0, teg).size() > 4) {
			variables_.push_back(need_data.substr(0, teg));
		}
		need_data.erase(0, teg + 1);
		teg = need_data.find('\n');
	}
	return variables_;
}

std::vector<std::string> ParserUML::getMethod(const std::string& filename, size_t count)
{
	methods_.clear();
	std::string data = getFileTxt(filename);
	std::string need_data = getSubStr(data, "methods", count);
	auto teg = need_data.find('\n');
	while (teg != std::string::npos)
	{
		if (need_data.substr(0, teg).size() > 4) {
			methods_.push_back(need_data.substr(0, teg));
		}
		need_data.erase(0, teg + 1);
		teg = need_data.find('\n');
	}
	return methods_;
}

std::string ParserUML::getClassName(const std::string& filename, size_t count)
{
	std::string data = getFileTxt(filename);
	class_name_ = getSubStr(data, "name", count);
	class_name_.erase(std::remove(class_name_.begin(), class_name_.end(), '\n'), class_name_.end());
	return class_name_;
}