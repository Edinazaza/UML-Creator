#pragma once
#include <string>
#include <fstream>
#include <iterator>

void WriteInFile(const std::string& filename, const std::string& text_for_file);
std::string ReadFromFile(const std::string& filename);
std::string change_text_by_tags(std::string source, std::string new_piece, size_t count);