/* AutoCAD DXF to NFF Translator */
/* Version 1.0 - Antonio Costa  INESC-Norte 1991 */

#include <stdio.h>
#include <string.h>

#define BUFFER_MAX 2048
#define STRING_MAX 128
#define SIZE_MAX 10

#define SMALL (0.001)
#define VERY_SMALL (0.00001)

int             getline();
void            writeobj();
void            writesurf();
void            lookupcolor();
int             checkdegen();

#ifdef unix
char           *strstr();
#endif

int             groupcode;
char            linbuf[BUFFER_MAX];
int             primitives = 0, degenerates = 0;
char            curobj[STRING_MAX];
int             curcolor;
float           xcoords[SIZE_MAX];
float           ycoords[SIZE_MAX];
float           zcoords[SIZE_MAX];
float           floats[SIZE_MAX];
float           angles[SIZE_MAX];
int             ints[SIZE_MAX];
float           max_x, max_y, max_z, min_x, min_y, min_z;

main(argc, argv)
  int             argc;
  char           *argv[];
{
  if (argc > 1)
  {
    fprintf(stderr, "%s: AutoCad DXF to NFF translator\n", argv[0]);
    fprintf(stderr, "usage is %s <infile >outfile\n", argv[0]);
    exit(1);
  }
  fprintf(stdout, "#\n# Converted from AutoCad DXF to NFF\n");
  fprintf(stdout, "# DXF translator - Antonio Costa, INESC-Norte 1991\n#\n");
  fprintf(stdout, "v\nfrom X Y Z\nat X Y Z\nup 0 1 0\n");
  fprintf(stdout, "angle 50\nhither 1\nresolution 512 512\n");
  fprintf(stdout, "b 0.1 0.5 0.7\n");
  fprintf(stdout, "l X Y Z\n");

  curobj[0] = '\0';		/* not working on any object currently */
  curcolor = 7;			/* and it also doesn't have a color yet... */
  max_x = max_y = max_z = -10000000.0;
  min_x = min_y = min_z = 10000000.0;

find:
  while (!feof(stdin))	/* run file up to the "ENTITIES" section */
  {
    if (getline())		/* get a group code and a line */
      goto stopit;
    if (groupcode == 0)		/* file section mark */
    {
      if (strstr(linbuf, "EOF"))
	goto stopit;
      if (strstr(linbuf, "SECTION"))
      {
	if (getline())
	  goto stopit;
	if (groupcode != 2)
	  continue;
	if (strstr(linbuf, "ENTITIES"))
	  break;
      }
    }
  }
  while (!feof(stdin))		/* scan ENTITIES section */
  {
    if (getline())		/* get a group code and a line */
      break;
    if (groupcode < 10)		/* cardinal group codes */
    {
      switch (groupcode)
      {
      case 0:			/* start of entity, table, file sep */
	if (strstr(linbuf, "EOF"))
	{
	  writeobj();		/* dump object */
	  goto stopit;
	}
	if (strstr(linbuf, "ENDSEC"))
	{
	  writeobj();		/* dump object */
	  goto find;
	}
	writeobj();		/* dump old object */
	curobj[0] = '\0';	/* reset object */
	curcolor = 7;
	strcpy(curobj, linbuf);	/* get new */
	break;
      case 1:			/* primary text value for entity (?) */
	break;
      case 2:			/* block name, attribute tag, etc */
      case 3:			/* other names */
      case 4:
	break;
      case 5:			/* entity handle (hex string) */
	break;
      case 6:			/* line type name */
	break;
      case 7:			/* text style name */
	break;
      case 8:			/* layer name */
	break;
      case 9:			/* variable name ID (only in header) */
	break;
      }
    } else if (groupcode >= 10 && groupcode < 19)	/* Some X coord */
    {
      sscanf(linbuf, "%f", &(xcoords[groupcode - 10]));
      if (xcoords[groupcode - 10] > max_x)
	max_x = xcoords[groupcode - 10];
      if (xcoords[groupcode - 10] < min_x)
	min_x = xcoords[groupcode - 10];
    } else if (groupcode >= 20 && groupcode < 29)	/* Some Y coord */
    {
      sscanf(linbuf, "%f", &(ycoords[groupcode - 20]));
      if (ycoords[groupcode - 20] > max_y)
	max_y = ycoords[groupcode - 20];
      if (ycoords[groupcode - 20] < min_y)
	min_y = ycoords[groupcode - 20];
    } else if (groupcode >= 30 && groupcode < 38)	/* Some Z coord */
    {
      sscanf(linbuf, "%f", &(zcoords[groupcode - 30]));
      if (zcoords[groupcode - 30] > max_z)
	max_z = zcoords[groupcode - 30];
      if (zcoords[groupcode - 30] < min_z)
	min_z = zcoords[groupcode - 30];
    } else if (groupcode == 38)	/* entity elevation if nonzero */
    {
    } else if (groupcode == 39)	/* entity thickness if nonzero */
    {
    } else if (groupcode >= 40 && groupcode < 49)	/* misc floats */
    {
      sscanf(linbuf, "%f", &(floats[groupcode - 40]));
    } else if (groupcode == 49)	/* repeated value groups */
    {
    } else if (groupcode >= 50 && groupcode < 59)	/* misc angles */
    {
      sscanf(linbuf, "%f", &(angles[groupcode - 50]));
    } else if (groupcode == 62)	/* Color number */
    {
      sscanf(linbuf, "%6d", &curcolor);
    } else if (groupcode == 66)	/* "entities follow" flag */
    {
    } else if (groupcode >= 70 && groupcode < 79)	/* misc ints */
    {
      sscanf(linbuf, "%f", &(ints[groupcode - 70]));
    } else if (groupcode == 210 || groupcode == 220 || groupcode == 230)
    {				/* X, Y, Z components of extrusion direction */
    }
  }
stopit:
  fprintf(stdout, "# Bounded by:\n");
  fprintf(stdout, "# Max (%g, %g, %g)\n", max_x, max_y, max_z);
  fprintf(stdout, "# Min (%g, %g, %g)\n", min_x, min_y, min_z);
  fflush(stdout);
  fprintf(stderr, "Total objects output: %d\n", primitives);
  fprintf(stderr, "Total degenerate triangles removed: %d\n", degenerates);
  fprintf(stderr, "X values range from %g to %g\n", min_x, max_x);
  fprintf(stderr, "Y values range from %g to %g\n", min_y, max_y);
  fprintf(stderr, "Z values range from %g to %g\n", min_z, max_z);
  exit(0);
}

