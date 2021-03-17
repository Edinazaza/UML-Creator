#pragma once
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "Constructor.h"

enum class head
{
	ARROW,
	AGREGATION
};

struct ArrowProperities
{
	head h = head::ARROW;
	sf::Color colour = sf::Color::Black;
	int width = 22, height = 12;
};

void create_arrow(std::map<std::string, ArrowProperities>& arrows, std::string& curr, bool& work, sf::Mutex& m);
void CreateImage(std::vector<std::string> meth, std::vector<std::string> var, std::string name, std::string FilePath = "output.jpg"); 
size_t  ParserUmlAndChangeImage(std::string FilePath = "output.jpg", size_t counter = 1);