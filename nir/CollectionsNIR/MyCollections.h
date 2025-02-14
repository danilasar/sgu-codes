#pragma once

namespace MyCollectionss {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyCollections
	/// </summary>
	public ref class MyCollections : public System::Windows::Forms::Form
	{
	public:
		MyCollections(void)
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
		~MyCollections()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lbl1;
	private: System::Windows::Forms::TextBox^ tBInputQue;
	private: System::Windows::Forms::TextBox^ tBOutputQue;
	protected:


	private: System::Windows::Forms::Label^ lbl2;
	private: System::Windows::Forms::TextBox^ tBInputPush;


	private: System::Windows::Forms::TextBox^ tBOutputPop;
	private: System::Windows::Forms::Button^ btnPush;
	private: System::Windows::Forms::Button^ btnPop;
	private: System::Windows::Forms::Button^ btnInputQue;
	private: System::Windows::Forms::Button^ btnClearQue;
	private: System::Windows::Forms::Button^ btnSum;
	private: System::Windows::Forms::TextBox^ tBInputA;
	private: System::Windows::Forms::TextBox^ tBInputB;




	private: System::Windows::Forms::Label^ lbl3;
	private: System::Windows::Forms::Label^ lbl4;

	private: System::Windows::Forms::TextBox^ tBOutputNAM;


	private: System::Windows::Forms::Button^ btnNewAfterMax;

	private: System::Windows::Forms::TextBox^ tBInputNAM;
	private: System::Windows::Forms::ErrorProvider^ eP1;



	private: System::Windows::Forms::TextBox^ tBOutputSum;

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
			this->lbl1 = (gcnew System::Windows::Forms::Label());
			this->tBInputQue = (gcnew System::Windows::Forms::TextBox());
			this->tBOutputQue = (gcnew System::Windows::Forms::TextBox());
			this->lbl2 = (gcnew System::Windows::Forms::Label());
			this->tBInputPush = (gcnew System::Windows::Forms::TextBox());
			this->tBOutputPop = (gcnew System::Windows::Forms::TextBox());
			this->btnPush = (gcnew System::Windows::Forms::Button());
			this->btnPop = (gcnew System::Windows::Forms::Button());
			this->btnInputQue = (gcnew System::Windows::Forms::Button());
			this->btnClearQue = (gcnew System::Windows::Forms::Button());
			this->btnSum = (gcnew System::Windows::Forms::Button());
			this->tBInputA = (gcnew System::Windows::Forms::TextBox());
			this->tBInputB = (gcnew System::Windows::Forms::TextBox());
			this->lbl3 = (gcnew System::Windows::Forms::Label());
			this->lbl4 = (gcnew System::Windows::Forms::Label());
			this->tBOutputNAM = (gcnew System::Windows::Forms::TextBox());
			this->btnNewAfterMax = (gcnew System::Windows::Forms::Button());
			this->tBInputNAM = (gcnew System::Windows::Forms::TextBox());
			this->eP1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->tBOutputSum = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->eP1))->BeginInit();
			this->SuspendLayout();
			// 
			// lbl1
			// 
			this->lbl1->AutoSize = true;
			this->lbl1->Location = System::Drawing::Point(22, 30);
			this->lbl1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbl1->Name = L"lbl1";
			this->lbl1->Size = System::Drawing::Size(108, 23);
			this->lbl1->TabIndex = 0;
			this->lbl1->Text = L"Ввод списка:";
			// 
			// tBInputQue
			// 
			this->tBInputQue->Location = System::Drawing::Point(163, 24);
			this->tBInputQue->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBInputQue->Name = L"tBInputQue";
			this->tBInputQue->Size = System::Drawing::Size(164, 30);
			this->tBInputQue->TabIndex = 1;
			// 
			// tBOutputQue
			// 
			this->tBOutputQue->Location = System::Drawing::Point(122, 97);
			this->tBOutputQue->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBOutputQue->Name = L"tBOutputQue";
			this->tBOutputQue->ReadOnly = true;
			this->tBOutputQue->Size = System::Drawing::Size(206, 30);
			this->tBOutputQue->TabIndex = 3;
			// 
			// lbl2
			// 
			this->lbl2->AutoSize = true;
			this->lbl2->Location = System::Drawing::Point(23, 103);
			this->lbl2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbl2->Name = L"lbl2";
			this->lbl2->Size = System::Drawing::Size(70, 23);
			this->lbl2->TabIndex = 2;
			this->lbl2->Text = L"Список:";
			// 
			// tBInputPush
			// 
			this->tBInputPush->Location = System::Drawing::Point(37, 209);
			this->tBInputPush->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBInputPush->Name = L"tBInputPush";
			this->tBInputPush->Size = System::Drawing::Size(122, 30);
			this->tBInputPush->TabIndex = 5;
			// 
			// tBOutputPop
			// 
			this->tBOutputPop->Location = System::Drawing::Point(216, 209);
			this->tBOutputPop->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBOutputPop->Name = L"tBOutputPop";
			this->tBOutputPop->ReadOnly = true;
			this->tBOutputPop->Size = System::Drawing::Size(122, 30);
			this->tBOutputPop->TabIndex = 6;
			// 
			// btnPush
			// 
			this->btnPush->Location = System::Drawing::Point(216, 271);
			this->btnPush->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnPush->Name = L"btnPush";
			this->btnPush->Size = System::Drawing::Size(165, 41);
			this->btnPush->TabIndex = 7;
			this->btnPush->Text = L"Добавить в конец";
			this->btnPush->UseVisualStyleBackColor = true;
			this->btnPush->Click += gcnew System::EventHandler(this, &MyCollections::btnPush_Click);
			// 
			// btnPop
			// 
			this->btnPop->Location = System::Drawing::Point(216, 322);
			this->btnPop->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnPop->Name = L"btnPop";
			this->btnPop->Size = System::Drawing::Size(165, 41);
			this->btnPop->TabIndex = 8;
			this->btnPop->Text = L"Удалить с конца";
			this->btnPop->UseVisualStyleBackColor = true;
			this->btnPop->Click += gcnew System::EventHandler(this, &MyCollections::btnPop_Click);
			// 
			// btnInputQue
			// 
			this->btnInputQue->Location = System::Drawing::Point(390, 22);
			this->btnInputQue->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnInputQue->Name = L"btnInputQue";
			this->btnInputQue->Size = System::Drawing::Size(297, 41);
			this->btnInputQue->TabIndex = 9;
			this->btnInputQue->Text = L"Добавить элементы в список";
			this->btnInputQue->UseVisualStyleBackColor = true;
			this->btnInputQue->Click += gcnew System::EventHandler(this, &MyCollections::btnInputQue_Click);
			// 
			// btnClearQue
			// 
			this->btnClearQue->Location = System::Drawing::Point(390, 93);
			this->btnClearQue->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnClearQue->Name = L"btnClearQue";
			this->btnClearQue->Size = System::Drawing::Size(297, 41);
			this->btnClearQue->TabIndex = 10;
			this->btnClearQue->Text = L"Очистить список";
			this->btnClearQue->UseVisualStyleBackColor = true;
			this->btnClearQue->Click += gcnew System::EventHandler(this, &MyCollections::btnClearQue_Click);
			// 
			// btnSum
			// 
			this->btnSum->Location = System::Drawing::Point(406, 345);
			this->btnSum->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnSum->Name = L"btnSum";
			this->btnSum->Size = System::Drawing::Size(260, 41);
			this->btnSum->TabIndex = 12;
			this->btnSum->Text = L"Сумма в интервале";
			this->btnSum->UseVisualStyleBackColor = true;
			this->btnSum->Click += gcnew System::EventHandler(this, &MyCollections::btnSum_Click);
			// 
			// tBInputA
			// 
			this->tBInputA->Location = System::Drawing::Point(406, 214);
			this->tBInputA->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBInputA->Name = L"tBInputA";
			this->tBInputA->Size = System::Drawing::Size(122, 30);
			this->tBInputA->TabIndex = 11;
			// 
			// tBInputB
			// 
			this->tBInputB->Location = System::Drawing::Point(541, 214);
			this->tBInputB->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBInputB->Name = L"tBInputB";
			this->tBInputB->Size = System::Drawing::Size(122, 30);
			this->tBInputB->TabIndex = 13;
			// 
			// lbl3
			// 
			this->lbl3->AutoSize = true;
			this->lbl3->Location = System::Drawing::Point(34, 163);
			this->lbl3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbl3->Name = L"lbl3";
			this->lbl3->Size = System::Drawing::Size(277, 23);
			this->lbl3->TabIndex = 14;
			this->lbl3->Text = L"Добавить / удалить один элемент:\r\n";
			// 
			// lbl4
			// 
			this->lbl4->AutoSize = true;
			this->lbl4->Location = System::Drawing::Point(459, 163);
			this->lbl4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbl4->Name = L"lbl4";
			this->lbl4->Size = System::Drawing::Size(126, 23);
			this->lbl4->TabIndex = 15;
			this->lbl4->Text = L"Интервал [a,b]:";
			// 
			// tBOutputNAM
			// 
			this->tBOutputNAM->Location = System::Drawing::Point(67, 413);
			this->tBOutputNAM->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBOutputNAM->Name = L"tBOutputNAM";
			this->tBOutputNAM->ReadOnly = true;
			this->tBOutputNAM->Size = System::Drawing::Size(620, 30);
			this->tBOutputNAM->TabIndex = 17;
			// 
			// btnNewAfterMax
			// 
			this->btnNewAfterMax->Location = System::Drawing::Point(67, 477);
			this->btnNewAfterMax->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnNewAfterMax->Name = L"btnNewAfterMax";
			this->btnNewAfterMax->Size = System::Drawing::Size(622, 41);
			this->btnNewAfterMax->TabIndex = 18;
			this->btnNewAfterMax->Text = L"Вставить после чётных";
			this->btnNewAfterMax->UseVisualStyleBackColor = true;
			this->btnNewAfterMax->Click += gcnew System::EventHandler(this, &MyCollections::btnNewAfterMax_Click);
			// 
			// tBInputNAM
			// 
			this->tBInputNAM->Location = System::Drawing::Point(27, 302);
			this->tBInputNAM->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBInputNAM->Name = L"tBInputNAM";
			this->tBInputNAM->Size = System::Drawing::Size(158, 30);
			this->tBInputNAM->TabIndex = 20;
			// 
			// eP1
			// 
			this->eP1->ContainerControl = this;
			// 
			// tBOutputSum
			// 
			this->tBOutputSum->Location = System::Drawing::Point(446, 282);
			this->tBOutputSum->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tBOutputSum->Name = L"tBOutputSum";
			this->tBOutputSum->ReadOnly = true;
			this->tBOutputSum->Size = System::Drawing::Size(164, 30);
			this->tBOutputSum->TabIndex = 21;
			// 
			// MyCollections
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 23);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(742, 546);
			this->Controls->Add(this->tBOutputSum);
			this->Controls->Add(this->tBInputNAM);
			this->Controls->Add(this->btnNewAfterMax);
			this->Controls->Add(this->tBOutputNAM);
			this->Controls->Add(this->lbl4);
			this->Controls->Add(this->lbl3);
			this->Controls->Add(this->tBInputB);
			this->Controls->Add(this->btnSum);
			this->Controls->Add(this->tBInputA);
			this->Controls->Add(this->btnClearQue);
			this->Controls->Add(this->btnInputQue);
			this->Controls->Add(this->btnPush);
			this->Controls->Add(this->tBOutputPop);
			this->Controls->Add(this->tBInputPush);
			this->Controls->Add(this->tBOutputQue);
			this->Controls->Add(this->lbl2);
			this->Controls->Add(this->tBInputQue);
			this->Controls->Add(this->lbl1);
			this->Controls->Add(this->btnPop);
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"MyCollections";
			this->Text = L"Работа с коллекциями";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->eP1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		System::Collections::Generic::LinkedList<int> q;
		// Очистка errorProvider-ов
		void ClearEP() {
			eP1->Clear();
		}

		void QueueOutput() {
			System::Collections::Generic::LinkedList<int>^ buffer = gcnew System::Collections::Generic::LinkedList<int>();
			String^ str = "";

			// Пока основной список не пуст
			while (q.Count > 0) {
				// Записываем первый элемент во вспомогательный список
				buffer->AddLast(q.First->Value);
				// Удаляем первый элемент из основного списка
				q.RemoveFirst();
			}

			// Пока вспомогательный список не пуст
			while (buffer->Count > 0) {
				// Записываем первый элемент в основной список
				q.AddLast(buffer->First->Value);
				// Записываем первый элемент списка в строку
				str += System::Convert::ToString(buffer->First->Value) + " ";
				// Удаляем первый элемент из вспомогательного списка
				buffer->RemoveFirst();
			}

			// Выводим результат
			if (str->Length > 0) {
				this->tBOutputQue->Text = str->Substring(0, str->Length - 1);
			}
		}

	private: System::Void btnInputQue_Click(System::Object^ sender, System::EventArgs^ e) {
		ClearEP();
		// Вспомогательный двусвязный список
		System::Collections::Generic::LinkedList<int>^ buffer = gcnew System::Collections::Generic::LinkedList<int>();
		// Считываем строку
		String^ str = Convert::ToString(this->tBInputQue->Text);
		int number, index;
		int pos = 0;

		if (str->IndexOf(",") != -1 || str->IndexOf(".") != -1) {
			this->eP1->SetError(btnInputQue, "Неправильный формат ввода очереди (элементы через пробел)");
			return;
		}
		else {
			str += " ";
			// Позиция первого пробела
			index = str->IndexOf(" ");
			String^ str2 = "";

			// Пока находим пробел
			while (index != -1) {
				// Считываем число
				String^ str2 = str->Substring(pos, index - pos);
				pos = index + 1;
				bool res = Int32::TryParse(str2, number);

				// Проверка на число
				if (!res) {
					this->eP1->SetError(btnInputQue, "Список должен состоять только из целых чисел");
					buffer->Clear();
					return;
				}
				else {
					// Проверка на лишние пробелы (без нее могут добавляться лишние элементы - 0)
					if (str->IndexOf(" ", pos) == pos) {
						this->eP1->SetError(btnInputQue, "Список содержит лишние пробелы");
						buffer->Clear();
						return;
					}
					else {
						// Записываем во вспомогательный двусвязный список
						buffer->AddLast(number);
						// Ищем следующий индекс
						index = str->IndexOf(" ", pos);
					}
				}
			}

			// Вспомогательный двусвязный список для хранения значений из основного списка
			System::Collections::Generic::LinkedList<int>^ buffer2 = gcnew System::Collections::Generic::LinkedList<int>();

			// Пока основной список не пуст
			while (q.Count > 0) {
				// Записываем первый элемент во вспомогательный список
				buffer2->AddLast(q.First->Value);
				// Удаляем первый элемент из основного списка
				q.RemoveFirst();
			}

			// Пока вспомогательный двусвязный список не пуст
			while (buffer->Count > 0) {
				// Записываем элементы из buffer в buffer2
				buffer2->AddLast(buffer->First->Value);
				buffer->RemoveFirst();
			}

			str2 = "";

			// Пока buffer2 не пуст
			while (buffer2->Count > 0) {
				// Записываем в основной список первый элемент
				q.AddLast(buffer2->First->Value);
				// Записываем первый элемент списка в строку
				str2 += System::Convert::ToString(buffer2->First->Value) + " ";
				// Удаляем первый элемент из buffer2
				buffer2->RemoveFirst();
			}

			// Выводим результат
			if (str2->Length > 0) {
				this->tBOutputQue->Text = str2->Substring(0, str2->Length - 1);
			}
		}
	}


		   // Очистить поле вывода очереди и очередь
	private: System::Void btnClearQue_Click(System::Object^ sender, System::EventArgs^ e) {
		ClearEP();
		q.Clear();
		this->tBOutputQue->Clear();
	}

	private: System::Void btnPush_Click(System::Object^ sender, System::EventArgs^ e) {
		ClearEP();
		// Считываем число
		int number;
		bool res = Int32::TryParse(tBInputPush->Text, number);
		String^ str = "";
		// Проверка на число
		if (!res) {
			this->eP1->SetError(btnPush, "Не целое число");
			return;
		}
		q.AddLast(number);
		QueueOutput();
	}

