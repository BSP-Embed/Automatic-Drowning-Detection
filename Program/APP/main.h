#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

//DEFINE PORTS
#define SW_DDR					DDRD
#define SW_PORT					PORTD
#define SW_PIN					PIND
#define TOP_SW_PIN				PD2
#define BOT_SW_PIN				PD3

//DEFINE CONSTANT
#define PRES_THRES		40.0f

//FUNCTION PROTOTYPES
static void		init		(void);
static void  	gpioinit	(void);
static void		flagsinit	(void);
static void 	tmr2init	(void);
static void 	disptitl 	(void);
static void		UnLockPool	(void);
static void		moton		(void);
static void		CtrlPool	(void);

#endif
