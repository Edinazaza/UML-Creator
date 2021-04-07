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
CreateImage(std::vector<std::string> meth, std::vector<std::string> var, std::string name, std::string FilePath, size_t count, 
	diagramm_properities prop)
{
	if (!(name.empty() && meth.empty() && var.empty())) {
		unsigned int width = prop.square_width;
	/*	for (std::string& i : meth)
		{
			width = max(unsigned(i.size()) * 5 + 20, width);
		}*/

		const float height = ((float(meth.size()) + float(var.size())) * (14 - prop.height_decrement) + 50.f ) ;

		sf::RectangleShape rectangle(sf::Vector2f(float(width - 2.5), float(height - 2.5)));
		rectangle.setFillColor(sf::Color::White);
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color::Black);
		rectangle.move(1, 1);

		sf::RenderTexture renderTexture;
		renderTexture.create(width, height + 5);
		renderTexture.draw(rectangle);

		sf::Text txt;
		sf::Font font = LoadFontFromResource(IDR_FONTS1);
		txt.setFont(font);
		txt.setFillColor(sf::Color::Black);

		// class name
		txt.setCharacterSize(prop.font_size + 4);
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
		txt.setCharacterSize(prop.font_size);
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
		txt.setCharacterSize(prop.font_size);
		for (size_t i = 0; i < meth.size(); ++i)
		{
			std::string line = meth[i];
			while (i+1 < meth.size() && line.size() + meth[i+1].size() <= prop.str_lenght && meth[i + 1].find('+') == npos && meth[i + 1].find('-') == npos && meth[i + 1].find('#') == npos)
			{
				line += " " + meth[++i];
			}
			txt.setString(line);
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
ParserUmlAndChangeImage(size_t counter, size_t wanted_class, diagramm_properities prop)
{
	std::string filename = get_data_dir() + "\\ParseClass.txt";
	std::ifstream source(filename);
	ParserUML pUML;
	size_t count = wanted_class;
	std::vector<std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>>> classes;
	for( ;count <= counter; ++count)
	{
		classes.push_back(CreateImage(pUML.getMethod(source, count), pUML.getVariables(source, count), 
			pUML.getClassName(source, count), get_data_dir() + "\\class_img" + std::to_string(count) + ".png", count, prop));
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
		if (!arrows.empty() && c != arrows.end() && (l_w != c->second.horizontal || l_h != (c->second.vertical_a + c->second.vertical_b))) {
			ArrowProperities curr_data = c->second;
			l_w = curr_data.horizontal;
			l_h = (curr_data.vertical_a + curr_data.vertical_b);

			sf::RenderTexture rt;
			rt.setSmooth(true);
			rt.create(l_w, l_h);

			size_t ver_a_counter = 0;
			size_t ver_b_counter = 0;
			size_t hor_counter = 0;

			if (curr_data.b == body::DOTTED_LINE)
			{
				float x_loc = 10;
				if (!curr_data.w_classic) { x_loc = l_w - 10; }

				int y_start = l_h - 20, y_finish = l_h - curr_data.vertical_a - 5;
				if (!curr_data.h_classic) { y_start = l_h - curr_data.vertical_b - 5, y_finish = 5; }
				for (int i = y_start; i >= y_finish; i -= 10)
				{
					++ver_a_counter;
					sf::RectangleShape r_4(sf::Vector2f(1.f, float(5)));
					r_4.move(x_loc, float(i));
					r_4.setFillColor(curr_data.colour);
					rt.draw(r_4);
				}

				if (!curr_data.h_classic) { y_start = l_h - 20, y_finish = l_h - curr_data.vertical_b + 5; }
				else { y_start = l_h - curr_data.vertical_a - 10, y_finish = 5; }

				for (int i = y_start; i >= y_finish; i -= 10)
				{
					++ver_b_counter;
					sf::RectangleShape r_3(sf::Vector2f(1.f, float(5)));
					r_3.move(float(abs(l_w - x_loc)), float(i));
					r_3.setFillColor(curr_data.colour);
					rt.draw(r_3);
				}

				float y_point = l_h - curr_data.vertical_a - 5;
				if (!curr_data.h_classic) { y_point = l_h - curr_data.vertical_b + 5; }
				for (int i = l_w - 20; i >= 10; i -= 10)
				{
					++hor_counter;
					sf::RectangleShape r_3(sf::Vector2f(1.f, float(5)));
					r_3.move(float(i), y_point);
					r_3.rotate(270);
					r_3.setFillColor(curr_data.colour);
					rt.draw(r_3);
				}
			}
			else if (curr_data.b == body::SOLID)
			{
				float x_loc = 10;
				if (!curr_data.w_classic) { x_loc = l_w - 10; }
				float y_loc = curr_data.vertical_b - 5;
				if (!curr_data.h_classic) { y_loc = curr_data.vertical_a + 5; }

				if (curr_data.horizontal > 20)
				{
					++hor_counter;
					sf::RectangleShape r_4(sf::Vector2f(1.f, float(l_w - 20)));
					r_4.move(float(10), y_loc);
					r_4.setFillColor(curr_data.colour);
					r_4.rotate(270);
					rt.draw(r_4);
				}

				if (!curr_data.h_classic) { y_loc = curr_data.vertical_a + 4; }
				else { y_loc = (curr_data.h == head::ARROW ? 5 : 17); }

				if (curr_data.vertical_b > 20)
				{
					++ver_b_counter;
					sf::RectangleShape r_3(sf::Vector2f(1.f, float(curr_data.vertical_b - (curr_data.h == head::ARROW ? 10 : 22))));
					r_3.move(float(abs(l_w - x_loc)), y_loc);
					r_3.setFillColor(curr_data.colour);
					rt.draw(r_3);
				}

				if (!curr_data.h_classic) { y_loc = 5; }
				else { y_loc = (l_h - curr_data.vertical_a - ((curr_data.h == head::ARROW || ver_b_counter > 0 || hor_counter > 0) ? 5 : -11)); }

				if (curr_data.vertical_a > 10) {
					++ver_a_counter;
					sf::RectangleShape r_3(sf::Vector2f(1.f, float(curr_data.vertical_a - ((curr_data.h == head::ARROW || ver_b_counter > 0 || hor_counter > 0) ? 0 : 12))));
					r_3.move(x_loc, y_loc);
					r_3.setFillColor(curr_data.colour);
					rt.draw(r_3);
				}
			}

			if (curr_data.h == head::ARROW) {
				sf::RectangleShape r_1(sf::Vector2f(1.f, 5.f));
				sf::RectangleShape r_2(sf::Vector2f(1.f, 5.f));

				if (ver_b_counter > 0)
				{
					float x_loc = l_w - 10, y_loc = 4, angle_increment = 0;
					if (!curr_data.w_classic) { x_loc = 10; }
					if (!curr_data.h_classic) { y_loc = l_h - 4; angle_increment = 180; x_loc += 1; }

					r_1.move(x_loc, y_loc);
					r_1.rotate(45 + angle_increment);
					r_2.move(x_loc, y_loc);
					r_2.rotate(315 + angle_increment);
				}

				else if (hor_counter > 0)
				{
					float x_loc = l_w - 10, y_loc = (l_h - curr_data.vertical_a - 6), angle_increment = 0;
					if (!curr_data.h_classic) { y_loc = curr_data.vertical_a + 4; }
					if (!curr_data.w_classic) { x_loc = 10; angle_increment = 180; y_loc += 1; }
					r_1.move(x_loc, y_loc);
					r_1.rotate(45 + angle_increment);
					r_2.move(x_loc, y_loc);
					r_2.rotate(135 + angle_increment);
				}

				else
				{
					float y_loc = 0, x_loc = 10, angle_increment = 0;
					if (!curr_data.h_classic) { y_loc = curr_data.vertical_a; angle_increment = 180; x_loc += 1; }

					r_1.move(x_loc, y_loc);
					r_1.rotate(45 + angle_increment);
					r_2.move(x_loc, y_loc);
					r_2.rotate(315 + angle_increment);
				}

				r_1.setFillColor(curr_data.colour);
				r_2.setFillColor(curr_data.colour);
				rt.draw(r_1);
				rt.draw(r_2);
			}

			if (curr_data.h == head::AGREGATION || curr_data.h == head::COMPOSITION)
			{
				//r_3.setSize(sf::Vector2f(1.f, float(l_w - 15)));
				sf::ConvexShape rhombus;
				rhombus.setPointCount(4);
				rhombus.setPoint(0, sf::Vector2f(0, 4));
				rhombus.setPoint(1, sf::Vector2f(6, 0));
				rhombus.setPoint(2, sf::Vector2f(12, 4));
				rhombus.setPoint(3, sf::Vector2f(6, 8));
				rhombus.setOutlineThickness(1);
				rhombus.setOutlineColor(curr_data.colour);
				rhombus.setFillColor((curr_data.h == head::AGREGATION ? sf::Color::White : sf::Color::Black));

				if (ver_b_counter > 0)
				{
					float x_loc = l_w - 6, y_loc = 4;
					if (!curr_data.w_classic) { x_loc = 14; }
					if (!curr_data.h_classic) { y_loc = l_h - 20; }
					rhombus.rotate(90);
					rhombus.move(x_loc, y_loc);
				}
				else if (hor_counter > 0)
				{
					float x_loc = l_w - 15, y_loc = l_h - curr_data.vertical_a - 10;
					if (!curr_data.w_classic) { x_loc = 10; }
					if (!curr_data.h_classic) { y_loc = curr_data.vertical_a; }

					rhombus.move(x_loc, y_loc);
				}
				else
				{
					float y_loc = 1;
					if (!curr_data.h_classic) { y_loc = curr_data.vertical_a - 20; }
					rhombus.rotate(90);
					rhombus.move(float(14), y_loc);
				}

				rt.draw(rhombus);
			}

			if (curr_data.h == head::INHERITANCE)
			{
				sf::ConvexShape triangle;

				triangle.setPointCount(3);
				triangle.setPoint(0, sf::Vector2f(0, 0));
				triangle.setPoint(1, sf::Vector2f(0, 9));
				triangle.setPoint(2, sf::Vector2f(10, 5));

				triangle.setOutlineThickness(1);
				triangle.setOutlineColor(sf::Color::Black);

				if (ver_b_counter > 0)
				{
					float x_loc = l_w - 14, y_loc = 16, angle_increment = 0;
					if (!curr_data.w_classic) { x_loc = 6; }
					if (!curr_data.h_classic) { y_loc = l_h - 18;  angle_increment = 180; x_loc += 9; }
					triangle.rotate(270 + angle_increment);
					triangle.move(x_loc, y_loc);
				}
				else if (hor_counter > 0)
				{
					float x_loc = l_w - 15, y_loc = l_h - curr_data.vertical_a - 10;
					if (!curr_data.h_classic) { y_loc = curr_data.vertical_a; }
					if (!curr_data.w_classic) { x_loc = 15; triangle.rotate(180);  y_loc += 10; }
					triangle.move(x_loc, y_loc);
				}
				else
				{
					float x_loc = 6, y_loc = 10, angle_increment = 0;
					if (!curr_data.h_classic) { angle_increment = 180; x_loc = 15, y_loc = curr_data.vertical_a - 11; }
					triangle.rotate(270 + angle_increment);
					triangle.move(x_loc, y_loc);
				}

				rt.draw(triangle);
			}

			m.lock();
			rt.getTexture().copyToImage().saveToFile("out.png");
			m.unlock();
		}
	}
}

void create_default_arrow()
{
	sf::RenderTexture rt;
	rt.create(22, 10);
	sf::RectangleShape r_3(sf::Vector2f(1.f, float(12)));
	r_3.move(0, 5);
	r_3.rotate(270);
	r_3.setFillColor(sf::Color::Black);
	rt.draw(r_3);
	sf::RectangleShape r_1(sf::Vector2f(1.f, 5.f));
	sf::RectangleShape r_2(sf::Vector2f(1.f, 5.f));
	r_1.move(float(12), float(4));
	r_1.rotate(45);
	r_2.move(float(12), float(4));
	r_2.rotate(135);
	r_1.setFillColor(sf::Color::Black);
	r_2.setFillColor(sf::Color::Black);
	rt.draw(r_1);
	rt.draw(r_2);
	rt.getTexture().copyToImage().saveToFile((get_data_dir() + "\\arrow_sample.png"));
}