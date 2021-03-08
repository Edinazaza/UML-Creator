#include "Parser.h"
#include <windows.h>

std::string get_data_dir();

bool DataCollector::Parse(std::ifstream& source)
{
	parse_cc_to_set();
	std::string str;
	char peek_res = '.';

	while (str != "class" && str != "struct" && source)
	{
		if (!source) { return true; }
		source >> str;
	}
	if (!source) { return true; }
	new_char;
	str.clear();
	while (peek_res != '{' && peek_res != '\n' && peek_res != '\t' && peek_res != ' ' && peek_res != ':')
	{
		str += peek_res;
		new_char;
	}

	class_name = str;
	str.clear();
	while (peek_res != '{') {
		if (peek_res == ':')
		{
			peek_res = source.peek();
			source.ignore(1);
			while (peek_res != '{')
			{
				new_char;
				str += peek_res;
				if ((peek_res == ' ' || peek_res == '\n' || peek_res == '\t') && !str.empty())
				{
					if (str == "public" || str == "private" || str == "protected") { inheritance.second = str; str.clear(); }
					else if (inheritance.second.empty()) { inheritance.second = "private"; inheritance.first = str; break; }
					else { inheritance.first = str; break; }
				}
			}
			if (inheritance.second.empty()) { inheritance.second = "private"; inheritance.first = str; break; }
			else if (inheritance.first.empty()) { inheritance.first = str; break; }
		}
		if (peek_res == '{') { break; }
		new_char;
	}

	std::string type;
	bool method = false;
	bool variable = false;
	bool variable_line = false;
	while (source && str != "};")
	{
		new_char;
		bool clean = main_cycle_checks(source, type, str, peek_res, s);
		while (!clean) { clean = main_cycle_checks(source, type, str, peek_res, s); }
		if ((!type.empty() || str == class_name) && peek_res == '(') { parse_method(source, type, str, peek_res); }
		else if (!type.empty() && (peek_res == ',' || peek_res == ';')) { parse_var_line(source, type, str, peek_res); }
		str += peek_res;
		//if (types.find(str) != types.end()) { type = str; str.clear(); }
		if (str == "public" || str == "private" || str == "protected") { curr_section = str; new_char; str.clear(); }
	}
	return false;
}

std::string DataCollector::sections_to_chars(const std::string& section) const
{
	std::string ret = "+";
	if (section == "public") { ret = "+"; }
	else if (section == "private") { ret = "-"; }
	else if (section == "protected") { ret = "#"; }
	return ret;
}

void DataCollector::define_template_type(std::ifstream& source, std::string& type, std::string& str, char& peek_res)
{
	size_t bracket_count = std::count(str.begin(), str.end(), '<') - std::count(str.begin(), str.end(), '>');
	while (bracket_count != 0)
	{
		new_char;
		if (peek_res == '>') { --bracket_count; }
		else if (peek_res == '<') { ++bracket_count; }
		str += peek_res;
	}
	clean_from_substrs(str, "std::");
	type = str;
	str.clear();
	new_char;
}

void DataCollector::parse_cc_to_set()
{
	std::ifstream source(get_data_dir() + "\\cc.dtt");
	std::string str;
	while (source)
	{
		source >> str;
		types.insert(str);
	}
}

void DataCollector::clean_from_substrs(std::string& source, const std::string substr)
{
	bool cleaned = false;
	size_t pos = 0;
	while (!cleaned)
	{
		pos = source.find(substr);
		if (pos == npos) { cleaned = true; }
		else
		{
			std::string copy = source.substr(0, pos);
			copy += source.substr(pos + substr.size(), source.size() - (pos + substr.size()));
			source = copy;
		}
	}
}

bool DataCollector::main_cycle_checks(std::ifstream& source, std::string& type, std::string& str, char& peek_res, bool s)
{
	bool clean = true;
	//if (str == "//") { ignore_commentary(source, str, peek_res); }
	if (types.find(str) != types.end()) { if (s || peek_res == '*') { type += (type.empty() ? "" : " ") + str; str.clear(); } }
	if (str == "std::") { str.clear(); }
	if (peek_res == '<') { str += peek_res; define_template_type(source, type, str, peek_res); clean = false; }
	if (!type.empty() && peek_res == '*') { type += "[1..*]"; new_char; clean = false; }
	if (peek_res == '=') { new_char; clean = false; }
	if (peek_res == '"') { ignore_string(source, peek_res); clean = false; }
	if (peek_res == '{') { ignore_block(source, peek_res); clean = false; }
	if (peek_res == '[')
	{
		type += "[1..";
		while (peek_res != ']')
		{
			new_char;
			type += peek_res;
		}
		new_char;
		clean = false;
	}
	if (type.empty() && s) { str.clear(); }

	return clean;
}

