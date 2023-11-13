#pragma once

#ifdef ARFLIBRARY_EXPORTS
#define ARFLIBRARY_API __declspec(dllexport)
#else
#define ARFLIBRARY_API __declspec(dllimport)
#endif

#include <string>
#include <stack>
#include "FileSections.h"
#include "Tools.h"

namespace arf {

    class ARFLIBRARY_API RSTReader
    {
    public:
        enum class DataType
        {
            ElementTypes,               // Read an element type records.
            RealConstants,              // Read real constant records.
            CoordinateSystems,          // Read a coordinate system records.
            NodalCoordinates,           // Read a nodes' coordinates.
            ElementsInfo,               // Read list of nodes and main information about each element.
            NodalDisplacements,         // Read a nodal displacements.
            ReactionForces,             // Read reaction force DOFs.
            Constraints,                // Read nodal constraint DOF.
            AppliedForces,              // Read nodal applied forces.
            ElementResults,             // Read an element summable miscellaneous data.
        };

        RSTReader() {}
        ~RSTReader();

        RSTReader(const RSTReader&) = delete;
        RSTReader(RSTReader&&) = delete;
        RSTReader& operator=(const RSTReader&) = delete;
        RSTReader& operator=(RSTReader&&) = delete;

        // Open .rst file by given path. Return 0 if successeful
        bool open(const std::string& path);
        // Close file.
        void close();

        // Select data type to extract from binary file.
        bool select(const DataType type);
        // Select result set number to analyze (by default - last set).
        void selectResultSetNumber(int number);
        // Get information about current status of load set.
        structures::ResultSetInfo getResultSetInfo();

