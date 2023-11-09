#pragma once
#include "ansysdef.h"

#ifdef ARFLIBRARY_EXPORTS
#define ARFLIBRARY_API __declspec(dllexport)
#else
#define ARFLIBRARY_API __declspec(dllimport)
#endif

namespace arf {

    extern "C" {

        /// <summary>
        /// Open the result file and extracts header information. Note, this call must be matched with a subsequent
        /// CResRdEnd() to ensure that the file is closed and internal structures are deallocated properly.
        /// </summary>
        /// <param name="FileName [in]"> Full path to the result file to open. (max 260 characters) </param>
        /// <param name="Title [out]"> Title the simulation separated by newlines. (max 162 characters) </param>
        /// <param name="JobName [out]"> Jobname for the simulation. (max 32 characters) </param>
        /// <param name="Units [out]"> Units designator:
        ///                             0 - User Defined Units
        ///                             1 - SI
        ///                             2 - CSG
        ///                             3 - U.S.Customary, using feet
        ///                             4 - U.S.Customary, using inches
        ///                             5 - MKS
        ///                             6 - MPA
        ///                             7 - uMKS
        /// </param>
        /// <param name="NumDOF [out]"> The number of DOF per node </param>
        /// <param name="DOFs [out]"> Array[MAXDOFSPERNODE] of the DOFs per node </param>
        /// <param name="UserCode [out]"> Internal code for this application </param>
        /// <param name="MaxNode [out]"> Maximum node number used </param>
        /// <param name="NumNode [out]"> Number of nodes attached to elements </param>
        /// <param name="MaxElem [out]"> Maximum element number used </param>
        /// <param name="NumElem [out]"> Number of elements used </param>
        /// <param name="MaxResultSet [out]"> Maximum number of result sets (usually 1000) </param>
        /// <param name="NumResultSet [out]"> Number of result sets on file </param>
        /// <returns> 0 - successful, other - error in file open </returns>
        ARFLIBRARY_API int CResRdBegin(
            char* FileName, char* Title, char* JobName, int* Units,
            int* NumDOF, int* DOFs, int* UserCode, int* MaxNode,
            int* NumNode, int* MaxElem, int* NumElem,
            int* MaxResultSet, int* NumResultSet
        );

        /// <summary>
        /// Close the result file, deallocates internal data.
        /// </summary>
        ARFLIBRARY_API void CResRdEnd();

        /// <summary>
        /// Read geometry header record. Note, this call must be matched with a subsequent
        /// CResRdGeomEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="MaxType [out]"> Maximum element type </param>
        /// <param name="MaxReal [out]"> Maximum real constant set number </param>
        /// <param name="MaxCsys [out]"> Maximum coordinate system number </param>
        /// <param name="nXYZ [out]"> Number of nodes with coordinates </param>
        ARFLIBRARY_API void CResRdGeomBegin(int* MaxType, int* MaxReal, int* MaxCsys, int* nXYZ);

        /// <summary>
        /// Finish Geometry Input.
        /// </summary>
        ARFLIBRARY_API void CResRdGeomEnd();

        /// <summary>
        /// Start element type records. Note, this call must be matched with a subsequent
        /// CResRdTypeEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="NumType [out]"> Number of defined element types </param>
        ARFLIBRARY_API void CResRdTypeBegin(int* NumType);

        /// <summary>
        /// Read an element type record.
        /// </summary>
        /// <param name="itype [in]"> Element type number </param>
        /// <param name="ielc [out]"> Array[IELCSZ] of element characteristics </param>
        /// <returns> Number of words read </returns>
        ARFLIBRARY_API int CResRdType(int* itype, int* ielc);

        /// <summary>
        /// End element types.
        /// </summary>
        ARFLIBRARY_API void CResRdTypeEnd();

        /// <summary>
        /// Start real constant records. Note, this call must be matched with a subsequent
        /// CResRdRealEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="NumReal [out]"> Number of real constant sets defined </param>
        /// <param name="NumPerReal [out]"> Maximum number of real constant in a set </param>
        ARFLIBRARY_API void CResRdRealBegin(int* NumReal, int* NumPerReal);

        /// <summary>
        /// Read real constant record.
        /// </summary>
        /// <param name="iReal [in]"> Real set number </param>
        /// <param name="Rcon [out]"> Array[MAXREALS] of real constants </param>
        /// <returns> Number of real constants in set </returns>
        ARFLIBRARY_API int CResRdReal(int* iReal, double* Rcon);

        /// <summary>
        /// End real constants.
        /// </summary>
        ARFLIBRARY_API void CResRdRealEnd();

        /// <summary>
        /// Start coordinate system records. Note, this call must be matched with a subsequent
        /// CResRdCsysEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="NumCsys [out]"> Number of defined coordinate systems </param>
        ARFLIBRARY_API void CResRdCsysBegin(int* NumCsys);

        /// <summary>
        /// Read a coordinate system record.
        /// </summary>
        /// <param name="iCsys [in]"> Coordinate system number </param>
        /// <param name="Csys [out]"> Array[MAXREALS] of coordinate system description </param>
        /// <returns> Number of values </returns>
        ARFLIBRARY_API int CResRdCsys(int* iCsys, double* Csys);

        /// <summary>
        /// End coordinate systems.
        /// </summary>
        ARFLIBRARY_API void CResRdCsysEnd();

        /// <summary>
        /// Start node records. Note, this call must be matched with a subsequent
        /// CResRdNodeEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        ARFLIBRARY_API void CResRdNodeBegin();

        /// <summary>
        /// Get a node.
        /// </summary>
        /// <param name="iNode [in]"> Node sequence number </param>
        /// <param name="xyzang [out]"> Array[6] of x, y, z, thxy, thyz, thzx for node </param>
        /// <returns> Node number </returns>
        ARFLIBRARY_API int CResRdNode(int* iNode, double* xyzang);

        /// <summary>
        /// End Nodes.
        /// </summary>
        ARFLIBRARY_API void CResRdNodeEnd();

        /// <summary>
        /// Start element input. Note, this call must be matched with a subsequent
        /// CResRdElemEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        ARFLIBRARY_API void CResRdElemBegin();

        /// <summary>
        /// Read an element.
        /// </summary>
        /// <param name="iElem [in]"> The element number </param>
        /// <param name="nodes [out]"> Array[MAXNODESPERELEM] of element nodes </param>
        /// <param name="ElemData [out]"> Array[10] of element information 
        ///                                 mat     - material reference number
        ///                                 type    - element
        ///                                 real    - real constant reference number
        ///                                 secnum  - section number
        ///                                 esys    - element coordinate system
        ///                                 death   - death flag
        ///                                           = 0 - alive
        ///                                           = 1 - dead
        ///                                 solidm  - solid model reference
        ///                                 shape   - coded shape key
        ///                                 elnum   - element number
        ///                                 pexcl   - P - Method exclude key
        /// </param>
        /// <returns> Number of nodes </returns>
        ARFLIBRARY_API int CResRdElem(int* iElem, int* nodes, int* ElemData);

        /// <summary>
        /// Finish element reading.
        /// </summary>
        ARFLIBRARY_API void CResRdElemEnd();

        /// <summary>
        /// Read the solution header records. Note, this call must be matched with a subsequent
        /// CResRdSolEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="key [in]">
        /// 0, find by set number
        /// 1, find by lstep / substep
        /// 2, find by ncumit
        /// 3, find by time
        /// </param>
        /// <param name="lstep [in / out]">
        /// Load step number. If key = 0, this is the set number
        /// </param>
        /// <param name="substep [in / out]"> Substep of this load step </param>
        /// <param name="ncumit [in / out]"> Cumulative iteration number </param>
        /// <param name="kcmplx [in]"> 0 - Real solution, 1 - Imaginary solution </param>
        /// <param name="time [in / out]"> Current solution time </param>
        /// <param name="Title [out]"> Title and 4 subtitles. (max 405 characters) </param>
        /// <param name="DofLab [out]"> Labels for DOFs. (max (MAXDOFLABELLEN-1) characters) </param>
        /// <returns> 0 - requested solution set found, 1 - not found </returns>
        ARFLIBRARY_API int CResRdSolBegin(int* key, int* lstep, int* substep,
            int* ncumit, int* kcmplx, double* time, char* Title, char* DofLab);

        /// <summary>
        /// End of a Solution Result Set.
        /// </summary>
        ARFLIBRARY_API void CResRdSolEnd();

        /// <summary>
        /// Read displacement vector. Note, this call must be matched with a subsequent
        /// CResRdDispEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        ARFLIBRARY_API void CResRdDispBegin();

        /// <summary>
        /// Retrieve a nodal displacement.
        /// </summary>
        /// <param name="node [in]"> Node number </param>
        /// <param name="Disp [out]"> Array[MAXDOFSPERNODE] of displacements </param>
        /// <returns> Number of displacements </returns>
        ARFLIBRARY_API int CResRdDisp(int* node, double* Disp);

        /// <summary>
        /// Finish displacements.
        /// </summary>
        ARFLIBRARY_API void CResRdDispEnd();

        /// <summary>
        /// Read reaction forces. Note, this call must be matched with a subsequent
        /// CResRdRforEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="nRForce [out]"> Number of reactions </param>
        ARFLIBRARY_API void CResRdRforBegin(int* nRForce);

        /// <summary>
        /// Retrieve a reaction force.
        /// </summary>
        /// <param name="node [in]"> External node number </param>
        /// <param name="idof [in]"> Internal dof number </param>
        /// <param name="value [out]"> Value of reaction force </param>
        /// <returns> Number of returned values (0 or 1) </returns>
        ARFLIBRARY_API int CResRdRfor(int* node, int* idof, double* value);

        /// <summary>
        /// Finish reaction forces.
        /// </summary>
        ARFLIBRARY_API void CResRdRforEnd();

        /// <summary>
        /// Read Header for Boundary Conditions. Note, this call must be matched with a subsequent
        /// CResRdBCEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="BCHeader [out]"> BC Header, array[40] </param>
        ARFLIBRARY_API void CResRdBCBegin(int* BCHeader);

        /// <summary>
        /// End of BC output.
        /// </summary>
        ARFLIBRARY_API void CResRdBCEnd();

        /// <summary>
        /// Read constraint information. Note, this call must be matched with a subsequent
        /// CResRdFixEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="BCHeader [in]"> BC Header, array[40] </param>
        /// <param name="nFixed [out]"> Number of constraints </param>
        ARFLIBRARY_API void CResRdFixBegin(int* BCHeader, int* nFixed);

        /// <summary>
        /// Retrieve a constraint value (in old format).
        /// </summary>
        /// <param name="node [in]"> External node number </param>
        /// <param name="idof [in]"> Internal dof number </param>
        /// <param name="value [out]"> Array[4] of Real, Imag, RealOld, ImagOld </param>
        /// <returns> Number of returned values (0 or 4) </returns>
        ARFLIBRARY_API int CResRdFixOld(int* node, int* idof, double* value);

        /// <summary>
        /// Retrieve a constraint value.
        /// </summary>
        /// <param name="node [in]"> External node number </param>
        /// <param name="idof [in]"> Internal dof number </param>
        /// <param name="value [out]"> Array[4] of Real, Imag, RealOld, ImagOld </param>
        /// <returns> Number of returned values (0 or 4) </returns>
        ARFLIBRARY_API int CResRdFix(int* node, int* idof, double* value);

        /// <summary>
        /// Finish the constraints.
        /// </summary>
        ARFLIBRARY_API void CResRdFixEnd();

        /// <summary>
        /// Read applied force information. Note, this call must be matched with a subsequent
        /// CResRdForcEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="BCHeader [in]"> BC Header, array[40] </param>
        /// <param name="nForces [out]"> Number of forces </param>
        ARFLIBRARY_API void CResRdForcBegin(int* BCHeader, int* nForces);

        /// <summary>
        /// Retrieve an applied force value (in old format).
        /// </summary>
        /// <param name="node [in]"> External node number </param>
        /// <param name="idof [in]"> Internal dof number </param>
        /// <param name="value [out]"> Array[4] of Real, Imag, RealOld, ImagOld </param>
        /// <returns> Number of returned values (0 or 4) </returns>
        ARFLIBRARY_API int CResRdForcOld(int* node, int* idof, double* value);

        /// <summary>
        /// Retrieve an applied force value.
        /// </summary>
        /// <param name="node [in]"> External node number </param>
        /// <param name="idof [in]"> Internal dof number </param>
        /// <param name="value [out]"> Array[4] of Real, Imag, RealOld, ImagOld </param>
        /// <returns> Number of returned values (0 or 4) </returns>
        ARFLIBRARY_API int CResRdForc(int* node, int* idof, double* value);

        /// <summary>
        /// Finish the applied forces.
        /// </summary>
        ARFLIBRARY_API void CResRdForcEnd();

        /// <summary>
        /// Retrieve index array for element results. Note, this call must be matched with a subsequent
        /// CResRdEresEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        ARFLIBRARY_API void CResRdEresBegin();

        /// <summary>
        /// End of element stresses.
        /// </summary>
        ARFLIBRARY_API void CResRdEresEnd();

        /// <summary>
        /// Retrieve results index for an element. Note, this call must be matched with a subsequent
        /// CResRdEstrEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="iElem [in]"> Element Number </param>
        /// <returns> Results index for an element </returns>
        ARFLIBRARY_API int CResRdEstrBegin(int* iElem);

        /// <summary>
        /// Get an element's results.
        /// </summary>
        /// <param name="iStr [in]"> Element record number (1-25). The interpretation of the results
        /// can be read in ANSYS Mechanical APDL Programmers Reference
        ///     1  - element summable miscellaneous data
        ///     2  - element nodal forces
        ///     3  - element nodal component stresses
        ///     4  - element volume and energies
        ///     5  - element nodal field gradients
        ///     6  - element nodal component elastic strains
        ///     7  - element nodal component plastic strains
        ///     8  - element nodal component creep strains
        ///     9  - element nodal component thermal strains
        ///     10 - element Euler angles
        ///     11 - element nodal field fluxes
        ///     12 - element nodal coupled-field forces
        ///     13 - element nonsummable miscellaneous data
        ///     14 - element current densities
        ///     15 - element nodal nonlinear data
        ///     16 - element heat generation
        ///     17 - element structural temperatures
        ///     18 - element surface stresses
        ///     19 - element diffusion strains
        ///     20 - ETABLE items (post1 only
        ///     21 - element contact data
        ///     22 - element integration point locations
        ///     23 - element back stresses
        ///     24 - element state variables
        ///     25 - material nonlinear record
        /// </param>
        /// <param name="Str [out]"> Array[MAXELERECORD] of element values </param>
        /// <returns> Number of element values </returns>
        ARFLIBRARY_API int CResRdEstr(int* iStr, double* Str);

        /// <summary>
        /// End of output for an element.
        /// </summary>
        ARFLIBRARY_API void CResRdEstrEnd();

        /// <summary>
        /// Read nodal stress vector(s). Note, this call must be matched with a subsequent
        /// CResRdNstrEnd() to ensure that the file is closed and internal structures
        /// are deallocated properly.
        /// </summary>
        /// <param name="kNodStr [out]"> I dont know what is this </param>
        ARFLIBRARY_API void CResRdNstrBegin(int* kNodStr);

        /// <summary>
        /// Retrieve nodal stresses.
        /// </summary>
        /// <param name="node [in]"> Node number </param>
        /// <param name="Nstr [out]"> Array[kNodstr, 6] of nodal stresses.
        /// Use kNodstr = 3 when pass in to function </param>
        /// <returns> kNodstr value </returns>
        ARFLIBRARY_API int CResRdNstr(int* node, double** Nstr);

        /// <summary>
        /// Finish displacements.
        /// </summary>
        ARFLIBRARY_API void CResRdNstrEnd();
    }
}

