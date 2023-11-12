#include "pch.h"
#include "RSTReader.h"
#include "CResRd.h"
#include <cassert>

using namespace arf;
using namespace arf::structures;
using namespace arf::subroutines;
using namespace arf::iterators;

RSTReader::~RSTReader()
{
    close();
}

bool RSTReader::open(const std::string& path)
{
    // close previous file if it was opened
    close();

    char Title[162];
    char JobName[32];
    int Units, UserCode, MaxResultSet;
    int DOFs[MAXDOFSPERNODE];

    m_sectionStack.push(std::make_unique<inner::BeginFileSection>());

    return CResRdBegin(path.c_str(), Title, JobName, &Units, &m_numDOF,
        DOFs, &UserCode, &m_maxNodeId, &m_numNode, &m_maxElementId,
        &m_numElement, &MaxResultSet, &m_resultSetInfo.numResultSet);
}

void RSTReader::close()
{
    while (!m_sectionStack.empty())
    {
        m_sectionStack.pop();
    }
}

bool RSTReader::select(const DataType type)
{
    // dispatcher
    switch (type) {
    case DataType::ElementTypes:
        return selectElementTypes();
    case DataType::RealConstants:
        return selectRealConstants();
    case DataType::CoordinateSystems:
        return selectCoordinateSystems();
    case DataType::NodalCoordinates:
        return selectNodalCoordinates();
    case DataType::ElementsInfo:
        return selectElementsInfo();
    case DataType::NodalDisplacements:
        return selectNodalDisplacements();
    case DataType::ReactionForces:
        return selectReactionForces();
    case DataType::Constraints:
        return selectConstraints();
    case DataType::AppliedForces:
        return selectAppliedForces();
    case DataType::ElementResults:
        return selectElementResults();
    default:
        return false;
    }
}

void RSTReader::selectResultSetNumber(int number)
{
    if (number < 1) number = m_resultSetInfo.numResultSet;
    if (m_resultSetInfo.resultSet == number)
        return;

    m_resultSetInfo.resultSet = number;
    m_resultSetInfo.loadStepNumber = number;
    reduceToLevel({ inner::ResultFileSectionLevel::BeginLevel });
    int key = 0, kcmplx = 0;
    int lstep = m_resultSetInfo.resultSet;
    char Title[405];
    char DofLab[MAXDOFLABELLEN - 1];
    int kerr = CResRdSolBegin(&key, &m_resultSetInfo.loadStepNumber, &m_resultSetInfo.substepNumber,
        &m_resultSetInfo.cumulativeIterationNumber, &kcmplx, &m_resultSetInfo.time, Title, DofLab);
    m_sectionStack.push(std::make_unique<inner::SolutionsFileSection>());
}

ResultSetInfo RSTReader::getResultSetInfo()
{
    selectResultSetNumber(m_resultSetInfo.resultSet);
    return m_resultSetInfo;
}

void RSTReader::setSolutionLevel()
{
    selectResultSetNumber(m_resultSetInfo.resultSet);
    m_sectionStack.push(std::make_unique<inner::SolutionsFileSection>());
}

inner::ResultFileSectionLevel RSTReader::reduceToLevel(
    const std::vector<inner::ResultFileSectionLevel> levels)
{
    // Find out what level we are currently at
    auto currentLevel = m_sectionStack.top()->getLevel();
    while (std::find(levels.begin(), levels.end(), currentLevel) == levels.end())
    {
        m_sectionStack.pop();
        currentLevel = m_sectionStack.top()->getLevel();
    }
    return currentLevel;
}

bool RSTReader::selectElementTypes()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::GeometryLevel,
        inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::ElementTypeLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        CResRdGeomBegin(&m_maxElementTypeId, &m_maxRealConstantSetId,
            &m_maxCoordinateSystemId, &m_numNodesWithCoordinates);
        m_sectionStack.push(std::make_unique<inner::GeometryFileSection>());
        level = inner::ResultFileSectionLevel::GeometryLevel;
    }
    if (level == inner::ResultFileSectionLevel::GeometryLevel)
    {
        int NumType;
        CResRdTypeBegin(&NumType);
        m_sectionStack.push(std::make_unique<inner::ElementTypeFileSection>());
    }
    return true;
}

