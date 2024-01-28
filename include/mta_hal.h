/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**
* @file mta_hal.h
* @brief The mta_hal provides an interface to get/set Media Terminal Adapter features
*/


#ifndef __MTA_HAL_H__
#define __MTA_HAL_H__

#include <stdint.h>
#include <netinet/in.h>

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/
/**
* @defgroup mta_hal MTA HAL
*
* This module provides the function call prototypes and structure definitions used for the  MTA hardware abstraction layer.
*
* @defgroup MTA_HAL_TYPES  MTA HAL Data Types
* @ingroup  mta_hal
*
* @defgroup MTA_HAL_APIS   MTA HAL  APIs
* @ingroup  mta_hal
*
**/


/**
 * @addtogroup MTA_HAL_TYPES
 * @{
 */

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  UCHAR
#endif

#ifndef INT
#define INT   int
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif

#ifndef IPV4_ADDRESS_SIZE
#define  IPV4_ADDRESS_SIZE                          4
#endif

#ifndef MTA_HAL_SHORT_VALUE_LEN
#define  MTA_HAL_SHORT_VALUE_LEN   16
#endif

#ifndef MTA_HAL_LONG_VALUE_LEN
#define  MTA_HAL_LONG_VALUE_LEN   64
#endif

#ifndef ANSC_IPV4_ADDRESS
/*
TODO: Facilitate the transition from IPv4 to IPv6, addressing areas where integer-based IP operations are more efficient than array-based.
*/
#define  ANSC_IPV4_ADDRESS                                                                  \
         union                                                                              \
         {                                                                                  \
            unsigned char           Dot[IPV4_ADDRESS_SIZE];                                 \
            uint32_t                Value;                                                  \
         }
#endif

/* DECT */
/* 
 * TODO: DH Move platform/HAL specific definitions to hal.c or an included header, and rectify similar issues in other RDK-B vendor's code. 
 *
typedef enum
{
    SNMPA_REQ_USER_HANDLER,
    SNMPA_REQ_GET_VAL_BY_OID,
    SNMPA_REQ_GETNEXT_VAL_BY_OID,
    SNMPA_REQ_SET_STRING_BY_OID,
    SNMPA_REQ_SET_BYTE_BY_OID,
    SNMPA_REQ_SET_OID_BY_OID,
    SNMPA_REQ_SET_INT_BY_OID,
    SNMPA_REQ_SET_UINT_BY_OID,
    SNMPA_REQ_SET_SHORT_BY_OID,
    SNMPA_REQ_SET_USHORT_BY_OID,
    SNMPA_REQ_SET_IP_BY_OID,
    SNMPA_REQ_ENGINE_GET_MY_ID,
    SNMPA_REQ_ENGINE_GET_MY_BOOTS,
    SNMPA_REQ_ENGINE_GET_MY_TIME,
    SNMPA_REQ_TLV11_CONF,
    SNMPA_REQ_TLV64_CONF,
    SNMPA_REQ_SET_MY_ENGINE_INFO,
}  SnmpaIfRequest_e;
 */

/*
 * TODO: DH Reevaluate the necessity of defining platform-specific capabilities in the HAL header file.
 */
#define DECT_MAX_HANDSETS 5

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
/**
 * @brief Structure representing DECT (Digital Enhanced Cordless Telecommunications) module information for an MTA (Multimedia Terminal Adapter).
 *
 * This structure stores configuration and status information about the DECT module of an MTA, including registration status,
 * hardware and software versions, RFPI (Radio Fixed Part Identity), and authentication PIN. It's used for managing and monitoring
 * the DECT module associated with an MTA.
 * 
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_DECT
{
    ULONG RegisterDectHandset;    /**< Registration status of the DECT handset. Currently, these values are set to 0 in the CCSP code. */
    ULONG DeregisterDectHandset;  /**< Deregistration status of the DECT handset. Currently, these values are set to 0 in the CCSP code. */
    char HardwareVersion[64];     /**< DECT module hardware version. Provides the version information of the hardware. */
    char RFPI[64];                /**< RFPI (Radio Fixed Part Identity) value of the DECT module from the EEPROM. Unique identifier for the DECT base station. */
    char SoftwareVersion[64];     /**< DECT module software version. Provides the version information of the software. */
    char PIN[64];                 /**< Authentication PIN for base module (CMBS) <-> handset communication. Used for securing communications between devices. */
} MTAMGMT_MTA_DECT, *PMTAMGMT_MTA_DECT;

/**
 * @brief Structure to hold the details of registered or subscribed MTA handsets.
 * 
 * This structure is used to store information about the handsets associated with an MTA (Multimedia Terminal Adapter).
 * It includes details such as the instance number, status, last active time, name, firmware version, and operating and supported TNs.
 * 
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_HANDSETS_INFO
{
    ULONG InstanceNumber;                        /**< Instance number of the MTA Handset. Unique identifier for each handset. */
    BOOLEAN Status;                              /**< Status of the MTA Handset. Indicates if the handset is active or inactive. */
    char LastActiveTime[64];                     /**< Last Active Time of the MTA Handset. Records the last time the handset was active. */
    char HandsetName[64];                        /**< Handset Name. The name assigned to the handset. */
    char HandsetFirmware[64];                    /**< Handset Firmware. The firmware version is installed on the handset. */
    char OperatingTN[64];                        /**< Operating TN. Indicates the Telephone Number (TN) the handset is operating on. Currently, only TN1 is assigned to DECT phones. */
    char SupportedTN[64];                        /**< Supported TN. Indicates the Telephone Number (TN) supported by the handset. Currently, only TN1 is assigned to DECT phones. */
} MTAMGMT_MTA_HANDSETS_INFO, *PMTAMGMT_MTA_HANDSETS_INFO;

