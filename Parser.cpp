#include "Parser.h"

void DataCollector::Parse(std::string filepath)
{
	std::ifstream source(filepath);
	std::string str;
	while (str != "class")
		source >> str;
	source >> str;
	class_name = str;
	source >> str;
	while (source)
	{
		source >> str;
		catch_section(str);
		if (str == "};")
			break;

		if (str.find('{') != std::string::npos && str.find('}') == std::string::npos)
		{
			ignore_by(source, '{', '}');
			continue;
		}
		clean_from_substrs(str, "std::");
		bool is_template_type = clean_template_type(source, str);
		std::string t;
		bool is_array = clean_array_type(str, t);

		if (types.find(str) != types.end() || is_template_type || is_array)
		{
			std::string type = str;
			if (is_array)
			{
				type = t;
			}

			if (is_template_type) { source >> str; }

			read_data_type(source, type, str);

			if (str.find('(') == std::string::npos)
			{
				if (str[str.size() - 1] == ';') {
					str.erase(str.size() - 1);
					clean_array_type(str, type);
					variables.push_back({ { str, type }, curr_section });
				}
				else if (str[str.size() - 1] == ',')
				{
					size_t is_arr = type.find('[');
					bool last = false;
					bool first = true;
					while (true)
					{
						is_arr = type.find('[');
						if (str.find(';') != std::string::npos)
							last = true;
						if (str[str.size() - 1] == ',' || str[str.size() - 1] == ';') { str.erase(str.size() - 1); }

						if (is_arr != std::string::npos && str.find('*') == std::string::npos && !first)
						{
							refresh_type(str, type);
							variables.push_back({ { str, type }, curr_section });
						}
						else if (is_arr != std::string::npos && str[0] == '*' && !first)
						{
							refresh_type(str, type);
							variables.push_back({ { str, type }, curr_section });
						}
						else if (is_arr == std::string::npos)
						{
							clean_array_type(str, type);
							variables.push_back({ { str, type }, curr_section });
						}

						else { variables.push_back({ { str, type }, curr_section }); }

						first = false;
						if (last)
							break;
						source >> str;
						if (str == "*")
						{
							source >> str;
							std::string temp = "*" + str;
							str = temp;
						}
					}
				}
			}
			else
			{
				auto sep = separate(str);
				std::pair<std::string, std::string> t_n_p = { type, str };
				n_t var_map;

				if (sep.second == ")" || sep.second == ");")
				{
					methods.push_back({ { t_n_p, curr_section }, var_map });
					continue;
				}

				if (sep.first && types.find(sep.second) != types.end())
				{
					str = sep.second;
					read_data_type(source, sep.second, str);
					clean_array_type(str, sep.second);

					if (str.find(')') != std::string::npos)
					{
						str.erase(str.find(')'));
						var_map.push_back({ str, sep.second });
						methods.push_back({ { t_n_p, curr_section }, std::move(var_map) });
						continue;
					}
					clean_from_symb(str, ',');
					var_map.push_back({ str, sep.second });
				}
				parse_method(source, var_map);
				methods.push_back({ { t_n_p, curr_section }, std::move(var_map) });
			}
			continue;
		}
		auto sep = separate(str);
		if (str == class_name)
		{
			std::pair<std::string, n_t> constructor;
			bool is_template = clean_template_type(source, sep.second);

			constructor.first = curr_section;
			if (sep.second == ")" || sep.second == ");")
			{
				constructors.push_back(constructor);
				continue;
			}
			if (sep.first && types.find(sep.second) != types.end() || is_template)
			{
				source >> str;
				if (str == "*")
				{
					sep.second += str;
					source >> str;
				}

				if (str[str.size() - 2] == ')' && str[str.size() - 1] == ';')
				{
					clean_from_symb(str, ')');
					clean_from_symb(str, ';');
					constructor.second.push_back({ str, sep.second });
					continue;
				}
				clean_from_symb(str, ')');
				clean_from_symb(str, ';');
				clean_from_symb(str, ',');
				clean_array_type(str, sep.second);
				constructor.second.push_back({ str, sep.second });
			}
			parse_method(source, constructor.second);
			constructors.push_back(constructor);
		}
	}
}

