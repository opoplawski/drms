#ifndef __SUM_RPC_H
#define __SUM_RPC_H

/*
 * This file was originally generated by rpcgen and then edited.
 * (copied from /home/jim/STAGING/src/pipe/rpc/pe_rpc.h)
 */
#include <SUM.h>
#include <rpc/rpc.h>
#include <soi_key.h>
#include <tape.h>
#include <sum_info.h>

/* !!TBD fix up these defs */
//#define OFFSITEHOST "d00.stanford.edu" //offsite hostname to send .md5 files
#define OFFSITEDIR "/dds/socdc" /* offsite dir to put .md5 files */
#define MAX_PART 64		/* max # +1 of dedicated /SUM partitions */
#define MAXSUMSETS 4		/* max # of SUM sets */
#define MAXSUMOPEN 16		/* max# of SUM opens for a single client */
#define MAXSUMREQCNT 512	/* max# of SU that can request in a single
			         * SUM_get() call */
#define MAX_STR 256		/* max size of a char[] */
#define MAXSTRING 4096
#define SUMARRAYSZ MAXSUMREQCNT	/* num of entries in SUM_t * arrays malloced */
#define RESPWAIT 30             /* secs to wait for completion response */
#define RPCMSG 2
#define TIMEOUTMSG 3
#define ERRMESS 4
#define ERRMSG 4
/* Define the storage sets used in sum->storeset */
#define JSOC 0		/* NOTE: JSOC must be 0 */
#define DSDS 1

/* Note: Do NOT change the following. They are in the database */
#define DARW 1          /* data allocate assigned as read/write */
#define DADP 2          /* data allocate deletion pending when effective date
*/
#define DAAP 4          /* data allocate archive pending */
#define DARO 8          /* data request assigned as read only */
#define DAPERM 16       /* data allocate is permanent */
#define DASAP 32        /* data allocate safe archive pending */
/* Here are sub-statuses for DAAP */
#define DAAEDDP 32      /* don't archive and when effective date mark DADP */
#define DAAPERM 64      /* archive then mark DAPERM */
#define DAADP 128       /* archive then mark DADP when effective date */
/* Here are sub-statuses for DADP */
#define DADMVA 256      /* active ds move, don't delete wd */
#define DADMVC 512      /* ds has been moved, don't mark offline when rm wd */
#define DADPDELSU 1024  /* delete_series has called SUM_delete_series() */
		        /* don't rm the records in Records.txt in the dir */


/* Handle RPC for 32 or 64 bit machines */
#ifdef _LP64
/*  extern CLIENT *
/*  clnt_create(char *host, uint32_t prog, uint32_t vers, char *proto);
/*
/*  extern enum clnt_stat
/*  clnt_call(CLIENT *clnt, uint32_t procnum, xdrproc_t inproc, char *in, 
/*		xdrproc_t outproc, char *out, struct timeval tout);
/*
/*  extern CLIENT *
/*  clnttcp_create(struct sockaddr_in *addr, unit32_t prognum,unit32_t versnum, 
/*		int *sockp, u_int sendsz, u_int recvsz);
/*
/*  extern bool_t 
/*  pmap_unset(uint32_t prognum, uint32_t versnum);
/*
/*  extern bool_t
/*  svc_register(SVCXPRT *xprt, unit32_t prognum, unit32_t versnum, 
/*		void (*dispatch) (), uint32_t protocol);
/*
/*  void
/*  svc_unregister(unit32_t prognum, unit32_t versnum);
/*
*/
#endif

#ifdef __APPLE__
#define xdr_uint_t xdr_u_int_t    
#define xdr_uint16_t xdr_u_int16_t
#define xdr_uint32_t xdr_u_int32_t
#define xdr_uint64_t xdr_u_int64_t
#endif /* __APPLE__ */

typedef char *nametype;
bool_t xdr_nametype(XDR *xdr, nametype *objp);

struct keyseg {
        nametype name;
        int key_type;
        union {
                nametype val_str;
                char *val_byte;
                u_char *val_ubyte;
                short *val_short;
                u_short *val_ushort;
                int *val_int;
                u_int *val_uint;
                long *val_long;
                u_long *val_ulong;
                uint32_t *val_uint32;
                uint64_t *val_uint64;
                float *val_float;
                double *val_double;
                FILE *val_FILE;
                TIME *val_time;
        } keyseg_u;
};
typedef struct keyseg keyseg;
bool_t xdr_keyseg(XDR *xdrs, keyseg *objp);

