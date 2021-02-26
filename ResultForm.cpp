#include "ResultForm.h"
#include "StartForm.h"

#include "ConvertFunction.h"
#include "FileWork.h"

System::Void UMLCreator::ResultForm::BackResultForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	StartForm^ form = gcnew StartForm();
	this->Hide();
	form->Show();
}

System::Void UMLCreator::ResultForm::RedactorResultForm_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
}

System::Void UMLCreator::ResultForm::ChangeResultForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string str;
	Convert_String_to_string(RedactorResultForm->Text->ToString(), str);
	WriteInFile("ParseClass.txt", str);
}
