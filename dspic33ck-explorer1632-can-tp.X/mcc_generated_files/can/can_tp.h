/**
 * CAN-TP Generated Header File
 * 
 * @defgroup cantpdriver CAN-TP Driver
 * 
 * @file      can_tp.h
 *            
 * @ingroup   cantpdriver
 *            
 * @brief     The CAN-TP firmware defines types and interfaces with the CAN-TP adaptor for communication over CAN/CAN-FD
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

#ifndef CAN_TP_H
#define CAN_TP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/**
 @ingroup  cantpdriver
 @enum     CAN_TP_EVENT 
 @brief    Enumeration defining the CAN-TP event information.
*/
enum CAN_TP_EVENT{
    CAN_TP_EVENT_FIRST_FRAME_INDICATION,
    CAN_TP_EVENT_OVERFLOW,
    CAN_TP_EVENT_INDICATION,
    CAN_TP_EVENT_DATA_CONFIRM
};

/**
 @ingroup  cantpdriver
 @enum     CAN_TP_MESSAGE_TYPE
 @brief    Enumeration defining the diagnostic type.
*/
enum CAN_TP_MESSAGE_TYPE{
    CAN_TP_MESSAGE_TYPE_DIAGNOSTICS,
    CAN_TP_MESSAGE_TYPE_REMOTE_DIAGNOSTICS
};

/**
 @ingroup  cantpdriver
 @enum     CAN_TP_NETWORK_TARGET_ADDRESS_TYPE
 @brief    Enumeration defining Address type.
*/
enum CAN_TP_NETWORK_TARGET_ADDRESS_TYPE{
    CAN_TP_NETWORK_TARGET_ADDRESS_TYPE_1,
    CAN_TP_NETWORK_TARGET_ADDRESS_TYPE_2,
    CAN_TP_NETWORK_TARGET_ADDRESS_TYPE_3,
    CAN_TP_NETWORK_TARGET_ADDRESS_TYPE_4,
    CAN_TP_NETWORK_TARGET_ADDRESS_TYPE_5,
    CAN_TP_NETWORK_TARGET_ADDRESS_TYPE_6,
    CAN_TP_NETWORK_TARGET_ADDRESS_TYPE_7,
    CAN_TP_NETWORK_TARGET_ADDRESS_TYPE_8
};

/**
 @ingroup  cantpdriver
 @enum     CAN_TP_RESULT
 @brief    Enumeration of results of a message.
*/
enum CAN_TP_RESULT {
    CAN_TP_RESULT_OK,
    CAN_TP_RESULT_TIMEOUT_A,
    CAN_TP_RESULT_TIMEOUT_BS,
    CAN_TP_RESULT_TIMEOUT_CR,
    CAN_TP_RESULT_WRONG_SEQUENCE_NUMBER,
    CAN_TP_RESULT_INVALID_FLOW_STATUS,
    CAN_TP_RESULT_UNEXPECTED_PROTOCOL_DATA_UNIT,
    CAN_TP_RESULT_WFT_OVERUN,
    CAN_TP_RESULT_BUFFER_OVERFLOW,
    CAN_TP_RESULT_ERROR
};

/**
 @ingroup  cantpdriver
 @struct   CAN_TP_SERVICE_HEADER   
 @brief    Structure that contains the message header information.
*/
struct CAN_TP_SERVICE_HEADER{
    enum CAN_TP_MESSAGE_TYPE messageType; 
    uint8_t networkSourceAddress; 
    uint8_t networkTargetAddress; 
    enum CAN_TP_NETWORK_TARGET_ADDRESS_TYPE networkTargetAddressType;
    uint8_t networkAddressExtension;
};

/**
 @ingroup  cantpdriver
 @struct   CAN_TP_EVENT_FIRST_FRAME_INDICATION_DATA
 @brief    Structure that contains the first frame length.
*/
struct CAN_TP_EVENT_FIRST_FRAME_INDICATION_DATA {
    uint32_t length;
};

/**
 @ingroup  cantpdriver
 @struct   CAN_TP_EVENT_INDICATION_DATA
 @brief    Structure that contains the event data. 
*/
struct CAN_TP_EVENT_INDICATION_DATA {
    uint8_t *messageData;
    uint32_t length;
    enum CAN_TP_RESULT result;
};

/**
 @ingroup  cantpdriver
 @struct   CAN_TP_EVENT_CONFIRM_DATA
 @brief    Structure that contains the results of an event.
*/
struct CAN_TP_EVENT_CONFIRM_DATA {
    enum CAN_TP_RESULT result;
};

/**
 @ingroup  cantpdriver
 @typedef  *CAN_TP_EventCallback
 @brief defines what the event callback value consists of.    
*/
typedef void (*CAN_TP_EventCallback)(
    enum CAN_TP_EVENT event, 
    struct CAN_TP_SERVICE_HEADER *header,
    void *payload
);

/**
  @ingroup cantpdriver

  @brief Initializes the CAN-TP layer
*/
void CAN_TP_Initialize(void);

/**
  @ingroup cantpdriver

  @brief Sets and event callback handler for the CAN-TP events to go to.

  @details
    The specified function will be called whenever there are events that 
    the ISO 15765-2 specification says the upper layer should be notified.
 
    This is typically called in the system configuration and will not be used
    during the normal operation.
  
    The callback will have 3 parameters:
     - The event of CAN_TP_EVENT type
     - The addressing information in the CAN_TP_SERVICE_HEADER struct
     - The event data payload in the *void pointer

    The event data payload will be a pointer to a structure that has the
    data for that specific type of event.  For example, the 
    CAN_TP_EVENT_INDICATION event will use the CAN_TP_EVENT_INDICATION_DATA
    structure for the data field.  

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @param[in] callback Function to call on an event.

  @returns None
*/
void CAN_TP_EventCallbackSet(CAN_TP_EventCallback callback);