/**
 * @brief Structure representing DHCP information for an MTA (Multimedia Terminal Adapter).
 * 
 * This structure contains details about DHCP (Dynamic Host Configuration Protocol) information,
 * including IP addresses, subnet mask, gateway, DNS information, lease times, and other DHCP options.
 *
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_DHCP_INFO
{
    ANSC_IPV4_ADDRESS IPAddress;               /**< IP Address assigned to the MTA. */
    CHAR BootFileName[64];                     /**< Boot file name received from the DHCP server. */
    CHAR FQDN[64];                             /**< Fully Qualified Domain Name. */
    ANSC_IPV4_ADDRESS SubnetMask;              /**< Subnet mask for the IP address. */
    ANSC_IPV4_ADDRESS Gateway;                 /**< Default gateway IP address. */
    ULONG LeaseTimeRemaining;                  /**< Remaining lease time in seconds. */
    CHAR RebindTimeRemaining[64];              /**< Remaining time to rebind in seconds. */
    CHAR RenewTimeRemaining[64];               /**< Remaining time to renew in seconds. */
    ANSC_IPV4_ADDRESS PrimaryDNS;              /**< Primary DNS server IP address. */
    ANSC_IPV4_ADDRESS SecondaryDNS;            /**< Secondary DNS server IP address. */
    CHAR DHCPOption3[64];                      /**< Custom DHCP Option 3. */
    CHAR DHCPOption6[64];                      /**< Custom DHCP Option 6. */
    CHAR DHCPOption7[64];                      /**< Custom DHCP Option 7. */
    CHAR DHCPOption8[64];                      /**< Custom DHCP Option 8. */
    CHAR PCVersion[64];                        /**< Version of the PC. */
    CHAR MACAddress[64];                       /**< MAC address of the MTA. */
    ANSC_IPV4_ADDRESS PrimaryDHCPServer;       /**< Primary DHCP server IP address. */
    ANSC_IPV4_ADDRESS SecondaryDHCPServer;     /**< Secondary DHCP server IP address. */
} MTAMGMT_MTA_DHCP_INFO, *PMTAMGMT_MTA_DHCP_INFO;

/**
 * @brief Structure representing DHCPv6 information for an MTA (Multimedia Terminal Adapter).
 * 
 * This structure contains details about DHCPv6 (Dynamic Host Configuration Protocol for IPv6) information,
 * including IPv6 addresses, prefixes, gateways, DNS information, lease times, and other DHCP options.
 *
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_DHCPv6_INFO
{
    CHAR IPV6Address[INET6_ADDRSTRLEN];                 /**< IPv6 Address assigned to the MTA. */
    CHAR BootFileName[64];                             /**< Boot file name received from the DHCPv6 server. */
    CHAR FQDN[64];                                     /**< Fully Qualified Domain Name. */
    CHAR Prefix[INET6_ADDRSTRLEN];                     /**< Network prefix associated with the IPv6 address. */
    CHAR Gateway[INET6_ADDRSTRLEN];                    /**< Default gateway IPv6 address. */
    ULONG LeaseTimeRemaining;                          /**< Remaining lease time in seconds. */
    CHAR RebindTimeRemaining[64];                      /**< Remaining time to rebind in seconds*/
    CHAR RenewTimeRemaining[64];                       /**< Remaining time to renew in seconds */
    CHAR PrimaryDNS[INET6_ADDRSTRLEN];                 /**< Primary DNS server IPv6 address. */
    CHAR SecondaryDNS[INET6_ADDRSTRLEN];               /**< Secondary DNS server IPv6 address. */
    CHAR DHCPOption3[64];                              /**< Custom DHCP Option 3. */
    CHAR DHCPOption6[64];                              /**< Custom DHCP Option 6. */
    CHAR DHCPOption7[64];                              /**< Custom DHCP Option 7. */
    CHAR DHCPOption8[64];                              /**< Custom DHCP Option 8. */
    CHAR PCVersion[64];                                /**< Version of the PC. */
    CHAR MACAddress[64];                               /**< The telephony IPv6 MAC address for this device. */
    CHAR PrimaryDHCPv6Server[INET6_ADDRSTRLEN];        /**< Primary DHCPv6 server IPv6 address. */
    CHAR SecondaryDHCPv6Server[INET6_ADDRSTRLEN];      /**< Secondary DHCPv6 server IPv6 address. */
} MTAMGMT_MTA_DHCPv6_INFO, *PMTAMGMT_MTA_DHCPv6_INFO;

/**
 * @brief Structure representing the service flow for an MTA (Multimedia Terminal Adapter).
 *
 * This structure contains detailed information about the service flow, including parameters for QoS (Quality of Service),
 * bandwidth allocation, traffic scheduling, and more. It is used to define the characteristics of a specific service flow
 * for an MTA, allowing for management and configuration of network traffic.
 *
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_SERVICE_FLOW
{
    ULONG SFID;                              /**< Service Flow ID. Unique identifier for the service flow. */
    CHAR ServiceClassName[256];              /**< Name of the service class. Used to identify the type of service the flow is associated with. */
    CHAR Direction[16];                      /**< Direction of the service flow. Can be 'Upstream' or 'Downstream'. */
    ULONG ScheduleType;                      /**< Schedule Type. Defines the scheduling mechanism used for the service flow. */
    BOOLEAN DefaultFlow;                     /**< Indicates if this is the default service flow. */
    ULONG NomGrantInterval;                  /**< Nominal Grant Interval. Specifies the nominal interval between grants. */
    ULONG UnsolicitGrantSize;                /**< Unsolicited Grant Size. The size of grants issued without a request. */
    ULONG TolGrantJitter;                    /**< Tolerated Grant Jitter. The maximum acceptable jitter in grant timing. */
    ULONG NomPollInterval;                   /**< Nominal Polling Interval. Specifies the nominal interval between polls. */
    ULONG MinReservedPkt;                    /**< Minimum Reserved Packets. The minimum packet size is reserved for the flow. */
    ULONG MaxTrafficRate;                    /**< Maximum Traffic Rate. The peak traffic rate allowed for the flow. */
    ULONG MinReservedRate;                   /**< Minimum Reserved Rate. The minimum data rate is reserved for the flow. */
    ULONG MaxTrafficBurst;                   /**< Maximum Traffic Burst. The maximum size of a burst of traffic allowed for the flow. */
    CHAR TrafficType[64];                    /**< Type of traffic. Can be 'SIP', 'RTP', or other types depending on the application. */
    ULONG NumberOfPackets;                   /**< Packet count. Number of packets that have been processed by this service flow. */
} MTAMGMT_MTA_SERVICE_FLOW, *PMTAMGMT_MTA_SERVICE_FLOW;

