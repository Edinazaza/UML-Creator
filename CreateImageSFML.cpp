#include <SFML/Graphics.hpp>

#include "CreateImageSFML.h"
#include "UMLParser.h"
#include "StartForm.h"
#include "resource.h"
#include <windows.h>
#include "Parser.h"
#include <algorithm>

sf::Font LoadFontFromResource(const int ID)
{
	HRSRC rsrcData = FindResource(NULL, MAKEINTRESOURCE(ID), L"FONTS");
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::Font font;
	if (!font.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load font from memory.");

	return font;
}

template <class T, class T_>
T max(T a, T_ b)
{
	if (a > b) { return a; }
	return b;
}

void CreateImage(std::vector<std::string> meth, std::vector<std::string> var, std::string name, std::string FilePath)
{
	unsigned int width = 252;
	for (std::string& i : meth)
	{
		width = max(unsigned(i.size()) * 2 + 20, width);
	}

	const unsigned int hight = (unsigned(meth.size()) + unsigned(var.size())) * 14 + 50;

	sf::RectangleShape rectangle(sf::Vector2f(float(width - 2), float(hight - 2)));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.move(1, 1);

	sf::RenderTexture renderTexture;
	renderTexture.create(width, hight);
	renderTexture.draw(rectangle);

	sf::Text txt;
	sf::Font font = LoadFontFromResource(IDR_FONTS1);
	txt.setFont(font);
	txt.setFillColor(sf::Color::Black);

	// class name
	txt.setCharacterSize(16);
	txt.setStyle(sf::Text::Bold);
	txt.setString(name);
	txt.move(sf::Vector2f((float(width)/2-4* float(name.size())), float(7)));
	renderTexture.draw(txt);
	rectangle.setSize(sf::Vector2f(float(width - 2), float(1)));
	rectangle.setOutlineThickness(0);
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition(rectangle.getPosition().x, txt.getPosition().y + 19);
	renderTexture.draw(rectangle);
	// end class name

	// variable
	txt.setStyle(sf::Text::Regular);
	txt.setCharacterSize(12);
	auto space = rectangle.getPosition().y + 5;
	for (auto& i : var)
	{
		txt.setString(i);
		txt.setPosition(8, space);
		txt.setStyle(sf::Text::Regular);
		renderTexture.draw(txt);
		space += 14;
	}
	renderTexture.draw(txt);
	rectangle.setSize(sf::Vector2f(float(width - 2), float(1)));
	rectangle.setOutlineThickness(0);
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition(rectangle.getPosition().x, txt.getPosition().y + 19);
	renderTexture.draw(rectangle);
	// end variable

	// method
	space += 5;
	txt.setCharacterSize(12);
	for (auto& i : meth)
	{
		txt.setString(i);
		txt.setPosition(4, space);
		renderTexture.draw(txt);
		space += 14;
	}
	// end method

	renderTexture.display();

	auto capturedTexture = renderTexture.getTexture().copyToImage();

	if (!capturedTexture.saveToFile(FilePath)) {}
}

void ParserUmlAndChangeImage(std::string FilePath)
{
	std::string filename = get_data_dir() + "\\ParseClass.txt";
	std::ifstream source(filename);
	ParserUML pUML;
	size_t counter = 1;
	CreateImage(pUML.getMethod(source, counter), pUML.getVariables(source, counter), pUML.getClassName(source, counter), FilePath);
}