bool RSTReader::selectRealConstants()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::GeometryLevel,
        inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::RealConstantsLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        CResRdGeomBegin(&m_maxElementTypeId, &m_maxRealConstantSetId,
            &m_maxCoordinateSystemId, &m_numNodesWithCoordinates);
        m_sectionStack.push(std::make_unique<inner::GeometryFileSection>());
        level = inner::ResultFileSectionLevel::GeometryLevel;
    }
    if (level == inner::ResultFileSectionLevel::GeometryLevel)
    {
        int NumReal, NumPerReal;
        CResRdRealBegin(&NumReal, &NumPerReal);
        m_sectionStack.push(std::make_unique<inner::RealConstantsFileSection>());
    }
    return true;
}

bool RSTReader::selectCoordinateSystems()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::GeometryLevel,
        inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::CoordinateSystemLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        CResRdGeomBegin(&m_maxElementTypeId, &m_maxRealConstantSetId,
            &m_maxCoordinateSystemId, &m_numNodesWithCoordinates);
        m_sectionStack.push(std::make_unique<inner::GeometryFileSection>());
        level = inner::ResultFileSectionLevel::GeometryLevel;
    }
    if (level == inner::ResultFileSectionLevel::GeometryLevel)
    {
        int NumCsys;
        CResRdCsysBegin(&NumCsys);
        m_sectionStack.push(std::make_unique<inner::CoordinateSystemFileSection>());
    }
    return true;
}

bool RSTReader::selectNodalCoordinates()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::GeometryLevel,
        inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::NodalCoordinatesLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        CResRdGeomBegin(&m_maxElementTypeId, &m_maxRealConstantSetId,
            &m_maxCoordinateSystemId, &m_numNodesWithCoordinates);
        m_sectionStack.push(std::make_unique<inner::GeometryFileSection>());
        level = inner::ResultFileSectionLevel::GeometryLevel;
    }
    if (level == inner::ResultFileSectionLevel::GeometryLevel)
    {
        CResRdNodeBegin();
        m_sectionStack.push(std::make_unique<inner::NodalCoordinatesFileSection>());
    }
    return true;
}

bool RSTReader::selectElementsInfo()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::GeometryLevel,
        inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::ElementsInfoLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        CResRdGeomBegin(&m_maxElementTypeId, &m_maxRealConstantSetId,
            &m_maxCoordinateSystemId, &m_numNodesWithCoordinates);
        m_sectionStack.push(std::make_unique<inner::GeometryFileSection>());
        level = inner::ResultFileSectionLevel::GeometryLevel;
    }
    if (level == inner::ResultFileSectionLevel::GeometryLevel)
    {
        CResRdElemBegin();
        m_sectionStack.push(std::make_unique<inner::ElementsInfoFileSection>());
    }
    return true;
}

bool RSTReader::selectNodalDisplacements()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::SolutionsLevel,
        inner::ResultFileSectionLevel::DisplacementsLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        setSolutionLevel();
        level = inner::ResultFileSectionLevel::SolutionsLevel;
    }
    if (level == inner::ResultFileSectionLevel::SolutionsLevel)
    {
        CResRdDispBegin();
        m_sectionStack.push(std::make_unique<inner::DisplacementsFileSection>());
    }
    return true;
}

bool RSTReader::selectReactionForces()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::SolutionsLevel,
        inner::ResultFileSectionLevel::ReactionForcesLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        setSolutionLevel();
        level = inner::ResultFileSectionLevel::SolutionsLevel;
    }
    if (level == inner::ResultFileSectionLevel::SolutionsLevel)
    {
        int nRForce;
        CResRdRforBegin(&nRForce);
        m_sectionStack.push(std::make_unique<inner::ReactionForcesFileSection>());
        if (nRForce < 0) return false;
    }
    return true;
}

bool RSTReader::selectConstraints()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::SolutionsLevel,
        inner::ResultFileSectionLevel::BoundaryConditionsLevel,
        inner::ResultFileSectionLevel::ConstraintsLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        setSolutionLevel();
        level = inner::ResultFileSectionLevel::SolutionsLevel;
    }
    if (level == inner::ResultFileSectionLevel::SolutionsLevel)
    {
        CResRdBCBegin(m_BCHeader.data());
        m_sectionStack.push(std::make_unique<inner::BoundaryConditionsFileSection>());
        level = inner::ResultFileSectionLevel::BoundaryConditionsLevel;
    }
    if (level == inner::ResultFileSectionLevel::BoundaryConditionsLevel)
    {
        int nFixed;
        CResRdFixBegin(m_BCHeader.data(), &nFixed);
        m_sectionStack.push(std::make_unique<inner::ConstraintsFileSection>());
        if (nFixed < 0) return false;
    }
    return true;
}

