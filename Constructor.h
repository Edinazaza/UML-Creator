#pragma once
#include <list>
#include <functional>
#include <thread>
#include <string>
#include "CreateImageSFML.h"

namespace UMLCreator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class Constructor : public System::Windows::Forms::Form
	{
	public:
		Constructor(bool& _work, size_t _images_size) : work(_work), images_size(_images_size), classes_count(_images_size)
		{
			InitializeComponent();
			this->KeyDown += gcnew KeyEventHandler(this, &Constructor::key_press);
			this->KeyPreview = true;
			this->MouseMove += gcnew MouseEventHandler(this, &Constructor::main_form_mouse_move);
			lb->Visible = false;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Constructor()
		{
			if (components)
			{
				delete components;
				work = false;
				exit(0);
			}
		}

	protected:
	public: ListBox^ lb = gcnew ListBox;
	private:
		bool down = false, ab_resizing = false;
		bool& work;
		PictureBox^ buffer;
		String^ focused_name;
		String^ focused_label_name;
		size_t images_size, classes_count;
		System::ComponentModel::Container^ labels = gcnew System::ComponentModel::Container;
		Point fixed;

		size_t count = 1;
	public: System::ComponentModel::Container^ pics = gcnew System::ComponentModel::Container;
		
	private: System::Windows::Forms::Button^ add_arrow;

	private: System::Windows::Forms::Button^ save_to_file;

	public: System::Windows::Forms::ContextMenuStrip^ PicBoxContMenu;

	private: System::Windows::Forms::ToolStripMenuItem^ rotateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ deleteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ formatToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ headToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ colourToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ classicToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ agreagatorToolStripMenuItem;
	private: System::Windows::Forms::Button^ add_textbox;
	private: System::Windows::Forms::Button^ back_to_res_form;
	private: System::Windows::Forms::Button^ add_class_diagramm;

	private: System::ComponentModel::IContainer^ components;
		   /// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Constructor::typeid));
			   this->add_arrow = (gcnew System::Windows::Forms::Button());
			   this->save_to_file = (gcnew System::Windows::Forms::Button());
			   this->PicBoxContMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			   this->rotateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->formatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->headToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->classicToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->agreagatorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->colourToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->add_textbox = (gcnew System::Windows::Forms::Button());
			   this->back_to_res_form = (gcnew System::Windows::Forms::Button());
			   this->add_class_diagramm = (gcnew System::Windows::Forms::Button());
			   this->PicBoxContMenu->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // add_arrow
			   // 
			   this->add_arrow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->add_arrow->Location = System::Drawing::Point(10, 349);
			   this->add_arrow->Margin = System::Windows::Forms::Padding(2);
			   this->add_arrow->Name = L"add_arrow";
			   this->add_arrow->Size = System::Drawing::Size(94, 33);
			   this->add_arrow->TabIndex = 1;
			   this->add_arrow->Text = L"ADD ARROW";
			   this->add_arrow->UseVisualStyleBackColor = true;
			   this->add_arrow->Click += gcnew System::EventHandler(this, &Constructor::add_arrow_Click);
			   // 
			   // save_to_file
			   // 
			   this->save_to_file->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->save_to_file->Location = System::Drawing::Point(117, 349);
			   this->save_to_file->Margin = System::Windows::Forms::Padding(2);
			   this->save_to_file->Name = L"save_to_file";
			   this->save_to_file->Size = System::Drawing::Size(56, 34);
			   this->save_to_file->TabIndex = 2;
			   this->save_to_file->Text = L"SAVE";
			   this->save_to_file->UseVisualStyleBackColor = true;
			   this->save_to_file->Click += gcnew System::EventHandler(this, &Constructor::save_to_file_Click);
			   // 
			   // PicBoxContMenu
			   // 
			   this->PicBoxContMenu->ImageScalingSize = System::Drawing::Size(20, 20);
			   this->PicBoxContMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->rotateToolStripMenuItem,
					   this->deleteToolStripMenuItem, this->formatToolStripMenuItem
			   });
			   this->PicBoxContMenu->Name = L"PicBoxContMenu";
			   this->PicBoxContMenu->Size = System::Drawing::Size(126, 76);
			   // 
			   // rotateToolStripMenuItem
			   // 
			   this->rotateToolStripMenuItem->Name = L"rotateToolStripMenuItem";
			   this->rotateToolStripMenuItem->Size = System::Drawing::Size(125, 24);
			   this->rotateToolStripMenuItem->Text = L"Rotate";
			   this->rotateToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::rotateToolStripMenuItem_Click);
			   // 
			   // deleteToolStripMenuItem
			   // 
			   this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			   this->deleteToolStripMenuItem->Size = System::Drawing::Size(125, 24);
			   this->deleteToolStripMenuItem->Text = L"Delete";
			   this->deleteToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::deleteToolStripMenuItem_Click);
			   // 
			   // formatToolStripMenuItem
			   // 
			   this->formatToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->headToolStripMenuItem,
					   this->colourToolStripMenuItem
			   });
			   this->formatToolStripMenuItem->Name = L"formatToolStripMenuItem";
			   this->formatToolStripMenuItem->Size = System::Drawing::Size(125, 24);
			   this->formatToolStripMenuItem->Text = L"Format";
			   // 
			   // headToolStripMenuItem
			   // 
			   this->headToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->classicToolStripMenuItem,
					   this->agreagatorToolStripMenuItem
			   });
			   this->headToolStripMenuItem->Name = L"headToolStripMenuItem";
			   this->headToolStripMenuItem->Size = System::Drawing::Size(136, 26);
			   this->headToolStripMenuItem->Text = L"Head";
			   // 
			   // classicToolStripMenuItem
			   // 
			   this->classicToolStripMenuItem->Name = L"classicToolStripMenuItem";
			   this->classicToolStripMenuItem->Size = System::Drawing::Size(168, 26);
			   this->classicToolStripMenuItem->Text = L"Classic";
			   this->classicToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::classicToolStripMenuItem_Click);
			   // 
			   // agreagatorToolStripMenuItem
			   // 
			   this->agreagatorToolStripMenuItem->Name = L"agreagatorToolStripMenuItem";
			   this->agreagatorToolStripMenuItem->Size = System::Drawing::Size(168, 26);
			   this->agreagatorToolStripMenuItem->Text = L"Agreagator";
			   this->agreagatorToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::agregatorToolStripMenuItem_Click);
			   // 
			   // colourToolStripMenuItem
			   // 
			   this->colourToolStripMenuItem->Name = L"colourToolStripMenuItem";
			   this->colourToolStripMenuItem->Size = System::Drawing::Size(136, 26);
			   this->colourToolStripMenuItem->Text = L"Colour";
			   // 
			   // add_textbox
			   // 
			   this->add_textbox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->add_textbox->Location = System::Drawing::Point(188, 349);
			   this->add_textbox->Name = L"add_textbox";
			   this->add_textbox->Size = System::Drawing::Size(99, 34);
			   this->add_textbox->TabIndex = 3;
			   this->add_textbox->Text = L"ADD LABLE";
			   this->add_textbox->UseVisualStyleBackColor = true;
			   this->add_textbox->Click += gcnew System::EventHandler(this, &Constructor::add_textbox_Click);
			   // 
			   // back_to_res_form
			   // 
			   this->back_to_res_form->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->back_to_res_form->Location = System::Drawing::Point(398, 349);
			   this->back_to_res_form->Name = L"back_to_res_form";
			   this->back_to_res_form->Size = System::Drawing::Size(90, 34);
			   this->back_to_res_form->TabIndex = 4;
			   this->back_to_res_form->Text = L"BACK";
			   this->back_to_res_form->UseVisualStyleBackColor = true;
			   this->back_to_res_form->Click += gcnew System::EventHandler(this, &Constructor::back_to_res_form_Click);
			   // 
			   // add_class_diagramm
			   // 
			   this->add_class_diagramm->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->add_class_diagramm->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->add_class_diagramm->Location = System::Drawing::Point(302, 349);
			   this->add_class_diagramm->Name = L"add_class_diagramm";
			   this->add_class_diagramm->Size = System::Drawing::Size(87, 34);
			   this->add_class_diagramm->TabIndex = 5;
			   this->add_class_diagramm->Text = L"ADD DIAGRAMM";
			   this->add_class_diagramm->UseVisualStyleBackColor = true;
			   this->add_class_diagramm->Click += gcnew System::EventHandler(this, &Constructor::add_diagramm_Click);
			   // 
			   // Constructor
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(500, 393);
			   this->Controls->Add(this->add_class_diagramm);
			   this->Controls->Add(this->back_to_res_form);
			   this->Controls->Add(this->add_textbox);
			   this->Controls->Add(this->save_to_file);
			   this->Controls->Add(this->add_arrow);
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->Margin = System::Windows::Forms::Padding(2);
			   this->Name = L"Constructor";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Constructor";
			   this->PicBoxContMenu->ResumeLayout(false);
			   this->ResumeLayout(false);

		   }
#pragma endregion

	public: System::Void pictureBox_MouseDown(Object^ sender, MouseEventArgs^ args);
	public: System::Void pictureBox_MouseUp(Object^ sender, MouseEventArgs^ args);
	public: System::Void pictureBox_MouseMove(Object^ sender, MouseEventArgs^ args);
	public: System::Void pictureBox_Click(Object^ sender, MouseEventArgs^ args);
	private: System::Void add_arrow_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void save_to_file_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void key_press(System::Object^ sender, KeyEventArgs^ e);

	private: System::Void rotateToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void deleteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void agregatorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void classicToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void create_new_pic_box(PictureBox^ pic, PictureBox^ obj);

	private: System::Void add_textbox_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_MouseDown(Object^ sender, MouseEventArgs^ args);
	private: System::Void textBox_MouseUp(Object^ sender, MouseEventArgs^ args);
	private: System::Void textBox_MouseMove(Object^ sender, MouseEventArgs^ args);
	private: System::Void main_form_mouse_move(Object^ sender, MouseEventArgs^ args);

	private: System::Void back_to_res_form_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void add_diagramm_Click(System::Object^ sender, System::EventArgs^ e);
};
}

