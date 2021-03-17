#pragma once
#include <stdlib.h>

namespace UMLCreator {

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
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ YourselfStartForm;
	private: System::Windows::Forms::Button^ CreateStartForm;
	private: System::Windows::Forms::Label^ label2;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->YourselfStartForm = (gcnew System::Windows::Forms::Button());
			this->CreateStartForm = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// ClassTextStartForm
			// 
			this->ClassTextStartForm->Location = System::Drawing::Point(36, 43);
			this->ClassTextStartForm->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->ClassTextStartForm->Multiline = true;
			this->ClassTextStartForm->Name = L"ClassTextStartForm";
			this->ClassTextStartForm->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->ClassTextStartForm->Size = System::Drawing::Size(539, 496);
			this->ClassTextStartForm->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Courier New", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(111, 0);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(369, 39);
			this->label1->TabIndex = 1;
			this->label1->Text = L"ENTER YOUR CLASS";
			// 
			// YourselfStartForm
			// 
			this->YourselfStartForm->Location = System::Drawing::Point(36, 548);
			this->YourselfStartForm->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->YourselfStartForm->Name = L"YourselfStartForm";
			this->YourselfStartForm->Size = System::Drawing::Size(201, 62);
			this->YourselfStartForm->TabIndex = 2;
			this->YourselfStartForm->Text = L"DO IT YOURSELF";
			this->YourselfStartForm->UseVisualStyleBackColor = true;
			this->YourselfStartForm->Click += gcnew System::EventHandler(this, &StartForm::YourselfStartForm_Click);
			// 
			// CreateStartForm
			// 
			this->CreateStartForm->Location = System::Drawing::Point(375, 548);
			this->CreateStartForm->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->CreateStartForm->Name = L"CreateStartForm";
			this->CreateStartForm->Size = System::Drawing::Size(201, 62);
			this->CreateStartForm->TabIndex = 3;
			this->CreateStartForm->Text = L"CREATE";
			this->CreateStartForm->UseVisualStyleBackColor = true;
			this->CreateStartForm->Click += gcnew System::EventHandler(this, &StartForm::CreateStartForm_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(260, 615);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(93, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"N.Krois \"Isus\"";
			// 
			// StartForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(609, 631);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->CreateStartForm);
			this->Controls->Add(this->YourselfStartForm);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ClassTextStartForm);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(627, 678);
			this->MinimumSize = System::Drawing::Size(627, 678);
			this->Name = L"StartForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UML Creator";
			this->Load += gcnew System::EventHandler(this, &StartForm::StartForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void StartForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void YourselfStartForm_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void CreateStartForm_Click(System::Object^ sender, System::EventArgs^ e);
};
}
