#include "pch.h"
#include "Tools.h"
#include "CResRd.h"
#include "RSTReader.h"

using namespace arf::structures;
using namespace arf::iterators;
using namespace arf::subroutines;


ElementTypeIterator::ElementTypeIterator(const ElementTypeIterator& other)
    : m_currentIndex(other.m_currentIndex)
    , m_maxIndex(other.m_maxIndex)
{
    m_ptr = std::make_unique<ElementType>();
    m_ptr->nodelm = other.m_ptr->nodelm;
    m_ptr->nodfor = other.m_ptr->nodfor;
    m_ptr->nodstr = other.m_ptr->nodstr;
    m_ptr->referenceNumber = other.m_ptr->referenceNumber;
    m_ptr->routineNumber = other.m_ptr->routineNumber;
    m_ptr->isValid = other.m_ptr->isValid;
}

ElementTypeIterator::ElementTypeIterator(int index, int maxIndex, bool read)
    : m_currentIndex(index)
    , m_maxIndex(maxIndex)
{
    m_ptr = std::make_unique<ElementType>();
    m_ptr->nodelm = m_ptr->nodfor = m_ptr->nodstr =
        m_ptr->referenceNumber = m_ptr->routineNumber = -1;
    m_ptr->isValid = false;
    if (read && index < maxIndex) readData();
}

ElementType& ElementTypeIterator::operator*() const
{
    return *m_ptr;
}

ElementType* ElementTypeIterator::operator->()
{
    return m_ptr.get();
}

ElementTypeIterator& ElementTypeIterator::operator++()
{
    m_currentIndex++;
    if (m_currentIndex != m_maxIndex)
        readData();
    return *this;
}

void ElementTypeIterator::readData()
{
    int ielc[IELCSZ];
    int n = CResRdType(&m_currentIndex, ielc);
    if (n > 0)
    {
        m_ptr->nodelm = ielc[60];
        m_ptr->nodfor = ielc[62];
        m_ptr->nodstr = ielc[93];
        m_ptr->referenceNumber = ielc[0];
        m_ptr->routineNumber = ielc[1];
        m_ptr->isValid = true;
    }
    else
    {
        m_ptr->isValid = false;
    }
}

RealConstantIterator::RealConstantIterator(const RealConstantIterator& other)
    : m_currentIndex(other.m_currentIndex)
    , m_maxIndex(other.m_maxIndex)
{
    m_ptr = std::make_unique<RealConstant>();
    m_ptr->realSetNumber = other.m_ptr->realSetNumber;
    m_ptr->data = other.m_ptr->data;
    m_ptr->isValid = other.m_ptr->isValid;
}

RealConstantIterator::RealConstantIterator(int index, int maxIndex, bool read)
    : m_currentIndex(index)
    , m_maxIndex(maxIndex)
{
    m_ptr = std::make_unique<RealConstant>();
    m_ptr->data.resize(MAXREALS);
    m_ptr->isValid = false;
    if (read && index < maxIndex) readData();
}

RealConstant& RealConstantIterator::operator*() const
{
    return *m_ptr;
}

RealConstant* RealConstantIterator::operator->()
{
    return m_ptr.get();
}

RealConstantIterator& RealConstantIterator::operator++()
{
    m_currentIndex++;
    if (m_currentIndex != m_maxIndex)
        readData();
    return *this;
}

void RealConstantIterator::readData()
{
    m_ptr->data.resize(MAXREALS);
    int n = CResRdReal(&m_currentIndex, m_ptr->data.data());
    if (n > 0 && n < MAXREALS)
    {
        m_ptr->realSetNumber = m_currentIndex;
        m_ptr->data.resize(n);
        m_ptr->isValid = true;
    }
    else
    {
        m_ptr->isValid = false;
    }
}

CoordinateSystemIterator::CoordinateSystemIterator(const CoordinateSystemIterator& other)
    : m_currentIndex(other.m_currentIndex)
    , m_maxIndex(other.m_maxIndex)
{
    m_ptr = std::make_unique<CoordinateSystem>();
    m_ptr->angles = other.m_ptr->angles;
    m_ptr->csNumber = other.m_ptr->csNumber;
    m_ptr->isValid = other.m_ptr->isValid;
    m_ptr->origin = other.m_ptr->origin;
    m_ptr->parameters = other.m_ptr->parameters;
    m_ptr->phiSingulatityKey = other.m_ptr->phiSingulatityKey;
    m_ptr->referenceNumber = other.m_ptr->referenceNumber;
    m_ptr->thetaSingularityKey = other.m_ptr->thetaSingularityKey;
    m_ptr->transformationMatrix = other.m_ptr->transformationMatrix;
    m_ptr->type = other.m_ptr->type;
}

