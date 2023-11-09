*comdeck,ResRd                       User                            ansys
c   **********   ANSYS RESULT FILE READING OBJECT   **********
c   Referenced libraries:  binlib.a
c   Source Object:  ResRd.F

c    This pair of files is to assist persons who would like to write a
c    result file which can be processed by the ANSYS program.

      integer     RECLENG,       NBLK,   MAXELNODE
      parameter  (RECLENG=16384, NBLK=1, MAXELNODE=20)

c  pointers:
      pointer (piIndexToDataL,IndexToData)
      pointer (plIndexToDataL,IndexToDataL)
      pointer (plIndexL,iIndexL)
      pointer (pdDataL,Data)
      pointer (pdNodesL,dNodes)
      pointer (piEinternalL,iEinternal)
      pointer (piNinternalL,iNinternal)
      pointer (piEntitiesL,Entities)
      pointer (piIobufL,iobuf)
      pointer (piResIndexL,iResIndex)
      pointer (piResLstepL,iResLstep)
      pointer (pdResTimeL,dResTime)
      pointer (pibcNodesL,bcNodes)
      pointer (pibcDofsL,bcDofs)

      integer  IndexToData(*), iEinternal(*), iNinternal(*),
     x         Entities(*), iobuf(*), iResIndex(*), iResLstep(3,*),
     x         bcNodes(*), bcDofs(*)
      LONGINT  iIndexL(*), IndexToDataL(*)
      double precision  Data(*), dResTime(*), dNodes(*)


      LONGINT  iLocL, LocHeaderL, LocGeomHeaderL, LocSolHeaderL,
     x         LocIndexL, LocResIndexL, LocNodeListL, LocElemListL,
     x         LocElemIndexL

      integer  Header, GeomHeader, ElRecord, SolHeader,
     x         mxNode,nNode, mxType,nType, mxReal,nReal, intpdp,
     x         intplong, mxCsys,nCsys, mxElem,nElem, nCount, nDOF,
     x         curdof, ElemIndex, nRF, nSets, maxPerElem, maxPerReal,
     x         Mask, nFix, nFor, iout, MaxResult, NumResult,
     x         nXYZnode, mxSect, mxMat, numberOfMat,MatVersion

      logical  lLongRes, lDebug

      common /ResRdCom/
     x  iLocL, LocHeaderL, LocGeomHeaderL, LocSolHeaderL,
     x  LocIndexL, LocResIndexL, LocNodeListL, LocElemListL,
     x  LocElemIndexL,
     x  piIndexToDataL, plIndexL, pdDataL, piEinternalL, piNinternalL,
     x  piEntitiesL, piIobufL, piResIndexL, piResLstepL,
     x  pdResTimeL, pdNodesL, pibcNodesL, pibcDofsL, plIndexToDataL,
     x  Header(80), GeomHeader(80),
     x  ElRecord(MAXELNODE+10), SolHeader(200),
     x  mxNode,nNode, mxType,nType, mxReal,nReal, intpdp, intplong,
     x  mxCsys,nCsys, mxElem,nElem, nCount,
     x  nDOF, curdof(32), ElemIndex(25), nRF, nSets,
     x  maxPerElem, maxPerReal, Mask, nFix, nFor, iout, MaxResult,
     x  NumResult, nXYZnode, mxSect, mxMat, lLongRes, lDebug,
     x  numberOfMat,MatVersion


c          **********  ResRd.inc Variable Definitions  **********

c  Parameter         Value             Definition
c   RECLENG          16384       Use 64KB (16KW) i/o buffer for the file
c   NBLK                 1       Use only the first buffer
c   MAXELNODE           20       Most nodes per ANSYS element is 20