/**
 * @brief Structure representing call details for an MTA (Multimedia Terminal Adapter).
 *
 * This structure stores comprehensive information about individual calls, including codec details, call timings,
 * signal quality metrics, jitter buffer configurations, and packet statistics, among other parameters.
 * It provides a detailed snapshot of both the local and remote parameters of a call, aiding in quality analysis and troubleshooting.
 */
typedef struct _MTAMGMT_MTA_CALLS
{
    CHAR Codec[64];                                    /**< Local codec used for the call. */
    CHAR RemoteCodec[64];                              /**< Remote codec used for the call. */
    CHAR CallStartTime[64];                            /**< Start time of the call. */
    CHAR CallEndTime[64];                              /**< End time of the call. */
    CHAR CWErrorRate[MTA_HAL_SHORT_VALUE_LEN];         /**< Code Word Error Rate. The ratio of useful signal to background noise. */
    CHAR PktLossConcealment[MTA_HAL_SHORT_VALUE_LEN];  /**< Packet Loss Concealment. The ratio of lost packets to total expected packets. */
    BOOLEAN JitterBufferAdaptive;                      /**< Indicates if Jitter Buffer Adaptive (JBA) is used. */
    BOOLEAN Originator;                                /**< Indicates if the local side is the originating side of the call. */
    ANSC_IPV4_ADDRESS RemoteIPAddress;                 /**< Remote IP address. */
    ULONG CallDuration;                                /**< Duration of the call in minutes. */
    CHAR CWErrors[MTA_HAL_SHORT_VALUE_LEN];            /**< Code Word Errors on this channel. */
    CHAR SNR[MTA_HAL_SHORT_VALUE_LEN];                 /**< Signal to Noise Ratio. */
    CHAR MicroReflections[MTA_HAL_SHORT_VALUE_LEN];    /**< Micro Reflections. Return loss measurement. */
    CHAR DownstreamPower[MTA_HAL_SHORT_VALUE_LEN];     /**< Downstream power in dBmV. */
    CHAR UpstreamPower[MTA_HAL_SHORT_VALUE_LEN];       /**< Upstream power in dBmV. */
    CHAR EQIAverage[MTA_HAL_SHORT_VALUE_LEN];          /**< EQI Average. */
    CHAR EQIMinimum[MTA_HAL_SHORT_VALUE_LEN];          /**< EQI Minimum. */
    CHAR EQIMaximum[MTA_HAL_SHORT_VALUE_LEN];          /**< EQI Maximum. */
    CHAR EQIInstantaneous[MTA_HAL_SHORT_VALUE_LEN];    /**< EQI Instantaneous. */
    CHAR MOS_LQ[MTA_HAL_SHORT_VALUE_LEN];              /**< Mean Opinion Score of Listening Quality. Scale: 10-50. */
    CHAR MOS_CQ[MTA_HAL_SHORT_VALUE_LEN];              /**< Mean Opinion Score of Conversational Quality. Scale: 10-50. */
    CHAR EchoReturnLoss[MTA_HAL_SHORT_VALUE_LEN];      /**< Residual Echo Return Loss, in dB. */
    CHAR SignalLevel[MTA_HAL_SHORT_VALUE_LEN];         /**< Voice signal relative level, in dB. */
    CHAR NoiseLevel[MTA_HAL_SHORT_VALUE_LEN];          /**< Noise relative level, in dB. */
    CHAR LossRate[MTA_HAL_SHORT_VALUE_LEN];            /**< Fraction of RTP data packet loss * 256. */
    CHAR DiscardRate[MTA_HAL_SHORT_VALUE_LEN];         /**< Fraction of RTP data packet discarded * 256. */
    CHAR BurstDensity[MTA_HAL_SHORT_VALUE_LEN];        /**< Fraction of bursting data packet * 256. */
    CHAR GapDensity[MTA_HAL_SHORT_VALUE_LEN];          /**< Fraction of packets within inter-burst gap * 256. */
    CHAR BurstDuration[MTA_HAL_SHORT_VALUE_LEN];       /**< Mean duration of bursts, in milliseconds. */
    CHAR GapDuration[MTA_HAL_SHORT_VALUE_LEN];         /**< Mean duration of gaps, in milliseconds. */
    CHAR RoundTripDelay[MTA_HAL_SHORT_VALUE_LEN];      /**< Most recent measured RTD, in milliseconds. */
    CHAR Gmin[MTA_HAL_SHORT_VALUE_LEN];                /**< Local gap threshold. */
    CHAR RFactor[MTA_HAL_SHORT_VALUE_LEN];             /**< Voice quality evaluation for this RTP session. */
    CHAR ExternalRFactor[MTA_HAL_SHORT_VALUE_LEN];     /**< Voice quality evaluation for a segment on the network external to this RTP session. */
    CHAR JitterBufRate[MTA_HAL_SHORT_VALUE_LEN];       /**< Adjustment rate of the jitter buffer, in milliseconds. */
    CHAR JBNominalDelay[MTA_HAL_SHORT_VALUE_LEN];      /**< Nominal jitter buffer length, in milliseconds. */
    CHAR JBMaxDelay[MTA_HAL_SHORT_VALUE_LEN];          /**< Maximum jitter buffer length, in milliseconds. */
    CHAR JBAbsMaxDelay[MTA_HAL_SHORT_VALUE_LEN];       /**< Absolute maximum delay, in milliseconds. */
    CHAR TxPackets[MTA_HAL_SHORT_VALUE_LEN];           /**< Count of transmitted packets. */
    CHAR TxOctets[MTA_HAL_SHORT_VALUE_LEN];            /**< Count of transmitted octet packets. */
    CHAR RxPackets[MTA_HAL_SHORT_VALUE_LEN];           /**< Count of received packets. */
    CHAR RxOctets[MTA_HAL_SHORT_VALUE_LEN];            /**< Count of received octet packets. */
    CHAR PacketLoss[MTA_HAL_SHORT_VALUE_LEN];          /**< Count of lost packets. */
    CHAR IntervalJitter[MTA_HAL_SHORT_VALUE_LEN];      /**< Stat variance of packet interarrival time, in milliseconds. */
    CHAR RemoteIntervalJitter[MTA_HAL_SHORT_VALUE_LEN];        /**< Interval Jitter at the remote side. Statistical variance of packet inter-arrival time in milliseconds. */
    CHAR RemoteMOS_LQ[MTA_HAL_SHORT_VALUE_LEN];                /**< Mean Opinion Score (Listening Quality) at the remote side. A measure of voice call quality as experienced by the listener. */
    CHAR RemoteMOS_CQ[MTA_HAL_SHORT_VALUE_LEN];                /**< Mean Opinion Score (Conversational Quality) at the remote side. A measure of voice call quality in conversation. */
    CHAR RemoteEchoReturnLoss[MTA_HAL_SHORT_VALUE_LEN];        /**< Echo Return Loss at the remote side. Measures the amount of echo on the line. */
    CHAR RemoteSignalLevel[MTA_HAL_SHORT_VALUE_LEN];           /**< Signal Level at the remote side. Measures the strength of the signal. */
    CHAR RemoteNoiseLevel[MTA_HAL_SHORT_VALUE_LEN];            /**< Noise Level at the remote side. Measures the level of background noise. */
    CHAR RemoteLossRate[MTA_HAL_SHORT_VALUE_LEN];              /**< Loss Rate at the remote side. Fraction of RTP data packet loss. */
    CHAR RemotePktLossConcealment[MTA_HAL_SHORT_VALUE_LEN];    /**< Packet Loss Concealment at the remote side. The ratio of lost packets to total expected packets. */
    CHAR RemoteDiscardRate[MTA_HAL_SHORT_VALUE_LEN];           /**< Discard Rate at the remote side. Fraction of RTP data packets discarded during transmission. */
    CHAR RemoteBurstDensity[MTA_HAL_SHORT_VALUE_LEN];          /**< Burst Density at the remote side. Fraction of packets in a burst compared to total packets. */
    CHAR RemoteGapDensity[MTA_HAL_SHORT_VALUE_LEN];            /**< Gap Density at the remote side. Fraction of packets within inter-burst gaps. */
    CHAR RemoteBurstDuration[MTA_HAL_SHORT_VALUE_LEN];         /**< Burst Duration at the remote side. The average duration of packet bursts is in milliseconds. */
    CHAR RemoteGapDuration[MTA_HAL_SHORT_VALUE_LEN];           /**< Gap Duration at the remote side. The average duration of gaps between packet bursts in milliseconds. */
    CHAR RemoteRoundTripDelay[MTA_HAL_SHORT_VALUE_LEN];       /**< Round-trip delay at the remote side. Most recent measured round-trip time in milliseconds. */
    CHAR RemoteGmin[MTA_HAL_SHORT_VALUE_LEN];                 /**< Gmin at the remote side. Specifies the gap threshold used in burst calculations. */
    CHAR RemoteRFactor[MTA_HAL_SHORT_VALUE_LEN];              /**< R-Factor at the remote side. Voice quality evaluation metric for the remote RTP session. */
    CHAR RemoteExternalRFactor[MTA_HAL_SHORT_VALUE_LEN];      /**< External R-Factor at the remote side. Voice quality evaluation for segments on the network external to the remote RTP session. */
    BOOLEAN RemoteJitterBufferAdaptive;                       /**< Indicates if the remote side is using an adaptive jitter buffer. */
    CHAR RemoteJitterBufRate[MTA_HAL_SHORT_VALUE_LEN];        /**< Adjustment rate of the remote jitter buffer in milliseconds. */
    CHAR RemoteJBNominalDelay[MTA_HAL_SHORT_VALUE_LEN];       /**< Nominal jitter buffer length at the remote side in milliseconds. */
    CHAR RemoteJBMaxDelay[MTA_HAL_SHORT_VALUE_LEN];           /**< Maximum jitter buffer length at the remote side in milliseconds. */
    CHAR RemoteJBAbsMaxDelay[MTA_HAL_SHORT_VALUE_LEN];        /**< Absolute maximum delay at the remote side in milliseconds. */
} MTAMGMT_MTA_CALLS, *PMTAMGMT_MTA_CALLS