bool RSTReader::selectAppliedForces()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::SolutionsLevel,
        inner::ResultFileSectionLevel::BoundaryConditionsLevel,
        inner::ResultFileSectionLevel::AppliedForcesLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        setSolutionLevel();
        level = inner::ResultFileSectionLevel::SolutionsLevel;
    }
    if (level == inner::ResultFileSectionLevel::SolutionsLevel)
    {
        CResRdBCBegin(m_BCHeader.data());
        m_sectionStack.push(std::make_unique<inner::BoundaryConditionsFileSection>());
        level = inner::ResultFileSectionLevel::BoundaryConditionsLevel;
    }
    if (level == inner::ResultFileSectionLevel::BoundaryConditionsLevel)
    {
        int nForces;
        CResRdForcBegin(m_BCHeader.data(), &nForces);
        m_sectionStack.push(std::make_unique<inner::AppliedForcesSection>());
        if (nForces < 0) return false;
    }
    return true;
}

bool RSTReader::selectElementResults()
{
    auto level = reduceToLevel({ inner::ResultFileSectionLevel::BeginLevel,
        inner::ResultFileSectionLevel::SolutionsLevel,
        inner::ResultFileSectionLevel::ElementSolutionLevel });

    if (level == inner::ResultFileSectionLevel::BeginLevel)
    {
        setSolutionLevel();
        level = inner::ResultFileSectionLevel::SolutionsLevel;
    }
    if (level == inner::ResultFileSectionLevel::SolutionsLevel)
    {
        CResRdEresBegin();
        m_sectionStack.push(std::make_unique<inner::ElementSolutionSection>());
    }
    return true;
}

ElementTypeIterator RSTReader::elementTypeBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementTypeLevel &&
    "The file level stack is not correct for reading element type data!");
    return ElementTypeIterator(1, m_maxElementTypeId + 1, true);
}

ElementTypeIterator RSTReader::elementTypeEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementTypeLevel &&
        "The file level stack is not correct for reading element type data!");
    return ElementTypeIterator(m_maxElementTypeId + 1);
}

ElementTypeRange RSTReader::elementTypes()
{
    return ElementTypeRange(this);
}

RealConstantIterator RSTReader::realConstantBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::RealConstantsLevel &&
        "The file level stack is not correct for reading real constant data!");
    return RealConstantIterator(1, m_maxRealConstantSetId + 1, true);
}

RealConstantIterator RSTReader::realConstantEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::RealConstantsLevel &&
        "The file level stack is not correct for reading real constant data!");
    return RealConstantIterator(m_maxRealConstantSetId + 1);
}

RealConstantRange RSTReader::realConstants()
{
    return RealConstantRange(this);
}

CoordinateSystemIterator RSTReader::coordinateSystemBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::CoordinateSystemLevel &&
        "The file level stack is not correct for reading coordinate system data!");
    return CoordinateSystemIterator(1, m_maxCoordinateSystemId + 1, true);
}

CoordinateSystemIterator RSTReader::coordinateSystemEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::CoordinateSystemLevel &&
        "The file level stack is not correct for reading coordinate system data!");
    return CoordinateSystemIterator(m_maxCoordinateSystemId + 1);
}

CoordinateSystemRange RSTReader::coordinateSystems()
{
    return CoordinateSystemRange(this);
}

NodalCoordinatesIterator RSTReader::nodalCoordinatesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::NodalCoordinatesLevel &&
        "The file level stack is not correct for reading nodal coordinates data!");
    return NodalCoordinatesIterator(1, m_maxNodeId + 1, true);
}

NodalCoordinatesIterator RSTReader::nodalCoordinatesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::NodalCoordinatesLevel &&
        "The file level stack is not correct for reading nodal coordinates data!");
    return NodalCoordinatesIterator(m_maxNodeId + 1);
}

