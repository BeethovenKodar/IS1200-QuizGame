/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // e)
  TRISD = TRISD | 0xFE0;

  TMR2 = 0;                 
  PR2 = (80000000 / 256 ) / 10; //count in prescale (still 1s period) and also divide by 10 for 100ms
  T2CONSET = 0x8070;            //start timer and set prescaling to 256 1000 0000 0111 0000 --> 8070

  // c)
  volatile int* trisE = (volatile int*) 0xbf886100;
  *trisE = *trisE & 0xFFFFFF00;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

  // d) funkar detta? 
  volatile int* portE = (volatile int*) 0xbf886110;

  if((mytime & 0xFFFF) == 0x5957)
    *portE = 0xFFFFFF00;

  // h)
  int btns = getbtns(); 
  int sw = getsw(); 

  //
  if(btns == 0x1) {  // 0x1 motsvarar btn 2 
    mytime = mytime & 0xFF0F;  // 001
    if(sw > 5)
      mytime = mytime & 0xFF00;
    else
      mytime = mytime | (sw << 4);
  }
  //
  if(btns == 0x2) { // 0x2 motsvarar btn 3
    mytime = mytime & 0xF0FF;  // 010
    if(sw > 9)
      mytime = mytime & 0xF000;
    else
      mytime = mytime | (sw << 8);
  }

  if(btns == 0x3) {
    mytime = mytime & 0xF00F;  // 011
    if(sw > 9) {
      mytime = mytime & 0xF00F;
    }
    else {
      mytime = mytime | (sw << 8);
      mytime = mytime | (sw << 4);
    }
  }
  //
  if(btns == 0x4) { // 0x3 motsvarar btn 4
    mytime = mytime & 0x0FFF;  // 100
    if(sw > 5)
      mytime = 0x0000;
    else
      mytime = mytime | (sw << 12);
  }
  //
  if(btns == 0x5) {
    mytime = mytime & 0x0F0F;  // 101
    if(sw > 5) {
      mytime = mytime & 0x0F0F; 
    }
    mytime = mytime | (sw << 12);
    mytime = mytime | (sw << 4);
  }
  //
  if(btns == 0x6) {
    mytime = mytime & 0x00FF;  // 110
    mytime = mytime | (sw << 8);
    mytime = mytime | (sw << 12);
  }

  if(btns == 0x7) {
    mytime = mytime & 0x000F;  // 111
    mytime = mytime | (sw << 4);
    mytime = mytime | (sw << 8);
    mytime = mytime | (sw << 12);
  }

  if(timeoutcount == 10) {
    time2string( textstring, mytime );
    tick( &mytime );
    display_update();
    *portE += 1;
    timeoutcount = 0; 
  }
    //delay( 5000 );
  if(((IFS(0) & 0x100) >> 8) == 1) {
    IFS(0) = IFS(0) & 0xFEFF;
    timeoutcount++;
  }
}


// . /opt/mcb32tools/environment
// 