bool DataCollector::parse_method_checks(std::ifstream& source, std::string& type, std::string& str, char& peek_res,
	std::pair<std::pair<std::pair<std::string, std::string>, std::string>, n_t>& method, bool s)
{
	bool clean = true;
	//if (types.find(str) != types.end()) { type += (type.empty() ? "" : " ") + str; str.clear(); }
	clean = main_cycle_checks(source, type, str, peek_res, s);
	if (peek_res == ',') {
		method.second.push_back({ str, type });
		str.clear();
		type.clear();
		new_char;
		clean = false;
	}
	return clean;
}

bool DataCollector::ignore_sep_symb(std::ifstream& source, char& peek_res)
{
	bool ret = false;
	while (peek_res == ' ' || peek_res == '\n' || peek_res == '\t' || peek_res == '\r')
	{
		peek_res = source.peek();
		source.ignore(1);
		ret = true;
	}
	return ret;
}

void DataCollector::parse_method(std::ifstream& source, std::string& type, std::string& str, char& peek_res)
{
	if (str.empty() && type == class_name) { str = type; type.clear(); }
	std::pair<std::pair<std::pair<std::string, std::string>, std::string>, n_t> method;
	method.first.first.first = type;
	method.first.first.second = str;
	method.first.second = curr_section;
	str.clear();
	type.clear();
	while (peek_res != ')')
	{
		new_char;
		bool clean = parse_method_checks(source, type, str, peek_res, method, s);
		while (!clean) { clean = parse_method_checks(source, type, str, peek_res, method, s); }
		str += peek_res;
	}
	if (!str.empty() && !type.empty()) {
		str.pop_back();
		method.second.push_back({ str, type });
	}
	methods.push_back(method);
	type.clear();
	str.clear();
	new_char;
}

//void DataCollector::ignore_commentary(std::ifstream& source, std::string& str, char& peek_res)
//{
//	while (peek_res != '\n')
//	{
//		new_char;
//	}
//	str.clear();
//	new_char;
//}

void DataCollector::parse_var_line(std::ifstream& source, std::string& type, std::string& str, char& peek_res)
{
	variables.push_back({ {str, type}, curr_section });
	str.clear();
	if (type.find('[') != npos) { type.erase(type.find('['), 6); }
	bool line = false;
	while (peek_res != ';')
	{
		new_char;
		bool clean = var_line_checks(source, type, str, peek_res);
		while (!clean) { clean = var_line_checks(source, type, str, peek_res); }
		str += peek_res;
		line = true;
	}
	if (line) {
		str.pop_back();
		variables.push_back({ {str, type}, curr_section });
	}
	type.clear();
	str.clear();
	new_char;
}

void DataCollector::ignore_block(std::ifstream& source, char& peek_res)
{
	size_t count = 1;
	bool b = false;
	while (count != 0)
	{
		if (!b) { new_char; }
		b = false;
		if (peek_res == '{') { ++count; }
		else if (peek_res == '}') { --count; }
		else if (peek_res == '"') { ignore_string(source, peek_res); b = true; }
	}
	new_char;
}

void DataCollector::ignore_string(std::ifstream& source, char& peek_res)
{
	new_char;
	while (peek_res != '"') { new_char; }
	new_char;
}

bool DataCollector::var_line_checks(std::ifstream& source, std::string& type, std::string& str, char& peek_res)
{
	bool clean = true;
	if (types.find(str) != types.end()) { type += (type.empty() ? "" : " ") + str; str.clear(); }
	if (peek_res == '=') { new_char; clean = false; }
	if (peek_res == '"') { ignore_string(source, peek_res); clean = false; }
	if (peek_res == '{') { ignore_block(source, peek_res); clean = false; }
	if (peek_res == ',') {
		variables.push_back({ {str, type}, curr_section });
		if (type.find('[') != npos) { type.erase(type.find('['), type.size()); }
		str.clear();
		new_char;
		clean = false;
	}
	if (peek_res == '[')
	{
		type += "[1..";
		while (peek_res != ']')
		{
			new_char;
			type += peek_res;
		}
		new_char;
		clean = false;
	}
	if (peek_res == '*') { type += "[1..*]"; new_char; clean = false; }
	return clean;
}

