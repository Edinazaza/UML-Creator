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
		bool down = false, ab_resizing = false, moving = false;;
		bool& work;
		PictureBox^ buffer;
		String^ focused_name;
		size_t images_size, classes_count;
		System::ComponentModel::Container^ labels = gcnew System::ComponentModel::Container;
		Point fixed;
		Point arrow_sample_location;
		Point textbox_sample_location;

		size_t count = 1;
	public: System::ComponentModel::Container^ pics = gcnew System::ComponentModel::Container;

	private: System::Windows::Forms::Button^ save_to_file;

	public: System::Windows::Forms::ContextMenuStrip^ PicBoxContMenu;

	private: System::Windows::Forms::ToolStripMenuItem^ rotateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ deleteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ formatToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ headToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ colourToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ classicToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ agreagatorToolStripMenuItem;
	private: System::Windows::Forms::Button^ back_to_res_form;
	private: System::Windows::Forms::Button^ add_textbox;
	private: System::Windows::Forms::Button^ add_arrow;
	private: System::Windows::Forms::ToolStripMenuItem^ bodyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ solidToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ dottedLineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ inheritanceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ compositionToolStripMenuItem;

	private: System::Windows::Forms::TextBox^ text_sample;
	private: System::Windows::Forms::PictureBox^ arrow_sample;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;

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
			   this->save_to_file = (gcnew System::Windows::Forms::Button());
			   this->PicBoxContMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			   this->rotateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->formatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->headToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->classicToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->agreagatorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->inheritanceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->compositionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->colourToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->bodyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->solidToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->dottedLineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->back_to_res_form = (gcnew System::Windows::Forms::Button());
			   this->text_sample = (gcnew System::Windows::Forms::TextBox());
			   this->arrow_sample = (gcnew System::Windows::Forms::PictureBox());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->PicBoxContMenu->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->arrow_sample))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // save_to_file
			   // 
			   this->save_to_file->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->save_to_file->Location = System::Drawing::Point(12, 443);
			   this->save_to_file->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			   this->save_to_file->Name = L"save_to_file";
			   this->save_to_file->Size = System::Drawing::Size(75, 42);
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
			   this->formatToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->headToolStripMenuItem,
					   this->colourToolStripMenuItem, this->bodyToolStripMenuItem
			   });
			   this->formatToolStripMenuItem->Name = L"formatToolStripMenuItem";
			   this->formatToolStripMenuItem->Size = System::Drawing::Size(125, 24);
			   this->formatToolStripMenuItem->Text = L"Format";
			   // 
			   // headToolStripMenuItem
			   // 
			   this->headToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				   this->classicToolStripMenuItem,
					   this->agreagatorToolStripMenuItem, this->inheritanceToolStripMenuItem, this->compositionToolStripMenuItem
			   });
			   this->headToolStripMenuItem->Name = L"headToolStripMenuItem";
			   this->headToolStripMenuItem->Size = System::Drawing::Size(136, 26);
			   this->headToolStripMenuItem->Text = L"Head";
			   // 
			   // classicToolStripMenuItem
			   // 
			   this->classicToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"classicToolStripMenuItem.Image")));
			   this->classicToolStripMenuItem->Name = L"classicToolStripMenuItem";
			   this->classicToolStripMenuItem->Size = System::Drawing::Size(177, 26);
			   this->classicToolStripMenuItem->Text = L"Classic";
			   this->classicToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::classicToolStripMenuItem_Click);
			   // 
			   // agreagatorToolStripMenuItem
			   // 
			   this->agreagatorToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"agreagatorToolStripMenuItem.Image")));
			   this->agreagatorToolStripMenuItem->Name = L"agreagatorToolStripMenuItem";
			   this->agreagatorToolStripMenuItem->Size = System::Drawing::Size(177, 26);
			   this->agreagatorToolStripMenuItem->Text = L"Agreagator";
			   this->agreagatorToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::agregatorToolStripMenuItem_Click);
			   // 
			   // inheritanceToolStripMenuItem
			   // 
			   this->inheritanceToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"inheritanceToolStripMenuItem.Image")));
			   this->inheritanceToolStripMenuItem->Name = L"inheritanceToolStripMenuItem";
			   this->inheritanceToolStripMenuItem->Size = System::Drawing::Size(177, 26);
			   this->inheritanceToolStripMenuItem->Text = L"Inheritance";
			   this->inheritanceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::inheritanceToolStripMenuItem_Click);
			   // 
			   // compositionToolStripMenuItem
			   // 
			   this->compositionToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"compositionToolStripMenuItem.Image")));
			   this->compositionToolStripMenuItem->Name = L"compositionToolStripMenuItem";
			   this->compositionToolStripMenuItem->Size = System::Drawing::Size(177, 26);
			   this->compositionToolStripMenuItem->Text = L"Copmosition";
			   this->compositionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::compositionToolStripMenuItem_Click);
			   // 
			   // colourToolStripMenuItem
			   // 
			   this->colourToolStripMenuItem->Name = L"colourToolStripMenuItem";
			   this->colourToolStripMenuItem->Size = System::Drawing::Size(136, 26);
			   this->colourToolStripMenuItem->Text = L"Colour";
			   // 
			   // bodyToolStripMenuItem
			   // 
			   this->bodyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->solidToolStripMenuItem,
					   this->dottedLineToolStripMenuItem
			   });
			   this->bodyToolStripMenuItem->Name = L"bodyToolStripMenuItem";
			   this->bodyToolStripMenuItem->Size = System::Drawing::Size(136, 26);
			   this->bodyToolStripMenuItem->Text = L"Body";
			   // 
			   // solidToolStripMenuItem
			   // 
			   this->solidToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"solidToolStripMenuItem.Image")));
			   this->solidToolStripMenuItem->Name = L"solidToolStripMenuItem";
			   this->solidToolStripMenuItem->Size = System::Drawing::Size(167, 26);
			   this->solidToolStripMenuItem->Text = L"Solid";
			   this->solidToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::solidToolStripMenuItem_Click);
			   // 
			   // dottedLineToolStripMenuItem
			   // 
			   this->dottedLineToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"dottedLineToolStripMenuItem.Image")));
			   this->dottedLineToolStripMenuItem->Name = L"dottedLineToolStripMenuItem";
			   this->dottedLineToolStripMenuItem->Size = System::Drawing::Size(167, 26);
			   this->dottedLineToolStripMenuItem->Text = L"Dotted line";
			   this->dottedLineToolStripMenuItem->Click += gcnew System::EventHandler(this, &Constructor::dottedLineToolStripMenuItem_Click);
			   // 
			   // back_to_res_form
			   // 
			   this->back_to_res_form->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->back_to_res_form->Location = System::Drawing::Point(94, 443);
			   this->back_to_res_form->Margin = System::Windows::Forms::Padding(4);
			   this->back_to_res_form->Name = L"back_to_res_form";
			   this->back_to_res_form->Size = System::Drawing::Size(120, 42);
			   this->back_to_res_form->TabIndex = 4;
			   this->back_to_res_form->Text = L"BACK";
			   this->back_to_res_form->UseVisualStyleBackColor = true;
			   this->back_to_res_form->Click += gcnew System::EventHandler(this, &Constructor::back_to_res_form_Click);
			   // 
			   // text_sample
			   // 
			   this->text_sample->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->text_sample->Location = System::Drawing::Point(445, 39);
			   this->text_sample->Name = L"text_sample";
			   this->text_sample->ReadOnly = true;
			   this->text_sample->Size = System::Drawing::Size(30, 22);
			   this->text_sample->TabIndex = 3;
			   this->text_sample->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Constructor::textBox_MouseDown);
			   this->text_sample->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Constructor::textBox_MouseMove);
			   this->text_sample->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Constructor::textBox_MouseUp);
			   // 
			   // arrow_sample
			   // 
			   this->arrow_sample->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->arrow_sample->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->arrow_sample->Location = System::Drawing::Point(509, 39);
			   this->arrow_sample->Name = L"arrow_sample";
			   this->arrow_sample->Size = System::Drawing::Size(22, 12);
			   this->arrow_sample->TabIndex = 2;
			   this->arrow_sample->TabStop = false;
			   this->arrow_sample->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Constructor::pictureBox_Click);
			   this->arrow_sample->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Constructor::pictureBox_MouseDown);
			   this->arrow_sample->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Constructor::pictureBox_MouseMove);
			   this->arrow_sample->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Constructor::pictureBox_MouseUp);
			   // 
			   // label2
			   // 
			   this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(442, 9);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(35, 17);
			   this->label2->TabIndex = 1;
			   this->label2->Text = L"Text";
			   // 
			   // label1
			   // 
			   this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(483, 9);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(73, 17);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"Connector";
			   // 
			   // Constructor
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoSize = true;
			   this->ClientSize = System::Drawing::Size(657, 496);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->text_sample);
			   this->Controls->Add(this->arrow_sample);
			   this->Controls->Add(this->back_to_res_form);
			   this->Controls->Add(this->save_to_file);
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			   this->Name = L"Constructor";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Constructor";
			   this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			   this->PicBoxContMenu->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->arrow_sample))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

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
	private: System::Void solidToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void dottedLineToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void compositionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void inheritanceToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void create_new_pic_box(PictureBox^ pic, PictureBox^ obj);

	private: System::Void add_textbox_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_MouseDown(Object^ sender, MouseEventArgs^ args);
	private: System::Void textBox_MouseUp(Object^ sender, MouseEventArgs^ args);
	private: System::Void textBox_MouseMove(Object^ sender, MouseEventArgs^ args);
	private: System::Void main_form_mouse_move(Object^ sender, MouseEventArgs^ args);

	private: System::Void back_to_res_form_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void lb_doubleclick(Object^ sender, MouseEventArgs^ args);
};
}

