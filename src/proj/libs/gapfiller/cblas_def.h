#if TYPE == FLOAT 
  #define ASUM  cblas_sasum
  #define AXPY  cblas_saxpy
  #define COPY  cblas_scopy
  #define DOT   cblas_sdot
  #define DOTU  cblas_sdot
  #define DOTC  cblas_sdot
  #define NRM2  cblas_snrm2
  #define ROT   cblas_srot
  #define ROTG  cblas_srotg
  #define ROTM  cblas_srotm
  #define ROTMG cblas_srotmg
  #define SCAL  cblas_sscal
  #define SWAP  cblas_sswap
  #define AMAX  cblas_isamax
  #define AMIN  cblas_isamin
#elif TYPE == DOUBLE 
  #define ASUM  cblas_dasum
  #define AXPY  cblas_daxpy
  #define COPY  cblas_dcopy
  #define DOT   cblas_ddot
  #define DOTU  cblas_ddot
  #define DOTC  cblas_ddot
  #define NRM2  cblas_dnrm2
  #define ROT   cblas_drot
  #define ROTG  cblas_drotg
  #define ROTM  cblas_drotm
  #define ROTMG cblas_drotmg
  #define SCAL  cblas_dscal
  #define SWAP  cblas_dswap
  #define AMAX  cblas_idamax
  #define AMIN  cblas_idamin
#elif TYPE == COMPLEXFLOAT
  #define ASUM  cblas_casum
  #define AXPY  cblas_caxpy
  #define COPY  cblas_ccopy
  #define DOT   cblas_cdotc
  #define DOTU  cblas_cdotu
  #define DOTC  cblas_cdotc
  #define NRM2  cblas_scnrm2
  #define ROT   cblas_srot
  #define ROTG  cblas_srotg
  #define ROTM  cblas_srotm
  #define ROTMG cblas_srotmg
  #define SCAL  cblas_cscal
  #define SWAP  cblas_cswap
  #define AMAX  cblas_icamax
  #define AMIN  cblas_icamin
#elif TYPE == COMPLEXDOUBLE
  #define ASUM  cblas_zasum
  #define AXPY  cblas_zaxpy
  #define COPY  cblas_zcopy
  #define DOT   cblas_zdotc
  #define DOTU  cblas_zdotu
  #define DOTC  cblas_zdotc
  #define NRM2  cblas_dznrm2
  #define ROT   cblas_drot
  #define ROTG  cblas_drotg
  #define ROTM  cblas_drotm
  #define ROTMG cblas_drotmg
  #define SCAL  cblas_zscal
  #define SWAP  cblas_zswap
  #define AMAX  cblas_izamax
  #define AMIN  cblas_izamin
#endif
