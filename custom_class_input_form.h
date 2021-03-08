#pragma once
#include "ConvertFunction.h"
#include "UMLParser.h"

namespace UMLCreator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ custom_class_input_form
	/// </summary>
	public ref class custom_class_input_form : public System::Windows::Forms::Form
	{
	public:
		custom_class_input_form(void)
		{
			InitializeComponent();
			Cibox->Text = parse_custom_classes();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~custom_class_input_form()
		{
			if (components)
			{
				delete components;
			}
			exit(0);
		}
	private: System::Windows::Forms::RichTextBox^ Cibox;
	protected:
	private: System::Windows::Forms::Button^ save_CIbox;
	private: System::Windows::Forms::Button^ back_to_main_form;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(custom_class_input_form::typeid));
			this->Cibox = (gcnew System::Windows::Forms::RichTextBox());
			this->save_CIbox = (gcnew System::Windows::Forms::Button());
			this->back_to_main_form = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Cibox
			// 
			this->Cibox->Location = System::Drawing::Point(12, 12);
			this->Cibox->Name = L"Cibox";
			this->Cibox->Size = System::Drawing::Size(399, 360);
			this->Cibox->TabIndex = 1;
			this->Cibox->Text = L"";
			// 
			// save_CIbox
			// 
			this->save_CIbox->Location = System::Drawing::Point(37, 378);
			this->save_CIbox->Name = L"save_CIbox";
			this->save_CIbox->Size = System::Drawing::Size(119, 43);
			this->save_CIbox->TabIndex = 2;
			this->save_CIbox->Text = L"SAVE";
			this->save_CIbox->UseVisualStyleBackColor = true;
			this->save_CIbox->Click += gcnew System::EventHandler(this, &custom_class_input_form::save_CIbox_Click);
			// 
			// back_to_main_form
			// 
			this->back_to_main_form->Location = System::Drawing::Point(262, 378);
			this->back_to_main_form->Name = L"back_to_main_form";
			this->back_to_main_form->Size = System::Drawing::Size(119, 43);
			this->back_to_main_form->TabIndex = 3;
			this->back_to_main_form->Text = L"BACK";
			this->back_to_main_form->UseVisualStyleBackColor = true;
			this->back_to_main_form->Click += gcnew System::EventHandler(this, &custom_class_input_form::back_to_main_form_Click);
			// 
			// custom_class_input_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(436, 448);
			this->Controls->Add(this->back_to_main_form);
			this->Controls->Add(this->save_CIbox);
			this->Controls->Add(this->Cibox);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"custom_class_input_form";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Custom Class Redactor";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void save_CIbox_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void back_to_main_form_Click(System::Object^ sender, System::EventArgs^ e);

	};
}