void DataCollector::output(const std::string& filepath)
{
	std::ofstream stream(filepath);

	(filepath == "nofile.txt" ? std::cout : stream) << (filepath == "nofile.txt" ? "class_name: " : "<name>\n") << class_name << (filepath == "nofile.txt" ? "\n\nvariables: " : "\n</name>\n<variables>");
	for (const auto& item : variables)
	{
		(filepath == "nofile.txt" ? std::cout : stream) << '\n' << sections_to_chars(item.second) << " " << item.first.first << ": " << item.first.second;
	}
	(filepath == "nofile.txt" ? std::cout : stream) << (filepath == "nofile.txt" ? "\n\nmethods:\n" : "\n</variables>\n<methods>\n");
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
		method += "): " + item.first.first.first;
		insert_newline_symb(method, 40);
		(filepath == "nofile.txt" ? std::cout : stream) << method << '\n';
	}
	(filepath == "nofile.txt" ? std::cout : stream) << (filepath == "nofile.txt" ? "\n\nconstructors:\n" : "\n");
	first = true;
	for (const auto& item : constructors) {
		std::string constructor = sections_to_chars(item.first) + " " + class_name + "(";
		first = true;
		for (const auto& itm : item.second)
		{
			if (!first)
				constructor += ", ";
			constructor += "in " + itm.first + ": " + itm.second;
			first = false;
		}
		constructor += ')';
		insert_newline_symb(constructor, 40);
		(filepath == "nofile.txt" ? std::cout : stream) << constructor << '\n';

	}
	(filepath == "nofile.txt" ? std::cout : stream) << "+ ~" << class_name << "()" << '\n';

	(filepath == "nofile.txt" ? std::cout : stream) << (filepath == "nofile.txt" ? "\n\n" : "</methods>");
}

const std::set<std::string> types = { "int", "void", "string", "char", "bool", "char*",
							"size_t", "unsigned", "long", "double", "short", "string", "float",
	"int*", "unsigned*" };
std::string class_name;
//{{name(var), type(var)}, section}
n_t_s variables;
//{{{type(method), name(method)}, section}, {{name(var), type(var)}}}
std::vector<std::pair<std::pair<std::pair<std::string, std::string>, std::string>, n_t>> methods;
std::vector<std::pair<std::string, n_t>> constructors;
std::string curr_section;

