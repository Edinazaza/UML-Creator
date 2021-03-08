#include <algorithm>
#include "UMLParser.h"
#include "ConvertFunction.h"
#include "Parser.h"

std::string ParserUML::getSubStr(const std::string& str, const std::string& sub_str, size_t count)
{
	auto start_teg = str.find('<' + std::to_string(count) + sub_str + '>');
	auto finish_teg = str.find("</" + std::to_string(count) + sub_str + '>');
	std::string substr = str.substr(start_teg + sub_str.size() + 3, finish_teg - start_teg - sub_str.size() - 3);
	return substr;
}

System::String^ parse_custom_classes()
{
	std::ifstream stream(get_data_dir() + "\\cc.dtt");
	std::string res;
	std::string item;

	while (stream)
	{
		stream >> item;
		if (stream) { res += "- " + item + "\n"; }
	}
	auto ret = Convert_string_to_String(res);
	return ret;
}

std::string parse_text_from_box(System::String^ source)
{
	std::string data = Convert_String_to_string(source);
	std::string ret;
	std::set<std::string> ret_source;
	bool parsed = false;
	while (!parsed)
	{
		size_t str_break_pos = data.find('\n');
		if (str_break_pos == npos && data.empty()) { break; }
		else {
			std::string substr = data.substr(0, str_break_pos);
			char symb = ' ';
			size_t counter = 0;
			while (symb == ' ')
			{
				symb = substr[counter];
				++counter;
			}
			if (symb != '-')
			{
				data.erase(0, str_break_pos + 1);
			}
			else
			{
				ret_source.insert(substr.substr(substr.find(symb) + 2, str_break_pos) + " ");
				data.erase(0, str_break_pos + 1);
			}
		}
		if (str_break_pos == npos) { break; }
	}
	for (auto& item : ret_source)
	{
		ret += std::move(item) + " ";
	}

	return ret;
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

std::vector<std::string> ParserUML::getVariables(std::ifstream& source, size_t count)
{
	variables_.clear();
	std::string line;
	std::string tag = "</" + std::to_string(count) + "variables>";
	std::getline(source, line);
	while (true)
	{
		std::getline(source, line);
		if (line == tag) { break; }
		variables_.push_back(line);
	}
	return variables_;
}

std::vector<std::string> ParserUML::getMethod(std::ifstream& source, size_t count)
{
	methods_.clear();
	std::string line;
	std::string tag = "</" + std::to_string(count) + "methods>";
	std::getline(source, line);
	while (true)
	{
		std::getline(source, line);
		if (line == tag) { break; }
		methods_.push_back(line); 
	}
	return methods_;
}

std::string ParserUML::getClassName(std::ifstream& source, size_t count)
{
	class_name_.clear();
	std::string line;
	std::string tag = "</" + std::to_string(count) + "name>";
	std::getline(source, line);
	while (true)
	{
		std::getline(source, line);
		if (line == tag) { break; }
		class_name_ += line;
	}
	return class_name_;
}