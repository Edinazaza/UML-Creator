#include "CreateImageSFML.h"
#include "UMLParser.h"
#include "StartForm.h"
#include "resource.h"
#include <windows.h>
#include "Parser.h"
#include <algorithm>
#include <filesystem>

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

std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>> 
CreateImage(std::vector<std::string> meth, std::vector<std::string> var, std::string name, std::string FilePath, size_t count)
{
	if (!(name.empty() && meth.empty() && var.empty())) {
		unsigned int width = 252;
		for (std::string& i : meth)
		{
			width = max(unsigned(i.size()) * 5 + 20, width);
		}

		const unsigned int height = (unsigned(meth.size()) + unsigned(var.size())) * 14 + 50;

		sf::RectangleShape rectangle(sf::Vector2f(float(width - 2), float(height - 2)));
		rectangle.setFillColor(sf::Color::White);
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color::Black);
		rectangle.move(1, 1);

		sf::RenderTexture renderTexture;
		renderTexture.create(width, height);
		renderTexture.draw(rectangle);

		sf::Text txt;
		sf::Font font = LoadFontFromResource(IDR_FONTS1);
		txt.setFont(font);
		txt.setFillColor(sf::Color::Black);

		// class name
		txt.setCharacterSize(16);
		txt.setStyle(sf::Text::Bold);
		txt.setString(name);
		txt.move(sf::Vector2f((float(width) / 2 - 4 * float(name.size())), float(7)));
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
		capturedTexture.saveToFile(FilePath);

		return { name, {FilePath, {capturedTexture.getSize().x, capturedTexture.getSize().y}} };
	}
}

std::pair<size_t, std::vector<std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>>>> 
ParserUmlAndChangeImage(size_t counter, size_t wanted_class)
{
	std::string filename = get_data_dir() + "\\ParseClass.txt";
	std::ifstream source(filename);
	ParserUML pUML;
	size_t count = wanted_class;
	std::vector<std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>>> classes;
	for( ;count <= counter; ++count)
	{
		classes.push_back(CreateImage(pUML.getMethod(source, count), pUML.getVariables(source, count), 
			pUML.getClassName(source, count), get_data_dir() + "\\class_img" + std::to_string(count) + ".png", count));
	}
	return { counter, classes };
}

void create_arrow(std::map<std::string, ArrowProperities>& arrows, std::string& curr, bool& work,
	sf::Mutex& m)
{
	int l_w = 20;
	int l_h = 10;

	while (work)
	{
		m.lock();
		auto c = arrows.find(curr);
		m.unlock();
		if (!arrows.empty() && c != arrows.end() && (l_w != c->second.width || l_h != c->second.height)) {
			ArrowProperities curr_data = c->second;
			l_w = curr_data.width;
			l_h = curr_data.height;

			sf::RenderTexture rt;
			rt.setSmooth(true);
			rt.create(l_w, l_h);

			sf::RectangleShape r_3(sf::Vector2f(1.f, float(l_w - 10)));

			if (curr_data.h == head::ARROW) {
				sf::RectangleShape r_1(sf::Vector2f(1.f, 5.f));
				sf::RectangleShape r_2(sf::Vector2f(1.f, 5.f));
				r_1.move(float(l_w - 10), float(4));
				r_1.rotate(45);
				r_2.move(float(l_w - 10), float(4));
				r_2.rotate(135);
				r_1.setFillColor(curr_data.colour);
				r_2.setFillColor(curr_data.colour);
				rt.draw(r_1);
				rt.draw(r_2);
			}

			if (curr_data.h == head::AGREGATION)
			{
				r_3.setSize(sf::Vector2f(1.f, float(l_w - 15)));
				sf::RectangleShape r_p_1(sf::Vector2f(1.f, 8.f));
				sf::RectangleShape r_p_2(sf::Vector2f(1.f, 8.f));
				sf::RectangleShape r_p_3(sf::Vector2f(1.f, 8.f));
				sf::RectangleShape r_p_4(sf::Vector2f(1.f, 8.f));

				r_p_1.setFillColor(curr_data.colour);
				r_p_2.setFillColor(curr_data.colour);
				r_p_3.setFillColor(curr_data.colour);
				r_p_4.setFillColor(curr_data.colour);

				r_p_1.move(float(l_w - 15), float(5));
				r_p_2.move(float(l_w - 15), float(5));
				r_p_3.move(float(l_w - 8), float(8));
				r_p_4.move(float(l_w - 8), float(2));

				r_p_1.rotate(295);
				r_p_2.rotate(245);
				r_p_3.rotate(245);
				r_p_4.rotate(295);

				rt.draw(r_p_1);
				rt.draw(r_p_2);
				rt.draw(r_p_3);
				rt.draw(r_p_4);
			}

			if (l_h > 10)
			{
				sf::RectangleShape r_4((sf::Vector2f(1.f, float(l_h - 10))));
				r_4.move(0, 5);
				r_4.setFillColor(curr_data.colour);
				rt.draw(r_4);
			}

			r_3.move(0, 5);
			r_3.rotate(270);
			r_3.setFillColor(curr_data.colour);

			rt.draw(r_3);
			m.lock();
			rt.getTexture().copyToImage().saveToFile((get_data_dir() + "\\out.png"));
			m.unlock();
		}
	}
}

