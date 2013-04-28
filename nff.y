%{
#include <stdio.h>
#include <math.h>
#include "defs.h"
#include "extern.h"

extern char   *yytext;
/*
 * #ifdef dos
 * extern char   *yytext;
 * #else
 * #ifdef BUFSIZ
 * #if BUFSIZ > 4096
 * char           yytext[BUFSIZ];
 * #else
 * char           yytext[4096];
 * #endif
 * #else
 * char           yytext[4096];
 * #endif
 * #endif
 */
extern FILE   *yyin;
extern int     newpoly, newtri;
extern Object *poly, *tri;
Vector        *pl, *plist;
%}

%token VIEWPOINT FROM AT UP ANGLE HITHER RESOLUTION LIGHT
%token BACKGROUND SURFACE CONE SPHERE POLYGON PATCH NUM TOKEN

%union {
	Vector  vec;
	Vector *vecl;
	double  flt;
	Object *obj;
};

%type <vec>	point primcolor TOKEN
%type <obj>	object cone sphere polygon ppatch
%type <flt>	num 

%%

scene:
	camera elementlist 
	{
	int i, l;
	  for (l = 0; l < nLights; l++)
	    Lights[l].brightness = sqrt((Float) nLights)/((Float) nLights);
	};

elementlist:
	elementlist element
	|;

element:
	light
	| background
	| surface
	| object 
	{
	char buf[80];
	  if (nPrims >= maxPrims)
	  {
	    sprintf(buf, "max objects = %d", maxPrims);
	    yyerror(buf);
	  }
	};

object:	  cone
	| sphere
	| polygon
	| ppatch;

camera:
	VIEWPOINT			/* $1      */
	FROM point			/* $2-$3   */
	AT point			/* $4-$5   */
	UP point			/* $6-$7   */
	ANGLE num 			/* $8-$9   */
	HITHER num			/* $10-$11 */
	RESOLUTION num num		/* $12-$14 */
	{
	  VectorCopy($3, Eye.view_from);
	  VectorCopy($5, Eye.view_at);
	  VectorCopy($7, Eye.view_up);
	  Eye.view_angle = ($9)/2.0;
	  Eye.view_dist = $11;
	  newpoly = 1;
	  newtri = 1;
	};

light:
	LIGHT point 
	{
	char buf[80];
	  if (nLights >= maxLights)
	  {
	    sprintf(buf, "max lights = %d", maxLights);
	    yyerror(buf);
	  }
	  VectorCopy($2, Lights[nLights].coords);
	  /* fill in brightness of the light, after we 
	   * know the number of lights sources in the scene
	   */
	  nLights++;
	}
	| LIGHT point primcolor
	{
	char buf[80];
	  if (nLights >= maxLights)
	  {
	    sprintf(buf, "max lights = %d", maxLights);
	    yyerror(buf);
	  }
	  VectorCopy($2, Lights[nLights].coords);
	  /* brightness not yet used */
	  nLights++;
	};

background:
	BACKGROUND primcolor
	{
	  VectorCopy($2, BackgroundColor);
	};

surface:
	SURFACE primcolor num num num num num 
	{
	char buf[80];
	  if (nSurfaces >= maxSurfaces)
	  {
	    sprintf(buf, "max surfaces = %d", maxSurfaces);
	    yyerror(buf);
	  }
	  VectorCopy($2, Surfaces[nSurfaces].color);
	  Surfaces[nSurfaces].diffuse = $3;
	  Surfaces[nSurfaces].specular = $4;
	  Surfaces[nSurfaces].shine = $5;
	  Surfaces[nSurfaces].transparency = $6;
	  Surfaces[nSurfaces].refraction = $7;
	  ActiveSurface = CheckSurfaces();
	  if (ActiveSurface == nSurfaces)
            nSurfaces++;
	  if (!newpoly)
	    newpoly = 1;
	  if (!newtri)
	    newtri = 1;
	};

cone:
	CONE point num point num 
	{
	  $$ = MakeCone($2, $3, $4, $5);
	  Prims[nPrims++] = $$;
	};

sphere:
	SPHERE point num 
	{
	  $$ = MakeSphere($2, $3);
	  Prims[nPrims++] = $$;
	};

polygon:
	POLYGON num 
	{
	  plist = (Vector *) calloc((int) $2, sizeof(Vector));
	  pl = plist;
	} 
	pointlist 
	{
	  if (newpoly)
	  {
	    poly = MakePoly(NULL, (int) $2, plist, 1);
	    Prims[nPrims++] = poly;
	    newpoly = 0;
	  }
	  else
	    MakePoly(poly, (int) $2, plist, 0);
	};
ppatch:
	PATCH num
        {
	  if ((int) $2 != 3)
	    fprintf(stderr, "Sorry, patches must have 3 vertices...\n");
	  plist = (Vector *) calloc(2 * (int) $2, sizeof(Vector));
	  pl = plist;
	}
	pointlist
	{
	  if (newtri)
	  {
	    tri = MakeTri(NULL, plist, 1);
	    Prims[nPrims++] = tri;
	    newtri = 0;
	  }
	  else
	    MakeTri(tri, plist, 0);
	};

primcolor:
	num num num 
	{
	  $$[0] = $1;
	  $$[1] = $2;
	  $$[2] = $3;
	}
	| TOKEN
	{
	char buf[80];

	  if (LookupColorByName(yytext, $$) == 0)
	  {
	    sprintf(buf, "cannot find color \"%s\"\n", yytext);
	    yyerror(buf) ;
	  }
	};

point:
	num num num
	{
	  $$[0] = $1;
	  $$[1] = $2;
	  $$[2] = $3;
	};

pointlist:
	pointlist point
	{
	  VectorCopy($2, (*pl));
	  pl++;
	} 
	|;

num:
	NUM
	{
	  double n;

	  sscanf(yytext, "%lf", &n);
	  $$ = n;
	};

%%

yyerror(str)
 char *str;
{
  fprintf(stderr, "%s: error at line %d\n", Progname, yylinecount);
  fprintf(stderr, "%s: %s at \"%s\"\n", Progname, str, yytext);
  exit(1);
}

ReadSceneFile(str)
 char *str;
{
  if (str == NULL) 
    yyin = stdin;
  else
  {
    if ((yyin = fopen(str, "r")) == NULL)
    {
      fprintf(stderr, "%s: cannot open %s\n", Progname, str);
      exit(1);
    }
  }
  if (yyparse())
  {
    fprintf(stderr, "%s: invalid input specification\n", Progname);
    exit(1);
  }
}
