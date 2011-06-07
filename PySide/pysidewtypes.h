#ifndef __PYSIDEWTYPES__
#define __PYSIDEWTYPES__

typedef struct HWND__ *HWND;
typedef unsigned UINT;
typedef long LONG;
typedef unsigned long DWORD;
typedef UINT WPARAM;
typedef LONG LPARAM;

struct POINT
{
    LONG x;
    LONG y;
};

struct MSG
{
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
};

#endif