/* Note: this must be the same as KEY defined in soi_key.h */
struct Rkey {
        struct Rkey *next;
	keyseg key_segment;
};
typedef struct Rkey Rkey;
bool_t xdr_Rkey(XDR *xdrs, Rkey *objp);

/* This is the sum_svc program registration. Client API sends here */
#define SUMPROG ((uint32_t)0x20000611) /* 536872465 */
#define SUMVERS ((uint32_t)1)
#define SUMDO ((uint32_t)1)
#define OPENDO ((uint32_t)2)
#define CLOSEDO ((uint32_t)3)
#define GETDO ((uint32_t)4)
#define SUMRESPDO ((uint32_t)5)
#define ALLOCDO ((uint32_t)6)
#define PUTDO ((uint32_t)7)
/**********************************
#define APUPDO ((uint32_t)8)
#define DPUPDO ((uint32_t)9)
#define SUMRMDO ((uint32_t)10)
**********************************/
#define DEBUGDO ((uint32_t)11)
#define DELSERIESDO ((uint32_t)12)
#define INFODO ((uint32_t)13)
#define SHUTDO ((uint32_t)14)

extern KEY *sumdo_1();
extern KEY *opendo_1();
extern KEY *shutdo_1();
extern KEY *closedo_1();
extern KEY *getdo_1();
extern KEY *infodo_1();
extern KEY *sumrespdo_1();
extern KEY *allocdo_1();
extern KEY *putdo_1();
/**********************************
extern KEY *apupdo_1();
extern KEY *dpupdo_1();
extern KEY *sumrmdo_1();
***********************************/
extern KEY *delseriesdo_1();

/* This is the tape_svc program registration */
#define TAPEPROG ((uint32_t)0x20000612)  /* 536872466 */
#define TAPEVERS ((uint32_t)1)
#define READDO ((uint32_t)1)
#define WRITEDO ((uint32_t)2)
#define TAPERESPREADDO ((uint32_t)3)
#define TAPERESPWRITEDO ((uint32_t)4)
#define TAPERESPROBOTDO ((uint32_t)5)
#define TAPERESPROBOTDOORDO ((uint32_t)6)
#define IMPEXPDO ((uint32_t)7)
#define TAPETESTDO ((uint32_t)8)
#define ONOFFDO ((uint32_t)9)
#define DRONOFFDO ((uint32_t)10)
#define ROBOTONOFFDO ((uint32_t)11)
#define JMTXTAPEDO ((uint32_t)12)

extern KEY *readdo_1();
extern KEY *writedo_1();
extern KEY *taperespreaddo_1();
extern KEY *taperespwritedo_1();
extern KEY *taperesprobotdo_1();
extern KEY *taperesprobotdoordo_1();
extern KEY *impexpdo_1();
extern KEY *tapetestdo_1();
extern KEY *onoffdo_1();
extern KEY *dronoffdo_1();
extern KEY *robotonoffdo_1();
extern KEY *jmtxtapedo_1();

/* This is the SUM client API code response handling registration */
#define RESPPROG ((uint32_t)0x20000613)  /* 536872467 */
#define RESPVERS ((uint32_t)1)
#define RESPDO ((uint32_t)1)
#define RESULT_PEND 32		/* returned by clnt_call GETDO request 
				   when storage unit is off line */
extern KEY *respdo_1();

/* This is the tapearc program registration */
#define TAPEARCPROG ((uint32_t)0x20000614) /* 536872468 */
#define TAPEARCVERS ((uint32_t)1)
#define TAPEARCVERS0 ((uint32_t)2)
#define TAPEARCVERS1 ((uint32_t)3)
#define TAPEARCVERS2 ((uint32_t)4)
#define TAPEARCVERS3 ((uint32_t)5)
#define TAPEARCDO ((uint32_t)1)

extern KEY *tapearcdo_1();

/* This is the drive0_svc program registration */
#define DRIVE0PROG ((uint32_t)0x20000615)  /* 536872469 */
#define DRIVE0VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

extern KEY *readdrvdo_1();
extern KEY *writedrvdo_1();