/**
  @ingroup cantpdriver
  
  @brief Provides the CAN-TP with a buffer to receive messages into.

  @details
    The CAN-TP layer will use this buffer to receive the messages and then notify 
    the upper layer via the event callback when the message is complete or terminated.

    This is typically called in the system configuration and will not be used
    during the normal operation.
 
  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @param[in] buffer Pointer to data buffer to use for message storage.
  @param[in] bufferSize  Size of the buffer that is being provided.

  @returns None
*/
void CAN_TP_RxMessageBufferSet(uint8_t *buffer, size_t bufferSize);

/**
  @ingroup cantpdriver
  
  @brief Tasks routine that keeps the CAN-TP layer running

  @details
    This should be called frequently to keep the CAN-TP layer running correctly.  
    This needs to be called at least as frequently as the minimum CAN-TP timeout 
    of the system which is typically at least once a second (though more frequent is 
    preferred).

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @return None
*/
void CAN_TP_Tasks(void);

/**
  @ingroup cantpdriver
  
  @brief
    Function that handles all the timed events.

  @details
    This function must be called by the user once every 1 millisecond 
    to keep the internal timing correct.  The precision of the call is
	  not very critical but should be once per millisecond.  The time spent 
    in this function is minimal.  A few variables are changed and then it
    returns and the events that are handled in the Tasks() function.

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @return None
*/
void CAN_TP_Tick(void);

/**
  @ingroup cantpdriver
  
  @brief Indicates if a message is complete and ready to read.

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @return bool - true if message is ready, false message is not available
*/
bool CAN_TP_IsMessageReady(void);

/**
  @ingroup cantpdriver
  
  @brief Gets the message received by the CAN-TP layer

  @details
    This buffer must be at least as large as the message in the buffer.  
    The CAN_TP_MessageLengthGet() function can be used to determine the 
    length if required.

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @param[out] buffer Pointer to the buffer to copy the message into.  if NULL, the message
    will be expired without copying it.

  @return bool - true if message was available, false if no message available.
*/
bool CAN_TP_MessageGet(uint8_t *buffer);

/**
  @ingroup cantpdriver
  
  @brief Gets the length of the available message

  @details This returns 0 if no message is available.

  @pre CAN_TP_Initialize function should have been called before calling this function.

  @return size_t - length of the available message.  0 if no message available.
*/
size_t CAN_TP_MessageLengthGet(void);

/**
  @ingroup cantpdriver
  
  @brief Sends a given message using CAN-TP.

  @details Sends the specified message through the CAN-TP layer.

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @param[in] buffer Pointer to a message to send.
  @param[in] length Length of the message to send.

  @return bool - true if able to start sending message, false if couldn't start
*/
bool CAN_TP_MessageSend(const uint8_t *buffer, size_t length);

/**
  @ingroup cantpdriver
  
  @brief Sets the requested separation time between RX frames.

  @details
    This is specified to the transmitter in the flow control packet.

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @param[in] separationTime Number of requested milliseconds between RX frames.
    Valid range [0-127].  Numbers above 127 will be truncated to 127. 

  @return None
*/
void CAN_TP_RxSeparationTimeSet(uint8_t separationTime);

/**
  @ingroup cantpdriver
  
  @brief Sets number of frames to receive in a segmented message before pausing the reception.

  @details
    This is the number of consecutive frames to receive after the first frame, thus 
    the first frame is not included in this count. 
  
    Must be set before the start of a segmented message reception.  This can be
    called as late as the FIRST_FRAME event and still take affect.  After the
    return of the FIRST_FRAME event, this function will have no effect until the
    next segmented message. 
 
    The default size if never called is 0, which indicates no pause (continuous
    reception until message is complete). 

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @param[in] blockSize Number of bytes to receive before pausing
    the incoming reception.  Setting to 0 will make the reception never pause.

  @return None
*/
void CAN_TP_RxBlockSizeSet(uint8_t blockSize);

/**
  @ingroup cantpdriver
  
  @brief Allows reception to continue after paused because of the block size limit or if Pause on First Frame selection is enabled.

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @return None
*/
void CAN_TP_RxResume(void);

/**
  @ingroup cantpdriver
  
  @brief Pause reception of a segmented at the next FlowControl or FirstFrame packet

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @return None
*/
void CAN_TP_RxPause(void);

/**
  @ingroup cantpdriver
  
  @brief Returns true if packet reception is paused.

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @return bool - if the reception is paused.
*/
bool CAN_TP_IsRxPaused(void);

/**
  @ingroup cantpdriver
  
  @brief Sets the maximum CAN frame allowed.

  @details
    Default will be the CAN_TP_TRANSMISSION_DATA_LENGTH_MAX configuration option if specified.  
    It will be 8 otherwise.  
  
    Valid options are 8 for CAN Classic and 12, 16,20, 24, 32, 48 or 64 for
    CAN-FD.

  @pre CAN_TP_Initialize function should have been called before calling this function. 

  @param[in] newMax Desired maximum CAN frame length allowed.

  @return bool - if the requested max is set.
*/
bool CAN_TP_MaxFrameLengthSet(uint8_t newMax);


#ifdef __cplusplus
}
#endif

#endif /* CAN_TP_H */
