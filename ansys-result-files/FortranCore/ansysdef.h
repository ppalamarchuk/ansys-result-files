
/*****************************************************************************
   This include file is used for the ANSYS solution database objects.  The values
   in this file should match those found in ansysdef.inc.  Any changes should be
   included in both files
*****************************************************************************/

/***********  custom definitions                  ************/
# define MAXDOFSPERNODE   32
# define MAXREALS         100
# define MAXNODESPERELEM  24

/***********  definitions for erinqr              ************/
# define ER_ERRORFLAG     1                  /* ansysdef.inc */
# define ER_ERRORFILE     2                  /* ansysdef.inc */
# define ER_NUMNOTE       3                  /* ansysdef.inc */
# define ER_NUMWARNING    4                  /* ansysdef.inc */
# define ER_NUMERROR      5                  /* ansysdef.inc */
# define ER_NUMFATAL      6                  /* ansysdef.inc */
# define ER_MAXMESSAGE    7                  /* ansysdef.inc */
# define ER_ERRORLEVEL    8                  /* ansysdef.inc */
# define ER_MAXCOMMAND    9                  /* ansysdef.inc */
# define ER_NUMCOMMAND    10                  /* ansysdef.inc */
# define ER_UICLEAR       11                  /* ansysdef.inc */
# define ER_NOMOREMSG     12                  /* ansysdef.inc */
# define ER_FILEOPEN      13                  /* ansysdef.inc */
# define ER_INTERERROR    14                  /* ansysdef.inc */
# define ER_KEYOPTTEST    15                  /* ansysdef.inc */
# define ER_MIXEDREV      16                  /* ansysdef.inc */
# define ER_MESHING       17                  /* ansysdef.inc */
# define ER_OPTLOOPING    19                  /* ansysdef.inc */
# define ER_KEYPDSTEST    20                  /* ansysdef.inc */
# define ER_PDSLOOPING    21                  /* ansysdef.inc */
# define ER_STOPKEY       25                  /* ansysdef.inc */
# define ER_INTERRUPT     28                  /* ansysdef.inc */

/***********  define database inquire constants   ************/
# define DB_SELECTED      1                  /* ansysdef.inc */
# define DB_NUMDEFINED    12                 /* ansysdef.inc */
# define DB_NUMSELECTED   13                 /* ansysdef.inc */
# define DB_MAXDEFINED    14                 /* ansysdef.inc */
# define DB_MAXRECLENG    15                 /* ansysdef.inc */
# define DB_OBJFLAG      -777                /* ansysdef.inc */
# define DB_NEXT         -888                /* ansysdef.inc */
# define DB_MODIFIED     -999                /* ansysdef.inc */
# define DB_INTERNAL     -9999               /* ansysdef.inc */

/***********  define element data constants       ************/
# define EL_DIM           10                 /* ansysdef.inc */
# define IELCSZ           200                /* echprm.inc   */
# define MAXLIB           300                /* echprm.inc   */

/***********  define some constants               ************/
# define BSEARCH_THRESH   8

/***********  define some material property constants  *******/
# define NLKWVAL          2                  /* ansysdef.inc */
# define NLKWMAX          14                 /* ansysdef.inc */
# define NLKWSIZE         NLKWVAL*NLKWMAX    /* ansysdef.inc */
# define NLPROP           80                 /* mpcom.inc    */
# define NAPROP           158                /* mpcom.inc    */

