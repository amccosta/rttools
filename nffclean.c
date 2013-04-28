#include <stdio.h>
#include <string.h>
#include <math.h>
#ifdef __STDC__
#include <stdlib.h>
#else
#include <malloc.h>
#endif

#define USAGE \
fprintf(stderr, "usage: %s [-r] -[ttol] [+Ppolys] [+Vvertices]\n", progname)

#define MAXPOLY   30000
#define MAXVERTEX 30000
#define MAXPOINT  10

#define ROUNDOFF ((double) 1.0e-7)

#define ABS(A) (fabs((double) (A)))
#define LENGTH(A) (sqrt((double) DOT_PRODUCT(A, A)))
#define DOT_PRODUCT(A, B) ((A)->x * (B)->x + (A)->y * (B)->y + (A)->z * (B)->z)
#define CROSS_PRODUCT(A, B, C)\
{\
  (C)->x = (A)->y * (B)->z - (A)->z * (B)->y;\
  (C)->y = (A)->z * (B)->x - (A)->x * (B)->z;\
  (C)->z = (A)->x * (B)->y - (A)->y * (B)->x;\
}
#define NORMALIZE(A)\
{\
  double  _len = LENGTH(A);\
  (A)->x /= _len;\
  (A)->y /= _len;\
  (A)->z /= _len;\
}
#define VECTOR(A, B, C)\
{\
  (C)->x = (B)->x - (A)->x;\
  (C)->y = (B)->y - (A)->y;\
  (C)->z = (B)->z - (A)->z;\
}
#define ADD_VECTORS(A, B, C)\
{\
  (C)->x = (A)->x + (B)->x;\
  (C)->y = (A)->y + (B)->y;\
  (C)->z = (A)->z + (B)->z;\
}

typedef struct
{
  float           x;
  float           y;
  float           z;
}               Vec;

typedef struct
{
  char            poly;
  int             n;
  int             s[MAXPOINT];
}               Poly;

Vec            *vertex_space;
Vec            *normal_space;
int             max_vertex = MAXVERTEX;

Poly           *poly_space;
int             max_poly = MAXPOLY;

int             degen_poly = 0, degen_patch = 0;

int            *s, reverse = 0;
long            ns, np;
Vec             point;
float           tolerance = ROUNDOFF;

char            progname[255];

