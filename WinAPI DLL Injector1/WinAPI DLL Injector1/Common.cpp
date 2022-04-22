#include "Common.h"

/*
extern struct movies_t
{
	const char * svgChar;

	int x;
	int y;
	int width;
	int height;
	
}mySVG[10][30];
*/

//GRAPH_OBJ graph_obj, *pGraph_obj;
mySVGstruct mySVG[10][30]; //*pGraph_obj;

extern HWND externHWND[100];
extern int width, height, cwidth, cheight, borderWidth, borderHeight;

char filename[10][MAX_PATH];
void FilePathDirectory(int counter, HWND hWnd)
{
	//char filename[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&filename[counter], sizeof(filename[counter]));
	ZeroMemory(&ofn,      sizeof(ofn));
	ofn.lStructSize  = sizeof(ofn);
	ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter  = _T("Any File\0*.*\0DLL Files\0*.dll\0SVG XML Files\0*.svg\0EXE Files\0*.exe\0Text Files\0*.txt\0");
	ofn.lpstrFile    = filename[counter];
	ofn.nMaxFile     = MAX_PATH;
	ofn.lpstrTitle   = _T("Select a File!");
	ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn))
	{
		//std::cout << "You chose the file \"" << filename[counter] << "\"\n";
		//MessageBox(NULL, filename[counter], "Note", MB_OK);
		
		SendMessage(hWnd, LB_ADDSTRING, NULL, (LPARAM)filename[counter]);

		/*
		if(counter == 1)
		{
			SendMessage(hWnd, LB_ADDSTRING, NULL, (LPARAM)filename[counter]);
		}
		*/
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above.
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE   : std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE  : std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION  : std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE  : std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE  : std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE  : std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE : std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE  : std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE     : std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK          : std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE      : std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE      : std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL  : std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME : std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE : std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default                    : std::cout << "You cancelled.\n";
		}
	}
}


void PrintProcessNameAndID(DWORD processID, HWND hWnd)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	//Get a handle to the process.
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	//Get the process name.
	if(NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;
		
		if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR));
		}
	}

	//LIST
	//int ii = 247593;
	//const char * s = "hello";
	TCHAR str[1000];
	sprintf(str, "%d ", processID);

	//processID
	TCHAR str1[100];
	TCHAR str2[100];
	strcpy(str1, str);
	strcpy(str2, szProcessName);
	strcat(str1, str2);

	/*
	char str1[16];
	char str2[16];
	strcpy(str1, "sssss");
	strcpy(str2, "kkkk");
	strcat(str1, str2);
	//printf("%s", str1);
	*/
	
	//Print the process name and identifier.
	//_tprintf(TEXT("%s (PID: %u)\n"), szProcessName, processID);
	SendMessage(hWnd, LB_ADDSTRING, NULL, (LPARAM)(str1));//(LPARAM)szProcessName
	//Release the handle to the process.
	CloseHandle(hProcess);
}


BOOL Inject(DWORD pID, const char*DLL_NAME)
{
	HANDLE Proc;
	HMODULE hLib;
	char buf[50] = {0};
	LPVOID RemoteString, LoadLibAddy;
	if(!pID)return false;
	
	Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if(!Proc)
	{
		//sprintf(buf, "OpenProcess() failed: %d", GetLastError());
		//MessageBox(NULL, buf, "OpenProcess error", MB_OK);
		//printf(buf);
		return false;
	}
	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	//Allocate space in the process for our DLL
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	// Write the string name of our DLL in the memory allocated
	WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, strlen(DLL_NAME), NULL);
	//Load our DLL
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);
	CloseHandle(Proc);
	return true;
}


