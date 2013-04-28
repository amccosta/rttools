#include <stdio.h>
#include "defs.h"
#include "extern.h"
#ifndef NULL
#define NULL (0)
#endif
CheckSurfaces()
{
  int             i;

  for (i = 0; i < nSurfaces; i++)
    if (VectorEqual(Surfaces[i].color, Surfaces[nSurfaces].color) &&
	Equal(Surfaces[i].diffuse, Surfaces[nSurfaces].diffuse) &&
	Equal(Surfaces[i].specular, Surfaces[nSurfaces].specular) &&
	Equal(Surfaces[i].shine, Surfaces[nSurfaces].shine) &&
	Equal(Surfaces[i].transparency, Surfaces[nSurfaces].transparency))
      return i;
  return nSurfaces;
}

Object         *
MakeSphere(centerpoint, radius)
  Vector          centerpoint;
  Float           radius;
{
  Object         *obj;
  Sphere         *sd;

  obj = (Object *) malloc(sizeof(Object));
  if (!obj)
  {
    fprintf(stderr, "%s: not enough memory\n", Progname);
    exit(1);
  }
  obj->type = T_SPHERE;
  obj->surface = ActiveSurface;

  sd = (Sphere *) malloc(sizeof(Sphere));
  if (!sd)
  {
    fprintf(stderr, "%s: not enough memory\n", Progname);
    exit(1);
  }
  VectorCopy(centerpoint, sd->center);
  sd->radius = radius;

  obj->data = (void *) sd;
  return (obj);
}

Object         *
MakeCone(basepoint, baseradius, apexpoint, apexradius)
  Vector          basepoint, apexpoint;
  Float           baseradius, apexradius;
{
  Object         *obj;
  Cone           *cd;

  obj = (Object *) malloc(sizeof(Object));
  if (!obj)
  {
    fprintf(stderr, "%s: not enough memory\n", Progname);
    exit(1);
  }
  obj->type = T_CONE;
  obj->surface = ActiveSurface;

  cd = (Cone *) malloc(sizeof(Cone));
  if (!cd)
  {
    fprintf(stderr, "%s: not enough memory\n", Progname);
    exit(1);
  }
  VectorCopy(basepoint, cd->base);
  cd->baseradius = baseradius;
  VectorCopy(apexpoint, cd->apex);
  cd->apexradius = apexradius;

  obj->data = (void *) cd;
  return (obj);
}

Object         *
MakePoly(poly, npoints, points, new)
  Object         *poly;
  int             npoints;
  Vector         *points;
  int             new;
{
  Object         *obj;
  Poly           *pd;

  if (new)
  {
    obj = (Object *) malloc(sizeof(Object));
    if (!obj)
    {
      fprintf(stderr, "%s: not enough memory\n", Progname);
      exit(1);
    }
    obj->type = T_POLY;
    obj->surface = ActiveSurface;
  } else
    obj = poly;

  pd = (Poly *) malloc(sizeof(Object));
  if (!pd)
  {
    fprintf(stderr, "%s: not enough memory\n", Progname);
    exit(1);
  }
  pd->npoints = npoints;
  pd->points = points;
  if (new)
    pd->next = NULL;
  else
    pd->next = (Poly *) obj->data;
  obj->data = (void *) pd;

  return (obj);
}

Object         *
MakeTri(tri, points, new)
  Object         *tri;
  Vector         *points;
  int             new;
{
  Object         *obj;
  Tri            *td;

  if (new)
  {
    obj = (Object *) malloc(sizeof(Object));
    if (!obj)
    {
      fprintf(stderr, "%s: not enough memory\n", Progname);
      exit(1);
    }
    obj->type = T_TRI;
    obj->surface = ActiveSurface;
  } else
    obj = tri;

  td = (Tri *) malloc(sizeof(Object));
  if (!td)
  {
    fprintf(stderr, "%s: not enough memory\n", Progname);
    exit(1);
  }
  td->points = points;
  if (new)
    td->next = NULL;
  else
    td->next = (Tri *) obj->data;
  obj->data = (void *) td;

  return (obj);
}
