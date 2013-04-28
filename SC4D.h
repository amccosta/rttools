
#define MakeID(a,b,c,d)  (((long)(a))<<24L | ((long)(b))<<16L | (c)<<8 | (d))

#define FORM MakeID('F','O','R','M')
#define SC3D MakeID('S','C','3','D')
#define LAMP MakeID('L','A','M','P')
#define OBSV MakeID('O','B','S','V')
#define WRLD MakeID('W','R','L','D')
#define VERT MakeID('V','E','R','T')
#define EDGE MakeID('E','D','G','E')
#define FACE MakeID('F','A','C','E')
#define HIER MakeID('H','I','E','R')
#define VNAM MakeID('V','N','A','M')
#define LNAM MakeID('L','N','A','M')
#define PATH MakeID('P','A','T','H')
#define KNOT MakeID('K','N','O','T')
#define SPLN MakeID('S','P','L','N')

#define NTEXTURE 6
#define T_DULL 0
#define T_SHINY 1
#define T_MIRROR 2
#define T_LUMINOUS 3
#define T_GLASS 4
#define T_METAL 5

typedef long    ID;
struct IffHeader
{
  ID              form;
  long            size;
  ID              header;
};

struct ChunkHeader
{
  ID              ckID;
  long            ckSize;
};

struct elamp
{
  long            pos[3];
  long            brightness;
  unsigned char   color[3];
  char            pad;
};

struct observer
{
  long            obsmode;
  long            fl;
  long            altresh;
  long            threshold;
  long            robspos[3];
  long            rtarget[3];
  short           hires;
  short           lace;
  short           lens;
  short           manexpflg;
  long            spfl;
  long            expoverride;
  long            manexpval;
  long            picsize;
  long            tilt;
  long            aamode;
  short           dithatten;
  short           colorlock;
  short           explock;
  short           expexp;
  short           expmant;
  unsigned char   wfcol1[4], wfcol2[4];
  short           displayearly;
  short           dummy[30];
};

struct world
{
  long            groundmode;
  long            skymode;
  long            checkscale;
  unsigned char   backbright[3];
  unsigned char   grcol1[3], grcol2[3];
  unsigned char   skycol1[3], skycol2[3];
  long            dummy[20];
};

struct evertex
{
  long            pos[3];
};

struct eedge
{
  long            evertexi[2];
};

struct eface
{
  long            evertexi[3];
  unsigned char   color[3];
  unsigned char   texture;
};

struct ename
{
  short           object;
  short           name;
};
