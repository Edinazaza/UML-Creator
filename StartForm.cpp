#include <iostream>
#include <fstream>

#include "StartForm.h"
#include "ResultForm.h"

#include "Parser.h"
#include "ConvertFunction.h"
#include "standart_class.h"
#include "FileWork.h"

System::Void UMLCreator::StartForm::YourselfStartForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	WriteInFile("ClassRead.txt", STANDART_CLASS);
	//do class of bogdan
	DataCollector DC_PARSER;
	DC_PARSER.Parse("ClassRead.txt");
	DC_PARSER.output("ParseClass.txt");
	ResultForm^ form = gcnew ResultForm();
	this->Hide();
	form->Show();
}

System::Void UMLCreator::StartForm::CreateStartForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string str;
	Convert_String_to_string(ClassTextStartForm->Text->ToString(), str);
	WriteInFile("ClassRead.txt", str);

	DataCollector DC_PARSER;
	DC_PARSER.Parse("ClassRead.txt");
	DC_PARSER.output("ParseClass.txt");

	ResultForm^ form = gcnew ResultForm();
	this->Hide();
	form->Show();
}