c  Variable              Type             Definition
c  ResTime(MAXRESULT)     dp   Time for each result data set
c  Header(80)             i    Result file header
c  LocHeader              i    Pointer to header location on file
c  GeomHeader(80)         i    Geometry Header
c  LocGeomHeader          i    Pointer to geometry header
c  intpdp                 i    Number of integers per dp (usually 2)(binlib.a)
c  iLoc                   i    Current file pointer
c  iobuf(RECLENG)         i    The i/o buffer for result file
c  ElRecord(MAXELNODE+10) i    Storage for element record
c  SolHeader(200)         i    Solution Header
c  LocSolHeader           i    Pointer to solution header
c  ResIndex(2*MAXRESULT)  i    64 bit Pointers to result sets
c  LocResIndex            i    Pointer to ResIndex
c  ResLstep(3,MAXRESULT)  i    Load Step, Substep, CumIter for each result set
c  mxNode                 i    Maximum node number
c  nNode                  i    Number of nodes attached to elements
c  nXYZnode               i    Number of nodes with coordinates
c  mxType                 i    Maximum element type
c  nType                  i    Number of defined types
c  mxReal                 i    Maximum real constant set
c  nReal                  i    Number of defined real constant sets
c  mxCsys                 i    Maximum coordinate system number
c  nCsys                  i    Number of defined coordinate systems
c  mxElem                 i    Maximum element number
c  nElem                  i    Number of defined elements
c  LocNodeList            i    Pointer to node xref list
c  LocElemList            i    Pointer to element xref list
c  LocIndex               i    Location of current working index
c  nCount                 i    Counter for current working set
c  nDOF                   i    Number of DOF per node for this solution
c  curdof(32)             i    DOFs set for each node (curdof(nDOF))
c  ElemIndex(25)          i    Index to individual element results
c  nRF                    i    Number of reaction forces
c  nSets                  i    Number of result data sets on result file
c  maxPerElem             i    Maximum number of nodes per element
c  maxPerReal             i    Maximum real set size
c  Mask                   i    Bit map for contents of results data set
c  nFix                   i    Number of nodal constraints
c  nFor                   i    Number of nodal forces
c  iout                   i    Current output (print) unit number (usually 6)
c  MaxResult              i    Maximum number of result data sets
c  NumResult              i    Number of result data sets on file    
c  mxSect                 i    Maximum section set number
c  mxMat                  i    Maximum material set number
c  lLongRes               l    true if long results file (9.0 onwards)
c  lDebug                 l    true if want debug print
c  numberOfMat            i    Number of materials
c  MatVersion             i    Material Version -101 indicates compressed data
c  
c      ****  Member functions  *****

c     function ResRdBegin (Nunit, Lunit, Fname, ncFname, Title, JobName,
c    x                     Units, NumDOF, DOF, UserCode,
c    x                     MaxNode, NumNode, MaxElem, NumElem, MaxResultSet)

c     subroutine ResRdGeomBegin (MaxType, MaxReal, MaxCsys, nXYZ)

c     subroutine ResRdSectMatBegin (MaxSect, MaxMat)

c        subroutine ResRdTypeBegin (NumType)
c           nVal = ResRdType (itype,ielc)
c        subroutine ResRdTypeEnd

c        subroutine ResRdRealBegin (NumReal,MaxPerReal)
c           nVal = ResRdReal (iReal,Rcon)
c        subroutine ResRdRealEnd

c        subroutine ResRdCsysBegin (NumCsys)
c           nVal = ResRdCsys (iCsys,Csys)
c        subroutine ResRdCsysEnd

c        subroutine ResRdSectBegin (NumSect,MaxPerSect)
c           nVal = ResRdSect (iSect,Sectdata)
c        subroutine ResRdSectEnd

c        subroutine ResRdMatBegin (NumMat,MaxPerMat)
c           nVal = ResRdMat (iMat,iprop,Matdata)
c        subroutine ResRdMatEnd

c        subroutine ResRdNodeBegin
c           nVal = ResRdNode (iNode,xyzang)
c        subroutine ResRdNodeEnd

c        subroutine ResRdElemBegin
c           nNodes = ResRdElem (iElem, nodes, ElemData)
c        subroutine ResRdElemEnd

c     subroutine ResRdGeomEnd

c     start loop on result sets

c        iReturn = ResRdSolBegin (key,lstep,substep,ncumit,kcmplx,
c    x                            time,Title,DofLab)

c           subroutine ResRdDispBegin
c              nVal = ResRdDisp (node,Disp)
c           subroutine ResRdDispEnd

c           subroutine ResRdRforBegin (nRForce)
c              nVal = ResRdRfor (node,idof,value)
c           subroutine ResRdRforEnd

c           subroutine ResRdBCBegin (nFixed,nForce)

c              subroutine ResRdFixBegin (nFixed)
c                 nVal = ResRdFix (node,idof,value)
c              subroutine ResRdFixEnd

c              subroutine ResRdForcBegin (nForce)
c                 nVal = ResRdForc (node,idof,value)
c              subroutine ResRdForcEnd

c           subroutine ResRdBCEnd

c           subroutine ResRdEresBegin

c              kerr = ResRdEstrBegin (iElem)
c                 nStr = ResRdEstr (iStr,Str)
c              subroutine ResRdEstrEnd

c           subroutine ResRdEresEnd

c        subroutine ResRdSolEnd

c     end loop on result sets

c     subroutine ResRdEnd
