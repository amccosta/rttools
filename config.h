#ifdef SYS_V
#define index 	strchr
#define rindex 	strrchr
#endif				/* SYS_V */

#define         TOL             ((Float) 5e-9)
#define         XMAX            (1024)
#define         YMAX            (1024)
#define         MAXLIGHTS       (16)
#define         MAXSURFACES     (256)
#define         MAXPRIMS        (25000)
#define         ORIGIN          ((Float) 0.0)
#define         SCALE           ((Float) 1.0)

#ifdef 		NOVOID
#define void 	char
#endif
