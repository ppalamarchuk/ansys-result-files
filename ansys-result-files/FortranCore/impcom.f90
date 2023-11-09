!#include "computer.h"
!
!intrinsic   int, dble, cmplx, aint, anint, nint, abs, mod, sign,            &
!            dim, max, min, sqrt, exp, log, log10, sin, cos, tan,            &
!            asin, acos, atan, atan2, sinh, cosh, tanh, dint, trim,          &
!            adjustr, adjustl, len_trim, cpu_time, date_and_time
!
!intrinsic   ichar, char, dprod, len, index, aimag, conjg
!
!#if  !defined(PCWINNT_SYS)
!    intrinsic    cdsqrt, dconjg, cdlog,  cdexp, dcmplx
!#endif
!
!#if !defined(PCWINNT_SYS) 
!    intrinsic    cdabs, dreal, dimag
!#endif
!
!#if !defined (PCWINNT_SYS)
!    intrinsic  not
!#endif
!
!!integer BIGINT,SMALLINT,INT_2_30,INT_2_30_1,                                &
!!        LONGINT BIGINT8,SMALLINT8,INT8_2,INT8_62,                           &
!!        INT8_2_62,INT8_2_62_1
!!
!!      parameter (INT8_2=2,INT8_62=62)
!!      parameter (INT_2_30=2**30)
!!      parameter (INT_2_30_1=INT_2_30-1)
!
