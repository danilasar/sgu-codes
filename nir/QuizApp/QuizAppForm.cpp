#include "QuizAppForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	QuizApp::QuizAppForm form; // здесь название вашего проекта  
	Application::Run(% form);
}