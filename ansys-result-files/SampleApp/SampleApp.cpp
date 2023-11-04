// SampleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "ARFSubroutines.h"

void readExample(char* FileName)
{
    char Title[162];
    char JobName[32];
    int Units, NumDOF, UserCode, MaxNode, NumNode,
        MaxElem, NumElem, MaxResultSet, NumResultSet;
    int DOFs[MAXDOFSPERNODE];

    ARF::CResRdBegin(FileName, Title, JobName, &Units, &NumDOF, DOFs, &UserCode,
        &MaxNode, &NumNode, &MaxElem, &NumElem, &MaxResultSet, &NumResultSet);

    // Read Geometry
    {
        int MaxType, MaxReal, MaxCsys, nXYZ;
        ARF::CResRdGeomBegin(&MaxType, &MaxReal, &MaxCsys, &nXYZ);

        // Element Types
        int NumType;
        ARF::CResRdTypeBegin(&NumType);
        for (int i = 0; i < MaxType; i++)
        {
            int ielc[IELCSZ];
            ARF::CResRdType(&i, ielc);
        }
        ARF::CResRdTypeEnd();

        // Real Constants
        int NumReal, NumPerReal;
        ARF::CResRdRealBegin(&NumReal, &NumPerReal);
        for (int i = 0; i < MaxReal; i++)
        {
            double Rcon[MAXREALS];
            ARF::CResRdReal(&i, Rcon);
        }
        ARF::CResRdRealEnd();

        // Coordinate Systems
        int NumCsys;
        ARF::CResRdCsysBegin(&NumCsys);
        for (int i = 0; i < MaxCsys; i++)
        {
            double Csys[MAXREALS];
            ARF::CResRdCsys(&i, Csys);
        }
        ARF::CResRdCsysEnd();

        // Nodal Coordinates
        ARF::CResRdNodeBegin();
        for (int i = 0; i < nXYZ; i++)
        {
            if (i == 10) break;
            double xyz[6];
            ARF::CResRdNode(&i, xyz);
        }
        ARF::CResRdNodeEnd();

        // Elements
        ARF::CResRdElemBegin();
        for (int i = 0; i < MaxElem; i++)
        {
            if (i == 10) break;
            int nodes[MAXNODESPERELEM];
            int ElemData[10];
            ARF::CResRdElem(&i, nodes, ElemData);
            std::cout << i << "\n";
        }
        ARF::CResRdElemEnd();

        ARF::CResRdGeomEnd();
    }

    // Load Sets
    {

    }


    ARF::CResRdEnd();

}

int main()
{
    char FileName[260] = "D:\\_Projects\\ansys-result-files\\data\\file.rst";
    readExample(FileName);

    return 0;
}


