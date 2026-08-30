#ifndef __LYRICS_H__
#define __LYRICS_H__

#define WO 0XA6
#define S_A 0XA7
#define S_I 0XA8
#define S_U 0XA9
#define S_E 0XAA
#define S_O 0XAB
#define S_YA 0XAC
#define S_YU 0XAD
#define S_YO 0XAE
#define S_TSU 0XAF
#define SUSTAIN 0XB0
#define A 0xB1
#define I 0xB2
#define U 0xB3
#define E 0xB4
#define O 0xB5
#define KA 0xB6
#define KI 0xB7
#define KU 0xB8
#define KE 0xB9
#define KO 0xBA
#define SA 0xBB
#define SHI 0xBC
#define SU 0xBD
#define SE 0xBE
#define SO 0xBF
#define TA 0xC0
#define CHI 0xC1
#define TSU 0xC2
#define TE 0xC3
#define TO 0xC4
#define NA 0xC5
#define NI 0xC6
#define NU 0xC7
#define NE 0xC8
#define NO 0xC9
#define HA 0xCA
#define HI 0xCB
#define FU 0xCC
#define HE 0xCD
#define HO 0xCE
#define MA 0xCF
#define MI 0xD0
#define MU 0xD1
#define ME 0xD2
#define MO 0xD3
#define YA 0xD4
#define YU 0xD5
#define YO 0xD6
#define RA 0xD7
#define RI 0xD8
#define RU 0xD9
#define RE 0xDA
#define RO 0xDB
#define WA 0xDC
#define N 0xDD
#define SONANT 0XDE
#define H_SONANT 0XDF

unsigned char code KoiKouEnishi_Lyrics[24][16] =
    {
        {0xA2, KO, HI, KO, FU, E, NI, SHI, 0xA3, ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {1, 2, 3, 4, ':', 'K', 'O', 'T', 'O', 'K', 'O', ' ', ' ', ' ', ' ', '\0'},
        {1, 2, 5, 6, ':', 'F', 'a', 'm', 'i', 's', 'h', 'i', 'n', ' ', ' ', '\0'},
        {MA, KO, TO, 0xA4, I, SHI, SONANT, NO, ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {WA, RU, I, KA, MI, NO, SHI, S_YO, KI, SONANT, S_YO, U, KA, '?', ' ', '\0'},
        {KI, SE, KI, '?', E, NI, SHI, '?', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {TA, MO, TO, FU, RE, A, U, FU, SHI, KI, SONANT, ' ', ' ', ' ', ' ', '\0'},
        {HA, NA, HI, TO, HI, RA, YU, RE, TE, ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {FU, I, NI, YA, TO, SONANT, S_TSU, TE, TA, ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {U, NA, SHI, SONANT, HO, TO, SONANT, I, TE, KU, HA, RU, KA, SE, SONANT, '\0'},
        {TA, WA, MU, RE, HA, SO, KO, SO, KO, NI, ' ', ' ', ' ', ' ', ' ', '\0'},
        {KO, I, TE, HO, TO, SONANT, KI, SHI, TE, ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {KU, TA, SONANT, SHI, S_YA, N, SE, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {YU, KE, SONANT, NI, HO, N, NO, RI, HO, HO, SO, ME, TE, ' ', ' ', '\0'},
        {YO, KA, SE, SONANT, NI, NE, KA, SONANT, FU, ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {0XA5, 0XA5, 0XA5, I, SA, SONANT, '!', '!', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {CHI, S_YO, SUSTAIN, TO, MA, HI, HA, NA, TO, NA, RI, TE, ' ', ' ', ' ', '\0'},
        {KI, NU, WO, MI, TA, SONANT, SHI, TE, HA, RA, I, MA, SHI, S_YO, SUSTAIN, '\0'},
        {A, YA, NA, SHI, KO, KO, RO, NO, KE, KA, SONANT, RE, ' ', ' ', ' ', '\0'},
        {0XA5, 0XA5, 0XA5, YU, E, '!', '!', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
        {TO, SUSTAIN, TO, NA, RI, TA, TE, TO, NA, RI, TE, ' ', ' ', ' ', ' ', '\0'},
        {KO, NO, O, MO, I, MA, MO, RI, TA, MA, E, ' ', ' ', ' ', ' ', '\0'},
        {KI, MI, KA, SONANT, KO, I, NO, MO, N, WO, A, YA, ME, TA, ' ', '\0'},
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}
    };

#endif