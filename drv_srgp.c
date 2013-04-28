/*
 * drv_srgp.c - SRGP graphics driver, BW version
 * Made by: Antonio Costa, 18-May-1994
 */

#include "drv.h"
#include "srgp.h"

#ifndef _Windows
#define SRGP_malloc malloc
#define SRGP_free free
#endif

static int hx, hy, sx, sy;
extern int kbhit();

#define POINT 1
#define LINE  2

typedef struct _list {
  char type;
  float x0, y0, x1, y1;
  struct _list *next;
} list;

static list *list_head, *list_current;

static int
resize_callback()
{
  list *node;

  SRGP_inquireCanvasSize(SCREEN_CANVAS, &sx, &sy);
  hx = sx-- / 2;
  hy = sy-- / 2;
  display_clear();
  node = list_head;
  while (node)
  {
    if (node->type == LINE)
      SRGP_lineCoord((int) (node->x0 * sx), (int) (node->y0 * sy),
                     (int) (node->x1 * sx), (int) (node->y1 * sy));
    else
      SRGP_markerCoord((int) (node->x0 * sx), (int) (node->y0 * sy));
    node = node->next;
  }
  return 1;
}

void
display_clear()
{
  /* Insert code to clear the graphics display here */
  SRGP_setColor(COLOR_BLACK);
  SRGP_fillRectangleCoord(0, 0, sx, sy);
  SRGP_setColor(COLOR_WHITE);
}

void
display_init(xres, yres, bk_color)
  int xres, yres;
  COORD3 bk_color;
{
  /* Insert code to open/initialize the graphics display here */
  SRGP_begin("SPD", xres, yres, 2, FALSE);
  SRGP_disableDebugAids();
  SRGP_allowResize(0);
  SRGP_inquireCanvasSize(SCREEN_CANVAS, &sx, &sy);
  hx = sx-- / 2;
  hy = sy-- / 2;
  list_head = (list *) NULL;
  SRGP_setInputMode(KEYBOARD, SAMPLE);
  SRGP_setKeyboardProcessingMode(RAW);
  SRGP_setColor(COLOR_WHITE);
  display_clear();
  SRGP_registerResizeCallback(resize_callback);
}

void
display_close(wait_flag)
  int wait_flag;
{
  /* Insert code to close the graphics display here */
  SRGP_allowResize(1);
  if (wait_flag)
    while (!kbhit())
      ;
  SRGP_end();
  while (list_head)
  {
    list_current = list_head;
    list_head = list_head->next;
    SRGP_free(list_current);
  }
#ifdef GRX
  exit(0);
#endif
}

/* currently not used for anything, so you don't have to implement */
void
display_plot(x, y, color)
  int x, y;
  COORD3 color;
{
  list *list_new;

  /* Insert code to plot a single pixel here */
  SRGP_markerCoord(x + hx, y + hy);
  if (kbhit())
    display_close(0);
  list_new = (list *) SRGP_malloc(sizeof(list));
  if (list_head)
    list_current->next = list_new;
  else
    list_head = list_new;
  list_current = list_new;
  list_current->type = POINT;
  list_current->x0 = (float) (x + hx) / sx;
  list_current->y0 = (float) (y + hy) / sy;
}

/* weirdly enough, x and y are centered around the origin - see hp.c for a
 * way to offset these coordinates to a [0 to resolution-1] type of scale.
 */
void
display_line(x0, y0, x1, y1, color)
  int x0, y0, x1, y1;
  COORD3 color;
{
  list *list_new;

  /* Insert line drawing code here */
  SRGP_lineCoord(x0 + hx, y0 + hy, x1 + hx, y1 + hy);
  if (kbhit())
    display_close(0);
  list_new = (list *) SRGP_malloc(sizeof(list));
  if (list_head)
    list_current->next = list_new;
  else
    list_head = list_new;
  list_current = list_new;
  list_current->type = LINE;
  list_current->x0 = (float) (x0 + hx) / sx;
  list_current->y0 = (float) (y0 + hy) / sy;
  list_current->x1 = (float) (x1 + hx) / sx;
  list_current->y1 = (float) (y1 + hy) / sy;
}

int
kbhit()
{
  char k[2];

  /* Insert keyboard hit test code here */
  SRGP_sampleKeyboard(k, 2);
  return (k[0] == ' ');
}
