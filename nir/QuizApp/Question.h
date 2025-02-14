#pragma once

ref class Question {
public:
	System::String^ Text;
	System::Collections::Generic::List<System::String^>^ CorrectAnswers;
	System::Collections::Generic::List<System::String^>^ Answers;


public:
	Question(System::String^ text, System::Collections::Generic::List<System::String^>^ correctAnswers, System::Collections::Generic::List<System::String^>^ answers) {
		Text = text;
		CorrectAnswers = correctAnswers;
		Answers = answers;
	}
};