// ShootingGame_2022_03_18.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "ShootingGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;                                      // 윈도우 핸들입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SHOOTINGGAME20220318, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //초기화    
    START_DEBUG_CONSOLE();                  //디버그 콘솔창 열기
    InitGraphic(hWnd, 0, 0, WIDTH, HEIGHT); //그래픽 초기화

    Time::Init();    //타임초기화
    Random::Init();  //랜덤초기화

    //배경, 플레이어 등...게임객체 로딩
    ObjectManager::Instantiate(new GameBG      (0, 0                    ));
    ObjectManager::Instantiate(new Player      (WIDTH/2 - 34, HEIGHT+100));
    ObjectManager::Instantiate(new EnemySpawner(WIDTH/2, 0              ));


    //****************애니메이션 클래스 테스트 하기****************************
    //ObjectManager::Instantiate(new Animation("", "", true, 200, 100));
    //ObjectManager::Instantiate(new Enemy(150,-200));
    


   

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
         //*************윈도우 실행부분******************//
         if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
         {
             if (msg.message == WM_QUIT)
             {
                 break;
             }

             TranslateMessage(&msg);
             DispatchMessage(&msg);
         }

         //****************게임실행...부분*****************//
         //화면클리어
         Clear(0, 0, 0);

         //업데이트
         Time::Update();
         Input::Update();

         //객체목록 업데이트
         ObjectManager::Update();

         //객체 충돌검사
         ObjectManager::CheckCollision();

         //위 객체가 모두 사용 완료 이후에 삭제
         ObjectManager::ClearDeadObjects();


         //그리기
         ObjectManager::Draw();

         //렌더링
         Render();
    }

    //프로램종료
    STOP_DEBUG_CONSOLE();   //디버그 콘솔창 닫기
    ExitGraphic();          //그래픽 종료
    ObjectManager::Clear(); //게임객체 목록..전체 삭제

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHOOTINGGAME20220318));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //윈도우 스타일 변수
   int style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

   //윈도우 크기 조정하기//
   RECT rt = {0, 0, WIDTH, HEIGHT};
   int width, height;

   AdjustWindowRect(&rt, style, FALSE);

   width  = rt.right  - rt.left;  //윈도우 너비
   height = rt.bottom - rt.top;   //윈도우 높이

   hWnd = CreateWindowW(szWindowClass, 
                             szTitle, 
                             style,
                             CW_USEDEFAULT, 
                             0, 
                             width, 
                             height, 
                             nullptr, 
                             nullptr, 
                             hInstance, 
                             nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            //윈도우의..PAINT 메세지에서..게임장면..화면에 보내기
            Render();

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}