/* This is the drive1_svc program registration */
#define DRIVE1PROG ((uint32_t)0x20000616)
#define DRIVE1VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive2_svc program registration */
#define DRIVE2PROG ((uint32_t)0x20000617)
#define DRIVE2VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive3_svc program registration */
#define DRIVE3PROG ((uint32_t)0x20000618)
#define DRIVE3VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive4_svc program registration */
#define DRIVE4PROG ((uint32_t)0x20000619)
#define DRIVE4VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive5_svc program registration */
#define DRIVE5PROG ((uint32_t)0x2000061a)
#define DRIVE5VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive6_svc program registration */
#define DRIVE6PROG ((uint32_t)0x2000061b)
#define DRIVE6VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive7_svc program registration */
#define DRIVE7PROG ((uint32_t)0x2000061c)
#define DRIVE7VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive8_svc program registration */
#define DRIVE8PROG ((uint32_t)0x2000061d)
#define DRIVE8VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive9_svc program registration */
#define DRIVE9PROG ((uint32_t)0x2000061e)
#define DRIVE9VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive10_svc program registration */
#define DRIVE10PROG ((uint32_t)0x2000061f)
#define DRIVE10VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the drive11_svc program registration */
#define DRIVE11PROG ((uint32_t)0x20000620)
#define DRIVE11VERS ((uint32_t)1)
#define READDRVDO ((uint32_t)1)
#define WRITEDRVDO ((uint32_t)2)

/* This is the robot0_svc program registration */
#define ROBOT0PROG ((uint32_t)0x20000627)
#define ROBOT0VERS ((uint32_t)1)
#define ROBOTDO ((uint32_t)1)
#define ROBOTDOORDO ((uint32_t)2)

extern KEY *robotdo_1();
extern KEY *robotdoordo_1();

/* This is the robot1_svc program registration */
#define ROBOT1PROG ((uint32_t)0x20000628)
#define ROBOT1VERS ((uint32_t)1)
#define ROBOTDO ((uint32_t)1)

/* This is the sum_rm program registration */
/* OBSOLETE no longer used */
#define SUMRMPROG ((uint32_t)0x20000629)
#define SUMRMVERS ((uint32_t)1)
/*#define RMRESPDO ((uint32_t)1)*/
/*extern KEY *rmrespdo_1();*/

/* This is the sum_pe_svc program registration */
#define SUMPEPROG ((uint32_t)0x2000062a) 
#define SUMPEVERS ((uint32_t)1)
#define SUMPEVERS2 ((uint32_t)2)
#define SUMPEDO ((uint32_t)1)
#define SUMPEACK ((uint32_t)2)
extern KEY *sumpedo_1();
extern KEY *sumpeack_1();

/* This is the pe/peq program registration for answers from sum_pe_svc */
#define PEPEQPROG ((uint32_t)0x2000062b)
#define PEPEQVERS ((uint32_t)1)
#define PEPEQRESPDO ((uint32_t)1)
extern KEY *pepeqdo_1();

/* This is the sum_export_svc program registration */
#define SUMEXPROG ((uint32_t)0x2000062c)
#define SUMEXVERS ((uint32_t)1)
#define SUMEXVERS2 ((uint32_t)2)
#define SUMEXDO ((uint32_t)1)
#define SUMEXACK ((uint32_t)2)
extern KEY *sumexdo_1();
extern KEY *sumexack_1();

/* This is the SUM_export() registration for answers from sum_export_svc */
#define REMSUMPROG ((uint32_t)0x2000062d)
#define REMSUMVERS ((uint32_t)1)
#define REMSUMRESPDO ((uint32_t)1)
extern KEY *respdo_1();

/* This is the jmtx program registration */
#define JMTXPROG ((uint32_t)0x2000062e) /* 536872494 */
#define JMTXVERS ((uint32_t)1)
#define JMTXDO ((uint32_t)1)
extern KEY *jmtxdo_1();

typedef struct SUM_struct
{
  SUMID_t uid;
  CLIENT *cl;            /* client handle for calling sum_rpc_svc */
  SUM_info_t *sinfo;	 /* info from sum_main for SUM_info() call */
  int debugflg;		 /* verbose debug mode if set */
  int mode;              /* bit map of various modes */
  int tdays;             /* touch days for retention */
  int group;             /* group # for the given dataseries */
  int storeset;          /* assign storage from JSOC, DSDS, etc. Default JSOC */
  int status;		 /* return status on calls. 1 = error, 0 = success */
  double bytes;
  char *dsname;          /* dataseries name */
  char *username;	 /* user's login name */
  char *history_comment; /* history comment string */
  int reqcnt;            /* # of entries in arrays below */
  uint64_t *dsix_ptr;    /* ptr to array of dsindex uint64_t */
  char **wd;		 /* ptr to array of char * */
} SUM_t;

