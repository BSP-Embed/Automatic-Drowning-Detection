#include "mps20n40.h"

extern int8u lcdptr;

float MeasPres(int8u disp)
{
	char s[10];
	int32u Pres;
	float PresFlo;
		
	Pres = HX711Read();
	PresFlo = (Pres - ATMOSPHERIC_PRESS) * ADC_CONST;
	
	if (disp){
		
		ftoa(PresFlo, s, 1);
	//	ltoa(Pres,s);
		lcdptr =disp;
		lcdws("          ");
		lcdptr = disp;
		lcdws(s);
	}
	
	return PresFlo;
}