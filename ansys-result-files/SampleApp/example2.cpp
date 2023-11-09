#include "example2.h"
#include "CResRd.h"
#include "CResWr.h"
#include <iostream>
#include <vector>

void example2(char* FileName)
{
    char Title[162];
    char JobName[32];
    int Units, NumDOF, UserCode, MaxNode, NumNode,
        MaxElem, NumElem, MaxResultSet, NumResultSet;
    int DOFs[MAXDOFSPERNODE];

    int kerr = arf::CResRdBegin(FileName, Title, JobName, &Units, &NumDOF, DOFs, &UserCode,
        &MaxNode, &NumNode, &MaxElem, &NumElem, &MaxResultSet, &NumResultSet);
    if (kerr != 0)
        return;

    std::cout << "JobName: " << JobName << "\n";
    std::cout << "Units: " << Units << ", NumDOF = " << NumDOF << ", UserCode = " << UserCode <<
        ", MaxNode: " << MaxNode << ", NumNode: " << NumNode << ", MaxElem: " << MaxElem << ", NumElem: " <<
        NumElem << ", MaxResultSet: " << MaxResultSet << ", NumResultSet: " << NumResultSet << "\n";

    int key = 0, lstep = NumResultSet, substep, ncumit, kcmplx = 0;
    double time;
    char Title2[405];
    char DofLab[MAXDOFLABELLEN - 1];
    std::vector<std::vector<double>> DOFVector;
    DOFVector.reserve(NumNode);

    kerr = arf::CResRdSolBegin(&key, &lstep, &substep,
        &ncumit, &kcmplx, &time, Title2, DofLab);
    if (kerr != 0)
    {
        std::cout << "Warning: Load set = " << NumResultSet << " not found on the file\n";
        return;
    }

    std::cout << "\n**********  Last Load Set = " << NumResultSet << " **********\n";
    std::cout << "lstep = " << lstep << ", substep = " << substep << ", ncumit = " <<
        ncumit << ", kcmplx = " << kcmplx << ", time = " << time << "\n";

    // Displacements
    std::vector<double> Disp;
    Disp.resize(MAXDOFSPERNODE);

    arf::CResRdDispBegin();
    for (int i = 1; i < MaxNode + 1; i++)
    {
        int k = arf::CResRdDisp(&i, Disp.data());
        if (k > 0)
        {
            std::vector<double> tDisp = std::vector<double>{ Disp.begin(), Disp.begin() + k };
            DOFVector.push_back(tDisp);
        }
    }
    arf::CResRdDispEnd();

    arf::CResRdSolEnd();

    arf::CResRdEnd();

    // Write start

    /*char FileName2[260] = "D:\\_Projects\\ansys-result-files\\AnsysExamples\\SimpleAnalysis\\file2.rst";

    kerr = arf::CResWrBegin(FileName2, Title, JobName, &Units, &NumDOF, DOFs,
        &UserCode, &MaxNode, &NumNode, &MaxElem, &NumElem, &MaxResultSet);
    if (kerr != 0)
        return;


    arf::CResWrEnd();*/
}

void readLastSet(int MaxNode, int NumDOF, int MaxElem, int NumResultSet)
{
    
}

void updateNodeDisplacements(int MaxNode)
{
    
}