int 
getline()			/* read a group code and the next line */
{
  fgets(linbuf, BUFFER_MAX, stdin);	/* get a line */
  if (feof(stdin))
    return (1);
  sscanf(linbuf, "%3d", &groupcode);	/* scan out group code */
  fgets(linbuf, BUFFER_MAX, stdin);	/* get a line */
  if (feof(stdin))
    return (1);
  return (0);
}

void 
writeobj()
{
  if (strstr(curobj, "LINE"))	/* a VERY skinny cylinder! */
  {
    if (xcoords[0] == xcoords[1] && ycoords[0] == ycoords[1]
        && zcoords[0] == zcoords[1])
    {
      degenerates++;
      return;
    }
    writesurf(curcolor);
    fprintf(stdout, "c\n%g %g %g %g\n%g %g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0], SMALL,
            xcoords[1], ycoords[1], zcoords[1], SMALL);
    fprintf(stdout, "s %g %g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0], SMALL);
    fprintf(stdout, "s %g %g %g %g\n",
            xcoords[1], ycoords[1], zcoords[1], SMALL);
    return;
  } else if (strstr(curobj, "POINT"))	/* an itty, bitty sphere! */
  {
    writesurf(curcolor);
    fprintf(stdout, "s %g %g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0], SMALL);
    return;
  } else if (strstr(curobj, "CIRCLE"))	/* a VERY flat cone! */
  {
    writesurf(curcolor);
    fprintf(stdout, "c\n%g %g %g %g\n%g %g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0] + SMALL, floats[0],
            xcoords[0], ycoords[0], zcoords[0] - SMALL, VERY_SMALL);
    return;
  } else if (strstr(curobj, "ARC"))	/* not implemented for now */
  {
    return;
  } else if (strstr(curobj, "TRACE"))	/* 2 back-to-back triangles */
  {
    if (checkdegen(0, 1, 2))
    {
      degenerates++;
      return;
    }
    writesurf(curcolor);
    fprintf(stdout, "p 3\n%g %g %g\n%g %g %g\n%g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0],
            xcoords[1], ycoords[1], zcoords[1],
            xcoords[2], ycoords[2], zcoords[2]);

    if (checkdegen(0, 3, 2))
    {
      degenerates++;
      return;
    }
    writesurf(curcolor);
    fprintf(stdout, "p 3\n%g %g %g\n%g %g %g\n%g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0],
            xcoords[3], ycoords[3], zcoords[3],
            xcoords[2], ycoords[2], zcoords[2]);
    return;
  } else if (strstr(curobj, "SOLID"))	/* 1 or 2 triangles */
  {
    if (checkdegen(0, 1, 2))
    {
      degenerates++;
      return;
    }
    writesurf(curcolor);
    fprintf(stdout, "p 3\n%g %g %g\n%g %g %g\n%g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0],
            xcoords[1], ycoords[1], zcoords[1],
            xcoords[2], ycoords[2], zcoords[2]);

    if (xcoords[2] == xcoords[3] && ycoords[2] == ycoords[3]
        && zcoords[2] == zcoords[3])
      return;			/* one triangle was enough... */

    if (checkdegen(0, 3, 2))
    {
      degenerates++;
      return;
    }
    writesurf(curcolor);
    fprintf(stdout, "p 3\n%g %g %g\n%g %g %g\n%g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0],
            xcoords[3], ycoords[3], zcoords[3],
            xcoords[2], ycoords[2], zcoords[2]);
    return;
  } else if (strstr(curobj, "TEXT"))	/* not implemented for now */
  {
    return;
  } else if (strstr(curobj, "SHAPE"))	/* these look very hard */
  {
    return;
  } else if (strstr(curobj, "BLOCK"))	/* these look very hard */
  {
    return;
  } else if (strstr(curobj, "ENDBLK"))	/* these look very hard */
  {
    return;
  } else if (strstr(curobj, "INSERT"))	/* these look very hard */
  {
    return;
  } else if (strstr(curobj, "ATTDEF"))	/* not implemented for now */
  {
    return;
  } else if (strstr(curobj, "ATTRIB"))	/* not implemented for now */
  {
    return;
  } else if (strstr(curobj, "POLYLINE"))	/* these look fairly hard */
  {
    return;
  } else if (strstr(curobj, "VERTEX"))	/* these look fairly hard */
  {
    return;
  } else if (strstr(curobj, "SEQEND"))	/* these look fairly hard */
  {
    return;
  } else if (strstr(curobj, "3DLINE"))	/* a VERY skinny cylinder! */
  {
    if (xcoords[0] == xcoords[1] && ycoords[0] == ycoords[1]
        && zcoords[0] == zcoords[1])
    {
      degenerates++;
      return;
    }
    writesurf(curcolor);
    fprintf(stdout, "c\n%g %g %g %g\n%g %g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0], SMALL,
            xcoords[1], ycoords[1], zcoords[1], SMALL);
    fprintf(stdout, "s %g %g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0], SMALL);
    fprintf(stdout, "s %g %g %g %g\n",
            xcoords[1], ycoords[1], zcoords[1], SMALL);
    return;
  } else if (strstr(curobj, "3DFACE"))	/* 1 or 2 triangles */
  {
    if (checkdegen(0, 1, 2))
    {
      degenerates++;
      return;
    }
    writesurf(curcolor);
    fprintf(stdout, "p 3\n%g %g %g\n%g %g %g\n%g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0],
            xcoords[1], ycoords[1], zcoords[1],
            xcoords[2], ycoords[2], zcoords[2]);

    if (xcoords[2] == xcoords[3] && ycoords[2] == ycoords[3]
        && zcoords[2] == zcoords[3])
      return;			/* one triangle was enough... */

    if (checkdegen(0, 3, 2))
    {
      degenerates++;
      return;
    }
    writesurf(curcolor);
    fprintf(stdout, "p 3\n%g %g %g\n%g %g %g\n%g %g %g\n",
            xcoords[0], ycoords[0], zcoords[0],
            xcoords[3], ycoords[3], zcoords[3],
            xcoords[2], ycoords[2], zcoords[2]);
    return;
  } else if (strstr(curobj, "DIMENSION"))	/* not implemented for now */
  {
    return;
  }
  return;			/* no current object defined... */
}

void 
writesurf(color)
  int             color;
{
  static int      lastcolor = -1;
  float           red, green, blue;

  primitives++;			/* count another output primitive */
  if (color == lastcolor)
    return;

  lookupcolor(color, &red, &green, &blue);
  fprintf(stdout, "f %g %g %g 1 0 0 0 1\n", red, green, blue);
  lastcolor = color;
}

void 
lookupcolor(color, red, green, blue)	/* basic AutoCAD 9-color pallette */
  int             color;
  float          *red, *green, *blue;
{
  switch (color)
  {
  case 0:			/* black */
    *red = *green = *blue = 0.0;
    break;
  case 1:			/* red */
    *red = 1.0;
    *blue = *green = 0.0;
    break;
  case 2:			/* yellow */
    *red = *green = 1.0;
    *blue = 0.0;
    break;
  case 3:			/* green */
    *green = 1.0;
    *red = *blue = 0.0;
    break;
  case 4:			/* cyan */
    *blue = *green = 1.0;
    *red = 0.0;
    break;
  case 5:			/* blue */
    *blue = 1.0;
    *red = *green = 0.0;
    break;
  case 6:			/* magenta */
    *blue = *red = 1.0;
    *green = 0.0;
    break;
  case 8:			/* dk. grey */
    *red = *green = *blue = 0.5;
    break;
  case 9:			/* lt. grey */
    *red = *green = *blue = 0.75;
    break;
  case 7:			/* white */
  default:			/* make anything else white (?) */
    *red = *green = *blue = 1.0;
  }
  return;
}

int 
checkdegen(a, b, c)		/* check for degenerate triangle structure */
  int             a, b, c;
{
  if (
      (xcoords[a] == xcoords[b] &&
       ycoords[a] == ycoords[b] &&
       zcoords[a] == zcoords[b]) ||
      (xcoords[b] == xcoords[c] &&
       ycoords[b] == ycoords[c] &&
       zcoords[b] == zcoords[c]) ||
      (xcoords[a] == xcoords[c] &&
       ycoords[a] == ycoords[c] &&
       zcoords[a] == zcoords[c]))
    return (1);
  return (0);
}

#ifdef unix
char           *
strstr(str1, str2)
  register char  *str1, *str2;
{
  register char  *token1, *token2;

  if (strpbrk(str1, str2) == NULL)
    return ((char *) NULL);

  while ((str1 = strchr(str1, str2[0])) != NULL)
  {
    token1 = str1;
    token2 = str2;
    while (*token1++ == *token2++)
      if (*token2 == '\0')
        return (str1);

    str1 = token1;
  }

  return ((char *) NULL);
}
#endif
