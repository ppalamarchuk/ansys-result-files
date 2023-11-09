// ******************************************************************************
// This example demonstrates reading data from .rst file using subroutines.
// Run "example1" function to understand basic features of file reading
//
// char FileName[260] = "D:\\Projects\\ansys-result-files\\data\\file.rst";
// example1(FileName);
//
// ******************************************************************************

#pragma once

void example1(char* FileName);
void readGeometry(int MaxElem);
void readLoadSet(int MaxNode, int NumDOF, int MaxElem, int NumResultSet);
void readBoundaryConditions(int MaxNode, int NumDOF);
void readResults(int MaxElem, int MaxNode);