NodalCoordinatesRange RSTReader::nodalCoordinates()
{
    return NodalCoordinatesRange(this);
}

ElementInfoIterator RSTReader::elementInfoBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementsInfoLevel &&
        "The file level stack is not correct for reading elements data!");
    return ElementInfoIterator(1, m_maxElementId + 1, true);
}

ElementInfoIterator RSTReader::elementInfoEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementsInfoLevel &&
        "The file level stack is not correct for reading elements data!");
    return ElementInfoIterator(m_maxElementId + 1);
}

ElementInfoRange RSTReader::elementsInfo()
{
    return ElementInfoRange(this);
}

Results1DIterator RSTReader::nodalDisplacementsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::DisplacementsLevel &&
        "The file level stack is not correct for reading nodal displacements data!");
    return Results1DIterator(1, Results1DIterator::Type::NodalDisplacements,
        { m_maxNodeId + 1 }, true);
}

Results1DIterator RSTReader::nodalDisplacementsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::DisplacementsLevel &&
        "The file level stack is not correct for reading nodal displacements data!");
    return Results1DIterator(m_maxNodeId + 1, Results1DIterator::Type::NodalDisplacements,
        { -1 }, false);
}

NodalDisplacementsRange RSTReader::nodalDisplacements()
{
    return NodalDisplacementsRange(this);
}

Results1DIterator RSTReader::reactionForcesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ReactionForcesLevel &&
        "The file level stack is not correct for reading reaction forces data!");
    return Results1DIterator(1, Results1DIterator::Type::ReactionForces, { m_maxNodeId + 1, m_numDOF }, true);
}

iterators::Results1DIterator RSTReader::reactionForcesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ReactionForcesLevel &&
        "The file level stack is not correct for reading reaction forces data!");
    return iterators::Results1DIterator(m_maxNodeId + 1, Results1DIterator::Type::ReactionForces,
        { -1, m_numDOF }, false);
}

ReactionForcesRange RSTReader::reactionForces()
{
    return ReactionForcesRange(this);
}

Results1DIterator RSTReader::constraintsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ConstraintsLevel &&
        "The file level stack is not correct for reading constraints data!");
    return Results1DIterator(1, Results1DIterator::Type::Constraints,
        { m_maxNodeId + 1, m_numDOF, m_BCHeader[6] }, true);
}

Results1DIterator RSTReader::constraintsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ConstraintsLevel &&
        "The file level stack is not correct for reading constraints data!");
    return Results1DIterator(m_maxNodeId + 1, Results1DIterator::Type::Constraints,
        { m_maxNodeId + 1, m_numDOF, m_BCHeader[6] }, false);
}

ConstraintsRange RSTReader::constraints()
{
    return ConstraintsRange(this);
}

Results1DIterator RSTReader::appliedForcesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::AppliedForcesLevel &&
        "The file level stack is not correct for reading applied forces data!");
    return Results1DIterator(1, Results1DIterator::Type::AppliedForces,
        { m_maxNodeId + 1, m_numDOF, m_BCHeader[6] }, true);
}

Results1DIterator RSTReader::appliedForcesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::AppliedForcesLevel &&
        "The file level stack is not correct for reading applied forces data!");
    return Results1DIterator(m_maxNodeId + 1, Results1DIterator::Type::AppliedForces,
        { m_maxNodeId + 1, m_numDOF, m_BCHeader[6] }, false);
}

AppliedForcesRange RSTReader::appliedForces()
{
    return AppliedForcesRange(this);
}

Results1DIterator RSTReader::miscellaneousBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading miscellaneous data!");
    return Results1DIterator(1, Results1DIterator::Type::MiscellaneousData,
        {m_maxElementId + 1}, true);
}

Results1DIterator RSTReader::miscellaneousEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading miscellaneous data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::MiscellaneousData,
        {}, false);
}

MiscellaneousRange RSTReader::miscellaneousData()
{
    return MiscellaneousRange(this);
}

Results1DIterator RSTReader::elementForcesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element forces data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementForces,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementForcesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element forces data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementForces,
        { m_maxElementId + 1 }, false);
}

ElementForcesRange RSTReader::elementForces()
{
    return ElementForcesRange(this);
}

Results1DIterator RSTReader::elementStressesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element stresses data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementStresses,
        { m_maxElementId + 1 }, true);
}

