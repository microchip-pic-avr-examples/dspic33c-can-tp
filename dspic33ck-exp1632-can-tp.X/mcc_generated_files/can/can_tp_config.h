/**
 * CAN-TP Generated Configuration Header File
 * 
 * @file      can_tp_config.h
 *            
 * @ingroup   cantpdriver
 *            
 * @brief     Configurations set in this file are utilized by the CAN-TP firmware files
 *            
 * @version   Driver Version 1.0.0
*/

/*
    (c) 2022 Microchip Technology Inc. and its subsidiaries. You may use this
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
#define CAN_TP_MESSAGE_ID_DATA         0xA1

/**
 @ingroup  cantpdriver
 @brief Configures the ID Data for the message being sent.
*/ 
#define CAN_TP_MESSAGE_ID_FLOW_CONTROL 0xA1

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
