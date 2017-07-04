// Because Sokoban++ 1.6.0.0 doens't support the SolveEx() function,
// this module contains the old/deprecated Solve() function. This function
// simply calls the SolveEx function, so if you want to maintain compatibility
// with the old version, you can simply include this module.

#include <malloc.h>
#define SOKOBAN_PLUGIN_ENABLE_BACKWARDS_COMPATIBILITY
#include "sokobanpluginsdll.h"

extern SOLVEEX SolveEx;
extern GETPLUGINNAME GetPluginName;

int __stdcall SolverCallback(void)
{
    // This function is normally implemented in the host program (e.g. Sokoban++).
    // Because when we are called from Sokoban++ 1.6.0.0, the host doesn't have this function,
    // we also implement a dummy function ourself, so we can safely call it from the SolveEx()
    // function.
    return SOLVER_OK;
}

int __stdcall Solve(unsigned int uiWidth, unsigned int uiHeight, unsigned char** ppucBoard, char* pcSolution, unsigned int uiSolutionBufferSize)
{
    // Solve() is included for backwards compatibility.
    // Sokoban++ version 1.6.0.0 only supported Solve()
    // SolveEx was added to 1.6.1.0
    // If you write your own solver, you can just copy this function,
    // all it does is calling SolveEx()
    char *pcBoard;
    struct SolverStatus ssStatus;
    int iResult;
    unsigned int i, j;

    pcBoard = malloc(uiWidth * uiHeight + 1);

    if(pcBoard != NULL)
    {
        // Copy board to single string. In the SolveEx function the passing of the board was simplified,
        // so we have to convert the old board to the new.
        for(i = 0; i < uiHeight; i++)
        {
            for(j = 0; j < uiWidth; j++)
            {
                pcBoard[i * uiWidth + j] = ppucBoard[i][j];
            }
        }
        pcBoard[uiWidth * uiHeight] = '\0'; // terminating NULL

        // initialize structure
        ssStatus.uiSize = sizeof(ssStatus);

        // Call newer function
        iResult = SolveEx(uiWidth, uiHeight, pcBoard, pcSolution, uiSolutionBufferSize, &ssStatus, &SolverCallback);

        // Clean up
        free(pcBoard);
    } else
    {
        iResult = SOLVER_FAILURE;
    }
    return iResult;
}

// The function GetSolverName was renamed to GetPluginName in version 3 of
// the plugin specification. Therefore it is required to also support the
// GetSolverName function if you are a solver and you want to support
// host programs (like Sokoban++ 1.6.2) which have not been updated to use
// GetPluginName yet.

void __stdcall GetSolverName(char* pcString, unsigned int uiStringBufferSize)
{
    // Pass call to newer function
    GetPluginName(pcString, uiStringBufferSize);
}
