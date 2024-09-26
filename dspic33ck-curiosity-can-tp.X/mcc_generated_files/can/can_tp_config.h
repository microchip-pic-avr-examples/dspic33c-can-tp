/**
 * CAN-TP Generated Configuration Header File
 * 
 * @file      can_tp_config.h
 *            
 * @ingroup   cantpdriver
 *            
 * @brief     Configurations set in this file are utilized by the CAN-TP firmware files
 *            
 * @version   Driver Version 1.1.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

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

#ifndef CAN_TP_CONFIG_H
#define CAN_TP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
    
 /**
 @ingroup  cantpdriver
 @brief Defined in the specification as TX_DL. Valid options are:
    8 = CAN Classic 
    8, 12, 16, 20, 24, 32, 48, or 64 = CAN-FD
*/
#define CAN_TP_TRANSMISSION_DATA_LENGTH_MAX 8

 /**
 @ingroup  cantpdriver
 @brief  Configures the message id to be extended or standard.
*/ 
#define CAN_TP_MESSAGE_ID_IS_EXTENDED  false

/**
 @ingroup  cantpdriver
 @brief Configures the ID Flow Control for the message being sent.
*/ 
#define CAN_TP_MESSAGE_ID_DATA         0xA2

/**
 @ingroup  cantpdriver
 @brief Configures the ID Data for the message being sent.
*/ 
#define CAN_TP_MESSAGE_ID_FLOW_CONTROL 0xA2

/**
 @ingroup  cantpdriver
 @brief Configures the time between messages being sent.
*/ 
#define CAN_TP_DEFAULT_SEPARATION_TIME_MS 1

/**
 @ingroup  cantpdriver
 @brief Configures the number of frames to send before another flow control is required.
*/ 
#define CAN_TP_DEFAULT_BLOCK_SIZE 0

/**
 @ingroup  cantpdriver
 @brief Configures if there is a pause on first frame. This stops any further CAN packets
  from being sent after the first frame until CAN-TP Rx is resumed again. Enabling this requires 
  the use of the CAN_TP_RxResume() function to be called to continue receiving packets.
*/  
#define CAN_TP_PAUSE_ON_FIRST_FRAME false

#ifdef __cplusplus
}
#endif

#endif /* CAN_TP_CONFIG_H */
