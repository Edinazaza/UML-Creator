#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <functional>
#include <filesystem>
#include <queue>

#define npos std::string::npos
#define new_char peek_res = source.peek();source.ignore();s = ignore_sep_symb(source, peek_res); 
typedef std::vector<std::pair<std::string, std::string>> n_t;
typedef std::vector<std::pair<std::pair<std::string, std::string>, std::string>> n_t_s;

class DataCollector
{
public:
	bool Parse(std::ifstream& source);
	void output(size_t& count, std::string filepath = "nofile.txt");
	void add_custom_class(std::string source);
	void read_custom_class();
	std::string get_dir() { return data_directory; }
	void set_dir(std::string dir) { data_directory = dir; }
private:
	std::set<std::string> types =
	{ "int", "void", "string", "char", "bool", "size_t", "unsigned", "long", "double", "short", "float", "uint64_t" };
	std::string class_name;

	//{{name(var), type(var)}, section}
	n_t_s variables;
	//{{{type(method), name(method)}, section}, {{name(var), type(var)}}}
	std::vector<std::pair<std::pair<std::pair<std::string, std::string>, std::string>, n_t>> methods;
	std::string curr_section;
	std::string data_directory = "empty";
	std::pair<std::string, std::string> inheritance;
	bool s;

	void parse_cc_to_set();
	void insert_newline_symb(std::string& source, size_t size);
	std::string sections_to_chars(const std::string& section) const;
	void parse_var_line(std::ifstream& source, std::string& type, std::string& str, char& peek_res);
	bool ignore_sep_symb(std::ifstream& source, char& peek_res);
	bool var_line_checks(std::ifstream& source, std::string& type, std::string& str, char& peek_res);
	void ignore_block(std::ifstream& source, char& peek_res);
	void ignore_string(std::ifstream& source, char& peek_res);
	bool main_cycle_checks(std::ifstream& source, std::string& type, std::string& str, char& peek_res, bool s);
	void parse_method(std::ifstream& source, std::string& type, std::string& str, char& peek_res);
	void clean_from_substrs(std::string& source, const std::string substr);
	void define_template_type(std::ifstream& source, std::string& type, std::string& str, char& peek_res);
	void ignore_commentary(std::ifstream& source, std::string& str, char& peek_res);
	bool parse_method_checks(std::ifstream& source, std::string& type, std::string& str, char& peek_res,
		std::pair<std::pair<std::pair<std::string, std::string>, std::string>, n_t>& method, bool s);
};

std::string create_dir(DataCollector& dc);
std::string get_data_dir(); 
size_t parse_several_classes(std::ifstream& source, const std::string& output_path, size_t _count = 1);