Results1DIterator arf::RSTReader::elementStressesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element stresses data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementStresses,
        { m_maxElementId + 1 }, false);
}

ElementStressesRange RSTReader::elementStresses()
{
    return ElementStressesRange(this);
}

Results1DIterator RSTReader::elementVolumeEnergiesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element volume and energies data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementVolumeAndEnergies,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementVolumeEnergiesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element volume and energies data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementVolumeAndEnergies,
        { m_maxElementId + 1 }, false);
}

ElementVolumeEnergiesRange RSTReader::elementVolumeAndEnergies()
{
    return ElementVolumeEnergiesRange(this);
}

Results1DIterator RSTReader::elementFieldGradientsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element field gradients data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementFieldGradients,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementFieldGradientsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element field gradients data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementFieldGradients,
        { m_maxElementId + 1 }, false);
}

ElementFieldGradientsRange RSTReader::elementFieldGradients()
{
    return ElementFieldGradientsRange(this);
}

Results1DIterator RSTReader::elementElasticStrainsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element elastic strains data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementElasticStrains,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementElasticStrainsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element elastic strains data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementElasticStrains,
        { m_maxElementId + 1 }, false);
}

ElementElasticStrainsRange RSTReader::elementElasticStrains()
{
    return ElementElasticStrainsRange(this);
}

Results1DIterator RSTReader::elementPlasticStrainsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element plastic strains data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementPlasticStrains,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementPlasticStrainsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element plastic strains data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementPlasticStrains,
        { m_maxElementId + 1 }, false);
}

ElementPlasticStrainsRange RSTReader::elementPlasticStrains()
{
    return ElementPlasticStrainsRange(this);
}

Results1DIterator RSTReader::elementCreepStrainsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element creep strains data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementCreepStrains,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementCreepStrainsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element creep strains data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementCreepStrains,
        { m_maxElementId + 1 }, false);
}

ElementCreepStrainsRange RSTReader::elementCreepStrains()
{
    return ElementCreepStrainsRange(this);
}

Results1DIterator RSTReader::elementThermalStrainsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element thermal strains data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementThermalStrains,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementThermalStrainsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element thermal strains data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementThermalStrains,
        { m_maxElementId + 1 }, false);
}

ElementThermalStrainsRange RSTReader::elementThermalStrains()
{
    return ElementThermalStrainsRange(this);
}

Results1DIterator RSTReader::elementEulerAnglesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element Euler angles data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementEulerAngles,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementEulerAnglesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element Euler angles data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementEulerAngles,
        { m_maxElementId + 1 }, false);
}

ElementEulerAnglesRange RSTReader::elementEulerAngles()
{
    return ElementEulerAnglesRange(this);
}

Results1DIterator RSTReader::elementFieldFluxesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element field fluxes data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementFieldFluxes,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementFieldFluxesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element field fluxes data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementFieldFluxes,
        { m_maxElementId + 1 }, false);
}

ElementFieldFluxesRange RSTReader::elementFieldFluxes()
{
    return ElementFieldFluxesRange(this);
}

Results1DIterator RSTReader::elementCoupledFieldForcesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element coupled field forces data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementCoupledFieldForces,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementCoupledFieldForcesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element coupled field forces data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementCoupledFieldForces,
        { m_maxElementId + 1 }, false);
}

ElementCoupledFieldForcesRange RSTReader::elementCoupledFieldForces()
{
    return ElementCoupledFieldForcesRange(this);
}

Results1DIterator RSTReader::elementNonsummableMiscDataBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element nonsummable miscellaneous data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementNonsummableMiscData,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementNonsummableMiscDataEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element nonsummable miscellaneous data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementNonsummableMiscData,
        { m_maxElementId + 1 }, false);
}

ElementNonsummableMiscDataRange RSTReader::elementNonsumMiscData()
{
    return ElementNonsummableMiscDataRange(this);
}

Results1DIterator RSTReader::elementDensitiesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element densities data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementDensities,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementDensitiesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element densities data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementDensities,
        { m_maxElementId + 1 }, false);
}

ElementDensitiesRange RSTReader::elementDensities()
{
    return ElementDensitiesRange(this);
}

