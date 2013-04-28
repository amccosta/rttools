/****************************************
 * NFF to SFF format converter          *
 ****************************************/

#include <stdio.h>
#include "defs.h"
#include "extern.h"

#define ONE ((Float) 0.99)

#define METAL_FACTOR(s) (Float) ((s) < 3.0 ? 0.0 : ((s) > 10.0 ? 1.0 : 0.5))

typedef struct t_vertex
{
  Vector         *coords;
  struct t_vertex *next;
}               Vertex;

int             nVertex;
Vertex         *vertextop;

static float    scale = 1.0;
#define VAL(x) ((scale > 0.99 && scale < 1.01) ? (x) : (x) * scale)

main(argc, argv)
  int             argc;
  char           *argv[];
{
  char           *infilename = NULL;
  char           *outfilename = NULL;

  if ((Progname = rindex(argv[0], '/')) == NULL)
    Progname = argv[0];
  else
    Progname++;

  if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 's')
  {
    if (sscanf(&argv[1][2], "%f", &scale) != 1)
    {
      fprintf(stderr, "%s: bad scale\n", Progname);
      exit(1);
    }
    if (scale < 1.0e-6 || scale > 1.0e+12)
    {
      fprintf(stderr, "%s: scale out of range\n", Progname);
      exit(1);
    }
    scale = 1.0 / scale;
    argc--;
    argv++;
  }
  if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 't')
  {
    if (sscanf(&argv[1][2], "%lf", &tolerance) != 1)
    {
      fprintf(stderr, "%s: bad tolerance\n", Progname);
      exit(1);
    }
    if (tolerance < 1.0e-12 || tolerance > 1.0e-3)
    {
      fprintf(stderr, "%s: tolerance out of range\n", Progname);
      exit(1);
    }
    argc--;
    argv++;
  }
  if (argc > 1 && argv[1][0] == '+' && argv[1][1] == 'O')
  {
    if (sscanf(&argv[1][2], "%d", &maxPrims) != 1 || maxPrims < 1)
    {
      fprintf(stderr, "%s: bad max number of objects\n", Progname);
      exit(1);
    }
    argc--;
    argv++;
  }
  if (argc > 1 && argv[1][0] == '+' && argv[1][1] == 'L')
  {
    if (sscanf(&argv[1][2], "%d", &maxLights) != 1 || maxLights < 1)
    {
      fprintf(stderr, "%s: bad max number of lights\n", Progname);
      exit(1);
    }
    argc--;
    argv++;
  }
  if (argc > 1 && argv[1][0] == '+' && argv[1][1] == 'S')
  {
    if (sscanf(&argv[1][2], "%d", &maxSurfaces) != 1 || maxSurfaces < 1)
    {
      fprintf(stderr, "%s: bad max number of surfaces\n", Progname);
      exit(1);
    }
    argc--;
    argv++;
  }
  if (argc > 1)
  {
    fprintf(stderr,
            "usage: %s [-sscale] [-ttol] [+Oobjs] [+Llights] [+Ssurfs]\n",
            Progname);
    exit(1);
  }

  Lights = (Light *) malloc(sizeof(Light) * maxLights);
  Surfaces = (Surface *) malloc(sizeof(Surface) * maxSurfaces);
  Prims = (ObjectPtr *) malloc(sizeof(ObjectPtr) * maxPrims);
  if (!Lights || !Surfaces || !Prims)
  {
    fprintf(stderr, "%s: not enough memory\n");
    exit(1);
  }
  
  ReadSceneFile(infilename);
  WriteSceneFile(outfilename);
}
WriteSceneFile(str)
  char           *str;
{
  FILE           *outfile;
  int             surface, i, j;
  Float           temp, refraction;
  Vector          objscale, objorigin;
  Sphere         *sd;
  Cone           *cd;
  Poly           *pd;
  Tri            *td;
  char           *author = "Antonio Costa / INESC-Norte";

  if (str == NULL)
    outfile = stdout;
  else if ((outfile = fopen(str, "w")) == NULL)
  {
    fprintf(stderr, "%s: cannot open %s\n", Progname, str);
    exit(1);
  }
  fprintf(outfile, "view\n");
  fprintf(outfile, "%g %g %g\n", VAL(Eye.view_from[0]), VAL(Eye.view_from[1]),
	  VAL(Eye.view_from[2]));
  fprintf(outfile, "%g %g %g\n", VAL(Eye.view_at[0]), VAL(Eye.view_at[1]),
	  VAL(Eye.view_at[2]));
  fprintf(outfile, "%g %g %g\n", Eye.view_up[0], Eye.view_up[1],
	  Eye.view_up[2]);
  temp = Eye.view_angle;
  fprintf(outfile, "%g %g\n", temp, temp);
  fprintf(outfile, "colors\n");
  fprintf(outfile, "%g %g %g\n", min(BackgroundColor[0], ONE),
	  min(BackgroundColor[1], ONE),
	  min(BackgroundColor[2], ONE));
  fprintf(outfile, "%g %g %g\n", min(AmbientLight[0], ONE),
	  min(AmbientLight[1], ONE),
	  min(AmbientLight[2], ONE));
  fprintf(outfile, "lights\n");
  for (i = 0; i < nLights; i++)
  {
    fprintf(outfile, "1 %g %g %g ", VAL(Lights[i].coords[0]),
            VAL(Lights[i].coords[1]), VAL(Lights[i].coords[2]));
    temp = min(Lights[i].brightness, ONE);
    fprintf(outfile, "%g %g %g\n", temp, temp, temp);
  }
  fprintf(outfile, "\nsurfaces\n");
  for (i = 0; i < nSurfaces; i++)
  {
    fprintf(outfile, "1 %g %g %g ", min(Surfaces[i].color[0], ONE),
	    min(Surfaces[i].color[1], ONE),
	    min(Surfaces[i].color[2], ONE));
    temp = min(Surfaces[i].diffuse, ONE);
    fprintf(outfile, "%g %g %g ", temp, temp, temp);
    temp = min(Surfaces[i].specular, ONE);
    fprintf(outfile, "%g %g %g ", temp, temp, temp);
    fprintf(outfile, "%g ", Surfaces[i].shine);
    fprintf(outfile, "%g ", METAL_FACTOR(Surfaces[i].shine));
    temp = min(Surfaces[i].transparency, ONE);
    fprintf(outfile, "%g %g %g\n", temp, temp, temp);
  }
  fprintf(outfile, "\nobjects\n");
  for (i = 0; i < nPrims; i++)
  {
    surface = Prims[i]->surface;
    refraction = Surfaces[surface].refraction;
    fprintf(outfile, "%d %d %g ", Prims[i]->type, ++surface,
	    (refraction == 0.0) ? 1.0 : refraction);
    switch (Prims[i]->type)
    {
    case T_SPHERE:
      sd = (Sphere *) Prims[i]->data;
      fprintf(outfile, "%g %g %g %g\n",
	      VAL(sd->center[0]), VAL(sd->center[1]),
	      VAL(sd->center[2]), VAL(sd->radius));
      break;
    case T_CONE:
      cd = (Cone *) Prims[i]->data;
      fprintf(outfile, "%g %g %g %g %g %g %g %g\n",
	      VAL(cd->base[0]), VAL(cd->base[1]), VAL(cd->base[2]),
              VAL(cd->baseradius),
	      VAL(cd->apex[0]), VAL(cd->apex[1]), VAL(cd->apex[2]),
              VAL(cd->apexradius));
      break;
    case T_POLY:
      pd = (Poly *) Prims[i]->data;
      PolyScaleOrigin(pd, &objscale[0], &objorigin[0]);
      fprintf(outfile, "%g %g %g %g %g %g -\n",
	      objorigin[0], objorigin[1], objorigin[2],
	      objscale[0], objscale[1], objscale[2]);
      nVertex = 0;
      for (; pd != NULL; pd = pd->next)
      {
	fprintf(outfile, "%d", pd->npoints);
	for (j = 0; j < pd->npoints; j++)
	  fprintf(outfile, " %d", VertexCode(pd->points[j]));
	fprintf(outfile, "\n");
      }
      fprintf(outfile, "\n");
      for (; vertextop != NULL; vertextop = vertextop->next)
	fprintf(outfile, "%g %g %g\n",
		(VAL((*vertextop->coords)[0]) - objorigin[0]) / objscale[0],
		(VAL((*vertextop->coords)[1]) - objorigin[1]) / objscale[1],
		(VAL((*vertextop->coords)[2]) - objorigin[2]) / objscale[2]);
      fprintf(outfile, "\n");
      break;
    case T_TRI:
      td = (Tri *) Prims[i]->data;
      TriScaleOrigin(td, &objscale[0], &objorigin[0]);
      fprintf(outfile, "%g %g %g %g %g %g -\n",
	      objorigin[0], objorigin[1], objorigin[2],
	      objscale[0], objscale[1], objscale[2]);
      for (; td != NULL; td = td->next)
	fprintf(outfile,
		"%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
	(VAL(td->points[0][0]) - objorigin[0]) / objscale[0],
	(VAL(td->points[0][1]) - objorigin[1]) / objscale[1],
	(VAL(td->points[0][2]) - objorigin[2]) / objscale[2],
	td->points[1][0], td->points[1][1], td->points[1][2],
	(VAL(td->points[2][0]) - objorigin[0]) / objscale[0],
	(VAL(td->points[2][1]) - objorigin[1]) / objscale[1],
	(VAL(td->points[2][2]) - objorigin[2]) / objscale[2],
	td->points[3][0], td->points[3][1], td->points[3][2],
	(VAL(td->points[4][0]) - objorigin[0]) / objscale[0],
	(VAL(td->points[4][1]) - objorigin[1]) / objscale[1],
	(VAL(td->points[4][2]) - objorigin[2]) / objscale[2],
	td->points[5][0], td->points[5][1], td->points[5][2]);
      fprintf(outfile, "\n");
      break;
    }
  }

  fprintf(outfile, "\n%s\n", author);
  if (outfile != stdout)
    fclose(outfile);
}
VertexCode(point)
  Vector         *point;
{
  int             v = 1;
  static Vertex  *vertexbottom;
  Vertex         *vd;

  if (nVertex == 0)
  {
    vertextop = (Vertex *) malloc(sizeof(Vertex));
    if (!vertextop)
    {
      fprintf(stderr, "%s: not enough memory\n");
      exit(1);
    }
    vertextop->coords = point;
    vertextop->next = NULL;
    vertexbottom = vertextop;
    return (++nVertex);
  }
  for (vd = vertextop; vd != NULL; vd = vd->next, v++)
    if (VectorEqual(*point, *(vd->coords)))
      return (v);

  vd = (Vertex *) malloc(sizeof(Vertex));
  if (!vd)
  {
    fprintf(stderr, "%s: not enough memory\n");
    exit(1);
  }
  vd->coords = point;
  vd->next = NULL;
  vertexbottom->next = vd;
  vertexbottom = vd;
  return (++nVertex);
}
PolyScaleOrigin(pd, objscale, objorigin)
  Poly		 *pd;
  Vector	 *objscale, *objorigin;
{
  Vector          minimum, maximum;
  int		  i;
  Float		  t;

  maximum[0] = maximum[1] = maximum[2] = -1.0 / tolerance;
  minimum[0] = minimum[1] = minimum[2] = 1.0 / tolerance;
  for (; pd != NULL; pd = pd->next)
    for (i = 0; i < pd->npoints; i++)
    {
      t = VAL(pd->points[i][0]);
      if (t > maximum[0])
        maximum[0] = t;
      if (t < minimum[0])
        minimum[0] = t;
      t = VAL(pd->points[i][1]);
      if (t > maximum[1])
        maximum[1] = t;
      if (t < minimum[1])
        minimum[1] = t;
      t = VAL(pd->points[i][2]);
      if (t > maximum[2])
        maximum[2] = t;
      if (t < minimum[2])
        minimum[2] = t;
    }
  (*objscale)[0] = maximum[0] - minimum[0];
  if ((*objscale)[0] < tolerance)
    (*objscale)[0] = 1.0;
  (*objscale)[1] = maximum[1] - minimum[1];
  if ((*objscale)[1] < tolerance)
    (*objscale)[1] = 1.0;
  (*objscale)[2] = maximum[2] - minimum[2];
  if ((*objscale)[2] < tolerance)
    (*objscale)[2] = 1.0;
  (*objorigin)[0] = minimum[0];
  (*objorigin)[1] = minimum[1];
  (*objorigin)[2] = minimum[2];
  return 1;
}
TriScaleOrigin(td, objscale, objorigin)
  Tri		 *td;
  Vector	 *objscale, *objorigin;
{
  Vector          minimum, maximum;
  int		  i;
  Float		  t;
  double	  l;

  maximum[0] = maximum[1] = maximum[2] = -1.0 / tolerance;
  minimum[0] = minimum[1] = minimum[2] = 1.0 / tolerance;
  for (; td != NULL; td = td->next)
  {
    for (i = 0; i < 6; i += 2)
    {
      t = VAL(td->points[i][0]);
      if (t > maximum[0])
        maximum[0] = t;
      if (t < minimum[0])
        minimum[0] = t;
      t = VAL(td->points[i][1]);
      if (t > maximum[1])
        maximum[1] = t;
      if (t < minimum[1])
        minimum[1] = t;
      t = VAL(td->points[i][2]);
      if (t > maximum[2])
        maximum[2] = t;
      if (t < minimum[2])
        minimum[2] = t;
    }
    for (i = 1; i < 6; i += 2)
    {
      t = td->points[i][0];
      l = t * t;
      t = td->points[i][1];
      l += t * t;
      t = td->points[i][2];
      l += t * t;
      l = sqrt(l);
      if (l < tolerance)
      {
        fprintf(stderr, "%s: null normal\n", Progname);
        exit(1);
      }
      td->points[i][0] /= l;
      td->points[i][1] /= l;
      td->points[i][2] /= l;
    }
  }
  (*objscale)[0] = maximum[0] - minimum[0];
  if ((*objscale)[0] < tolerance)
    (*objscale)[0] = 1.0;
  (*objscale)[1] = maximum[1] - minimum[1];
  if ((*objscale)[1] < tolerance)
    (*objscale)[1] = 1.0;
  (*objscale)[2] = maximum[2] - minimum[2];
  if ((*objscale)[2] < tolerance)
    (*objscale)[2] = 1.0;
  (*objorigin)[0] = minimum[0];
  (*objorigin)[1] = minimum[1];
  (*objorigin)[2] = minimum[2];
  return 1;
}
