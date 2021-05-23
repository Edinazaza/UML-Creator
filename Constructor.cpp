#include "Constructor.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include "ConvertFunction.h"
#include "ResultForm.h"
#include "Parser.h"
#include "CreateImageSFML.h"

namespace C
{
	std::string curr;
	std::map<std::string, ArrowProperities> arrows;
	sf::Mutex m;
	bool thread_created = false;
}

using namespace C;

System::Void UMLCreator::Constructor::pictureBox_MouseDown(Object^ sender, MouseEventArgs^ args)
{
	down = true;
	PictureBox^ obj = safe_cast<PictureBox^>(sender);
	if (obj->Name == "arrow_sample")
	{
		arrow_sample_location = this->arrow_sample->Location;
		PictureBox^ new_a_s = gcnew PictureBox;
		create_new_pic_box(new_a_s, obj);
		new_a_s->Location = this->arrow_sample->Location;
		this->Controls->Add(new_a_s);
		pics->Add(new_a_s);
	}

	focused_name = obj->Name;
	m.lock();
	curr = Convert_String_to_string(obj->Name);
	m.unlock();
	fixed.X = Cursor->Position.X - this->Location.X;
	fixed.Y = Cursor->Position.Y - this->Location.Y;
	fixed.X -= obj->Location.X;
	fixed.Y -= obj->Location.Y;
}

