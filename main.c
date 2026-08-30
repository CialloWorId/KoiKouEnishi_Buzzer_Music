#include <REGX52.H>
#include "Timer.h"
#include "Delay.h"
#include "Music.h"
#include "Lyrics.h"
#include "LCD1602.h"
#include "Yuzusoft.h"
#include "MusicInfo.h"

sbit Buzzer = P2 ^ 5;

unsigned char CurrentNote, NoteGap, MusicEnd, LrcSelect;
unsigned int NoteSelect, NoteTime;

unsigned int Beat;
unsigned int *FreqTable;
unsigned char *MusicScore;

void main()
{
    unsigned char i;

    LCD_Init();
    Timer_Init();
    
    Yuzusoft();
    Delay(3000);
    for (i = 0; i < 37; i++)
    {
        MusicTitle();
    }

    MusicInfo_SetChar();
    LCD_ShowChar(1, 1, '>');
	LCD_ShowString(1, 2, KoiKouEnishi_Lyrics[0]);
    LCD_ShowString(2, 2, KoiKouEnishi_Lyrics[1]);
	
    Beat = KoiKouEnishi_Beat;
    FreqTable = KoiKouEnishi_Freq;
    MusicScore = KoiKouEnishi_Score;

    CurrentNote = MusicScore[NoteSelect];
    NoteTime = (Beat * 4) / MusicScore[1] - 20;
    MusicEnd = 1;

    Timer0_Start();
    Timer1_Start();
    while (MusicEnd);
    
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

        switch (MusicScore[NoteSelect + 2])
        {
        case LINK:
            NoteSelect += 2;
            NoteTime = NoteTime = (Beat * 4) / MusicScore[NoteSelect + 1];
            break;
        
        case REST:
            Timer0_Stop();
            Buzzer = 1;
            NoteSelect += 2;
            NoteTime = NoteTime = (Beat * 4) / MusicScore[NoteSelect + 1];
            break;

        default:
            Timer0_Stop();
            Buzzer = 1;
            NoteGap = !NoteGap;

            if (NoteGap)
            {
                NoteTime = 20;
            }
            else
            {
                NoteSelect += 2;
                if(MusicScore[NoteSelect] == SCROLL)
                {
                    NoteSelect++;
                    LrcSelect++;
                    LCD_ShowString(1,2,KoiKouEnishi_Lyrics[LrcSelect]);
                    LCD_ShowString(2,2,KoiKouEnishi_Lyrics[LrcSelect+1]);
                }
                CurrentNote = MusicScore[NoteSelect];
                NoteTime = NoteTime = (Beat * 4) / MusicScore[NoteSelect + 1] - 20;
                Timer0_Start();
            }
            break;
        }

        if (MusicScore[NoteSelect + 1] == 0)
        {
            MusicEnd = 0;
        }
    }
}