DWORD GetTargetThreadIDFromProcName(const char*ProcName)
{
	PROCESSENTRY32 pe;
	HANDLE thSnapShot;
	BOOL retval, ProcFound = false;
	thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(thSnapShot == INVALID_HANDLE_VALUE)
	{
		//MessageBox(NULL, "Error: Unable to create toolhelp snapshot!", "2MLoader", MB_OK);
		printf("Error: Unable to create toolhelp snapshot!");
		return false;
	}
	pe.dwSize = sizeof(PROCESSENTRY32);
	retval = Process32First(thSnapShot, &pe);
	while(retval)
	{
		if(StrStrI(pe.szExeFile, ProcName))
		{
			return pe.th32ProcessID;
		}
		retval = Process32Next(thSnapShot, &pe);
	}
	return 0;
}


/*
int main()
{
	//Get the list of process identifiers.
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	
	if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}
	//Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);
	//Print the name and process identifier for each process.
	for(i = 0; i < cProcesses; i++)
	{
		if(aProcesses[i] != 0)
		{
			PrintProcessNameAndID(aProcesses[i]);
		}
	}
	//return 0;
}
*/



struct xmlVectorArray
{
	float x, y, z;
};

//bool verticesfound = 0, indicesfound = 0;



//PRE-DEFINITIONS
extern int newarraytest;// = 0;
extern int svgcounter;// = -1;
//int rectcounter = 0;
extern int test;// = 0;
//const char * svgChar[4] = { "Blue", "Red", "Orange", "Yellow" };
//const char * svgChar[100][1000];


