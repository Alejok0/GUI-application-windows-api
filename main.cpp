#include <windows.h>

#define BUTTON_CLIQUE_AQUI 3

HWND hEdit;

void loadImage();
void agregarBotones(HWND hWnd);

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

  WNDCLASS wc = {};

  wc.lpszClassName = "My Window Class";
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpfnWndProc = WindowProcedure;
  wc.hInstance = hInst;

  int anchoPantalla = GetSystemMetrics(SM_CXSCREEN);
  int altoPantalla = GetSystemMetrics(SM_CYSCREEN);

  int anchoVentana = 800;
  int altoVentana = 600;

  int x = (anchoPantalla - anchoVentana) / 2;
  int y = (altoPantalla - altoVentana) / 2;
  
  RegisterClass(&wc);
  
  CreateWindow(
    wc.lpszClassName,
    "My GUI App",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    x, y, anchoVentana, altoVentana,
    NULL, NULL, NULL, NULL
    );

  MSG msg = {};
  
  while(GetMessage(&msg, NULL, 0, 0)){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){

  switch (msg){
  case WM_CREATE:
    agregarBotones(hWnd);
    break;

  case WM_COMMAND:
    switch(wp){
    case BUTTON_CLIQUE_AQUI:
      char editText[100];
      GetWindowText(hEdit,  , 100);
      MessageBox(NULL, editText, "Message", MB_OK);
    }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hWnd, msg, wp, lp);
}

void agregarBotones(HWND hWnd){

  CreateWindow(
    "Static",
    "Digite un valor numerico",
    WS_VISIBLE | WS_CHILD | SS_CENTER,
    100, 100, 600, 20,
    hWnd,
    NULL, NULL, NULL
    );

  hEdit = CreateWindow(
    "Edit",
    "",
    WS_VISIBLE | WS_CHILD | WS_BORDER,
    100, 130, 600, 20,
    hWnd,
    NULL, NULL, NULL
    );

  CreateWindow(
    "Button",
    "Click aqui",
    WS_VISIBLE | WS_CHILD,
    100, 160, 600, 50,
    hWnd,
    (HMENU)BUTTON_CLIQUE_AQUI, NULL, NULL
    );

  HWND hLogoStatic = CreateWindow(
    "Static",
    NULL,
    WS_VISIBLE | WS_CHILD | SS_BITMAP,
    250, 220, 0, 0,
    hWnd,
    NULL, NULL, NULL
    );

  HBITMAP hLogoImage = (HBITMAP)LoadImage(NULL, "img\\logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);  

  SendMessage(hLogoStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
}
