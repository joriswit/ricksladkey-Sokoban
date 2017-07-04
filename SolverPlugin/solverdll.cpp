#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef MessageBox
#pragma pack(push, 1)
#include "sokobanpluginsdll.h"
#pragma pack(pop)
#include "ParentWindow.h"

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Sokoban::Engine::Solvers;
using namespace Sokoban::Engine::Utilities;
using namespace Sokoban::Engine::Levels;

public ref class Globals abstract sealed {
public:
    static ISolver ^solver;
};

extern "C"
{

void ShowMessage(struct PluginStatus *psStatus, PLUGINCALLBACK *pc, const char *szMsg)
{
    strcpy_s(psStatus->szStatusText, 256, szMsg);
    pc();
}

int __stdcall SolveEx(unsigned int uiWidth, unsigned int uiHeight, char* pcBoard, char* pcSolution, unsigned int uiSolutionBufferSize, struct PluginStatus *psStatus, PLUGINCALLBACK *pc)
{
    try
    {
        String^ board = gcnew String(pcBoard);
        array< String^ >^ lines = gcnew array< String^ >(uiHeight);
        for (unsigned int y = 0; y < uiHeight; y++)
        {
            lines[y] = board->Substring(y * uiWidth, uiWidth);
        }
        Level ^level = gcnew Level(LevelEncoder::DecodeLevel(lines));

        ISolver ^solver = Solver::CreateInstance(SolverAlgorithm::BruteForce);

        solver->Level = level;

        ShowMessage(psStatus, pc, "Searching...");
        Globals::solver = solver;
        if (solver->Solve())
        {
            Globals::solver = nullptr;
            ShowMessage(psStatus, pc, "Found a solution!");

            // Get the solution
            String ^strSolution = solver->Solution->AsText;
            if (strSolution->Length != 0)
            {
                IntPtr szSolutionPtr = Marshal::StringToHGlobalAnsi(strSolution);
                strcpy_s(pcSolution, uiSolutionBufferSize, (char*)szSolutionPtr.ToPointer());
                Marshal::FreeHGlobal(szSolutionPtr);
                return SOKOBAN_PLUGIN_RESULT_SUCCESS;
            }
            else
            {
                return SOKOBAN_PLUGIN_RESULT_GIVEUP;
            }
        }
        else
        {
            Globals::solver = nullptr;
            return SOKOBAN_PLUGIN_RESULT_GIVEUP;
        }
    }
    catch (...)
    {
        return SOKOBAN_PLUGIN_RESULT_FAILURE;
    }
}

void __stdcall GetConstraints(unsigned int* puiMaxWidth, unsigned int* puiMaxHeight, unsigned int* puiMaxObjects)
{
    *puiMaxWidth = 0;
    *puiMaxHeight = 0;
    *puiMaxObjects = 0;
}

void __stdcall GetPluginName(char* pcString, unsigned int uiStringLength)
{
    char* pcAuthorString = "ZSokoban Solver";

    if (strlen(pcAuthorString) < uiStringLength)
    {
        strcpy_s(pcString, uiStringLength, pcAuthorString);
    }
}

void __stdcall Configure(HWND hwndParent)
{
    System::Windows::Forms::MessageBox::Show(gcnew ParentWindow(hwndParent), L"There is nothing to configure.", L"ZSokoban Solver", System::Windows::Forms::MessageBoxButtons::OK);
}

void __stdcall ShowAbout(HWND hwndParent)
{
    System::Windows::Forms::MessageBox::Show(gcnew ParentWindow(hwndParent), L"ZSokoban Solver plug-in\nversion 1.0", L"ZSokoban Solver", System::Windows::Forms::MessageBoxButtons::OK);
}

int __stdcall Terminate()
{
    try
    {
        ISolver ^solver = Globals::solver;
        if (solver != nullptr)
        {
            solver->CancelInfo->Cancel = true;
            return SOKOBAN_PLUGIN_RESULT_SUCCESS;
        }
        else
        {
            return SOKOBAN_PLUGIN_RESULT_FAILURE;
        }
    }
    catch (...)
    {
        return SOKOBAN_PLUGIN_RESULT_FAILURE;
    }
}

}