void traverse_dom_trees(xmlNode*a_node)
{
	xmlNode*cur_node = NULL;
	if(NULL == a_node)
	{
		//printf("Invalid argument a_node %p\n", a_node);
		return;
	}

	for(cur_node = a_node; cur_node; cur_node = cur_node->next)
	{
		if(cur_node->type == XML_ELEMENT_NODE)
		{
			/* Check for if current node should be exclude or not */
			printf("\nEleNode type: %s\n", cur_node->name);
						
			if(strcmp((char*)cur_node->name, "svg") == 0)
			{
				svgcounter++;
				//printf("SVG: %d\n", svgcounter);
				//printf("Test: %d\n", test);
				
				mySVG[svgcounter][test].svgChar = "";
				mySVG[svgcounter][test].x = 0;
				mySVG[svgcounter][test].y = 0;
				mySVG[svgcounter][test].width = 0;
				mySVG[svgcounter][test].height = 0;

				/*
				printf("X: %d Y: %d W: %d H: %d\n",
				mySVG[svgcounter][test].x,
				mySVG[svgcounter][test].y,
				mySVG[svgcounter][test].width,
				mySVG[svgcounter][test].height);
				*/
				test++;
			}

			if(strcmp((char*)cur_node->name, "rect") == 0)
			{
				/*
				//rectcounter++;
				printf("RECT: %d\n", rectcounter);
				printf("Test: %d\n", test);
				//mySVG[svgcounter][rectcounter].svgChar[test] = "";
				mySVG[svgcounter][rectcounter].x[test] = 0;
				mySVG[svgcounter][rectcounter].y[test] = 0;
				mySVG[svgcounter][rectcounter].width[test] = 0;
				mySVG[svgcounter][rectcounter].height[test] = 0;
				
				printf("X: %d Y: %d W: %d H: %d\n",
				mySVG[svgcounter][rectcounter].x[test],
				mySVG[svgcounter][rectcounter].y[test],
				mySVG[svgcounter][rectcounter].width[test],
				mySVG[svgcounter][rectcounter].height[test]);
				*/

				//printf("SVG: %d\n", svgcounter);
				//printf("Test: %d\n", test);

				mySVG[svgcounter][test].svgChar = "";
				mySVG[svgcounter][test].x = 0;
				mySVG[svgcounter][test].y = 0;
				mySVG[svgcounter][test].width = 0;
				mySVG[svgcounter][test].height = 0;

				/*
				printf("X: %d Y: %d W: %d H: %d\n",
				mySVG[svgcounter][test].x,
				mySVG[svgcounter][test].y,
				mySVG[svgcounter][test].width,
				mySVG[svgcounter][test].height);
				*/
				test++;
			}
			
			//printf("TZZZ: %d\n", test);
			
			xmlAttr* attribute = cur_node->properties;
			while(attribute)
			{
				//xmlChar* value = xmlNodeListGetString(cur_node->doc, attribute->children, 1);
				printf("EleAttr: %s - ContentSTR: %s\n", attribute->name, (char*)attribute->children->content);
				//if(strcmp((char*)attribute->name, "id") == 0 ||
				if(strcmp((char*)attribute->name, "id") == 0)
				{
					mySVG[svgcounter][test-1].svgChar = (char*)attribute->children->content;
					printf("SVG: %s\n", mySVG[svgcounter][test-1].svgChar);
				}

				if(strcmp((char*)attribute->name, "x") == 0)
				{
					newarraytest = atoi((char*)attribute->children->content);
					mySVG[svgcounter][test-1].x = newarraytest;
					printf("CHARtoINT: %d - TEST: %d\n", newarraytest, test);
				}
				if(strcmp((char*)attribute->name, "y") == 0)
				{
					newarraytest = atoi((char*)attribute->children->content);
					mySVG[svgcounter][test-1].y = newarraytest;
					printf("CHARtoINT: %d - TEST: %d\n", newarraytest, test);
				}
				if(strcmp((char*)attribute->name, "width") == 0)
				{
					newarraytest = atoi((char*)attribute->children->content);
					mySVG[svgcounter][test-1].width = newarraytest;
					printf("CHARtoINT: %d - TEST: %d\n", newarraytest, test);
				}
				if(strcmp((char*)attribute->name, "height") == 0)
				{
					newarraytest = atoi((char*)attribute->children->content);
					mySVG[svgcounter][test-1].height = newarraytest;
					printf("CHARtoINT: %d - TEST: %d\n", newarraytest, test);
				}
				//UNUSED
				/*
				{
					//if(strcmp((char*)attribute->children->content, "Cube-mesh-positions-array") == 0)
					//if(strcmp((char*)cur_node->name, "p") == 0)
					///////////////////////////////////////////////////////////////////////////////////////////////////////////
					newarraytest = atoi((char*)attribute->children->content);
					printf("CHARtoINT: %d - TEST: %d\n", newarraytest, test);
					
					mySVG[svgcounter][test].svgChar = (char*)attribute->children->content;
					
					//char* myName = (char*)attribute->children->content;
					printf("AAA: %s\n", mySVG[svgcounter][test].svgChar);
					printf("PASS: %s\n", (char*)attribute->name);
					//test++;
				}
				*/
				//xmlFree(value);//do something with value
				attribute = attribute->next;
			}
			
		}
		
		if(cur_node->type == XML_TEXT_NODE)
		{
			/* Process here text node, It is available in cpStr :TODO: */
			char *newChar;
			char *stringarray;

			int *intarray;
			float *floatarray;

			int slen = strlen((char*)cur_node->content);
			printf("TxtNode Content: %s - Content Length %d\n", (char*)cur_node->content, slen);
			
			xmlVectorArray *xmlVec;
			//int size = 10;
			xmlVec = new xmlVectorArray[newarraytest];
			//xmlVec[0].x = 5;


			/*
			if(indicesfound == 1)
			{
				printf("INDICES START HERE!\n");
				indicesfound = 0;
			}
						
			if(newarraytest > 0 || indicesfound == 1)
			{
				int lastLoop = 0;
				int stuff = 0;
				char testarray[1000];

				intarray = new int[slen];
				floatarray = new float[slen];
				
				for(int i = 0; i <= slen; i++)
				{
					testarray[i] = (char)cur_node->content[i];
					//printf("%c", testarray[i]);
					//printf("%c\n", (char*)cur_node->content[i]);
					if((int)cur_node->content[i] == 32 || (char)cur_node->content[i] == '\0')
					{
						printf("STUFF: %d SLEN: %d / %d\n", stuff, i, slen);
						if(verticesfound == 1)
						{
							int diff = i - lastLoop +1;
							newChar = new char[diff];
							stringarray = new char[diff];
							
							for(int ii = 1; lastLoop <= i; ii++ && lastLoop++)
							{
								//printf("LOOP %d - %d - %d\n", lastLoop, i, diff);
								newChar[ii] = testarray[lastLoop];
								//printf("%c", newChar[ii]);
							}

							for(int iii = -1; iii < diff; iii++)
							{
								stringarray[iii] = testarray[lastLoop-diff+iii];
								//printf("STRINGARRAY: %c\n", stringarray[iii]);
							}
							//printf("STRING RESULT: %s\n", stringarray);
							
							floatarray[stuff] = atof((char*)stringarray);
							printf("FLOATARRAY: %.7f\n", floatarray[stuff]);

							intarray[stuff] = atoi((char*)stringarray);
							printf("INTARRAY: %d\n", intarray[stuff]);
						}
						
						stuff++;
						_getch();
					}
				}
				//if(verticesfound == 1)for(int a = 0; a < 24; a++)printf("a: %.7f\n", morearray[a]);
				if(indicesfound == 1)indicesfound = 0;
			}
			*/
		}

		///////////////////////////////////////////////////

		traverse_dom_trees(cur_node->children);
	}
}


