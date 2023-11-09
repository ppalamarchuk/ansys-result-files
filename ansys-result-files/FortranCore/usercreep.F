*deck,usercreep    USERDISTRIB  parallel                                gal
      SUBROUTINE usercreep (impflg, ldstep, isubst, matId , elemId,
     &                      kDInPt, kLayer, kSecPt, nstatv, nprop,
     &                      prop  , time  , dtime , temp  , dtemp , 
     &                      toffst, Ustatev, creqv , pres  , seqv  ,
     &                      delcr , dcrda)
c*************************************************************************
c     *** primary function ***
c           Define creep laws when creep table options are
c           TB,CREEP with TBOPT=100.
c           Demonstrate how to implement usercreep subroutine 
c
c            Creep equation is 
c               dotcreq := k0 * seqv ^ n * creqv ^ m * exp (-b/T)
c
c               seqv  is equivalent effective stress (Von-Mises stress)
c               creqv is equivalent effective creep strain
c               T     is the temperature
c               k0, m, n, b are materials constants,
c
c           This model corresponds to  primary creep function  TBOPT = 1
c
c                                                          gal 10.01.1998
c
c*************************************************************************
c Copyright ANSYS.  All Rights Reserved.
c
c     input arguments
c     ===============
c      impflg   (in ,sc   ,i)             Explicit/implicit integration 
c                                         flag (currently not used)
c      ldstep   (in ,sc   ,i)             Current load step
c      isubst   (in ,sc   ,i)             Current sub step 
c      matId    (in ,sc   ,i)             number of material index
c      elemId   (in ,sc   ,i)             Element number
c      kDInPt   (in ,sc   ,i)             Material integration point
c      kLayer   (in ,sc   ,i)             Layer number
c      kSecPt   (in ,sc   ,i)             Section point
c      nstatv   (in ,sc   ,i)             Number of state variables
c      nprop    (in ,sc   ,i)             size of mat properties array    
c
c      prop     (dp ,ar(*),i)             mat properties array    
c                                         This array is passed all the creep
c                                         constants defined by command
c                                         TBDATA associated with TB,CREEP
c                                         (do not use prop(13), as it is used 
c                                         elsewhere)
c                                         at temperature temp.
c      time                               Current time
c      dtime                              Current time increment
c      temp                               Current temperature
c      dtemp                              Current temperature increment
c      toffst   (dp, sc,   i)             temperature offset from absolute zero
c      seqv     (dp ,sc  , i)             equivalent effective stress
c      creqv    (dp ,sc  , i)             equivalent effective creep strain
c      pres     (dp ,sc  , i)             hydrostatic pressure stress, -(Sxx+Syy+Szz)/3
c                                         note that: constitutive consistency is not accounted for
c                                         if creep strains are function of pressure 
c
c     input output arguments              input desc     / output desc
c     ======================              ==========       ===========
c      Ustatev  (dp,ar(*), i/o)           user defined iinternal state variables at 
c                                         time 't' / 't+dt'.
c                                         This array will be passed in containing the 
c                                         values of these variables at start of the 
c                                         time increment. They must be updated in this
c                                         subroutine to their values at the end of 
c                                         time increment, if any of these internal 
c                                         state variables are associated with the 
c                                         creep behavior.
c
c     output arguments
c     ================
c      delcr    (dp ,sc  , o)             incremental creep strain
c      dcrda    (dp,ar(*), o)             output array
c                                         dcrda(1) - derivitive of incremental creep 
c                                                    strain to effective stress
c                                         dcrda(2) - derivitive of incremental creep 
c                                                    strain to creep strain
c
c     local variables
c     ===============
c      c1,c2,c3,c4 (dp, sc, l)            temporary variables as creep constants 
c      con1        (dp ,sc, l)            temporary variable
c      t           (dp ,sc, l)            temporary variable
c
c*************************************************************************
c
c --- parameters
c
#include "impcom.inc"

      DOUBLE PRECISION ZERO
      PARAMETER        (ZERO = 0.0d0)
c
c --- argument list
c
      INTEGER          ldstep, isubst, matId , elemId,
     &                 kDInPt, kLayer, kSecPt, nstatv,
     &                 impflg, nprop
      DOUBLE PRECISION dtime , time  , temp  , dtemp , toffst,
     &                 creqv , seqv  , pres
      DOUBLE PRECISION prop(*), dcrda(*), Ustatev(nstatv)
c
c --- local variables
c
      DOUBLE PRECISION c1    , c2    , c3    , c4    ,
     &                 con1  , delcr , t
c
c*************************************************************************
c
c *** skip when stress and creep strain are all zero
      if (seqv.LE.ZERO.AND.creqv.LE.ZERO) GO TO 990
c *** add temperature off set
      t       = temp + toffst
c *** Primary creep function 
c        delcr := c1 * seqv ^ n * creqv ^ m * exp (-b/T) * dtime
      c1      = prop(1)
      c2      = prop(2)
      c3      = prop(3)
      c4      = prop(4)
c *** user need to make sure if c4 has nonzero value, temperature should be also nonzero.
      con1    = ZERO
      if(c4.ne.ZERO .and. t.gt.ZERO) con1 = c4/t
c *** calculate incremental creep strain
      if (creqv .le. TINY) creqv = sqrt(TINY)
      delcr   = ZERO
      IF(c1.gt.ZERO) delcr   = (exp( log(c1) +  c2 * log(seqv) +
     &                         c3 * log(creqv) - con1 )) * dtime
c *** derivitive of incremental creep strain to effective stress
      dcrda(1)= c2 * delcr / seqv
c *** derivitive of incremental creep strain to effective creep strain
      dcrda(2)= c3 * delcr / creqv
c *** write the effective creep strain to last state variable for verification
      if (nstatv .gt. 0) then
         Ustatev(nstatv) = creqv
      end if
 990  continue
      return
      end
