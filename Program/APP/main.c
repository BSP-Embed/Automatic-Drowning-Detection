#include "main.h"

const char *MSG[] = { "Person sinked into swimming Pool. Please Attend immediately." };

volatile struct  {
	volatile int8u Meas:1;
}Flags;

extern int8u lcdptr;

int main(void)
{
	init();
	
	while (TRUE) {
		if (Flags.Meas) {
			if (MeasPres(0) > PRES_THRES) {
				buzon();
				CtrlPool();
			}
			Flags.Meas = FALSE;
		}
	}
	return 0;
}
static void init(void)
{
	buzinit();
	beep(2,100);
	ledinit();
	gpioinit();
	flagsinit();	
	lcdinit();
	uartinit();
	HX711init();
	GSMinit();
	tmr2init();
	motorinit();
	UnLockPool();
	disptitl();
	sei();
}
static void flagsinit(void)
{
	Flags.Meas = FALSE;
}
	
static void gpioinit(void)
{
	SW_DDR  &= ~(_BV(TOP_SW_PIN) | _BV(BOT_SW_PIN));
	SW_PORT |= (_BV(TOP_SW_PIN) | _BV(BOT_SW_PIN));
}
static void disptitl(void)
{
	lcdclr();
	lcdws(" Auto Drowning");
	lcdr2();
	lcdws("Detect&Security");
}
static void tmr2init(void)
{
	TCNT2   = 75;
	TIMSK   |= _BV(TOIE2);			//ENABLE OVERFLOW INTERRUPT
	TCCR2  |=  _BV(CS22) | _BV(CS21) | _BV(CS20); /* PRESCALAR BY 256 */
}

/* overflows at every 25msec */
ISR(TIMER2_OVF_vect)
{
	static int8u i,j,k;
	TCNT2 = 75;

	if (++i >= 200) i = 0;
	switch(i) {
		case 0: case 5: ledon(); break;
		case 1: case 6: ledoff(); break;
	}
	
	if (++j >= 40) {
		j = 0;
		Flags.Meas =  TRUE;
	}
}
static void CtrlPool(void)
{
	moton();
	buzoff();
	GSMsndmsg(OPhNum, MSG[0]);
	disptitl();
	ledon();
	cli();
	sleep();
	for(;;);
}
static void moton(void)
{
	lcdclr();
	lcdws("  Lifting Plate");
	MotClk();	
	while (SW_PIN & _BV(TOP_SW_PIN));
	MotStop();
	
}
static void UnLockPool(void)
{
	lcdclr();
	lcdws(" UnLocking Pool");
	beep(1,100);
	MotAclk();
	while (SW_PIN & _BV(BOT_SW_PIN));
	MotStop();
	beep(1,100);
}