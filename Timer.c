#include <REGX52.H>

void Timer_Init()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TF0 = 0;
	TL0 = 0xFF;
	TH0 = 0xFF;
	ET0 = 1;
	PT0 = 1;

	TMOD &= 0x0F;
	TMOD |= 0x10;
	TF1 = 0;
	TL1 = 0x66;
	TH1 = 0xFC;
	ET1 = 1;
	PT1 = 0;

	EA = 1;
}

void Timer0_Start()
{
	TR0 = 1;
}

void Timer0_Stop()
{
	TR0 = 0;
}

void Timer1_Start()
{
	TR1 = 1;
}

void Timer1_Stop()
{
	TR1 = 0;
}