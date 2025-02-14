#pragma once

namespace Winform8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ btnSaveInFile;
	private: System::Windows::Forms::Button^ btnReadFile;

	protected:









	private: System::Windows::Forms::DataGridView^ dGrInput;





	private: System::Windows::Forms::Button^ btnRemoveRow;
	private: System::Windows::Forms::Button^ btnAddRow;
	private: System::Windows::Forms::DataGridView^ dGrOutput;





	private: System::Windows::Forms::Label^ lblInput;
	private: System::Windows::Forms::Label^ lblOuput;
	private: System::Windows::Forms::ErrorProvider^ errorProvider;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ inpSurname;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ inpName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ inpPatronymic;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ workTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ position;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ salary;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Oklad;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ filterTextbox;
	private: System::Windows::Forms::Button^ filterButton;

	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->btnSaveInFile = (gcnew System::Windows::Forms::Button());
			this->btnReadFile = (gcnew System::Windows::Forms::Button());
			this->dGrInput = (gcnew System::Windows::Forms::DataGridView());
			this->inpSurname = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->inpName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->inpPatronymic = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->workTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->position = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->salary = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnRemoveRow = (gcnew System::Windows::Forms::Button());
			this->btnAddRow = (gcnew System::Windows::Forms::Button());
			this->dGrOutput = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Oklad = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->lblInput = (gcnew System::Windows::Forms::Label());
			this->lblOuput = (gcnew System::Windows::Forms::Label());
			this->errorProvider = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->filterTextbox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->filterButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dGrInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dGrOutput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider))->BeginInit();
			this->SuspendLayout();
			// 
			// btnSaveInFile
			// 
			this->btnSaveInFile->Enabled = false;
			this->btnSaveInFile->Location = System::Drawing::Point(239, 411);
			this->btnSaveInFile->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnSaveInFile->Name = L"btnSaveInFile";
			this->btnSaveInFile->Size = System::Drawing::Size(97, 23);
			this->btnSaveInFile->TabIndex = 15;
			this->btnSaveInFile->Text = L"Сохранить как";
			this->btnSaveInFile->UseVisualStyleBackColor = true;
			this->btnSaveInFile->Click += gcnew System::EventHandler(this, &MyForm::btnSaveInFile_Click);
			// 
			// btnReadFile
			// 
			this->btnReadFile->Location = System::Drawing::Point(52, 11);
			this->btnReadFile->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnReadFile->Name = L"btnReadFile";
			this->btnReadFile->Size = System::Drawing::Size(123, 24);
			this->btnReadFile->TabIndex = 14;
			this->btnReadFile->Text = L"Открыть файл";
			this->btnReadFile->UseVisualStyleBackColor = true;
			this->btnReadFile->Click += gcnew System::EventHandler(this, &MyForm::btnReadFile_Click);
			// 
			// dGrInput
			// 
			this->dGrInput->AllowUserToAddRows = false;
			this->dGrInput->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dGrInput->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->inpSurname,
					this->inpName, this->inpPatronymic, this->workTime, this->position, this->salary
			});
			this->dGrInput->Location = System::Drawing::Point(11, 46);
			this->dGrInput->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->dGrInput->Name = L"dGrInput";
			this->dGrInput->RowHeadersWidth = 51;
			this->dGrInput->RowTemplate->Height = 24;
			this->dGrInput->Size = System::Drawing::Size(584, 164);
			this->dGrInput->TabIndex = 12;
			// 
			// inpSurname
			// 
			this->inpSurname->HeaderText = L"Фамилия";
			this->inpSurname->MinimumWidth = 6;
			this->inpSurname->Name = L"inpSurname";
			this->inpSurname->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->inpSurname->Width = 125;
			// 
			// inpName
			// 
			this->inpName->HeaderText = L"Имя";
			this->inpName->MinimumWidth = 6;
			this->inpName->Name = L"inpName";
			this->inpName->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->inpName->Width = 125;
			// 
			// inpPatronymic
			// 
			this->inpPatronymic->HeaderText = L"Отчество";
			this->inpPatronymic->MinimumWidth = 6;
			this->inpPatronymic->Name = L"inpPatronymic";
			this->inpPatronymic->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->inpPatronymic->Width = 125;
			// 
			// workTime
			// 
			this->workTime->HeaderText = L"Стаж";
			this->workTime->MinimumWidth = 6;
			this->workTime->Name = L"workTime";
			this->workTime->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->workTime->Width = 125;
			// 
			// position
			// 
			this->position->HeaderText = L"Должность";
			this->position->MinimumWidth = 6;
			this->position->Name = L"position";
			this->position->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->position->Width = 125;
			// 
			// salary
			// 
			this->salary->HeaderText = L"Оклад";
			this->salary->Name = L"salary";
			// 
			// btnRemoveRow
			// 
			this->btnRemoveRow->Location = System::Drawing::Point(128, 411);
			this->btnRemoveRow->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnRemoveRow->Name = L"btnRemoveRow";
			this->btnRemoveRow->Size = System::Drawing::Size(111, 23);
			this->btnRemoveRow->TabIndex = 17;
			this->btnRemoveRow->Text = L"Удалить строку";
			this->btnRemoveRow->UseVisualStyleBackColor = true;
			this->btnRemoveRow->Click += gcnew System::EventHandler(this, &MyForm::btnRemoveRow_Click);
			// 
			// btnAddRow
			// 
			this->btnAddRow->Location = System::Drawing::Point(11, 411);
			this->btnAddRow->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnAddRow->Name = L"btnAddRow";
			this->btnAddRow->Size = System::Drawing::Size(111, 23);
			this->btnAddRow->TabIndex = 16;
			this->btnAddRow->Text = L"Добавить строку";
			this->btnAddRow->UseVisualStyleBackColor = true;
			this->btnAddRow->Click += gcnew System::EventHandler(this, &MyForm::btnAddRow_Click);
			// 
			// dGrOutput
			// 
			this->dGrOutput->AllowUserToAddRows = false;
			this->dGrOutput->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dGrOutput->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->dataGridViewTextBoxColumn4, this->dataGridViewTextBoxColumn5,
					this->Oklad
			});
			this->dGrOutput->Location = System::Drawing::Point(11, 244);
			this->dGrOutput->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->dGrOutput->Name = L"dGrOutput";
			this->dGrOutput->RowHeadersWidth = 51;
			this->dGrOutput->RowTemplate->Height = 24;
			this->dGrOutput->Size = System::Drawing::Size(584, 164);
			this->dGrOutput->TabIndex = 18;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"Фамилия";
			this->dataGridViewTextBoxColumn1->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewTextBoxColumn1->Width = 125;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"Имя";
			this->dataGridViewTextBoxColumn2->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewTextBoxColumn2->Width = 125;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->HeaderText = L"Отчество";
			this->dataGridViewTextBoxColumn3->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewTextBoxColumn3->Width = 125;
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->HeaderText = L"Стаж";
			this->dataGridViewTextBoxColumn4->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			this->dataGridViewTextBoxColumn4->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewTextBoxColumn4->Width = 125;
			// 
			// dataGridViewTextBoxColumn5
			// 
			this->dataGridViewTextBoxColumn5->HeaderText = L"Должность";
			this->dataGridViewTextBoxColumn5->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn5->Name = L"dataGridViewTextBoxColumn5";
			this->dataGridViewTextBoxColumn5->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewTextBoxColumn5->Width = 125;
			// 
			// Oklad
			// 
			this->Oklad->HeaderText = L"Оклад";
			this->Oklad->Name = L"Oklad";
			// 
			// lblInput
			// 
			this->lblInput->AutoSize = true;
			this->lblInput->Location = System::Drawing::Point(15, 17);
			this->lblInput->Name = L"lblInput";
			this->lblInput->Size = System::Drawing::Size(35, 13);
			this->lblInput->TabIndex = 19;
			this->lblInput->Text = L"Ввод:";
			// 
			// lblOuput
			// 
			this->lblOuput->AutoSize = true;
			this->lblOuput->Location = System::Drawing::Point(15, 228);
			this->lblOuput->Name = L"lblOuput";
			this->lblOuput->Size = System::Drawing::Size(43, 13);
			this->lblOuput->TabIndex = 20;
			this->lblOuput->Text = L"Вывод:";
			// 
			// errorProvider
			// 
			this->errorProvider->ContainerControl = this;
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog1";
			// 
			// filterTextbox
			// 
			this->filterTextbox->Location = System::Drawing::Point(394, 414);
			this->filterTextbox->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->filterTextbox->Name = L"filterTextbox";
			this->filterTextbox->Size = System::Drawing::Size(121, 20);
			this->filterTextbox->TabIndex = 22;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(341, 416);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 13);
			this->label2->TabIndex = 23;
			this->label2->Text = L"Фильтр:";
			// 
			// filterButton
			// 
			this->filterButton->Location = System::Drawing::Point(520, 414);
			this->filterButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->filterButton->Name = L"filterButton";
			this->filterButton->Size = System::Drawing::Size(75, 20);
			this->filterButton->TabIndex = 24;
			this->filterButton->Text = L"ы";
			this->filterButton->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->filterButton->UseVisualStyleBackColor = true;
			this->filterButton->Click += gcnew System::EventHandler(this, &MyForm::filterButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(613, 448);
			this->Controls->Add(this->filterButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->filterTextbox);
			this->Controls->Add(this->lblOuput);
			this->Controls->Add(this->lblInput);
			this->Controls->Add(this->dGrOutput);
			this->Controls->Add(this->btnRemoveRow);
			this->Controls->Add(this->btnAddRow);
			this->Controls->Add(this->btnSaveInFile);
			this->Controls->Add(this->btnReadFile);
			this->Controls->Add(this->dGrInput);
			this->Name = L"MyForm";
			this->Text = L"отчислятор отчислятор";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dGrInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dGrOutput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// Очистка таблиц
		void ClearTables() {
			while (this->dGrInput->RowCount){
				this->dGrInput->Rows->Remove(this->dGrInput->Rows[this->dGrInput->RowCount - 1]);
			}
			while (this->dGrOutput->RowCount){
				this->dGrOutput->Rows->Remove(this->dGrOutput->Rows[this->dGrOutput->RowCount - 1]);
			}
		}

		// Чтение данных
		private: System::Void btnReadFile_Click(System::Object^ sender, System::EventArgs^ e) {
			this->errorProvider->SetError(this->dGrInput, System::String::Empty);
			System::IO::Stream^ myStream;
			btnSaveInFile->Enabled = true;
			if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				if ((myStream = openFileDialog->OpenFile()) != nullptr) {
					System::IO::StreamReader^ sw =
						gcnew System::IO::StreamReader(myStream,
							System::Text::Encoding::GetEncoding(1251)
						);

					// Очистка таблиц
					ClearTables();

					String^ strBuf;
					array<System::String^>^ arrBuf;
					int i = 0;
					int j = 0;
					// Вывод в таблицы
					while (sw->Peek() + 1) {
						this->dGrInput->Rows->Add(1);
						// Чтение строки из файла
						strBuf = sw->ReadLine();
						try {
							// Вывод ФИО в таблицу dGrInput
							arrBuf = strBuf->Split(' ');
							this->dGrInput->Rows[i]->Cells[0]->Value = arrBuf[0];
							this->dGrInput->Rows[i]->Cells[1]->Value = arrBuf[1];
							this->dGrInput->Rows[i]->Cells[2]->Value = arrBuf[2];
							this->dGrInput->Rows[i]->Cells[4]->Value = arrBuf[4];

							// Проверка на корректность стажа
							int worktime;
							if (!Int32::TryParse(arrBuf[3], worktime)) {
								this->errorProvider->SetError(this->dGrInput, "Стаж должен быть целым числом");
								ClearTables();
								return;
							}

							// Проверка на корректность оклада
							int salary;
							if (!Int32::TryParse(arrBuf[5], salary)) {
								this->errorProvider->SetError(this->dGrInput, "Оклад должен быть целым числом");
								ClearTables();
								return;
							}

							this->dGrInput->Rows[i]->Cells[3]->Value = arrBuf[3];
							this->dGrInput->Rows[i]->Cells[5]->Value = arrBuf[5];						
						}
						catch (...) {
						}
						++i;
					}

				}
			}

		}

		// Добавление строки
		private: System::Void btnAddRow_Click(System::Object^ sender, System::EventArgs^ e) {
			this->dGrOutput->Rows->Add(1);
		}

		// Удаление строки
		private: System::Void btnRemoveRow_Click(System::Object^ sender, System::EventArgs^ e) {
			this->errorProvider->SetError(this->dGrOutput, System::String::Empty);
			if (!this->dGrOutput->CurrentRow) {
				this->errorProvider->SetError(this->dGrOutput, "Нельзя удалить несуществующую строку");
				return;
			}
			if (!this->dGrOutput->CurrentRow->IsNewRow) {
				int i = this->dGrOutput->CurrentRow->Index;
				this->dGrOutput->Rows->Remove(this->dGrOutput->Rows[i]);
			}
		}

		// Перевод строки из таблицы в строку для вывода в файл
		System::String^ dGrOutputToString(int i) {
			this->errorProvider->SetError(this->dGrOutput, System::String::Empty);
			System::String^ buff = "";
			System::String^ strBuf = "";
			// Проверяем ФИО
			for (int j = 0; j < 3; ++j) {
				if (System::Convert::ToString(this->dGrOutput->Rows[i]->Cells[j]->Value)->Trim() == "") {
					this->errorProvider->SetError(this->dGrOutput, "Некорректное ФИО");
					return " ";
				}
			}
			// Проверка на корректность стажа
			int worktime;
			if (!Int32::TryParse(Convert::ToString(this->dGrOutput->Rows[i]->Cells[3]->Value), worktime)) {
				this->errorProvider->SetError(this->dGrOutput, "Стаж должен быть целым числом");
				return " ";
			}

			// Проверка на корректность оклада
			int salary;
			if (!Int32::TryParse(Convert::ToString(this->dGrOutput->Rows[i]->Cells[5]->Value), salary)) {
				this->errorProvider->SetError(this->dGrOutput, "Оклад должен быть целым числом");
				return " ";
			}

			strBuf = "";
			for (int j = 0; j < 5; ++j) {
				strBuf += System::Convert::ToString(this->dGrOutput->Rows[i]->Cells[j]->Value) + " ";
			}
			return strBuf;
		}

		// Сохранение файла
		private: System::Void btnSaveInFile_Click(System::Object^ sender, System::EventArgs^ e) {
			System::IO::Stream^ myStream;
			if (this->saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				if ((myStream = saveFileDialog->OpenFile()) != nullptr) {
					System::IO::StreamWriter^ sw =
						gcnew System::IO::StreamWriter(myStream,
							System::Text::Encoding::GetEncoding(1251)
						);
					try {
						for (int i = 0; i < this->dGrOutput->RowCount - 1; ++i) {
							sw->WriteLine(dGrOutputToString(i));
						}
						sw->Write(dGrOutputToString(this->dGrOutput->RowCount - 1));
					}
					catch (...) {
					}
					sw->Close();
				}
		}

	private: System::Void filterButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->dGrOutput->Rows->Clear();
		for (int i = 0; i < this->dGrInput->RowCount; ++i) {
			if (this->dGrInput->Rows[i]->Cells[4]->Value->Equals(filterTextbox->Text)) {
				this->dGrOutput->Rows->Add(this->dGrInput->Rows[i]->Cells[0]->Value,
										this->dGrInput->Rows[i]->Cells[1]->Value,
										this->dGrInput->Rows[i]->Cells[2]->Value,
										this->dGrInput->Rows[i]->Cells[3]->Value,
										this->dGrInput->Rows[i]->Cells[4]->Value,
										this->dGrInput->Rows[i]->Cells[5]->Value);
			}
		}
	}
};
}