CoordinateSystemIterator::CoordinateSystemIterator(int index, int maxIndex, bool read)
    : m_currentIndex(index)
    , m_maxIndex(maxIndex)
{
    m_ptr = std::make_unique<CoordinateSystem>();
    m_ptr->isValid = false;
    if (read && index < maxIndex) readData();
}

CoordinateSystem& CoordinateSystemIterator::operator*() const
{
    return *m_ptr;
}

CoordinateSystem* CoordinateSystemIterator::operator->()
{
    return m_ptr.get();
}

CoordinateSystemIterator& CoordinateSystemIterator::operator++()
{
    m_currentIndex++;
    if (m_currentIndex != m_maxIndex)
        readData();
    return *this;
}

void CoordinateSystemIterator::readData()
{
    std::vector<double> description;
    description.resize(MAXREALS);
    int n = CResRdCsys(&m_currentIndex, description.data());
    if (n > 0)
    {
        std::copy(description.begin(), description.begin() + 9,
            m_ptr->transformationMatrix.begin());
        std::copy(description.begin() + 10, description.begin() + 12,
            m_ptr->origin.begin());
        std::copy(description.begin() + 13, description.begin() + 14,
            m_ptr->parameters.begin());
        std::copy(description.begin() + 16, description.begin() + 18,
            m_ptr->angles.begin());
        m_ptr->thetaSingularityKey = description.at(18);
        m_ptr->phiSingulatityKey = description.at(19);
        m_ptr->type = description.at(20);
        m_ptr->referenceNumber = description.at(21);
        m_ptr->isValid = true;
    }
    else
    {
        m_ptr->isValid = false;
    }
}

NodalCoordinatesIterator::NodalCoordinatesIterator(
    const NodalCoordinatesIterator& other)
    : m_currentIndex(other.m_currentIndex)
    , m_maxIndex(other.m_maxIndex)
{
    m_ptr = std::make_unique<NodalCoordinates>();
    m_ptr->nodeNumber = other.m_ptr->nodeNumber;
    m_ptr->coordinates = other.m_ptr->coordinates;
    m_ptr->rotations = other.m_ptr->rotations;
    m_ptr->isValid = other.m_ptr->isValid;
}

NodalCoordinatesIterator::NodalCoordinatesIterator(int index, int maxIndex, bool read)
    : m_currentIndex(index)
    , m_maxIndex(maxIndex)
{
    m_ptr = std::make_unique<NodalCoordinates>();
    m_ptr->nodeNumber = -1;
    if (read && index < maxIndex) readData();
}

NodalCoordinates& NodalCoordinatesIterator::operator*() const
{
    return *m_ptr;
}

NodalCoordinates* NodalCoordinatesIterator::operator->()
{
    return m_ptr.get();
}

NodalCoordinatesIterator& NodalCoordinatesIterator::operator++()
{
    m_currentIndex++;
    if (m_currentIndex != m_maxIndex)
        readData();
    return *this;
}

void NodalCoordinatesIterator::readData()
{
    std::vector<double> data;
    data.resize(6);
    int n = CResRdNode(&m_currentIndex, data.data());
    if (n > 0)
    {
        m_ptr->nodeNumber = n;
        std::copy(data.begin(), data.begin() + 3, m_ptr->coordinates.begin());
        std::copy(data.begin() + 3, data.begin() + 6, m_ptr->rotations.begin());
        m_ptr->isValid = true;
    }
    else
    {
        m_ptr->isValid = false;
    }
}

ElementInfoIterator::ElementInfoIterator(const ElementInfoIterator& other)
    : m_currentIndex(other.m_currentIndex)
    , m_maxIndex(other.m_maxIndex)
{
    m_ptr = std::make_unique<ElementInfo>();
    m_ptr->baseElemId = other.m_ptr->baseElemId;
    m_ptr->coordSystemId = other.m_ptr->coordSystemId;
    m_ptr->deathFlag = other.m_ptr->deathFlag;
    m_ptr->elementNumber = other.m_ptr->elementNumber;
    m_ptr->elementType = other.m_ptr->elementType;
    m_ptr->isValid = other.m_ptr->isValid;
    m_ptr->materialId = other.m_ptr->materialId;
    m_ptr->nodes = other.m_ptr->nodes;
    m_ptr->realConstantId = other.m_ptr->realConstantId;
    m_ptr->sectionNumber = other.m_ptr->sectionNumber;
    m_ptr->shape = other.m_ptr->shape;
    m_ptr->solidModelId = other.m_ptr->solidModelId;
}

