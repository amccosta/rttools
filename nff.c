
/*  A Bison parser, made from nff.y with Bison version GNU Bison version 1.21
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	VIEWPOINT	258
#define	FROM	259
#define	AT	260
#define	UP	261
#define	ANGLE	262
#define	HITHER	263
#define	RESOLUTION	264
#define	LIGHT	265
#define	BACKGROUND	266
#define	SURFACE	267
#define	CONE	268
#define	SPHERE	269
#define	POLYGON	270
#define	PATCH	271
#define	NUM	272
#define	TOKEN	273

#line 1 "nff.y"

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

#line 32 "nff.y"
typedef union {
	Vector  vec;
	Vector *vecl;
	double  flt;
	Object *obj;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		65
#define	YYFLAG		-32768
#define	YYNTBASE	19

#define YYTRANSLATE(x) ((unsigned)(x) <= 273 ? yytranslate[x] : 37)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     6,     7,     9,    11,    13,    15,    17,    19,
    21,    23,    38,    41,    45,    48,    56,    62,    66,    67,
    72,    73,    78,    82,    84,    88,    91,    92
};

static const short yyrhs[] = {    23,
    20,     0,    20,    21,     0,     0,    24,     0,    25,     0,
    26,     0,    22,     0,    27,     0,    28,     0,    29,     0,
    31,     0,     3,     4,    34,     5,    34,     6,    34,     7,
    36,     8,    36,     9,    36,    36,     0,    10,    34,     0,
    10,    34,    33,     0,    11,    33,     0,    12,    33,    36,
    36,    36,    36,    36,     0,    13,    34,    36,    34,    36,
     0,    14,    34,    36,     0,     0,    15,    36,    30,    35,
     0,     0,    16,    36,    32,    35,     0,    36,    36,    36,
     0,    18,     0,    36,    36,    36,     0,    35,    34,     0,
     0,    17,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    45,    53,    55,    57,    59,    60,    61,    71,    72,    73,
    74,    76,    94,   109,   122,   128,   152,   159,   166,   173,
   183,   192,   203,   210,   221,   229,   235,   237
};

static const char * const yytname[] = {   "$","error","$illegal.","VIEWPOINT",
"FROM","AT","UP","ANGLE","HITHER","RESOLUTION","LIGHT","BACKGROUND","SURFACE",
"CONE","SPHERE","POLYGON","PATCH","NUM","TOKEN","scene","elementlist","element",
"object","camera","light","background","surface","cone","sphere","polygon","@1",
"ppatch","@2","primcolor","point","pointlist","num",""
};
#endif

static const short yyr1[] = {     0,
    19,    20,    20,    21,    21,    21,    21,    22,    22,    22,
    22,    23,    24,    24,    25,    26,    27,    28,    30,    29,
    32,    31,    33,    33,    34,    35,    35,    36
};

static const short yyr2[] = {     0,
     2,     2,     0,     1,     1,     1,     1,     1,     1,     1,
     1,    14,     2,     3,     2,     7,     5,     3,     0,     4,
     0,     4,     3,     1,     3,     2,     0,     1
};

static const short yydefact[] = {     0,
     0,     3,     0,     1,    28,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     2,     7,     4,     5,     6,     8,
     9,    10,    11,     0,     0,    13,    24,    15,     0,     0,
     0,     0,    19,    21,     0,    25,    14,     0,     0,     0,
    18,    27,    27,     0,    23,     0,     0,    20,    22,     0,
     0,    17,    26,     0,     0,     0,    16,     0,     0,     0,
     0,    12,     0,     0,     0
};

static const short yydefgoto[] = {    63,
     4,    15,    16,     2,    17,    18,    19,    20,    21,    22,
    42,    23,    43,    28,    53,    48,     7
};

static const short yypact[] = {     1,
     4,-32768,    -8,    45,-32768,    10,    -8,    -8,    -6,    -6,
    -8,    -8,    -8,    -8,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    -8,    -8,    -6,-32768,-32768,    -8,    -8,
    -8,    -8,-32768,-32768,    14,-32768,-32768,    -8,    -8,    -8,
-32768,-32768,-32768,    -8,-32768,    -8,    -8,    -8,    -8,     9,
    -8,-32768,-32768,    -8,    -8,    13,-32768,    -8,    18,    -8,
    -8,-32768,    28,    29,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    -9,     2,   -13,    -7
};


#define	YYLAST		61


static const short yytable[] = {    25,
    30,    29,    29,     1,     6,    33,    34,     3,     5,    26,
     5,    27,    31,    32,    24,    54,    37,    36,    29,    44,
    58,    38,    39,    40,    41,    35,    60,    64,    65,    49,
    45,    46,     0,     0,     0,     0,     0,     0,    51,    52,
     0,    47,     0,    55,     0,    50,    56,    57,     0,     0,
    59,     0,    61,    62,     8,     9,    10,    11,    12,    13,
    14
};

static const short yycheck[] = {     7,
    10,     9,    10,     3,     3,    13,    14,     4,    17,     8,
    17,    18,    11,    12,     5,     7,    26,    25,    26,     6,
     8,    29,    30,    31,    32,    24,     9,     0,     0,    43,
    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,
    -1,    40,    -1,    51,    -1,    44,    54,    55,    -1,    -1,
    58,    -1,    60,    61,    10,    11,    12,    13,    14,    15,
    16
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca (unsigned int);
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#define YYLEX		yylex(&yylval, &yylloc)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 184 "bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
#ifdef YYLSP_NEEDED
		 &yyls1, size * sizeof (*yylsp),
#endif
		 &yystacksize);

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 47 "nff.y"
{
	int i, l;
	  for (l = 0; l < nLights; l++)
	    Lights[l].brightness = sqrt((Float) nLights)/((Float) nLights);
	;
    break;}
case 7:
#line 62 "nff.y"
{
	char buf[80];
	  if (nPrims >= maxPrims)
	  {
	    sprintf(buf, "max objects = %d", maxPrims);
	    yyerror(buf);
	  }
	;
    break;}
case 12:
#line 84 "nff.y"
{
	  VectorCopy(yyvsp[-11].vec, Eye.view_from);
	  VectorCopy(yyvsp[-9].vec, Eye.view_at);
	  VectorCopy(yyvsp[-7].vec, Eye.view_up);
	  Eye.view_angle = (yyvsp[-5].flt)/2.0;
	  Eye.view_dist = yyvsp[-3].flt;
	  newpoly = 1;
	  newtri = 1;
	;
    break;}
case 13:
#line 96 "nff.y"
{
	char buf[80];
	  if (nLights >= maxLights)
	  {
	    sprintf(buf, "max lights = %d", maxLights);
	    yyerror(buf);
	  }
	  VectorCopy(yyvsp[0].vec, Lights[nLights].coords);
	  /* fill in brightness of the light, after we 
	   * know the number of lights sources in the scene
	   */
	  nLights++;
	;
    break;}
