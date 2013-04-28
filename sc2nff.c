/*
 * sc2nff - convert Sculpt4D scenes to nff
 *
 * sc2nff [-s] [-g] file
 *  -s generate polygonal patches for smoothed faces
 *  -g generate an additional face for ground if required
 *
 */

#include <stdio.h>
#include <math.h>
#include "SC4D.h"

#define OK 0
#define NOT_SC3D 1
#define NO_MEM 2
#define BAD_ARGS 3
#define NO_FILE 4

#define TRUE 1
#define FALSE 0

#define ROUNDOFF 1e-8

#define DOT_PRODUCT(A, B)\
((A).pos[0] * (B).pos[0] + (A).pos[1] * (B).pos[1] + (A).pos[2] * (B).pos[2])
#define VECTOR(A, B, C)\
{\
  (C).pos[0] = (B).pos[0] - (A).pos[0];\
  (C).pos[1] = (B).pos[1] - (A).pos[1];\
  (C).pos[2] = (B).pos[2] - (A).pos[2];\
}
#define ADD_VECTORS(A, B, C)\
{\
  (C).pos[0] = (B).pos[0] + (A).pos[0];\
  (C).pos[1] = (B).pos[1] + (A).pos[1];\
  (C).pos[2] = (B).pos[2] + (A).pos[2];\
}
#define LENGTH(A) ((float) sqrt(DOT_PRODUCT(A, A)))
#define NORMALIZE(A)\
{\
  float   _len = LENGTH(A);\
  if (_len != 0.0)\
  {\
    (A).pos[0] /= (double) _len;\
    (A).pos[1] /= (double) _len;\
    (A).pos[2] /= (double) _len;\
  }\
}
#define CROSS_PRODUCT(A, B, C)\
{\
  (C).pos[0] = (A).pos[1] * (B).pos[2] - (A).pos[2] * (B).pos[1];\
  (C).pos[1] = (A).pos[2] * (B).pos[0] - (A).pos[0] * (B).pos[2];\
  (C).pos[2] = (A).pos[0] * (B).pos[1] - (A).pos[1] * (B).pos[0];\
}
#define PRINT_VECTOR(S, N, A)\
{\
  fprintf(stderr, "%s %d: %g %g %g\n", (S), (N),\
          (A).pos[0], (A).pos[1], (A).pos[2]);\
}

char           *progname;

FILE           *file;
FILE           *parms;
struct eface   *faces = 0;

typedef struct
{
  double          pos[3];
}               vector;
vector         *vert = 0, *norm_vert = 0, *malloc();
double          max[3], min[3];
struct observer obs;
struct world    wrld;
long            degenerated, nface, nvert, nsmoothed = 0;
int             used_textures[6] = { 0, 0, 0, 0, 0, 0 };

int             smooth_ok = FALSE, ground_ok = FALSE;

long            lastcolor[3];
char            lasttexture;
long            firstface = TRUE;