ElementInfoIterator::ElementInfoIterator(int index, int maxIndex, bool read)
    : m_currentIndex(index)
    , m_maxIndex(maxIndex)
{
    m_ptr = std::make_unique<ElementInfo>();
    m_ptr->isValid = false;
    if (read && index < maxIndex) readData();
}

ElementInfo& ElementInfoIterator::operator*() const
{
    return *m_ptr;
}

ElementInfo* ElementInfoIterator::operator->()
{
    return m_ptr.get();
}

ElementInfoIterator& ElementInfoIterator::operator++()
{
    m_currentIndex++;
    if (m_currentIndex != m_maxIndex)
        readData();
    return *this;
}

void ElementInfoIterator::readData()
{
    int ElemData[10];
    m_ptr->nodes.resize(MAXNODESPERELEM);

    int n = CResRdElem(&m_currentIndex, m_ptr->nodes.data(), ElemData);
    if (n > 0)
    {
        m_ptr->nodes.resize(n);
        m_ptr->materialId = ElemData[0];
        m_ptr->elementType = ElemData[1];
        m_ptr->realConstantId = ElemData[2];
        m_ptr->sectionNumber = ElemData[3];
        m_ptr->coordSystemId = ElemData[4];
        m_ptr->deathFlag = ElemData[5];
        m_ptr->solidModelId = ElemData[6];
        m_ptr->shape = ElemData[7];
        m_ptr->elementNumber = ElemData[8];
        m_ptr->isValid = true;
    }
    else
    {
        m_ptr->isValid = false;
    }
}

Results1DIterator::Results1DIterator(const Results1DIterator& other)
    : m_currentIndex(other.m_currentIndex)
    , m_params(other.m_params)
    , m_type(other.m_type)
{
    m_ptr->data = other.m_ptr->data;
    m_ptr->id = other.m_ptr->id;
    m_ptr->isValid = other.m_ptr->isValid;
}

Results1DIterator::Results1DIterator(int index, Type type,
    const std::vector<int>& params, bool read)
    : m_currentIndex(index)
    , m_params(params)
    , m_type(type)
{
    m_ptr = std::make_unique<Results1D>();
    m_ptr->isValid = false;
    if (read && index < m_params.at(0)) readData();
}

Results1D& Results1DIterator::operator*() const
{
    return *m_ptr;
}

Results1D* Results1DIterator::operator->()
{
    return m_ptr.get();
}

Results1DIterator& Results1DIterator::operator++()
{
    m_currentIndex++;
    if (m_currentIndex != m_params.at(0))
        readData();
    return *this;
}

