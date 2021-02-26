#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <functional>

typedef std::vector<std::pair<std::string, std::string>> n_t;
typedef std::vector<std::pair<std::pair<std::string, std::string>, std::string>> n_t_s;

class DataCollector
{
public:
	void Parse(std::string filepath);
	void output(const std::string& filepath = "nofile.txt");

private:
	const std::set<std::string> types =
	{ "int", "void", "string", "char", "bool", "char*","size_t", "unsigned", "long", "double", "short", "string", "float", "int*", "unsigned*" };
	std::string class_name;

	//{{name(var), type(var)}, section}
	n_t_s variables;
	//{{{type(method), name(method)}, section}, {{name(var), type(var)}}}
	std::vector<std::pair<std::pair<std::pair<std::string, std::string>, std::string>, n_t>> methods;
	std::vector<std::pair<std::string, n_t>> constructors;
	std::string curr_section;

	std::pair<bool, std::string> separate(std::string& source);
	std::string sections_to_chars(const std::string& section) const;
	void insert_newline_symb(std::string& source, size_t size);

	void parse_method(std::ifstream& source, n_t& var_map);
	void clean_from_symb(std::string& str, char symb);
	void ignore_by(std::ifstream& source, char o_bracket, char c_bracket);

	void clean_from_substrs(std::string& source, const std::string substr);
	bool clean_template_type(std::ifstream& source, std::string& first_part);
	bool clean_array_type(std::string& source, std::string& type);

	void refresh_type(std::string& str, std::string& type);
	void read_data_type(std::ifstream& source, std::string& type, std::string& str);
	void catch_section(const std::string& str);
};