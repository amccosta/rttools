#include "defs.h"

int             yylinecount = 1;
Viewpoint       Eye;
Light          *Lights;
int             nLights = 0;
int             maxLights = MAXLIGHTS;
Vector          BackgroundColor, AmbientLight = {0.2, 0.2, 0.2};
Surface        *Surfaces;
int             nSurfaces = 0;
int             maxSurfaces = MAXSURFACES;
int             ActiveSurface;
ObjectPtr      *Prims;
int             nPrims = 0;
int             maxPrims = MAXPRIMS;
char           *Progname;
int             newpoly, newtri;
Object         *poly, *tri;
Float		tolerance = 0.5e-8;