main(argc, argv)
  int             argc;
  char           *argv[];
{
  strcpy(progname, argv[0]);

  while (argc > 1)
  {
    if (strcmp(argv[1], "-r") == 0)
      reverse = 1;
    else
    if (strncmp(argv[1], "-t", 2) == 0)
    {
      if (sscanf(&(argv[1][2]), "%f", &tolerance) != 1
          || tolerance < ROUNDOFF)
      {
        fprintf(stderr, "%s: bad tolerance\n", progname);
        USAGE;
        exit(1);
      }
    } else
    if (strncmp(argv[1], "+P", 2) == 0)
    {
      if (sscanf(&(argv[1][2]), "%d", &max_poly) != 1
          || max_poly < 1)
      {
        fprintf(stderr, "%s: bad max polygons\n", progname);
        USAGE;
        exit(1);
      }
    } else
    if (strncmp(argv[1], "+V", 2) == 0)
    {
      if (sscanf(&(argv[1][2]), "%d", &max_vertex) != 1
          || max_vertex < 1)
      {
        fprintf(stderr, "%s: bad max vertices\n", progname);
        USAGE;
        exit(1);
      }
    } else
    {
      fprintf(stderr, "%s: bad argument [%s]\n", progname, argv[1]);
      USAGE;
      exit(1);
    }
    argc--;
    argv++;
  }

  vertex_space = (Vec *) malloc(sizeof(Vec) * max_vertex);
  normal_space = (Vec *) malloc(sizeof(Vec) * max_vertex);
  poly_space = (Poly *) malloc(sizeof(Poly) * max_poly);
  if (!vertex_space || !normal_space || !poly_space)
  {
    fprintf(stderr, "%s: not enough core\n", progname);
    exit(1);
  }

  ReadWrite();

  if (degen_poly)
    fprintf(stderr, "Total degenerate polygons removed: %d\n", degen_poly);
  if (degen_patch)
    fprintf(stderr, "Total degenerate patches removed: %d\n", degen_patch);

  exit(0);
}
ReadWrite()
{
  char            key[BUFSIZ];

  /* read "key" */
  while (fscanf(stdin, "%s", key) != EOF)
  {
    if (strcmp(key, "p") == 0)
      ReadPoly();
    else
    if (strcmp(key, "pp") == 0)
      ReadPatch();
    else
    {
      if (np != 0)
	WriteObject();
      fprintf(stdout, "%s", key);
      CopyLine();
    }
  }
  if (np != 0)
    WriteObject();
}
CopyLine()
{
  char            c;
  do
  {
    putc((c = getc(stdin)), stdout);
  } while (c != '\n');
}
CheckThree(point, p, pn)
  Vec            *point;
  int             p, pn;
{
  int             p0;
  float           t;
  Vec             u, v;

  if (p == 0)
    p0 = pn - 1;
  else
    p0 = p - 1;
  VECTOR(&(vertex_space[s[p]]), &(vertex_space[s[p0]]), &u);
  NORMALIZE(&u);
  VECTOR(&(vertex_space[s[p]]), point, &v);
  NORMALIZE(&v);
  t = ABS(DOT_PRODUCT(&u, &v));
  if (t > 1.0 - ROUNDOFF)
    return (1);
  return (0);
}
StorePoint(p, pn)
  int             p, pn;
{
  int             i;

  for (i = ns - 1; i >= 0; i--)
  {
    if (ABS(vertex_space[i].x - point.x) < tolerance &&
	ABS(vertex_space[i].y - point.y) < tolerance &&
	ABS(vertex_space[i].z - point.z) < tolerance )
    {
      if (p > 0 && s[p] != s[p - 1])
      {
        if (i == s[p] || i == s[p - 1])
          return (-s[p]);
        if (CheckThree(&point, p, pn))
          return (-i);
      }
      return (i);
    }
  }
  if (ns >= MAXVERTEX)
  {
    fprintf(stderr, "%s: too many vertices\n", progname);
    exit(1);
  }
  vertex_space[ns].x = point.x;
  vertex_space[ns].y = point.y;
  vertex_space[ns].z = point.z;
  if (p > 0 && s[p] != s[p - 1])
  {
    if (CheckThree(&point, p, pn))
      return (-(ns++));
  }
  return (ns++);
}
VertFilter()
{
  int             head, tail, skip, in_vert;

  in_vert = poly_space[np].n;
  head = 0;			/* points to s[0] */
  tail = head + 1;		/* points to s[1] */
  skip = 0;			/* "skip occurred" flag */
  do
  {
    while (s[head] == s[tail])
    {
      tail++;
      if (tail == in_vert)
	goto last_vert;
      skip = 1;
    }
    if (skip)
      s[head + 1] = s[tail];
    head++;
    tail++;
  } while (tail < in_vert);

last_vert:
  if (s[0] == s[head])
    poly_space[np].n = head;
  else
    poly_space[np].n = head + 1;
}
ReadPoly()
{
  int             n, i, t;

  fscanf(stdin, "%d", &n);
  if (n > MAXPOINT)
  {
    fprintf(stderr, "%s: too many vertices for polygon\n", progname);
    exit(1);
  }
  if (np >= MAXPOLY)
  {
    fprintf(stderr, "%s: too many polygons\n", progname);
    exit(1);
  }
  poly_space[np].poly = 1;
  poly_space[np].n = n;
  s = poly_space[np].s;
  for (i = 0; i < n; i++)
  {
    fscanf(stdin, "%f %f %f", &(point.x), &(point.y), &(point.z));
    if ((t = StorePoint(i - 1, n)) >= 0)
      s[i] = t;
    else
    {
      s[i - 1] = s[i - 2];
      s[i] = -t;
    }
  }
  if (n > 3)
  {
    if (s[0] != s[n - 1] && s[0] != s[n - 2] && s[n - 1] != s[n - 2]
        && CheckThree(&(vertex_space[s[0]]), n - 1, n))
      s[n - 1] = s[0];
    if (s[1] != s[n - 1] && s[1] != s[0] && s[n - 1] != s[0]
        && CheckThree(&(vertex_space[s[1]]), 0, n))
      s[0] = s[1];
  }
  VertFilter();
  n = poly_space[np].n;
  if (n < 3)
  {
    degen_poly++;
    return;
  } else
  {
    Vec             u, v, w;

    VECTOR(&(vertex_space[s[0]]), &(vertex_space[s[1]]), &u);
    VECTOR(&(vertex_space[s[0]]), &(vertex_space[s[2]]), &v);
    CROSS_PRODUCT(&u, &v, &w);
    if (LENGTH(&w) < ROUNDOFF)
    {
      degen_poly++;
      return;
    }
  }
  np++;
}
ReadPatch()
{
  int             n, i, t;

  fscanf(stdin, "%d", &n);
  if (n > MAXPOINT)
  {
    fprintf(stderr, "%s: too many vertices for patch\n", progname);
    exit(1);
  }
  if (np >= MAXPOLY)
  {
    fprintf(stderr, "%s: too many patches\n", progname);
    exit(1);
  }
  poly_space[np].poly = 0;
  poly_space[np].n = n;
  s = poly_space[np].s;
  for (i = 0; i < n; i++)
  {
    fscanf(stdin, "%f %f %f", &(point.x), &(point.y), &(point.z));
    if ((t = StorePoint(i - 1, n)) >= 0)
      s[i] = t;
    else
    {
      s[i - 1] = s[i - 2];
      s[i] = -t;
    }
    fscanf(stdin, "%f %f %f", &(normal_space[s[i]].x), &(normal_space[s[i]].y),
           &(normal_space[s[i]].z));
  }
  if (n > 3)
  {
    if (s[0] != s[n - 1] && s[0] != s[n - 2] && s[n - 1] != s[n - 2]
        && CheckThree(&(vertex_space[s[0]]), n - 1, n))
      s[n - 1] = s[0];
    if (s[1] != s[n - 1] && s[1] != s[0] && s[n - 1] != s[0]
        && CheckThree(&(vertex_space[s[1]]), 0, n))
      s[0] = s[1];
  }
  VertFilter();
  n = poly_space[np].n;
  if (n < 3)
  {
    degen_patch++;
    return;
  }
  np++;
}
WriteObject()
{
  int             i, j;
  Vec            *v;

  for (i = 0; i < np; i++)
  {
    int             n;

    n = poly_space[i].n;
    if (poly_space[i].poly)
    {
      fprintf(stdout, "p %d\n", n);
      s = poly_space[i].s;
      if (reverse)
        for (j = n - 1; j >= 0; j--)
        {
          v = &(vertex_space[s[j]]);
          fprintf(stdout, "%g %g %g\n", v->x, v->y, v->z);
        }
      else
        for (j = 0; j < n; j++)
        {
          v = &(vertex_space[s[j]]);
          fprintf(stdout, "%g %g %g\n", v->x, v->y, v->z);
        }
    } else
    {
      fprintf(stdout, "pp %d\n", n);
      s = poly_space[i].s;
      for (j = 0; j < n; j++)
      {
        v = &(vertex_space[s[j]]);
        fprintf(stdout, "%g %g %g ", v->x, v->y, v->z);
        v = &(normal_space[s[j]]);
        if (reverse)
          fprintf(stdout, "%g %g %g\n", -(v->x), -(v->y), -(v->z));
        else
          fprintf(stdout, "%g %g %g\n", v->x, v->y, v->z);
      }
    }
  }
  np = 0;
  ns = 0;
}
