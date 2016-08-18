// ProjectoNEW.cpp : main project file.
#pragma once

#include "stdafx.h"
static double PI = 3.14159265;
static int BULLET_VELOCITY = 9;
static int RESOURCE_VELOCITY = 2;
static int MAX_VELOCITY = 6;
static int MIN_VELOCITY = 2;
#include "Form1.h"

using namespace ProjectoNEW;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	
	return 0;
}