System::Void UMLCreator::Constructor::pictureBox_MouseMove(Object^ sender, MouseEventArgs^ args)
{
	Point p;
	PictureBox^ obj = safe_cast<PictureBox^>(sender);
	p.X = Cursor->Position.X;
	p.Y = Cursor->Position.Y;
	p.X -= this->Location.X;
	p.Y -= this->Location.Y;
	auto current_picbox = arrows.find(Convert_String_to_string(obj->Name));

	if (obj->Name[0] == 'A' && obj->Name[1] == 'B' && !moving)
	{
		auto head_point = arrows.find(Convert_String_to_string(obj->Name))->second.head_location;
		if (((p.X < (head_point.X + 1) && p.X >(head_point.X - 6)) && (p.Y < (head_point.Y + 29) && p.Y >(head_point.Y + 22)) || ab_resizing))
		{
			Cursor->Current = Cursors::SizeAll;
			if (down)
			{
				ArrowProperities new_prop;

				arrow_location = current_picbox->second.arrow_location;
				m.lock();

				bool classic_w = current_picbox->second.w_classic;
				bool classic_h = current_picbox->second.h_classic;

				ab_resizing = true;
				auto current = arrows[curr];
				new_prop = current;

				int height = Cursor->Position.Y - this->Location.Y - arrow_location.Y - 20;
				int width = Cursor->Position.X - this->Location.X - arrow_location.X;

				new_prop.w_classic = true;
				new_prop.h_classic = true;

				if (!current_picbox->second.h_classic && height > 0)
				{
					new_prop.arrow_location.Y = obj->Location.Y;
				}
				if (!current_picbox->second.w_classic && width > 0)
				{
					new_prop.arrow_location.X = obj->Location.X;
				}

				if (width < 0)
				{
					classic_w = false;
					new_prop.w_classic = false;
				}

				if (height < 0)
				{
					classic_h = false;
					new_prop.h_classic = false;
				}


				if (!new_prop.h_classic && !new_prop.w_classic)
				{
					obj->Location = System::Drawing::Point(Cursor->Position.X - this->Location.X - 9, Cursor->Position.Y - this->Location.Y - 35);
				}
				else if (!new_prop.w_classic)
				{
					obj->Location = System::Drawing::Point(Cursor->Position.X - this->Location.X - 9, obj->Location.Y);
				}
				else if (!new_prop.h_classic)
				{
					obj->Location = System::Drawing::Point(obj->Location.X, Cursor->Position.Y - this->Location.Y - 35);
				}

				obj->Width = new_prop.horizontal = abs(width);
				obj->Height = abs(height);

				if (current.horizontal > 20)
				{
					if ((obj->Height < current.vertical_a + current.vertical_b) && current.vertical_b < 10)
					{
						new_prop.vertical_a = obj->Height - 10;
					}
					new_prop.vertical_b = obj->Height - current.vertical_a;
				}
				else
				{
					new_prop.vertical_b = 0;
					new_prop.vertical_a = obj->Height - 10;
				}

				if (!classic_w && !classic_h)
				{
					new_prop.head_location =
						System::Drawing::Point(obj->Location.X + 10, obj->Location.Y + 10);
				}
				else if (!classic_w)
				{
					new_prop.head_location =
						System::Drawing::Point(obj->Location.X + 10, obj->Location.Y + obj->Height);
				}
				else if (!classic_h)
				{
					new_prop.head_location =
						System::Drawing::Point(obj->Location.X + obj->Width, obj->Location.Y + 10);
				}
				else
				{
					new_prop.head_location =
						System::Drawing::Point(obj->Location.X + obj->Width, obj->Location.Y + obj->Height);
				}
				arrows[curr] = new_prop;
				m.unlock();
			}
		}
	}

	if (down && !ab_resizing)
	{
		moving = true;
		p.X -= fixed.X;
		p.Y -= fixed.Y;
		obj->Location = p;
		if (current_picbox != arrows.end())
		{
			ArrowProperities new_ap = arrows[Convert_String_to_string(obj->Name)];
			if (!current_picbox->second.w_classic && !current_picbox->second.h_classic)
			{
				new_ap.head_location = System::Drawing::Point(obj->Location.X + 10, obj->Location.Y + 10);
				new_ap.arrow_location = System::Drawing::Point(obj->Location.X + obj->Width + 9, obj->Location.Y + obj->Height + 16);
			}
			else if (!current_picbox->second.w_classic)
			{
				new_ap.head_location = System::Drawing::Point(obj->Location.X + 10, obj->Location.Y + obj->Height);
				new_ap.arrow_location = System::Drawing::Point(obj->Location.X + obj->Width + 9, obj->Location.Y);
			}
			else if (!current_picbox->second.h_classic)
			{
				new_ap.head_location = System::Drawing::Point(obj->Location.X + obj->Width, obj->Location.Y + 10);
				new_ap.arrow_location = System::Drawing::Point(obj->Location.X, obj->Location.Y + obj->Height + 16);
			}
			else
			{
				new_ap.head_location = System::Drawing::Point(obj->Location.X + obj->Width, obj->Location.Y + obj->Height);
				new_ap.arrow_location = System::Drawing::Point(obj->Location.X, obj->Location.Y);
			}
			m.lock();
			arrows[Convert_String_to_string(obj->Name)] = new_ap;
			m.unlock();
		}
	}
	if (obj->Name[0] == 'A' && obj->Name[1] == 'B' && down && ab_resizing) {
		obj->ImageLocation = Convert_string_to_String(get_data_dir() + "\\out.png");
	}
}

System::Void UMLCreator::Constructor::pictureBox_MouseUp(Object^ sender, MouseEventArgs^ args)
{
	PictureBox^ obj = safe_cast<PictureBox^>(sender);
	if (obj->Name == "arrow_sample")
	{
		PictureBox^ new_a_s = safe_cast<PictureBox^>(pics->Components[pics->Components->Count - 1]);
		new_a_s->Location = obj->Location;
		obj->Location = arrow_sample_location;
		m.lock();
		arrows[Convert_String_to_string(new_a_s->Name)].head_location =
			Point(new_a_s->Location.X + new_a_s->Width, new_a_s->Location.Y + new_a_s->Height);
		arrows[Convert_String_to_string(new_a_s->Name)].arrow_location = new_a_s->Location;
		m.unlock();
	}

	if (obj->Name[0] == 'A' && obj->Name[1] == 'B' && ab_resizing) {
		obj->ImageLocation = Convert_string_to_String(get_data_dir() + "\\out.png");
	}
	down = false;
	ab_resizing = false;
	moving = false;
}

System::Void UMLCreator::Constructor::add_arrow_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::Windows::Forms::PictureBox^ pic = gcnew System::Windows::Forms::PictureBox();
	create_new_pic_box(pic, nullptr);
	this->Controls->Add(pic);
}

