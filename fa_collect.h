
#ifdef DEBUG
#define DEBUG_LEVEL 5 /*1=0x01 main, 2=0x02 libera threads -->, 3=0x04 ,4=0x08 <--,5=0x10 arch thread -->,6=0x20,7=0x40,8=0x80 <--,>8=0xff*/
#else
#define DEBUG_LEVEL 0
#endif
/*threads*/
#define MAX_LIB_THREADS 4
#define BUF 255
/*Libera UDP*/
//#define BUF_SIZE 16384
#define RCV_BUF_SIZE 64  //MAX Size of the Libera data struct,bc different size of Photon&Spark
#define BUF_SIZE 32 //Size of the Libera Photon data struct,the interesting spark size has also the same pattern.
#define PAYLOAD_BUF_SIZE 16 //bytes for the arch struct 
#define MAX_ERR_LENGTH  1024
#define SAMPLES 2048
#define STRLEN 30

/*
struct libera_payload {
    int32_t sum;
    int32_t x;
    int32_t y;
#if LIBERA_GROUPING == 0
    uint16_t counter;
    struct libera_status status;
#elif LIBERA_GROUPING == 1
    struct libera_status status;
    uint16_t counter;
#else
    #error "Invalid value for LIBERA_GROUPING, must be 0 or 1"
#endif

}
*/

struct libData {
   int nb;
   int *ex_flag;
   unsigned short debug_switch; //debug switch 
   unsigned short dlevel; //Debug level
   long stat; 
   char msg[BUF];
   char ipaddr[STRLEN];
   unsigned short port;
   ssize_t received;
   int     fd[2];
   //char sum[STRLEN];
   //int     fdsum[2];
};

//char sip[MAX_LIB_THREADS][STRLEN]={"193.149.14.50","193.149.14.221","193.149.14.222","193.149.14.79"}; //source ips i.e. LiberaDev
char sip[MAX_LIB_THREADS][STRLEN]={"10.10.8.101","10.10.8.104","10.10.8.106","10.10.8.112"}; //source ips i.e. LiberaDev
//const unsigned short sport[MAX_LIB_THREADS]={2048,2047,2049,2046 };//Libera Client (Source) Ports
const unsigned short dport[MAX_LIB_THREADS]={2048,2047,2049,2046};//Dest. Ports
const unsigned short dbswitch[MAX_LIB_THREADS]={1,0,0,0};// switch for selected lib thread debugging
//char sum[MAX_LIB_THREADS][STRLEN]={"XSPM0F1B001L:sum","XTPM0F1B004L:sum","XBPM0F1B006L:sum","XSPM0F1B012L:sum"}; //source ips i.e. LiberaDev


struct archData {
   long stat; 
   int *ex_flag;
   unsigned short debug_switch; //debug switch
   unsigned short dlevel; //Debug level
   char msg[BUF];
   char ipaddr[STRLEN];
   unsigned short aport;
   //unsigned short cport;
   ssize_t received;
   int     fd[MAX_LIB_THREADS][2];
};
char archIP[STRLEN]="127.0.0.1"; 
const unsigned short aport=32768;//archPort
//const unsigned short cport=2046; //Client Port
const unsigned short dbaswitch=0;// switch for selected arch thread debugging
