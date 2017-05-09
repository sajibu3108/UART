/* ========================================
 *
 * Copyright Eduardo Inreriano, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Eduardo Interiano.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>


/* Global variables */
int16 data = 0;
float volts = 0;
float angulo = 0.0;
int   ContInt=0;

int value_counter = 0;
float distancia = 0;
char imp[9];

float tiempo = 0.0;

char displayStrLCD[16] = {'\0'};
char displayStrUART[16] = {'\0'};

/* Interrupt prototype */
CY_ISR_PROTO(isr_10_Handler);

// Interrupt handler declaration
CY_ISR(isr_10_Handler)
{
    // Denotes interrupt begin

    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    data = ADC_GetResult16();
    volts = ADC_CountsTo_Volts(data);
    angulo = (15.523*volts - 34.891)*3.1416/180;    
    
    if (ContInt>10){
        Trigger_out_Write(1);
        CyDelayUs(10);
        Trigger_out_Write(0);
        CyDelayUs(1000);
        while (echo_Read()==1){}
        value_counter=65535-Timer2_ReadCounter();
        distancia=value_counter/58.0;
        ContInt=0;
    }
    ContInt++;
   
}

int main(void)
{    
    /* Place your startup code here (e.g. MyInst_Start()) */
    ADC_Start();
    ADC_StartConvert();
    Timer2_Start();
    Timer_Start();
    
    T1_Start();//Temporizacion del motor
    
    // Interrrup process init with StartEx not simple Start
    isr_10_StartEx(isr_10_Handler);

    CyGlobalIntEnable; /* Enable global interrupts. */

    LCD_Start();
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("Angulo - Dist");
    
    UART_Start();
    sprintf(displayStrLCD,"%.2f r %.1f cm",volts, distancia);
    LCD_Position(1,0);
    LCD_PrintString(displayStrLCD);
        
    UART_PutString(displayStrUART);
    UART_PutString("\n\r");    
    // Infinite loop
    for(;;)
    {  
       sprintf(displayStrLCD,"%.2f r %.1f cm",volts, distancia);
       sprintf(displayStrUART,"%.2f, %.1f",angulo,distancia);
       LCD_Position(1,0);
       LCD_PrintString(displayStrLCD);
    
       UART_PutString(displayStrUART);
       UART_PutString("\n\r");
    } // for

} // main

/* [] END OF FILE */
