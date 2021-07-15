/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

#include "../global.h"

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */

static const char *fonts[] = { FONT_1, FONT_2, FONT_3 };

static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#bbbbbb", "#2f343f" },
	[SchemeSel] = { "#eeeeee", "#bb92ac" },
	[SchemeOut] = { "#000000", "#2f343f" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