typedef struct
{
  double          kd,		/* diffuse component */
                  ks,		/* specular */
                  sh,		/* Phong cosine power */
                  t,		/* transmittance */
                  ir;		/* index of refraction */
  char            name[20];
}               photoparms;
/* Textures used by Sculpt4D */
photoparms      texture[NTEXTURE] =
{
  { 1.0, 0.0, 0.0, 0.0, 0.0, "DULL" },
  { 0.5, 0.5, 1.0, 0.0, 0.0, "SHINY" },
  { 0.1, 0.9, 9.0, 0.0, 0.0, "MIRROR" },
  { 0.8, 0.5, 3.0, 0.0, 0.0, "LUMINOUS" },
  { 0.1, 0.9, 100.0, 0.95, 1.5, "GLASS" },
  { 0.7, 0.3, 5.0, 0.0, 0.0, "METAL" }
};
/* converts ligth intensity from 0..255 to 0..1 */
double
btof(n)
  unsigned char   n;
{
  return ((double) n / (double) 255);
}
/* Seek to IFF header */
Get_Header(file)
  FILE           *file;
{
  struct IffHeader ch;
  if (fread(&ch, sizeof(struct IffHeader), 1, file) == FALSE)
    return (FALSE);
  if (ch.form != FORM || ch.header != SC3D)
    return (FALSE);
  return (TRUE);
}
/* Seek to a given IFF chunk */
long
Get_Chunk(file, val)
  FILE           *file;
  long            val;
{
  struct ChunkHeader chunk;
  fseek(file, 12, 0);

  while (1)
  {
    if (fread(&chunk, sizeof(struct ChunkHeader), 1, file) == FALSE)
      quit(NOT_SC3D);
    if (chunk.ckID == val)
      return (chunk.ckSize);
    fseek(file, chunk.ckSize, 1);
  }
}
Get_Lamp()
{
  struct elamp    lamp;
  if (fread(&lamp, sizeof(struct elamp), 1, file) == FALSE)
    quit(NOT_SC3D);
  printf("l %ld %ld %ld\n", lamp.pos[0], lamp.pos[1], lamp.pos[2]);
}
Get_Obsv()
{
  double          y;
  int             fl;

  if (fread(&obs, sizeof(struct observer), 1, file) == FALSE)
    quit(NOT_SC3D);
  printf("v\n");
  printf("from %ld %ld %ld\n", obs.robspos[0], obs.robspos[1],
	 obs.robspos[2]);
  printf("at %ld %ld %ld\n", obs.rtarget[0], obs.rtarget[1],
	 obs.rtarget[2]);
  printf("up 0 0 1\n");

  /* assume 40 degrees for 50mm focal lens */
  y = 50.0 * tan((40.0 / 180.0) * 3.1415927);
  fl = (int) 180.0 *(atan(y / (double) obs.fl) / 3.1415927);
  printf("angle %d\n", fl);

  printf("hither 1.0\n");
  printf("resolution 512 512\n");
}
Get_Wrld()
{
  double          add_x, add_y;
  if (fread(&wrld, sizeof(struct world), 1, file) == FALSE)
    quit(NOT_SC3D);

  printf("b %g %g %g\n",
	 btof(wrld.skycol1[0]),
	 btof(wrld.skycol1[1]),
	 btof(wrld.skycol1[2]));

  /* ground generation */
  if (wrld.groundmode != 0 && ground_ok)
  {
    printf("f %g %g %g ",
	   btof(wrld.grcol1[0]),
	   btof(wrld.grcol1[1]),
	   btof(wrld.grcol1[2]));
    printf("%g %g %g %g %g\n",
	   texture[0].kd,
	   texture[0].ks,
	   texture[0].sh,
	   texture[0].t,
	   texture[0].ir);

    add_x = (max[0] - (max[0] + min[0]) / 2.0) * 50.0;
    add_x = (max[1] - (max[1] + min[1]) / 2.0) * 50.0;

    printf("p 4\n%g %g 0\n%g %g 0\n%g %g 0\n%g %g 0\n",
	   max[0] + add_x, min[1] - add_y,
	   max[0] + add_x, max[1] + add_y,
	   min[0] - add_x, max[1] + add_y,
	   min[0] - add_x, min[1] - add_y);
  }
}

vector         *
Get_Vertex()
{
  vector          v;
  struct evertex  vertex;
  if (fread(&vertex, sizeof(struct evertex), 1, file) == FALSE)
    quit(NOT_SC3D);
  v.pos[0] = (double) vertex.pos[0];
  v.pos[1] = (double) vertex.pos[1];
  v.pos[2] = (double) vertex.pos[2];
  return (&v);
}
Get_Face(face)
  struct eface   *face;
{
  if (fread(face, sizeof(struct eface), 1, file) == FALSE)
    quit(NOT_SC3D);
}
Print_Face(face)
  struct eface   *face;
{
  long            i;
  int             smoothed = FALSE;
  vector          first;

  if (face->texture > 127 && smooth_ok == TRUE)
    smoothed = TRUE;

  face->texture &= 127;		/* turn smoothing off */
  if (face->texture == NTEXTURE)
  {
    degenerated++;
    return;
  }
  used_textures[face->texture]++;

