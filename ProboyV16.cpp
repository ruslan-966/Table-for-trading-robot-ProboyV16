// ProboyV16.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "ProboyV16.h"
#include <string>                               // подключаем строки
#include <fstream>                              // подключаем файлы
#include <cctype>                               // для функции toupper


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hEdt1, hEdt2, hEdt3, hEdt4, hEdt5, hEdt6;
HWND hEdt7, hEdt8, hEdt9;
HWND hBtn;
HWND CheckBox;
HWND hStat, hStat1, hStat2, hStat3, hStat4;     // дескриптор окна с изменяемым текстом
TCHAR StrA[20];
std::wstring result, classcode, amnt, controlvalue;
std::wstring market, setmod, typesize, deltacandle;
std::wstring step_common, ordertype, demomode;
std::wstring account, seccode,clientcode, depoaccount;
std::wstring timeframe;
std::wstring name_file_param (TEXT("\\source_data_file.txt"));
std::wstring name_file_key(TEXT("\\key_file.txt"));
INT Len;
LPWSTR    glpCmdLine;
//char filename[] = "D:\\ProboyTest\\source_data_file.txt";
std::wstring path1, path2;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//*
// Функция создания фйла ключа
int fail_key_turn_on(std::wstring path)
{
    std::ofstream outf(path);
        // Если мы не можем открыть этот файл для записи данных,
    if (!outf)
    {
        // то выводим сообщение об ошибке и выполняем функцию exit()
        MessageBox(NULL, TEXT("key_file.txt could not be generated!"), TEXT("Message from fail_key_turn_on"), MB_OK);
        exit(1);
    }
    // Записываем в файл сообщение
    outf << "key_file is generated." << std::endl;
    return 0;
}
// Функция записи переменной в строку
LPWSTR CharToLPWSTR(LPCSTR char_string, int& l)
{
    LPWSTR res;
    l = 0;
    while (char_string[l++]);

    res = (LPWSTR)GlobalAlloc(GPTR, (l) * sizeof(WCHAR));
    MultiByteToWideChar(1251, 0, char_string, -1, res, l--);

    return res;
}
//*/
//функция перевода string -> wstring
std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

//функция перевода строчных букв в прописные в строке
std::string small2largeletters(std::string& str)
{
    int ix = 0;                               // индекс символов строки
    char character;
    int strlength = (int)str.length() + 1;
    //char buf[10];
    char* buf = new char[strlength];
    while (str[ix])                           // пока не конец строки
    {
        character = str[ix];
        buf[ix] = (char)toupper(character);  // преобразовать строчную букву в прописную
        ix++;                                   // инкремент индекса символов строки
    }
    buf[ix] = '\0';
    std::string r(buf);
    delete [] buf;
    return r;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)

