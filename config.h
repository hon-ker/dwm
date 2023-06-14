/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 4;        /* horizontal padding for statusbar */
static const int vertpadbar         = 8;        /* vertical padding for statusbar */
static const int vertpad            = 4;       /* vertical padding of bar */
static const int sidepad            = 4;       /* horizontal padding of bar */
static const char *fonts[]          = {
  "monospace:size=13",
  "WenQuanYi Micro Hei:size=12:type=Regular:antialias=true:autohint=true",
  "symbols Nerd Font:pixelsize=16:type=Regular:antialias=true:autohint=true"
  "JoyPixels:pixelsize=16:type=Regular:antialias=true:autohint=true"
};

#define ICONSIZE 19   /* icon size */
#define ICONSPACING 9 /* space between icon and title */

static const char dmenufont[]       = "monospace:size=6";

// 配色
// 注意如若要实现类似透明背景效果，务必使状态栏背景 gray 和标签的背景颜色一致
static const char theme[]           = "#9999ff";    //
static const char gray[]            = "#24283b";    //背景色
static const char black[]           = "#222222";
static const char white[]           = "#ffffff";
static const char blue[]            = "#7aa2f7";
static const char green[]           = "#9ece6a";
static const char red[]             = "#f7768e";
static const char orange[]          = "#ff9e64";
static const char yellow[]          = "#e0af68";
static const char pink[]            = "#bb9af7";
static const char syan[]            = "#01ffff";

static const char *colors[][3]      = {
  /*                    fg              bg              border   */
  [SchemeNorm]      = { white,      gray,        gray },        // 状态栏
  [SchemeSel]       = { gray,      gray,        theme},             // 窗口
  [SchemeTitle]     = { theme,     gray,        gray  },        // 窗口标题颜色
};

  /* tagging */
static const char *tags[] = { "","","󰮤","", "", "", "" };

static const char *tagsel[][2] = {
//  icon            bg
	{ blue      ,   gray  },
	{ orange       ,gray  },
	{ red       ,   gray  },
	{ green     ,   gray  },
	{ pink      ,   gray  },
	{ yellow    ,   gray  },
	{ syan      ,   gray  },
	//{ "#000000" ,   gray  },
	//{ "#ffffff" ,   gray  },
};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


static const Layout layouts[] = {
  /* symbol     arrange function */
  { "",      tile },    /* first entry is default */
  { "󱕐",      NULL },    /* no layout function means floating behavior */
  { "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "alacritty", NULL };

static const Key keys[] = {
  /* modifier                     key        function        argument */
  // 系统级 亮度，音量等
  {ControlMask,                 XK_F2,      spawn,            SHCMD("~/.dwm/scripts/setVol.sh down")},
  {ControlMask,                 XK_F3,      spawn,            SHCMD("~/.dwm/scripts/setVol.sh up")},
  {ControlMask,                 XK_F6,      spawn,            SHCMD("~/.dwm/scripts/setBacklight.sh down")},
  {ControlMask,                 XK_F7,      spawn,            SHCMD("~/.dwm/scripts/setBacklight.sh up")},
  // 自定义快捷键
  { MODKEY,                     XK_d,       spawn,            SHCMD("rofi -show drun") },
  { MODKEY,                     XK_c,       spawn,            SHCMD("google-chrome-stable") },
  { MODKEY,                     XK_Return,  spawn,            SHCMD("alacritty")},
  { ControlMask|Mod1Mask,       XK_a,       spawn,            SHCMD("flameshot gui")},

  { MODKEY,                     XK_q,       killclient,     {0} },
  { MODKEY|ShiftMask,           XK_Return,  zoom,           {0} },

  // 打开关闭状态栏
  { MODKEY,                     XK_m,       togglebar,      {0} },

  // grid模式和切换
  //{ MODKEY,                     XK_a,       setlayout,      {.v = &layouts[3]} },
  //{ MODKEY|ControlMask,         XK_a,       setlayout,      {.v = &layouts[0]} },
  // 改变mask窗口大小
  { MODKEY,                     XK_comma,     setmfact,       {.f = -0.05} },
  { MODKEY,                     XK_period,    setmfact,       {.f = +0.05} },

  // 全屏切换
//  { MODKEY,                     XK_f,      togglefullscr,  {0} },

  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  //{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  //{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
  { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
  { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
  TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

