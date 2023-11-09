#include "pch.h"
#include "CResRd.h"


extern "C" int FResRdBegin(char* FileName, char* Title, char* JobName, int* Units, int* NumDOF,
    int* DOFs, int* UserCode, int* MaxNode, int* NumNode, int* MaxElem, int* NumElem,
    int* MaxResultSet, int* NumResultSet);
extern "C" void FResRdEnd();
extern "C" void FResRdGeomBegin(int* MaxType, int* MaxReal, int* MaxCsys, int* nXYZ);
extern "C" void FResRdGeomEnd();
extern "C" void FResRdTypeBegin(int* NumType);
extern "C" int FResRdType(int* itype, int* ielc);
extern "C" void FResRdTypeEnd();
extern "C" void FResRdRealBegin(int* NumReal, int* NumPerReal);
extern "C" int FResRdReal(int* iReal, double* Rcon);
extern "C" void FResRdRealEnd();
extern "C" void FResRdCsysBegin(int* NumCsys);
extern "C" int FResRdCsys(int* iCsys, double* Csys);
extern "C" void FResRdCsysEnd();
extern "C" void FResRdNodeBegin();
extern "C" int FResRdNode(int* iNode, double* xyzang);
extern "C" void FResRdNodeEnd();
extern "C" void FResRdElemBegin();
extern "C" int FResRdElem(int* iElem, int* nodes, int* ElemData);
extern "C" void FResRdElemEnd();
extern "C" int FResRdSolBegin(int* key, int* lstep, int* substep, int* ncumit,
    int* kcmplx, double* time, char* Title, char* DofLab);
extern "C" void FResRdSolEnd();
extern "C" void FResRdDispBegin();
extern "C" int FResRdDisp(int* node, double* Disp);
extern "C" void FResRdDispEnd();
extern "C" void FResRdRforBegin(int* nRForce);
extern "C" int FResRdRfor(int* node, int* idof, double* value);
extern "C" void FResRdRforEnd();
extern "C" void FResRdBCBegin(int* BCHeader);
extern "C" void FResRdBCEnd();
extern "C" void FResRdFixBegin(int* BCHeader, int* nFixed);
extern "C" int FResRdFixOld(int* node, int* idof, double* value);
extern "C" int FResRdFix(int* node, int* idof, double* value);
extern "C" void FResRdFixEnd();
extern "C" void FResRdForcBegin(int* BCHeader, int* nForces);
extern "C" int FResRdForcOld(int* node, int* idof, double* value);
extern "C" int FResRdForc(int* node, int* idof, double* value);
extern "C" void FResRdForcEnd();
extern "C" void FResRdEresBegin();
extern "C" void FResRdEresEnd();
extern "C" int FResRdEstrBegin(int* iElem);
extern "C" int FResRdEstr(int* iStr, double* Str);
extern "C" void FResRdEstrEnd();
extern "C" void FResRdNstrBegin(int* kNodStr);
extern "C" void FResRdNstrEnd();
extern "C" int FResRdNstr(int* node, double** Nstr);
extern "C" int FTestFunction(int* iNode, double* xyzang);


int arf::CResRdBegin(char* FileName, char* Title, char* JobName, int* Units, int* NumDOF,
    int* DOFs, int* UserCode, int* MaxNode, int* NumNode, int* MaxElem, int* NumElem,
    int* MaxResultSet, int* NumResultSet)
{
    return FResRdBegin(FileName, Title, JobName, Units, NumDOF, DOFs, UserCode,
        MaxNode, NumNode, MaxElem, NumElem, MaxResultSet, NumResultSet);
}

void arf::CResRdEnd()
{
    FResRdEnd();
}

void arf::CResRdGeomBegin(int* MaxType, int* MaxReal, int* MaxCsys, int* nXYZ)
{
    FResRdGeomBegin(MaxType, MaxReal, MaxCsys, nXYZ);
}

void arf::CResRdGeomEnd()
{
    FResRdGeomEnd();
}

void arf::CResRdTypeBegin(int* NumType)
{
    FResRdTypeBegin(NumType);
}

int arf::CResRdType(int* itype, int* ielc)
{
    return FResRdType(itype, ielc);
}

