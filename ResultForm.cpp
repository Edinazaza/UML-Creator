#include "ResultForm.h"
#include "StartForm.h"

#include "ConvertFunction.h"
#include "FileWork.h"
#include "CreateImageSFML.h"

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
	WriteInFile("ParseClass.txt", str);
	ParserUmlAndChangeImage();
	Bitmap^ img = gcnew Bitmap("output.jpg");
	this->PictureResultForm->Image = img;
	this->PictureResultForm->Refresh();
	this->PictureResultForm->Visible = true;
}

System::Void UMLCreator::ResultForm::PictureResultForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	delete this->PictureResultForm->Image;
	this->PictureResultForm->Image = gcnew Bitmap("output.jpg");
	this->PictureResultForm->Refresh();
	this->PictureResultForm->Visible = true;
}

System::Void UMLCreator::ResultForm::DownloadResultForm_Click_1(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("You Diagram in file output.jpg! Pls donate for developer!", "Download", MessageBoxButtons::OK);
}
