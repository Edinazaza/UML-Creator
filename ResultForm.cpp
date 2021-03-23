#include "ResultForm.h"
#include "StartForm.h"

#include "ConvertFunction.h"
#include "FileWork.h"
#include "CreateImageSFML.h"
#include "Parser.h"
#include "UMLParser.h"

bool work = true; 

System::Void UMLCreator::ResultForm::BackResultForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	delete this->PictureResultForm->Image;
	StartForm^ form = gcnew StartForm();
	this->Hide();
	form->Show();
}

System::Void UMLCreator::ResultForm::ChangeResultForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->RedactorResultForm->Text->Length < 60 && this->class_list->SelectedItem == nullptr) 
	{
		return System::Void(); 
	}
	std::string str;
	Convert_String_to_string(RedactorResultForm->Text->ToString(), str);
	str = change_text_by_tags(Convert_String_to_string(this->text), str, 
		this->class_list->SelectedIndex == -1 ? this->class_list->Items->Count : this->class_list->SelectedIndex + 1);
	WriteInFile(get_data_dir() + "\\ParseClass.txt", str);
	this->text = Convert_string_to_String(str);
	std::string location;

	if (this->class_list->SelectedItem != nullptr) 
	{
		location = Convert_String_to_string(this->class_list->SelectedItem->ToString());
	}
	else
	{
		location = Convert_String_to_string(class_list->Items[class_list->Items->Count - 1]->ToString());
	}

	size_t space_ind = location.rfind(' ') + 1;
	location = location.substr(space_ind, location.rfind('{') - space_ind);
	size_t counter;
	for (size_t i = 0; i < location.size(); ++i)
	{
		if (isdigit(location[i]))
		{
			counter = size_t(std::stoi(location.substr(i, location.rfind('.'))));
			break;
		}
	}
	auto ret = ParserUmlAndChangeImage(counter, counter);
	this->change_class_list(ret.second, counter-1);
	
	this->PictureResultForm->ImageLocation = Convert_string_to_String(location);
	//Bitmap^ img = gcnew Bitmap(Convert_string_to_String(location));
	//this->PictureResultForm->Image = img;
	//this->PictureResultForm->Refresh();
	//this->PictureResultForm->Visible = true;
}

System::Void UMLCreator::ResultForm::PictureResultForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	delete this->PictureResultForm->Image;
	this->PictureResultForm->Image = gcnew Bitmap(Convert_string_to_String(get_data_dir() + "\\output.jpg"));
	this->PictureResultForm->Refresh();
	this->PictureResultForm->Visible = true;
}

System::Void UMLCreator::ResultForm::DownloadResultForm_Click_1(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ downloadImage = gcnew SaveFileDialog();
	downloadImage->DefaultExt = ".jpg";
	downloadImage->FileName = "out.jpg";
	if (downloadImage->ShowDialog() != System::Windows::Forms::DialogResult::OK) {
		return;
	}
	//std::string filename;
	//Convert_String_to_string(downloadImage->FileName->ToString(), filename);
	this->PictureResultForm->Image->Save(downloadImage->FileName->ToString());

	MessageBox::Show(downloadImage->FileName->ToString(), "Download", MessageBoxButtons::OK);
}

System::Void UMLCreator::ResultForm::ccr_Click(System::Object^ sender, System::EventArgs^ e)
{
	UMLCreator::custom_class_input_form^ next_form = gcnew UMLCreator::custom_class_input_form();
	next_form->Show();
	return System::Void();
}

System::Void UMLCreator::ResultForm::constructor_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	create_default_arrow();
	delete this->PictureResultForm->Image;
	UMLCreator::Constructor^ next_form = gcnew UMLCreator::Constructor(work, images_size);
	next_form->lb->Items->AddRange(this->class_list->Items);
	next_form->lb->Visible = true;
	next_form->lb->Size = System::Drawing::Size(53, 121);
	next_form->lb->Location = Point(next_form->Width - next_form->lb->Width-16, 0);
	next_form->lb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
	next_form->Controls->Add(next_form->lb);
	for (size_t i = 1; i <= images_size; ++i)
	{
		PictureBox^ pic = gcnew PictureBox;
		pic->ImageLocation = Convert_string_to_String(get_data_dir() + "\\class_img" + std::to_string(i) + ".png");
		System::Drawing::Size s;
		std::string size = Convert_String_to_string(this->class_list->Items[i-1]->ToString());
		size = size.substr(size.rfind('{') + 1, size.size());
		s.Width = std::stoi(size.substr(0, size.find(',')));
		s.Height = std::stoi(size.substr(size.find(',')+1, size.size()));
		pic->Size = s;
		pic->MouseDown += gcnew MouseEventHandler(next_form, &Constructor::pictureBox_MouseDown);
		pic->MouseUp += gcnew MouseEventHandler(next_form, &Constructor::pictureBox_MouseUp);
		pic->MouseMove += gcnew MouseEventHandler(next_form, &Constructor::pictureBox_MouseMove);
		pic->MouseClick += gcnew MouseEventHandler(next_form, &Constructor::pictureBox_Click);
		pic->Name = Convert_string_to_String(std::string("class_box" + std::to_string(i)));
		pic->BorderStyle = BorderStyle::None;
		pic->Location = Point(12, 12);
		next_form->pics->Add(pic);
		next_form->Controls->Add(pic);
	}

	this->Hide();
	next_form->Show();
	return System::Void();
}

System::Void UMLCreator::ResultForm::class_list_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	ListBox^ obj = safe_cast<ListBox^>(sender);
	if (obj->SelectedItem != nullptr) {
		std::string location = Convert_String_to_string(obj->SelectedItem->ToString());
		size_t space_ind = location.rfind(' ') + 1;
		location = location.substr(space_ind, location.rfind('{') - space_ind);
		this->PictureResultForm->ImageLocation = Convert_string_to_String(location);
		std::string new_text = Convert_String_to_string(this->text);
		std::string o_tag = "<" + std::to_string(obj->SelectedIndex+1) + "name>";
		std::string c_tag = "</" + std::to_string(obj->SelectedIndex+1) + "methods>";
		this->RedactorResultForm->Text = Convert_string_to_String(new_text.substr(new_text.find(o_tag), new_text.find(c_tag) + c_tag.size()));
	}
}
