#ifndef        __MENU_h__
#define        __MENU_h__

struct MenuItem
{

	short menu_count;

	char *disp_str;

	void (*Subs)();

	struct MenuItem *children_menus;

	struct MenuItem *parent_menus;

};

/***********************

*     º¯ Êý Éù Ã÷ Çø   *

***********************/

void NullSubs(void);

void InitMainMenu(void);

void InitClockMenu(void);

void InitTimeMenu(void);

void InitLedMenu(void);

void InitTempMenu(void);

void InitFileMenu(void);

#endif