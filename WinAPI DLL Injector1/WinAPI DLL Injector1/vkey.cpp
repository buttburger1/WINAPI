#include "Common.h"
 
//VK_TAB 0x09

void convertVKEY(char* key)
{
	for(int i = 0; i < strlen(key); i++)
	{
		//printf("CHAR: %c - %d - 0x%X\n", key[i], key[i], key[i]);

		if(key[i] == 95)
		{
			key[i] = 0xBD;
			//printf("AAA: %d - %d\n", i, key[i]);
		}

		if(key[i] > 95 && key[i] < 122) //96,123
		{
			//printf("BBB: %d - %d\n", i, key[i]);
			key[i] = key[i] - 32;
			//printf("CCC: %d\n", key[i]);
		}

	}
	//printf("OKAY!\n");
}

int sendinputglobalcounter = 0;

void printSendkey(char* buffer)
{
	Sleep(100);
	//int intarray[100];
	//WORD morearray[10];
	//INPUT ip[15] = {0};
	INPUT inp = {0};
	INPUT ip[30];
	
	int bufferstrlen = strlen(buffer);
	//int passwordstrlen = strlen(passwordbuffer);
		
	for(int i = 0; i < bufferstrlen; i++)//bufferstrlen; i++)//sizeof(intarray) / sizeof(intarray[0]); i++)
	{
		//printf("iLoop: %d - %d\n", i, bufferstrlen);//sizeof(intarray) / sizeof(intarray[0]));
		//printf("iLoop: %d - %d\n", i, bufferstrlen);
		//INPUT ip[100];
		//Sleep(100);
		

		//morearray[i] = 75+i;
		//morearray[i] = 55+i;
		//WORD wCharacter[2];
		//int len = ToAscii(kbdStruct.vkCode, kbdStruct.scanCode, keyboard_state, wCharacter, 0);
		//if (len == 1) printf("%c", wCharacter[0]);
		//if (len == 2) printf("%c", wCharacter[1]);

		
		if(buffer[i] == -67)//(buffer[i] == -67)
		{
			ip[i].type = INPUT_KEYBOARD;
			ip[i].ki.wVk = VK_LSHIFT;
			SendInput(1, &ip[i], sizeof(INPUT));
			//printf("ASS\n");
		}


		ip[i].type = INPUT_KEYBOARD;
		ip[i].ki.wScan = 0;
		ip[i].ki.dwFlags = 0;//KEYEVENTF_UNICODE;
		ip[i].ki.time = 0;
		ip[i].ki.dwExtraInfo = 0;
		ip[i].ki.wVk = buffer[i];//morearray[i];//105;//morearray[i];//intarray[i];
		SendInput(1, &ip[i], sizeof(INPUT));//SendInput(sendinputglobalcounter, ip, sizeof(INPUT));


		ip[i].type       = INPUT_KEYBOARD;
		ip[i].ki.dwFlags = KEYEVENTF_KEYUP;
		ip[i].ki.wVk   = buffer[i];//buffer[i];
		SendInput(1, &ip[i], sizeof(INPUT));


		if(buffer[i] == -67)//(buffer[i] == -67)
		{
			ip[i].type = INPUT_KEYBOARD;
			//ip[i].ki.wVk = VK_LSHIFT;
			ip[i].ki.wVk = VK_LSHIFT;
			SendInput(1, &ip[i], sizeof(INPUT));
			//printf("ASS2\n");
		}
		
		// Send the keyboard event to the specified window
		//SendInput(1, &ip[i], sizeof(INPUT));
		//ip[i].ki.dwFlags = KEYEVENTF_KEYUP;
		//SendInput(1, &ip[i], sizeof(INPUT));
		//SendInput(1, &ip[i], sizeof(INPUT));
		//ip[i].ki.dwFlags = KEYEVENTF_KEYUP;
		//SendInput(sendinputglobalcounter, ip, sizeof(INPUT));
		sendinputglobalcounter++;
	}

	inp.type = INPUT_KEYBOARD;
	inp.ki.wScan = 0;
	inp.ki.dwFlags = 0;//KEYEVENTF_UNICODE;
	inp.ki.time = 0;
	inp.ki.dwExtraInfo = 0;
	inp.ki.wVk = 0x09;//morearray[i];//105;//morearray[i];//intarray[i];
	SendInput(1, &inp, sizeof(INPUT));//SendInput(sendinputglobalcounter, ip, sizeof(INPUT));


	inp.type       = INPUT_KEYBOARD;
	inp.ki.dwFlags = KEYEVENTF_KEYUP;
	inp.ki.wVk   = 0x09;//buffer[i];
	SendInput(1, &inp, sizeof(INPUT));

}