void Results1DIterator::readData()
{
    if (m_type == Type::NodalDisplacements)
    {
        m_ptr->data.resize(MAXDOFSPERNODE);
        int n = CResRdDisp(&m_currentIndex, m_ptr->data.data());
        if (n > 0)
        {
            m_ptr->data.resize(n);
            m_ptr->id = m_currentIndex;
            m_ptr->isValid = true;
        }
        else
        {
            m_ptr->isValid = false;
        }
    }
    else if (m_type == Type::ReactionForces)
    {
        int counter = 0;
        m_ptr->data.clear();
        for (int i = 1; i < m_params.at(1) + 1; i++)
        {
            double value;
            counter += CResRdRfor(&m_currentIndex, &i, &value);
            m_ptr->id = m_currentIndex;
            m_ptr->data.push_back(value);
        }
        m_ptr->isValid = (counter == m_params.at(1));
    }
    else if (m_type == Type::Constraints)
    {
        int counter = 0;
        m_ptr->data.clear();
        std::array<double, 4> values;
        for (int i = 1; i < m_params.at(1) + 1; i++)
        {
            int k = (m_params.at(2) == 0) ?
                CResRdFixOld(&m_currentIndex, &i, values.data()) :
                CResRdFix(&m_currentIndex, &i, values.data());
            counter += k;
            m_ptr->data.insert(m_ptr->data.end(), values.begin(), values.end());
            m_ptr->id = m_currentIndex;
        }
        m_ptr->isValid = (counter == m_params.at(1));
    }
    else if (m_type == Type::AppliedForces)
    {
        int counter = 0;
        m_ptr->data.clear();
        std::array<double, 4> values;
        for (int i = 1; i < m_params.at(1) + 1; i++)
        {
            int k = (m_params.at(2) == 0) ?
                CResRdForcOld(&m_currentIndex, &i, values.data()) :
                arf::subroutines::CResRdForc(&m_currentIndex, &i, values.data());
            counter += k;
            m_ptr->data.insert(m_ptr->data.end(), values.begin(), values.end());
            m_ptr->id = m_currentIndex;
        }
        m_ptr->isValid = (counter == m_params.at(1));
    }
    else if (m_type == Type::MiscellaneousData)
    {
        readElementResult(1);
    }
    else if (m_type == Type::ElementForces)
    {
        readElementResult(2);
    }
    else if (m_type == Type::ElementStresses)
    {
        readElementResult(3);
    }
    else if (m_type == Type::ElementVolumeAndEnergies)
    {
        readElementResult(4);
    }
    else if (m_type == Type::ElementFieldGradients)
    {
        readElementResult(5);
    }
    else if (m_type == Type::ElementElasticStrains)
    {
        readElementResult(6);
    }
    else if (m_type == Type::ElementPlasticStrains)
    {
        readElementResult(7);
    }
    else if (m_type == Type::ElementCreepStrains)
    {
        readElementResult(8);
    }
    else if (m_type == Type::ElementThermalStrains)
    {
        readElementResult(9);
    }
    else if (m_type == Type::ElementEulerAngles)
    {
        readElementResult(10);
    }
    else if (m_type == Type::ElementFieldFluxes)
    {
        readElementResult(11);
    }
    else if (m_type == Type::ElementCoupledFieldForces)
    {
        readElementResult(12);
    }
    else if (m_type == Type::ElementNonsummableMiscData)
    {
        readElementResult(13);
    }
    else if (m_type == Type::ElementDensities)
    {
        readElementResult(14);
    }
    else if (m_type == Type::ElementNonlinearData)
    {
        readElementResult(15);
    }
    else if (m_type == Type::ElementHeatGeneration)
    {
        readElementResult(16);
    }
    else if (m_type == Type::ElementTemperatures)
    {
        readElementResult(17);
    }
    else if (m_type == Type::ElementSurfaceStresses)
    {
        readElementResult(18);
    }
    else if (m_type == Type::ElementDiffusionStrains)
    {
        readElementResult(19);
    }
    else if (m_type == Type::ElementTable)
    {
        readElementResult(20);
    }
    else if (m_type == Type::ElementContactResults)
    {
        readElementResult(21);
    }
    else if (m_type == Type::ElementIntegrationPointCoord)
    {
        readElementResult(22);
    }
    else if (m_type == Type::ElementBackStresses)
    {
        readElementResult(23);
    }
    else if (m_type == Type::ElementStateVariable)
    {
        readElementResult(24);
    }
    else if (m_type == Type::MaterialNonlinearRecord)
    {
        readElementResult(25);
    }
}

void Results1DIterator::readElementResult(int record)
{
    int kerr = CResRdEstrBegin(&m_currentIndex);
    if (kerr == 0)
    {
        m_ptr->data.resize(MAXELERECORD);
        int nValues = CResRdEstr(&record, m_ptr->data.data());
        m_ptr->data.resize(nValues);
        m_ptr->id = m_currentIndex;
        m_ptr->isValid = (nValues > 0);
    }
    else
    {
        m_ptr->isValid = false;
    }
    arf::subroutines::CResRdEstrEnd();
}

ElementTypeRange::ElementTypeRange(RSTReader* container)
    : m_container(container)
{ }

ElementTypeIterator ElementTypeRange::begin() const
{
    return m_container->elementTypeBegin();
}

ElementTypeIterator ElementTypeRange::end() const
{
    return m_container->elementTypeEnd();
}

RealConstantRange::RealConstantRange(RSTReader* container)
    : m_container(container)
{ }

RealConstantIterator RealConstantRange::begin() const
{
    return m_container->realConstantBegin();
}

RealConstantIterator RealConstantRange::end() const
{
    return m_container->realConstantEnd();
}

CoordinateSystemRange::CoordinateSystemRange(RSTReader* container)
    : m_container(container)
{ }

CoordinateSystemIterator CoordinateSystemRange::begin() const
{
    return m_container->coordinateSystemBegin();
}