typedef struct SUMEXP_struct
{
  SUMID_t uid;
  int reqcnt;		/* # of entries in arrays below */
  uint32_t port;	/* port #, -P, to use in scp command */
  char *cmd;            /* copy cmd (eg, scp, hpn-scp) */
  char *host;		/* hostname target of scp call */
  char **src;		/* ptr to char * of source dirs */
  char **dest;		/* ptr to char * of destination dirs */
} SUMEXP_t;

/* SUMID/SUM assignment table. One of these is put onto the sum_hdr pointer
 * each time a single client registers (opens) with sum_svc, and removed when 
 * it deregisters (closes).
*/
struct sumopened {
  struct sumopened *next;
  SUMID_t uid;
  SUM_t *sum;
  char user[16];
};
typedef struct sumopened SUMOPENED;

/* SUMID/Offcnt assignment table. An entry is made by readdo_1() in 
 * tape_svc_proc.c when a SUM_get() is made by a user and one or more storge
 * units are offline. This keeps track of unique tapeids and file numbers 
 * to read. Also, whenever a tape read completes, the offcnt is incremented
 * until the uniqcnt is reach, at which point a response
 * is finnally sent to sum_svc that the SUM_get() is complete.
*/
struct sumoffcnt {
  struct sumoffcnt *next;
  SUMID_t uid;
  int offcnt;
  int uniqcnt;
  char *tapeids[MAXSUMREQCNT];
  int tapefns[MAXSUMREQCNT];
  int reqofflinenum[MAXSUMREQCNT];
  uint64_t dsix[MAXSUMREQCNT];
};
typedef struct sumoffcnt SUMOFFCNT;
 

/* Tape queue assignment table. One of these is put onto the tq_rd_hdr or
 * tq_wrt_hdr pointer each time tape_svc gets a tape read or write request.
*/
struct tq {
  struct tq *next;
  KEY *list;
  SUMID_t uid;
  uint64_t ds_index;
  int filenum;
  char *tapeid;
  char *username;
};
typedef struct tq TQ;

/* Partition assignment table. For working directory assignments made
 * by dsds_svc, there will be a number of these tables linked onto one of
 * the pahdr_xx pointers.
*/
struct padata {
  struct padata *next;
  char *wd;
  char *effective_date;
  uint64_t sumid;
  double bytes;
  int status;
  int archsub;          /* archive pend substatuses */
  int group_id;         /* for grouping in tape archives */
  int safe_id;          /* for grouping in safe tape archives */
  uint64_t ds_index;
};
typedef struct padata PADATA;

/* Partition definition table. One for each dedicated SUM partition.
 * Initialized by sum_svc from the sum_partn_avail data base table. */
struct partition {
  char *name;           /* name of the partition */
  double bytes_total;   /* total number of bytes of the partition */
  double bytes_left;    /* bytes unassigned */
  double bytes_alloc;   /* bytes allocated by DS_Allocate() */
  int pds_set_num;      /* SUM set the part. belongs to. aka sum_set_num */
};
typedef struct partition PART;

/* Pe/uid assignment table. One of these is put onto the peuid_hdr pointer
 * each time a pe registers (opens) with dsds_svc, and removed when pe
 * deregisters (closes).
 * !!TBD see how this fits in with SUMS
*/
struct peuid {
  struct peuid *next;
  uint64_t uid;
  int petid;
};
typedef struct peuid PEUID;


