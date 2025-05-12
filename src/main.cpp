//################################################################
//                      Platform Global
//################################################################
static bool running = true;

//################################################################
//                     Platform Funktionen
//################################################################
bool platform_create_window(int width, int height, char* title);
void platform_update_window();


//################################################################
//                      Windows Platform
//################################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMIMAX
#include <Windows.h>


//################################################################
//               Windows Globals
//################################################################

static HWND window;




//################################################################
//               Platform Implementation
//################################################################
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,
                                        WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch(msg){
        case WM_CLOSE:
        {
            running = false;
            break;
        }
        default:
        {
            result = DefWindowProcA(window, msg, wParam, lParam);
        }
    }

    return result;
}



bool platform_create_window(int width, int height, char* title)
{
    HINSTANCE instance = GetModuleHandleA(0);

    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);           // Design Vom Cursor
    wc.lpszClassName = title;
    wc.lpfnWndProc = windows_window_callback;                    // Windows Eingabe

    if(!RegisterClassA(&wc))
    {
        return false;
    }

    int dwstyle = WS_OVERLAPPEDWINDOW;
    
    window = CreateWindowExA(0, title, // reference LPSZCLASSName von wc
                                  title,   // Der Richtige Titel.
                                  dwstyle,
                                  100,
                                  100,
                                  width,
                                  height,
                                  NULL,
                                  NULL,
                                  instance,
                                  NULL);
    
    if(window == NULL)
    {
        return false;
    }

    ShowWindow(window, SW_SHOW);

    return true;
}

void platform_update_window()
{
    MSG msg;

    while (PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg); // senden zu call back
    }
    
}

#endif





int main(){

    platform_create_window(1200, 720, "KartoffelMotor");

    while (running)
    {
        //Update
        platform_update_window();
    }
    return 0;
}