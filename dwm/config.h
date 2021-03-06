/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
#include "../global.h"

#define SCREENSHOT SCRIPTS_PATH "screenshot.sh"
#define POLYBAR SCRIPTS_PATH "launch_polybar.sh"
#define CLIPBOARD SCRIPTS_PATH "clipboard.bash"
#define EMOJI_MENU SCRIPTS_PATH "emoji.sh"

/* IPC patch */
static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

/* appearance */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* Rounded borders anf gaps */
static const unsigned int borderpx  = 0;       	/* border pixel of windows */
static const unsigned int cornerrad = 0;		/* Use picom-rounded-corners instead */
static const unsigned int gappih    = 4;
static const unsigned int gappiv    = 4;
static const unsigned int gappoh    = 4;
static const unsigned int gappov    = 4;
static const int smartgaps          = 0; /* Will produce gaps whenn only one window exists if set */


/* anybar patch */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd        = POLYBAR; /* Alternate bar launch command */

static const char *fonts[] = { FONT_1, FONT_2, FONT_3 };

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_accent[]        = "#bb92ac";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1,   col_gray1   },
	[SchemeSel]  = { col_gray4, col_accent,  col_accent  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags        mask     isfloating   monitor */
	{ "Gimp",     			  NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  			  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "VirtualBox Machine",   NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "恵",      tile },     /* first entry is default */
	{ "",      NULL },     /* no layout function means floating behavior */
	{ "裡",      monocle },  /* tab between fullscreen windows */
};

/* key definitions */
#define MODKEY Mod4Mask

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon,  NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *tabbedTermCmd[]  = { "tabbed", "-c", "-r", "2", "st", "-w", "''", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *mixercmd[]  = { "st", "-e", "pulsemixer", NULL };
static const char *barcmd[]  = { POLYBAR, NULL };

static const char *screenShot[] = { SCREENSHOT, NULL };
static const char *emojiMenu[] = { EMOJI_MENU, NULL };

static const char *saveClipboard[] = { CLIPBOARD, "save", NULL };
static const char *loadClipboard[] = { CLIPBOARD, "load", NULL };


#ifdef USE_ALSA
	static const char *volumeToggle[] = { "amixer", "set", "Master", "toggle", NULL };
	static const char *volumeUp[] = { "amixer", "set", "Master", "3%+", NULL };
	static const char *volumeDown[] = { "amixer", "set", "Master", "3%-", NULL };
#else
	static const char *volumeToggle[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
	static const char *volumeUp[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+3%", NULL };
	static const char *volumeDown[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-3%", NULL };
#endif

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,             		    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = tabbedTermCmd } },
	{ MODKEY,                       XK_b,      spawn,      	   {.v = browsercmd} },
	{ MODKEY,                       XK_p,      spawn,      	   {.v = mixercmd} },
	{ MODKEY|ShiftMask,             XK_p,      spawn,      	   {.v = barcmd} },

	/* 'Alt-tab' through windows */
	{ ControlMask,                  XK_q,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },

	/* Increment/decrement the number of windows in the master (right) stack */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	/* Change width of left/right window stacks */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	/* Close window */	
	{ MODKEY,             			XK_q,      killclient,     {0} },

	/* Set layout */
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },

	/* Toggle fullscreen */
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,         {0}  },

	/* Move the current window up/down the stack in tiled mode */
	{ MODKEY,                       XK_j,   pushdown,           	  {0} },
	{ MODKEY,                       XK_k,   pushup,           	 	  {0} },

	/* Switch between tags */
	/* NOTE: uses custom patch to work with 'pertag' and not 'focusadjacent' */
	{ MODKEY,                       XK_Left,   viewToLeft,            {0} },
	{ MODKEY,                       XK_Right,  viewToRight,           {0} },
	
	/* Ctrl to switch between numbers directly */
	{ ControlMask,                    XK_1,      	   view,           {.ui = 1 << 0} },  
	{ ControlMask,                    XK_2,      	   view,           {.ui = 1 << 1} }, 
	{ ControlMask,                    XK_3,      	   view,           {.ui = 1 << 2} }, 
	{ ControlMask,                    XK_4,      	   view,           {.ui = 1 << 3} }, 
	{ ControlMask,                    XK_5,      	   view,           {.ui = 1 << 4} }, 
	{ ControlMask,                    XK_section,      view,           {.ui = 1 << 5} }, 

	/* Move current window left/right and switch to that tag (focusadjacent patch) */
	{ ControlMask|ShiftMask,        XK_Left,   switchTagToLeft,      {0} },
	{ ControlMask|ShiftMask,        XK_Right,  switchTagToRight,     {0} },

	/* Volume control */
	{ 0,                       XF86XK_AudioMute,        spawn, {.v = volumeToggle } },
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = volumeDown } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = volumeUp   } },
	
	/* Screen shot */
	{ MODKEY|ShiftMask,        	 XK_3,               spawn,           {.v = screenShot} },
	
	/* Clipboard sharing */
	{ MODKEY|ShiftMask,             XK_s,    spawn,     {.v = saveClipboard } },
	{ MODKEY|ShiftMask,             XK_l,    spawn,     {.v = loadClipboard } },
	
	/* Emoji menu */
	{ MODKEY|ControlMask,        XK_space,           spawn,           {.v = emojiMenu} },

	/* Quit X */
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	/* Resize windows with MODKEY+Right-mouse-button */
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

