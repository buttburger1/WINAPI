#include "Common.h"

HWND hWnd;
HWND hWndList1; //SELECT DLL
HWND hWndList2; //SELECT SVG XML
HWND hWndList3; //MINI COUNTER
HWND hWndList4; //TARGET EXE
HWND hWndList5; //LOGIN CREDENTIALS
HWND hWndList6; //ACTIVITY LOG
HWND hWndList7; //ACTIVITY LOGGER
HWND hWndButton;

HWND externHWND[100];
HWND firstWindow;

int width, height, cwidth, cheight, borderWidth, borderHeight;
int list[1000];

//PRE-DEFINITIONS
int newarraytest = 0;
int svgcounter = -1;
//int rectcounter = 0;
int test = 0;

char strg[100];
char *strp;


htmlDocPtr doc;
xmlNode *roo_element = NULL;

//extern mySVGstruct mySVG[10][30]; //*pGraph_obj;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	WNDCLASS wc = {0};
	wc.lpszClassName = TEXT("Buttons");
	wc.hInstance     = hInstance ;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc   = WndProc ;
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	
	RegisterClass(&wc);
	/*
	CreateWindow(wc.lpszClassName, TEXT("ButtonsTEST"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		150, 150, 230, 150, 0, 0, hInstance, 0);
	*/
	
	hWnd = CreateWindowEx(NULL, wc.lpszClassName, TEXT("ButtonsTEST"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 640, 480, NULL, NULL, hInstance, NULL);
	//SendMessage(hWndList1, LB_ADDSTRING, NULL, (LPARAM)"two");
	
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	//unsigned int i;
	
	if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}
	//Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);
	//Print the name and process identifier for each process.
	
	/*
	int ii = 247593;
	TCHAR str[10];
	sprintf(str, "%d", ii);
	const char * s = "hello";
	
	for(i = 0; i < cProcesses; i++)
	{
		if(aProcesses[i] != 0)
		{
			PrintProcessNameAndID(aProcesses[i], hWndList7);
			list[i] = aProcesses[i];
		}
	}
	*/
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	


		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//CLOCK REFRESH
	//SetTimer(hWnd, TIMER1, 3000, NULL);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;

	//LIBXML FREE EVERYTHING UP & CLOSE
    xmlFreeDoc(doc);   //free document
    xmlCleanupParser();//free globals
}


char DLLpath[1000];
char SVGXMLpath[1000];
char EXEpath[1000];
char Loginpath[1000];

TCHAR buffer[1000];
int index = 0;
LPTSTR long_string;

HWND found = GetForegroundWindow();

//int lastResized = 0;
int lastResized = 1;
int seekcounter = 1;
//int buffint = 0;

//LOGIN CREDENTIALS
extern char cTEXTprint[100][1000];