private: System::Void btnPop_Click(System::Object^ sender, System::EventArgs^ e) {
	ClearEP();
	this->tBOutputPop->Clear();

	// Проверка на непустой список
	if (q.Count > 0) {
		// Считываем последнее число
		String^ str = Convert::ToString(q.Last->Value);
		// Выводим число
		this->tBOutputPop->Text = str;
		// Удаляем последний элемент
		q.RemoveLast();

		// Если в списке есть элементы, то выводим
		if (q.Count > 0) {
			QueueOutput();
		}
		else {
			this->tBOutputQue->Clear();
		}
	}
	else {
		this->eP1->SetError(btnPop, "Пустой список");
		return;
	}
}



private: System::Void btnSum_Click(System::Object^ sender, System::EventArgs^ e) {
	ClearEP();
	// Вспомогательный двусвязный список
	System::Collections::Generic::LinkedList<int>^ buffer = gcnew System::Collections::Generic::LinkedList<int>();
	int a, b;
	bool resA = Int32::TryParse(tBInputA->Text, a);
	bool resB = Int32::TryParse(tBInputB->Text, b);
	int sum = 0, i = 0;

	if (!resA) {
		this->eP1->SetError(tBInputA, "Не целое число");
		return;
	}
	if (!resB) {
		this->eP1->SetError(tBInputB, "Не целое число");
		return;
	}
	if (a < 0 || a > b || a > q.Count) {
		this->eP1->SetError(tBInputA, "Неверный интервал");
		return;
	}
	if (b > q.Count) {
		this->eP1->SetError(tBInputB, "Неверный интервал");
		return;
	}

	// Пока основной список не пуст
	while (q.Count > 0) {
		// Записываем первый элемент во вспомогательный список
		buffer->AddLast(q.First->Value);

		// Суммируем элементы в заданном интервале
		if (i >= a && i <= b) {
			sum += q.First->Value;
		}

		// Удаляем первый элемент из основного списка
		q.RemoveFirst();
		i++;
	}

	// Пока вспомогательный список не пуст
	while (buffer->Count > 0) {
		// Записываем в основной список первый элемент
		q.AddLast(buffer->First->Value);
		// Удаляем первый элемент из вспомогательного списка
		buffer->RemoveFirst();
	}

	// Выводим результат
	this->tBOutputSum->Text = Convert::ToString(sum);
}


	private: System::Void btnNewAfterMax_Click(System::Object^ sender, System::EventArgs^ e) {
		ClearEP();
		this->tBOutputNAM->Clear();

		// Вспомогательные двусвязные списки
		System::Collections::Generic::LinkedList<int>^ buffer = gcnew System::Collections::Generic::LinkedList<int>();
		System::Collections::Generic::LinkedList<int>^ buffer2 = gcnew System::Collections::Generic::LinkedList<int>();

		if (q.Count == 0) {
			this->eP1->SetError(btnNewAfterMax, "Пустой список");
			return;
		}

		int number;
		bool res = Int32::TryParse(tBInputNAM->Text, number);
		if (!res) {
			this->eP1->SetError(tBInputNAM, "Не целое число");
			return;
		}

		// Перемещение элементов из основного списка в buffer2 и поиск четных элементов
		while (q.Count > 0) {
			// Записываем первый элемент во вспомогательный список buffer2
			int currentValue = q.First->Value;
			buffer2->AddLast(currentValue);

			// Если элемент четный, добавляем новый элемент после него
			if (currentValue % 2 == 0) {
				buffer->AddLast(currentValue);
				buffer->AddLast(number); // Вставляем новый элемент после четного
			}
			else {
				buffer->AddLast(currentValue); // Просто добавляем нечетный элемент
			}

			// Удаляем первый элемент из основного списка
			q.RemoveFirst();
		}

		// Перемещение элементов из buffer2 обратно в основной список
		while (buffer2->Count > 0) {
			q.AddLast(buffer2->First->Value);
			buffer2->RemoveFirst();
		}

		// Формирование результата для вывода
		String^ result = "";
		while (buffer->Count > 0) {
			result += System::Convert::ToString(buffer->First->Value) + " ";
			buffer->RemoveFirst();
		}

		this->tBOutputNAM->Text = result;
	}

	};
}
