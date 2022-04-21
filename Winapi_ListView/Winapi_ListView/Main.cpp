//REFERENCES
//https://docs.microsoft.com/en-us/windows/win32/controls/list-view-window-styles?redirectedfrom=MSDN
//https://stackoverflow.com/questions/23859399/c-winapi-listview-sort
//https://www.codeproject.com/Articles/2890/Using-ListView-control-under-Win32-API
//https://stackoverflow.com/questions/22879397/sorting-tables-with-listview
//https://stackoverflow.com/questions/57862412/winapi-how-to-implement-listview-sorting

//EXTRAS
//https://docs.microsoft.com/en-us/windows/win32/controls/create-a-list-view-control
//https://stackoverflow.com/questions/3910092/single-select-win32-listview-common-controls



#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")

struct _LV_ITEM {
	UINT   mask;        // attributes of this data structure
	int    iItem;       // index of the item to which this structure refers
	int    iSubItem;    // index of the subitem to which this structure refers
	UINT   state;       // Specifies the current state of the item
	UINT   stateMask;   // Specifies the bits of the state member that are valid.
	LPTSTR  pszText;    // Pointer to a null-terminated string
                        // that contains the item text
	int    cchTextMax;  // Size of the buffer pointed to by the pszText member
	int    iImage;      // index of the list view item's icon
	LPARAM lParam;      // 32-bit value to associate with item
} LV_IT;

struct _LV_COLUMN {
	UINT mask;       // which members of this structure contain valid information
	int fmt;         // alignment of the column heading and the subitem text
	int cx;          // Specifies the width, in pixels, of the column.
	LPTSTR pszText;  // Pointer to a null-terminated string
                     // that contains the column heading
	int cchTextMax;  // Specifies the size, in characters, of the buffer
	int iSubItem;    // index of subitem
} LV_COL;


typedef struct
{
    HWND hlist;
    int  iSubItem;
    BOOL bSortAscending;
}t_data;



HWND ListView;
HWND hwnd;
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	MSG messages;
	WNDCLASSEX wincl = { 0 };
	
	wincl.lpszClassName = "Testtttt";
	wincl.lpfnWndProc = WindowProc;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof(WNDCLASSEX);
	
	wincl.hIcon = 0;
	wincl.hIconSm = 0;
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0,0,0));// COLOR_BACKGROUND;
	wincl.hInstance = GetModuleHandle(NULL);
	
	RegisterClassEx(&wincl);
	
	hwnd = CreateWindowEx(
		0,
		wincl.lpszClassName,
		"Test",
		WS_SYSMENU | WS_EX_STATICEDGE | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL);
	
	RECT rec;
	GetClientRect(hwnd, &rec);
	//SetWindowPos(ListView, 0, 0, 0, rec.right, rec.bottom - 25, 0);
	SetWindowPos(ListView, 0, 0, 0, rec.right, rec.bottom, 0);
	
	ShowWindow(hwnd, nCmdShow);
	
	while (GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
}

void AddListViewItem(char item, char *text)
{
	static int i;
	LVITEM lis;
	lis.mask = LVIF_TEXT /*| LVIF_PARAM*/;
	lis.pszText = (LPSTR)(text);
	lis.iItem = i;
	lis.iSubItem = item;
	lis.lParam = i;
	if (item==1)
		i++;
	if (item == 0)
		ListView_InsertItem(ListView, &lis);
	else
		SendMessage(ListView, LVM_SETITEM, 0, (LPARAM)&lis);
}

int CALLBACK myCompFunc(LPARAM lp1, LPARAM lp2, LPARAM sortParam)
{
	bool isAsc = (sortParam > 0);
	int column = abs(sortParam) - 1;
	

	/*
	switch (column)
	{
	case 0:
		if (isAsc) return parseDateStr(item1->pubdate) - parseDateStr(item2->pubdate);
		else return parseDateStr(item2->pubdate) - parseDateStr(item1->pubdate);
		break;
	
	case 1:
		if (isAsc) return strcasecmp(item1->title.c_str(), item2->title.c_str());
		else return strcasecmp(item2->title.c_str(), item1->title.c_str());
	
	case 2:
		if (isAsc) return strcasecmp(item1->author.c_str(), item2->author.c_str());
		else return strcasecmp(item2->author.c_str(), item1->author.c_str());
		break;
    }
	
	t_data *data = (t_data*)sortParam;
    wchar_t buf1[100], buf2[100];
    ListView_GetItemText(data->hlist, lp1, data->iSubItem, (LPSTR)buf1, _countof(buf1));
    ListView_GetItemText(data->hlist, lp2, data->iSubItem, (LPSTR)buf2, _countof(buf2));
    int res = wcscmp(buf1, buf2);
    return data->bSortAscending ? res >= 0 : res <= 0;

	*/
	
	t_data *data = (t_data*)sortParam;
    wchar_t buf1[100], buf2[100];
    ListView_GetItemText(hwnd, lp1, 0, (LPSTR)buf1, _countof(buf1));
    ListView_GetItemText(hwnd, lp2, 0, (LPSTR)buf2, _countof(buf2));
    int res = wcscmp(buf1, buf2);
    return 1 ? res >= 0 : res <= 0;
	

	char tmp[128];
	sprintf_s(tmp,sizeof tmp, "%d %d %d", lp1, lp2, column);
	//MessageBox(0, (LPCSTR)tmp, "myCompFunc", MB_OK);
	return 0;
}


