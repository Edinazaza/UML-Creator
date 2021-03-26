#include <iostream>
#include <fstream>

#include "StartForm.h"
#include "ResultForm.h"

#include "Parser.h"
#include "ConvertFunction.h"
#include "standart_class.h"
#include "FileWork.h"
#include "CreateImageSFML.h"

#define PARSE_INPUT_EXCEPTION \
MessageBox^ mb;\
mb->Show(this, "Wrong input!", "Error");\
return System::Void();

System::Void UMLCreator::StartForm::CreateStartForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ClassTextStartForm->Text->Length < 9) {PARSE_INPUT_EXCEPTION}

	std::string str;
	Convert_String_to_string(ClassTextStartForm->Text->ToString(), str);

	DataCollector DC_PARSER;
	create_dir(DC_PARSER);
	WriteInFile(get_data_dir() + "\\ClassRead.txt", str);

	std::ifstream source(get_data_dir() + "\\ClassRead.txt");
	size_t counter = parse_several_classes(source, (get_data_dir() + "\\ParseClass.txt"), this->count+1);
	if(counter == 0) { PARSE_INPUT_EXCEPTION }
	auto res = ParserUmlAndChangeImage(counter);
	this->Hide();
	if (start)
	{
		ResultForm^ form = gcnew ResultForm(res.first, res.second);
		form->Show();
	}
	else
	{
		ResultForm^ form = gcnew ResultForm(res.first, res.second);
		form->_new = false;
		form->Show();
	}
}

System::Void UMLCreator::StartForm::back_to_result_form_Click(System::Object^ sender, System::EventArgs^ e)
{
	auto res = ParserUmlAndChangeImage(this->count);
	ResultForm^ form = gcnew ResultForm(res.first, res.second);
	form->_new = false;
	form->Show();
	this->Hide();
	return System::Void();
}
