#include "ResultForm.h"
#include "StartForm.h"

#include "ConvertFunction.h"
#include "FileWork.h"
#include "CreateImageSFML.h"
#include "Parser.h"

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
	delete this->PictureResultForm->Image;
	std::string str;
	Convert_String_to_string(RedactorResultForm->Text->ToString(), str);
	WriteInFile(get_data_dir() + "\\ParseClass.txt", str);
	ParserUmlAndChangeImage(get_data_dir() + "\\output.jpg");
	Bitmap^ img = gcnew Bitmap(Convert_string_to_String(get_data_dir() + "\\output.jpg"));
	this->PictureResultForm->Image = img;
	this->PictureResultForm->Refresh();
	this->PictureResultForm->Visible = true;
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
	delete this->PictureResultForm->Image;
	UMLCreator::custom_class_input_form^ next_form = gcnew UMLCreator::custom_class_input_form();
	this->Hide();
	next_form->Show();
	return System::Void();
}

System::Void UMLCreator::ResultForm::constructor_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	delete this->PictureResultForm->Image;
	UMLCreator::Constructor^ next_form = gcnew UMLCreator::Constructor(work, images_size);
	
	for (size_t i = 1; i <= images_size; ++i)
	{
		PictureBox^ pic = gcnew PictureBox;
		Image^ image = Image::FromFile(Convert_string_to_String(get_data_dir() + "\\class_img" + std::to_string(i) + ".png"));
		pic->Size = image->Size;
		pic->Image = image;
		pic->MouseDown += gcnew MouseEventHandler(next_form, &Constructor::pictureBox_MouseDown);
		pic->MouseUp += gcnew MouseEventHandler(next_form, &Constructor::pictureBox_MouseUp);
		pic->MouseMove += gcnew MouseEventHandler(next_form, &Constructor::pictureBox_MouseMove);
		pic->MouseClick += gcnew MouseEventHandler(next_form, &Constructor::pictureBox_Click);
		pic->Name = Convert_string_to_String(std::string("class_box"));
		pic->BorderStyle = BorderStyle::FixedSingle;
		pic->Location = Point(12, 12);
		next_form->pics->Add(pic);
		next_form->Controls->Add(pic);
	}
	this->Hide();
	next_form->Show();
	return System::Void();
}
