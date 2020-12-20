/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Noto Mono:size=22:style=Bold", "Noto Color Emoji:style=Bold:size=20", "Symbols Nerd Font:size=24" };
static const char dmenufont[]       = "Noto Mono:size=22";
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
static const char *tags[] = { "1", "2", "3"};

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
	{ "離",      tile },     /* first entry is default */
	{ "",      NULL },     /* no layout function means floating behavior */
	{ "裡",      monocle },  /* tab between fullscreen windows */
};

/* key definitions */
#define MODKEY Mod4Mask

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,             		    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	/* 'Alt-tab' through windows */
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },

	/* Increment/decrement the number of windows in the master (right) stack */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	/* Change width of left/right window stacks */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	/* Close window */	
	{ MODKEY,             			XK_w,      killclient,     {0} },
	{ MODKEY,             			XK_q,      killclient,     {0} },

	/* Set layout */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	
	/* Move the current window up/down the stack in tiled mode */
	{ MODKEY,                       XK_j,   pushdown,           	  {0} },
	{ MODKEY,                       XK_k,   pushup,           	 	  {0} },

	/* Switch between tags */
	/* NOTE: uses custom patch to work with 'pertag' and not 'focusadjacent' */
	{ MODKEY,                       XK_Left,   viewToLeft,            {0} },
	{ MODKEY,                       XK_Right,  viewToRight,           {0} },

	/* Move current window left/right and switch to that tag (focusadjacent patch) */
	{ ControlMask|ShiftMask,        XK_Left,   switchTagToLeft,      {0} },
	{ ControlMask|ShiftMask,        XK_Right,  switchTagToRight,     {0} },
	
	/* Quit X */
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
	
	//{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	//{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	//{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	//{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

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
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