/***********  define some load constants          ************/
# define BODYLOAD_TEMP    1                  /* ansysdef.inc */
# define BODYLOAD_FLUE    2                  /* ansysdef.inc */
# define BODYLOAD_HGEN    3                  /* ansysdef.inc */
# define BODYLOAD_DGEN    4                  /* ansysdef.inc */
# define BODYLOAD_MVDI    5                  /* ansysdef.inc */
# define BODYLOAD_CHRG    6                  /* ansysdef.inc */
# define BODYLOAD_JS      7                  /* ansysdef.inc */
# define BODYLOAD_VLTG    8                  /* ansysdef.inc */
# define BODYLOAD_EF      9                  /* ansysdef.inc */
# define BODYLOAD_H       10                 /* ansysdef.inc */
# define BODYLOAD_PORT    11                 /* ansysdef.inc */
# define BODYLOAD_FVIN    12                 /* ansysdef.inc */
# define BODYLOAD_SRCE    13                 /* ansysdef.inc */
# define BODYLOAD_VMEN    14                 /* ansysdef.inc */
# define BODYLOAD_INIS    15                 /* ansysdef.inc */
# define BODYLOAD_IMPD    16                 /* ansysdef.inc */
# define BODYLOAD_HGIN    17                 /* ansysdef.inc */
# define BODYLOAD_FSOU    18                 /* ansysdef.inc */
# define BODYLOAD_FORC    19                 /* ansysdef.inc */
# define BODYLOAD_VELO    20                 /* ansysdef.inc */
# define BODYLOAD_MASS    21                 /* ansysdef.inc */
# define BODYLOAD_SPRE    22                 /* ansysdef.inc */
# define BODYLOAD_FPBC    23                 /* ansysdef.inc */
# define BODYLOAD_SELV    24                 /* ansysdef.inc */
# define MAXBODYLOADTYPE  24                 /* ansysdef.inc */

# define SURFLOAD_PRES    1                  /* ansysdef.inc */
# define SURFLOAD_CONV    2                  /* ansysdef.inc */
# define SURFLOAD_IMPD    3                  /* ansysdef.inc */
# define SURFLOAD_DFLU    4                  /* ansysdef.inc */
# define SURFLOAD_FLGS    5                  /* ansysdef.inc */
# define SURFLOAD_CHRG    6                  /* ansysdef.inc */
# define SURFLOAD_PORT    7                  /* ansysdef.inc */
# define SURFLOAD_RAD     8                  /* ansysdef.inc */
# define SURFLOAD_FSIN    9                  /* ansysdef.inc */
# define SURFLOAD_RDSF    10                 /* ansysdef.inc */
# define SURFLOAD_SHLD    12                 /* ansysdef.inc */
# define SURFLOAD_FFLX    13                 /* ansysdef.inc */
# define SURFLOAD_PERB    14                 /* ansysdef.inc */
# define SURFLOAD_VFRC    15                 /* ansysdef.inc */
# define SURFLOAD_HFLU    16                 /* ansysdef.inc */
# define SURFLOAD_ATTN    17                 /* ansysdef.inc */
# define MAXSURFLOADTYPE  17                 /* ansysdef.inc */

/***********  define some element result contants  ***********/
# define ELMRESULT_FORC   1                  /* ansysdef.inc */
# define ELMRESULT_EPEL   2                  /* ansysdef.inc */
# define ELMRESULT_EPPL   3                  /* ansysdef.inc */
# define ELMRESULT_EPCR   4                  /* ansysdef.inc */
# define ELMRESULT_EPTH   5                  /* ansysdef.inc */
# define ELMRESULT_EULR   6                  /* ansysdef.inc */
# define ELMRESULT_FLUX   7                  /* ansysdef.inc */
# define ELMRESULT_MSCS   8                  /* ansysdef.inc */
# define ELMRESULT_NONL   9                  /* ansysdef.inc */
# define ELMRESULT_MSCN   10                 /* ansysdef.inc */
# define ELMRESULT_ESTR   11                 /* ansysdef.inc */
# define ELMRESULT_HGEN   12                 /* ansysdef.inc */
# define ELMRESULT_CONT   13                 /* ansysdef.inc */
# define ELMRESULT_LOCI   14                 /* ansysdef.inc */
# define ELMRESULT_BSTR   15                 /* ansysdef.inc */
# define ELMRESULT_SVAR   16                 /* ansysdef.inc */
# define ELMRESULT_SSTR   17                 /* ansysdef.inc */
# define ELMRESULT_CURR   18                 /* ansysdef.inc */
# define ELMRESULT_TEMP   19                 /* ansysdef.inc */
# define ELMRESULT_NFOR   20                 /* ansysdef.inc */
# define ELMRESULT_ENGR   21                 /* ansysdef.inc */
# define ELMRESULT_GRAD   22                 /* ansysdef.inc */
# define ELMRESULT_NSTR   23                 /* ansysdef.inc */
# define ELMRESULT_DPAR   24                 /* ansysdef.inc */
# define ELMRESULT_EPDI   25                 /* ansysdef.inc */
# define ELMRESULT_ENMR   26                 /* ansysdef.inc */
# define MAXELMRESULTTYPE 26                 /* ansysdef.inc */

