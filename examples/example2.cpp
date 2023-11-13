// ******************************************************************************
// This example demonstrates reading data from .rst file using RSTReader class.
// ******************************************************************************

#include <iostream>
#include "RSTReader.h"

int main()
{
    arf::RSTReader reader;
    reader.open("D:\\path\\to\\file\\file.rst");

    std::cout << "\n**********  Elements  **********\n";
    reader.select(arf::RSTReader::DataType::ElementTypes);
    for (const auto& elType : reader.elementTypes())
    {
        if (!elType.isValid) continue;
        std::cout << "Element " << elType.referenceNumber << ": id = " << elType.routineNumber <<
            ", nodelem = " << elType.nodelm << ", nodfor = " << elType.nodfor << ", nodstr = " <<
            elType.nodstr << "\n";
    }

    reader.select(arf::RSTReader::DataType::RealConstants);
    for (const auto& rc : reader.realConstants())
    {
        if (!rc.isValid) continue;
        // work with RealConstant data
    }

    reader.select(arf::RSTReader::DataType::CoordinateSystems);
    for (const auto& cs : reader.coordinateSystems())
    {
        if (!cs.isValid) continue;
        // work with CoordinateSystem data (transformation matrix, origin, angles, and more)
    }

    std::cout << "\n*****  Nodal Coordinates  *****";
    int counter = 0;
    reader.select(arf::RSTReader::DataType::NodalCoordinates);
    for (const auto& node : reader.nodalCoordinates())
    {
        if (!node.isValid) continue;
        std::cout << "\nnodeNumber: " << node.nodeNumber << ", coordinates: ";
        std::copy(node.coordinates.begin(), node.coordinates.end(),
            std::ostream_iterator<double>(std::cout, " "));
        if (counter++ == 10) break;
    }

    std::cout << "\n\n**********  Elements  **********";
    counter = 0;
    reader.select(arf::RSTReader::DataType::ElementsInfo);
    for (const auto& el : reader.elementsInfo())
    {
        if (!el.isValid) continue;
        std::cout << "\nelementNumber: " << el.elementNumber << ", materialId: " << el.materialId <<
            ", elementType: " << el.elementType << ", deathFlag: " << el.deathFlag << "\nnodes: ";
        std::copy(el.nodes.begin(), el.nodes.end(), std::ostream_iterator<int>(std::cout, " "));
        if (counter++ == 10) break;
    }

    std::cout << "\n\n*****  Displacements  *****";
    counter = 0;
    reader.select(arf::RSTReader::DataType::NodalDisplacements);
    for (const auto& ndisp : reader.nodalDisplacements())
    {
        if (!ndisp.isValid) continue;
        std::cout << "\nnodeNumber: " << ndisp.id << ", displacements: ";
        std::copy(ndisp.data.begin(), ndisp.data.end(), std::ostream_iterator<double>(std::cout, " "));
        if (counter++ == 10) break;
    }

    reader.select(arf::RSTReader::DataType::ElementResults);

    std::cout << "\n\n*****  Element Solution, Stresses  *****";
    counter = 0;
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


