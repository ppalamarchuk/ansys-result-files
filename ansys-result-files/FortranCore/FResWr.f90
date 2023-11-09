! ===============================================================================
! Pavlo Palamarchuk
! -------------------------------------------------------------------------------
! PURPOSE:  These routines function as an interoperability shim between
!           the BINLIB fortran functions and the C family of languages.
!           Each routine collects the arguments passed to it and forwards
!           them directly to the corresponding BINLIB routine.

#include "ansysdef.h"

! === FResWrBegin ===============================================================
!     Shim function for ResWrBegin
!
    integer(c_int) function FResWrBegin (Fname, Title, JobName, Units, NumDOF,  &
                                        DOF, UserCode, MaxNode, NumNode,        &
                                        MaxElem, NumElem, MaxResultSet)         &
                                        BIND(C, NAME="FResWrBegin")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResWrBegin
    use, intrinsic :: ISO_C_BINDING
    implicit none
    ! Fname:            The name (with extension) for the file
    !                   (Limit to 260 printable characters)
    character(len=1), dimension(261), intent(in) :: Fname
    ! Title:            The Title. This is broken into strings at most 80
    !                   characters. Each subtitle in the title is separated by
    !                   a newline character
    character(len=1), dimension(163), intent(in) :: Title
    ! JobName:          The jobname from file (Limit to 32 printable characters)
    character(len=1), dimension(33), intent(in) :: JobName
    ! Units:            Unit System
    !                   = 0 - User Defined Units
    !                   = 1 - SI
    !                   = 2 - CSG
    !                   = 3 - U.S. Customary, using feet
    !                   = 4 - U.S. Customary, using inches
    !                   = 5 - MKS
    !                   = 6 - MPA
    !                   = 7 - uMKS
    integer(c_int), intent(in) :: Units
    ! NumDOF:           The number of DOF per node
    integer(c_int), intent(in) :: NumDOF
    ! DOF:              The DOFs per node
    integer(c_int), dimension(MAXDOFSPERNODE), intent(in) :: DOF
    ! UserCode:         Code for this application
    integer(c_int), intent(in) :: UserCode
    ! MaxNode:          Maximum node number used
    integer(c_int), intent(in) :: MaxNode
    ! NumNode:          Number of nodes attached to elements
    integer(c_int), intent(in) :: NumNode
    ! MaxElem:          Maximum element number used
    integer(c_int), intent(in) :: MaxElem
    ! NumElem:          Number of elements used
    integer(c_int), intent(in) :: NumElem
    ! MaxResultSet:     Maximum number of result sets (usually 1000)
    integer(c_int), intent(in) :: MaxResultSet

    interface
        integer function ResWrBegin(Nunit, Lunit, Fname, ncFname, Title,        &
            JobName, Units, NumDOF, DOF, UserCode, MaxNode, NumNode, MaxElem,   &
            NumElem, MaxResultSet)
            integer, intent(in) :: Nunit, Lunit, ncFname, Units, NumDOF,        &
                UserCode, MaxNode, NumNode, MaxElem, NumElem, MaxResultSet
            character*260, intent(in) :: Fname
            character*80, dimension(2), intent(in) :: Title
            character*8, intent(in) :: JobName
            integer, intent(in) :: DOF(*)
        end function ResWrBegin
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
    do ii=1, 261
        FortFName(ii:ii)=Fname(ii)
    end do
    ! Call the base function
    FResWrBegin = ResWrBegin (Nunit, Lunit, FortFName, ncFname, FortTitle(1),   &
                            FortJName, Units, NumDOF, DOF(1), UserCode,         &
                            MaxNode, NumNode, MaxElem, NumElem, MaxResultSet)
    end


! === FResWrEnd =================================================================
!     Shim function for ResWrEnd
!
    subroutine FResWrEnd () BIND(C, NAME="FResWrEnd")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResWrEnd
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResWrEnd
    call ResWrEnd()
    end


! === FResWrDisp ================================================================
!     Shim function for ResWrDisp
!
    integer(c_int) function FResWrDisp (node, Disp) BIND(C, NAME="FResWrDisp")
    !DEC$ ATTRIBUTES DLLEXPORT :: FResWrDisp
    use, intrinsic :: ISO_C_BINDING
    implicit none
    external ResWrDisp
    ! node:             Node number
    integer(c_int), intent(in) :: node
    ! Disp:             Displacements
    real(c_double), dimension(MAXDOFSPERNODE), intent(in) :: Disp

    call ResWrDisp(node, Disp(1))
    end

