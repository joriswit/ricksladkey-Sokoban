#pragma once

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;

ref class ParentWindow: public System::Windows::Forms::IWin32Window
{
    HWND m_hWnd;

public:

    ParentWindow(HWND hWnd);

    virtual property IntPtr Handle { IntPtr get(); }

}; 