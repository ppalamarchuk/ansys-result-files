#if !defined (FORTRAN)                       /* FORTRAN wrapper */
/* C style Comments cannot be include for FORTRAN files. */

/*  Note:  See also syspar.inc for system dependent information  */

/* computer.h                                                        JAS,SYS
------------------------------------------------------------------------
------- Notice - This file contains ANSYS Confidential information --------
------------------------------------------------------------------------
*/
/* *** Copyright ANSYS.  All Rights Reserved.
 * *** ansys, inc.
 */
/* Notice - changes to this header file DO NOT cause a recompile of
            all routines which reference it (it is called by impcom.inc).
            If a change is made which is other than a comment it should
            be checked in on Friday to hit the weekend full recompile.
            Changes will however force a recompile of the 744 .c routines
            which reference this header file.
*/
/*------------------------------ Description ---------------------------
\Author:        John A. Swanson (From F. J. Bogden)
\Title:         Computer macro definition header file
\Desc:          This file contains computer(machine) dependent macros
                which should be included in any file which needs to
                distinguish between computing environments.  Many but
                -not- all C preprocessors contain predefined machine
                macros. These are keyed on below as much as possible.
                When none was available, we invented one for that
                machine in which case you will need to add to your
                compile command :  cc -D<computermacro> flag  where
                <computermacro> is defined within this file.  Example,
                cc -DRS6000_SYS  is to be used for the IBM risc rs6000
                system. To be consistent, please use these as
                specified below. If a system is used which is -not-
                contained on this file, then you must add the
                appropriate changes for that system.  All variables
                defined here are usually self explanatory.  Current list :

   Machine Name            Comments         Owner
   --------                --------         -----
   NT_SYS               Any NT system
   PCWINNT_SYS          Any NT system       Lou Muccioli 
   PCWINX64_SYS                             Lou Muccioli

   LINUX_SYS            Any LINUX system    Chris Aiken
   LINUXMIC_SYS                             Chris Aiken
   LINX64_SYS                               Chris Aiken

\Function(s)
 -Primary:      To supply standard macros for different computer systems
 -Secondary:    To supply additional macros and to foster portability

    OTHER MACROS BEING DEFINED

   Name                    Comments
   ----                    --------
   PTR64                   Defined if pointers are 64 bits
   LITTLE_ENDIAN           Defined for PC, DEC
   LONGINT                 Set to integer*8 if supported, else integer 
   LONGINT2                Defined if LONGINT is integer*8
   PTRFTN                  Set to integer*8 for 64 bit pointers, else integer
   IEEE_SYS                Defined if system uses IEEE data format
   INLINE_VECT             Defined if inline vectors are faster
   NOUNDER_SYS             Systems which do not require _ on c to fortran calls
   UPCASE_SYS              Systems which user upper case for routine names
   ARGTRAIL_SYS            Systems which put all FORTRAN character variable lengths 
                           at the end of the calling signature
   LOWERCASEUNDER_SYS      Systems which use lower case and add an underscore 
                           to FORTRAN link symbols
   LOWERCASENOUNDER_SYS    Systems which use lower case and DO NOT add an 
                           underscore to FORTRAN link symbols
   UPPERCASENOUNDER_SYS    Systems which use upper case and DO NOT add an 
                           underscore to FORTRAN link symbols
   

   INT_DYNA                define integer for dyna interface routines
   REAL_DYNA               define real for dyna interface routines
   ANS_NEWCPPLIBS          Defined if the new version of c++ libraries are
                           used on a particular machine.
   CALLINT64               Defined if INTEGERs at the interface between ANSYS
                           and the Sparse solver codes are INTEGER*8

----------------------------------------------------------------------*/
#endif        /* End of first FORTRAN wrapper C comments */

/* Pavlo Palamarchuk defines */
# define PCWINNT_SYS
# define PCWINX64_SYS
# define SYSTEM_FLOAT_H


#if !defined (__COMPUTER_H__)         /* Below spans entire file */
#  define __COMPUTER_H__


#if defined (PCWINNT_SYS)                         /* ANY NT */
#  define NT_SYS
#  define LITTLE_ENDIAN
#if defined (PCWINX64_SYS)
#  define PTRFTN         integer*8
#  define LONGINT        integer*8
#  define LONGINT2
#  define PTR64
#else
#  define PTRFTN         integer
#  define LONGINT        integer*8
#  define LONGINT2
#endif
#endif