/**
 * @brief Structure representing line table information for an MTA (Multimedia Terminal Adapter).
 *
 * This structure stores information about a specific line on an MTA, including its status, test results, call information,
 * and other related details. It's used to monitor and manage the state and configuration of MTA lines.
 *
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_LINETABLE_INFO
{
    ULONG InstanceNumber;                         /**< Instance number of the line. */
    ULONG LineNumber;                             /**< Line number. */
    ULONG Status;                                 /**< Line status. 1 = OnHook; 2 = OffHook. */
    CHAR HazardousPotential[128];                 /**< Result of the HEMF (High Electric and Magnetic Fields) test. E.g., 'Passed', 'Not Started'. */
    CHAR ForeignEMF[128];                         /**< Result of the FEMF (Foreign Electromagnetic Fields) test. E.g., 'Passed', 'Not Started'. */
    CHAR ResistiveFaults[128];                    /**< Status of resistive faults test. E.g., 'Not Started'. */
    CHAR ReceiverOffHook[128];                    /**< Status of the receiver off-hook test. E.g., 'Not Started'. */
    CHAR RingerEquivalency[64];                   /**< Ringer equivalency number. Typically indicates the load a ringer places on the line. */
    CHAR CAName[64];                              /**< Circuit Assurance (CA) name associated with this line. */
    ULONG CAPort;                                 /**< Circuit Assurance (CA) port number. */
    ULONG MWD;                                    /**< Message Waiting Indicator. Indicates the presence of a voicemail or similar message. */
    ULONG CallsNumber;                            /**< Number of calls associated with this line. */
    PMTAMGMT_MTA_CALLS pCalls;                    /**< Pointer to calls data. */
    ULONG CallsUpdateTime;                        /**< Timestamp of the last update to calls information. */
    ULONG OverCurrentFault;                       /**< Over-current fault status. 1 = Normal, 2 = Fault. */
} MTAMGMT_MTA_LINETABLE_INFO, *PMTAMGMT_MTA_LINETABLE_INFO;

