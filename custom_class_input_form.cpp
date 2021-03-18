#include "custom_class_input_form.h"
#include "ResultForm.h"
#include "Parser.h"

System::Void UMLCreator::custom_class_input_form::save_CIbox_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::ofstream stream(get_data_dir() + "\\cc.dtt");
	String^ text = Cibox->Text->ToString();
	std::string str = parse_text_from_box(text);
	stream << str;
	stream.close();
	Cibox->Text = parse_custom_classes();
	return System::Void();
}

System::Void UMLCreator::custom_class_input_form::back_to_main_form_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Hide();
	return System::Void();
}