DWORD hwndPID, foundPID;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_TIMER:
		if(TIMER1)
		{
			//SetTimer(hwnd,TIMER1,3000,NULL);
			//DWORD hwndPID, foundPID;
			found = GetForegroundWindow();
			
			//int seek = seekcounter;
			//char seekStr[100];
			//sprintf(seekStr, "%d", seek);
			//MessageBox(NULL, seekStr, "FINDWINDOW", MB_OK);

			for(int ii = 1; ii < seekcounter; ii++)//6
			{
				GetWindowThreadProcessId(found, &hwndPID);
				GetWindowThreadProcessId(externHWND[ii], &foundPID);
				if(hwndPID == foundPID)
				{
					//char*bufftok;
					char buff[100];
					GetWindowText(found, buff, sizeof(buff));
					char*bufftok = buff;
					
					/*
					//strcpy(bufftok, buff);
					//char*bufftok = buff;
					//MessageBox(NULL, bufftok, "FINDWINDOW", MB_OK);
					
					//RISKY TO USE
					//bufftok = strtok(buff, " ,.-_");
					//MessageBox(NULL, bufftok, "FINDWINDOW", MB_OK);
					//bufftok = strtok(NULL, " ,.-_");
					//MessageBox(NULL, bufftok, "FIND ALERT", MB_OK);

					//char *a = "1234";
					//int i = atoi(a);

					//char *a = "1234";
					*/

					
					//charscan(bufftok, buffint);
					//char buff[100];
					char*entirebuff = "";
					//strcpy(buff, ch);
					//MessageBox(NULL, buff, "FINDWINDOW", MB_OK);
					
					/*
					//char buff[100] = "WoW_1";
					//char*bufftok = buff;
					//MessageBox(NULL, bufftok, "FINDWINDOW", MB_OK);
					//printf("TEST: %s\n", buff);
					*/
					
					char buff1[100];
					char buff2[100];
					char*buff2tok = "";
					
					int counter = 0;
					//int test = 0;
					
					//char homo3[100];
					//char*homo4;
					
					for(int i = 0; i < 50; i++)
					{
						//printf("cARRAY: %c\n", buff[i]);
						if(buff[i] == '_')
						{
							//printf("GOT SOMETHING: %d\n", i);
							strncpy(buff1, buff, i);
							//dest[10] = 0;
							counter = i;
						}
						if(buff[i] == '\0')
						{
							int internalcounter = 0;
							//printf("EOF: %d\n", i);
							entirebuff = buff;
							
							for(int ii = counter + 1; ii < i; ii++)
							{
								//printf("TESTBUFFS: %c\n", buff[ii]);
								buff2[internalcounter] = buff[ii];
								internalcounter++;
							}
							buff2tok = buff2;
							//printf("TEST: %d Counter: %d I: %d\n", test, counter, i);
							//strncpy(buff2, myString, 10);
							break;
						}
					}
					
					//printf("ASS: %s\n", entirebuff);
					//MessageBox(NULL, entirebuff, entirebuff, MB_OK);
					//printf("HOMO: %s\n", buff1);
					//MessageBox(NULL, buff1, buff1, MB_OK);
					
					int buffint = atoi(buff2tok);
					//MessageBox(NULL, buff2tok, "BUFF2TOK", MB_OK);
					//printf("AAA: %s\n", buff2tok);
					

					if(buffint != lastResized)
					{

						//MOVE TO MAINWINDOW
						SetWindowPos(found, 0, mySVG[svgcounter][test-1].x, mySVG[svgcounter][test-1].y,
							mySVG[svgcounter][test-1].width, mySVG[svgcounter][test-1].height, 0);

						//REVERT BACK TO PLACE
						SetWindowPos(externHWND[lastResized], 0, mySVG[svgcounter][lastResized].x, mySVG[svgcounter][lastResized].y,
						mySVG[svgcounter][lastResized].width, mySVG[svgcounter][lastResized].height, 0);

						lastResized = buffint;
					}

				}
			}
			
			/*
			if(found == externHWND[0])
			{
				char buff[256];
				char*bufftok;
				GetWindowText(found, buff, sizeof(buff));			
				//strcpy(bufftok, buff);
				bufftok = strtok(buff, " ,.-_");
				//MessageBox(NULL, bufftok, "FINDWINDOW", MB_OK);
				bufftok = strtok(NULL, " ,.-_");
				//MessageBox(NULL, bufftok, "FIND ALERT", MB_OK);

				//char string[] = "1234";
				//int sum = atoi(bufftok);
				//int tick = atoi(bufftok);
				
				SetWindowPos(found, 0, mySVG[svgcounter][test-1].x, mySVG[svgcounter][test-1].y,
								mySVG[svgcounter][test-1].width, mySVG[svgcounter][test-1].height, 0);

				//MessageBox(NULL, "BBB", "AAAALERT", MB_OK);
			}
			*/
						
			/*
			char bff[256];
			GetWindowText(hWnd, bff, sizeof(bff));
			//printf("WINDOWTEXT: %s\n", bff);
			//MessageBox(NULL, bff, "TESTICLES", MB_OK);

			char titlebuffer[256] = "WoW_";
			strcat(titlebuffer, strp);
			//MessageBox(NULL, titlebuffer, "TESTICLES", MB_OK);

			//SetWindowText(hWnd, "Nutsack");
			SetWindowText(hWnd, titlebuffer);
			GetWindowText(hWnd,bff,sizeof(bff));
			//printf("WINDOWTEXT: %s\n", bff);
			*/


			//MessageBox(NULL, "REFRESH TEST!", "Note", MB_OK);
		}
		
		if(TIMER2)
        {
			//SetTimer(hwnd,TIMER2,5000,NULL);
			//MessageBox(NULL, "I'm a faggot!", "Note", MB_OK);
        }
        break;

	case WM_CREATE:
		{
			CreateWindow(TEXT("button"), TEXT("DLL"),
				WS_VISIBLE | WS_CHILD,
				20, 10, 80, 20,
				hwnd, (HMENU) 1, NULL, NULL);

			CreateWindow(TEXT("button"), TEXT("SVG XML"),
				WS_VISIBLE | WS_CHILD ,
				20, 90, 80, 20,
				hwnd, (HMENU) 2, NULL, NULL);

			CreateWindow(TEXT("button"), TEXT("EXE"),
				WS_VISIBLE | WS_CHILD ,
				20, 170, 80, 20,
				hwnd, (HMENU) 3, NULL, NULL);

			CreateWindow(TEXT("button"), TEXT("LOGIN TXT"),
				WS_VISIBLE | WS_CHILD ,
				20, 250, 80, 20,
				hwnd, (HMENU) 4, NULL, NULL);
			
			CreateWindow(TEXT("button"), TEXT("Exit"),
				WS_VISIBLE | WS_CHILD ,
				540, 420, 80, 20,
				hwnd, (HMENU) 5, NULL, NULL);
			
			//Create Listbox's
			//LOAD DLL
			hWndList1 = CreateWindowEx(NULL, "LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL, 20, 40, 600, 40, hwnd, NULL, GetModuleHandle(NULL), NULL); //LBS_NOTIFY
			//LOAD XML
			hWndList2 = CreateWindowEx(NULL, "LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL, 20, 120, 600, 40, hwnd, NULL, GetModuleHandle(NULL), NULL); //LBS_NOTIFY
			//LOAD MINI COUNTER
			hWndList3 = CreateWindowW(L"Static", L"0", WS_CHILD | WS_VISIBLE, 130, 90, 200, 20, hwnd, NULL, NULL, NULL);//(HMENU)1
			//target executable
			hWndList4 = CreateWindowEx(NULL, "LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL, 20, 200, 600, 40, hwnd, NULL, GetModuleHandle(NULL), NULL);
			//LOGIN CREDENTIALS
			hWndList5 = CreateWindowEx(NULL, "LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL, 20, 280, 600, 40, hwnd, NULL, GetModuleHandle(NULL), NULL);
			//LOG COUNTER
			hWndList6 = CreateWindowW(L"Static", L"CONSOLE", WS_CHILD | WS_VISIBLE, 20, 330, 200, 20, hwnd, NULL, NULL, NULL);//(HMENU)1//250
			//LOGGER
			//hWndList7 = CreateWindowEx(NULL, "LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | LBS_NOTIFY, 20, 360, 600, 60, hwnd, NULL, GetModuleHandle(NULL), NULL);//280
			hWndList7 = CreateWindowEx(NULL, "LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | LBS_NOTIFY | WS_VSCROLL, 20, 360, 600, 60, hwnd, NULL, GetModuleHandle(NULL), NULL);//280	
			//Create Button
			hWndButton = CreateWindowEx(NULL, "BUTTON", "LAUNCH!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 420, 80, 20, hwnd, (HMENU)IDC_MAIN_BUTTON, GetModuleHandle(NULL), NULL);// | WS_DISABLED

			break;
		}
	
	case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
			case CBN_SELCHANGE: //LBN_SELCHANGE
				{
					//EnableWindow( GetDlgItem( hWnd, (HMENU)IDC_BUTTON_MAIN ), TRUE );
					//SendMessage(hWndList1, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));
					
					HWND const control = (HWND)lParam;
					index = ::SendMessage(control, LB_GETCURSEL, 0, 0);
					if (index == CB_ERR)
					{
						return 0;
					}
										
					//int i = 3;
					std::string str;
					//LPTSTR long_string;
										
					str = std::to_string(index);
					long_string = new TCHAR[str.size() + 1];
					strcpy(long_string, str.c_str());
					//MessageBox(NULL, long_string, "SELECT ALERT", MB_OK);
					
					/*
					// [optional] Retrieve text of selected item
					int const len = (int)::SendMessage(control, CB_GETLBTEXTLEN, (WPARAM)index, 0) ;
					if (len == CB_ERR)
					{
						return 0;
					}
					std::vector<wchar_t> buffer(len + 1);
					::SendMessageW(control, CB_GETLBTEXT, (WPARAM)index, (LPARAM)buffer.data());
					*/
					
					//char *buffer[10];
					//int index = SendMessage(hWndList7, CB_GETCURSEL, (WORD)0, 0L);
					//SendMessage(hWndList7, CB_GETLBTEXT, (WPARAM)index, (LPARAM)buffer);
					
					/*
					char buf[10];
					HWND hCombo = GetDlgItem(hwnd, IDC_MAIN_BUTTON);
					nIndex =::SendMessage(hCombo,CB_GETCURSEL,0,0);

					GetDlgItemText(hWndList7, nIndex, buf, 9);
					MessageBox(NULL, buf, NULL, MB_OK);
					*/
					
					//EnableWindow(hWndButton, true);
					break;
				}
			}


			switch(LOWORD(wParam))
			{
			case IDC_MAIN_BUTTON:
				{
					//EXECUTE BUTTON
					//length = SendMessage(hWndList1, LB_GETTEXTLEN, NULL, NULL);
					//SendMessage(hWndList7, LB_GETTEXT, (LPARAM)index, (LPARAM)buffer);
					//SendMessage(hWndList6, LB_ADDSTRING, NULL, (LPARAM)buffer);
					//SendMessage(hWndList1, LB_DELETESTRING, NULL, NULL);
					//SendMessage(hWndList1, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));
					//MessageBox(NULL, buffer, "INJECT ALERT", MB_OK);
					
					/*
					//int i = 3;
					std::string str;
					LPTSTR ltest;
					str = std::to_string(list[index+1]);
					ltest = new TCHAR[str.size() + 1];
					strcpy(ltest, str.c_str());
					//MessageBox(NULL, ltest, "LAUNCH ALERT", MB_OK);
					*/
										
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//LAUNCH EXE
					HANDLE htest;
					STARTUPINFO si;
					PROCESS_INFORMATION pi;

					for(int ii = 0; ii < test; ii++)
					{
						//LIMIT TO JUST BOX ONLY
						//MessageBox(NULL, mySVG[svgcounter][ii].svgChar, "TEST EXE", MB_OK);
						//char strg[100]; //= {(char)mySVG[svgcounter][ii].svgChar};
						strcpy(strg, mySVG[svgcounter][ii].svgChar);
						//char *strp;
						strp = strtok(strg, " ,.-_");

						if(strcmp(strp, "Box") == 0)
						{
							strp = strtok(NULL, " ,.-_");
							//MessageBox(NULL, strp, "LAUNCH ALERT", MB_OK);
							
							ZeroMemory(&si, sizeof(si));
							si.cb = sizeof(si);
							ZeroMemory(&pi, sizeof(pi));
							//Start the child process.
							if(!CreateProcess(NULL,     // No module name (use command line)
								//"directxtutorial1.exe", // Command line
									//"WoW.exe",
										EXEpath,
										NULL,                   // Process handle not inheritable
										NULL,                   // Thread handle not inheritable
										FALSE,                  // Set handle inheritance to FALSE
										0,                      // No creation flags
										NULL,                   // Use parent's environment block
										NULL,                   // Use parent's starting directory 
										&si,                    // Pointer to STARTUPINFO structure
										&pi))                   // Pointer to PROCESS_INFORMATION structure
							{
								//printf("CreateProcess failed (%d).\n", GetLastError());
								//return;
							}
							//printf("TEST: %d\n", pi.dwProcessId);
							htest = pi.hProcess;
							if(WaitForInputIdle(htest, 10000))
							{
								//EnumWindowsProc(NULL, (LPARAM)pi.dwProcessId);
								//EnumWindowsProc(NULL, (LPARAM)pi.dwProcessId);
								//EnumWindows(enumWindowCallback, NULL);
								//lpEnumFunc(cmdWnd, cmdProcess);
							}
							//_getch();

							EnumWindows(enumWindowCallback, pi.dwProcessId);
							
							Sleep(2000);

							if(ii == 1)
							{
								firstWindow = externHWND[ii];
							}

							int adjustedW = mySVG[svgcounter][ii].width - borderWidth;
							int adjustedH = mySVG[svgcounter][ii].height - borderHeight;


							SetWindowPos(externHWND[ii], 0, mySVG[svgcounter][ii].x, mySVG[svgcounter][ii].y,
								mySVG[svgcounter][ii].width, mySVG[svgcounter][ii].height, 0); //SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE

							
							if(*DLLpath == '\0')
							{
								//MessageBox(NULL, "EMPTY", "DLL Injector", MB_OK);
							}
							else
							{
								//MessageBox(NULL, "GOT SOMETHING", "DLL Injector", MB_OK);
								//INJECT DLL HERE
								DWORD pID = pi.dwProcessId;//list[index+1]; //= GetTargetThreadIDFromProcName("directxtutorial1.exe"); //Retrieve process ID
								//Get the dll's full path name
								char buf[MAX_PATH] = {0};
								//GetFullPathName("test.dll", MAX_PATH, buf, NULL);
								GetFullPathName(DLLpath, MAX_PATH, buf, NULL);
								//printf(buf);
								//printf("\n");
								//Inject our main dll
								if(!Inject(pID, buf))
								{
									//printf("DLL Not Loaded!");
									//MessageBox(NULL, "DLL Not Loaded!", "DLL Injector", MB_OK);
								}
								//else
								//{
									//printf("DLL Loaded!");
									//MessageBox(NULL, "DLL Loaded!", "DLL Injector", MB_OK);
								//}
							}

							//INPUT LOGIN KEYS////////////////////////////////////////////////////////////////////////////

							//WAIT FOR PROGRAM TO LOAD
							Sleep(1000);
							
							//printf("USERN: %d - %s\n", a, cTEXTprint[a*2+0]);
							//printf("PASSW: %d - %s\n", a, cTEXTprint[a*2+1]);
							//TCHAR bowels = cTEXTprint[(seekcounter-1)*2+0];
							

							convertVKEY(cTEXTprint[(seekcounter-1)*2+0]);
							convertVKEY(cTEXTprint[(seekcounter-1)*2+1]);

							Sleep(100);
							printSendkey(cTEXTprint[(seekcounter-1)*2+0]);
							printSendkey(cTEXTprint[(seekcounter-1)*2+1]);

							//////////////////////////////////////////////////////////////////////////////////////////////

							
							seekcounter++;
						}
					}

					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//CREATEPROCESSES
					//Wait until child process exits.
					//WaitForSingleObject(pi.hProcess, INFINITE);
					//Close process and thread handles.
					//CloseHandle(pi.hProcess);
					//CloseHandle(pi.hThread);
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//DESELECT COMBOBOX
					//SendMessage(hWndList7, LB_SETCURSEL, -1, MAKELPARAM(-1,0));//SendMessage(hWndList7, CB_SETCURSEL, -1, MAKELPARAM(-1,0));
					//EnableWindow(hWndButton, false);//DISABLE BUTTON
					
					
					SetForegroundWindow(firstWindow);
					SetWindowPos(firstWindow, 0, mySVG[svgcounter][test-1].x, mySVG[svgcounter][test-1].y,
								mySVG[svgcounter][test-1].width, mySVG[svgcounter][test-1].height, 0); //SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE

					//CLOCK REFRESH
					//SetTimer(hWnd, TIMER1, 3000, NULL);
					SetTimer(hWnd, TIMER1, 100, NULL);
					//break;
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
			}

			if(LOWORD(wParam) == 1)
			{
				//LOAD AND/OR REFRESH
				//SendMessage(hWndList1, LB_ADDSTRING, NULL, (LPARAM)buffer);
				SendMessage(hWndList1, LB_DELETESTRING, NULL, NULL);
				SendMessage(hWndList1, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));

				//Beep(40, 50);
				FilePathDirectory(wParam, hWndList1);

				SendMessage(hWndList1, LB_GETTEXT, NULL, (LPARAM)DLLpath);
				//MessageBox(NULL, DLLpath, "TEST DLL", MB_OK);
			}

			if(LOWORD(wParam) == 2)
			{
				//LOAD AND/OR REFRESH
				//SendMessage(hWndList2, LB_ADDSTRING, NULL, (LPARAM)buffer);
				SendMessage(hWndList2, LB_DELETESTRING, NULL, NULL);
				SendMessage(hWndList2, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));

				//Beep(40, 50);
				FilePathDirectory(wParam, hWndList2);

				SendMessage(hWndList2, LB_GETTEXT, NULL, (LPARAM)SVGXMLpath);
				//MessageBox(NULL, SVGXMLpath, "TEST SVGXML", MB_OK);
				
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//LOADXML
				//if(argc != 2){
				//printf("\nInvalid argument\n");
				//return(1);}
				
				//Macro to check API for match with the DLL we are using
				//LIBXML_TEST_VERSION
				//FILE * pFile;
				//pFile = fopen("dummy.dae","r");

				const char*fname = SVGXMLpath;//"MultiboxTOP.svg";
				//doc = htmlReadFile(argv[1], NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
				doc = htmlReadFile(fname, NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
				if (doc == NULL)
				{
					fprintf(stderr, "Document not parsed successfully.\n");
					return 0;
				}
				roo_element = xmlDocGetRootElement(doc);
				if(roo_element == NULL)
				{
					fprintf(stderr, "empty document\n");
					xmlFreeDoc(doc);
					return 0;
				}
				printf("Root Node is %s\n", roo_element->name);
				traverse_dom_trees(roo_element);
				
				//printf("\n\n\n\n\n\n\nEXTRAS!\n");
				for(int i = 0; i < test; i++)
				{
					char s[16];
					char*svgChar;
					//char*ptr2 = s;
					
					svgChar = const_cast<char*>(mySVG[0][i].svgChar);//str.c_str());
					//printf("TESTSTR: %s\n", mySVG[0][i].svgChar);
					SendMessage(hWndList7, LB_ADDSTRING, NULL, (LPARAM)(svgChar));//(LPARAM)szProcessName
					
					//printf("TESTX: %d\n", mySVG[0][i].x);
					//svgXchar = const_cast<char*>(mySVG[0][i].x);
					
					//int svgXchar = mySVG[0][i].x;
					//const char* c = (char*)i;
					char bufferX[16], bufferY[16], bufferW[16], bufferH[16];
					
					int svgXchar = mySVG[0][i].x;
					sprintf(bufferX,"%d",svgXchar);
					const char* strX = bufferX;
					//SendMessage(hWndList7, LB_ADDSTRING, NULL, (LPARAM)strX);//(LPARAM)szProcessName
					
					int svgYchar = mySVG[0][i].y;
					sprintf(bufferY,"%d",svgYchar);
					const char* strY = bufferY;
					//SendMessage(hWndList7, LB_ADDSTRING, NULL, (LPARAM)strY);//(LPARAM)szProcessName
					
					int svgWchar = mySVG[0][i].width;
					sprintf(bufferW,"%d",svgWchar);
					const char* strW = bufferW;
					//SendMessage(hWndList7, LB_ADDSTRING, NULL, (LPARAM)strW);//(LPARAM)szProcessName
					
					int svgHchar = mySVG[0][i].height;
					sprintf(bufferH,"%d",svgHchar);
					const char* strH = bufferH;
					//SendMessage(hWndList7, LB_ADDSTRING, NULL, (LPARAM)strH);//(LPARAM)szProcessName
				}

				LRESULT pos = test;
				wchar_t buf[4];
				wsprintfW(buf, L"%d", pos);
				SetWindowTextW(hWndList3, buf);//buf
			}
			
			if(LOWORD(wParam) == 3)
			{
				//LOAD AND/OR REFRESH
				//SendMessage(hWndList4, LB_ADDSTRING, NULL, (LPARAM)buffer);
				SendMessage(hWndList4, LB_DELETESTRING, NULL, NULL);
				SendMessage(hWndList4, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));

				//Beep(40, 50);
				FilePathDirectory(wParam, hWndList4);

				SendMessage(hWndList4, LB_GETTEXT, NULL, (LPARAM)EXEpath);
				//MessageBox(NULL, EXEpath, "TEST EXE", MB_OK);
			}

			if(LOWORD(wParam) == 4)
			{
				//Loginpath
				FilePathDirectory(wParam, hWndList5);
				SendMessage(hWndList5, LB_GETTEXT, NULL, (LPARAM)Loginpath);
				//MessageBox(NULL, Loginpath, "LOGIN CREDENTIALS", MB_OK);
				cReadTextFile(Loginpath);
			}
			
			if(LOWORD(wParam) == 5)
			{
				PostQuitMessage(0);
			}

			break;
		}
	
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


/*
if(LOWORD(wParam) == 2)
{
	//Beep(40, 50);
	FilePathDirectory(1, hWndList1);
}
*/