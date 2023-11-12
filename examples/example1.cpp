// ******************************************************************************
// This example demonstrates reading data from .rst file using subroutines.
// ******************************************************************************

#include "CResRd.h"
#include <iostream>

void readBoundaryConditions(int MaxNode, int NumDOF)
{
    std::cout << "\n******  Boundary Conditions  *****\n";
    int BCHeader[40];
    arf::subroutines::CResRdBCBegin(BCHeader);

    // Constraints
    std::cout << "\n******  Constraints  *****\n";
    int nFixed;
    arf::subroutines::CResRdFixBegin(BCHeader, &nFixed);
    if (nFixed > 0)
    {
        double values[4];

        for (int i = 1; i < MaxNode + 1; i++)
        {
            for (int j = 1; j < NumDOF + 1; j++)
            {
                int k = (BCHeader[6] == 0) ?
                    arf::subroutines::CResRdFixOld(&i, &j, values) :
                    arf::subroutines::CResRdFix(&i, &j, values);
                if (k > 0)
                {
                    std::cout << "Node = " << i << ", DOF = " << j << ", Values = " << values[0] <<
                        " " << values[1] << " " << values[2] << " " << values[3] << "\n";
                }
            }
            if (i == 10) break;
        }
        arf::subroutines::CResRdFixEnd();
    }

    // Applied Forces
    std::cout << "\n******  Applied Forces  *****\n";
    int nForces;
    arf::subroutines::CResRdForcBegin(BCHeader, &nForces);
    if (nForces > 0)
    {
        double values[4];
        for (int i = 1; i < MaxNode + 1; i++)
        {
            for (int j = 1; j < NumDOF + 1; j++)
            {
                int k = (BCHeader[6] == 0) ?
                    arf::subroutines::CResRdForcOld(&i, &j, values) :
                    arf::subroutines::CResRdForc(&i, &j, values);
                if (k > 0)
                {
                    std::cout << "Node = " << i << ", DOF = " << j << ", Values = " << values[0] <<
                        " " << values[1] << " " << values[2] << " " << values[3] << "\n";
                }
            }
            if (i == 10) break;
        }
        arf::subroutines::CResRdForcEnd();
    }

    arf::subroutines::CResRdBCEnd();
}

void readResults(int MaxElem, int MaxNode)
{
    // Element Stresses
    std::cout << "\n*****  Element Solution, Stresses  *****\n";
    arf::subroutines::CResRdEresBegin();
    double Str[MAXELERECORD];

    for (int i = 1; i < MaxElem + 1; i++)
    {
        int kerr = arf::subroutines::CResRdEstrBegin(&i);
        if (kerr == 0)
        {
            int j = 3; // Element nodal component stresses.
            std::cout << "Element = " << i << "\n";
            int nodstr = arf::subroutines::CResRdEstr(&j, Str) / 6;
            for (int k = 0; k < nodstr; k++)
            {
                std::cout << Str[6 * k] << " " << Str[6 * k + 1] << " " << Str[6 * k + 2] <<
                    " " << Str[6 * k + 3] << " " << Str[6 * k + 4] << " " << Str[6 * k + 5] << "\n";
            }
        }
        if (i == 5) break;
        arf::subroutines::CResRdEstrEnd();
    }

    arf::subroutines::CResRdEresEnd();
}

void readLoadSet(int MaxNode, int NumDOF, int MaxElem, int NumResultSet)
{
    std::cout << "\n\n**********  Load Sets  **********\n";
    int key = 0, lstep, substep, ncumit, kcmplx = 0;
    double time;
    char Title[405];
    char DofLab[MAXDOFLABELLEN - 1];

    for (int iSet = 1; iSet < NumResultSet + 1; iSet++)
    {
        lstep = iSet;
        int kerr = arf::subroutines::CResRdSolBegin(&key, &lstep, &substep,
            &ncumit, &kcmplx, &time, Title, DofLab);
        if (kerr != 0)
        {
            std::cout << "Warning: Load set = " << iSet << " not found on the file\n";
            continue;
        }

        std::cout << "\n**********  Load Set = " << iSet << " **********\n";
        std::cout << "lstep = " << lstep << ", substep = " << substep << ", ncumit = " <<
            ncumit << ", kcmplx = " << kcmplx << ", time = " << time << "\n";

        // Displacements
        std::cout << "\n*****  Displacements  *****\n";
        double Disp[MAXDOFSPERNODE];
        arf::subroutines::CResRdDispBegin();
        for (int i = 1; i < MaxNode + 1; i++)
        {
            int k = arf::subroutines::CResRdDisp(&i, Disp);
            if (k > 0)
            {
                std::cout << "Node = " << i << ", Disp = ";
                for (int j = 0; j < k; j++)
                {
                    std::cout << Disp[j] << " ";
                }
                std::cout << "\n";
            }
            if (i == 10) break;
        }
        arf::subroutines::CResRdDispEnd();

        // Reaction Forces
        std::cout << "\n******  Reaction Forces  *****\n";
        int nRForce;
        arf::subroutines::CResRdRforBegin(&nRForce);
        if (nRForce > 0)
        {
            double value;
            for (int i = 1; i < MaxNode + 1; i++)
            {
                for (int j = 1; j < NumDOF + 1; j++)
                {
                    int k = arf::subroutines::CResRdRfor(&i, &j, &value);
                    if (k > 0)
                    {
                        std::cout << "Node = " << i << ", DOF = " << j <<
                            ", Value = " << value << "\n";
                    }
                }
                if (i == 10) break;
            }
            arf::subroutines::CResRdRforEnd();
        }

        readBoundaryConditions(MaxNode, NumDOF);

        readResults(MaxElem, MaxNode);

        //if (iSet == 1) break;

        arf::subroutines::CResRdSolEnd();
    }
}

