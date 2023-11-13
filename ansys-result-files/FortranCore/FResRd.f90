! ===============================================================================
! Pavlo Palamarchuk
! -------------------------------------------------------------------------------
! PURPOSE:  These routines function as an interoperability shim between
!           the BINLIB fortran functions and the C family of languages.
!           Each routine collects the arguments passed to it and forwards
!           them directly to the corresponding BINLIB routine.

#include "ansysdef.h"
!#include "computer.h"

! === FResRdBegin ===============================================================
!     Shim function for ResRdBegin
!
    integer(c_int) function FResRdBegin (Fname, Title, JobName, Units, NumDOF,  &
                                        DOF, UserCode, MaxNode, NumNode,        &
                                        MaxElem, NumElem, MaxResultSet,         &
                                        NumResultSet) BIND(C, NAME="FResRdBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
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

    interface
        integer function ResRdBegin(Nunit, Lunit, Fname, ncFname, Title,        &
            JobName, Units, NumDOF, DOF, UserCode, MaxNode, NumNode, MaxElem,   &
            NumElem, MaxResultSet, NumResultSet)
            integer, intent(in) :: Nunit, Lunit, ncFname
            character*260, intent(in) :: Fname
            character*80, dimension(2), intent(out) :: Title
            character*32, intent(out) :: JobName
            integer, intent(out) :: Units, NumDOF, UserCode, MaxNode, NumNode,  &
                MaxElem, NumElem, MaxResultSet, NumResultSet
            integer DOF(*)
        end function ResRdBegin
    end interface

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
    FResRdBegin = ResRdBegin (Nunit, Lunit, FortFName, ncFname, FortTitle(1),   &
                            FortJName, Units, NumDOF, DOF(1), UserCode,         &
                            MaxNode, NumNode, MaxElem, NumElem, MaxResultSet,   &
                            NumResultSet)
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
    integer(c_int) function FResRdType (itype, ielc) BIND(C, NAME="FResRdType")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdType
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! itype:            Element type number
    integer(c_int), intent(in) :: itype
    ! ielc:             Element characteristics
    integer(c_int), dimension(IELCSZ), intent(out) :: ielc
    
    interface
        integer function ResRdType(itype, ielc)
            integer, intent(in) :: itype
            integer, dimension(IELCSZ), intent(out) :: ielc
        end function ResRdType
    end interface
    
    FResRdType = ResRdType(itype, ielc(1))
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
    integer(c_int) function FResRdReal (iReal, Rcon) BIND(C, NAME="FResRdReal")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdReal
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! iReal:            Real set number
    integer(c_int), intent(in) :: iReal
    ! Rcon:             Real Constants
    real(c_double), dimension(MAXREALS), intent(out) :: Rcon

    interface
        integer function ResRdReal(iReal, Rcon)
            integer, intent(in) :: iReal
            double precision, dimension(MAXREALS), intent(out) :: Rcon
        end function ResRdReal
    end interface

    FResRdReal = ResRdReal(iReal, Rcon(1))
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
    integer(c_int) function FResRdCsys (iCsys, Csys) BIND(C, NAME="FResRdCsys")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdCsys
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! iCsys:            Coordinate system number
    integer(c_int), intent(in) :: iCsys
    ! Csys:             Coordinate system description
    real(c_double), dimension(MAXREALS), intent(out) :: Csys

    interface
        integer function ResRdCsys(iCsys, Csys)
            integer, intent(in) :: iCsys
            double precision, dimension(MAXREALS), intent(out) :: Csys
        end function ResRdCsys
    end interface

    FResRdCsys = ResRdCsys(iCsys, Csys(1))
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
    integer(c_int) function FResRdNode (iNode, xyzang) BIND(C, NAME="FResRdNode")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdNode
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! iNode:            Node sequence number
    integer(c_int), intent(in) :: iNode
    ! xyzang:           x,y,z,thxy,thyz,thzx for node
    real(c_double), dimension(6), intent(out) :: xyzang

    interface
        integer function ResRdNode(iNode, xyzang)
            integer, intent(in) :: iNode
            double precision, dimension(6), intent(out) :: xyzang
        end function ResRdNode
    end interface

    FResRdNode = ResRdNode(iNode, xyzang)
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
    integer(c_int) function FResRdElem (iElem, nodes, ElemData)                 &
                                        BIND(C, NAME="FResRdElem")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdElem
    use, intrinsic :: ISO_C_BINDING
    implicit none
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

    interface
        integer function ResRdElem(iElem, nodes, ElemData)
            integer, intent(in) :: iElem
            integer, dimension(MAXNODESPERELEM), intent(out) :: nodes
            integer, dimension(10) :: ElemData
        end function ResRdElem
    end interface

    FResRdElem = ResRdElem(iElem, nodes(1), ElemData(1))
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
    integer(c_int) function FResRdSolBegin (key, lstep, substep, ncumit,        &
                                            kcmplx, time,  Title, DofLab)       &
                                            BIND(C, NAME="FResRdSolBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdSolBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
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
    character(len=1), dimension(406), intent(out) :: Title
    ! DofLab:           Labels for DOFs
    character(len=1), dimension(MAXDOFLABELLEN), intent(out) :: DofLab

    interface
        integer function ResRdSolBegin(key, lstep, substep, ncumit, kcmplx,     &
                                        time, Title, DofLab)
            integer, intent(in) :: key, kcmplx
            integer, intent(inout) :: lstep, substep, ncumit
            double precision, intent(inout) :: time
            character*80, dimension(5), intent(out) :: Title
            character*4, dimension(MAXDOFSPERNODE), intent(out) :: DofLab
        end function ResRdSolBegin
    end interface

    ! Internal variables for use with the call to the ANSYS
    ! ResRdSolBegin function
    integer ii, jj, idx
    character(80) :: FortTitle(5)
    character(4) :: FortDofLab(MAXDOFSPERNODE)
    
    ! Call the base function
    FResRdSolBegin = ResRdSolBegin (key, lstep, substep, ncumit, kcmplx, time,  &
                        FortTitle(1), FortDofLab(1))
    ! Copy the Title back across
    idx = 1
    do ii = 1, 5
        do jj = 1, len_trim(FortTitle(ii))
            Title(idx) = FortTitle(ii)(jj:jj)
            idx = idx + 1
        end do
        Title(idx) = C_NEW_LINE
        idx = idx + 1
    end do
    Title(idx) = C_NULL_CHAR
    ! Copy the DofLab back across
    idx = 1
    do ii = 1, 5
        do jj = 1, len_trim(FortDofLab(ii))
            DofLab(idx) = FortDofLab(ii)(jj:jj)
            idx = idx + 1
        end do
        DofLab(idx) = C_NEW_LINE
        idx = idx + 1
    end do
    DofLab(idx) = C_NULL_CHAR
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


! === FResRdDispBegin ===========================================================
!     Shim function for ResRdDispBegin
!
    subroutine FResRdDispBegin () BIND(C, NAME="FResRdDispBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdDispBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdDispBegin
    call ResRdDispBegin()
    end


! === FResRdDisp ================================================================
!     Shim function for ResRdDisp
!
    integer(c_int) function FResRdDisp (node, Disp) BIND(C, NAME="FResRdDisp")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdDisp
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! node:             Node number
    integer(c_int), intent(in) :: node
    ! Disp:             Displacements
    real(c_double), dimension(MAXDOFSPERNODE), intent(out) :: Disp
    
    interface
        integer function ResRdDisp(node, Disp)
            integer, intent(in) :: node
            double precision, dimension(MAXDOFSPERNODE), intent(out) :: Disp
        end function ResRdDisp
    end interface
    
    FResRdDisp = ResRdDisp(node, Disp(1))
    end

!    integer(c_int) function FResRdDisp (node, Disp) BIND(C, NAME="FResRdDisp")
!    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdDisp
!    use, intrinsic :: ISO_C_BINDING
!    implicit none
!    ! node:             Node number
!    integer(c_int), intent(in) :: node
!    ! Disp:             Displacements
!    real(c_double), dimension(MAXDOFSPERNODE), intent(out) :: Disp
!
!INCLUDE "impcom.inc"
!
!    interface
!        integer function ResRdDisp(node, Disp)
!            integer, intent(in) :: node
!            double precision, dimension(MAXDOFSPERNODE), intent(out) :: Disp
!        end function ResRdDisp
!    end interface
!    
!    FResRdDisp = ResRdDisp(node, Disp(1))
!    end

!*deck,ResRdDisp
!      function ResRdDisp (node,Disp)
!c primary function:    Retrieve a nodal displacement
!
!c object/library: ResRd
!
!c  input arguments:
!c     node     (int,sc,in)       - Node number
!
!c  output arguments:  none
!c     Disp     (dp,ar(nDOF),out) - Displacements
!c     ResRdDisp(int,sc,out)      - Number of displacements
!
!#include "impcom.inc"
!#include "ResRd.inc"
!
!      integer  ResRdDisp, node, i, j
!      double precision  Disp(*)
!
!      ResRdDisp = 0
!      if (iNinternal(node) .gt. 0) then
!         j = (iNinternal(node)-1)*nDOF
!         do  i = 1,nDOF
!            Disp(i) = Data(j+i)
!         enddo
!         ResRdDisp = nDOF
!      endif
!
!      return
!      end

! === FResRdDispEnd =============================================================
!     Shim function for ResRdDispEnd
!
    subroutine FResRdDispEnd () BIND(C, NAME="FResRdDispEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdDispEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdDispEnd
    call ResRdDispEnd()
    end


! === FResRdRforBegin ===========================================================
!     Shim function for ResRdRforBegin
!
    subroutine FResRdRforBegin (nRForce) BIND(C, NAME="FResRdRforBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdRforBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdRforBegin
    ! nRForce:          Number of reactions
    integer(c_int), intent(out) :: nRForce
    call ResRdRforBegin(nRForce)
    end


! === FResRdRfor ================================================================
!     Shim function for ResRdRfor
!
    integer(c_int) function FResRdRfor (node, idof, value) BIND(C, NAME="FResRdRfor")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdRfor
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! node:             External node number
    integer(c_int), intent(in) :: node
    ! idof:             Internal dof number
    integer(c_int), intent(in) :: idof
    ! value:            Value of reaction force
    real(c_double), intent(out) :: value

    interface
        integer function ResRdRfor(node, idof, value)
            integer, intent(in) :: node, idof
            double precision, intent(out) :: value
        end function ResRdRfor
    end interface

    FResRdRfor = ResRdRfor(node, idof, value)
    end


! === FResRdRforEnd =============================================================
!     Shim function for ResRdRforEnd
!
    subroutine FResRdRforEnd () BIND(C, NAME="FResRdRforEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdRforEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdRforEnd
    call ResRdRforEnd()
    end


! === FResRdBCBegin =============================================================
!     Shim function for ResRdBCBegin
!
    subroutine FResRdBCBegin (BCHeader) BIND(C, NAME="FResRdBCBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdBCBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdBCBegin
    ! BCHeader:         BC Header
    integer(c_int), dimension(40), intent(out) :: BCHeader

    call ResRdBCBegin(BCHeader)
    end


! === FResRdBCEnd ===============================================================
!     Shim function for ResRdBCEnd
!
    subroutine FResRdBCEnd () BIND(C, NAME="FResRdBCEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdBCEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdBCEnd
    call ResRdBCEnd()
    end


! === FResRdFixBegin ============================================================
!     Shim function for ResRdFixBegin
!
    subroutine FResRdFixBegin (BCHeader, nFixed) BIND(C, NAME="FResRdFixBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdFixBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdFixBegin
    ! BCHeader:         BC Header
    integer(c_int), dimension(40), intent(in) :: BCHeader
    ! nFixed:           Number of constraints
    integer(c_int), intent(out) :: nFixed

    call ResRdFixBegin(BCHeader, nFixed)
    end


! === FResRdFixOld ==============================================================
!     Shim function for ResRdFixOld
!
    integer(c_int) function FResRdFixOld (node, idof, value) BIND(C, NAME="FResRdFixOld")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdFixOld
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! node:             External node number
    integer(c_int), intent(in) :: node
    ! idof:             Internal dof number
    integer(c_int), intent(in) :: idof
    ! value:            Real, Imag, RealOld, ImagOld
    real(c_double), dimension(4), intent(out) :: value

    interface
        integer function ResRdFixOld(node, idof, value)
            integer, intent(in) :: node, idof
            double precision, dimension(4), intent(out) :: value
        end function ResRdFixOld
    end interface

    FResRdFixOld = ResRdFixOld(node, idof, value(1))
    end


! === FResRdFix =================================================================
!     Shim function for ResRdFix
!
    integer(c_int) function FResRdFix (node, idof, value) BIND(C, NAME="FResRdFix")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdFix
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! node:             External node number
    integer(c_int), intent(in) :: node
    ! idof:             Internal dof number
    integer(c_int), intent(in) :: idof
    ! value:            Real, Imag, RealOld, ImagOld
    real(c_double), dimension(4), intent(out) :: value

    interface
        integer function ResRdFix(node, idof, value)
            integer, intent(in) :: node, idof
            double precision, dimension(4), intent(out) :: value
        end function ResRdFix
    end interface

    FResRdFix = ResRdFix(node, idof, value(1))
    end


! === FResRdFixEnd ==============================================================
!     Shim function for ResRdFixEnd
!
    subroutine FResRdFixEnd () BIND(C, NAME="FResRdFixEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdFixEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdFixEnd
    call ResRdFixEnd()
    end


! === FResRdForcBegin ===========================================================
!     Shim function for ResRdForcBegin
!
    subroutine FResRdForcBegin (BCHeader, nForces) BIND(C, NAME="FResRdForcBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdForcBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdForcBegin
    ! BCHeader:         BC Header
    integer(c_int), dimension(40), intent(in) :: BCHeader
    ! nForces:          Number of forces
    integer(c_int), intent(out) :: nForces

    call ResRdForcBegin(BCHeader, nForces)
    end


! === FResRdForcOld =============================================================
!     Shim function for ResRdForcOld
!
    integer(c_int) function FResRdForcOld (node, idof, value)                   &
                                            BIND(C, NAME="FResRdForcOld")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdForcOld
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! node:             External node number
    integer(c_int), intent(in) :: node
    ! idof:             Internal dof number
    integer(c_int), intent(in) :: idof
    ! value:            Real, Imag, RealOld, ImagOld
    real(c_double), dimension(4), intent(out) :: value

    interface
        integer function ResRdForcOld(node, idof, value)
            integer, intent(in) :: node, idof
            double precision, dimension(4), intent(out) :: value
        end function ResRdForcOld
    end interface

    FResRdForcOld = ResRdForcOld(node, idof, value(1))
    end


! === FResRdForc ================================================================
!     Shim function for ResRdForc
!
    integer(c_int) function FResRdForc (node, idof, value) BIND(C, NAME="FResRdForc")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdForc
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! node:             External node number
    integer(c_int), intent(in) :: node
    ! idof:             Internal dof number
    integer(c_int), intent(in) :: idof
    ! value:            Real, Imag, RealOld, ImagOld
    real(c_double), dimension(4), intent(out) :: value

    interface
        integer function ResRdForc(node, idof, value)
            integer, intent(in) :: node, idof
            double precision, dimension(4), intent(out) :: value
        end function ResRdForc
    end interface

    FResRdForc = ResRdForc(node, idof, value(1))
    end


! === FResRdForcEnd =============================================================
!     Shim function for ResRdForcEnd
!
    subroutine FResRdForcEnd () BIND(C, NAME="FResRdForcEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdForcEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdForcEnd
    call ResRdForcEnd()
    end


! === FResRdEresBegin ===========================================================
!     Shim function for ResRdEresBegin
!
    subroutine FResRdEresBegin () BIND(C, NAME="FResRdEresBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdEresBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdEresBegin
    call ResRdEresBegin()
    end


! === FResRdEresEnd =============================================================
!     Shim function for ResRdEresEnd
!
    subroutine FResRdEresEnd () BIND(C, NAME="FResRdEresEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdEresEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdEresEnd
    call ResRdEresEnd()
    end


! === FResRdEstrBegin ===========================================================
!     Shim function for ResRdEstrBegin
!
    integer(c_int) function FResRdEstrBegin (iElem) BIND(C, NAME="FResRdEstrBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdEstrBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! iElem:            Element Number
    integer(c_int), intent(in) :: iElem

    interface
        integer function ResRdEstrBegin(iElem)
            integer, intent(in) :: iElem
        end function ResRdEstrBegin
    end interface

    FResRdEstrBegin = ResRdEstrBegin(iElem)
    end


! === FResRdEstr ================================================================
!     Shim function for ResRdEstr
!
    integer(c_int) function FResRdEstr (iStr, Str) BIND(C, NAME="FResRdEstr")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdEstr
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! iStr:             Element record number (1-25)
    integer(c_int), intent(in) :: iStr
    ! Str:              Element values
    real(c_double), dimension(MAXELERECORD), intent(out) :: Str

    interface
        integer function ResRdEstr(iStr, Str)
            integer, intent(in) :: iStr
            double precision, dimension(MAXELERECORD), intent(out) :: Str
        end function ResRdEstr
    end interface

    FResRdEstr = ResRdEstr(iStr, Str(1))
    end


! === FResRdEstrEnd =============================================================
!     Shim function for ResRdEstrEnd
!
    subroutine FResRdEstrEnd () BIND(C, NAME="FResRdEstrEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdEstrEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdEstrEnd
    call ResRdEstrEnd()
    end


! === FResRdNstrBegin ===========================================================
!     Shim function for ResRdNstrBegin
!
    subroutine FResRdNstrBegin (kNodStr) BIND(C, NAME="FResRdNstrBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdNstrBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdNstrBegin
    integer(c_int), intent(out) :: kNodStr
    call ResRdNstrBegin(kNodStr)
    end


! === FResRdNstr ================================================================
!     Shim function for ResRdNstr
!
    integer(c_int) function FResRdNstr (node, Nstr) BIND(C, NAME="FResRdNstr")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdNstr
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! node:             Node number
    integer(c_int), intent(in) :: node
    ! Nstr:             Nodal stresses
    real(c_double), dimension(6, 3), intent(out) :: Nstr

    interface
        integer function ResRdNstr(node, Nstr)
            integer, intent(in) :: node
            double precision, dimension(6, 3), intent(out) :: Nstr
        end function ResRdNstr
    end interface

    FResRdNstr = ResRdNstr(node, Nstr(1, 1))
    end


! === FResRdNstrEnd =============================================================
!     Shim function for ResRdNstrEnd
!
    subroutine FResRdNstrEnd () BIND(C, NAME="FResRdNstrEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResRdNstrEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResRdNstrEnd
    call ResRdNstrEnd()
    end
