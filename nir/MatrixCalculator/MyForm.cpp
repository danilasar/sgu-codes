#include <cmath>
#include <vector>
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^> ^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MatrixCalculator::MyForm form;
	Application::Run(% form);
}