CoordinateSystemIterator CoordinateSystemRange::end() const
{
    return m_container->coordinateSystemEnd();
}

NodalCoordinatesRange::NodalCoordinatesRange(RSTReader* container)
{
    m_container = container;
}

NodalCoordinatesIterator NodalCoordinatesRange::begin() const
{
    return m_container->nodalCoordinatesBegin();
}

NodalCoordinatesIterator NodalCoordinatesRange::end() const
{
    return m_container->nodalCoordinatesEnd();
}

ElementInfoRange::ElementInfoRange(RSTReader* container)
    : m_container(container)
{ }

ElementInfoIterator ElementInfoRange::begin() const
{
    return m_container->elementInfoBegin();
}

ElementInfoIterator ElementInfoRange::end() const
{
    return m_container->elementInfoEnd();
}

NodalDisplacementsRange::NodalDisplacementsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator NodalDisplacementsRange::begin() const
{
    return m_container->nodalDisplacementsBegin();
}

Results1DIterator NodalDisplacementsRange::end() const
{
    return m_container->nodalDisplacementsEnd();
}

ReactionForcesRange::ReactionForcesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ReactionForcesRange::begin() const
{
    return m_container->reactionForcesBegin();
}

Results1DIterator ReactionForcesRange::end() const
{
    return m_container->reactionForcesEnd();
}

ConstraintsRange::ConstraintsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ConstraintsRange::begin() const
{
    return m_container->constraintsBegin();
}

Results1DIterator ConstraintsRange::end() const
{
    return m_container->constraintsEnd();
}

AppliedForcesRange::AppliedForcesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator AppliedForcesRange::begin() const
{
    return m_container->appliedForcesBegin();
}

Results1DIterator AppliedForcesRange::end() const
{
    return m_container->appliedForcesEnd();
}

MiscellaneousRange::MiscellaneousRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator MiscellaneousRange::begin() const
{
    return m_container->miscellaneousBegin();
}

Results1DIterator MiscellaneousRange::end() const
{
    return m_container->miscellaneousEnd();
}

ElementForcesRange::ElementForcesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementForcesRange::begin() const
{
    return m_container->elementForcesBegin();
}

Results1DIterator ElementForcesRange::end() const
{
    return m_container->elementForcesEnd();
}

ElementStressesRange::ElementStressesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementStressesRange::begin() const
{
    return m_container->elementStressesBegin();
}

Results1DIterator ElementStressesRange::end() const
{
    return m_container->elementStressesEnd();
}

ElementVolumeEnergiesRange::ElementVolumeEnergiesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementVolumeEnergiesRange::begin() const
{
    return m_container->elementVolumeEnergiesBegin();
}

Results1DIterator ElementVolumeEnergiesRange::end() const
{
    return m_container->elementVolumeEnergiesEnd();
}

ElementFieldGradientsRange::ElementFieldGradientsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementFieldGradientsRange::begin() const
{
    return m_container->elementFieldGradientsBegin();
}

Results1DIterator ElementFieldGradientsRange::end() const
{
    return m_container->elementFieldGradientsEnd();
}

ElementElasticStrainsRange::ElementElasticStrainsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementElasticStrainsRange::begin() const
{
    return m_container->elementElasticStrainsBegin();
}

Results1DIterator ElementElasticStrainsRange::end() const
{
    return m_container->elementElasticStrainsEnd();
}

ElementPlasticStrainsRange::ElementPlasticStrainsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementPlasticStrainsRange::begin() const
{
    return m_container->elementPlasticStrainsBegin();
}

Results1DIterator ElementPlasticStrainsRange::end() const
{
    return m_container->elementPlasticStrainsEnd();
}

ElementCreepStrainsRange::ElementCreepStrainsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementCreepStrainsRange::begin() const
{
    return m_container->elementCreepStrainsBegin();
}

Results1DIterator ElementCreepStrainsRange::end() const
{
    return m_container->elementCreepStrainsEnd();
}

ElementThermalStrainsRange::ElementThermalStrainsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementThermalStrainsRange::begin() const
{
    return m_container->elementThermalStrainsBegin();
}

Results1DIterator ElementThermalStrainsRange::end() const
{
    return m_container->elementThermalStrainsEnd();
}

ElementEulerAnglesRange::ElementEulerAnglesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementEulerAnglesRange::begin() const
{
    return m_container->elementEulerAnglesBegin();
}

