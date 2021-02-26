#pragma once
#include "FileWork.h"
#include "ConvertFunction.h"

#include <string>
#include <fstream>
#include <iostream>

namespace UMLCreator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ ResultForm
	/// </summary>
	public ref class ResultForm : public System::Windows::Forms::Form
	{
	public:
		ResultForm(void)
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
		~ResultForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ PictureResultForm;
	protected:
	private: System::Windows::Forms::TextBox^ RedactorResultForm;
	private: System::Windows::Forms::Button^ DownloadResultForm;
	private: System::Windows::Forms::Button^ ChangeResultForm;
	private: System::Windows::Forms::Button^ BackResultForm;

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
			this->PictureResultForm = (gcnew System::Windows::Forms::PictureBox());
			this->RedactorResultForm = (gcnew System::Windows::Forms::TextBox());
			this->DownloadResultForm = (gcnew System::Windows::Forms::Button());
			this->ChangeResultForm = (gcnew System::Windows::Forms::Button());
			this->BackResultForm = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureResultForm))->BeginInit();
			this->SuspendLayout();
			// 
			// PictureResultForm
			// 
			this->PictureResultForm->Location = System::Drawing::Point(408, 12);
			this->PictureResultForm->Name = L"PictureResultForm";
			this->PictureResultForm->Size = System::Drawing::Size(353, 448);
			this->PictureResultForm->TabIndex = 0;
			this->PictureResultForm->TabStop = false;
			// 
			// RedactorResultForm
			// 
			this->RedactorResultForm->Location = System::Drawing::Point(35, 12);
			this->RedactorResultForm->Multiline = true;
			this->RedactorResultForm->Name = L"RedactorResultForm";
			this->RedactorResultForm->Size = System::Drawing::Size(345, 447);
			this->RedactorResultForm->TabIndex = 1;
			this->RedactorResultForm->TextChanged += gcnew System::EventHandler(this, &ResultForm::RedactorResultForm_TextChanged);
			
			std::ifstream ifs("ParseClass.txt");
			std::string s;
			this->RedactorResultForm->Text = L"";
			while (std::getline(ifs, s)) {
				this->RedactorResultForm->Text += Convert_string_to_String(s) + System::Environment::NewLine;
			}
			ifs.close();
			
			// 
			// DownloadResultForm
			// 
			this->DownloadResultForm->Location = System::Drawing::Point(517, 470);
			this->DownloadResultForm->Name = L"DownloadResultForm";
			this->DownloadResultForm->Size = System::Drawing::Size(159, 37);
			this->DownloadResultForm->TabIndex = 2;
			this->DownloadResultForm->Text = L"DOWNLOAD";
			this->DownloadResultForm->UseVisualStyleBackColor = true;
			// 
			// ChangeResultForm
			// 
			this->ChangeResultForm->Location = System::Drawing::Point(122, 465);
			this->ChangeResultForm->Name = L"ChangeResultForm";
			this->ChangeResultForm->Size = System::Drawing::Size(159, 37);
			this->ChangeResultForm->TabIndex = 3;
			this->ChangeResultForm->Text = L"CHANGE";
			this->ChangeResultForm->UseVisualStyleBackColor = true;
			this->ChangeResultForm->Click += gcnew System::EventHandler(this, &ResultForm::ChangeResultForm_Click);
			// 
			// BackResultForm
			// 
			this->BackResultForm->Location = System::Drawing::Point(35, 465);
			this->BackResultForm->Name = L"BackResultForm";
			this->BackResultForm->Size = System::Drawing::Size(48, 37);
			this->BackResultForm->TabIndex = 4;
			this->BackResultForm->Text = L"BACK";
			this->BackResultForm->UseVisualStyleBackColor = true;
			this->BackResultForm->Click += gcnew System::EventHandler(this, &ResultForm::BackResultForm_Click);
			// 
			// ResultForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(773, 519);
			this->Controls->Add(this->BackResultForm);
			this->Controls->Add(this->ChangeResultForm);
			this->Controls->Add(this->DownloadResultForm);
			this->Controls->Add(this->RedactorResultForm);
			this->Controls->Add(this->PictureResultForm);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(789, 558);
			this->MinimumSize = System::Drawing::Size(789, 558);
			this->Name = L"ResultForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UML Creator";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureResultForm))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BackResultForm_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void RedactorResultForm_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ChangeResultForm_Click(System::Object^ sender, System::EventArgs^ e);
};
}
