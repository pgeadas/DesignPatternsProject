#pragma once
#include "stdafx.h"
#include "Form1.h"



namespace ProjectoNEW {
	using namespace System::Threading;
	
	void Form1::DoWork() {
		Thread::Sleep(20);
		int data = 5;
		Console::WriteLine("Instance thread procedure. Data = {0}", data);
		//this->label1->Text = L"label N";
		this->Refresh();
		Thread::Sleep(3000);
		this->Refresh();

	}

	Renderer::Renderer(Form1^ f): form(f) {
		
		ThreadStart^ threadDelegate = gcnew ThreadStart(form, &Form1::DoWork);
		Thread^ newThread = gcnew Thread(threadDelegate);
		newThread->Start();
	}
	void Renderer::render() {}
}