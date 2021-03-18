#include "FileWork.h"
#include <windows.h>
#include <sstream>

void WriteInFile(const std::string& filename, const std::string& text_for_file)
{
	std::ofstream fout(filename);
	if (fout.is_open()) {
		fout << text_for_file;
		fout.close();
	}
}

std::string ReadFromFile(const std::string& filename)
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

std::string change_text_by_tags(std::string source, std::string new_piece, size_t count)
{
    std::string o_tag = "<" + std::to_string(count) + "name>";
    std::string c_tag = "</" + std::to_string(count) + "methods>";
    std::string ret = "", line;
    std::istringstream stream(source);
    while (std::getline(stream, line))
    {
        if (line.find(o_tag) != std::string::npos) 
        { 
            ret += new_piece + "\n";
            while (line.find(c_tag) == std::string::npos) { std::getline(stream, line); }
            std::getline(stream, line);
        }
        ret += line;
    }
    return ret;
}