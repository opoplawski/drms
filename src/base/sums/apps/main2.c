/* This is just play stuff.
 * It was put into the cvs tree because it was used to 
 * test some cvs stuff too.
*/
#include <SUM.h>
#include <soi_key.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <rpc/rpc.h>
#include <sum_rpc.h>
#include <soi_error.h>

extern int errno;
/*static void respd();*/
/*static char datestr[32];*/
/*char *datestring();*/


KEY *rlist;             /* The global keylist returned by unpackmsg() */
FILE *logfp;
SUM_t *sum;
SUMID_t uid;
/*static int errcnt = 0;*/
int soi_errno = NO_ERROR;
int bytes, msgtag, petid, req_num, status, cnt, i, j, inum;
char **cptr;
float ftmp;
uint64_t *dsixpt;
uint64_t alloc_index;
char alloc_wd[64];
char cmd[128];
char mod_name[] = "sum_rpc";
char dsname[] = "hmi_lev1_fd_V";	/* !!TEMP name */
char hcomment[] = "this is a dummy history comment that is greater than 80 chars long to check out the code";

static struct timeval first[8], second[8];

void StartTimer(int n)
{
  gettimeofday (&first[n], NULL);
}

float StopTimer(int n)
{
  gettimeofday (&second[n], NULL);
  if (first[n].tv_usec > second[n].tv_usec) {
    second[n].tv_usec += 1000000;
    second[n].tv_sec--;
  }
  return (float) (second[n].tv_sec-first[n].tv_sec) +
    (float) (second[n].tv_usec-first[n].tv_usec)/1000000.0;
}

/* Before running this you must have the sum_svc running on d00 like so:
 * sum_svc hmidb &
 * The log file will be at /usr/local/logs/SUM/sum_svc_PID.log
*/
int main(int argc, char *argv[])
{
  /*char touched[128];*/

  if((sum = SUM_open(NULL, NULL, printf)) == 0) {
    printf("Failed on SUM_open()\n");
    exit(1);
  }
  uid = sum->uid;
  /*sum->debugflg = 1;			/* use debug mode for future calls */
  /*sum->debugflg = 0;*/
  sum->username = "production";		/* !!TEMP */
  printf("Opened with sumid = %d\n", uid);

  sum->bytes = (double)120000000;	/* 120MB */
  sum->reqcnt = 1;
  if(status = SUM_alloc(sum, printf)) {	/* allocate a data segment */
   printf("SUM_alloc() failed to alloc %g bytes. Error code = %d\n", 
			sum->bytes, status);
   SUM_close(sum, printf);
   exit(1);
  }
  cptr = sum->wd;
  dsixpt = sum->dsix_ptr;
  alloc_index = *dsixpt;
  strcpy(alloc_wd, *cptr);
  printf("Allocated %g bytes at %s with dsindex=%ld\n", 
			sum->bytes, *cptr, alloc_index);
  /* put something in the alloc wd for this test */
  sprintf(cmd, "cp -rp /home/jim/cvs/PROTO/src/SUM %s", *cptr);
  printf("cmd is: %s\n", cmd);
  system(cmd);
  sprintf(cmd, "touch %s/%s%d", *cptr, "touch", uid);
  printf("cmd is: %s\n", cmd);
  system(cmd);
  /*sum->mode = RETRIEVE + TOUCH;*/
  sum->mode = NORETRIEVE;
  sum->tdays = 5;
/*******************************************
  sum->reqcnt = 3;
  *dsixpt++ = 634590;
  *dsixpt++ = 634591; 
  *dsixpt++ = 634592; 
*******************************************/
sum->reqcnt = 1;
/*inum = 588650;			/* starting ds_index for get calls */
inum = 612311;			/* starting ds_index for get calls */
StartTimer(0);
for(j=0; j < MAXSUMREQCNT; j++) {
  *dsixpt++ = inum++;
}
  /**dsixpt = inum++;*/
sum->reqcnt = MAXSUMREQCNT;
  status = SUM_get(sum, printf); 
  switch(status) {
  case 0:			/* success. data in sum */
      cnt = sum->reqcnt;
      cptr = sum->wd;
      /*printf("The wd's found from the SUM_get() call are:\n");*/
      for(i = 0; i < cnt; i++) {
        printf("wd = %s\n", *cptr++);
      }
    break;
  case 1:			/* error */
    printf("Failed on SUM_get()\n");
    break;
  case RESULT_PEND:		/* result will be sent later */
    printf("SUM_get() call RESULT_PEND...\n");
    /* NOTE: the following is the same as doing a SUM_wait() */
    while(1) {
      if(!SUM_poll(sum)) break;
    }
    /* !!TEMP wait for second msg too!!!! */
    /*printf("About to do second SUM_wait()\n");
    /*SUM_wait(sum);
    */

      if(sum->status) {
        printf("***Error on SUM_get() call. tape_svc may have died or\n");
        printf("check /usr/local/logs/SUM/ logs for possible tape errs\n\n");
        break;
      }
      cnt = sum->reqcnt;
      cptr = sum->wd;
      printf("The wd's found from the SUM_get() call are:\n");
      for(i = 0; i < cnt; i++) {
        printf("wd = %s\n", *cptr++);
      }
    break;
  default:
    printf("Error: unknown status from SUM_get()\n");
    break;
  }
/*}*/
ftmp = StopTimer(0);
printf("\nTime sec for %d SUM_get() in one call = %f\n\n", MAXSUMREQCNT, ftmp);



  /*sum->mode = ARCH;*/
  sum->mode = TEMP;
  sum->dsname = "testname";
  sum->group = 100;
  /*sum->group = 65;*/
  /*sum->group = 101;*/
  sum->reqcnt = 1;
  dsixpt = sum->dsix_ptr;
  *dsixpt = alloc_index;	/* ds_index of alloced data segment */
  cptr = sum->wd;
  strcpy(*cptr, alloc_wd);
  sum->dsname = dsname;
  sum->history_comment = hcomment;
  /*sum->group = 99;*/
  sum->storeset = 0;
  sum->bytes = 120000000.0;
  if(SUM_put(sum, printf)) {	/* save the data segment for archiving */
    printf("Error: on SUM_put()\n");
  }
  else {
    printf("The put wd = %s\n", *sum->wd);
    printf("Marked for archive data unit ds_index=%ld\n", *dsixpt);
  }
  SUM_close(sum, printf);
}

/*!!! THIS IS IN sumsapi/sum_open.c */
/* Return ptr to "mmm dd hh:mm:ss". Uses global datestr[].
*/
/*char *datestring()
/*{
/*  struct timeval tvalr;
/*  struct tm *t_ptr;
/*  int tvalr_int;
/*                                                                              
/*  gettimeofday(&tvalr, NULL);
/*  tvalr_int = (int)tvalr.tv_sec; /* need int vrbl for this to work on sgi4*/
/*  t_ptr = localtime((const time_t *)&tvalr_int);
/*  sprintf(datestr, "%s", asctime(t_ptr));
/*  datestr[19] = NULL;
/*  return(&datestr[4]);          /* isolate the mmm dd hh:mm:ss */
/*}
*/

