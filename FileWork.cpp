#include "FileWork.h"

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