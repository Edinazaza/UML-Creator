#pragma once
#include <vector>
#include <string>

void CreateImage(std::vector<std::string> meth, std::vector<std::string> var, std::string name, std::string FilePath = "output.jpg");
void ParserUmlAndChangeImage(std::string FilePath = "output.jpg");