#pragma once
#include "FileWork.h"
#include "ConvertFunction.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "Parser.h"
#include "custom_class_input_form.h"

namespace UMLCreator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Ñâîäêà äëÿ ResultForm
	/// </summary>
	public ref class ResultForm : public System::Windows::Forms::Form
	{
	public:
		ResultForm(size_t _images_size,
			std::vector<std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>>>  classes) : images_size(_images_size)
		{
			InitializeComponent();
			for (auto& item : classes)
			{
				class_list->Items->Add(Convert_string_to_String(item.first + "                " + item.second.first
					+ "{" + std::to_string(item.second.second.first) + "," + std::to_string(item.second.second.second) +"}"));
			}
			this->class_list->SetSelected(class_list->Items->Count - 1, true);
		}

		void change_class_list(std::vector<std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>>> classes, size_t index)
		{
			if (index <= class_list->Items->Count - 1) {
				class_list->Items[index] =
					Convert_string_to_String(classes.front().first + "                " + classes.front().second.first
						+ "{" + std::to_string(classes.front().second.second.first) + "," +
						std::to_string(classes.front().second.second.second) + "}");
			}
			else
			{
				class_list->Items->Add(Convert_string_to_String(classes.front().first + "                " + classes.front().second.first
					+ "{" + std::to_string(classes.front().second.second.first) + "," +
					std::to_string(classes.front().second.second.second) + "}"));
			}
		}

		ResultForm(size_t _images_size) : images_size(_images_size)
		{
			InitializeComponent();
			class_list->Visible = true;
		}

		ResultForm(void)
		{
			InitializeComponent();
			//
			//TODO: äîáàâüòå êîä êîíñòðóêòîðà
			//
		}

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ðåñóðñû.
		/// </summary>
		~ResultForm()
		{
			if (components)
			{
				delete components;
			}
			delete this->PictureResultForm->Image;
			exit(0);
		}
	private: System::Windows::Forms::PictureBox^ PictureResultForm;
	private: System::ComponentModel::Container^ result_pics = gcnew System::ComponentModel::Container;
	protected:
	private: System::Windows::Forms::Button^ DownloadResultForm;
	public: size_t images_size;
	public: String^ text = gcnew String("");
	public: bool _new = true;
	private: size_t diagramm_size = 1;
	private: System::Windows::Forms::Button^ ChangeResultForm;
	private: System::Windows::Forms::Button^ BackResultForm;
	private: System::Windows::Forms::Button^ ccr;
	private: System::Windows::Forms::RichTextBox^ RedactorResultForm;
	private: System::Windows::Forms::Button^ constructor_button;
	public: ListBox^ class_list = gcnew ListBox;
	private: System::Windows::Forms::Button^ add_class;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ size_2_rb;
	private: System::Windows::Forms::RadioButton^ size_1_rb;
	private: System::Windows::Forms::RadioButton^ size_3_rb;
	public:


	private:
		/// <summary>
		/// Îáÿçàòåëüíàÿ ïåðåìåííàÿ êîíñòðóêòîðà.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Òðåáóåìûé ìåòîä äëÿ ïîääåðæêè êîíñòðóêòîðà — íå èçìåíÿéòå 
		/// ñîäåðæèìîå ýòîãî ìåòîäà ñ ïîìîùüþ ðåäàêòîðà êîäà.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ResultForm::typeid));
			this->PictureResultForm = (gcnew System::Windows::Forms::PictureBox());
			this->DownloadResultForm = (gcnew System::Windows::Forms::Button());
			this->ChangeResultForm = (gcnew System::Windows::Forms::Button());
			this->BackResultForm = (gcnew System::Windows::Forms::Button());
			this->ccr = (gcnew System::Windows::Forms::Button());
			this->RedactorResultForm = (gcnew System::Windows::Forms::RichTextBox());
			this->constructor_button = (gcnew System::Windows::Forms::Button());
			this->class_list = (gcnew System::Windows::Forms::ListBox());
			this->add_class = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->size_2_rb = (gcnew System::Windows::Forms::RadioButton());
			this->size_1_rb = (gcnew System::Windows::Forms::RadioButton());
			this->size_3_rb = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureResultForm))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// PictureResultForm
			// 
			this->PictureResultForm->Location = System::Drawing::Point(545, 15);
			this->PictureResultForm->Margin = System::Windows::Forms::Padding(4);
			this->PictureResultForm->Name = L"PictureResultForm";
			this->PictureResultForm->Size = System::Drawing::Size(469, 549);
			this->PictureResultForm->TabIndex = 0;
			this->PictureResultForm->TabStop = false;
			this->PictureResultForm->Click += gcnew System::EventHandler(this, &ResultForm::PictureResultForm_Click);
			// 
			// DownloadResultForm
			// 
			this->DownloadResultForm->Location = System::Drawing::Point(545, 572);
			this->DownloadResultForm->Margin = System::Windows::Forms::Padding(4);
			this->DownloadResultForm->Name = L"DownloadResultForm";
			this->DownloadResultForm->Size = System::Drawing::Size(155, 46);
			this->DownloadResultForm->TabIndex = 2;
			this->DownloadResultForm->Text = L"DOWNLOAD";
			this->DownloadResultForm->UseVisualStyleBackColor = true;
			this->DownloadResultForm->Click += gcnew System::EventHandler(this, &ResultForm::DownloadResultForm_Click_1);
			// 
			// ChangeResultForm
			// 
			this->ChangeResultForm->Location = System::Drawing::Point(145, 574);
			this->ChangeResultForm->Margin = System::Windows::Forms::Padding(4);
			this->ChangeResultForm->Name = L"ChangeResultForm";
			this->ChangeResultForm->Size = System::Drawing::Size(173, 46);
			this->ChangeResultForm->TabIndex = 3;
			this->ChangeResultForm->Text = L"CHANGE";
			this->ChangeResultForm->UseVisualStyleBackColor = true;
			this->ChangeResultForm->Click += gcnew System::EventHandler(this, &ResultForm::ChangeResultForm_Click);
			// 
			// BackResultForm
			// 
			this->BackResultForm->Location = System::Drawing::Point(47, 572);
			this->BackResultForm->Margin = System::Windows::Forms::Padding(4);
			this->BackResultForm->Name = L"BackResultForm";
			this->BackResultForm->Size = System::Drawing::Size(64, 46);
			this->BackResultForm->TabIndex = 4;
			this->BackResultForm->Text = L"BACK";
			this->BackResultForm->UseVisualStyleBackColor = true;
			this->BackResultForm->Click += gcnew System::EventHandler(this, &ResultForm::BackResultForm_Click);
			// 
			// ccr
			// 
			this->ccr->Location = System::Drawing::Point(357, 574);
			this->ccr->Margin = System::Windows::Forms::Padding(4);
			this->ccr->Name = L"ccr";
			this->ccr->Size = System::Drawing::Size(133, 46);
			this->ccr->TabIndex = 5;
			this->ccr->Text = L"CUSTOM CLASS READCTOR";
			this->ccr->UseVisualStyleBackColor = true;
			this->ccr->Click += gcnew System::EventHandler(this, &ResultForm::ccr_Click);
			// 
			// RedactorResultForm
			// 
			this->RedactorResultForm->Location = System::Drawing::Point(47, 15);
			this->RedactorResultForm->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->RedactorResultForm->Name = L"RedactorResultForm";
			this->RedactorResultForm->Size = System::Drawing::Size(465, 549);
			this->RedactorResultForm->TabIndex = 6;
			this->RedactorResultForm->Text = L"";
			if (_new) {
				std::ifstream ifs(get_data_dir() + "\\ParseClass.txt");
				std::string s;
				this->RedactorResultForm->Text = L"";
				std::string tag = "<" + std::to_string(images_size) + "name>";
				bool is_found = false;
				while (std::getline(ifs, s)) {
					text += Convert_string_to_String(s) + "\n";
					if (s == tag) { is_found = true; }
					if (is_found) {
						this->RedactorResultForm->Text += Convert_string_to_String(s) + System::Environment::NewLine;
					}
				}
				ifs.close();
			}
			// 
			// constructor_button
			// 
			this->constructor_button->Location = System::Drawing::Point(739, 574);
			this->constructor_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->constructor_button->Name = L"constructor_button";
			this->constructor_button->Size = System::Drawing::Size(147, 46);
			this->constructor_button->TabIndex = 7;
			this->constructor_button->Text = L"CONSTRUCTOR (alfa)";
			this->constructor_button->UseVisualStyleBackColor = true;
			this->constructor_button->Click += gcnew System::EventHandler(this, &ResultForm::constructor_button_Click);
			// 
			// class_list
			// 
			this->class_list->FormattingEnabled = true;
			this->class_list->ItemHeight = 16;
			this->class_list->Location = System::Drawing::Point(1023, 36);
			this->class_list->Margin = System::Windows::Forms::Padding(4);
			this->class_list->MultiColumn = true;
			this->class_list->Name = L"class_list";
			this->class_list->Size = System::Drawing::Size(69, 148);
			this->class_list->TabIndex = 8;
			this->class_list->SelectedIndexChanged += gcnew System::EventHandler(this, &ResultForm::class_list_SelectedIndexChanged);
			// 
			// add_class
			// 
			this->add_class->Location = System::Drawing::Point(909, 574);
			this->add_class->Name = L"add_class";
			this->add_class->Size = System::Drawing::Size(105, 46);
			this->add_class->TabIndex = 9;
			this->add_class->Text = L"ADD CLASS";
			this->add_class->UseVisualStyleBackColor = true;
			this->add_class->Click += gcnew System::EventHandler(this, &ResultForm::add_class_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->size_3_rb);
			this->groupBox1->Controls->Add(this->size_2_rb);
			this->groupBox1->Controls->Add(this->size_1_rb);
			this->groupBox1->Location = System::Drawing::Point(1021, 191);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(94, 119);
			this->groupBox1->TabIndex = 11;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"diagramms size";
			// 
			// size_2_rb
			// 
			this->size_2_rb->AutoSize = true;
			this->size_2_rb->Location = System::Drawing::Point(7, 64);
			this->size_2_rb->Name = L"size_2_rb";
			this->size_2_rb->Size = System::Drawing::Size(42, 21);
			this->size_2_rb->TabIndex = 1;
			this->size_2_rb->Text = L"-1";
			this->size_2_rb->UseVisualStyleBackColor = true;
			this->size_2_rb->CheckedChanged += gcnew System::EventHandler(this, &ResultForm::size_2_rb_CheckedChanged);
			// 
			// size_1_rb
			// 
			this->size_1_rb->AutoSize = true;
			this->size_1_rb->Checked = true;
			this->size_1_rb->Location = System::Drawing::Point(7, 36);
			this->size_1_rb->Name = L"size_1_rb";
			this->size_1_rb->Size = System::Drawing::Size(82, 21);
			this->size_1_rb->TabIndex = 0;
			this->size_1_rb->TabStop = true;
			this->size_1_rb->Text = L"common";
			this->size_1_rb->UseVisualStyleBackColor = true;
			this->size_1_rb->CheckedChanged += gcnew System::EventHandler(this, &ResultForm::size_1_rb_CheckedChanged);
			// 
			// size_3_rb
			// 
			this->size_3_rb->AutoSize = true;
			this->size_3_rb->Location = System::Drawing::Point(7, 92);
			this->size_3_rb->Name = L"size_3_rb";
			this->size_3_rb->Size = System::Drawing::Size(42, 21);
			this->size_3_rb->TabIndex = 2;
			this->size_3_rb->TabStop = true;
			this->size_3_rb->Text = L"-2";
			this->size_3_rb->UseVisualStyleBackColor = true;
			this->size_3_rb->CheckedChanged += gcnew System::EventHandler(this, &ResultForm::size_3_rb_CheckedChanged);
			// 
			// ResultForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1109, 629);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->add_class);
			this->Controls->Add(this->class_list);
			this->Controls->Add(this->constructor_button);
			this->Controls->Add(this->RedactorResultForm);
			this->Controls->Add(this->ccr);
			this->Controls->Add(this->BackResultForm);
			this->Controls->Add(this->ChangeResultForm);
			this->Controls->Add(this->DownloadResultForm);
			this->Controls->Add(this->PictureResultForm);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximumSize = System::Drawing::Size(1127, 676);
			this->MinimumSize = System::Drawing::Size(1046, 676);
			this->Name = L"ResultForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UML Creator";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureResultForm))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void BackResultForm_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ChangeResultForm_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void PictureResultForm_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void DownloadResultForm_Click_1(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ccr_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void constructor_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void class_list_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void add_class_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void size_1_rb_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void size_2_rb_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void size_3_rb_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
};
}
