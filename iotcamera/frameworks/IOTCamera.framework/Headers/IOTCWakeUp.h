/*! \file IOTCWakeUp.h
Due to power consumption concern, device will enter sleep mode and all. 
IOTC module will be disconnected. It needs a way to keep login and wake IOTC up.

\copyright Copyright (c) 2010 by Throughtek Co., Ltd. All Rights Reserved.

Revision Table

Version     | Name             |Date           |Description
------------|------------------|---------------|-------------------
 3.1.5.0    |Ferando           |2017-03-03     |Add new API IOTC_WakeUp_Setup_Auto_WakeUp, IOTC_WakeUp_Get_SleepPacket, IOTC_WakeUp_SleepPacketCB is a function callback for IOTC_WakeUp_Get_SleepPacket
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

#ifndef __IOTC_WAKEUP_H__
#define __IOTC_WAKEUP_H__


#ifdef _WIN32
	#if defined P2PAPI_EXPORTS
		#define P2PAPI_API __declspec(dllexport)
	#else
		#define P2PAPI_API __declspec(dllimport)
	#endif
#else
	#define P2PAPI_API
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define P2PAPI_API_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
    #ifdef IOTC_STATIC_LIB
        #define P2PAPI_API_DEPRECATED __declspec(deprecated)
    #elif defined P2PAPI_EXPORTS
        #define P2PAPI_API_DEPRECATED __declspec(deprecated, dllexport)
    #else
        #define P2PAPI_API_DEPRECATED __declspec(deprecated, dllimport)
    #endif
#else
    #define P2PAPI_API_DEPRECATED
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _IOTC_WakeUpData
{
    uint32_t 		ulLoginAddr;		   // Login Address
    uint16_t		usLoginPort;		   // Login Port
    size_t          nLoginPacketLength;    // Login packet length
    char		    *pszLoginPacket;       // Login packet data buffer
    uint32_t        nLoginInterval;        // Send login time interval
    size_t          nWakeupPatternLength;  // WakeUp pattern length
    char		    *pszWakeupPattern;     // WakeUp pattern
} IOTC_WakeUpData;

typedef struct _IOTC_WakeUpDataEx {
    uint32_t    ulAliveAddr;            // Alive Address
    uint16_t    usAlivePort;            // Alive Port
    size_t      nAlivePacketLength;     // Alive packet length
    char        *pszAlivePacket;        // Alive packet data buffer
    uint32_t    nAliveInterval;         // Send Alive time interval
    size_t      nWakeupPatternLength;   // WakeUp pattern length
    char        *pszWakeupPattern;      // WakeUp pattern
    size_t      nLoginPacketLength;     // Login packet length
    char        *pszLoginPacket;        // Login packet data buffer
} IOTC_WakeUpDataEx;

/**
 * \brief the callback funciton for IOTC_WakeUp_Get_SleepPacket
 *
 * \param pData pointer to IOTC_WakeUpData structure
 * \param nDataCnt the length of pData
 * \param nErrCode error code. 0 for success.
 */
typedef void (*IOTC_WakeUp_SleepPacketCB) (IOTC_WakeUpData *pData, uint32_t nDataCnt, int32_t nErrCode);

/**
 * \brief the callback funciton for IOTC_WakeUp_Get_SleepPacketEx
 *
 * \param pData pointer to IOTC_WakeUpDataEx structure
 * \param nDataCnt the length of pData
 * \param nErrCode error code. 0 for success.
 */
typedef void (*IOTC_WakeUp_SleepPacketExCB)(IOTC_WakeUpDataEx *pData, uint32_t nDataCnt, int32_t nErrCode);

/**
 * \brief Initial IOTC WakeUp feature
 *
 * \param None
 *
 * \return None
 *
 * \attention "Only" Device needs to use this API.
 *            Must invoke this API before using IOTC_WakeUp_Get_SleepPacket() API
 */