/***********  define MPI constants                 ***********/
# define MPI_NUMCPU       1                  /* ansysdef.inc */
# define MPI_THISCPU      2                  /* ansysdef.inc */
# define MPI_WORLD        3                  /* ansysdef.inc */
# define MPI_NUMCPU_ORIG  4                  /* ansysdef.inc */
# define MPI_THISCPU_ORIG 5                  /* ansysdef.inc */
# define MPI_WORLD_ORIG   6                  /* ansysdef.inc */
# define MPI_WORLD_MYSELF_ONLY 7             /* ansysdef.inc */
# define MPI_BUFFERSIZE   524288             /* ansysdef.inc */

/***********  define processor constants           ***********/
# define PPMAXPROC        256                   /* ppcom.inc */
# define MAX_NUMCPU       8192                 /* mpicom.inc */

/***********  define statistics constants          ***********/
# define STATLVLMAX       10             /* statTableCom.inc */
# define STAT_TOTAL       1                  /* ansysdef.inc */
# define STAT_PREP7       2                  /* ansysdef.inc */
# define STAT_SOLUTION    3                  /* ansysdef.inc */
# define STAT_POST1       4                  /* ansysdef.inc */
# define STAT_CHECK       5                  /* ansysdef.inc */
# define STAT_OBJECTS     6                  /* ansysdef.inc */
# define STAT_FORM        7                  /* ansysdef.inc */
# define STAT_SOLVER      8                  /* ansysdef.inc */
# define STAT_OUTPUT      9                  /* ansysdef.inc */
# define STAT_COMBINE     10                 /* ansysdef.inc */
# define STAT_LINESEARCH  11                 /* ansysdef.inc */
# define STAT_CONTACT     12                 /* ansysdef.inc */
# define STAT_CONVERGENCE 13                 /* ansysdef.inc */
# define STAT_GATHER      14                 /* ansysdef.inc */
# define STAT_ASSEMBLE    15                 /* ansysdef.inc */
# define STAT_PRECOND     16                 /* ansysdef.inc */
# define STAT_AMULTX      17                 /* ansysdef.inc */
# define STAT_PCSOLVE     18                 /* ansysdef.inc */
# define STAT_INPUTK      19                 /* ansysdef.inc */
# define STAT_ORDERK      20                 /* ansysdef.inc */
# define STAT_FACTORK     21                 /* ansysdef.inc */
# define STAT_SOLVEK      22                 /* ansysdef.inc */
# define STAT_DOMORDER    23                 /* ansysdef.inc */
# define STAT_TOTSOLVE    24                 /* ansysdef.inc */

/***********  define word sizes                    ***********/
#if defined(FULL_64)
# define BYTPINT           8                 /* syspar.inc   */
# define BYTPLONG          8                 /* syspar.inc   */
# define BYTPDP            8                 /* syspar.inc   */
#else
# define BYTPINT           4                 /* syspar.inc   */
# define BYTPLONG          8                 /* syspar.inc   */
# define BYTPDP            8                 /* syspar.inc   */
#endif

/***********  define word sizes                    ***********/
# define LENEXT            8                 /* syspar.inc   */
# define LENNAM          248                 /* syspar.inc   */
# define LENFNM          260                 /* syspar.inc   */

/***********  define sparse solver key array lengths  ********/
# define NUMINTKEYS       51                 /* ansysdef.inc */
# define NUMDPKEYS        21                 /* ansysdef.inc */

/***********  define command line constants        ***********/
# define CMD_MAX_LENG    640                 /* ansysdef.inc */

/***********  define command line constants        ***********/
# define MAXFLD            6                 /* mfldcm.inc   */