SUM_t *SUM_open();
int SUM_shutdown();
int SUM_close();
int SUM_get();
int SUM_put();
int SUM_alloc();
int SUM_alloc2();
int SUM_poll();
int SUM_wait();
int SUM_Init();
int SUM_delete_series();
int SUM_export();
//int SUM_info();
int SUM_info(SUM_t *sum, uint64_t sunum, int (*history)(const char *fmt, ...));
int NC_PaUpdate();
SUMID_t SUMLIB_Open();
SUMID_t sumrpcopen_1();
void setsumopened (SUMOPENED **list, SUMID_t uid, SUM_t *sum, char *user);
SUMOPENED *getsumopened (SUMOPENED *list, SUMID_t uid);
void remsumopened (SUMOPENED **list, SUMID_t uid);
SUMOFFCNT *setsumoffcnt (SUMOFFCNT **list, SUMID_t uid, int offcnt);
SUMOFFCNT *getsumoffcnt (SUMOFFCNT *list, SUMID_t uid);
void remsumoffcnt (SUMOFFCNT **list, SUMID_t uid);
TQ *delete_q_rd_front(void);
TQ *delete_q_wrt_front(void);
TQ *delete_q_rd(TQ *p);
TQ *delete_q_wrt(TQ *p);
TQ *q_entry_make(KEY *list, SUMID_t uid, char *tapeid, int filenum, char *user, uint64_t dsix);
void tq_entry_rd_dump(char *user);
void insert_tq_entry_rd_sort(TQ *p);
void insert_tq_entry_rd(TQ *p);
void insert_tq_entry_wrt(TQ *p);
PADATA *getpadata(PADATA *list, char *wd, uint64_t sumid);
PADATA *getpauid(PADATA *list, uint64_t uid);
PADATA *getpawd(PADATA *list, char *wd);
PADATA *getpanext(PADATA *list);
PADATA *NC_PaRequest_AP (int groupset);
PADATA *NC_PaRequest_AP_60d ();
int DS_ConnectDB (char *dbname);
int DS_DisConnectDB ();
int DS_ConnectDB_Q (char *dbname);
int DS_DisConnectDB_Q ();
int DS_DataRequest (KEY *params, KEY **results);
int DS_PavailRequest();
int DS_PallocRequest();
int DS_PallocClean();
int DS_RmDo(double *bytesdel);
int DS_RmNow(char *wd, uint64_t sumid, double bytes, char *effdate, uint64_t ds_index, int archsub, double *rmbytes);
int DS_RmDoX(char *name, double bytesdel);
int DS_RmNowX(char *wd, uint64_t sumid, double bytes, char *effdate, uint64_t ds_index, int archsub, double *rmbytes);
int rmdirs(char *wd, char *root);
int SUM_Main_Update (KEY *params);
int SUMLIB_Close(KEY *params);
int SUMLIB_TapeState(char *tapeid);
int SUM_StatOffline(uint64_t ds_index);
int SUMLIB_TapeClose(char *tapeid);
int SUMLIB_TapeActive(char *tapeid);
int SUMLIB_TapeCatalog(char *tapeid);
int SUMLIB_MainTapeUpdate(KEY *params); 
int SUMLIB_EffDateUpdate(char *tapeid, int operation);
int SUMLIB_MD5info(char *tapeid);
int SUMLIB_SafeTapeUpdate(char *suname, char *tapeid, int tapefn, char *tapedate); 
int DS_SumMainDelete(uint64_t ds_index);
int SUM_StatOnline(uint64_t ds_index, char *newwd);
int DS_DataRequest_WD(KEY *params, KEY **results);
int SUMLIB_TapeUpdate(char *tapeid, int tapenxtfn, uint64_t tellblock, double totalbytes);
int SUMLIB_TapeFilenumber(char *tapeid);
int SUMLIB_TapeFindGroup(int group, double bytes, TAPE *tape);
int SUMLIB_PavailGet(double bytes, int pds_set, uint64_t uid, uint64_t sunum, KEY **results);
int SUMLIB_PavailUpdate(char *name, double bytes);
int SUMLIB_DelSeriesSU(char *file, char *series); 
int SUMLIB_InfoGet(uint64_t sunum , KEY **results);


void setpeuid(PEUID **list, uint64_t uid, int petid);
void updpadata (PADATA **list, char *wd, uint64_t sumid, char *eff_date);
PEUID *getpeuid(PEUID *list, uint64_t uid);
PEUID *getpeuidnext(PEUID *list);
void rempeuid(PEUID **list, uint64_t uid);
void setpadata(PADATA **list, char *wd, uint64_t sumid, double bytes,
int stat, int substat, char *eff_date,
int group_id, int safe_id, uint64_t ds_index);
int tape_inventory(int sim, int catalog);
void uidpadata(PADATA *new, PADATA **start, PADATA **end);
void remuidpadata(PADATA **start, PADATA **end, char *wd, uint64_t sumid);
void rempadata(PADATA **list, char *wd, uint64_t sumid);
char *get_effdate(int plusdays);
char *get_datetime();
void write_time();
void send_ack();
CLIENT *set_client_handle(uint32_t prognum, uint32_t versnum);
double du_dir(char *wd);

#endif

