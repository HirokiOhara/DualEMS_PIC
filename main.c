/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC32MM0064GPL028
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
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
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/uart1.h"

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    RN52_GPIO9_SetValue(false);  // Set RB11 as L  (= Data mode to Command mode)
    OD_L_SetValue(false);  // Set RB5 as L (= Start OD_L)
    OD_R_SetValue(false);  // Set RB6 as L (= Start OD_R)
    
    // define variables
    bool Flag = false;
    uint16_t portValue;
    uint8_t data[20];
    int i;
    int t;

    while (Flag == false)
    {
        portValue = RN52_GPIO2_GetValue();  // Read RB12 (= output from GPIO2)
        if (portValue == 0){  // If the input is L,
            while (UART1_IsRxReady()){
                UART1_Read();
            }
            UART1_Write('Q');  // Send command "Q\r\n"
            UART1_Write(0x0d);
            UART1_Write(0x0a);
            for(i=0; i<6; ++i){
                for(t=0; t< 400000 && !UART1_IsRxReady(); t++);
                if(UART1_IsRxReady()) {
                    data[i] = UART1_Read();  // Check RN52's condition
                }else{
                    data[i] = 0;
                }
            }
            if (data[0] == '0' && data[1] == '4' && data[2] == '0' && data[3]=='D'){  // If RN52 is connected,
//                RN52_GPIO9_SetValue(true);
                OD_L_SetValue(true);
                OD_R_SetValue(true);                 
            }else{
                OD_L_SetValue(false);
                OD_R_SetValue(false);
            }
        }
    }
    return 1;
}
/**
 End of File
*/

