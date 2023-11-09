// SampleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "example1.h"


int main()
{
    //char FileName[260] = "D:\\_Projects\\ansys-result-files\\AnsysExamples\\ElasticBeam\\file.rst";
    //char FileName[260] = "D1:\\_Projects\\ansys-result-files\\AnsysExamples\\PlasticityBeam\\file.rst";
    //char FileName[260] = "D:\\_Projects\\ansys-result-files\\AnsysExamples\\CreepBeam\\file.rst";
    char FileName[260] = "D:\\_Projects\\ansys-result-files\\AnsysExamples\\SimpleAnalysis\\file.rst";

    example1(FileName);

    return 0;
}


