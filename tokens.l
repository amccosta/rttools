%{
#include <stdio.h>
#include "defs.h"
#ifdef dos
#include "y_tab.h"
#else
#include "y.tab.h"
#endif
#include "extern.h"
%}

%%
[ \t]			;
\#			{ register int c;
			  while ((c = input()) != '\n' && c != EOF);
			  yylinecount++;
			}
\n			yylinecount++;
v			return VIEWPOINT;
viewpoint		return VIEWPOINT;
from			return FROM;
at			return AT;
up			return UP;
angle			return ANGLE;
hither			return HITHER;
resolution		return RESOLUTION;
l			return LIGHT;
light			return LIGHT;
b			return BACKGROUND;
background		return BACKGROUND;
f			return SURFACE;
surface			return SURFACE;
c			return CONE;
cone			return CONE;
s			return SPHERE;
sphere			return SPHERE;
p			return POLYGON;
polygon			return POLYGON;
pp			return PATCH;
patch			return PATCH;
\-?[0-9]*((\.[0-9]+)?(e(\-|\+)?[0-9]+)?)? 	return NUM;
[A-Za-z0-9_]+		return TOKEN;
.			return yytext[0];

%%
#ifndef dos
yywrap()
{
	return 1;
}
#endif