System::Void UMLCreator::Constructor::save_to_file_Click(System::Object^ sender, System::EventArgs^ e)
{
	sf::RenderTexture rt;
	rt.create(this->Width, this->Height);

	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		sf::Texture t;
		obj->Image->Save(Convert_string_to_String(get_data_dir() + "\\out_2.png"));
		t.loadFromFile((get_data_dir() + "\\out_2.png"));
		sf::Sprite sp(t, sf::IntRect(0, 0, obj->Width, obj->Height));
		sp.move(sf::Vector2<float>(float(obj->Location.X), float(this->Height - obj->Location.Y)));
		sp.scale(sf::Vector2<float>(1.f, -1.f));
		rt.draw(sp);
	}

	for (size_t i = 0; i < labels->Components->Count; ++i)
	{
		TextBox^ obj = safe_cast<TextBox^>(labels->Components[i]);
		sf::Text txt;
		txt.setString(Convert_String_to_string(obj->Text));
		txt.setStyle(sf::Text::Regular);
		sf::Font f = LoadFontFromResource(101);
	
		txt.setFont(f);
		txt.setCharacterSize(10);
		txt.setFillColor(sf::Color::Black);
		txt.move(sf::Vector2<float>(float(obj->Location.X), float(this->Height - obj->Location.Y)));
		txt.scale(sf::Vector2<float>(1.f, -1.f));
		rt.draw(txt);
	}

	SaveFileDialog^ downloadImage = gcnew SaveFileDialog();
	downloadImage->DefaultExt = ".png";
	downloadImage->FileName = "constructor_output.png";
	if (downloadImage->ShowDialog() != System::Windows::Forms::DialogResult::OK) {
		return;
	}

	rt.getTexture().copyToImage().saveToFile(Convert_String_to_string(downloadImage->FileName->ToString()));

	MessageBox::Show(downloadImage->FileName->ToString(), "Download", MessageBoxButtons::OK);
}

System::Void UMLCreator::Constructor::key_press(System::Object^ sender, KeyEventArgs^ e)
{
	if (!focused_name){return System::Void();} 

	if (Convert_String_to_string(focused_name).find("LB") != npos || Convert_String_to_string(focused_name).find("text_sample") != npos)
	{
		TextBox^ obj = gcnew TextBox;
		if (e->KeyCode == Keys::Delete)
		{
			for (size_t i = 0; i < labels->Components->Count; ++i)
			{
				obj = safe_cast<TextBox^>(labels->Components[i]);
				if (obj->Name == focused_name)
				{
					obj->Hide();
					labels->Remove(obj);
					delete obj;
					focused_name = nullptr;
					break;
				}
			}
		}
	}
	else
	{
		PictureBox^ obj = gcnew PictureBox;
		for (size_t i = 0; i < pics->Components->Count; ++i)
		{
			obj = safe_cast<PictureBox^>(pics->Components[i]);
			if (obj->Name == focused_name) { break; }
		}
		if (e->KeyCode == Keys::Delete) {
			obj->Hide();
			m.lock();
			arrows.erase(Convert_String_to_string(obj->Name));
			m.unlock();
			pics->Remove(obj);
			delete obj;
			focused_name = nullptr;
		}
		else if (e->KeyCode == Keys::V && e->Modifiers == Keys::Control)
		{
			System::Windows::Forms::PictureBox^ pic = gcnew System::Windows::Forms::PictureBox();
			create_new_pic_box(pic, buffer);
			pic->Location = Point(Cursor->Position.X, Cursor->Position.Y-32);
			if (buffer->Name[0] == 'A' && buffer->Name[1] == 'B')
			{
				ArrowProperities new_ap = arrows[Convert_String_to_string(buffer->Name)];
				new_ap.arrow_location = pic->Location;
				if (!new_ap.w_classic && !new_ap.h_classic){new_ap.head_location = System::Drawing::Point(pic->Location.X + 10, pic->Location.Y + 10);}
				else if (!new_ap.w_classic){new_ap.head_location = System::Drawing::Point(pic->Location.X + 10, pic->Location.Y + pic->Height);}
				else if (!new_ap.h_classic){new_ap.head_location = System::Drawing::Point(pic->Location.X + pic->Width, pic->Location.Y + 10);}
				else{new_ap.head_location = System::Drawing::Point(pic->Location.X + pic->Width, pic->Location.Y + pic->Height);}
				m.lock();
				arrows[Convert_String_to_string(pic->Name)] = new_ap;
				m.unlock();
			}
			this->Controls->Add(pic);
		}
		else if (e->KeyCode == Keys::C && e->Modifiers == Keys::Control)
		{
			buffer = obj;
		}
	}
}

