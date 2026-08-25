#include <REGX52.H>
#include "Timer.h"
#include "Delay.h"
#include "Music.h"
#include "MusicInfo.h"

sbit Buzzer = P2^5;

unsigned char CurrentNote, NoteFinish, MusicEnd;
unsigned int NoteSelect, NoteTime;

unsigned int Beat;
unsigned int *FreqTable;
unsigned char *MusicScore;

void main()
{
	LCD_Init();
    Timer_Init();
	
	Beat = koihikoen_Beat;
    FreqTable = koihikoen_Freq;
    MusicScore = koihikoen_Score;
	
	CurrentNote = MusicScore[NoteSelect];
	NoteTime = (Beat * 4) / MusicScore[1] - 20;
	MusicEnd = 1;
	
	Timer0_Start();
	Timer1_Start();
	while(MusicEnd)
	{	
        if(NoteFinish)
        {
			Timer0_Stop();
			Timer1_Stop();
			
            Buzzer = 1;
			NoteFinish = 0;
            NoteSelect += 2;
            CurrentNote = MusicScore[NoteSelect];
			
            if(MusicScore[NoteSelect + 2] != LINK)
			{
                NoteTime = (Beat * 4) / MusicScore[NoteSelect + 1] - 20;
            }
            else
            {
                unsigned int temp = NoteSelect + 2;
                NoteTime = (Beat * 4) / MusicScore[NoteSelect + 1] - 20;
                while (MusicScore[temp] == LINK)
                {
                    NoteTime += (Beat * 4) / MusicScore[temp + 1];
                    temp += 2;
                }
            }
            
            Delay(20);

            if (MusicScore[NoteSelect] != REST && MusicScore[NoteSelect] != LINK)
            {
                Timer0_Start();
            }
            if (MusicScore[NoteSelect] != LINK)
			{
                Timer1_Start();
            }
            else
            {
                NoteFinish = 1;
            }
        }

        if (!MusicScore[NoteSelect + 1])
        {
            MusicEnd = 0;
        }
	}
    Timer0_Stop();
	Timer1_Stop();
    Buzzer = 1;
    NoteSelect = 0;
    Delay(1000);
}

void Timer0_Rountine(void) interrupt 1
{
	TL0 = FreqTable[CurrentNote] % 256;
	TH0 = FreqTable[CurrentNote] / 256;
	Buzzer = !Buzzer;
}

void Timer1_Rountine(void) interrupt 3
{
	static unsigned int TCount = 0;
    TL1 = 0x66;
	TH1 = 0xFC;
    TCount++;
    if (TCount >= NoteTime)
    {
        TCount = 0;
        NoteFinish = 1;
    }
}