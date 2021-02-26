#include <iostream>
#include <fstream>

#include "StartForm.h"
#include "ResultForm.h"
#include "ConvertFunction.h"
#include "standart_class.h"

System::Void UMLCreator::StartForm::YourselfStartForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::ofstream fout("ClassRead.txt");
	if (fout.is_open()) {
		fout << STANDART_CLASS;
		fout.close();
	}
	ResultForm^ form = gcnew ResultForm();
	this->Hide();
	form->Show();
}

System::Void UMLCreator::StartForm::CreateStartForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string str;
	Convert_String_to_string(ClassTextStartForm->Text->ToString(), str);
	std::ofstream fout("ClassRead.txt");
	if (fout.is_open()) {
		fout << str;
		fout.close();
	}
	ResultForm^ form = gcnew ResultForm();
	this->Hide();
	form->Show();
}