System::Void UMLCreator::Constructor::pictureBox_Click(Object^ sender, MouseEventArgs^ args)
{
	PictureBox^ obj = safe_cast<PictureBox^>(sender);
	std::string obj_name = Convert_String_to_string(obj->Name);
	if (args->Button == System::Windows::Forms::MouseButtons::Right && obj_name[0] == 'A' && obj_name[1] == 'B') {
		focused_name = obj->Name;
		m.lock();
		curr = Convert_String_to_string(obj->Name);
		m.unlock();

		auto l = obj->Location;
		l.X += this->Location.X;
		l.Y += this->Location.Y;

		this->PicBoxContMenu->Show(l);
	}
	else if (args->Button == System::Windows::Forms::MouseButtons::Left && obj_name[0] == 'A' && obj_name[1] == 'B')
	{
		focused_name = obj->Name;
		m.lock();
		curr = Convert_String_to_string(obj->Name);
		m.unlock();
	}
	else if (args->Button == System::Windows::Forms::MouseButtons::Left)
	{
		focused_name = obj->Name;
	}
}

System::Void UMLCreator::Constructor::rotateToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		if (obj->Name == focused_name)
		{
			System::Drawing::Image^ im = obj->Image;
			im->RotateFlip(RotateFlipType::Rotate90FlipNone);
			im->Save(Convert_string_to_String(get_data_dir()+"\\out_2.png"));
			obj->ImageLocation = Convert_string_to_String(get_data_dir() + "\\out_2.png");
			int temp = obj->Width;
			obj->Width = obj->Height;
			obj->Height = temp;
			break;
		}
	}
}

System::Void UMLCreator::Constructor::deleteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		if (obj->Name == focused_name)
		{
			obj->Hide();
			m.lock();
			arrows.erase(Convert_String_to_string(obj->Name));
			m.unlock();
			pics->Remove(obj);
			delete obj;
			break;
		}
	}
}

System::Void UMLCreator::Constructor::create_new_pic_box(PictureBox^ pic, PictureBox^ obj)
{
	pic->Location = Point(12, 12);
	obj == nullptr ? pic->Size = System::Drawing::Size(22, 12) : pic->Size = obj->Size;
	pic->MinimumSize = System::Drawing::Size(22, 12);
	pics->Add(pic);
	pic->MouseDown += gcnew MouseEventHandler(this, &Constructor::pictureBox_MouseDown);
	pic->MouseUp += gcnew MouseEventHandler(this, &Constructor::pictureBox_MouseUp);
	pic->MouseMove += gcnew MouseEventHandler(this, &Constructor::pictureBox_MouseMove);
	pic->MouseClick += gcnew MouseEventHandler(this, &Constructor::pictureBox_Click);
	if (obj != nullptr && Convert_String_to_string(obj->Name).find("class_box") != npos)
	{
		pic->Name = Convert_string_to_String("class_box" + std::to_string(++classes_count));
	}
	else {
		pic->Name = Convert_string_to_String("AB" + std::to_string(count));
	}
	pic->BorderStyle = BorderStyle::FixedSingle;
	obj == nullptr ? pic->ImageLocation = Convert_string_to_String(get_data_dir() + "\\arrow_sample.png") : pic->Image = obj->Image;
	if (Convert_String_to_string(pic->Name).find("AB") != npos) {
		if (obj == nullptr || obj->Name == "arrow_sample") {
			ArrowProperities ap;
			m.lock();
			arrows["AB" + std::to_string(count++)] = ap;
			m.unlock();
		}
		else{
			m.lock();
			arrows["AB" + std::to_string(count++)] = arrows[Convert_String_to_string(obj->Name)];
			m.unlock();
		}
	}

}