/*
int main()//int argc, char**argv)
{
	htmlDocPtr doc;
	xmlNode *roo_element = NULL;
	
	//if(argc != 2){
		//printf("\nInvalid argument\n");
		//return(1);}
	
	//Macro to check API for match with the DLL we are using
	//LIBXML_TEST_VERSION

	//FILE * pFile;
	//pFile = fopen("dummy.dae","r");

	const char*fname = "MultiboxTOP.svg";
	//doc = htmlReadFile(argv[1], NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	doc = htmlReadFile(fname, NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	if (doc == NULL)
	{
		fprintf(stderr, "Document not parsed successfully.\n");
		return 0;
	}
	roo_element = xmlDocGetRootElement(doc);
	if (roo_element == NULL)
    {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return 0;
    }
	printf("Root Node is %s\n", roo_element->name);
	traverse_dom_trees(roo_element);
	

	printf("\n\n\n\n\n\n\nEXTRAS!\n");
	for(int i = 0; i < test; i++)
	{
		printf("TESTSTR: %s\n", mySVG[0][i].svgChar);
		printf("TESTX: %d\n", mySVG[0][i].x);
		printf("TESTY: %d\n", mySVG[0][i].y);
		printf("TESTW: %d\n", mySVG[0][i].width);
		printf("TESTH: %d\n", mySVG[0][i].height);
	}
	
	//FREE EVERYTHING UP & CLOSE
    xmlFreeDoc(doc);   //free document
    xmlCleanupParser();//free globals
		
	getchar();
    return 0;
}

*/


extern char strg;
extern char *strp;

BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam)
{
	int length = GetWindowTextLength(hWnd);
	char* buffer = new char[length + 1];
	GetWindowText(hWnd, buffer, length + 1);
	std::string windowTitle(buffer);
	//printf("TITLEBUFFER: %s\n", buffer);
	
	DWORD dwPID;
	GetWindowThreadProcessId(hWnd, &dwPID);
	
	//List visible windows with a non-empty title
	if(IsWindowVisible(hWnd) && length != 0)
	{
		//std::cout << hWnd << ":  " << windowTitle << std::endl;
		//printf("dwPID: %d TESTPARAM: %d\n", dwPID, lparam);
		
		if(dwPID == lparam)
		{
			char bff[256];
			GetWindowText(hWnd, bff, sizeof(bff));
			//printf("WINDOWTEXT: %s\n", bff);
			//MessageBox(NULL, bff, "TESTICLES", MB_OK);

			char titlebuffer[256] = "WoW_";
			strcat(titlebuffer, strp);

			int counter = atoi(strp);
			//MessageBox(NULL, titlebuffer, "TESTICLES", MB_OK);

			//SetWindowText(hWnd, "Nutsack");
			SetWindowText(hWnd, titlebuffer);
			GetWindowText(hWnd,bff,sizeof(bff));
			//printf("WINDOWTEXT: %s\n", bff);



			RECT windowRect;
			if(GetWindowRect(hWnd, &windowRect))
			{
				width = windowRect.right - windowRect.left;
				height = windowRect.bottom - windowRect.top;
				//printf("WSIZE: W: %d H: %d\n", width, height);
			}

			RECT clientRect;
			if(GetClientRect(hWnd, &clientRect))
			{
				cwidth = clientRect.right - clientRect.left;
				cheight = clientRect.bottom - clientRect.top;
				//printf("CWSIZE: W: %d H: %d\n", cwidth, cheight);
			}

			borderWidth = ((windowRect.right - windowRect.left) - (clientRect.right -clientRect.left))/2;
			//printf("bWidth: %d\n", borderWidth);

			borderHeight = ((windowRect.bottom - windowRect.top) - (clientRect.bottom -clientRect.top))/2;
			//printf("bHeight: %d\n", borderHeight);

			externHWND[counter] = hWnd;
		}
	}
		
	//char bff[256];
	//int b;
	//GetWindowModuleFileName(hWnd, bff, b); //HWND hwnd, LPTSTR lpszFileName, UINT cchFileNameMax); //UINT
	//printf("svgChar: %s - %d\n", bff, b);
	return TRUE;
}

