#include <REGX52.H>
#include "Timer.h"
#include "Delay.h"
#include "Music.h"
#include "Lyrics.h"
#include "LCD1602.h"
#include "Character.h"

sbit Buzzer = P2 ^ 5;

struct MusicControl
{
    unsigned char CurrentNote;
    unsigned char NoteEnd;
    unsigned char NoteGap;
    unsigned char MusicEnd;
    unsigned char LrcSelect;

    unsigned int NoteSelect;
    unsigned int NoteTime;
};

struct MusicInfo
{
    unsigned int Beat;
    unsigned int *FreqTable;
    unsigned char *MusicScore;
    unsigned char (*MusicLyrics)[16];
};

struct MusicControl Ctrl = {0, 0, 0, 0, 0, 0, 0};
struct MusicInfo Info;

void main()
{
    unsigned char i;

    LCD_Init();
    Timer_Init();

    Yuzusoft_ShowIcon();
    Delay(3000);
    for (i = 0; i < 37; i++)
    {
        MusicTitle();
    }

    Info.Beat = KoiKouEnishi_Beat;
    Info.FreqTable = KoiKouEnishi_Freq;
    Info.MusicScore = KoiKouEnishi_Score;
    Info.MusicLyrics = KoiKouEnishi_Lyrics;

    Ctrl.CurrentNote = Info.MusicScore[Ctrl.NoteSelect];
    Ctrl.NoteTime = (Info.Beat * 4) / Info.MusicScore[1] - 20;
    Ctrl.MusicEnd = 1;

    MusicInfo_SetChar();
    LCD_ShowChar(1, 1, '>');
    LCD_ShowString(1, 2, Info.MusicLyrics[0]);
    LCD_ShowString(2, 2, Info.MusicLyrics[1]);

    Timer0_Start();
    Timer1_Start();
    while (Ctrl.MusicEnd)
    {
        if (Ctrl.NoteEnd)
        {
            switch (Info.MusicScore[Ctrl.NoteSelect + 2])
            {
            case LINK:
                Ctrl.NoteSelect += 2;
                Ctrl.NoteTime = (Info.Beat * 4) / Info.MusicScore[Ctrl.NoteSelect + 1];
                Ctrl.NoteEnd = 0;
                break;

            case REST:
                Timer0_Stop();
                Buzzer = 1;
                Ctrl.NoteSelect += 2;
                Ctrl.NoteTime = (Info.Beat * 4) / Info.MusicScore[Ctrl.NoteSelect + 1];
                Ctrl.NoteEnd = 0;
                break;

            case SCROLL:
                Timer0_Stop();
                Ctrl.NoteSelect++;
                Ctrl.LrcSelect++;
                LCD_ShowString(1, 2, Info.MusicLyrics[Ctrl.LrcSelect]);
                LCD_ShowString(2, 2, Info.MusicLyrics[Ctrl.LrcSelect + 1]);
                if (Ctrl.LrcSelect == 23)
                {
                    LCD_ShowChar(1, 1, ' ');
                    Yuzusoft_SetChar();
                }
                break;

            default:
                Timer0_Stop();
                Buzzer = 1;
                Ctrl.NoteGap = !Ctrl.NoteGap;
                if (Ctrl.NoteGap)
                {
                    Ctrl.NoteTime = 20;
                    Ctrl.NoteEnd = 0;
                }
                else
                {
                    Ctrl.NoteSelect += 2;
                    Ctrl.CurrentNote = Info.MusicScore[Ctrl.NoteSelect];
                    Ctrl.NoteTime = (Info.Beat * 4) / Info.MusicScore[Ctrl.NoteSelect + 1] - 20;
                    Ctrl.NoteEnd = 0;
                    Timer0_Start();
                }

                break;
            }
        }

        if (Info.MusicScore[Ctrl.NoteSelect + 1] == 0)
        {
            Ctrl.MusicEnd = 0;
        }
    }

    Timer0_Stop();
    Timer1_Stop();
    Buzzer = 1;
    Ctrl.NoteSelect = 0;
    Delay(1000);
}

void Timer0_Rountine(void) interrupt 1
{
    TL0 = Info.FreqTable[Ctrl.CurrentNote] % 256;
    TH0 = Info.FreqTable[Ctrl.CurrentNote] / 256;
    Buzzer = !Buzzer;
}

void Timer1_Rountine(void) interrupt 3
{
    static unsigned int TCount = 0;
    TL1 = 0x66;
    TH1 = 0xFC;
    TCount++;
    if (TCount >= Ctrl.NoteTime)
    {
        TCount = 0;
        Ctrl.NoteEnd = 1;
        Ctrl.NoteTime = 10;
    }
}