/**
 * @brief Structure representing the call processing information for an MTA (Multimedia Terminal Adapter).
 *
 * This structure holds information about the call processing state, line card (LC) state, and loop current status of the MTA.
 * It's used to monitor and manage the call processing behavior and line card conditions of an MTA.
 * 
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_CALLP
{
    CHAR LCState[64];                /**< Line Card State. Indicates the current state of the line card. Possible values: 'In Use', 'Idle', 'Out of Service'. */
    CHAR CallPState[64];             /**< Call Processing State. Represents the current state of call processing. Possible values: 'In Service', 'OOS (Out of Service)'. */
    CHAR LoopCurrent[64];            /**< Loop Current Status. Represents the status of the loop current. Possible values: 'Normal', 'Boosted'. */
} MTAMGMT_MTA_CALLP, *PMTAMGMT_MTA_CALLP;

/**
 * @brief Structure representing the DSX (Digital Signal Cross-connect) log entries for an MTA (Multimedia Terminal Adapter).
 *
 * This structure stores log entries related to DSX operations, including time of the log, description of the event,
 * and other vendor-specific identifiers and levels. It's used for monitoring and debugging DSX operations.
 * 
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_DSXLOG
{
    CHAR Time[64];              /**< Time of the log entry. */
    CHAR Description[128];      /**< Description of the log entry. Provides details about the DSX operation or event. */
    ULONG ID;                   /**< Identifier for the log entry. A unique value is provided by the vendor to identify the log entry. */
    ULONG Level;                /**< Log level of the entry. Specifies the severity or importance of the log.  */
} MTAMGMT_MTA_DSXLOG, *PMTAMGMT_MTA_DSXLOG;

/**
 * @brief Structure representing the full log entries for an MTA (Multimedia Terminal Adapter).
 *
 * This structure holds comprehensive information about log entries, including an index, event identifier,
 * event level, timestamp, and a detailed description of the event. It's designed for in-depth monitoring and
 * analysis of events in an MTA environment.
 * 
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_MTALOG_FULL
{
    ULONG Index;                  /**< Index of the log entry. Unique identifier within the log. Example values: 1, 2. */
    ULONG EventID;                /**< Identifier of the event. A unique value to identify the type of event. Example values: 1, 2. */
    CHAR EventLevel[64];          /**< Level of the event. Represents the severity or importance of the event. Example values: "1", "2". */
    CHAR Time[64];                /**< Timestamp of the log entry. Indicates when the event occurred. Example format: "1998-05-14". */
    CHAR* pDescription;           /**< Pointer to the description of the log entry. Provides detailed information about the event. Example values: "this is a log for matLog1", "this is a log for matLog2". */
} MTAMGMT_MTA_MTALOG_FULL, *PMTAMGMT_MTA_MTALOG_FULL;

/**
 * @brief Structure representing battery information for an MTA (Multimedia Terminal Adapter).
 *
 * This structure stores detailed information about the battery associated with an MTA, including model number,
 * serial number, part number, and charger firmware revision. It's used to identify and manage the battery
 * component of an MTA.
 *
 * @note Ensure that any value specified does not exceed the buffer size limit defined.
 */
typedef struct _MTAMGMT_MTA_BATTERY_INFO
{
    CHAR ModelNumber[32];                  /**< Model number of the battery. Identifies the battery model. */
    CHAR SerialNumber[32];                 /**< Serial number of the battery. Unique identifier for the battery. */
    CHAR PartNumber[32];                   /**< Part number of the battery. Identifies the part specification. */
    CHAR ChargerFirmwareRevision[32];      /**< Charger firmware revision. Identifies the firmware version of the battery charger. */
} MTAMGMT_MTA_BATTERY_INFO, *PMTAMGMT_MTA_BATTERY_INFO;


#define MTA_LINENUMBER 8

/**
 * @brief Represents the MTA Operational Status.
 *
 * This enumeration is used to distinguish between different MTA Operational status/
 * Config file status/ DHCP status/ line register status.
 */
typedef  enum {
	MTA_INIT=0,         /**< MTA provisioning init */
	MTA_START=1,        /**< MTA provisioning is in progress */
	MTA_COMPLETE=2,     /**< MTA is operational */
	MTA_ERROR=3,        /**< MTA provisioning failed */
	MTA_REJECTED=4      /**< Rejected */
} MTAMGMT_MTA_STATUS;

/**
 * @brief Represents the MTA Provisioning Status.
 *
 * This enumeration is used to distinguish between different MTA Provisioning statuses.
 */
typedef enum{
        MTA_PROVISIONED=0,      /**< MTA Provisioned. If status is MTA_PROVISIONED then a valid MTA IP should be obtained when Device.DeviceInfo.X_COMCAST-COM_MTA_IP is queried. */
        MTA_NON_PROVISIONED=1   /**< MTA Non Provisioned. If status is MTA_NON_PROVISIONED, then MTA IP should be 0.0.0.0. */
} MTAMGMT_MTA_PROVISION_STATUS;
/**
 * @}
 */