System::Void UMLCreator::Constructor::agregatorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		if (obj->Name == focused_name)
		{
			arrows[Convert_String_to_string(obj->Name)].h = head::AGREGATION;
			break;
		}
	}
}

System::Void UMLCreator::Constructor::classicToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		if (obj->Name == focused_name)
		{
			arrows[Convert_String_to_string(obj->Name)].h = head::ARROW;
			break;
		}
	}
}

System::Void UMLCreator::Constructor::compositionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		if (obj->Name == focused_name)
		{
			arrows[Convert_String_to_string(obj->Name)].h = head::COMPOSITION;
			break;
		}
	}
}

System::Void UMLCreator::Constructor::inheritanceToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		if (obj->Name == focused_name)
		{
			arrows[Convert_String_to_string(obj->Name)].h = head::INHERITANCE;
			break;
		}
	}
}

System::Void UMLCreator::Constructor::solidToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		if (obj->Name == focused_name)
		{
			arrows[Convert_String_to_string(obj->Name)].b = body::SOLID;
			break;
		}
	}
}

System::Void UMLCreator::Constructor::dottedLineToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (size_t i = 0; i < pics->Components->Count; ++i)
	{
		PictureBox^ obj = safe_cast<PictureBox^>(pics->Components[i]);
		if (obj->Name == focused_name)
		{
			arrows[Convert_String_to_string(obj->Name)].b = body::DOTTED_LINE;
			break;
		}
	}

}

System::Void UMLCreator::Constructor::add_textbox_Click(System::Object^ sender, System::EventArgs^ e)
{
	TextBox^ tb = gcnew TextBox;
	tb->Location = Point(12, 12);
	tb->Size = System::Drawing::Size(20, 10);
	labels->Add(tb);
	tb->MouseDown += gcnew MouseEventHandler(this, &Constructor::textBox_MouseDown);
	tb->MouseUp += gcnew MouseEventHandler(this, &Constructor::textBox_MouseUp);
	tb->MouseMove += gcnew MouseEventHandler(this, &Constructor::textBox_MouseMove);
	tb->MinimumSize = System::Drawing::Size(20, 10);
	tb->Name = Convert_string_to_String("LB" + std::to_string(count++));
	tb->BorderStyle = BorderStyle::FixedSingle;
	this->Controls->Add(tb);
}

System::Void UMLCreator::Constructor::textBox_MouseDown(Object^ sender, MouseEventArgs^ args)
{
	down = true;
	TextBox^ obj = safe_cast<TextBox^>(sender);
	if (obj->Name == "text_sample")
	{
		textbox_sample_location = text_sample->Location;
		TextBox^ tb = gcnew TextBox;
		tb->Location = textbox_sample_location;
		tb->Size = System::Drawing::Size(20, 10);
		labels->Add(tb);
		tb->MouseDown += gcnew MouseEventHandler(this, &Constructor::textBox_MouseDown);
		tb->MouseUp += gcnew MouseEventHandler(this, &Constructor::textBox_MouseUp);
		tb->MouseMove += gcnew MouseEventHandler(this, &Constructor::textBox_MouseMove);
		tb->MinimumSize = System::Drawing::Size(20, 10);
		tb->Name = Convert_string_to_String("LB" + std::to_string(count++));
		tb->BorderStyle = BorderStyle::FixedSingle;
		this->Controls->Add(tb);
	}

	focused_name = obj->Name;
	fixed.X = Cursor->Position.X - this->Location.X;
	fixed.Y = Cursor->Position.Y - this->Location.Y;
	fixed.X -= obj->Location.X;
	fixed.Y -= obj->Location.Y;
}

System::Void UMLCreator::Constructor::textBox_MouseUp(Object^ sender, MouseEventArgs^ args)
{
	TextBox^ obj = safe_cast<TextBox^>(sender);
	if (obj->Name == "text_sample")
	{
		TextBox^ new_t_b = safe_cast<TextBox^>(labels->Components[labels->Components->Count - 1]);
		new_t_b->Location = obj->Location;
		obj->Location = textbox_sample_location;
	}

	down = false;
	moving = false;
	ab_resizing = false;
}

