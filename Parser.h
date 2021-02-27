#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <functional>
#include <filesystem>

typedef std::vector<std::pair<std::string, std::string>> n_t;
typedef std::vector<std::pair<std::pair<std::string, std::string>, std::string>> n_t_s;

class DataCollector
{
public:
	void Parse(std::string filepath);
	void output(std::string filepath = "nofile.txt");
	void add_custom_class(std::string source);
	void read_custom_class();
	std::string get_dir() { return data_directory; }
	void set_dir(std::string dir) { data_directory = dir; }


private:
	std::set<std::string> types =
	{ "int", "void", "string", "char", "bool", "char*","size_t", "unsigned", "long", "double", "short", "string", "float", "int*", "unsigned*" };
	std::string class_name;

	//{{name(var), type(var)}, section}
	n_t_s variables;
	//{{{type(method), name(method)}, section}, {{name(var), type(var)}}}
	std::vector<std::pair<std::pair<std::pair<std::string, std::string>, std::string>, n_t>> methods;
	std::vector<std::pair<std::string, n_t>> constructors;
	std::string curr_section;
	std::string data_directory = "empty";

	std::pair<bool, std::string> separate(std::string& source);

	std::string sections_to_chars(const std::string& section) const;
	void insert_newline_symb(std::string& source, size_t size);
	void peek_char(std::ifstream& source, std::string& str, char c);

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

std::string create_dir(DataCollector& dc);
std::string get_data_dir();