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

enum class body
{
	SOLID,
	DOTTED_LINE
};

struct ArrowProperities
{
	head h = head::ARROW;
	body b = body::SOLID;
	sf::Color colour = sf::Color::Black;
	int width = 22, height = 12;
};

sf::Font LoadFontFromResource(const int ID);
void create_arrow(std::map<std::string, ArrowProperities>& arrows, std::string& curr, bool& work, sf::Mutex& m);

std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>> 
CreateImage(std::vector<std::string> meth, std::vector<std::string> var,
	std::string name, std::string FilePath = "output.jpg", size_t count = 1);

std::pair<size_t, std::vector<std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>>>> 
ParserUmlAndChangeImage(size_t counter = 1, size_t wanted_class = 1);