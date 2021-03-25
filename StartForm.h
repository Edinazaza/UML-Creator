#pragma once
#include <stdlib.h>

namespace UMLCreator 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ StartForm
	/// </summary>
	public ref class StartForm : public System::Windows::Forms::Form
	{
	public:
		StartForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~StartForm()
		{
			if (components)
			{
				delete components;
			}
			exit(0);
		}
	private: System::Windows::Forms::TextBox^ ClassTextStartForm;

	private: System::Windows::Forms::Button^ CreateStartForm;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ back_to_result_form;
	public: ListBox^ class_list = gcnew ListBox;
	public: String^ text = gcnew String("");
	public: size_t count = 0;
	private: bool start = true;
	public: void set_back_button_visible() { this->back_to_result_form->Visible = true; }
	public: void set_start() { this->start = false; }

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(StartForm::typeid));
			this->ClassTextStartForm = (gcnew System::Windows::Forms::TextBox());
			this->CreateStartForm = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->back_to_result_form = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// ClassTextStartForm
			// 
			this->ClassTextStartForm->Location = System::Drawing::Point(36, 42);
			this->ClassTextStartForm->Margin = System::Windows::Forms::Padding(4);
			this->ClassTextStartForm->Multiline = true;
			this->ClassTextStartForm->Name = L"ClassTextStartForm";
			this->ClassTextStartForm->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->ClassTextStartForm->Size = System::Drawing::Size(539, 497);
			this->ClassTextStartForm->TabIndex = 0;
			// 
			// CreateStartForm
			// 
			this->CreateStartForm->Location = System::Drawing::Point(200, 547);
			this->CreateStartForm->Margin = System::Windows::Forms::Padding(4);
			this->CreateStartForm->Name = L"CreateStartForm";
			this->CreateStartForm->Size = System::Drawing::Size(201, 62);
			this->CreateStartForm->TabIndex = 3;
			this->CreateStartForm->Text = L"PARSE";
			this->CreateStartForm->UseVisualStyleBackColor = true;
			this->CreateStartForm->Click += gcnew System::EventHandler(this, &StartForm::CreateStartForm_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(253, 613);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(93, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"N.Krois \"Isus\"";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(124, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(337, 29);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Input any class or struct to start";
			// 
			// back_to_result_form
			// 
			this->back_to_result_form->Location = System::Drawing::Point(499, 547);
			this->back_to_result_form->Name = L"back_to_result_form";
			this->back_to_result_form->Size = System::Drawing::Size(98, 62);
			this->back_to_result_form->TabIndex = 6;
			this->back_to_result_form->Text = L"BACK";
			this->back_to_result_form->UseVisualStyleBackColor = true;
			this->back_to_result_form->Visible = false;
			this->back_to_result_form->Click += gcnew System::EventHandler(this, &StartForm::back_to_result_form_Click);
			// 
			// StartForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(609, 631);
			this->Controls->Add(this->back_to_result_form);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->CreateStartForm);
			this->Controls->Add(this->ClassTextStartForm);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(627, 678);
			this->MinimumSize = System::Drawing::Size(627, 678);
			this->Name = L"StartForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UML Creator";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CreateStartForm_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void back_to_result_form_Click(System::Object^ sender, System::EventArgs^ e);
};
}
