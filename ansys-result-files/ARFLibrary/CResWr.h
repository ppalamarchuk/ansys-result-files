#pragma once
#include "ansysdef.h"

#ifdef ARFLIBRARY_EXPORTS
#define ARFLIBRARY_API __declspec(dllexport)
#else
#define ARFLIBRARY_API __declspec(dllimport)
#endif

namespace arf {
    extern "C" {
        /// <summary>
        /// Open the result file and extracts header information. Note, this call must be matched with a subsequent
        /// CResWrEnd() to ensure that the file is closed and internal structures are deallocated properly.
        /// </summary>
        /// <param name="FileName [in]"> Full path to the result file to open. (max 260 characters) </param>
        /// <param name="Title [in]"> Title the simulation separated by newlines. (max 162 characters) </param>
        /// <param name="JobName [in]"> Jobname for the simulation. (max 32 characters) </param>
        /// <param name="Units [in]"> Units designator:
        ///                             0 - User Defined Units
        ///                             1 - SI
        ///                             2 - CSG
        ///                             3 - U.S.Customary, using feet
        ///                             4 - U.S.Customary, using inches
        ///                             5 - MKS
        ///                             6 - MPA
        ///                             7 - uMKS
        /// </param>
        /// <param name="NumDOF [in]"> The number of DOF per node </param>
        /// <param name="DOFs [in]"> Array[MAXDOFSPERNODE] of the DOFs per node </param>
        /// <param name="UserCode [in]"> Internal code for this application </param>
        /// <param name="MaxNode [in]"> Maximum node number used </param>
        /// <param name="NumNode [in]"> Number of nodes attached to elements </param>
        /// <param name="MaxElem [in]"> Maximum element number used </param>
        /// <param name="NumElem [in]"> Number of elements used </param>
        /// <param name="MaxResultSet [in]"> Maximum number of result sets (usually 1000) </param>
        /// <returns> 0 - successful, other - error in file open </returns>
        ARFLIBRARY_API int CResWrBegin(char* FileName, char* Title, char* JobName, int* Units,
            int* NumDOF, int* DOFs, int* UserCode, int* MaxNode, int* NumNode, int* MaxElem,
            int* NumElem, int* MaxResultSet);

        /// <summary>
        /// Close result file.
        /// </summary>
        ARFLIBRARY_API void CResWrEnd();

        /// <summary>
        /// Store nodal displacements
        /// </summary>
        /// <param name="node [int]"> Node number </param>
        /// <param name="Disp [int]"> Array [nDOF] of displacements </param>
        ARFLIBRARY_API void CResWrDisp(int* node, double* Disp);
    }
}

