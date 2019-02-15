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

//These are here, just in case the mouse input doesn't work. If I change the preferences inside of the game,
//All I have to do is update it here. No need to go back on the internet and search for the same codes over and over.
#define KEY_UP		0x48
#define KEY_DOWN	0x50
#define KEY_LEFT	0x4B
#define KEY_RIGHT	0x4D

void pressKey(int, int);

//I need to simulate mouse and keyboard input, because that's what the Guitar Hero game needs.
//The keyboard input is mapped to the game as such:
//The 'V' key is green, 'C' red, 'X' yellow, 'Z' blue, and 'Left Shift' is orange.

INPUT ip; //Global INPUT struct, for both <-keyboard and
INPUT mp; //<-mouse input

using namespace System;
using namespace System::IO::Ports;

int main(array<System::String ^> ^args)
{
	//Setting up keyboard INPUT struct
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	//Setting up mouse INPUT struct
	mp.type = INPUT_MOUSE;
	mp.mi.mouseData = 0;
	mp.mi.dwFlags = 0;

	//Setting up Arduino to be read, through some native libraries I discovered online. This code was found online.
	String^ portName = "COM1";
	int baudRate = 4800;
	SerialPort^ arduino;
	arduino = gcnew SerialPort(portName, baudRate);

	//This variable is the Arduino COM input, when it is to be read.
	int colors;

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
			colors = std::atoi(linkStr);

			switch (colors)
			{
				//This first two cases are for the mouse input. If the Arduino sends an '8' or a '9', the strum bar was pressed.
				case 8:
					//Set a flag indicating that we want the left mouse button to be pressed.
					mp.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					//Pass this mouse INPUT struct through the system, thus pressing the mouse button.
					SendInput(1, &mp, sizeof(INPUT));

					//Continue to press the mouse button down while the Arduino continues to send an '8' to through the COM port.
					while (colors == 8)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);
					}

					//Since the '8' is no longer being sent or since we stopped pressing the strum bar, update the flag and send it through.
					mp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &mp, sizeof(INPUT));
					break;
				case 9:
					//This code is identical to the case above, but adjusted for the right mouse button and 'up' strum.
					mp.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
					SendInput(1, &mp, sizeof(INPUT));

					while (colors == 9)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);
					}

					mp.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
					SendInput(1, &mp, sizeof(INPUT));
					break;
				
				//Now we process the most common, single button presses that might occur. 
				case 1:
					//Set up the keyboard INPUT struct with hardware scan codes, instead of virtual scan codes. Virtual scan codes aren't
					//detected by the Guitar Hero game.
					ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					ip.ki.wScan = KEY_V;
					SendInput(1, &ip, sizeof(INPUT));

					while (colors == 1)
					{
						IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(arduino->ReadLine());
						const char* linkStr = static_cast<char*>(p.ToPointer());
						System::Runtime::InteropServices::Marshal::FreeHGlobal(p);

						colors = std::atoi(linkStr);
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					break;

				//The remaining code for the Switch statement is identical, but adjusted for different inputs.
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					break;
				//We've covered all of the singular button presses, now it's time for the possibilities of double button presses.
				case 11:
					//We set up the INPUT struct, send it through, modify it, then send it again. 
					//The first button hasn't been released yet, so this works perfectly fine.
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
					}

					//Since the scan code didn't change, there is no need to modify it. It's still the second key, or the 'C' key.
					//We set the flags to release the key, then we change the scan code back to the key that's still being pressed.
					//Then we remove it.
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_V;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_V;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_V;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_V;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_C;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_C;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_C;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_X;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_X;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
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
					}

					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.wScan = KEY_Z;
					ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					break;
				//These are all possible combinations of triple presses, which are definitely less common. They are only
				//available on 'Expert' mode. They haven't been coded as of yet.
				/*case 00001011:
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
					break; */
				//We don't have a 'default' because we don't want to do anything if it is anything other than
				//what we have prepared for. We want to remain idle.
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
	
	//This is the end of the program.
	system("PAUSE");
	return 0;
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