#if defined (LINUXMIC_SYS)                       /* LINUX MIC 64-bit */
#  define LINUX_SYS
#  define LITTLE_ENDIAN
#  define PTRFTN integer*8
#  define LONGINT integer*8
#  define LONGINT2
#  define PTR64
#endif

#if defined (LINX64_SYS)                         /* LINUX x86 64-bit */
#  define LINUX_SYS
#  define LITTLE_ENDIAN
#  define PTRFTN integer*8
#  define LONGINT integer*8
#  define LONGINT2
#  define PTR64
#endif


#if defined (autodouble) || defined (AUTODOUBLE)  /* DYNA DEFINITIONS */
#  define INT_DYNA      integer*8
#  define REAL_DYNA     double precision
#else
#  define INT_DYNA      integer
#  define REAL_DYNA     real
#endif

#define BIGIARRY   integer
#define BIGDARRY   double precision
#define BIGRARRY   real
#define BIGCARRY   complex*16
#define BIGLARRY   LONGINT

#define RPCPTR     integer*8

#if defined (PTR64)
#  define CALLINT64
#  define BCS_INT integer*8
#  define DSP_INT integer*8
#else
#  define BCS_INT integer*4
#  define DSP_INT integer*4
#endif


#if !defined (FORTRAN)                  /* Second FORTRAN wrapper */
/*
 ***********************************************************************
 * BELOW SECTION DEFINES SPECIAL MACHINE DEPENDANT FLAGS
 *
 * THIS SECTION IS ONLY ACTIVE IN C FILES.  DEFINITIONS THAT ARE NOT NEEDED 
 * IN FORTRAN SHOULD BE ADDED HERE.
 *
 * Use_drem :		If true, use drem() in lieu of default fmod()
 * Use_memmove :	If true, use memmove/memset in lieu of bcopy/bzero
 * Use_memcpy :		If true, use memcpy/memset in lieu of bcopy/bzero
 * UseSpecialSqrt :	If true, uses a special squartroot in lieu of sqrt()
 * UseSystem_fabs :	If true, uses the fabs() function
 *
 ***********************************************************************
 */

/* For most -ALL- systems, define below macros */

/*
 * Generic stuff for C to FORTRAN connections
 */
#define CALLTYP
#define FUNCTION
#define SUBROUTINE void


#if defined (PCWINNT_SYS)                        /* ALL NTs */
#  if !defined (NOSTDCALL)
#    undef FUNCTION
#    define FUNCTION __stdcall
#    undef SUBROUTINE
#    define SUBROUTINE void __stdcall
#    undef CALLTYP
#    define CALLTYP __stdcall
#  endif
#  define UPPERCASENOUNDER_SYS
#  define UPCASE_SYS
#  if !defined (SYSTEM_FLOAT_H)
#    define SYSTEM_FLOAT_H
#    include <float.h>
#  endif
#  if !defined (MAXDOUBLE)
#    define MAXDOUBLE       DBL_MAX
#  endif
#  if !defined (MAXFLOAT)
#    define MAXFLOAT        FLT_MAX
#  endif
#  if !defined (MINDOUBLE)
#    define MINDOUBLE       DBL_MIN
#  endif
#  if !defined (MINFLOAT)
#    define MINFLOAT        FLT_MIN
#  endif
#  define Use_memcpy
#  define ANS_NEWCPPLIBS
#endif


#if defined(PCWINX64_SYS) || defined (ARGTRAIL)   /* NT 64 or Intel NT 32 */
#  define ARGTRAIL_SYS
#endif

#if defined(PCWINNT_SYS)
#define ANS_EXPORT __declspec(dllexport)
#define ANS_IMPORT __declspec(dllimport)
#else
#define ANS_EXPORT
#define ANS_IMPORT
#endif


#if defined(LINUX_SYS)                           /* ALL LINUXs */
#  define ARGTRAIL_SYS
#  define LOWERCASEUNDER_SYS
#endif


/* stuff for passing strings from C to FORTRAN and vice versa */
#if defined (ARGTRAIL_SYS)
# define FCHAR(x) char * x
# define FCHARL(x) , int x
# define CCHAR(x) x
# define CCHARL(x) , x
#else
# define FCHAR(x) char * x , int x ## _len
# define FCHARL(x)
# define CCHAR(x) x , x ## _len
# define CCHARL(x)
#endif

#endif                  /* End of non-FORTRAN definitions */

#endif                  /* End of if that spans entire file. */