//BOOL SetWindowTextA(HWND hWnd, LPCSTR lpString);

/*
int main()//int argc, TCHAR *argv[])
{
	HANDLE htest;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	//Start the child process.
	if(!CreateProcess(NULL,     // No module name (use command line)
		//"directxtutorial1.exe", // Command line
			"WoW.exe",
		NULL,                   // Process handle not inheritable
		NULL,                   // Thread handle not inheritable
		FALSE,                  // Set handle inheritance to FALSE
		0,                      // No creation flags
		NULL,                   // Use parent's environment block
		NULL,                   // Use parent's starting directory 
		&si,                    // Pointer to STARTUPINFO structure
		&pi))                   // Pointer to PROCESS_INFORMATION structure
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		//return;
	}

	printf("TEST: %d\n", pi.dwProcessId);
	htest = pi.hProcess;
	if(WaitForInputIdle(htest, 5000))
	{
		//EnumWindowsProc(NULL, (LPARAM)pi.dwProcessId);
		//EnumWindowsProc(NULL, (LPARAM)pi.dwProcessId);
		//EnumWindows(enumWindowCallback, NULL);
		//lpEnumFunc(cmdWnd, cmdProcess);
	}

	//_getch();

	EnumWindows(enumWindowCallback, pi.dwProcessId);
	
	//Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);
	//Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	//getchar();
	return 0;
}
*/



//LOGIN CREDENTIALS GLOBALS
//#define MAXCHAR 1000
char cTEXTprint[100][1000];
void cReadTextFile(char*filepathdestination)
{
	int TEXTbuffertick = 0;
	char*cTEXTbuffer[100][1000] = {0};
	char TEXTstr[1000];
	char* filename = filepathdestination;//"test.txt";//"c:\\temp\\test.txt";
	//MessageBox(NULL, filepathdestination, "LOGIN CREDENTIALS", MB_OK);
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		//printf("Could not open file %s\n",filename);
		//return 1;
	}

	while(fgets(TEXTstr, 1000, fp) != NULL)//(fgets(str, MAXCHAR, fp) != NULL)
	{
		//printf("TXTSTRING: %s\n", TEXTstr);
		strncpy((char*)cTEXTbuffer[TEXTbuffertick], TEXTstr, strlen(TEXTstr));
		TEXTbuffertick++;
	}

	for(int a = 0; a < 10; a++)
	{
		strncpy(cTEXTprint[a*2+0], (char*)cTEXTbuffer[a*2+0], strlen((char*)cTEXTbuffer[a*2+0]));
		//printf("USERN: %d - %s\n", a, cTEXTprint[a*2+0]);
		strncpy(cTEXTprint[a*2+1], (char*)cTEXTbuffer[a*2+1], strlen((char*)cTEXTbuffer[a*2+1]));
		//printf("PASSW: %d - %s\n", a, cTEXTprint[a*2+1]);
	}

	fclose(fp);
}