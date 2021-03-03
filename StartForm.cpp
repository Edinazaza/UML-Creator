#include <iostream>
#include <fstream>

#include "StartForm.h"
#include "ResultForm.h"

#include "Parser.h"
#include "ConvertFunction.h"
#include "standart_class.h"
#include "FileWork.h"
#include "CreateImageSFML.h"

System::Void UMLCreator::StartForm::YourselfStartForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	DataCollector DC_PARSER;
	create_dir(DC_PARSER);
	WriteInFile(get_data_dir() + "\\ClassRead.txt", STANDART_CLASS);
	/*DC_PARSER.Parse(get_data_dir() + "\\ClassRead.txt");
	DC_PARSER.output(get_data_dir() + "\\ParseClass.txt");*/
	std::ifstream source(get_data_dir() + "\\ClassRead.txt");
	parse_several_classes(source, (get_data_dir() + "\\ParseClass.txt"));
	ParserUmlAndChangeImage(get_data_dir() + "\\output.jpg");

	ResultForm^ form = gcnew ResultForm();
	this->Hide();
	form->Show();
}

System::Void UMLCreator::StartForm::CreateStartForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string str;
	Convert_String_to_string(ClassTextStartForm->Text->ToString(), str);

	DataCollector DC_PARSER;
	create_dir(DC_PARSER);
	WriteInFile(get_data_dir() + "\\ClassRead.txt", str);

	/*DC_PARSER.Parse(get_data_dir() + "\\ClassRead.txt");
	DC_PARSER.output(get_data_dir() + "\\ParseClass.txt");*/
	std::ifstream source(get_data_dir() + "\\ClassRead.txt");
	parse_several_classes(source, (get_data_dir() + "\\ParseClass.txt"));

	ParserUmlAndChangeImage(get_data_dir() + "\\output.jpg");

	ResultForm^ form = gcnew ResultForm();
	this->Hide();
	form->Show();
}
