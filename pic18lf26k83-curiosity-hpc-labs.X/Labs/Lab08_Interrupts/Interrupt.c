/**
  Interrupt Lab Source File

  Company:
    Microchip Technology Inc.

  File Name:
    Interrupt.c

  Summary:
    This is the source file for the Interrupt lab

  Description:
    This source file contains the code on how the Interrupt lab works.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18LF26K83
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.45
        MPLAB             :  MPLAB X v4.15
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
 */

#include "../../mcc_generated_files/pin_manager.h"
#include "../../mcc_generated_files/interrupt_manager.h"
#include "../../mcc_generated_files/tmr0.h"
#include "../../labs.h"

/**
  Section: Local Function Prototypes
 */
void LAB_ISR(void);

/**
  Section: Local Variable Declarations
 */
static uint8_t rotateReg;

/*
                             Application    
 */
void Interrupt(void) {

    if (labState == NOT_RUNNING) {
        LEDs_SetLow();
        LED_D2_SetHigh();
        
        rotateReg = 1;
       
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_TMR0InterruptEnable();
        
        TMR0_SetInterruptHandler(LAB_ISR);
 
        labState = RUNNING;
    }

    if(labState == RUNNING){ 
        // Do nothing. Just wait for an interrupt event 
    }
    
    if (switchEvent) {
        INTERRUPT_TMR0InterruptDisable();

        INTERRUPT_GlobalInterruptDisable();

        labState = NOT_RUNNING;
    }
}

void LAB_ISR(void) {    
    //If the last LED has been lit, restart the pattern    
    if (rotateReg == 1) {
        rotateReg = LAST;
    }

    rotateReg >>= 1;
    
    //Check which LED should be lit
    LEDs = (rotateReg << 4);
}
/**
 End of File
 */
