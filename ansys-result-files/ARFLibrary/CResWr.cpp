#include "pch.h"
#include "CResWr.h"


extern "C" void FResWrDisp(int* node, double* Disp);
extern "C" int FResWrBegin(char* FileName, char* Title, char* JobName, int* Units, int* NumDOF,
    int* DOFs, int* UserCode, int* MaxNode, int* NumNode, int* MaxElem, int* NumElem, int* MaxResultSet);
extern "C" void FResWrEnd();


int arf::CResWrBegin(char* FileName, char* Title, char* JobName, int* Units, int* NumDOF, int* DOFs,
    int* UserCode, int* MaxNode, int* NumNode, int* MaxElem, int* NumElem, int* MaxResultSet)
{
    return FResWrBegin(FileName, Title, JobName, Units, NumDOF, DOFs, UserCode,
        MaxNode, NumNode, MaxElem, NumElem, MaxResultSet);
}

void arf::CResWrEnd()
{
    FResWrEnd();
}

void arf::CResWrDisp(int* node, double* Disp)
{
    FResWrDisp(node, Disp);
}
