#ifndef        __MENU_h__
#define        __MENU_h__

// const struct MenuItem* menu_point = main_menu ; //main()

#include "mega16_v3_1_func.h"

#define NULL ((void*)0)

#define DISPLAY_ITEMS 4

#define MAIN_MENU_NUMS 5

#define TIME_MENU_NUMS 1

#define STOPWATCH_MENU_NUMS 2

#define LED_MENU_NUMS 5

#define TEMP_MENU_NUMS 1

#define SET_MENU_NUMS 2


struct MenuItem
{

	const short menu_count;

	char * const disp_str;

	void(*Subs)();

	const struct MenuItem *children_menus;

	const struct MenuItem *parent_menus;

	char * const disp_title;
	
};

extern const struct MenuItem main_menu[			MAIN_MENU_NUMS		];

extern const struct MenuItem time_menu[			TIME_MENU_NUMS		];

extern const struct MenuItem stopwatch_menu[	STOPWATCH_MENU_NUMS	];

extern const struct MenuItem led_menu[			LED_MENU_NUMS		];

extern const struct MenuItem temp_menu[			TEMP_MENU_NUMS		];

extern const struct MenuItem setting_menu[		SET_MENU_NUMS		];



void NullSubs(void)
{
	// JUST NULL
}


// main_menu
const struct MenuItem main_menu[MAIN_MENU_NUMS] = {
	{ MAIN_MENU_NUMS,		"1 LED Control ",	NullSubs, 		led_menu, 			NULL,			"   MAIN MENU" },
	{ MAIN_MENU_NUMS,		"2 Clock       ",	NullSubs, 		time_menu, 			NULL },
	{ MAIN_MENU_NUMS,		"3 Temperture  ",	NullSubs, 		temp_menu, 			NULL },
	{ MAIN_MENU_NUMS,		"4 Settings    ",	NullSubs, 		setting_menu,		NULL },
	{ MAIN_MENU_NUMS,		"5 About System",	AboutSystem,	NULL,	  			NULL } 
};

// time_menu
const struct MenuItem time_menu[TIME_MENU_NUMS] = {
	{ TIME_MENU_NUMS,		"1 Stopwatch   ",	NullSubs,	 	stopwatch_menu,	   main_menu,		"   TIME MENU" }
	//{ TIME_MENU_NUMS,		"2 SET Time  :)",	NullSubs,		NULL,	  		   main_menu }
};

// stopwatch_menu
const struct MenuItem stopwatch_menu[STOPWATCH_MENU_NUMS] = {
	{ STOPWATCH_MENU_NUMS,	"1 Start/Pause ",	StopWatch,		NULL,				time_menu,		"   STOPWATCH" },
	{ STOPWATCH_MENU_NUMS,	"2 Reset       ",	ResetTime,		NULL,				time_menu }
};

// led_menu
const struct MenuItem led_menu[LED_MENU_NUMS] = {
	{ LED_MENU_NUMS,		"1 Lighten  All",	LightenAll,		NULL,				main_menu,		"   LED MENU" },
	{ LED_MENU_NUMS,		"2 LightOFF All",	LightOffAll, 	NULL,				main_menu },
	{ LED_MENU_NUMS,		"3 Left Shift  ",	LeftShift,	 	NULL,				main_menu },
	{ LED_MENU_NUMS,		"4 Right Shift ",	RightShift,		NULL,				main_menu },
	{ LED_MENU_NUMS,		"5 Customize   ",	CustomizeLed,	NULL,				main_menu } };

// temp_menu
const struct MenuItem temp_menu[TEMP_MENU_NUMS] = {
	{ TEMP_MENU_NUMS,		"1 Show Temp   ",	ShowTemp,		NULL,				main_menu,		"   TEMP MENU" }
};

// setting_menu
const struct MenuItem setting_menu[SET_MENU_NUMS] = {
	{ SET_MENU_NUMS,		"1 Volume      ",	SetVolume,		NULL,				main_menu,		" SETTING MENU" },
	{ SET_MENU_NUMS,		"2 Reset System",	ResetSystem,	NULL,				main_menu }
};


#endif