#include <math.h>

typedef double  Float;
typedef Float   Vector[3];

#include "config.h"

#define max(a,b) 	 ((a)>(b)?(a):(b))
#define min(a,b) 	 ((a)<(b)?(a):(b))
#define Equal(a,b)       fabs((double) ((a)-(b)))< (double) tolerance
#define VectorEqual(a,b) fabs((double) ((a)[0]-(b)[0]))< (double) tolerance &&\
                         fabs((double) ((a)[1]-(b)[1]))< (double) tolerance &&\
                         fabs((double) ((a)[2]-(b)[2]))< (double) tolerance
#define VectorCopy(a,b)  (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];

typedef struct t_surface
{
  Vector          color;
  Float           diffuse;
  Float           specular;
  Float           shine;
  Float           transparency;
  Float           refraction;
}               Surface;

typedef struct t_light
{
  Vector          coords;
  Float           brightness;
}               Light;

typedef struct t_viewpoint
{
  Vector          view_from;
  Vector          view_at;
  Vector          view_up;
  Float           view_angle;
  Float           view_dist;
}               Viewpoint;

typedef struct t_object
{
  unsigned short  type;
  int             surface;
  void           *data;
}               Object;
typedef Object *ObjectPtr;

typedef struct t_spheredata
{
  Vector          center;
  Float           radius;
}               Sphere;

typedef struct t_conedata
{
  Vector          base, apex;
  Float           baseradius, apexradius;
}               Cone;

typedef struct t_polydata
{
  int             npoints;
  Vector         *points;
  struct t_polydata *next;
}               Poly;

typedef struct t_tridata
{
  Vector         *points;
  struct t_tridata *next;
}               Tri;
#define T_SPHERE (1)
#define T_CONE   (4)
#define T_POLY   (5)
#define T_TRI    (6)