/**
 * @addtogroup MTA_HAL_APIS
 * @{
 */


/**********************************************************************************
 *
 *  MTA Subsystem level function prototypes
 *
**********************************************************************************/

/*
 * TODO: Extend returns codes for all functions and change to enums
 * 1. Extend the return codes by listing out the possible reasons for failure, to improve the interface in the future. This was reported during the review for header file migration to open-source GitHub.
 *
 * TODO: Add return cases for battery functions with enums
 * 2. Add return error cases for battery-related functions with and without battery present.
 *
 * TODO: Split header files based on API and re-include to not affect clients
 * 3. Plan to split the header files based on the purpose of the APIs, for example, DHCP, battery, etc.
*/

/**
* @brief Retrieves the global information for all shared DBs and makes them accessible locally.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*

*
*/
INT   mta_hal_InitDB(void);

/**
* @brief Retrieve all the relevant DHCP info for MTA.
* @param[out] pInfo pointer to PMTAMGMT_MTA_DHCP_INFO structure that will hold all DHCP info for MTA, to be returned.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_GetDHCPInfo(PMTAMGMT_MTA_DHCP_INFO pInfo);

/**
* @brief Retrieve all the relevant DHCPv6 info for MTA.
* @param[out] pInfo pointer to PMTAMGMT_MTA_DHCPv6_INFO that will hold all DHCP info for MTA, to be returned.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/

INT mta_hal_GetDHCPV6Info(PMTAMGMT_MTA_DHCPv6_INFO pInfo);

/**
* @brief Get the number of entries in the line table.
*
* @return ULONG - number of entries
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
ULONG mta_hal_LineTableGetNumberOfEntries(void);

/**
* @brief Get an entry of the line table at the given index
* @param[in] Index - index to the table entry. The value ranges from 0 to (2^32)-1.
* @param[out] pEntry - Structure variable containing MTA Line table entry info, to be returned.
*
* @return The status of the operation
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT   mta_hal_LineTableGetEntry(ULONG Index, PMTAMGMT_MTA_LINETABLE_INFO pEntry);

/**
* @brief Trigger GR909 Diagnostics
* @param[in] Index - it is an unsigned long integer that provides a line number to perform the GR909 diagnostics on. The value ranges from 0 to (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT   mta_hal_TriggerDiagnostics(ULONG Index);

/**
* @brief Get all the service flow info
* @param[out] Count - it is an unsigned long integer that provides the number of service flow entries, to be returned. The value ranges from 0 to (2^32)-1.
* @param[out] ppCfg - Pointer to structure containing service flow info, to be returned.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT   mta_hal_GetServiceFlow(ULONG* Count, PMTAMGMT_MTA_SERVICE_FLOW *ppCfg);

/**
* @brief Get info on if DECT(Digital Enhanced Cordless Telecommunications) is enabled
* @param[out] pBool - It is a boolean pointer of 1 byte size, that stores the value for DECT enable, to be returned.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT   mta_hal_DectGetEnable(BOOLEAN *pBool);

/**
* @brief Set DECT according to the boolean value passed
* @param[in] bBool - It is a boolean variable of 1-byte size, that contains a value for DECT enabled or not, to be set.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_DectSetEnable(BOOLEAN bBool);

/**
* @brief Get DECT registration mode, whether enabled or not.
* @param[out] pBool - It is a boolean pointer of 1 byte size, that stores the value of DECT enabled or not, to be returned.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_DectGetRegistrationMode(BOOLEAN* pBool);

/**
* @brief Set DECT registration mode according to the boolean value passed.
* @param[in] bBool - It is a boolean pointer of 1-byte size, enabled or not.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_DectSetRegistrationMode(BOOLEAN bBool);

/**
* @brief Deregister DECT Handset
* @param[in] uValue - unsigned long pointer value for deregister DECT handset. The value ranges from 0 to 4294967295. It is a vendor-specific value.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_DectDeregisterDectHandset(ULONG uValue);

/**
* @brief  Get DECT info
* @param[out] pDect - Info of DECT. pDect is a pointer to structure PMTAMGMT_MTA_DECT.
*                                        \n The structure members are defined as below:
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_GetDect(PMTAMGMT_MTA_DECT pDect);

/**
* @brief get DECT PIN
* @param[out] pPINString - It is 128 bytes of character pointer that provides PIN value.
*                          \n It is a zero-terminated string.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_GetDectPIN(char* pPINString);

/**
* @brief Set DECT PIN using the provided PIN string.
* @param[in] pPINString - It is a 128 bytes character pointer that provides DECT PIN value.
*                         \n It is a zero-terminated string.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_SetDectPIN(char* pPINString);

/**
* @brief Get MTA handset info
* @param[in] pulCount  - Unsigned long integer pointer that provides handset number. The value ranges from 0 to (2^32)-1.
* @param[out] ppHandsets - Pointer to ppHandsets structure that contains Info of MTA handset.
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_GetHandsets(ULONG* pulCount, PMTAMGMT_MTA_HANDSETS_INFO* ppHandsets);

/**
* @brief Retrieve all call info for the given instance number of LineTable
* @param[in] InstanceNumber - Unsigned long integer that provides LineTable's instance number. The valid range is 0 to (2^32)-1.
* @param[out] Count - Unsigned long integer pointer that provides number of entries(calls) for the call info array, to be returned. The valid range is 0 to (2^32)-1.
* @param[out] ppCfg - Array with call info, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT   mta_hal_GetCalls(ULONG InstanceNumber, ULONG *Count, PMTAMGMT_MTA_CALLS *ppCfg);

/**
* @brief Retrieve the Call processing status information for the line number
* @param[in]  LineNumber - Unsigned long integer that provides Line number for which to retrieve info on Call processing status.
* @param[out]  pCallp - Call processing information, to be returned.

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT   mta_hal_GetCALLP(ULONG LineNumber, PMTAMGMT_MTA_CALLP pCallp);

/**
* @brief Retrieve all DSX log entries
* @param[out] Count - Unsigned long integer pointer to store the number of entries in the log. The value ranges from 0 to (2^32)-1.
* @param[out] ppDSXLog - array of DSX log entries, to be returned.

* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT   mta_hal_GetDSXLogs(ULONG *Count, PMTAMGMT_MTA_DSXLOG *ppDSXLog);

/**
* @brief Get DSX log enable status
* @param[out] pBool - It is a boolean pointer of 1 byte size, pointing to the value of enable, to be returned.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT   mta_hal_GetDSXLogEnable(BOOLEAN *pBool);

/**
* @brief Set value of DSX log enable to the value passed.
* @param[in] Bool - It is a boolean variable with 1 byte size, containing the value to set DSX log enable to.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT   mta_hal_SetDSXLogEnable(BOOLEAN Bool);


/**
* @brief Clear DSX logs based on the value passed.
* @param[in] Bool - It is a boolean variable with 1 byte size, containing the value indicating whether clearDSXlog should enabled or disabled.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_ClearDSXLog(BOOLEAN Bool) ;

/**
* @brief Get the value of if CallSignalling log is enabled
* @param[out] pBool - It is a boolean pointer with 1 byte size, pointing to the value of enable, to be returned.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/

INT mta_hal_GetCallSignallingLogEnable(BOOLEAN *pBool) ;

/**
* @brief Set value of CallSignalling enable to the value passed.
* @param[in] Bool - It is a boolean variable with 1 byte size, holding the value to set CallSignalling log enable to.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/

INT mta_hal_SetCallSignallingLogEnable(BOOLEAN Bool) ;


/**
* @brief Clear CallSignalling log based on the value passed.
* @param[in] Bool - It is a boolean variable with 1 byte size, containing the value indicating whether clear CallSignalling log should enabled or disabled.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*
*/

