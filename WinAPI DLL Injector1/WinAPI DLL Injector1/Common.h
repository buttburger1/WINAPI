//ENUM PROCESS
//https://docs.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes
//https://stackoverflow.com/questions/185254/how-can-a-win32-process-get-the-pid-of-its-parent
//https://stackoverflow.com/questions/31147690/c-cant-get-process-id-windows

//https://stackoverflow.com/questions/865152/how-can-i-get-a-process-handle-by-its-name-in-c

//https://stackoverflow.com/questions/4102569/get-process-name-from-process-id-win32
//https://stackoverflow.com/questions/298257/ms-c-get-pid-of-current-process

//SCROLL BAR
//https://docs.microsoft.com/en-us/windows/win32/controls/create-scroll-bars
//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enablescrollbar
//https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/Controls/create-scroll-bars.md
//https://stackoverflow.com/questions/46736411/how-to-set-the-scroll-bar-for-a-listbox-at-runtime-properly
//https://stackoverflow.com/questions/16095394/winapi-scrollbar-handling
//https://stackoverflow.com/questions/46736411/how-to-set-the-scroll-bar-for-a-listbox-at-runtime-properly

//COMBO BOX
//https://stackoverflow.com/questions/39995382/win32-combobox-programmatically-select-highlight-string-from-the-list-withou
//https://docs.microsoft.com/en-us/windows/win32/controls/lb-setcursel?redirectedfrom=MSDN
//http://forums.codeguru.com/showthread.php?551581-deselect-text-in-combo-box

//STRING CONVERSIONS
//int to char, char* to char
//https://stackoverflow.com/questions/5050067/simple-int-to-char-conversion/39434550
//https://stackoverflow.com/questions/2074116/how-to-convert-from-char-to-char-in-c
//https://stackoverflow.com/questions/11268289/c-convert-char-into-char
//https://stackoverflow.com/questions/48689642/why-it-cannot-convert-char-to-char
//https://www.experts-exchange.com/questions/24610043/convert-int-to-const-char.html

//CHAR STRING CHECKS
//https://cboard.cprogramming.com/c-programming/59741-how-check-if-char*-empty-null.html
//https://stackoverflow.com/questions/50644885/how-can-i-check-if-a-char-is-empty
//https://stackoverflow.com/questions/1793867/best-way-to-check-if-a-character-array-is-empty
//https://stackoverflow.com/questions/7970617/how-can-i-check-if-char-variable-points-to-empty-string

//MERGE TWO STRINGS
//https://stackoverflow.com/questions/18468229/concatenate-two-char-strings-in-a-c-program/18468459
//https://skylinelimit.blogspot.com/2018/02/c-3.html

//STRUCT
//https://stackoverflow.com/questions/19323507/declare-struct-in-header-and-use-in-multiple-sources
//https://cboard.cprogramming.com/c-programming/128355-intellisense-declaration-incompatible.html
//https://stackoverflow.com/questions/33111509/declaration-is-incompatible
//https://stackoverflow.com/questions/3041797/how-to-use-a-defined-struct-from-another-source-file
//https://stackoverflow.com/questions/35320522/how-to-use-a-struct-from-another-file

//Get selected item in dropdown Win32
//https://stackoverflow.com/questions/52734970/get-selected-item-in-dropdown-win32

//MORE
//https://cboard.cprogramming.com/windows-programming/89505-get-current-selection-combobox.html
//https://forums.codeguru.com/showthread.php?411899-RESOLVED-Getting-the-Combo-Box-selected-item
//https://stackoverflow.com/questions/739095/win32-lb-gettext-returns-garbage
//https://stackoverflow.com/questions/16879669/c-win32-lb-gettext-only-returns-one-character
//http://www.cplusplus.com/doc/tutorial/ntcs/
//https://stackoverflow.com/questions/49344665/disabling-a-combobox-item-in-win32-api
//https://stackoverflow.com/questions/56360679/get-hwnd-of-a-window-i-clicked-on


#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Shlwapi.lib")
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <conio.h>
#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ)

#define IDC_MAIN_BUTTON 101 //Button identifier
#define TIMER1 1001
#define TIMER2 1002

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <conio.h>

#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")


/*
#ifndef NOMINMAX
#define NOMINMAX
#endif
*/


//#pragma comment(lib,"libxml2.lib")
//#pragma comment(lib,"iconv.lib")
//#define LIBXML_STATIC

#pragma comment(lib,"libxml2-static.lib")
#pragma comment(lib,"libz-static.lib")
#pragma comment(lib,"libiconv-static.lib")
#pragma comment(lib, "WS2_32.lib")


#include <libxml/HTMLparser.h>
//#include <libxml/xmlreader.h>
//#include <libxml/parser.h>
//#include <libxml/tree.h>
//#include <libxml/encoding.h>
//#include <libxml/xmlwriter.h>


#include <string.h>

#include <string>
#include <vector>
#include <iostream>
using namespace std;

void FilePathDirectory(int counter, HWND hWnd);
void PrintProcessNameAndID(DWORD processID, HWND hWnd);

BOOL Inject(DWORD pID, const char*DLL_NAME);
DWORD GetTargetThreadIDFromProcName(const char*ProcName);

void traverse_dom_trees(xmlNode*a_node);

typedef struct //struct movies_t
{
	const char * svgChar;

	int x;
	int y;
	int width;
	int height;
	
}mySVGstruct;//[10][30];

extern mySVGstruct mySVG[10][30]; //*pGraph_obj;

//BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam);
BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam);

void convertVKEY(char* key);
void printSendkey(char* buffer);

void cReadTextFile(char*filepathdestination);




/*
typedef struct 
{
	const u16 *id;
	int x,y;
	u16 w, h;
}GRAPH_OBJ;

extern GRAPH_OBJ graph_obj, *pGraph_obj; 
*/


/*
	//case CBN_SELCHANGE: //LBN_SELCHANGE
	HWND const control = (HWND)lParam;
	int index = SendMessage(control, LB_GETCURSEL, wParam, lParam);
	if (index == CB_ERR)
	{
		return 0;
	}
					
	//int i = 3;
	std::string str;
	LPTSTR long_string;
	
	str = std::to_string(index);
	long_string = new TCHAR[str.size() + 1];
	strcpy(long_string, str.c_str());
					
	MessageBox(NULL, long_string, "AAA", MB_OK);
*/


/*
					
//int len = strlen(buffer);
//char PID[100];
//for(int i = 0; i < len; i++)

*/




