#ifndef        __MENU_h__
#define        __MENU_h__

#include "mega16_v3_1_func.h"

#define CLOCK_MENU_NUMS 2

struct MenuItem
{

	short menu_count;

	char *disp_str;

	void (*Subs)();

	struct MenuItem *children_menus;

	struct MenuItem *parent_menus;

};

struct MenuItem main_menu[5];

struct MenuItem clock_menu[CLOCK_MENU_NUMS];

struct MenuItem time_menu[4];

struct MenuItem led_menu[4];

struct MenuItem temp_menu[4];

struct MenuItem file_menu[4];

void NullSubs(void)
{

}

void InitMainMenu(void)

{

	main_menu[0].menu_count = 5;

	main_menu[0].disp_str = "1 Clock      ";

	main_menu[0].Subs = NullSubs;

	main_menu[0].children_menus = clock_menu;

	main_menu[0].parent_menus = 0;


	main_menu[1].menu_count = 5;

	main_menu[1].disp_str = "2 Time       ";

	main_menu[1].Subs = NullSubs;

	main_menu[1].children_menus = time_menu;

	main_menu[1].parent_menus = 0;


	main_menu[2].menu_count = 5;

	main_menu[2].disp_str = "3 LED Control";

	main_menu[2].Subs = NullSubs;

	main_menu[2].children_menus = led_menu;

	main_menu[2].parent_menus = 0;


	main_menu[3].menu_count = 5;

	main_menu[3].disp_str = "4 Temperture ";

	main_menu[3].Subs = NullSubs;

	main_menu[3].children_menus = temp_menu;

	main_menu[3].parent_menus = 0;


	main_menu[4].menu_count = 5;

	main_menu[4].disp_str = "5 File System";

	main_menu[4].Subs = NullSubs;

	main_menu[4].children_menus = file_menu;

	main_menu[4].parent_menus = 0;
	

}

void InitClockMenu(void)
{

 	clock_menu[0].menu_count = CLOCK_MENU_NUMS;
	
	clock_menu[0].disp_str = "1 Show Time  ";
	
	clock_menu[0].Subs = NullSubs;
	
	clock_menu[0].children_menus = 0;
	
	clock_menu[0].parent_menus = main_menu;
	
	
	clock_menu[1].menu_count = CLOCK_MENU_NUMS;
	
	clock_menu[1].disp_str = "2 Set Time   ";
	
	clock_menu[1].Subs = NullSubs;
	
	clock_menu[1].children_menus = 0;
	
	clock_menu[1].parent_menus = main_menu;
	
	
}

void InitTimeMenu(void)
{

}

void InitLedMenu(void)
{

}

void InitTempMenu(void) 
{

}

void InitFileMenu(void)
{

}

#endif