case 14:
#line 110 "nff.y"
{
	char buf[80];
	  if (nLights >= maxLights)
	  {
	    sprintf(buf, "max lights = %d", maxLights);
	    yyerror(buf);
	  }
	  VectorCopy(yyvsp[-1].vec, Lights[nLights].coords);
	  /* brightness not yet used */
	  nLights++;
	;
    break;}
case 15:
#line 124 "nff.y"
{
	  VectorCopy(yyvsp[0].vec, BackgroundColor);
	;
    break;}
case 16:
#line 130 "nff.y"
{
	char buf[80];
	  if (nSurfaces >= maxSurfaces)
	  {
	    sprintf(buf, "max surfaces = %d", maxSurfaces);
	    yyerror(buf);
	  }
	  VectorCopy(yyvsp[-5].vec, Surfaces[nSurfaces].color);
	  Surfaces[nSurfaces].diffuse = yyvsp[-4].flt;
	  Surfaces[nSurfaces].specular = yyvsp[-3].flt;
	  Surfaces[nSurfaces].shine = yyvsp[-2].flt;
	  Surfaces[nSurfaces].transparency = yyvsp[-1].flt;
	  Surfaces[nSurfaces].refraction = yyvsp[0].flt;
	  ActiveSurface = CheckSurfaces();
	  if (ActiveSurface == nSurfaces)
            nSurfaces++;
	  if (!newpoly)
	    newpoly = 1;
	  if (!newtri)
	    newtri = 1;
	;
    break;}
case 17:
#line 154 "nff.y"
{
	  yyval.obj = MakeCone(yyvsp[-3].vec, yyvsp[-2].flt, yyvsp[-1].vec, yyvsp[0].flt);
	  Prims[nPrims++] = yyval.obj;
	;
    break;}
case 18:
#line 161 "nff.y"
{
	  yyval.obj = MakeSphere(yyvsp[-1].vec, yyvsp[0].flt);
	  Prims[nPrims++] = yyval.obj;
	;
    break;}
case 19:
#line 168 "nff.y"
{
	  plist = (Vector *) calloc((int) yyvsp[0].flt, sizeof(Vector));
	  pl = plist;
	;
    break;}
case 20:
#line 173 "nff.y"
{
	  if (newpoly)
	  {
	    poly = MakePoly(NULL, (int) yyvsp[-2].flt, plist, 1);
	    Prims[nPrims++] = poly;
	    newpoly = 0;
	  }
	  else
	    MakePoly(poly, (int) yyvsp[-2].flt, plist, 0);
	;
    break;}
case 21:
#line 185 "nff.y"
{
	  if ((int) yyvsp[0].flt != 3)
	    fprintf(stderr, "Sorry, patches must have 3 vertices...\n");
	  plist = (Vector *) calloc(2 * (int) yyvsp[0].flt, sizeof(Vector));
	  pl = plist;
	;
    break;}
case 22:
#line 192 "nff.y"
{
	  if (newtri)
	  {
	    tri = MakeTri(NULL, plist, 1);
	    Prims[nPrims++] = tri;
	    newtri = 0;
	  }
	  else
	    MakeTri(tri, plist, 0);
	;
    break;}
case 23:
#line 205 "nff.y"
{
	  yyval.vec[0] = yyvsp[-2].flt;
	  yyval.vec[1] = yyvsp[-1].flt;
	  yyval.vec[2] = yyvsp[0].flt;
	;
    break;}
case 24:
#line 211 "nff.y"
{
	char buf[80];

	  if (LookupColorByName(yytext, yyval.vec) == 0)
	  {
	    sprintf(buf, "cannot find color \"%s\"\n", yytext);
	    yyerror(buf) ;
	  }
	;
    break;}
case 25:
#line 223 "nff.y"
{
	  yyval.vec[0] = yyvsp[-2].flt;
	  yyval.vec[1] = yyvsp[-1].flt;
	  yyval.vec[2] = yyvsp[0].flt;
	;
    break;}
case 26:
#line 231 "nff.y"
{
	  VectorCopy(yyvsp[0].vec, (*pl));
	  pl++;
	;
    break;}
case 28:
#line 239 "nff.y"
{
	  double n;

	  sscanf(yytext, "%lf", &n);
	  yyval.flt = n;
	;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 457 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 246 "nff.y"


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
