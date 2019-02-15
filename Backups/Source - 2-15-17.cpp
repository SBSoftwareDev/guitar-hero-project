/*
*	Sean Brown
*	This was last updated on 1-6-17
*/
#using <System.dll>
#include <windows.h>
#include <iostream>
#include "StdAfx.h"
#include <string>

//Easy to read key definitions, no need to memorize all of these codes.
#define KEY_V		0x2F
#define KEY_C		0x2E
#define KEY_X		0x2D
#define KEY_Z		0x2C
#define KEY_LSHIFT	0x2A
#define KEY_BSPACE	0x0E
#define KEY_M		0x32
#define KEY_N		0x31

//These are here, just in case the mouse input doesn't work. If I change the preferences inside of the game,
//All I have to do is update it here. No need to go back on the internet and search for the same codes over and over.
#define KEY_UP		0x48
#define KEY_DOWN	0x50
#define KEY_LEFT	0x4B
#define KEY_RIGHT	0x4D

void readData(const char*);

//I need to simulate mouse and keyboard input, because that's what the Guitar Hero game needs.
//The keyboard input is mapped to the game as such:
//The 'V' key is green, 'C' red, 'X' yellow, 'Z' blue, and 'Left Shift' is orange.

INPUT ip; //Global INPUT struct, for both <-keyboard and
INPUT mp; //<-mouse input

using namespace System;
using namespace System::IO::Ports;

int main(array<System::String ^> ^args)
{
	temp = "0000000000";

	//Setting up keyboard INPUT struct
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	//Setting up mouse INPUT struct
	mp.type = INPUT_MOUSE;
	mp.mi.dwFlags = 0;

	//Setting up Arduino to be read, through some native libraries I discovered online. This code was found online.
	String^ portName = "COM1";
	int baudRate = 9600;
	SerialPort^ arduino;
	arduino = gcnew SerialPort(portName, baudRate);

	//This variable is the Arduino COM input, when it is to be read.
	const char* colors;

	try
	{
		arduino->Open();

		std::cout << "Running..." << std::endl;

		/*As far as what we are accepting as input from the Arduino, its either:
		********
		A '0' meaning nothing is being pressed.
		An '8' meaning a 'down' strum.
		A '9' meaning an 'up' strum.
		A binary sequence for the state of the buttons.
		**
		The buttons are, in order, Green, Red, Yellow, Blue, Orange.
		E.g. 10101 means Orange, Yellow, and Green respectively.
		Similarly, 1001 means Blue and Green.
		11 would mean Red and Green,
		10 would mean Red only.
		*/

		//This loop is running until the program closes.
		while (true)
		{
			//These three lines are required to convert type "String^" to type "Integer"
			IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
			const char* linkStr = static_cast<char*>(p.ToPointer());
			System::Runtime::InteropServices::Marshal::FreeHGlobal(p);
			
			//This is the final line needed to get usable Arduino COM input.
			colors = linkStr;
			readData(colors);
			temp = colors;
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
	
	//This is the end of the program.
	system("PAUSE");
	return 0;
}

void readData(const char* data)
{
	for (int i = 0; i < strlen(data); i++)
	{
		switch (i)
		{
			//Up Strum
		case 0:
			if (data[i] == '1')
			//if(colors->substr(0, colors->length(), 1) == "1")
			{
				mp.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				SendInput(1, &mp, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				mp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SendInput(1, &mp, sizeof(INPUT));
			}
			break;
			//Down Strum
		case 1:
			if (data[i] == '1')
			{
				mp.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
				SendInput(1, &mp, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				mp.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
				SendInput(1, &mp, sizeof(INPUT));
			}
			break;
		case 2:
			if (data[i] == '1')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_V;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_V;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;
		case 3:
			if (data[i] == '1')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_C;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_C;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;
		case 4:
			if (data[i] == '1')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_X;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_X;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;
		case 5:
			if (data[i] == '1')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_Z;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_Z;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;
		case 6:
			if (data[i] == '1')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_LSHIFT;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_LSHIFT;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;
		case 7:
			if (data[i] == '1')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_BSPACE;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_BSPACE;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;
		case 8:
			if (data[i] == '1')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_BSPACE;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_BSPACE;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;
		case 9:
			if (data[i] == '1')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_M;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if (temp[i] == '1' && data[i] == '0')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_M;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;
		/*case 10:
			if (data[i] == '0' || data[i] == '1' || data[i] == '2')
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE;
				ip.ki.wScan = KEY_N;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if ((temp[i] == '0' || temp[i] == '1' || temp[i] == '2') && (data[i] == '8' || data[i] == '9'))
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				ip.ki.wScan = KEY_N;
				SendInput(1, &ip, sizeof(INPUT));
			}
			break;*/
		}
	}
}

//I might need this function, I doubt it, but I'm not sure yet.

/*
void pressKey(int Vk, int delay)
{
	ip.ki.wVk = Vk;
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(delay);
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}*/
