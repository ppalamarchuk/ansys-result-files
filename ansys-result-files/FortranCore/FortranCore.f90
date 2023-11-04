! ===============================================================================
! Pavlo Palamarchuk
! -------------------------------------------------------------------------------
! PURPOSE:  These routines function as an interoperability shim between
!           the BINLIB fortran functions and the C family of languages.
!           Each routine collects the arguments passed to it and forwards
!           them directly to the corresponding BINLIB routine.

#include "ansysdef.h"

! === CResRdBegin ===============================================================
!     Shim function for ResRdBegin
!
    subroutine FResRdBegin (Fname, Title, JobName, Units, NumDOF, DOF,          &
                            UserCode, MaxNode, NumNode, MaxElem, NumElem,       &
                            MaxResultSet, NumResultSet)                         &
                            BIND(C, NAME="FResRdBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdBegin
    ! Fname:            The name (with extension) for the file
    !                   (Limit to 260 printable characters)
    character(len=1), dimension(261), intent(in) :: Fname
    ! Title:            The Title. This is broken into strings at most 80
    !                   characters. Each subtitle in the title is separated by
    !                   a newline character
    character(len=1), dimension(163), intent(out) :: Title
    ! JobName:          The jobname from file (Limit to 32 printable characters)
    character(len=1), dimension(33), intent(out) :: JobName
    ! Units:            Unit System
    !                   = 0 - User Defined Units
    !                   = 1 - SI
    !                   = 2 - CSG
    !                   = 3 - U.S. Customary, using feet
    !                   = 4 - U.S. Customary, using inches
    !                   = 5 - MKS
    !                   = 6 - MPA
    !                   = 7 - uMKS
    integer(c_int), intent(out) :: Units
    ! NumDOF:           The number of DOF per node
    integer(c_int), intent(out) :: NumDOF
    ! DOF:              The DOFs per node
    integer(c_int), dimension(MAXDOFSPERNODE), intent(out) :: DOF
    ! UserCode:         Code for this application
    integer(c_int), intent(out) :: UserCode
    ! MaxNode:          Maximum node number used
    integer(c_int), intent(out) :: MaxNode
    ! NumNode:          Number of nodes attached to elements
    integer(c_int), intent(out) :: NumNode
    ! MaxElem:          Maximum element number used
    integer(c_int), intent(out) :: MaxElem
    ! NumElem:          Number of elements used
    integer(c_int), intent(out) :: NumElem
    ! MaxResultSet:     Maximum number of result sets (usually 1000)
    integer(c_int), intent(out) :: MaxResultSet
    ! NumResultSet:     Number of result sets on file
    integer(c_int), intent(out) :: NumResultSet
    
    ! Internal variables for use with the call to the ANSYS
    ! ResRdBegin function
    character(261) :: FortFName
    integer ncFname
    integer Nunit, Lunit, ii, jj, idx
    character(80) :: FortTitle(2)
    character(32) :: FortJName
    
    ! Convert the input file name to a fortran character variable
    do ii=1, 261
        FortFName(ii:ii)=Fname(ii)
    end do
    ncFname = index(FortFName, C_NULL_CHAR) - 1
    
    ! Result file Unit number
    Nunit = 12
    ! Stdout Unit number
    Lunit = 6
    ! Call the base function
    call ResRdBegin (Nunit, Lunit, FortFName, ncFname, FortTitle(1),    &
                    FortJName, Units, NumDOF, DOF(1), UserCode,         &
                    MaxNode, NumNode, MaxElem, NumElem,                 &
                    MaxResultSet, NumResultSet)
    ! Copy the jobname back over
    do ii = 1, len_trim(FortJName)
        JobName(ii) = FortJName(ii:ii)
    end do
    JobName(len_trim(FortJName)+1) = C_NULL_CHAR
    ! Copy the title back across
    idx = 1
    do ii = 1, 2
        do jj = 1, len_trim(FortTitle(ii))
            Title(idx) = FortTitle(ii)(jj:jj)
            idx = idx + 1
        end do
        Title(idx) = C_NEW_LINE
        idx = idx + 1
    end do
    Title(idx) = C_NULL_CHAR
    end


! === FResRdEnd =================================================================
!     Shim function for ResRdEnd
!
    subroutine FResRdEnd () BIND(C, NAME="FResRdEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdEnd
    call ResRdEnd()
    end


! === FResRdGeomBegin ===========================================================
!     Shim function for ResRdGeomBegin
!
    subroutine FResRdGeomBegin (MaxType, MaxReal, MaxCsys, nXYZ)                &
                                BIND(C, NAME="FResRdGeomBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdGeomBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdGeomBegin
    ! MaxType:           Maximum element type
    integer(c_int), intent(out) :: MaxType
    ! MaxReal:           Maximum real constant set number
    integer(c_int), intent(out) :: MaxReal
    ! MaxCsys:           Maximum coordinate system number
    integer(c_int), intent(out) :: MaxCsys
    ! nXYZ:              Number of nodes with coordinates
    integer(c_int), intent(out) :: nXYZ
    
    call ResRdGeomBegin(MaxType, MaxReal, MaxCsys, nXYZ)
    end


! === FResRdGeomEnd =============================================================
!     Shim function for ResRdGeomEnd
!
    subroutine FResRdGeomEnd () BIND(C, NAME="FResRdGeomEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdGeomEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdGeomEnd
    call ResRdGeomEnd()
    end


! === FResRdTypeBegin ===========================================================
!     Shim function for ResRdTypeBegin
!
    subroutine FResRdTypeBegin (NumType) BIND(C, NAME="FResRdTypeBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdTypeBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdTypeBegin
    ! NumType:           Number of defined element types
    integer(c_int), intent(out) :: NumType

    call ResRdTypeBegin(NumType)
    end


! === FResRdType ================================================================
!     Shim function for ResRdType
!
    subroutine FResRdType (itype, ielc) BIND(C, NAME="FResRdType")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdType
    use, intrinsic :: ISO_C_BINDING
    implicit none
    !external ResRdType
    ! itype:            Element type number
    integer(c_int), intent(in) :: itype
    ! ielc:             Element characteristics
    integer(c_int), dimension(IELCSZ), intent(out) :: ielc
    
    call ResRdType(itype + 1, ielc(1))
    end


! === FResRdTypeEnd =============================================================
!     Shim function for ResRdTypeEnd
!
    subroutine FResRdTypeEnd () BIND(C, NAME="FResRdTypeEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdTypeEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdTypeEnd
    call ResRdTypeEnd()
    end


! === FResRdRealBegin ===========================================================
!     Shim function for ResRdRealBegin
!
    subroutine FResRdRealBegin (NumReal,NumPerReal) BIND(C, NAME="FResRdRealBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdRealBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdRealBegin
    ! NumReal:          Number of real constant sets defined
    integer(c_int), intent(out) :: NumReal
    ! NumPerReal:       Maximum number of real constant in a set
    integer(c_int), intent(out) :: NumPerReal

    call ResRdRealBegin(NumReal, NumPerReal)
    end


! === FResRdReal ================================================================
!     Shim function for ResRdReal
!
    subroutine FResRdReal (iReal, Rcon) BIND(C, NAME="FResRdReal")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdReal
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdReal
    ! iReal:            Real set number
    integer(c_int), intent(in) :: iReal
    ! Rcon:             Real Constants
    real(c_double), dimension(MAXREALS), intent(out) :: Rcon

    call ResRdReal(iReal + 1, Rcon(1))
    end


! === FResRdRealEnd =============================================================
!     Shim function for ResRdRealEnd
!
    subroutine FResRdRealEnd () BIND(C, NAME="FResRdRealEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdRealEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdRealEnd
    call ResRdRealEnd()
    end
    

! === FResRdCsysBegin ===========================================================
!     Shim function for ResRdCsysBegin
!
    subroutine FResRdCsysBegin (NumCsys) BIND(C, NAME="FResRdCsysBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdCsysBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdCsysBegin
    ! NumCsys:          Number of defined coordinate systems
    integer(c_int), intent(out) :: NumCsys

    call ResRdCsysBegin(NumCsys)
    end


! === FResRdCsys ================================================================
!     Shim function for ResRdCsys
!
    subroutine FResRdCsys (iCsys,Csys) BIND(C, NAME="FResRdCsys")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdCsys
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdCsys
    ! iCsys:            Coordinate system number
    integer(c_int), intent(in) :: iCsys
    ! Csys:             Coordinate system description
    real(c_double), dimension(MAXREALS), intent(out) :: Csys

    call ResRdCsys(iCsys + 1, Csys(1))
    end


! === FResRdCsysEnd =============================================================
!     Shim function for ResRdCsysEnd
!
    subroutine FResRdCsysEnd () BIND(C, NAME="FResRdCsysEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdCsysEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdCsysEnd
    call ResRdCsysEnd()
    end


! === FResRdNodeBegin ===========================================================
!     Shim function for ResRdNodeBegin
!
    subroutine FResRdNodeBegin () BIND(C, NAME="FResRdNodeBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdNodeBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdNodeBegin
    call ResRdNodeBegin()
    end


! === FResRdNode ================================================================
!     Shim function for ResRdNode
!
    subroutine FResRdNode (iNode, xyzang) BIND(C, NAME="FResRdNode")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdNode
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdNode
    ! iNode:            Node sequence number
    integer(c_int), intent(in) :: iNode
    ! xyzang:           x,y,z,thxy,thyz,thzx for node
    real(c_double), dimension(6), intent(out) :: xyzang

    call ResRdNode(iNode + 1, xyzang)
    end


! === FResRdNodeEnd =============================================================
!     Shim function for ResRdNodeEnd
!
    subroutine FResRdNodeEnd () BIND(C, NAME="FResRdNodeEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdNodeEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdNodeEnd
    call ResRdNodeEnd()
    end


! === FResRdElemBegin ===========================================================
!     Shim function for ResRdElemBegin
!
    subroutine FResRdElemBegin () BIND(C, NAME="FResRdElemBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdElemBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdElemBegin
    call ResRdElemBegin()
    end


! === FResRdElem ================================================================
!     Shim function for ResRdElem
!
    subroutine FResRdElem (iElem, nodes, ElemData) BIND(C, NAME="FResRdElem")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdElem
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdElem
    ! iElem:            The element number
    integer(c_int), intent(in) :: iElem
    ! nodes:            Element nodes
    integer(c_int), dimension(MAXNODESPERELEM), intent(out) :: nodes
    ! ElemData:         Element information
    !                       mat     - material reference number
    !                       type    - element
    !                       real    - real constant reference number
    !                       secnum  - section number
    !                       esys    - element coordinate system
    !                       death   - death flag
    !                                 = 0 - alive
    !                                 = 1 - dead
    !                       solidm  - solid model reference
    !                       shape   - coded shape key
    !                       elnum   - element number
    !                       pexcl   - P-Method exclude key
    integer(c_int), dimension(10), intent(out) :: ElemData

    call ResRdElem(iElem + 1, nodes(1), ElemData(1))
    end


! === FResRdElemEnd =============================================================
!     Shim function for ResRdElemEnd
!
    subroutine FResRdElemEnd () BIND(C, NAME="FResRdElemEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdElemEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdElemEnd
    call ResRdElemEnd()
    end


! === FResRdSolBegin ============================================================
!     Shim function for ResRdSolBegin
!
    subroutine FResRdSolBegin (key, lstep, substep, ncumit, kcmplx, time,       &
                               Title, DofLab) BIND(C, NAME="FResRdSolBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdSolBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdSolBegin
    ! key:              - 0, find by set number
    !                     1, find by lstep/substep
    !                     2, find by ncumit
    !                     3, find by time
    integer(c_int), intent(in) :: key
    ! lstep:            Load step number
    !                   if key=0, this is the set number
    integer(c_int), intent(inout) :: lstep
    ! substep:          Substep of this load step
    integer(c_int), intent(inout) :: substep
    ! ncumit:           Cumulative iteration number
    integer(c_int), intent(inout) :: ncumit
    ! kcmplx:           0, Real solution
    !                   1, Imaginary solution
    integer(c_int), intent(in) :: kcmplx
    ! time:             Current solution time
    real(c_double), intent(inout) :: time
    ! Title:            Title and 4 subtitles
    character(len=1), dimension(400), intent(out) :: Title
    ! DofLab:           Labels for DOFs
    character(len=1), dimension(400), intent(out) :: DofLab
    
    call ResRdSolBegin(key, lstep, substep, ncumit, kcmplx, time, Title, DofLab)
    end


! === FResRdSolEnd ==============================================================
!     Shim function for ResRdSolEnd
!
    subroutine FResRdSolEnd () BIND(C, NAME="FResRdSolEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdSolEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdSolEnd
    call ResRdSolEnd()
    end


    