        // [Geometry] Iterate through element types data.
        iterators::ElementTypeRange elementTypes();
        // [Geometry] Iterate through real constants data.
        iterators::RealConstantRange realConstants();
        // [Geometry] Iterate through coordinate systems data.
        iterators::CoordinateSystemRange coordinateSystems();
        // [Geometry] Iterate through nodal coordinates data.
        iterators::NodalCoordinatesRange nodalCoordinates();
        // [Geometry] Iterate through elements data.
        iterators::ElementInfoRange elementsInfo();
        // [Solution] Iterate through nodal displacements data.
        iterators::NodalDisplacementsRange nodalDisplacements();
        // [Boundary Conditions] Iterate through nodal reaction forces.
        iterators::ReactionForcesRange reactionForces();
        // [Boundary Conditions] Iterate through nodal constraint DOF.
        iterators::ConstraintsRange constraints();
        // [Boundary Conditions] Iterate through nodal applied forces.
        iterators::AppliedForcesRange appliedForces();
        // [Solution] Iterate through elements summable miscellaneous data. The contents
        // and number of data items is element-dependent. For a list of what's available,
        // see the SMICS item in the description of the ETABLE command in the ANSYS
        // Commands Reference.
        iterators::MiscellaneousRange miscellaneousData();
        // [Solution] Iterate through elements nodal forces. Each record contains the forces
        // at each node, in the same DOF order as the DOF number reference table. For static,
        // damping, and inertia forces, a set of forces will be repeated (as appropriate).
        // Number of data items: nodfor*NDOF*M, where NDOF is the number of DOFs/node for
        // this element, nodfor is the number of nodes per element having nodal forces
        // (defined in element description record), and M may be 1, 2, or 3. For a static
        // analysis, M = 1 only. For transient analysis, M can be 1, 2, or 3.
        iterators::ElementForcesRange elementForces();
        // [Solution] Iterate through elements nodal component stresses. Each record contains
        // the stresses at each corner node, in the order SX, SY, SZ, SXY, SYZ, SXZ. Nodal
        // order corresponds to the connectivity defined in the element description. Stresses
        // can be nodal values extrapolated from the integration points or values at the
        // integration points moved to the nodes. If an element is nonlinear, integration
        // point values always will be written. An element is considered nonlinear when either
        // plastic, creep, or swelling strains are present.
        iterators::ElementStressesRange elementStresses();
        // [Solution] Iterate through elements volume and energies. Each record contains
        // 11 items: volume, senergy, aenergy, kenergy, coenergy, incenergy, 0.0, 0.0,
        // thenergy, 0.0, 0.0. Where volume - element volume, senergy - element energy
        // associated with the stiffness matrix, aenergy - artificial hourglass energy,
        // kenergy - kinetic energy, coenergy - co-energy (magnetics), incenergy - 
        // incremental energy (magnetics), thenergy - thermal dissipation energy (see TherMat,
        // shell131/132 only, 0.0 - position not used.
        iterators::ElementVolumeEnergiesRange elementVolumeAndEnergies();
        // [Solution] Iterate through elements nodal field gradients. Each record contains
        // the gradients at each corner node in the order X, Y, Z. Nodal order corresponds
        // to the connectivity defined in the element description. If this is a coupled-field
        // analysis, the data is stored in the following order (as available): fluid, thermal
        // (TEMP), electric (VOLT), magnetic (AZ), and diffusion (CONC). Gradients can be nodal
        // values extrapolated from the integration points or values at the integration points
        // moved to the nodes. The number of items in each record is nodstr*3*N, where N can
        // be 1, 2, 3, or 4 (depending on the coupled-field conditions).
        iterators::ElementFieldGradientsRange elementFieldGradients();
        // [Solution] Iterate through elements elastic strains. Each record contains strains
        // in the order X, Y, Z, XY, YZ, XZ, EQV. Elastic strains can be nodal values
        // extrapolated from the integration points or values at the integration points moved
        // to the nodes. If an element is nonlinear, integration point values always will be
        // written. An element is considered nonlinear when either plastic, creep, or swelling
        // strains are present. For beam elements, see item LEPEL in the description in the
        // Output Data section for the particular element in the ANSYS Elements Reference.
        // NOTE: See ENS record section for more details on record content and length.
        iterators::ElementElasticStrainsRange elementElasticStrains();
        // [Solution] Iterate through elements plastic strains. Each record contains strains
        // in the order X, Y, Z, XY, YZ, XZ, EQV. Plastic strains are always values at the
        // integration points moved to the nodes. For beam elements, see item LEPPL in the
        // Output Data section for the particular element in the ANSYS Elements Reference.
        // NOTE: See ENS record section for more details on record content and length.
        iterators::ElementPlasticStrainsRange elementPlasticStrains();
        // [Solution] Iterate through elements creep srains. Each record contains strains in
        // the order X, Y, Z, XY, YZ, XZ, EQV. Creep strains are always values at the
        // integration points moved to the nodes. For beam elements, see item LEPCR in the Output
        // Data section for the particular element in the ANSYS Elements Reference.
        // NOTE: See ENS record section for more details on record content and length.
        iterators::ElementCreepStrainsRange elementCreepStrains();
        // [Solution] Iterate through elements thermal strains. Each record contains strains in
        // the order X, Y, Z, XY, YZ, XZ, EQV plus the element swelling strain. Thermal strains
        // can be nodal values extrapolated from the integration points or values at the integration
        // points moved to the nodes. If the element is nonlinear, integration point data always
        // be written. An element is considered nonlinear when either plastic, creep, or swelling
        // strains are present. For beam elements, see item LEPTH in the description of the Output
        // Data section for the particular element in the ANSYS Elements Reference.
        // NOTE: See ENS record section for more details on record content and length.
        iterators::ElementThermalStrainsRange elementThermalStrains();
        // [Solution] Iterate through elements Euler angles. Each record contains the Euler
        // angles THXY, THYZ, THZX. No attempt is made to make this information complete for
        // all cases of all element types. Read ANSYS Elements Reference.
        iterators::ElementEulerAnglesRange elementEulerAngles();
        // [Solution] Iterate through elements nodal field fluxes. Each record contains the fluxes
        // at each corner node in the order X, Y, Z. If this is a coupled-field analysis, the
        // flux data is stored in the following order: thermal, electric, magnetic. Nodal order
        // corresponds to the connectivity defined in the element description. Fluxes can be nodal
        // values extrapolated from the integration points or values at the integration points
        // moved to the nodes. The number of items in the record is nodstr*3*N, where N can be
        // 1, 2, or 3 depending on the coupled-field conditions.
        // NOTE: nodstr is defined in the element type description record.
        iterators::ElementFieldFluxesRange elementFieldFluxes();
        // [Solution] Iterate through elements nodal coupled-field forces. Each record lists the
        // forces at each node in the order X, Y, Z. For most elements, the number of items in
        // record is nodfor*3. However, for the PLANE53 element, the number of items is either
        // nodfor*3 or nodstr*3. (See the description of KEYOPT(7) for PLANE53 in the ANSYS Elements
        // Reference.)
        // NOTE: nodfor and nodstr are defined in the element type description record.
        iterators::ElementCoupledFieldForcesRange elementCoupledFieldForces();
        // [Solution] Iterate through elements nonsummable miscellaneous data. The contents and
        // number data items for the record is element-dependent. See the description for item NMISC
        // of the ETABLE command in the ANSYS Commands Reference.
        iterators::ElementNonsummableMiscDataRange elementNonsumMiscData();
        // [Solution] Iterate through elemenets current densities. Each record contains the
        // calculated current densities in the order X, Y, Z.
        iterators::ElementDensitiesRange elementDensities();
        // [Solution] Iterate through elements nodal nonlinear data. Each record stores nonlinear
        // data at each corner node in the order SEPL, SRAT, HPRES, EPEQ, PSV or CREQ, PLWK, CRWK,
        // and ELENG followed by 2 spares. Here SEPL - equivalent stress parameter, SRAT - stress
        // ratio, HPRES - hydrostatic pressure, EPEQ - accumulated equivalent plastic strain,
        // PSV - plastic state variable, CREQ - accumulated equivalent creep strain (Applies to
        // current technology element types 180, 181, 182, 183, 185, 186, 187, 188, 189, 208, 209,
        // 265, 281, 288, 289, 290), PLWK - plastic strain energy density (work), CRWK - creep strain
        // energy density (work), ELENG - elestic strain energy density.
        iterators::ElementNonlinearDataRange elementNonlinearData();
        // [Solution] Iterate through elements heat generation. Each record stores the calculated
        // heat generation.
        iterators::ElementHeatGenerationRange elementHeatGeneration();
        // [Solution] Iterate through elements structural nodal temperatures. For solid elements and
        // SHELL 41, each record contains nodal temperatures at each node and the number of items in
        // the record is nodfor. For shell elements, except SHELL41 and SHELL91, the record contains
        // nodal temperatures at each corner node for the top surface and the bottom surface. The
        // number of items in this record is nodstr*2. For another elements, the contents and number
        // of data items is element-dependent. See ANSYS Elements Reference.
        iterators::ElementTemperaturesRange elementTemperatures();
        // [Solution] Iterate through elements surface stresses. The length of each record is nsurf*19
        // where nsurf is the number of surfaces that have surface stress information. The stress
        // information is simply repeated in the format shown in Guide to Interfacing with ANSYS.
        iterators::ElementSurfaceStressesRange elementSurfaceStresses();
        // [Solution] Iterate through elements nodal component diffusion strains. Each record contains
        // strains in the order X, Y, Z, XY, YZ, XZ, EQV. Diffusion strains can be nodal values
        // extrapolated from the integration points or values at the integration points moved to the
        // nodes.
        // NOTE: See ENS record section for more details on record content and length.
        iterators::ElementDiffusionStrainsRange elementDiffusionStrains();
        // [Solution] Iterate through elements ETABLE items.
        iterators::ElementTablesRange elementTables();
        // [Solution] Iterate through elements contact results. Each record stores contact results at
        // each corner node in the order STAT, PENE, SFRIC, STOT, SLIDE, GAP, FLUX, CNOS, FPRS. Here
        // STAT - contact status, PENE - contact penetration, PRES - contact pressure, SFRIC - contact
        // friction stress, STOT - contact total stress (pressure plus friction), SLIDE - contact sliding
        // distance, GAP - contact gap distance, FLUX - total heat flux at contact surface, CNOS - total
        // number of contact status changes during substep, FPRS - actual applied fluid penetration pressure
        iterators::ElementContactResultsRange elementContactResults();
        // [Solution] Iterate through elements integration point coordinates. The length of each record
        // is numint*3, where numint is the number of integration points. Even two-dimensional elements
        // use the 3. They are output only if requested with the OUTRES,loci command.
        // Applicable only to legacy element types 2, 42, 45, 82, 92, 95, and current technology element
        // types 180, 181, 182, 183, 185, 186, 187, 188, 189, 208, 209, 265, 281, 288, 289, 290.
        iterators::ElementIntPointCoordsRange elementIntPointCoords();
        // [Solution] Iterate through elements structural nodal back stresses. Each record has the same form
        // as the plastic strains. They are output if the form of plasticity is kinematic hardening and the
        // plastic strains are requested. Applicable only to legacy element types 2, 42, 45, 82, 92, 95, and
        // current technology element types 180, 181, 182, 183, 185, 186, 187, 18, 189, 208, 209, 265, 281,
        // 288, 289, 290.
        iterators::ElementBackStressesRange elementBackStresses();
        // [Solution] Iterate through elements state variable record. Exists only if written by user in
        // usermat or usercreep.
        iterators::ElementStateVariableRange elementStateVariable();
        // [Solution] Iterate through materials nonlinear record
        iterators::MaterialsNonlinearRange materialNonlinearData();