void OnColumnClickEx(LPNMLISTVIEW pLVInfo)
{
    static int nSortColumn = 0;
    static BOOL bSortAscending = TRUE;
    if(pLVInfo->iSubItem != nSortColumn)
        bSortAscending = TRUE;
    else
        bSortAscending = !bSortAscending;
    nSortColumn = pLVInfo->iSubItem;

    t_data data;
    data.hlist = pLVInfo->hdr.hwndFrom;
    data.iSubItem = nSortColumn;
    data.bSortAscending = bSortAscending;
    ListView_SortItemsEx(pLVInfo->hdr.hwndFrom, myCompFunc, &data);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_NOTIFY)
    {
        LPNMHDR lpnmh = (LPNMHDR)lParam;
        if (lpnmh->idFrom == 8553)
        if (lpnmh->code == LVN_COLUMNCLICK)
        {
            NMLISTVIEW*    pListView = (NMLISTVIEW*)lParam;
            ListView_SortItems(ListView, myCompFunc, pListView->iSubItem);
        }
    }
    else if (message == WM_CREATE)
    {
        ListView = CreateWindow(WC_LISTVIEW, (LPCSTR)L"", (WS_CHILD | WS_VISIBLE | LVS_REPORT), 0, 0, 800, 600, hwnd, (HMENU)8553, GetModuleHandle(NULL), NULL);
        SendMessage(ListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT); // Set style

		//LVS_SORTASCENDING
		//LVS_SORTDESCENDING

		//Memset(&LvCol,0,sizeof(LvCol));                  // Zero Members
		//LV_COL.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;    // Type of mask
		//LV_COL.cx=0x28;                                   // width between each coloum
		//LV_COL.pszText="Item";                            // First Header Text
		//LV_COL.cx=0x42;                                   // width of column

		LV_COL.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;    // Type of mask
		LV_COL.cx=0x100;                                   // width between each coloum
		LV_COL.pszText="Item";                            // First Header Text
		LV_COL.cx=0x100;                                   // width of column

		SendMessage(ListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT); // Set style
		
		SendMessage(ListView,LVM_INSERTCOLUMN,0,(LPARAM)&LV_COL);
		LV_COL.pszText="Sub Item1";
		SendMessage(ListView,LVM_INSERTCOLUMN,1,(LPARAM)&LV_COL);
		LV_COL.pszText="Sub Item2";
		SendMessage(ListView,LVM_INSERTCOLUMN,2,(LPARAM)&LV_COL);
		LV_COL.pszText="Sub Item3";
		SendMessage(ListView,LVM_INSERTCOLUMN,3,(LPARAM)&LV_COL);
		LV_COL.pszText="Sub Item4";
		SendMessage(ListView,LVM_INSERTCOLUMN,4,(LPARAM)&LV_COL);
		LV_COL.pszText="Sub Item5";
		SendMessage(ListView,LVM_INSERTCOLUMN,5,(LPARAM)&LV_COL);
		LV_COL.pszText="Sub Item6";

		//memset(&LvItem,0,sizeof(LvItem)); // Zero struct's Members
		
		//Setting properties Of members:
		LV_IT.mask=LVIF_TEXT;   // Text Style
		LV_IT.cchTextMax = 256; // Max size of test
		LV_IT.iItem=0;          // choose item  
		LV_IT.iSubItem=0;       // Put in first coluom
		LV_IT.pszText="Item 0"; // Text to display (can be from a char variable) (Items)

		SendMessage(ListView,LVM_INSERTITEM,0,(LPARAM)&LV_IT); // Send info to the Listview

		char buffer [50];
		for(int i=1;i<=5;i++) // Add SubItems in a loop
		{
			LV_IT.iSubItem=i;
			sprintf(buffer,"SubItem %d",i);
			LV_IT.pszText=buffer;
			SendMessage(ListView,LVM_SETITEM,0,(LPARAM)&LV_IT); // Enter text to SubItems
		}

		LV_IT.mask=LVIF_TEXT;   // Text Style
		LV_IT.cchTextMax = 256; // Max size of test
		LV_IT.iItem=1;          // choose item  
		LV_IT.iSubItem=0;       // Put in first coluom
		LV_IT.pszText="Item 1"; // Text to display (can be from a char variable) (Items)

		SendMessage(ListView,LVM_INSERTITEM,1,(LPARAM)&LV_IT); // Send info to the Listview

		for(int i=1;i<=5;i++) // Add SubItems in a loop
		{
			LV_IT.iSubItem=i;
			sprintf(buffer,"SubItem %d",5*1+i);
			LV_IT.pszText=buffer;
			SendMessage(ListView,LVM_SETITEM,1,(LPARAM)&LV_IT); // Enter text to SubItems
		}

    }
    else if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    else
        return DefWindowProc(hwnd, message, wParam, lParam);
    return DefWindowProc(hwnd, message, wParam, lParam);
    return 0;
}


/*
LVCOLUMN listColumn = { 0 };
listColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
listColumn.pszText = "Column1";
listColumn.cx = 150;
listColumn.fmt = LVCFMT_LEFT;
ListView_InsertColumn(ListView, 0, &listColumn);
		
listColumn.pszText = "Column2";
listColumn.cx = 150;
listColumn.iSubItem = 1;
ListView_InsertColumn(ListView, 1, &listColumn);
{
	//AddListViewItem(0, "a");
	//AddListViewItem(1, "a 1");
			
	//AddListViewItem(0, "b");
	//AddListViewItem(1, "b 1");
			
	//AddListViewItem(0, "c");
	//AddListViewItem(1, "c 1");

	AddListViewItem(0, "c");
	AddListViewItem(0, "a");
	AddListViewItem(0, "d");
	AddListViewItem(0, "b");
			
	AddListViewItem(1, "d 1");	
	AddListViewItem(1, "b 1");	
	AddListViewItem(1, "c 1");			
	AddListViewItem(1, "a 1");
	}
*/