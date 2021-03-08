#include "ResultForm.h"
#include "StartForm.h"

#include "ConvertFunction.h"
#include "FileWork.h"
#include "CreateImageSFML.h"
#include "Parser.h"

System::Void UMLCreator::ResultForm::BackResultForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	delete this->PictureResultForm->Image;
	StartForm^ form = gcnew StartForm();
	this->Hide();
	form->Show();
}

System::Void UMLCreator::ResultForm::RedactorResultForm_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
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
	UMLCreator::custom_class_input_form^ next_form = gcnew UMLCreator::custom_class_input_form();
	this->Hide();
	next_form->Show();
	return System::Void();
}
