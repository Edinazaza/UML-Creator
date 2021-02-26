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