std::pair<bool, std::string> DataCollector::separate(std::string& source)
{
	std::string ret = "";
	bool separated = false;
	for (size_t i = source.size() - 1; i != 0; --i)
	{
		if (source[i] == '(')
		{
			ret = source.substr(i + 1, source.size() - i);
			source.erase(i, source.size() - i);
			separated = true;
			break;
		}
	}
	return { separated, ret };
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

std::string DataCollector::sections_to_chars(const std::string& section) const
{
	std::string ret = "+";
	if (section == "public:") { ret = "+"; }
	else if (section == "private:") { ret = "-"; }
	else if (section == "protected:") { ret = "#"; }
	return ret;
}

void DataCollector::parse_method(std::ifstream& source, n_t& var_map)
{
	std::string type, str = " ";
	size_t counter = 0;
	while (str.find(')') == std::string::npos && source)
	{
		source >> str;
		clean_template_type(source, str);
		bool is_type = clean_array_type(str, type);
		if (types.find(str) != types.end() || is_type)
		{
			if (is_type)
				source >> str;
			else
				type = str;
			read_data_type(source, type, str);
			clean_array_type(str, type);

			if (str[str.size() - 1] == ')') {
				str.erase(str.size() - 1);
				var_map.push_back({ str, type });
				break;
			}
			else if (str[str.size() - 2] == ')' && str[str.size() - 1] == ';')
			{
				str.erase(str.size() - 2);
				var_map.push_back({ str, type });
				break;
			}
			str.erase(str.size() - 1);
			var_map.push_back({ str, type });
		}
	}
}

void DataCollector::clean_from_symb(std::string& str, char symb)
{
	size_t res = str.find(symb);
	if (res != std::string::npos) {
		str.erase(res, 1);
	}
}

void DataCollector::ignore_by(std::ifstream& source, char o_bracket, char c_bracket)
{
	std::string str;
	source >> str;
	while (str.find(c_bracket) == std::string::npos)
	{
		if (str.find(o_bracket) != std::string::npos)
			ignore_by(source, o_bracket, c_bracket);
		source >> str;
	}
}

void DataCollector::clean_from_substrs(std::string& source, const std::string substr)
{
	bool cleaned = false;
	size_t pos = 0;
	while (!cleaned)
	{
		pos = source.find(substr);
		if (pos == std::string::npos) { cleaned = true; }
		else
		{
			std::string copy = source.substr(0, pos);
			copy += source.substr(pos + substr.size(), source.size() - (pos + substr.size()));
			source = copy;
		}
	}
}

bool DataCollector::clean_template_type(std::ifstream& source, std::string& first_part)
{
	if (first_part.find('(') != std::string::npos)
		return false;
	std::string str;
	int brackets = std::count(first_part.begin(), first_part.end(), '<') - std::count(first_part.begin(), first_part.end(), '>');
	if (brackets < 0)
		return false;
	bool is_type = false;
	while (brackets != 0)
	{
		is_type = true;
		source >> str;
		brackets += std::count(str.begin(), str.end(), '<') - std::count(str.begin(), str.end(), '>');
		clean_from_substrs(str, "std::");
		first_part += " " + str;
	}
	return is_type;
}

bool DataCollector::clean_array_type(std::string& source, std::string& type)
{
	bool is_type = false;
	if (source.find('[') != std::string::npos && source.find(']') != std::string::npos)
	{
		auto o_b = source.find('[');
		auto c_b = source.find(']');
		std::string size = source.substr(o_b + 1, c_b - o_b - 1);
		type += "[1.." + size + ']';
		source.erase(o_b, c_b - o_b + 1);
	}
	if (source.find('*') != std::string::npos)
	{
		source.erase(source.find('*'), 1);
		if (types.find(source) != types.end())
		{
			type = source + "[1..*]";
			is_type = true;
		}
		else
		{
			type += "[1..*]";
		}

	}
	if (type.size() != 0 && type[type.size() - 1] == '*')
	{
		std::string subtype = type.substr(0, type.size() - 1);
		if (types.find(subtype) != types.end() && subtype.find(' ') == std::string::npos)
		{
			type.erase(type.size() - 1, 1);
			type += "[1..*]";
		}
		else if (subtype.find(' ') != std::string::npos)
		{
			std::string s = subtype.substr(0, subtype.find(' '));
			if (types.find(s) != types.end())
			{
				type.erase(type.size() - 1, 1);
				type += "[1..*]";
			}
		}
	}
	return is_type;
}

void DataCollector::refresh_type(std::string& str, std::string& type)
{
	std::string nptr_type = type;
	nptr_type.erase(nptr_type.find('['));
	type = nptr_type;
	clean_array_type(str, type);
}

void DataCollector::read_data_type(std::ifstream& source, std::string& type, std::string& str)
{
	while (types.find(str) != types.end())
	{
		source >> str;
		if (str == "*") {
			type += str;
			source >> str;
		}
		if (types.find(str) != types.end())
			type += " " + str;
	}
}

void DataCollector::catch_section(const std::string& str)
{
	if (str == "public:" || str == "private:" || str == "protected:")
	{
		curr_section = str;
	}
}