    private:
        inner::ResultFileSectionLevel reduceToLevel(
            const std::vector<inner::ResultFileSectionLevel> levels);
        void setSolutionLevel();
        bool selectElementTypes();
        bool selectRealConstants();
        bool selectCoordinateSystems();
        bool selectNodalCoordinates();
        bool selectElementsInfo();
        bool selectNodalDisplacements();
        bool selectReactionForces();
        bool selectConstraints();
        bool selectAppliedForces();
        bool selectElementResults();

        friend class iterators::ElementTypeRange;
        friend class iterators::RealConstantRange;
        friend class iterators::CoordinateSystemRange;
        friend class iterators::NodalCoordinatesRange;
        friend class iterators::ElementInfoRange;
        friend class iterators::NodalDisplacementsRange;
        friend class iterators::ReactionForcesRange;
        friend class iterators::ConstraintsRange;
        friend class iterators::AppliedForcesRange;
        friend class iterators::MiscellaneousRange;
        friend class iterators::ElementForcesRange;
        friend class iterators::ElementStressesRange;
        friend class iterators::ElementVolumeEnergiesRange;
        friend class iterators::ElementFieldGradientsRange;
        friend class iterators::ElementElasticStrainsRange;
        friend class iterators::ElementPlasticStrainsRange;
        friend class iterators::ElementCreepStrainsRange;
        friend class iterators::ElementThermalStrainsRange;
        friend class iterators::ElementEulerAnglesRange;
        friend class iterators::ElementFieldFluxesRange;
        friend class iterators::ElementCoupledFieldForcesRange;
        friend class iterators::ElementNonsummableMiscDataRange;
        friend class iterators::ElementDensitiesRange;
        friend class iterators::ElementNonlinearDataRange;
        friend class iterators::ElementHeatGenerationRange;
        friend class iterators::ElementTemperaturesRange;
        friend class iterators::ElementSurfaceStressesRange;
        friend class iterators::ElementDiffusionStrainsRange;
        friend class iterators::ElementTablesRange;
        friend class iterators::ElementContactResultsRange;
        friend class iterators::ElementIntPointCoordsRange;
        friend class iterators::ElementBackStressesRange;
        friend class iterators::ElementStateVariableRange;
        friend class iterators::MaterialsNonlinearRange;