Results1DIterator RSTReader::elementNonlinearDataBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element nonlinear data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementNonlinearData,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementNonlinearDataEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element nonlinear data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementNonlinearData,
        { m_maxElementId + 1 }, false);
}

ElementNonlinearDataRange RSTReader::elementNonlinearData()
{
    return ElementNonlinearDataRange(this);
}

Results1DIterator RSTReader::elementHeatGenerationBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element heat generation data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementHeatGeneration,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementHeatGenerationEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element heat generation data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementHeatGeneration,
        { m_maxElementId + 1 }, false);
}

ElementHeatGenerationRange RSTReader::elementHeatGeneration()
{
    return ElementHeatGenerationRange(this);
}

Results1DIterator RSTReader::elementTemperaturesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element temperatures data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementTemperatures,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementTemperaturesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element temperatures data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementTemperatures,
        { m_maxElementId + 1 }, false);
}

ElementTemperaturesRange RSTReader::elementTemperatures()
{
    return ElementTemperaturesRange(this);
}

Results1DIterator RSTReader::elementSurfaceStressesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element surface stresses data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementSurfaceStresses,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementSurfaceStressesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element surface stresses data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementSurfaceStresses,
        { m_maxElementId + 1 }, false);
}

ElementSurfaceStressesRange RSTReader::elementSurfaceStresses()
{
    return ElementSurfaceStressesRange(this);
}

Results1DIterator RSTReader::elementDiffusionStrainsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element diffusion strains data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementDiffusionStrains,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementDiffusionStrainsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element diffusion strains data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementDiffusionStrains,
        { m_maxElementId + 1 }, false);
}

ElementDiffusionStrainsRange RSTReader::elementDiffusionStrains()
{
    return ElementDiffusionStrainsRange(this);
}

Results1DIterator RSTReader::elementTablesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element tables data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementTable,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementTablesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element tables data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementTable,
        { m_maxElementId + 1 }, false);
}

ElementTablesRange RSTReader::elementTables()
{
    return ElementTablesRange(this);
}

Results1DIterator RSTReader::elementContactResultsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element contact results!");
    return Results1DIterator(1, Results1DIterator::Type::ElementContactResults,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementContactResultsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element contact results!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementContactResults,
        { m_maxElementId + 1 }, false);
}

ElementContactResultsRange RSTReader::elementContactResults()
{
    return ElementContactResultsRange(this);
}

Results1DIterator RSTReader::elementIntPointCoordsBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element integration point coordinates data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementIntegrationPointCoord,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementIntPointCoordsEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element integration point coordinates data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementIntegrationPointCoord,
        { m_maxElementId + 1 }, false);
}

ElementIntPointCoordsRange RSTReader::elementIntPointCoords()
{
    return ElementIntPointCoordsRange(this);
}

Results1DIterator RSTReader::elementBackStressesBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element back stresses data!");
    return Results1DIterator(1, Results1DIterator::Type::ElementBackStresses,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementBackStressesEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element back stresses data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementBackStresses,
        { m_maxElementId + 1 }, false);
}

ElementBackStressesRange RSTReader::elementBackStresses()
{
    return ElementBackStressesRange(this);
}

Results1DIterator RSTReader::elementStateVariableBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element state variable!");
    return Results1DIterator(1, Results1DIterator::Type::ElementStateVariable,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::elementStateVariableEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element state variable!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::ElementStateVariable,
        { m_maxElementId + 1 }, false);
}

ElementStateVariableRange RSTReader::elementStateVariable()
{
    return ElementStateVariableRange(this);
}

Results1DIterator RSTReader::materialsNonlinearBegin() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element material nonlinear data!");
    return Results1DIterator(1, Results1DIterator::Type::MaterialNonlinearRecord,
        { m_maxElementId + 1 }, true);
}

Results1DIterator RSTReader::materialsNonlinearEnd() const
{
    assert(m_sectionStack.top()->getLevel() ==
        inner::ResultFileSectionLevel::ElementSolutionLevel &&
        "The file level stack is not correct for reading element material nonlinear data!");
    return Results1DIterator(m_maxElementId + 1, Results1DIterator::Type::MaterialNonlinearRecord,
        { m_maxElementId + 1 }, false);
}

MaterialsNonlinearRange RSTReader::materialNonlinearData()
{
    return MaterialsNonlinearRange(this);
}

