#include "pch.h"
#include "ARFSubroutines.h"


extern "C" void FResRdBegin(char* FileName, char* Title, char* JobName, int* Units, int* NumDOF,
    int* DOFs, int* UserCode, int* MaxNode, int* NumNode, int* MaxElem, int* NumElem,
    int* MaxResultSet, int* NumResultSet);
extern "C" void FResRdEnd();
extern "C" void FResRdGeomBegin(int* MaxType, int* MaxReal, int* MaxCsys, int* nXYZ);
extern "C" void FResRdGeomEnd();
extern "C" void FResRdTypeBegin(int* NumType);
extern "C" void FResRdType(int* itype, int* ielc);
extern "C" void FResRdTypeEnd();
extern "C" void FResRdRealBegin(int* NumReal, int* NumPerReal);
extern "C" void FResRdReal(int* iReal, double* Rcon);
extern "C" void FResRdRealEnd();
extern "C" void FResRdCsysBegin(int* NumCsys);
extern "C" void FResRdCsys(int* iCsys, double* Csys);
extern "C" void FResRdCsysEnd();
extern "C" void FResRdNodeBegin();
extern "C" void FResRdNode(int* iNode, double* xyzang);
extern "C" void FResRdNodeEnd();
extern "C" void FResRdElemBegin();
extern "C" void FResRdElem(int* iElem, int* nodes, int* ElemData);
extern "C" void FResRdElemEnd();


void ARF::CResRdBegin(char* FileName, char* Title, char* JobName, int* Units, int* NumDOF,
    int* DOFs, int* UserCode, int* MaxNode, int* NumNode, int* MaxElem, int* NumElem,
    int* MaxResultSet, int* NumResultSet)
{
    FResRdBegin(FileName, Title, JobName, Units, NumDOF, DOFs, UserCode, MaxNode,
        NumNode, MaxElem, NumElem, MaxResultSet, NumResultSet);
}

void ARF::CResRdEnd()
{
    FResRdEnd();
}

void ARF::CResRdGeomBegin(int* MaxType, int* MaxReal, int* MaxCsys, int* nXYZ)
{
    FResRdGeomBegin(MaxType, MaxReal, MaxCsys, nXYZ);
}

void ARF::CResRdGeomEnd()
{
    FResRdGeomEnd();
}

void ARF::CResRdTypeBegin(int* NumType)
{
    FResRdTypeBegin(NumType);
}

void ARF::CResRdType(int* itype, int* ielc)
{
    FResRdType(itype, ielc);
}

void ARF::CResRdTypeEnd()
{
    FResRdTypeEnd();
}

void ARF::CResRdRealBegin(int* NumReal, int* NumPerReal)
{
    FResRdRealBegin(NumReal, NumPerReal);
}

void ARF::CResRdReal(int* iReal, double* Rcon)
{
    FResRdReal(iReal, Rcon);
}

void ARF::CResRdRealEnd()
{
    FResRdRealEnd();
}

void ARF::CResRdCsysBegin(int* NumCsys)
{
    FResRdCsysBegin(NumCsys);
}

void ARF::CResRdCsys(int* iCsys, double* Csys)
{
    FResRdCsys(iCsys, Csys);
}

void ARF::CResRdCsysEnd()
{
    FResRdCsysEnd();
}

void ARF::CResRdNodeBegin()
{
    FResRdNodeBegin();
}

void ARF::CResRdNode(int* iNode, double* xyzang)
{
    FResRdNode(iNode, xyzang);
}

void ARF::CResRdNodeEnd()
{
    FResRdNodeEnd();
}

void ARF::CResRdElemBegin()
{
    FResRdElemBegin();
}

void ARF::CResRdElem(int* iElem, int* nodes, int* ElemData)
{
    FResRdElem(iElem, nodes, ElemData);
}

void ARF::CResRdElemEnd()
{
    FResRdElemEnd();
}