{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    std::wstring path(lpCmdLine);           //строка закрывается при отладке
    //std::wstring path(L"D:\\ProboyTest"); //строка открывается при отладке 
    path1 = path + name_file_param;
    path2 = path + name_file_key;
    
    std::string s; // сюда будем класть считанные строки
    std::ifstream file(path1); // 
    if (!file)
    {
        // то выводим следующее сообщение об ошибке и выполняем функцию exit()
        MessageBox(NULL, TEXT("File with parameters cannot be opened for reading!"), TEXT("Message from wWinMain"), MB_OK);
        exit(1);
    }
    demomode = TEXT("NO");
    while (getline(file, s)) { // пока не достигнут конец файла класть очередную строку в переменную (s)
        s.erase(remove(s.begin(), s.end(), ' '), s.end());  //удалили все пробелы из строки
        std::size_t pos = s.find(":");          // position of ":" in string
        std::string s1 = s.substr(pos+1);       // get from ":" to the end of string
        std::wstring stemp = s2ws(s1);          //перевод std::string -> LPCWSTR
                
        if (s.find("classcode")==0)
        {
            classcode = stemp;
        }
        if (s.find("seccode") == 0)
        {
            seccode = stemp;
        }
        if (s.find("clientCode") == 0)
        {
            clientcode = stemp;
        }
        if (s.find("depoaccount") == 0)
        {
            depoaccount = stemp;
        }
        if (s.find("amnt") == 0)
        {
            amnt = stemp;
        }
        if (s.find("controlvalue") == 0)
        {
            controlvalue = stemp;
        }
        if (s.find("deltacandle") == 0)
        {
            deltacandle = stemp;
        }
        if (s.find("timeframe") == 0)
        {
            timeframe = stemp;
        }

        if (s.find("whatismarket") == 0)
        {
            market = stemp;
        }
        if (s.find("settlementmode") == 0)
        {
            setmod = stemp;
        }
        if (s.find("typesize") == 0)
        {
            typesize = stemp;
        }
        if (s.find("ordertype") == 0)
        {
            ordertype = stemp;
        }
        if (s.find("account") == 0)
        {
            account = stemp;
        }
    }

    file.close(); // обязательно закрываем файл что бы не повредить его

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROBOYV16, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROBOYV16));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROBOYV16));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROBOYV16);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 940/*CW_USEDEFAULT*/, 270, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   // Создаем и показываем поле редактирования --счёт ФОРТС
   hEdt1 = CreateWindow(L"edit", account.c_str(),
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 150, 99, 105, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt1, SW_SHOWNORMAL);
   // Создаем и показываем поле редактирования --Код клиента
   hEdt2 = CreateWindow(L"edit", clientcode.c_str(),
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 150, 124, 105, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt2, SW_SHOWNORMAL);
   // Создаем и показываем поле редактирования --Счёт Депо
   hEdt3 = CreateWindow(L"edit", depoaccount.c_str(),
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 150, 149, 105, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt3, SW_SHOWNORMAL);
   // Создаем и показываем поле редактирования --Количество лотов
   hEdt4 = CreateWindow(L"edit", amnt.c_str(),                                  
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 430, 99, 60, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt4, SW_SHOWNORMAL);
   // Создаем и показываем поле редактирования --Объем в лотах
   hEdt5 = CreateWindow(L"edit", controlvalue.c_str(),
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 638, 99, 71, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt5, SW_SHOWNORMAL);
   // Создаем и показываем поле редактирования --Высота свечи
   hEdt6 = CreateWindow(L"edit", deltacandle.c_str(),
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 430, 171, 60, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt6, SW_SHOWNORMAL);
   // Создаем и показываем поле редактирования --Код бумаги
   hEdt7 = CreateWindow(L"edit", seccode.c_str(),
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 430, 124, 60, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt7, SW_SHOWNORMAL);
   // Создаем и показываем поле редактирования --Код класса
   hEdt8 = CreateWindow(L"edit", classcode.c_str(),
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 430, 149, 60, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt8, SW_SHOWNORMAL);
   // Создаем и показываем поле редактирования --Интервал свечи
   hEdt9 = CreateWindow(L"edit", timeframe.c_str(),
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 670, 124, 39, 20,
       hWnd, 0, hInst, NULL);
   ShowWindow(hEdt9, SW_SHOWNORMAL);
   // Создаем и показываем поле текста для выбора рынка торговли
   if (market[0] == L'F' && market[1] == L'U' && market[2] == L'N')
   {
       hStat = CreateWindow(L"static", L"Фондовый рынок", WS_CHILD | WS_VISIBLE,
           110, 40, 135, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat, SW_SHOWNORMAL);
   }
   if (market[0] == L'F' && market[1]==L'U' && market[2] == L'T')
   {
       hStat = CreateWindow(L"static", L"Срочный рынок", WS_CHILD | WS_VISIBLE,
           110, 40, 135, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat, SW_SHOWNORMAL);
   }
   //Создаем и показываем поле текста для выбора режима расчётов
   int st1x = 360;
   int st1y = 40;
   if (setmod[0] == L'T' && setmod[1] == L'0')
   {
       hStat1 = CreateWindow(L"static", L"Режим T0", WS_CHILD | WS_VISIBLE,
           st1x, st1y, 69, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat1, SW_SHOWNORMAL);
   }
   if (setmod[0] == L'T' && setmod[1] == L'1')
   {
       hStat1 = CreateWindow(L"static", L"Режим T1", WS_CHILD | WS_VISIBLE,
           st1x, st1y, 69, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat1, SW_SHOWNORMAL);
   }
   if (setmod[0] == L'T' && setmod[1] == L'2')
   {
       hStat1 = CreateWindow(L"static", L"Режим T2", WS_CHILD | WS_VISIBLE,
           st1x, st1y, 69, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat1, SW_SHOWNORMAL);
   }
   //Создаем и показываем поле текста для выбора направления торговли
   int st2x = 540;
   int st2y = 40;
   if (typesize[0] == L'L' && typesize[1] == L'O')
   {
       hStat2 = CreateWindow(L"static", L"Режим Лонг", WS_CHILD | WS_VISIBLE,
           st2x, st2y, 101, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat2, SW_SHOWNORMAL);
   }
   if (typesize[0] == L'S' && typesize[1] == L'H')
   {
       hStat2 = CreateWindow(L"static", L"Режим Шорт", WS_CHILD | WS_VISIBLE,
           st2x, st2y, 101, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat2, SW_SHOWNORMAL);
   }
   if (typesize[0] == L'R' && typesize[1] == L'E')
   {
       hStat2 = CreateWindow(L"static", L"Режим Реверс", WS_CHILD | WS_VISIBLE,
           st2x, st2y, 101, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat2, SW_SHOWNORMAL);
   }
   //Создаем и показываем поле текста для выбора типа ордера (лимитный или по рынку)
   int st3x = 760;
   int st3y = 40;
   if (ordertype[0] == L'L' && ordertype[1] == L'I')
   {
       hStat3 = CreateWindow(L"static", L"Лимитный ордер", WS_CHILD | WS_VISIBLE,
           st3x, st3y, 118, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat3, SW_SHOWNORMAL);
   }
   if (ordertype[0] == L'M' && ordertype[1] == L'A')
   {
       hStat3 = CreateWindow(L"static", L"Рыночный ордер", WS_CHILD | WS_VISIBLE,
           st3x, st3y, 118, 16, hWnd, 0, hInst, NULL);
       ShowWindow(hStat3, SW_SHOWNORMAL);
   }
   //Создаем чекбокс и вываодим его
   CheckBox = CreateWindowEx(NULL, L"BUTTON", L"Демо режим",
       WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
       757, 100, 120, 30, hWnd, (HMENU)10001 /*NULL*/, GetModuleHandle(NULL), NULL);
       UINT t = SendMessage(CheckBox, BM_GETCHECK, 0, 0);
   // Создаем и показываем кнопку
   hBtn = CreateWindow(L"button", L"Сохранить",
       WS_CHILD | WS_VISIBLE | WS_BORDER,
       757, 140, 120, 30, hWnd, 0, hInst, NULL);
   ShowWindow(hBtn, SW_SHOWNORMAL);
   //создаем комбобокс Вид торговли
   int xpos = 550;           // Horizontal position of the window.
   int ypos = 60;            // Vertical position of the window.
   int nwidth = 91;          // Width of the window
   int nheight = 200;         // Height of the window
   HWND hwndParent = hWnd; // Handle to the parent window
   HWND hWndComboBox = CreateWindow(L"combobox" /*WC_COMBOBOX*/, TEXT(""),
       CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
       xpos, ypos, nwidth, nheight, hwndParent, NULL, hInst,
       NULL);
   //создаем комбобокс Выбор рынка для торговли
   int xpos1 = 125;            // Horizontal position of the window.
   int ypos1 = 60;            // Vertical position of the window.
   int nwidth1 = 120;          // Width of the window
   int nheight1 = 200;         // Height of the window
   HWND hwndParent1 = hWnd; // Handle to the parent window
   HWND hWndComboBox1 = CreateWindow(L"combobox" /*WC_COMBOBOX*/, TEXT(""),
       CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
       xpos1, ypos1, nwidth1, nheight1, hwndParent1, NULL, hInst,
       NULL);
   //создаем комбобокс Режим рассчётов
   int xpos2 = 370;           // Horizontal position of the window.
   int ypos2 = 60;            // Vertical position of the window.
   int nwidth2 = 59;          // Width of the window
   int nheight2 = 200;         // Height of the window
   HWND hwndParent2 = hWnd; // Handle to the parent window
   HWND hWndComboBox2 = CreateWindow(L"combobox" /*WC_COMBOBOX*/, TEXT(""),
       CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
       xpos2, ypos2, nwidth2, nheight2, hwndParent2, NULL, hInst,
       NULL);
   //создаем комбобокс Тип ордера (лимитный, рыночный)
   int xpos3 = 775;           // Horizontal position of the window.
   int ypos3 = 60;            // Vertical position of the window.
   int nwidth3 = 103;          // Width of the window
   int nheight3 = 200;         // Height of the window
   HWND hwndParent3 = hWnd; // Handle to the parent window
   HWND hWndComboBox3 = CreateWindow(L"combobox", TEXT(""),
       CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
       xpos3, ypos3, nwidth3, nheight3, hwndParent3, NULL, hInst,
       NULL);
   // load the combobox with item list.  
   // Send a CB_ADDSTRING message to load each item
   TCHAR Markets[2][9] =
   {
       TEXT("Срочный"), TEXT("Фондовый")
   };
   TCHAR A1[16];
   int  k1 = 0;
   memset(&A1, 0, sizeof(A1));
   for (k1 = 0; k1 <= 1; k1 += 1)
   {
       wcscpy_s(A1, sizeof(A1) / sizeof(TCHAR), (TCHAR*)Markets[k1]);
       // Add string to combobox.
       SendMessage(hWndComboBox1, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A1);
   }
   // Send the CB_SETCURSEL message to display an initial item 
   //  in the selection field  
   SendMessage(hWndComboBox1, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
   // load the combobox with item list.  
   // Send a CB_ADDSTRING message to load each item
   TCHAR TypeOfTrading[3][8] =
   {
       TEXT("Лонг"), TEXT("Шорт"), TEXT("Реверс")
   };
   TCHAR A[16];
   int  k = 0;
   memset(&A, 0, sizeof(A));
   for (k = 0; k <= 2; k += 1)
   {
       wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)TypeOfTrading[k]);
       // Add string to combobox.
       SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
   }
   // Send the CB_SETCURSEL message to display an initial item 
   //  in the selection field  
   SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
   // load the combobox with item list.  
   // Send a CB_ADDSTRING message to load each item
   TCHAR СalculationModes[3][3] =
   {
       TEXT("T0"), TEXT("T1"), TEXT("T2")
   };
   TCHAR A2[16];
   int  k2 = 0;
   memset(&A2, 0, sizeof(A2));
   for (k2 = 0; k2 <= 2; k2 += 1)
   {
       wcscpy_s(A2, sizeof(A2) / sizeof(TCHAR), (TCHAR*)СalculationModes[k2]);
       // Add string to combobox.
       SendMessage(hWndComboBox2, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A2);
   }
   // Send the CB_SETCURSEL message to display an initial item 
   //  in the selection field  
   SendMessage(hWndComboBox2, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
   // load the combobox with item list.  
   // Send a CB_ADDSTRING message to load each item
   TCHAR EntryMarkets[2][12] =
   {
       TEXT("На Лимитный"), TEXT("На Рыночный")
   };
   TCHAR A3[16];
   int  k3 = 0;
   memset(&A3, 0, sizeof(A3));
   for (k3 = 0; k3 <= 1; k3 += 1)
   {
       wcscpy_s(A3, sizeof(A3) / sizeof(TCHAR), (TCHAR*)EntryMarkets[k3]);
       // Add string to combobox.
       SendMessage(hWndComboBox3, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A3);
   }
   // Send the CB_SETCURSEL message to display an initial item 
   //  in the selection field  
   SendMessage(hWndComboBox3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        if (HIWORD(wParam) == CBN_SELCHANGE)
            // If the user makes a selection from the list:
            //   Send CB_GETCURSEL message to get the index of the selected list item.
            //   Send CB_GETLBTEXT message to get the item.
            //   Display the item in a messagebox.
        {
            LRESULT ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,   //int
                (WPARAM)0, (LPARAM)0);
            TCHAR  ListItem[256];
            (TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)ListItem);
            ListItem[255] = L'\0';
            //Если нажали что то из листингов
            if ((ListItem[0] == L'Ф') && (ListItem[1] == L'о'))
            {
                market = L"FUNDS";
                SetWindowText(hStat, L"Фондовый рынок");
            }
            if ((ListItem[0] == L'С') && (ListItem[1] == L'р'))
            {
                market = L"FUTURES";
                SetWindowText(hStat, L"Срочный рынок");
            }
            if ((ListItem[0] == L'T') && (ListItem[1] == L'0'))
            {
                setmod = L"T0";
                SetWindowText(hStat1, L"Режим T0");
            }
            if ((ListItem[0] == L'T') && (ListItem[1] == L'1'))
            {
                setmod = L"T1";
                SetWindowText(hStat1, L"Режим T1");
            }
            if ((ListItem[0] == L'T') && (ListItem[1] == L'2'))
            {
                setmod = L"T2";
                SetWindowText(hStat1, L"Режим T2");
            }

            if ((ListItem[0] == L'Л') && (ListItem[1] == L'о'))
            {
                typesize = L"LONG";
                SetWindowText(hStat2, L"Режим Лонг");
            }
            if ((ListItem[0] == L'Ш') && (ListItem[1] == L'о'))
            {
                typesize = L"SHORT";
                SetWindowText(hStat2, L"Режим Шорт");
            }
            if ((ListItem[0] == L'Р') && (ListItem[1] == L'е'))
            {
                typesize = L"REVERS";
                SetWindowText(hStat2, L"Режим Реверс");
            }
            if ((ListItem[3] == L'Л') && (ListItem[4] == L'и'))
            {
                ordertype = L"LIMIT";
                SetWindowText(hStat3, L"Лимитный ордер");
            }
            if ((ListItem[3] == L'Р') && (ListItem[4] == L'ы'))
            {
                ordertype = L"MARKET";
                SetWindowText(hStat3, L"Рыночный ордер");
            }
            
            if ((ListItem[0] == L'M') && (ListItem[1] == L'1') && ListItem[2] == '\0')
            {
                timeframe = L"1M";
                SetWindowText(hStat4, L"Интервал 1М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'2') && ListItem[2] == '\0')
            {
                timeframe = L"2M";
                SetWindowText(hStat4, L"Интервал 2М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'3') && ListItem[2] == '\0')
            {
                timeframe = L"3M";
                SetWindowText(hStat4, L"Интервал 3М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'4') && ListItem[2] == '\0')
            {
                timeframe = L"4M";
                SetWindowText(hStat4, L"Интервал 4М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'5') && ListItem[2] == '\0')
            {
                timeframe = L"5M";
                SetWindowText(hStat4, L"Интервал 5М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'6') && ListItem[2] == '\0')
            {
                timeframe = L"6M";
                SetWindowText(hStat4, L"Интервал 6М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'1') && ListItem[2] == '0')
            {
                timeframe = L"10M";
                SetWindowText(hStat4, L"Интервал 10М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'1') && ListItem[2] == '5')
            {
                timeframe = L"15M";
                SetWindowText(hStat4, L"Интервал 15М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'2') && ListItem[2] == '0')
            {
                timeframe = L"20M";
                SetWindowText(hStat4, L"Интервал 20М");
            }
            if ((ListItem[0] == L'M') && (ListItem[1] == L'3') && ListItem[2] == '0')
            {
                timeframe = L"30M";
                SetWindowText(hStat4, L"Интервал 30М");
            }

        }
        if (lParam == (LPARAM)hBtn)    // если нажали на кнопку
        {
            //опрашиваем все редактируемые поля
            Len = GetWindowText(hEdt1, StrA, 20);
            account = StrA;
            Len = GetWindowText(hEdt2, StrA, 20);
            clientcode = StrA;
            Len = GetWindowText(hEdt3, StrA, 20);
            depoaccount = StrA;
            Len = GetWindowText(hEdt4, StrA, 20);
            amnt = StrA;
            Len = GetWindowText(hEdt5, StrA, 20);
            controlvalue = StrA;
            Len = GetWindowText(hEdt6, StrA, 20);
            deltacandle = StrA;
            Len = GetWindowText(hEdt7, StrA, 20);
            seccode = StrA;
            Len = GetWindowText(hEdt8, StrA, 20);
            classcode = StrA;
            Len = GetWindowText(hEdt9, StrA, 20);
            timeframe = StrA;
            //сохраняем в файл собранные настройки
            std::ofstream out;          // поток для записи
            out.open(path1); // окрываем файл для записи
            if (out.is_open())
            {
                const std::string s(classcode.begin(), classcode.end());
                out << "classcode : " << s << std::endl;
                const std::string s1(seccode.begin(), seccode.end());
                out << "seccode : " << s1 << std::endl;
                const std::string s2(account.begin(), account.end());
                out << "account : " << s2 << std::endl;
                const std::string s3(clientcode.begin(), clientcode.end());
                out << "clientCode : " << s3 << std::endl;
                const std::string s4(depoaccount.begin(), depoaccount.end());
                out << "depoaccount : " << s4 << std::endl;
                const std::string s5(amnt.begin(), amnt.end());
                out << "amnt : " << s5 << std::endl;
                const std::string s6(timeframe.begin(), timeframe.end());
                out << "timeframe : " << s6 << std::endl;
                const std::string s7(controlvalue.begin(), controlvalue.end());
                out << "controlvalue : " << s7 << std::endl;
                const std::string s8(deltacandle.begin(), deltacandle.end());
                out << "deltacandle : " << s8 << std::endl;
                const std::string s9(ordertype.begin(), ordertype.end());
                out << "ordertype : " << s9 << std::endl;
                const std::string s10(typesize.begin(), typesize.end());
                out << "typesize : " << s10 << std::endl;
                const std::string s11(market.begin(), market.end());
                out << "whatismarket : " << s11 << std::endl;
                const std::string s12(demomode.begin(), demomode.end());
                out << "demomode : " << s12 << std::endl;
                const std::string s13(setmod.begin(), setmod.end());
                out << "settlementmode : " << s13 << std::endl;
            }
            //закрываем окно
            fail_key_turn_on(path2);
            PostQuitMessage(0);
        }
        int wmId = LOWORD(wParam);
        //разбираем чекбокс
        if (lParam == (LPARAM)CheckBox)    // если нажали на окошко в чекбоксе
        {
            // Получаем HWND нашего chechbox'а.
            HWND hwndCheck = GetDlgItem(hWnd, 10001);
            // Выясняем текущее состояние chechbox'а.
            LRESULT res = SendMessage(hwndCheck, BM_GETCHECK, 0, 0);
            // Если галочка стоит.
            if (res == BST_CHECKED)
            {
                demomode = TEXT("YES");
            }
            // Если галочка не стоит.
            if (res == BST_UNCHECKED)
            {
                demomode = TEXT("NO");
            }
        }
        
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
        break;
    case WM_PAINT:
        {
            // Obtain the window's client rectangle 
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // вывод текстовых сообщений
            TCHAR text[] = TEXT("Выбор рынка для торговли:");
            TextOut(hdc, 50, 20, text, ARRAYSIZE(text));
            TCHAR text1[] = TEXT("Режим рассчётов:");
            TextOut(hdc, 300, 20, text1, ARRAYSIZE(text1));
            TCHAR text2[] = TEXT("Вид торговли:              ");
            TextOut(hdc, 480, 20, text2, ARRAYSIZE(text2));
            TCHAR text3[] = TEXT("Вход в рынок:                  ");
            TextOut(hdc, 700, 20, text3, ARRAYSIZE(text3));
            TCHAR text4[] = TEXT("Счёт ФОРТС: ");
            TextOut(hdc, 50, 100, text4, ARRAYSIZE(text4));
            TCHAR text5[] = TEXT("Код клиента: ");
            TextOut(hdc, 50, 125, text5, ARRAYSIZE(text5));
            TCHAR text6[] = TEXT("Счёт Депо:    ");
            TextOut(hdc, 50, 150, text6, ARRAYSIZE(text6));
            TCHAR text7[] = TEXT("Количество лотов:");
            TextOut(hdc, 300, 100, text7, ARRAYSIZE(text7));
            TCHAR text8[] = TEXT("Таймфрейм, мин.:     ");
            TextOut(hdc, 540, 125, text8, ARRAYSIZE(text8));
            TCHAR text9[] = TEXT("Объем лотов:");
            TextOut(hdc, 540, 100, text9, ARRAYSIZE(text9));
            TCHAR text10[] = TEXT("Высота свечи:       ");
            TextOut(hdc, 300, 172, text10, ARRAYSIZE(text10));
            TCHAR text11[] = TEXT("Код бумаги:           ");
            TextOut(hdc, 300, 125, text11, ARRAYSIZE(text11));
            TCHAR text12[] = TEXT("Код класса:           ");
            TextOut(hdc, 300, 150, text12, ARRAYSIZE(text12));
            
            TCHAR text13[] = TEXT("Тек.зн.:");
            TextOut(hdc, 50, 40, text13, ARRAYSIZE(text13));
            TextOut(hdc, 300, 40, text13, ARRAYSIZE(text13));
            TextOut(hdc, 480, 40, text13, ARRAYSIZE(text13));
            TextOut(hdc, 700, 40, text13, ARRAYSIZE(text13));
            TCHAR text16[] = TEXT("Изменить:");
            TextOut(hdc, 50, 64, text16, ARRAYSIZE(text16));
            TextOut(hdc, 300, 64, text16, ARRAYSIZE(text16));
            TextOut(hdc, 480, 64, text16, ARRAYSIZE(text16));
            TextOut(hdc, 700, 64, text16, ARRAYSIZE(text16));
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        fail_key_turn_on(path2);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