void arf::CResRdTypeEnd()
{
    FResRdTypeEnd();
}

void arf::CResRdRealBegin(int* NumReal, int* NumPerReal)
{
    FResRdRealBegin(NumReal, NumPerReal);
}

int arf::CResRdReal(int* iReal, double* Rcon)
{
    return FResRdReal(iReal, Rcon);
}

void arf::CResRdRealEnd()
{
    FResRdRealEnd();
}

void arf::CResRdCsysBegin(int* NumCsys)
{
    FResRdCsysBegin(NumCsys);
}

int arf::CResRdCsys(int* iCsys, double* Csys)
{
    return FResRdCsys(iCsys, Csys);
}

void arf::CResRdCsysEnd()
{
    FResRdCsysEnd();
}

void arf::CResRdNodeBegin()
{
    FResRdNodeBegin();
}

int arf::CResRdNode(int* iNode, double* xyzang)
{
    return FResRdNode(iNode, xyzang);
}

void arf::CResRdNodeEnd()
{
    FResRdNodeEnd();
}

void arf::CResRdElemBegin()
{
    FResRdElemBegin();
}

int arf::CResRdElem(int* iElem, int* nodes, int* ElemData)
{
    return FResRdElem(iElem, nodes, ElemData);
}

void arf::CResRdElemEnd()
{
    FResRdElemEnd();
}

int arf::CResRdSolBegin(int* key, int* lstep, int* substep, int* ncumit,
    int* kcmplx, double* time, char* Title, char* DofLab)
{
    return FResRdSolBegin(key, lstep, substep, ncumit, kcmplx, time, Title, DofLab);
}

void arf::CResRdSolEnd()
{
    FResRdSolEnd();
}

void arf::CResRdDispBegin()
{
    FResRdDispBegin();
}

int arf::CResRdDisp(int* node, double* Disp)
{
    return FResRdDisp(node, Disp);
}

void arf::CResRdDispEnd()
{
    FResRdDispEnd();
}

void arf::CResRdRforBegin(int* nRForce)
{
    FResRdRforBegin(nRForce);
}

int arf::CResRdRfor(int* node, int* idof, double* value)
{
    return FResRdRfor(node, idof, value);
}

void arf::CResRdRforEnd()
{
    FResRdRforEnd();
}

void arf::CResRdBCBegin(int* BCHeader)
{
    FResRdBCBegin(BCHeader);
}

void arf::CResRdBCEnd()
{
    FResRdBCEnd();
}

void arf::CResRdFixBegin(int* BCHeader, int* nFixed)
{
    FResRdFixBegin(BCHeader, nFixed);
}

int arf::CResRdFixOld(int* node, int* idof, double* value)
{
    return FResRdFixOld(node, idof, value);
}

int arf::CResRdFix(int* node, int* idof, double* value)
{
    return FResRdFix(node, idof, value);
}

void arf::CResRdFixEnd()
{
    FResRdFixEnd();
}

void arf::CResRdForcBegin(int* BCHeader, int* nForces)
{
    FResRdForcBegin(BCHeader, nForces);
}

int arf::CResRdForcOld(int* node, int* idof, double* value)
{
    return FResRdForcOld(node, idof, value);
}

int arf::CResRdForc(int* node, int* idof, double* value)
{
    return FResRdForc(node, idof, value);
}

void arf::CResRdForcEnd()
{
    FResRdForcEnd;
}

void arf::CResRdEresBegin()
{
    FResRdEresBegin();
}

void arf::CResRdEresEnd()
{
    FResRdEresEnd();
}

int arf::CResRdEstrBegin(int* iElem)
{
    return FResRdEstrBegin(iElem);
}

int arf::CResRdEstr(int* iStr, double* Str)
{
    return FResRdEstr(iStr, Str);
}

void arf::CResRdEstrEnd()
{
    FResRdEstrEnd();
}

void arf::CResRdNstrBegin(int* kNodStr)
{
    FResRdNstrBegin(kNodStr);
}

int arf::CResRdNstr(int* node, double** Nstr)
{
    return FResRdNstr(node, Nstr);
}

void arf::CResRdNstrEnd()
{
    FResRdNstrEnd();
}