void readGeometry(int MaxElem)
{
    std::cout << "\n**********  Geometry  **********\n";
    int MaxType, MaxReal, MaxCsys, nXYZ;
    arf::subroutines::CResRdGeomBegin(&MaxType, &MaxReal, &MaxCsys, &nXYZ);

    std::cout << "MaxType: " << MaxType << ", MaxReal = " << MaxReal <<
        ", MaxCsys = " << MaxCsys << ", nXYZ = " << nXYZ << "\n";

    // Element Types
    std::cout << "\n*****  Element Types  *****\n";
    int NumType;
    int ielc[IELCSZ];
    arf::subroutines::CResRdTypeBegin(&NumType);
    std::cout << "NumType = " << NumType << "\n";
    for (int i = 1; i < MaxType + 1; i++)
    {
        int n = arf::subroutines::CResRdType(&i, ielc);
        if (n > 0)
        {
            // read documentation for "ielc" interpretation
            std::cout << "iType = " << i << ", ElementNumber = " << ielc[1] <<
                ", Number of nodes per elem = " << ielc[60] <<
                ", Number of corner nodes = " << ielc[93] << "\n";
        }
        if (i == 10) break;
    }
    arf::subroutines::CResRdTypeEnd();

    // Real Constants
    std::cout << "\n*****  Real Constants  *****\n";
    int NumReal, NumPerReal;
    double Rcon[MAXREALS];
    arf::subroutines::CResRdRealBegin(&NumReal, &NumPerReal);
    std::cout << "NumReal = " << NumReal << ", NumPerReal = " << NumPerReal << "\n";
    for (int i = 1; i < MaxReal + 1; i++)
    {
        int n = arf::subroutines::CResRdReal(&i, Rcon);
        if (n > 0)
        {
            // See the ANSYS Elements Reference manual for Rcon values for a specific element
            std::cout << "iReal = " << i << ", Number of reals: " << n << "\n";
        }
        if (i == 10) break;
    }
    arf::subroutines::CResRdRealEnd();

    // Coordinate Systems
    std::cout << "\n*****  Coordinate Systems  *****\n";
    int NumCsys;
    double Csys[MAXREALS];
    arf::subroutines::CResRdCsysBegin(&NumCsys);
    std::cout << "NumCsys: " << NumCsys << "\n";
    for (int i = 1; i < MaxCsys + 1; i++)
    {
        int n = arf::subroutines::CResRdCsys(&i, Csys);
        if (n > 0)
        {
            // Csys stores coord system description (transformation matrix,
            // origin, and more). Read documentation.
            std::cout << "iCsys = " << i << ", Number of values = " << n << "\n";
        }
        if (i == 10) break;
    }
    arf::subroutines::CResRdCsysEnd();

    // Nodal Coordinates
    std::cout << "\n*****  Nodal Coordinates  *****\n";
    double xyz[6];
    arf::subroutines::CResRdNodeBegin();
    for (int i = 1; i < nXYZ + 1; i++)
    {
        int n = arf::subroutines::CResRdNode(&i, xyz);
        if (n > 0)
        {
            std::cout << "Node number: " << n << ", xyz: " << xyz[0] <<
                "\t" << xyz[1] << "\t" << xyz[2] << "\n";
        }
        if (i == 10) break;
    }
    arf::subroutines::CResRdNodeEnd();

    // Elements
    std::cout << "\n**********  Elements  **********\n";
    int nodes[MAXNODESPERELEM];
    int ElemData[10];
    arf::subroutines::CResRdElemBegin();
    for (int i = 1; i < MaxElem + 1; i++)
    {
        int n = arf::subroutines::CResRdElem(&i, nodes, ElemData);
        if (n > 0)
        {
            std::cout << "iElem: " << i << ", number of nodes: " << n <<
                ", material: " << ElemData[0] << "\n";
            std::cout << "Elem nodes: ";
            for (int j = 0; j < n; j++)
                std::cout << nodes[j] << " ";
            std::cout << "\n\n";
        }
        if (i == 10) break;
    }
    arf::subroutines::CResRdElemEnd();

    arf::subroutines::CResRdGeomEnd();
}

int main()
{
    char FileName[260] = "D:\\path\\to\\file\\file.rst";
    char Title[162];
    char JobName[32];
    int Units, NumDOF, UserCode, MaxNode, NumNode,
        MaxElem, NumElem, MaxResultSet, NumResultSet;
    int DOFs[MAXDOFSPERNODE];

    int kerr = arf::subroutines::CResRdBegin(FileName, Title, JobName, &Units, &NumDOF, DOFs,
        &UserCode, &MaxNode, &NumNode, &MaxElem, &NumElem, &MaxResultSet, &NumResultSet);
    if (kerr != 0)
    {
        std::cout << "Error in file open!\n";
        return -1;
    }

    std::cout << "JobName: " << JobName << "\n";
    std::cout << "Units: " << Units << ", NumDOF = " << NumDOF << ", UserCode = " << UserCode <<
        ", MaxNode: " << MaxNode << ", NumNode: " << NumNode << ", MaxElem: " << MaxElem << ", NumElem: " <<
        NumElem << ", MaxResultSet: " << MaxResultSet << ", NumResultSet: " << NumResultSet << "\n";

    readGeometry(MaxElem);

    readLoadSet(MaxNode, NumDOF, MaxElem, NumResultSet);

    arf::subroutines::CResRdEnd();

    return 0;
}