System::Void UMLCreator::Constructor::textBox_MouseMove(Object^ sender, MouseEventArgs^ args)
{
	Point p;
	TextBox^ obj = safe_cast<TextBox^>(sender);
	p.X = Cursor->Position.X;
	p.Y = Cursor->Position.Y;
	p.X -= this->Location.X;
	p.Y -= this->Location.Y;

	if ((obj->Name[0] == 'L' && obj->Name[1] == 'B' && (p.X < (obj->Location.X + obj->Width + 1) && p.X >(obj->Location.X + obj->Width - 6))
		|| ab_resizing) && !moving)
	{
		Cursor->Current = Cursors::VSplit;
		if (down)
		{
			ab_resizing = true;
			obj->Width = Cursor->Position.X - this->Location.X - obj->Location.X;
			obj->Height = Cursor->Position.Y - this->Location.Y - obj->Location.Y - 25;
		}
	}

	if (down && !ab_resizing)
	{
		moving = true;
		p.X -= fixed.X;
		p.Y -= fixed.Y;
		obj->Location = p;
	}
}

System::Void UMLCreator::Constructor::main_form_mouse_move(Object^ sender, MouseEventArgs^ args)
{
	if(!thread_created) {
		this->lb->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &UMLCreator::Constructor::lb_doubleclick);
		arrow_sample->ImageLocation = Convert_string_to_String(get_data_dir() + "\\arrow_sample.png");
		std::thread arrow_crerator(create_arrow, std::ref(arrows), std::ref(curr), std::ref(work), std::ref(m));
		arrow_crerator.detach();
		thread_created = true;
		work = true;
	}
}

System::Void UMLCreator::Constructor::back_to_res_form_Click(System::Object^ sender, System::EventArgs^ e)
{
	work = false;
	thread_created = false;
	UMLCreator::ResultForm^ next = gcnew UMLCreator::ResultForm(images_size);
	next->class_list->Items->AddRange(this->lb->Items);
	next->class_list->Visible = true;
	next->class_list->SetSelected(next->class_list->Items->Count - 1, true);
	this->Hide();
	next->Show();
	return System::Void();
}

System::Void UMLCreator::Constructor::lb_doubleclick(Object^ sender, MouseEventArgs^ args)
{
	std::string location = Convert_String_to_string(this->lb->SelectedItem != nullptr ? this->lb->SelectedItem->ToString() : this->lb->Items[this->lb->Items->Count - 1]->ToString());
	size_t space_ind = location.rfind(' ') + 1;
	location = location.substr(space_ind, location.rfind('{') - space_ind);
	PictureBox^ pic = gcnew PictureBox;
	pic->ImageLocation = Convert_string_to_String(location);
	System::Drawing::Size s;
	std::string size = Convert_String_to_string((this->lb->SelectedItem != nullptr ? this->lb->SelectedItem->ToString() : this->lb->Items[this->lb->Items->Count - 1]->ToString()));
	size = size.substr(size.rfind('{') + 1, size.size());
	s.Width = std::stoi(size.substr(0, size.find(',')));
	s.Height = std::stoi(size.substr(size.find(',') + 1, size.size()));
	pic->Size = s;
	pic->MouseDown += gcnew MouseEventHandler(this, &Constructor::pictureBox_MouseDown);
	pic->MouseUp += gcnew MouseEventHandler(this, &Constructor::pictureBox_MouseUp);
	pic->MouseMove += gcnew MouseEventHandler(this, &Constructor::pictureBox_MouseMove);
	pic->MouseClick += gcnew MouseEventHandler(this, &Constructor::pictureBox_Click);
	pic->Name = Convert_string_to_String(std::string("class_box" + std::to_string(++classes_count)));
	pic->BorderStyle = BorderStyle::None;
	pic->Location = Point(12, 12);
	this->pics->Add(pic);
	this->Controls->Add(pic);
}