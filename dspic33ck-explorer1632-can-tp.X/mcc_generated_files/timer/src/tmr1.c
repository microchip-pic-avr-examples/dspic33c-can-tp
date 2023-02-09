/**
 * TMR1 Generated Driver Source File 
 * 
 * @file      tmr1.c
 * 
 * @ingroup   timerdriver
 * 
 * @brief     This is the generated driver source file for TMR1 driver
 *
 * @version   Driver Version 1.4.0
 *
 * @skipline  Device : dsPIC33CK256MP508
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

// Section: Included Files
#include "../tmr1.h"

// Section: Data Type Definitions

#define MASK_32_BIT_LOW 0x0000FFFFU
#define MASK_32_BIT_HIGH 0xFFFF0000U

// Section: File specific functions

static void (*TMR1_TimeoutHandler)(void) = NULL;

// Section: Driver Interface

const struct TIMER_INTERFACE Timer1 = {
    .Initialize            = &TMR1_Initialize,
    .Deinitialize          = &TMR1_Deinitialize,
    .Start                 = &TMR1_Start,
    .Stop                  = &TMR1_Stop,
    .PeriodCountSet        = &TMR1_PeriodCountSet,
    .PeriodSet             = &TMR1_PeriodSet,
	.PeriodGet             = &TMR1_PeriodGet,
    .CounterGet            = &TMR1_CounterGet,
    .InterruptPrioritySet  = &TMR1_InterruptPrioritySet,
    .TimeoutCallbackRegister = &TMR1_TimeoutCallbackRegister,
    .Tasks          = NULL
};

// Section: TMR1 Module APIs

void TMR1_Initialize (void)
{
    //TCS FOSC/2; TSYNC disabled; TCKPS 1:1; TGATE disabled; TECS ; PRWIP Write complete; TMWIP Write complete; TMWDIS disabled; TSIDL disabled; TON disabled; 
    T1CON = 0x0;
    //TMR 0x0; 
    TMR1 = 0x0;
    //Period 1 ms; Frequency 4,000,000 Hz; PR 3999; 
    PR1 = 0xF9F;
    
    TMR1_TimeoutCallbackRegister(&TMR1_TimeoutCallback);

    TMR1_Start();
}

void TMR1_Deinitialize (void)
{
    TMR1_Stop();
    
    T1CON = 0x0;
    TMR1 = 0x0;
    PR1 = 0x0;
}

void TMR1_Start( void )
{
    //Clear interrupt flag
    IFS0bits.T1IF = 0;
    //Enable the interrupt
    IEC0bits.T1IE = 1;
    
    // Start the Timer 
    T1CONbits.TON = 1;
}

void TMR1_Stop( void )
{
    // Stop the Timer 
    T1CONbits.TON = 0;
    
    //Disable the interrupt
    IEC0bits.T1IE = 0;
}

void TMR1_PeriodSet(uint32_t count)
{
    PR1 = (uint16_t)(count & MASK_32_BIT_LOW);
}

void TMR1_InterruptPrioritySet(enum INTERRUPT_PRIORITY priority)
{
    IPC0bits.T1IP = priority;
}

void TMR1_TimeoutCallbackRegister(void (*handler)(void))
{
    if(NULL != handler)
    {
        TMR1_TimeoutHandler = handler;
    }
}

void __attribute__ ((weak)) TMR1_TimeoutCallback( void )
{ 

} 

void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    (*TMR1_TimeoutHandler)();
    IFS0bits.T1IF = 0;
}

void TMR1_PeriodCountSet(size_t count)
{
    PR1 = count & MASK_32_BIT_LOW;
}

/**
 End of File
*/
