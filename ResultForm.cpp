#include "ResultForm.h"
#include "StartForm.h"

System::Void UMLCreator::ResultForm::BackResultForm_Click(System::Object^ sender, System::EventArgs^ e)
{
	StartForm^ form = gcnew StartForm();
	this->Hide();
	form->Show();
}
