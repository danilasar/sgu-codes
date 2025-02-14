#include "MyCollections.h" 

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MyCollectionss::MyCollections form;
	Application::Run(% form);
}