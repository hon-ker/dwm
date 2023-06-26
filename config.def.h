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
  "WenQuanYi Micro Hei:size=13:type=Regular:antialias=true:autohint=true",
  "symbols Nerd Font:pixelsize=15:type=Regular:antialias=true:autohint=true"
  "JoyPixels:pixelsize=15:type=Regular:antialias=true:autohint=true"
};

#define ICONSIZE 19   /* icon size */
#define ICONSPACING 9 /* space between icon and title */

//static const char dmenufont[]       = "monospace:size=12";

// 启动时自动加载的脚本，可以自己设置个性化桌面
static const char *const autostart[] = {
  //"alacritty", NULL,
    NULL /* terminate */
};

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
  /*                    fg          bg      border   */
  [SchemeNorm]      = { white,      gray,       gray },        // 状态栏
  [SchemeSel]       = { red,        gray,       theme},        // 窗口
  [SchemeTitle]     = { theme,      gray,       gray },        // 窗口标题颜色
};

  /* tagging */
static const char *tags[] = { "","","", "", "","","󰎈"};

static const char *tagsel[][2] = {
//  icon            bg
	{ blue      ,   gray  },
	{ pink      ,   gray  },
	{ red       ,   gray  },
	{ green     ,   gray  },
	{ yellow    ,   gray  },
	{ syan      ,   gray  },
	{ orange    ,   gray  },
	//{ "#000000" ,   gray  },
	//{ "#ffffff" ,   gray  },
};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

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
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "",      tile },    /* first entry is default */
  { "󰍽",      NULL },    /* no layout function means floating behavior */
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
static const char scratchpadname[] = "small cmd";
static const char *scratchpadcmd[] = { "alacritty", "-T", scratchpadname, "-o","window.dimensions.columns=90","-o","window.dimensions.lines=25", NULL };
//static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const Key keys[] = {
  /* modifier                     key        function        argument */
  // 系统级 亮度，音量等
  {ControlMask,                 XK_F1,      spawn,            SHCMD("~/.dwm/script/setVol.sh none")},
  {ControlMask,                 XK_F2,      spawn,            SHCMD("~/.dwm/script/setVol.sh down")},
  {ControlMask,                 XK_F3,      spawn,            SHCMD("~/.dwm/script/setVol.sh up")},
  {ControlMask,                 XK_F6,      spawn,            SHCMD("~/.dwm/script/setBacklight.sh down")},
  {ControlMask,                 XK_F7,      spawn,            SHCMD("~/.dwm/script/setBacklight.sh up")},
  // 自定义快捷键
  { MODKEY,                     XK_d,       spawn,            SHCMD("rofi -show drun") },
  { MODKEY,                     XK_c,       spawn,            SHCMD("google-chrome-stable") },
  { MODKEY,                     XK_Return,  spawn,            SHCMD("alacritty")},
  { Mod1Mask,                   XK_a,       spawn,            SHCMD("flameshot gui")},
  
  // kill窗口
  { MODKEY,                     XK_q,       killclient,     {0} },

  // 打开关闭状态栏
  { MODKEY,                     XK_m,       togglebar,      {0} },

  // 选装当前tag的窗口
  { ShiftMask,                  XK_Return,      rotatestack,    {.i = -1 } },
  { ShiftMask ,                 XK_space,       rotatestack,    {.i = +1 } },
  
  // grid模式和切换
  //{ MODKEY,                     XK_a,       setlayout,      {.v = &layouts[3]} },

  // 改变主窗口大小 win + < / >
  { MODKEY,                     XK_comma,     setmfact,       {.f = -0.05} },
  { MODKEY,                     XK_period,    setmfact,       {.f = +0.05} },

  // 全屏切换
  { MODKEY,                       XK_f,      fullscreen,     {0} },
 
  // stack区添加和减少窗口
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
  
  // 浮动小窗口 small s
  { MODKEY,                       XK_s,  togglescratch,  {.v = scratchpadcmd } },
  
  // 切换
  { MODKEY,                       XK_Tab,    view,           {0} },         // 切换tag
  // 切换tag
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },  // 切换窗口
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },  // 切换窗口
  
  // 移动                                                                         //
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 1h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
  // 大小调整
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
  // 位置
  { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	// 放大
  { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  //{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  //{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  //{ MODKEY,                       XK_space,  setlayout,      {0} },
  //{ MODKEY|ShiftMask,           XK_Return,  zoom,           {0} },
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

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
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
	{ ClkClientWin,         MODKEY,         Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,         Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,         Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,         Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

