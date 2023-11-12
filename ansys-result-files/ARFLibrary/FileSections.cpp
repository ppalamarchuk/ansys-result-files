#include "pch.h"
#include "FileSections.h"
#include "CResRd.h"

using namespace arf::inner;

BeginFileSection::~BeginFileSection()
{
    arf::subroutines::CResRdEnd();
}

ResultFileSectionLevel BeginFileSection::getLevel() const
{
    return ResultFileSectionLevel::BeginLevel;
}

GeometryFileSection::~GeometryFileSection()
{
    arf::subroutines::CResRdGeomEnd();
}

ResultFileSectionLevel GeometryFileSection::getLevel() const
{
    return ResultFileSectionLevel::GeometryLevel;
}

ElementTypeFileSection::~ElementTypeFileSection()
{
    arf::subroutines::CResRdTypeEnd();
}

ResultFileSectionLevel ElementTypeFileSection::getLevel() const
{
    return ResultFileSectionLevel::ElementTypeLevel;
}

RealConstantsFileSection::~RealConstantsFileSection()
{
    arf::subroutines::CResRdRealEnd();
}

ResultFileSectionLevel RealConstantsFileSection::getLevel() const
{
    return ResultFileSectionLevel::RealConstantsLevel;
}

CoordinateSystemFileSection::~CoordinateSystemFileSection()
{
    arf::subroutines::CResRdCsysEnd();
}

ResultFileSectionLevel CoordinateSystemFileSection::getLevel() const
{
    return ResultFileSectionLevel::CoordinateSystemLevel;
}

NodalCoordinatesFileSection::~NodalCoordinatesFileSection()
{
    arf::subroutines::CResRdNodeEnd();
}

ResultFileSectionLevel NodalCoordinatesFileSection::getLevel() const
{
    return ResultFileSectionLevel::NodalCoordinatesLevel;
}

ElementsInfoFileSection::~ElementsInfoFileSection()
{
    arf::subroutines::CResRdElemEnd();
}

ResultFileSectionLevel ElementsInfoFileSection::getLevel() const
{
    return ResultFileSectionLevel::ElementsInfoLevel;
}

SolutionsFileSection::~SolutionsFileSection()
{
    arf::subroutines::CResRdSolEnd();
}

ResultFileSectionLevel SolutionsFileSection::getLevel() const
{
    return ResultFileSectionLevel::SolutionsLevel;
}

DisplacementsFileSection::~DisplacementsFileSection()
{
    arf::subroutines::CResRdDispEnd();
}

ResultFileSectionLevel DisplacementsFileSection::getLevel() const
{
    return ResultFileSectionLevel::DisplacementsLevel;
}

ReactionForcesFileSection::~ReactionForcesFileSection()
{
    arf::subroutines::CResRdRforEnd();
}

ResultFileSectionLevel ReactionForcesFileSection::getLevel() const
{
    return ResultFileSectionLevel::ReactionForcesLevel;
}

BoundaryConditionsFileSection::~BoundaryConditionsFileSection()
{
    arf::subroutines::CResRdBCEnd();
}

ResultFileSectionLevel BoundaryConditionsFileSection::getLevel() const
{
    return ResultFileSectionLevel::BoundaryConditionsLevel;
}

ConstraintsFileSection::~ConstraintsFileSection()
{
    arf::subroutines::CResRdFixEnd();
}

ResultFileSectionLevel ConstraintsFileSection::getLevel() const
{
    return ResultFileSectionLevel::ConstraintsLevel;
}

AppliedForcesSection::~AppliedForcesSection()
{
    arf::subroutines::CResRdForcEnd();
}

ResultFileSectionLevel AppliedForcesSection::getLevel() const
{
    return ResultFileSectionLevel::AppliedForcesLevel;
}

ElementSolutionSection::~ElementSolutionSection()
{
    arf::subroutines::CResRdEresEnd();
}

ResultFileSectionLevel ElementSolutionSection::getLevel() const
{
    return ResultFileSectionLevel::ElementSolutionLevel;
}