INT mta_hal_ClearCallSignallingLog(BOOLEAN Bool) ;

/**
* @brief Get all log entries from the MTA Log
* @param[out] Count - Unsigned long integer pointer that provides number of entries in the log, to be returned. The range is 0 to the (2^32)-1.
* @param[out] ppCfg - array of log entries, to be returned.

* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_GetMtaLog(ULONG *Count, PMTAMGMT_MTA_MTALOG_FULL *ppCfg);

/**
* @brief Check to see if the battery is installed
* @param[out] Val - It is a boolean pointer with 1 byte size, which holds the value to be returned.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetInstalled(BOOLEAN* Val);

/**
* @brief Get the total capacity of the battery
* @param[out] Val - Pointer to variable that stores the capacity in mAVHour. It is an unsigned long integer pointer with 4 bytes size. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetTotalCapacity(ULONG* Val);

/**
* @brief Retrieve the actual capacity of the battery
* @param[out] Val - Pointer to variable that stores the capacity in mAVHour. It is an unsigned long integer pointer with 4 bytes size. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetActualCapacity(ULONG* Val);

/**
* @brief Retrieve the current charge remaining in the battery
* @param[out] Val - Pointer to variable that stores the capacity/remaining charge in mAVHour. It is an unsigned long integer pointer with 4 bytes size. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetRemainingCharge(ULONG* Val);

/**
* @brief Get estimated battery remaining time if current usage continues
* @param[out] Val -  It is an unsigned long integer pointer with 4 bytes size. Remaining time in minutes, to be returned. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetRemainingTime(ULONG* Val);

/**
* @brief Get max number of cycles the battery can be charge cycled
* @param[out] Val -  It is an unsigned long integer pointer with 4 bytes size which holds the max number of cycles, to be returned. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetNumberofCycles(ULONG* Val);

/**
* @brief Get power status of MTA
* @param[out] Val - It is a character pointer which stores the battery power status, to be returned. Possible values are of "AC", "Battery", or "Unknown"
*                   \n It is a zero-terminated string.
* @param[out] len - It is an unsigned long integer pointer of 4 bytes size which holds the string length, to be returned. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetPowerStatus(CHAR *Val, ULONG *len);

/**
* @brief Get the battery condition
* @param[out] Val - It is a character pointer which stores the battery condition, to be returned. Possible values are "Good" or "Bad".
*                   \n It is a zero-terminated string.
* @param[in] len - It is an unsigned long integer pointer of 4 bytes size, string length, to be returned. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetCondition(CHAR *Val, ULONG *len);

/**
* @brief Get the battery status
* @param[out] Val - It is a character pointer that stores the battery status, to be returned. The values are: "Missing", "Idle", "Charging",
*                   \n "Discharging", or "Unknown".
*                   \n It is a zero-terminated string.
* @param[out] len - It is an unsigned long integer pointer of 4 bytes size, string length, to be returned. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetStatus(CHAR* Val, ULONG *len);

/**
* @brief Get the battery life status
* @param[out] Val - It is a character pointer which stores the battery life status, to be returned. The values are: "Need Replacement", or "Good".
*                   \n It is a zero-terminated string.
* @param[in] len - It is an unsigned long integer pointer of 4 bytes size, string length, to be returned. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetLife(CHAR* Val, ULONG *len);


/**
* @brief Get the battery info
* @param[out] pInfo - Structure variable of type PMTAMGMT_MTA_BATTERY_INFO containing the battery info, to be returned

* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_BatteryGetInfo(PMTAMGMT_MTA_BATTERY_INFO pInfo);

/**
* @brief Get the battery Power Saving Mode Status
* @param[out] pValue- It is an unsigned long integer pointer of 4 bytes size which contains the battery Power Saving Mode Status. Values of 1 for Enabled, 2 for Disabled. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_BatteryGetPowerSavingModeStatus(ULONG *pValue);

/**
* @brief Get the reset count of MTA
* @param[out] resetcnt- It is an unsigned long integer pointer of 4 bytes size, that gives the reset count of MTA. The range is 0 to the (2^32)-1. Sample value: 4.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/

INT mta_hal_Get_MTAResetCount(ULONG *resetcnt);

/**
* @brief Get the reset count of MTA Lines
* @param[out] resetcnt- It is an unsigned long integer pointer of 4 bytes size, that gives the reset count of MTA Lines. The range is 0 to the (2^32)-1. The value is 5.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/

INT mta_hal_Get_LineResetCount(ULONG *resetcnt);

/**
* @brief clear the VQM stats per line
* @param[in] InstanceNumber - It is an unsigned long integer pointer of 4 bytes size, that gives the instance number. The range is 0 to the (2^32)-1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_ClearCalls(ULONG InstanceNumber);

/**
* @brief Get the DHCP status for MTA
* @param[out] output_pIpv4status - ipv4 dhcp status from MTAMGMT_MTA_STATUS enumeration.
* @param[out] output_pIpv6status - ipv6 dhcp status from MTAMGMT_MTA_STATUS enumeration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_getDhcpStatus(MTAMGMT_MTA_STATUS *output_pIpv4status, MTAMGMT_MTA_STATUS *output_pIpv6status);

/**
* @brief Get the MTA config file status.
* @param[out] poutput_status - MTA config file status from MTAMGMT_MTA_STATUS enumeration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_getConfigFileStatus(MTAMGMT_MTA_STATUS *poutput_status);

/**
* @brief Get the register status for all lines
* @param[out] output_status_array - return array buffer for all line register status from MTAMGMT_MTA_STATUS enumeration.
* @param[in] array_size - It is an integer variable with 4 bytes size, buffer size (total line number).
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_getLineRegisterStatus(MTAMGMT_MTA_STATUS *output_status_array, int array_size);

/**
* @brief Set boolean value passed to reset MTA device.
* @param[in] bResetValue - boolean value of 1 byte size, to reset the device.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_devResetNow(BOOLEAN bResetValue);

/**
* @brief Get the operational status of MTA
* @param[out] operationalStatus - Return buffer for operational status from MTAMGMT_MTA_STATUS enumeration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_getMtaOperationalStatus(MTAMGMT_MTA_STATUS *operationalStatus);

/**
* @brief Get the provisional status of MTA
* @param[out] provisionStatus - return buffer for provision status from MTAMGMT_MTA_PROVISION_STATUS enumeration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
INT mta_hal_getMtaProvisioningStatus(MTAMGMT_MTA_PROVISION_STATUS *provisionStatus);

#define MTA_DHCPOPTION122SUBOPTION1_MAX          4
#define MTA_DHCPOPTION122SUBOPTION2_MAX          4
#define MTA_DHCPOPTION122CCCV6DSSID1_MAX         32
#define MTA_DHCPOPTION122CCCV6DSSID2_MAX         32

/**
 * @brief Represents the MTA Provisioning IP Modes.
 *
 * This enumeration is used to distinguish between different MTA Provisioning IP Modes.
 */

