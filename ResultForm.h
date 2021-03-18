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
		}

		void change_class_list(std::vector<std::pair<std::string, std::pair<std::string, std::pair<size_t, size_t>>>> classes, size_t index)
		{
			class_list->Items[index]=
				Convert_string_to_String(classes.front().first + "                " + classes.front().second.first
					+ "{" + std::to_string(classes.front().second.second.first) + "," + 
					std::to_string(classes.front().second.second.second) + "}");
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
	private: size_t images_size;
	private: String^ text = gcnew String("");
	private: System::Windows::Forms::Button^ ChangeResultForm;
	private: System::Windows::Forms::Button^ BackResultForm;
	private: System::Windows::Forms::Button^ ccr;
	private: System::Windows::Forms::RichTextBox^ RedactorResultForm;
	private: System::Windows::Forms::Button^ constructor_button;
	public: ListBox^ class_list = gcnew ListBox;


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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureResultForm))->BeginInit();
			this->SuspendLayout();
			// 
			// PictureResultForm
			// 
			this->PictureResultForm->Location = System::Drawing::Point(409, 12);
			this->PictureResultForm->Name = L"PictureResultForm";
			this->PictureResultForm->Size = System::Drawing::Size(352, 446);
			this->PictureResultForm->TabIndex = 0;
			this->PictureResultForm->TabStop = false;
			this->PictureResultForm->Click += gcnew System::EventHandler(this, &ResultForm::PictureResultForm_Click);
			// 
			// DownloadResultForm
			// 
			this->DownloadResultForm->Location = System::Drawing::Point(409, 465);
			this->DownloadResultForm->Name = L"DownloadResultForm";
			this->DownloadResultForm->Size = System::Drawing::Size(116, 37);
			this->DownloadResultForm->TabIndex = 2;
			this->DownloadResultForm->Text = L"DOWNLOAD";
			this->DownloadResultForm->UseVisualStyleBackColor = true;
			this->DownloadResultForm->Click += gcnew System::EventHandler(this, &ResultForm::DownloadResultForm_Click_1);
			// 
			// ChangeResultForm
			// 
			this->ChangeResultForm->Location = System::Drawing::Point(109, 466);
			this->ChangeResultForm->Name = L"ChangeResultForm";
			this->ChangeResultForm->Size = System::Drawing::Size(130, 37);
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
			// ccr
			// 
			this->ccr->Location = System::Drawing::Point(268, 466);
			this->ccr->Name = L"ccr";
			this->ccr->Size = System::Drawing::Size(100, 37);
			this->ccr->TabIndex = 5;
			this->ccr->Text = L"CUSTOM CLASS READCTOR";
			this->ccr->UseVisualStyleBackColor = true;
			this->ccr->Click += gcnew System::EventHandler(this, &ResultForm::ccr_Click);
			std::string path = (get_data_dir() + "\\class_img" + std::to_string(images_size) + ".png");
			this->PictureResultForm->ImageLocation = Convert_string_to_String(path);
			// 
			// RedactorResultForm
			// 
			this->RedactorResultForm->Location = System::Drawing::Point(35, 12);
			this->RedactorResultForm->Margin = System::Windows::Forms::Padding(2);
			this->RedactorResultForm->Name = L"RedactorResultForm";
			this->RedactorResultForm->Size = System::Drawing::Size(350, 447);
			this->RedactorResultForm->TabIndex = 6;
			this->RedactorResultForm->Text = L"";
			std::ifstream ifs(get_data_dir() + "\\ParseClass.txt");
			std::string s;
			this->RedactorResultForm->Text = L"";
			std::string tag = "<" + std::to_string(images_size) + "name>";
			bool is_found = false;
			while (std::getline(ifs, s)) {
				text += Convert_string_to_String(s) + System::Environment::NewLine;
				if (s == tag) { is_found = true; }
				if (is_found) {
					this->RedactorResultForm->Text += Convert_string_to_String(s) + System::Environment::NewLine;
				}
			}
			ifs.close();

			// 
			// constructor_button
			// 
			this->constructor_button->Location = System::Drawing::Point(554, 466);
			this->constructor_button->Margin = System::Windows::Forms::Padding(2);
			this->constructor_button->Name = L"constructor_button";
			this->constructor_button->Size = System::Drawing::Size(110, 37);
			this->constructor_button->TabIndex = 7;
			this->constructor_button->Text = L"CONSTRUCTOR (pre-alfa)";
			this->constructor_button->UseVisualStyleBackColor = true;
			this->constructor_button->Click += gcnew System::EventHandler(this, &ResultForm::constructor_button_Click);
			// 
			// class_list
			// 
			this->class_list->FormattingEnabled = true;
			this->class_list->Location = System::Drawing::Point(767, 29);
			this->class_list->MultiColumn = true;
			this->class_list->Name = L"class_list";
			this->class_list->Size = System::Drawing::Size(53, 121);
			this->class_list->TabIndex = 8;
			this->class_list->SelectedIndexChanged += gcnew System::EventHandler(this, &ResultForm::class_list_SelectedIndexChanged);
			// 
			// ResultForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(832, 511);
			this->Controls->Add(this->class_list);
			this->Controls->Add(this->constructor_button);
			this->Controls->Add(this->RedactorResultForm);
			this->Controls->Add(this->ccr);
			this->Controls->Add(this->BackResultForm);
			this->Controls->Add(this->ChangeResultForm);
			this->Controls->Add(this->DownloadResultForm);
			this->Controls->Add(this->PictureResultForm);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(850, 558);
			this->MinimumSize = System::Drawing::Size(789, 558);
			this->Name = L"ResultForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UML Creator";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureResultForm))->EndInit();
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
};
}
