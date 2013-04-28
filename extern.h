extern int      yylinecount;
extern Viewpoint Eye;
extern Light   *Lights;
extern int      nLights;
extern int      maxLights;
extern Vector   BackgroundColor, AmbientLight;
extern Surface *Surfaces;
extern int      nSurfaces;
extern int      maxSurfaces;
extern int      ActiveSurface;
extern ObjectPtr *Prims;
extern int      nPrims;
extern int      maxPrims;
extern char    *Progname;
extern Float	tolerance;

char           *rindex();

extern int      CheckSurfaces();
extern Object  *MakeCone();
extern Object  *MakeSphere();
extern Object  *MakePoly();
extern Object  *MakeTri();
