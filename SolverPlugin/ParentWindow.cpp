#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "ParentWindow.h"

#using <mscorlib.dll>
#using <System.Windows.Forms.dll>
#using <System.dll>

using namespace System;

ParentWindow::ParentWindow(HWND hWnd)
{
    m_hWnd = hWnd;
}
IntPtr ParentWindow::Handle::get()
{
    return (IntPtr)m_hWnd;
} 
