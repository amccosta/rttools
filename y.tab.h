typedef union {
	Vector  vec;
	Vector *vecl;
	double  flt;
	Object *obj;
} YYSTYPE;
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


extern YYSTYPE yylval;
