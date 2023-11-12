
#include <iostream>
#include "RSTReader.h"

int main()
{
    arf::RSTReader reader;
    reader.open("D:\\_Projects\\ansys-result-files\\AnsysExamples\\CreepBeam\\file.rst");

    reader.select(arf::RSTReader::DataType::ElementResults);

    std::cout << "\n\n*****  Element Solution, Stresses  *****";
    int counter = 0;
    for (const auto& elStresses : reader.elementStresses())
    {
        if (!elStresses.isValid) continue;
        std::cout << "\nelementNumber: " << elStresses.id <<
            ", stress values SX, SY, SZ, SXY, SYZ, SXZ for each corner node:\n";
        for (int i = 0; i < elStresses.data.size() / 6; i++)
        {
            std::copy(elStresses.data.begin() + 6*i, elStresses.data.begin() + 6*(i+1),
                std::ostream_iterator<double>(std::cout, " "));
            std::cout << "\n";
        }
        if (counter++ == 5) break;
    }

    std::cout << "\n\n*****  Element Solution, Elastic Strains  *****";
    counter = 0;
    for (const auto& elStrains : reader.elementElasticStrains())
    {
        if (!elStrains.isValid) continue;
        std::cout << "\nelementNumber: " << elStrains.id <<
            ", elastic strains values X, Y, Z, XY, YZ, XZ, EQV for each corner node:\n";
        for (int i = 0; i < elStrains.data.size() / 7; i++)
        {
            std::copy(elStrains.data.begin() + 7 * i, elStrains.data.begin() + 7 * (i + 1),
                std::ostream_iterator<double>(std::cout, " "));
            std::cout << "\n";
        }
        if (counter++ == 5) break;
    }

    return 0;
}


