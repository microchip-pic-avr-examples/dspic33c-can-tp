/**
 * CAN-TP Generated Adaptor Source File
 * 
 * @file      can_tp_adaptor.c
 *            
 * @ingroup   cantpdriver
 *            
 * @brief     This is the generated adaptor source file for CAN-TP.
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

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
    
#include "../can_tp_config.h"
#include "../can1.h"
#include "../can_tp_phy_adaptor.h"
        
static uint8_t DlcToDataBytesGet(const enum CAN_DLC dlc)
{
    static const uint8_t dlcByteSize[] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U};
    return dlcByteSize[dlc];
}

static enum CAN_DLC BytesToDLCGet(uint8_t length)
{
    enum CAN_DLC dlc = DLC_64;

    if(length <= 8u)
    {
        dlc = length;
    }
    else if(length <= 12u)
    {
        dlc = DLC_12;
    }
    else if(length <= 16u)
    {
        dlc = DLC_16;
    }
    else if(length <= 20u)
    {
        dlc = DLC_20;
    }
    else if(length <= 24u)
    {
        dlc = DLC_24;
    }
    else if(length <= 32u)
    {
        dlc = DLC_32;
    }
    else if(length <= 48u)
    {
        dlc = DLC_48;
    }
    else
    {
        dlc = DLC_64;
    }

    return dlc;
}
    
uint8_t CAN_PHY_ReceivedMessageCountGet(void)
{
    return CAN_FD1.ReceivedMessageCountGet();
}

bool CAN_PHY_Receive(uint8_t *data, uint8_t *length)
{
    struct CAN_MSG_OBJ rxCanMsg;
    bool isReceived = false;

    if(CAN_FD1.ReceivedMessageCountGet() > 0u)
    {
        CAN_FD1.Receive(&rxCanMsg);

        *length = DlcToDataBytesGet(rxCanMsg.field.dlc);
        (void)memcpy(data, rxCanMsg.data, *length);  
        
        isReceived = true;
    }
    
    return isReceived;
}

bool CAN_PHY_Transmit(uint32_t messageId, bool isEid, uint8_t *data, uint8_t length)
{   
    struct CAN_MSG_OBJ txCanMsg;

    txCanMsg.msgId = messageId;
    txCanMsg.data = data;     // Pointer to the buffer to send
    txCanMsg.field.brs = CAN_BRS_MODE;           // 1 bit (Supported only in CAN FD mode)
    txCanMsg.field.dlc = BytesToDLCGet(length);  // amount of data to send.  
    txCanMsg.field.formatType = CAN_FD_FORMAT;   // 1 bit (CAN 2.0 Format or CAN_FD Format)
    txCanMsg.field.frameType  = CAN_FRAME_DATA;  // 1 bit (Data Frame or RTR Frame)

    if(isEid == true)
    {
        txCanMsg.field.idType     = CAN_FRAME_EXT;   // 1 bit (Standard Frame or Extended Frame)
    }
    else
    {
        txCanMsg.field.idType     = CAN_FRAME_STD;   // 1 bit (Standard Frame or Extended Frame)
    }
    return (CAN_FD1.Transmit(CAN1_TX_TXQ, &txCanMsg) == CAN_TX_MSG_REQUEST_SUCCESS);
}

enum CAN_PHY_TRANSMIT_STATUS CAN_PHY_TransmitStatusGet(void)
{
    enum CAN_PHY_TRANSMIT_STATUS status = CAN_PHY_TRANSMIT_STATUS_ERROR;

    switch(CAN_FD1.TransmitFIFOStatusGet(CAN1_TX_TXQ))
    {
        case CAN_TX_FIFO_AVAILABLE:
            status = CAN_PHY_TRANSMIT_STATUS_SUCCESS;
            break;
            
        case CAN_TX_FIFO_FULL:
            status = CAN_PHY_TRANSMIT_STATUS_PENDING;
            break;
            
        default:
            break;
    }
    
    return status;
}
