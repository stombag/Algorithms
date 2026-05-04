#include <windows.h>
#include <math.h>

struct AffineVector { float x, y, w; };

// 민혁님의 행렬 [1,0,0], [0,1,0], [2,2,1] (열 기준 -> 행 계산식)
float mat[3][3] = {
    {1.0f, 0.0f, 2.0f}, 
    {0.0f, 1.0f, 2.0f}, 
    {0.0f, 0.0f, 1.0f}  
};

AffineVector Transform(AffineVector v) {
    return {
        mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.w,
        mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.w,
        mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.w
    };
}

POINT ToScreen(AffineVector v) {
    return { (long)(200 + v.x * 60), (long)(500 - v.y * 60) };
}

// 화살표를 그리는 도우미 함수
void DrawArrow(HDC hdc, POINT start, POINT end, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 3, color);
    SelectObject(hdc, hPen);
    
    // 몸통 선
    MoveToEx(hdc, start.x, start.y, NULL);
    LineTo(hdc, end.x, end.y);

    // 화살표 촉 계산
    double angle = atan2(end.y - start.y, end.x - start.x);
    int arrowSize = 12;
    LineTo(hdc, (int)(end.x - arrowSize * cos(angle - 0.5)), (int)(end.y - arrowSize * sin(angle - 0.5)));
    MoveToEx(hdc, end.x, end.y, NULL);
    LineTo(hdc, (int)(end.x - arrowSize * cos(angle + 0.5)), (int)(end.y - arrowSize * sin(angle + 0.5)));
    
    DeleteObject(hPen);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // 1. 원래 공간의 기저 벡터 (빨강: e1, 파랑: e2) - 반투명 느낌으로 얇게
        POINT origin = ToScreen({0, 0, 1});
        DrawArrow(hdc, origin, ToScreen({1, 0, 1}), RGB(255, 150, 150)); // Original e1
        DrawArrow(hdc, origin, ToScreen({0, 1, 1}), RGB(150, 150, 255)); // Original e2

        // 2. 변환된 공간의 기저 벡터 (진한 색상)
        // 행렬의 첫 번째 열 [1, 0, 0]과 두 번째 열 [0, 1, 0]이 이동 성분을 만나 변한 결과
        AffineVector e1_prime = Transform({1, 0, 0}); // 순수 벡터 변환 (이동 미포함)
        AffineVector e2_prime = Transform({0, 1, 0}); 
        
        // 주의: 기저 벡터의 '방향'을 보기 위해 원점에서 해당 벡터만큼 더한 지점으로 화살표 그림
        DrawArrow(hdc, origin, ToScreen({e1_prime.x, e1_prime.y, 1}), RGB(200, 0, 0)); // Transformed e1
        DrawArrow(hdc, origin, ToScreen({e2_prime.x, e2_prime.y, 1}), RGB(0, 0, 200)); // Transformed e2

        // 3. 입력 점 [1, 1, 1]과 결과 점 [5, 5, 1] 벡터 선
        AffineVector inputP = {1, 1, 1};
        AffineVector resultP = Transform(inputP);
        
        // 원점에서 결과 점까지 뻗어나가는 굵은 녹색 화살표 (이게 민혁님이 보고 싶어 하신 선!)
        DrawArrow(hdc, origin, ToScreen(resultP), RGB(0, 150, 0));

        // 점 강조
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
        SelectObject(hdc, hBrush);
        POINT pRes = ToScreen(resultP);
        Ellipse(hdc, pRes.x - 5, pRes.y - 5, pRes.x + 5, pRes.y + 5);

        TextOut(hdc, 20, 20, L"Red/Blue: Basis Vectors (Light=Old, Dark=New)", 45);
        TextOut(hdc, 20, 40, L"Green Arrow: Vector to [5, 5, 1]", 32);

        DeleteObject(hBrush);
        EndPaint(hwnd, &ps);
    }
    else if (msg == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lC, int nS) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc; wc.hInstance = hI; wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = L"AffineVisual";
    RegisterClass(&wc);
    HWND hwnd = CreateWindow(L"AffineVisual", L"Vector Transformation Visualization", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 700, NULL, NULL, hI, NULL);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
    return 0;
}