typedef  enum {
   MTA_IPV4=0,          /**<  IPv4 mode */
   MTA_IPV6=1,          /**<  IPv6 mode */
   MTA_DUAL_STACK=2,    /**<  Dual stack mode */
} MTAMGMT_MTA_PROV_IP_MODE; // MTAMGMT_PROVISIONING_PARAMS.MtaIPMode

/**
 * @brief Structure to hold all the provisioning parameters for MTA.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */

typedef struct _MTAMGMT_PROVISIONING_PARAMS
{

INT  MtaIPMode;
INT  DhcpOption2171CccV6DssID1Len;                                      /**<  Length of DhcpOption2171CccV6DssID1 */
INT  DhcpOption2171CccV6DssID2Len;                                      /**<  Length of DhcpOption2171CccV6DssID2 */
CHAR DhcpOption122Suboption1[MTA_DHCPOPTION122SUBOPTION1_MAX+1];        /**<  4 byte hex value ie. FFFFFFFF = "255.255.255.255". IPv4 addresses MUST be encoded as 4 binary octets in network  byte-order (high order byte first). */
CHAR DhcpOption122Suboption2[MTA_DHCPOPTION122SUBOPTION2_MAX+1];        /**<  4 byte hex value ie. FFFFFFFF = "255.255.255.255" */
CHAR DhcpOption2171CccV6DssID1[MTA_DHCPOPTION122CCCV6DSSID1_MAX+1];     /**<  32 byte hex value */
CHAR DhcpOption2171CccV6DssID2[MTA_DHCPOPTION122CCCV6DSSID2_MAX+1];     /**<  32 byte hex value */
}
MTAMGMT_PROVISIONING_PARAMS, *PMTAMGMT_MTA_PROVISIONING_PARAMS;


/**
* @brief This API call will start IP provisioning for all the lines for IPv4/IPv6 , or dual mode
* @param[in] pParameters - IP provisioning for all line register status from PMTAMGMT_MTA_PROVISIONING_PARAMS structure.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
INT mta_hal_start_provisioning(PMTAMGMT_MTA_PROVISIONING_PARAMS pParameters);

/**
* @brief Callback function type for getting MTA line register status.
*        This callback function is used to obtain the status of line registration.
* @param output_status_array - return array buffer for all line register status data from MTAMGMT_MTA_STATUS enumeration.
* @param array_size - It is a 4 byte integer that provides buffer size (total line number).
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*/
typedef INT ( * mta_hal_getLineRegisterStatus_callback)(MTAMGMT_MTA_STATUS *output_status_array, int array_size);

/**
* @brief Register a callback function for line register status updates.
*        This function registers a callback that will be called whenever there is an update in the line register status.
* @param[in] callback_proc - Callback registration function.
*
*/

void mta_hal_LineRegisterStatus_callback_register(mta_hal_getLineRegisterStatus_callback callback_proc); //Callback registration function.

#endif /* __MTA_HAL_H__ */
/**
 * @}
 */