P2PAPI_API void IOTC_WakeUp_Init();

/**
 * \brief DeInitial IOTC WakeUp feature
 *
 * \param pData[in]	pointer to IOTC_WakeUpData structure
 *
 * \return None
 *
 * \attention "Only" Device needs to use this API.
 *            DeInit wake up feature and free all memory allocated by IOTC.
 *            It will cause memory leak if doesn't use this function at the
 *            end of wake up feature.
 */
P2PAPI_API_DEPRECATED void IOTC_WakeUp_DeInit(IOTC_WakeUpData *pData);

/**
 * \brief DeInitial IOTC WakeUp feature
 *
 * \param pData[in]	pointer to IOTC_WakeUpDataEx structure
 *
 * \return None
 *
 * \attention "Only" Device needs to use this API.
 *            DeInit wake up feature and free all memory allocated by IOTC.
 *            It will cause memory leak if doesn't use this function at the
 *            end of wake up feature.
 */
P2PAPI_API void IOTC_WakeUp_DeInitEx(IOTC_WakeUpDataEx *pData);

/**
 * \brief Send IOTC WakeUp request to wake device up
 *
 * \param pcszUID[in] The UID of a device that client wants to connect
 *
 * \return Error code if return value < 0
 *			- #IOTC_ER_NOT_SUPPORT Feature is not supported on current UID.
 *
 * \attention "Only" Client needs to use this API.
 */
P2PAPI_API int32_t IOTC_WakeUp_WakeDevice(const char *pcszUID);


/**
 * \brief notify P2P servers that device is going to sleep.
 * 
 * \param fptrReadyForSleepingCB[in] fptrReadyForSleepingCB will be called when all servers reponse or reach timeout.
 * \param nTimeout[in] set the timeout of waiting ack from servers. default 6 sec if given 0.
 *
 * \attention "Only" Device needs to use this API.
 */
P2PAPI_API_DEPRECATED int32_t IOTC_WakeUp_Get_SleepPacket(IOTC_WakeUp_SleepPacketCB fptrReadyForSleepingCB, int32_t nTimeoutMs);

/**
 * \brief notify P2P servers that device is going to sleep with Wake Up 3.0 protocol.
 *
 * \param fptrReadyForSleepingCB[in] fptrReadyForSleepingCB will be called when all servers reponse or reach timeout.
 * \param nTimeout[in] set the timeout of waiting ack from servers. default 6 sec if given 0.
 *
 * \attention "Only" Device needs to use this API.
 */
P2PAPI_API_DEPRECATED int32_t IOTC_WakeUp_Get_SleepPacket2(IOTC_WakeUp_SleepPacketCB fptrReadyForSleepingCB, int32_t nTimeoutMs);

/**
 * \brief notify P2P servers that device is going to sleep and wake up with Wake Up 3.0 protocol.
 *
 * \param fptrReadyForSleepingCB[in] fptrReadyForSleepingCB will be called when all servers reponse or reach timeout.
 * \param nTimeout[in] set the timeout of waiting ack from servers. default 6 sec if given 0.
 *
 * \attention "Only" Device needs to use this API.
 */
P2PAPI_API int32_t IOTC_WakeUp_Get_SleepPacketEx(IOTC_WakeUp_SleepPacketExCB fptrReadyForSleepingCB, int32_t nTimeoutMs);

/**
 * \brief enable that IOTC_Connect_ByUID and IOTC_Connect_ByUID_Parallel will auto wake up device.
 *        Use this function before calling IOTC_Connect_ByUID and IOTC_Connect_ByUID_Parallel.
 *        Default value is disable.
 *        This Setup will reset to disable in IOTC_DeInitialize.
 *
 * \param nEnableAutoWakeUp[in] 0:disable, 1:enable.
 */
P2PAPI_API void IOTC_WakeUp_Setup_Auto_WakeUp(int32_t nEnableAutoWakeUp);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __IOTC_WAKEUP_H__