  if (face->color[0] != lastcolor[0] ||
      face->color[1] != lastcolor[1] ||
      face->color[2] != lastcolor[2] ||
      face->texture != lasttexture || firstface == TRUE)
  {
    printf("f %g %g %g ", btof(face->color[0]),
	   btof(face->color[1]),
	   btof(face->color[2]));
    printf("%g %g %g %g %g\n", texture[face->texture].kd,
	   texture[face->texture].ks,
	   texture[face->texture].sh,
	   texture[face->texture].t,
	   texture[face->texture].ir);
    used_textures[face->texture]++;

    lastcolor[0] = face->color[0];
    lastcolor[1] = face->color[1];
    lastcolor[2] = face->color[2];
    lasttexture = face->texture;
    firstface = FALSE;
  }
  if (smoothed)
  {
    printf("pp 3\n");
    first = norm_vert[face->evertexi[0]];
    for (i = 0; i < 3; i++)
    {
      printf("%g %g %g ",
	     vert[face->evertexi[i]].pos[0],
	     vert[face->evertexi[i]].pos[1],
	     vert[face->evertexi[i]].pos[2]);
      if (DOT_PRODUCT(first, norm_vert[face->evertexi[i]]) < 0)
	printf("%g %g %g\n",
	       -norm_vert[face->evertexi[i]].pos[0],
	       -norm_vert[face->evertexi[i]].pos[1],
	       -norm_vert[face->evertexi[i]].pos[2]);
      else
	printf("%g %g %g\n",
	       norm_vert[face->evertexi[i]].pos[0],
	       norm_vert[face->evertexi[i]].pos[1],
	       norm_vert[face->evertexi[i]].pos[2]);

    }
  } else
  {
    printf("p 3\n");
    for (i = 0; i < 3; i++)
      printf("%g %g %g\n", vert[face->evertexi[i]].pos[0],
	     vert[face->evertexi[i]].pos[1],
	     vert[face->evertexi[i]].pos[2]);
  }
}
/* compare the photometric description of two faces for sorting */
int
compar(f1, f2)
  struct eface   *f1, *f2;
{
  if (f1->color[0] > f2->color[0])
    return (1);
  else if (f1->color[0] < f2->color[0])
    return (-1);
  else if (f1->color[1] > f2->color[1])
    return (1);
  else if (f1->color[1] < f2->color[1])
    return (-1);
  else if (f1->color[2] > f2->color[2])
    return (1);
  else if (f1->color[2] < f2->color[2])
    return (-1);
  else if (f1->texture > f2->texture)
    return (1);
  else if (f1->texture < f2->texture)
    return (-1);
  else
    return (0);
}
quit(error)
  int             error;
{
  switch (error)
  {
  case OK:
    fclose(file);
    free(vert);
    free(norm_vert);
    free(faces);
    break;
  case NOT_SC3D:
    fprintf(stderr, "%s: not a valid Sculpt 3D Iff file\n", progname);
    if (vert != 0)
      free(vert);
    fclose(file);
    break;
  case NO_MEM:
    if (vert != 0)
      free(vert);
    if (norm_vert != 0)
      free(norm_vert);
    if (faces != 0)
      free(faces);
    fclose(file);
    fprintf(stderr, "%s: not enough memory\n", progname);
    break;
  case BAD_ARGS:
    fprintf(stderr,
            "usage: %s [-s] [-g] 'Sculpt4d scene file' > outfile\n", progname);
    break;
  case NO_FILE:
    fprintf(stderr, "%s: unable to open file\n", progname);
    break;
  default:
    break;
  }
  exit();
}

