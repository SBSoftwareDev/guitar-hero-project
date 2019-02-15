#using <System.dll>
#include <windows.h>
#include <iostream>
#include "StdAfx.h"
#include <string>

#define KEY_V		0x2F
#define KEY_C		0x2E
#define KEY_X		0x2D
#define KEY_Z		0x2C
#define KEY_LSHIFT	0x2A

#define PRESS_DELAY	200 //Milliseconds

//The PRESS_DELAY seems to affect my COM reading.

void pressKey(int, int);
//void holdKey(int, SerialPort);

INPUT ip;

using namespace System;
using namespace System::IO::Ports;

int main(array<System::String ^> ^args)
{
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	String^ portName = "COM1";
	int baudRate = 9600;
	// arduino settings
	SerialPort^ arduino;
	arduino = gcnew SerialPort(portName, baudRate);
	// open port

	int colors;

	try
	{
		arduino->Open();
		
		while (true)
		{
			IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
			const char* linkStr = static_cast<char*>(p.ToPointer());
			System::Runtime::InteropServices::Marshal::FreeHGlobal(p);
			
			colors = std::atoi(linkStr);
			std::cout << colors << std::endl;

			//We need to press the button, and hold it down until it is not pressed anymore.
			//Don't keep rapidly pressing it.

			if (colors != 0)
			{
				switch (colors)
				{
				//Most Common, Single Buttons
				case 00000001:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 00000001)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);
					}
					
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					
					break;
				case 00000010:
					ip.ki.dwFlags = 0;
					ip.ki.wVk = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 00000010)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);
					}

					ip.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					break;
				case 00000100:
					ip.ki.dwFlags = 0;
					ip.ki.wVk = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 00000100)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);
					}

					ip.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					break;
				case 00001000:
					ip.ki.dwFlags = 0;
					ip.ki.wVk = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 00001000)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);
					}

					ip.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					break;
				case 00010000:
					ip.ki.dwFlags = 0;
					ip.ki.wVk = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 00010000)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);
					}

					ip.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					break;
				//Double button presses
				case 00000011:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_C, PRESS_DELAY);
					break;
				case 00000101:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_X, PRESS_DELAY);
					break;
				case 00001001:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					break;
				case 00010001:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
				case 00000110:
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_X, PRESS_DELAY);
					break;
				case 00001010:
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					break;
				case 00010010:
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
				case 00001100:
					pressKey(KEY_X, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					break;
				case 00010100:
					pressKey(KEY_X, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
				case 00011000:
					pressKey(KEY_Z, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
					//Triple presses
				case 00001011:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					break;
				case 00011010:
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
				case 00001101:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_X, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					break;
				case 00010110:
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_X, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
				case 00001110:
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_X, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					break;
				case 00000111:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_X, PRESS_DELAY);
					break;
				case 00011100:
					pressKey(KEY_X, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
				case 00010101:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_X, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
				case 00011001:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_Z, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
				case 00010011:
					pressKey(KEY_V, PRESS_DELAY);
					pressKey(KEY_C, PRESS_DELAY);
					pressKey(KEY_LSHIFT, PRESS_DELAY);
					break;
					//00000000
					//default:
				}
			}
			
		}

		arduino->Close();
	}
	catch (IO::IOException^ e)
	{
		Console::WriteLine(e->GetType()->Name + ": Port is not ready");
	}
	catch (ArgumentException^ e)
	{
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax, must start with COM/com");
	}
	// end program
	system("PAUSE");

	return 0;
}

void pressKey(int Vk, int delay)
{
	ip.ki.wVk = Vk;
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(delay);
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

/*void holdKey(int Vk,  SerialPort COM)
{
	ip.ki.dwFlags = 0;
	ip.ki.wVk = KEY_V;
	SendInput(1, &ip, sizeof(INPUT));

	while (Vk == 00000001)
	{
		IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(COM->ReadLine());
		const char* linkStr = static_cast<char*>(p.ToPointer());
		System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

		Vk = std::atoi(linkStr);
	}

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}*/