void DataCollector::output(size_t& count, std::string filepath)
{
	std::ofstream stream(filepath, (count == 1 ? std::ios_base::out : std::ios_base::app));
	if (class_name.size() == 0)
	{
		(filepath == "nofile.txt" ? std::cout : stream) << "There is no any class in your input!";
		return;
	}
	create_dir(*this);

	(filepath == "nofile.txt" ? std::cout : stream) << (filepath == "nofile.txt" ? "class_name: " : ("<" + std::to_string(count) + "name>\n")) <<
		class_name << (filepath == "nofile.txt" ? (inheritance.first.empty() ? "\ninheritance: No" : "\ninheritance: parent - " + inheritance.first + ", type - " + inheritance.second) : "")
		<< (filepath == "nofile.txt" ? "\n\nvariables: " : ("\n</" + std::to_string(count) + "name>\n<" + std::to_string(count) + "variables>"));

	for (const auto& item : variables)
	{
		(filepath == "nofile.txt" ? std::cout : stream) << '\n' << sections_to_chars(item.second) << " " << item.first.first << ": " << item.first.second;
	}
	(filepath == "nofile.txt" ? std::cout : stream) <<
		(filepath == "nofile.txt" ? "\n\nmethods:\n" : ("\n</" + std::to_string(count) + "variables>\n<" + std::to_string(count) + "methods>\n"));
	bool first = true;
	for (const auto& item : methods)
	{
		std::string method = sections_to_chars(item.first.second) + " " + item.first.first.second + "(";
		first = true;
		for (const auto& itm : item.second)
		{
			if (!first)
				method += ", ";
			method += "in " + itm.first + ": " + itm.second;
			first = false;
		}
		method += (item.first.first.second == class_name ? ")" : "): ") + item.first.first.first;
		insert_newline_symb(method, 40);
		(filepath == "nofile.txt" ? std::cout : stream) << method << '\n';
	}
	(filepath == "nofile.txt" ? std::cout : stream) << "+ ~" << class_name << "()" << '\n';

	(filepath == "nofile.txt" ? std::cout : stream) << (filepath == "nofile.txt" ? "\n\n" : "</" + std::to_string(count) + "methods>\n");
	++count;
}

void DataCollector::insert_newline_symb(std::string& source, size_t size)
{
	size_t size_safe = size;
	while (source.size() > size)
	{
		size_t space = size;
		while (source[space] != ' ')
		{
			--space;
		}
		source.insert(source.begin() + space, '\n');
		source.erase(source.begin() + space + 1);
		size += size_safe;
	}
}

void DataCollector::add_custom_class(std::string source)
{
	create_dir(*this);
	std::ofstream stream(data_directory + "\\cc.dtt", std::ios_base::app);
	stream << " " << source;
}

void DataCollector::read_custom_class()
{
	if (std::filesystem::exists(data_directory + "\\cc.dtt")) {
		std::ifstream stream(data_directory + "\\cc.dtt");
		std::string type;
		while (stream)
		{
			stream >> type;
			types.insert(type);
		}
	}
}

std::string create_dir(DataCollector& dc)
{
	static std::string dir;
	if (dc.get_dir() == "empty") {
		LPWSTR data = new WCHAR[500];
		GetSystemDirectory(data, 500);
		std::string sys_disc = "";
		sys_disc += char(data[0]);
		sys_disc += char(data[1]);
		sys_disc += "\\UML_Creator";
		dc.set_dir(sys_disc);
		if (!std::filesystem::exists(sys_disc)) { std::filesystem::create_directory(sys_disc); }
		dir = sys_disc;
	}
	else if (dc.get_dir() != "empty" && !std::filesystem::exists(dc.get_dir()))
	{
		std::filesystem::create_directory(dc.get_dir());
	}
	return dir;
}

size_t parse_several_classes(std::ifstream& source, const std::string& output_path)
{
	size_t count = 1;
	std::vector<DataCollector> data_vec;
	std::ios_base::app;
	bool finished = false;
	while (!finished)
	{
		DataCollector dc;
		finished = dc.Parse(source);
		if (!finished) { data_vec.push_back(std::move(dc)); }
	}
	for (auto& item : data_vec)
	{
		item.output(count, output_path);
	}
	return count;
}

std::string get_data_dir()
{
	LPWSTR data = new WCHAR[500];
	GetSystemDirectory(data, 500);
	std::string sys_disc = "";
	sys_disc += char(data[0]);
	sys_disc += char(data[1]);
	sys_disc += "\\UML_Creator";
	return sys_disc;
}