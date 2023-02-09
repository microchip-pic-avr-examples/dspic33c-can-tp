/**
 * CAN-TP Generated Adaptor Header File
 * 
 * @file      can_tp_adaptor.h
 *            
 * @ingroup   cantpdriver
 *            
 * @brief     The CAN-TP Adaptor interfaces directly with the generated CAN/CAN-FD files. 
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

#ifndef CAN_PHY_H
#define CAN_PHY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/**
 @ingroup  cantpdriver
 @enum     CAN_PHY_TRANSMIT_STATUS
 @brief    This enumeration defines the FIFO status.
*/
enum CAN_PHY_TRANSMIT_STATUS{
    CAN_PHY_TRANSMIT_STATUS_SUCCESS,
    CAN_PHY_TRANSMIT_STATUS_ERROR,
    CAN_PHY_TRANSMIT_STATUS_PENDING
};
    
/**
  @ingroup cantpdriver

  @brief Adaptor method that interfaces with the can method ReceivedMessageCountGet.

  @pre CAN/CAN-FD Initialize function should be called before calling this function.

  @returns Number of messages received through CAN.
*/
uint8_t CAN_PHY_ReceivedMessageCountGet(void);

/**
  @ingroup cantpdriver

  @brief Adaptor method that interfaces with the CAN/CAN-FD method Recieve.

  @pre CAN/CAN-FD Initialize function should be called before calling this function.
  
  @param[out] data Pointer to the full message recieved by CAN-TP.
  @param[out] length Pointer to the length of the message.

  @returns if message was recieved successfully or not
*/
bool CAN_PHY_Receive(uint8_t *data, uint8_t *length);

/**
  @ingroup cantpdriver

  @brief Adaptor method that interfaces with the CAN/CAN-FD method Transmit.

  @pre CAN/CAN-FD Initialize function should be called before calling this function.
  
  @param[in] messageId ID of the message to send over CAN/CAN-FD.
  @param[in] isEid ID is extended or not.
  @param[in] data Pointer to the message to send.
  @param[in] length Length of the message to send.

  @returns if message was transmitted successfully or not.
*/
bool CAN_PHY_Transmit(uint32_t messageId, bool isEid, uint8_t *data, uint8_t length);

/**
  @ingroup cantpdriver

  @brief Adaptor method that interfaces with the CAN/CAN-FD method TransmitFIFOStatusGet.

  @pre CAN/CAN-FD Initialize function should be called before calling this function.
  
  @returns Enum of transmit status.
*/
enum CAN_PHY_TRANSMIT_STATUS CAN_PHY_TransmitStatusGet(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_PHY_H */
