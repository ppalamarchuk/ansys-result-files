// ******************************************************************************
// This example demonstrates updating data in .rst file using subroutines.
// Run "example2" function to understand basic features of data updating
//
// char FileName[260] = "D:\\Projects\\ansys-result-files\\data\\file.rst";
// example2(FileName);
//
// ******************************************************************************

#pragma once

void example2(char* FileName);
void readLastSet(int MaxNode, int NumDOF, int MaxElem, int NumResultSet);
void updateNodeDisplacements(int MaxNode);

