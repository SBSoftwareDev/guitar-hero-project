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

#define KEY_LBRACK	0x1A //UP
#define KEY_RBRACK	0x1B //DOWN
#define KEY_UP		0x48
#define KEY_DOWN	0x50
#define KEY_LEFT	0x4B
#define KEY_RIGHT	0x4D

#define PRESS_DELAY	200 //Milliseconds

//The PRESS_DELAY seems to affect my COM reading.

void pressKey(int, int);
//void checkStrum(int);
//void checkStrum(int, int);
//void holdKey(int, SerialPort);

INPUT ip;
INPUT mp;

using namespace System;
using namespace System::IO::Ports;

int main(array<System::String ^> ^args)
{
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	mp.type = INPUT_MOUSE;
	mp.mi.mouseData = 0;
	mp.mi.dwFlags = 0;

	String^ portName = "COM1";
	int baudRate = 4800;
	// arduino settings
	SerialPort^ arduino;
	arduino = gcnew SerialPort(portName, baudRate);
	// open port

	int colors;

	try
	{
		arduino->Open();

		std::cout << "Running..." << std::endl;

		while (true)
		{
			IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
			const char* linkStr = static_cast<char*>(p.ToPointer());
			System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

			colors = std::atoi(linkStr);

			if (colors != 0)
			{
				//checkStrum(colors);

				switch (colors)
				{
					//Mouse buttons, strum bar
				case 8:
					mp.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &mp, sizeof(INPUT));

					while (colors == 8)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						//checkStrum(colors, KEY_V);
					}

					mp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &mp, sizeof(INPUT));
					break;

				case 9:
					mp.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
					SendInput(1, &mp, sizeof(INPUT));

					while (colors == 9)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						//checkStrum(colors, KEY_V);
					}

					mp.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
					SendInput(1, &mp, sizeof(INPUT));
					break;
					//Most Common, Single Buttons
				case 1:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 1)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						//checkStrum(colors, KEY_V);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 10:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_C;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 10)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						//checkStrum(colors, KEY_C);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 100:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_X;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 100)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_X);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 1000:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_Z;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 1000)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_Z);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 10000:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_LSHIFT;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 10000)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_LSHIFT);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
					//Double button presses
				case 11:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_C;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 11)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_C);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_V;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 101:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_X;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 101)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_X);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_V;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 1001:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_Z;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 1001)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_Z);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_V;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 10001:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_LSHIFT;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 10001)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_LSHIFT);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_V;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 110:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_C;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_X;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 110)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_X);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_C;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 1010:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_C;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_Z;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 1010)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						////checkStrum(colors, KEY_Z);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_C;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 10010:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_C;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_LSHIFT;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 10010)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						//checkStrum(colors, KEY_LSHIFT);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_C;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 1100:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_X;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_Z;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 1100)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						//checkStrum(colors, KEY_Z);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_X;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 10100:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_X;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_LSHIFT;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 10100)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						//checkStrum(colors, KEY_LSHIFT);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_X;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
					break;
				case 11000:
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_Z;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_LSHIFT;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 11000)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);

						//checkStrum(colors, KEY_LSHIFT);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_Z;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));

					//checkStrum(colors);
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

/*void checkStrum(int input)
{
	mp.type = INPUT_MOUSE;
	mp.mi.mouseData = 0;
	mp.mi.dwFlags = 0;

	if (input == 8)
	{
		mp.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &mp, sizeof(INPUT));

		Sleep(5);

		mp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &mp, sizeof(INPUT));
	}

	if (input == 9)
	{
		mp.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &mp, sizeof(INPUT));

		Sleep(5);

		mp.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &mp, sizeof(INPUT));
	}

}*/

/*void //checkStrum(int input, int key1)
{
if (input == 8)
{
ip.ki.dwFlags = KEYEVENTF_SCANCODE;
ip.ki.wScan = KEY_UP;
SendInput(1, &ip, sizeof(INPUT));

ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
SendInput(1, &ip, sizeof(INPUT));
}

if (input == 9)
{
ip.ki.dwFlags = KEYEVENTF_SCANCODE;
ip.ki.wScan = KEY_DOWN;
SendInput(1, &ip, sizeof(INPUT));

ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
SendInput(1, &ip, sizeof(INPUT));
}

ip.ki.wScan = key1;
}*/

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