void
stats()
{
  long            i;

  fprintf(stderr, "vertices: %d\n", nvert);
  fprintf(stderr, "faces: %d (%d smoothed)\n", nface, nsmoothed);
  fprintf(stderr, "bounding box: %g %g; %g %g; %g %g;\n",
	  min[0], max[0], min[1], max[1], min[2], max[2]);

  switch (wrld.groundmode)
  {
  case 0:
    fprintf(stderr, "no ground\n");
    break;
  case 1:
    fprintf(stderr, "solid ground\n");
    break;
  case 2:
    fprintf(stderr, "checkered ground\n");
    break;
  }

  switch (obs.lens)
  {
  case 0:
    fprintf(stderr, "normal lens (50mm)\n");
    break;
  case 1:
    fprintf(stderr, "wide angle lens (28mm)\n");
    break;
  case 2:
    fprintf(stderr, "telephoto lens (135mm)\n");
    break;
  case 3:
    fprintf(stderr, "special lens (%dmm)\n", obs.spfl);
    break;
  }
  if (obs.manexpflg)
  {
    fprintf(stderr, "manual exposure (override %d)\n",
	    obs.expoverride);
    if (obs.expoverride != obs.manexpval)
    {
      fprintf(stderr, "exposure value %d\n", obs.manexpval);
    }
  } else
  {
    fprintf(stderr, "autoexposure (override %d)\n", obs.expoverride);
  }

  fprintf(stderr, "degenerated polygons: %d\n", degenerated);

  fprintf(stderr, "textures : ");
  for (i = 0; i < NTEXTURE; i++)
  {
    if (used_textures[i] != 0)
      fprintf(stderr, "%s: %d ", texture[i].name,
	      used_textures[i]);
  }

  fprintf(stderr, "\n");
}
main(argc, argv)
  int             argc;
  char          **argv;
{
  long            i, j;
  long            size;
  int             (*ptr) () = compar;

  progname = argv[0];
  if (argc == 1)
    quit(BAD_ARGS);
  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-s") == 0)
      smooth_ok = TRUE;
    if (strcmp(argv[i], "-g") == 0)
      ground_ok = TRUE;
  }
  if ((file = fopen(argv[argc - 1], "r")) == FALSE)
    quit(NO_FILE);

  if (Get_Header(file) == FALSE)
    quit(NOT_SC3D);

  printf("#\n# %s\n#\n", argv[argc - 1]);

  Get_Chunk(file, OBSV);
  Get_Obsv();

  size = Get_Chunk(file, LAMP);
  for (i = 0; i < size / sizeof(struct elamp); i++)
    Get_Lamp();

  /* read vertices and compute bounding box */
  size = Get_Chunk(file, VERT);
  nvert = size / (long) sizeof(struct evertex);

  if ((vert = malloc(nvert * sizeof(vector))) == 0)
    quit(NO_MEM);
  if ((norm_vert = malloc(nvert * sizeof(vector))) == 0)
    quit(NO_MEM);

  for (i = 0; i < nvert; i++)
    for (j = 0; j < 3; j++)
      norm_vert[i].pos[j] = 0.0;

  vert[0] = *Get_Vertex();
  for (j = 0; j < 3; j++)
  {
    max[j] = vert[0].pos[j];
    min[j] = vert[0].pos[j];
  }

  for (i = 1; i < nvert; i++)
  {
    vert[i] = *Get_Vertex();
    for (j = 0; j < 3; j++)
    {
      if (vert[i].pos[j] > max[j])
	max[j] = vert[i].pos[j];
      if (vert[i].pos[j] < min[j])
	min[j] = vert[i].pos[j];
    }
  }

  Get_Chunk(file, WRLD);
  Get_Wrld();

  /* read faces */
  size = Get_Chunk(file, FACE);
  if ((faces = (struct eface *) malloc(size)) == 0)
    quit(NO_MEM);
  nface = size / (long) sizeof(struct eface);
  for (i = 0; i < nface; i++)
    Get_Face(&faces[i]);

  /* sort faces to minimize photometric descriptions */
  qsort(faces, nface, sizeof(struct eface), ptr);

  /* compute normal vectors for vertices if needed */
  if (smooth_ok)
  {
    for (i = 0; i < nface; i++)
    {
      if (faces[i].texture > 127)
      {
	vector          u, v, result;

	nsmoothed++;
	VECTOR(vert[faces[i].evertexi[0]], vert[faces[i].evertexi[1]], u);
	VECTOR(vert[faces[i].evertexi[0]], vert[faces[i].evertexi[2]], v);
	CROSS_PRODUCT(u, v, result);

	if (LENGTH(result) < ROUNDOFF)
	{
	  faces[i].texture = NTEXTURE;
	  break;
	}
	NORMALIZE(result);

	for (j = 0; j < 3; j++)
	{
	  if (DOT_PRODUCT(result, norm_vert[faces[i].evertexi[j]]) < 0)
	  {
	    result.pos[0] = -result.pos[0];
	    result.pos[1] = -result.pos[1];
	    result.pos[2] = -result.pos[2];
	  }
	  ADD_VECTORS(norm_vert[faces[i].evertexi[j]],
		      result, norm_vert[faces[i].evertexi[j]]);
	}
      }
    }
  }
  for (i = 1; i < nvert; i++)
  {
    NORMALIZE(norm_vert[i]);
  }

  for (i = 0; i < nface; i++)
    Print_Face(&faces[i]);

  stats();

  quit(OK);
}