Results1DIterator ElementEulerAnglesRange::end() const
{
    return m_container->elementEulerAnglesEnd();
}

ElementFieldFluxesRange::ElementFieldFluxesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementFieldFluxesRange::begin() const
{
    return m_container->elementFieldFluxesBegin();
}

Results1DIterator ElementFieldFluxesRange::end() const
{
    return m_container->elementFieldFluxesEnd();
}

ElementCoupledFieldForcesRange::ElementCoupledFieldForcesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementCoupledFieldForcesRange::begin() const
{
    return m_container->elementCoupledFieldForcesBegin();
}

Results1DIterator ElementCoupledFieldForcesRange::end() const
{
    return m_container->elementCoupledFieldForcesEnd();
}

ElementNonsummableMiscDataRange::ElementNonsummableMiscDataRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementNonsummableMiscDataRange::begin() const
{
    return m_container->elementNonsummableMiscDataBegin();
}

Results1DIterator ElementNonsummableMiscDataRange::end() const
{
    return m_container->elementNonsummableMiscDataEnd();
}

ElementDensitiesRange::ElementDensitiesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementDensitiesRange::begin() const
{
    return m_container->elementDensitiesBegin();
}

Results1DIterator ElementDensitiesRange::end() const
{
    return m_container->elementDensitiesEnd();
}

ElementNonlinearDataRange::ElementNonlinearDataRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementNonlinearDataRange::begin() const
{
    return m_container->elementNonlinearDataBegin();
}

Results1DIterator ElementNonlinearDataRange::end() const
{
    return m_container->elementNonlinearDataEnd();
}

ElementHeatGenerationRange::ElementHeatGenerationRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementHeatGenerationRange::begin() const
{
    return m_container->elementHeatGenerationBegin();
}

Results1DIterator ElementHeatGenerationRange::end() const
{
    return m_container->elementHeatGenerationEnd();
}

ElementTemperaturesRange::ElementTemperaturesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementTemperaturesRange::begin() const
{
    return m_container->elementTemperaturesBegin();
}

Results1DIterator ElementTemperaturesRange::end() const
{
    return m_container->elementTemperaturesEnd();
}

ElementSurfaceStressesRange::ElementSurfaceStressesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementSurfaceStressesRange::begin() const
{
    return m_container->elementSurfaceStressesBegin();
}

Results1DIterator ElementSurfaceStressesRange::end() const
{
    return m_container->elementSurfaceStressesEnd();
}

ElementDiffusionStrainsRange::ElementDiffusionStrainsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementDiffusionStrainsRange::begin() const
{
    return m_container->elementDiffusionStrainsBegin();
}

Results1DIterator ElementDiffusionStrainsRange::end() const
{
    return m_container->elementDiffusionStrainsEnd();
}

ElementTablesRange::ElementTablesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementTablesRange::begin() const
{
    return m_container->elementTablesBegin();
}

Results1DIterator ElementTablesRange::end() const
{
    return m_container->elementTablesEnd();
}

ElementContactResultsRange::ElementContactResultsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementContactResultsRange::begin() const
{
    return m_container->elementContactResultsBegin();
}

Results1DIterator ElementContactResultsRange::end() const
{
    return m_container->elementContactResultsEnd();
}

ElementIntPointCoordsRange::ElementIntPointCoordsRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementIntPointCoordsRange::begin() const
{
    return m_container->elementIntPointCoordsBegin();
}

Results1DIterator ElementIntPointCoordsRange::end() const
{
    return m_container->elementIntPointCoordsEnd();
}

ElementBackStressesRange::ElementBackStressesRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementBackStressesRange::begin() const
{
    return m_container->elementBackStressesBegin();
}

Results1DIterator ElementBackStressesRange::end() const
{
    return m_container->elementBackStressesEnd();
}

ElementStateVariableRange::ElementStateVariableRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator ElementStateVariableRange::begin() const
{
    return m_container->elementStateVariableBegin();
}

Results1DIterator ElementStateVariableRange::end() const
{
    return m_container->elementStateVariableEnd();
}

MaterialsNonlinearRange::MaterialsNonlinearRange(RSTReader* container)
    : m_container(container)
{ }

Results1DIterator MaterialsNonlinearRange::begin() const
{
    return m_container->materialsNonlinearBegin();
}

Results1DIterator MaterialsNonlinearRange::end() const
{
    return m_container->materialsNonlinearEnd();
}