        iterators::ElementTypeIterator elementTypeBegin() const;
        iterators::ElementTypeIterator elementTypeEnd() const;
        iterators::RealConstantIterator realConstantBegin() const;
        iterators::RealConstantIterator realConstantEnd() const;
        iterators::CoordinateSystemIterator coordinateSystemBegin() const;
        iterators::CoordinateSystemIterator coordinateSystemEnd() const;
        iterators::NodalCoordinatesIterator nodalCoordinatesBegin() const;
        iterators::NodalCoordinatesIterator nodalCoordinatesEnd() const;
        iterators::ElementInfoIterator elementInfoBegin() const;
        iterators::ElementInfoIterator elementInfoEnd() const;
        iterators::Results1DIterator nodalDisplacementsBegin() const;
        iterators::Results1DIterator nodalDisplacementsEnd() const;
        iterators::Results1DIterator reactionForcesBegin() const;
        iterators::Results1DIterator reactionForcesEnd() const;
        iterators::Results1DIterator constraintsBegin() const;
        iterators::Results1DIterator constraintsEnd() const;
        iterators::Results1DIterator appliedForcesBegin() const;
        iterators::Results1DIterator appliedForcesEnd() const;
        iterators::Results1DIterator miscellaneousBegin() const;
        iterators::Results1DIterator miscellaneousEnd() const;
        iterators::Results1DIterator elementForcesBegin() const;
        iterators::Results1DIterator elementForcesEnd() const;
        iterators::Results1DIterator elementStressesBegin() const;
        iterators::Results1DIterator elementStressesEnd() const;
        iterators::Results1DIterator elementVolumeEnergiesBegin() const;
        iterators::Results1DIterator elementVolumeEnergiesEnd() const;
        iterators::Results1DIterator elementFieldGradientsBegin() const;
        iterators::Results1DIterator elementFieldGradientsEnd() const;
        iterators::Results1DIterator elementElasticStrainsBegin() const;
        iterators::Results1DIterator elementElasticStrainsEnd() const;
        iterators::Results1DIterator elementPlasticStrainsBegin() const;
        iterators::Results1DIterator elementPlasticStrainsEnd() const;
        iterators::Results1DIterator elementCreepStrainsBegin() const;
        iterators::Results1DIterator elementCreepStrainsEnd() const;
        iterators::Results1DIterator elementThermalStrainsBegin() const;
        iterators::Results1DIterator elementThermalStrainsEnd() const;
        iterators::Results1DIterator elementEulerAnglesBegin() const;
        iterators::Results1DIterator elementEulerAnglesEnd() const;
        iterators::Results1DIterator elementFieldFluxesBegin() const;
        iterators::Results1DIterator elementFieldFluxesEnd() const;
        iterators::Results1DIterator elementCoupledFieldForcesBegin() const;
        iterators::Results1DIterator elementCoupledFieldForcesEnd() const;
        iterators::Results1DIterator elementNonsummableMiscDataBegin() const;
        iterators::Results1DIterator elementNonsummableMiscDataEnd() const;
        iterators::Results1DIterator elementDensitiesBegin() const;
        iterators::Results1DIterator elementDensitiesEnd() const;
        iterators::Results1DIterator elementNonlinearDataBegin() const;
        iterators::Results1DIterator elementNonlinearDataEnd() const;
        iterators::Results1DIterator elementHeatGenerationBegin() const;
        iterators::Results1DIterator elementHeatGenerationEnd() const;
        iterators::Results1DIterator elementTemperaturesBegin() const;
        iterators::Results1DIterator elementTemperaturesEnd() const;
        iterators::Results1DIterator elementSurfaceStressesBegin() const;
        iterators::Results1DIterator elementSurfaceStressesEnd() const;
        iterators::Results1DIterator elementDiffusionStrainsBegin() const;
        iterators::Results1DIterator elementDiffusionStrainsEnd() const;
        iterators::Results1DIterator elementTablesBegin() const;
        iterators::Results1DIterator elementTablesEnd() const;
        iterators::Results1DIterator elementContactResultsBegin() const;
        iterators::Results1DIterator elementContactResultsEnd() const;
        iterators::Results1DIterator elementIntPointCoordsBegin() const;
        iterators::Results1DIterator elementIntPointCoordsEnd() const;
        iterators::Results1DIterator elementBackStressesBegin() const;
        iterators::Results1DIterator elementBackStressesEnd() const;
        iterators::Results1DIterator elementStateVariableBegin() const;
        iterators::Results1DIterator elementStateVariableEnd() const;
        iterators::Results1DIterator materialsNonlinearBegin() const;
        iterators::Results1DIterator materialsNonlinearEnd() const;

        using SectionPtrT = std::unique_ptr<inner::ResultFileSection>;
        std::stack<SectionPtrT> m_sectionStack;

        int m_numDOF = -1;                      // The number of DOF per node
        int m_maxNodeId = -1;                   // Maximum node number
        int m_numNode = -1;                     // Number of nodes used
        int m_maxElementId = -1;                // Maximum element number
        int m_numElement = -1;                  // Number of elements used

        int m_maxElementTypeId = -1;            // Maximum element type
        int m_maxRealConstantSetId = -1;        // Maximum real constant set number
        int m_maxCoordinateSystemId = -1;       // Maximum coordinate system number
        int m_numNodesWithCoordinates = -1;     // Number of nodes with coordinates

        std::array<int, 40> m_BCHeader = std::array<int, 40>{};

        structures::ResultSetInfo m_resultSetInfo;
    };
}

