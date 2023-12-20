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
 * TODO:
 * While we're trying really hard to smooth the procedure of switch-over from IPv4 to IPv4, there
 * are many places where using the IP address as an integer for comparision and calculation is much
 * easier than array-based operation.
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
 *  TODO: 
 *  DH  This is not the right place to place platform/HAL
 *      implementation specific definitions here.
 *      This kind of definitions belongs to hal.c, or another
 *      header file which is included by hal.c
 *
 *  Fix the other RDK-B vendor's code!!!
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
 *  TODO:
 *  DH  This is also questionable why we have to define this kind of
 *      platform specific capacility in the hal header file
 */
#define DECT_MAX_HANDSETS 5

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
/**
 * @struct _MTAMGMT_MTA_DECT
 * @brief It is a structure to populate information/settings associated with DECT module.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef struct
_MTAMGMT_MTA_DECT
{
    ULONG                           RegisterDectHandset;    /**< Information required for these parameters is unknown.
                                                                 Currently these values are set to 0 in the CCSP code. */
    ULONG                           DeregisterDectHandset;  /**< Information required for these parameters is unknown.
                                                                 Currently these values are set to 0 in the CCSP code. */
    char                            HardwareVersion[64];    /**< Contains the DECT module hardware version. */
    char                            RFPI[64];               /**< RFPI value of the DECT module from the EEPROM. */
    char                            SoftwareVersion[64];    /**< Contains the DECT module software version. */
    char                            PIN[64];                /**< Authentication PIN for base module(CMBS)<->handset communication. */
}
MTAMGMT_MTA_DECT, *PMTAMGMT_MTA_DECT;

/**
 * @brief Structure to hold the details of registered or subscribed MTA handsets.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_HANDSETS_INFO
{
    ULONG                           InstanceNumber;         /**< Instance number of the MTA Handset */
    BOOLEAN                         Status;                 /**< Status of the MTA Handset */
    char                            LastActiveTime[64];     /**< Last Active Time of the MTA Handset */
    char                            HandsetName[64];        /**< Handset Name */
    char                            HandsetFirmware[64];    /**< Handset version     */
    char                            OperatingTN[64];        /**< Operating TN. At present only TN1 will be assigned to DECT phones. */
    char                            SupportedTN[64];        /**< Supported TN. At present only TN1 will be assigned to DECT phones. */
}
MTAMGMT_MTA_HANDSETS_INFO,  *PMTAMGMT_MTA_HANDSETS_INFO;

/**
 * @brief Structure to hold all the DHCP information for MTA.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_DHCP_INFO
{
    ANSC_IPV4_ADDRESS               IPAddress;                  /**< It is a ANSC_IPV4_ADDRESS union type value that represents the IP Address.  The union members are defined as below:
                                                                     Dot - An unsigned character array of size 4.
                                                                     Value - A 32 bit unsigned integer value.
                                                                     The valid ranges for IPv4 addresses are: 1.0.0.0 to 127.0.0.0, 128.0.0.0 to 191.255.0.0, 192.0.0.0 to 223.255.255.0 */
    CHAR                            BootFileName[64];           /**< Represents the Boot File Name.*/
    CHAR                            FQDN[64];                   /**< Represents the fully qualified domain name.*/
    ANSC_IPV4_ADDRESS               SubnetMask;                 /**< It is a ANSC_IPV4_ADDRESS union type value that represents the Subnet Mask.  The union members are defined as below:
                                                                     Dot - An unsigned character array of size 4.
                                                                     Value - A 32 bit unsigned integer value.
                                                                     The range of values for each octet is 0 to 255. */
    ANSC_IPV4_ADDRESS               Gateway;                    /**< It is a ANSC_IPV4_ADDRESS union type value that represents the Gateway.  The union members are defined as below:
                                                                     Dot - An unsigned character array of size 4.
                                                                     Value - A 32 bit unsigned integer value.
                                                                     The valid range is: 1.0.0.0 to 127.0.0.0, 128.0.0.0 to 191.255.0.0, 192.0.0.0 to 223.255.255.0 */
    ULONG                           LeaseTimeRemaining;         /**< Represents the Lease Time Remaining. */
    CHAR                            RebindTimeRemaining[64];    /**< Represents the Rebind Time Remaining. */
    CHAR                            RenewTimeRemaining[64];     /**< Represents the Renew Time Remaining. */
    ANSC_IPV4_ADDRESS               PrimaryDNS;                 /**< It is a ANSC_IPV4_ADDRESS union type value that represents the Primary DNS. The union members are defined as below:
                                                                     Dot - An unsigned character array of size 4.
                                                                     Value - A 32 bit unsigned integer value.
                                                                     The valid range is: 1.0.0.0 to 127.0.0.0, 128.0.0.0 to 191.255.0.0, 192.0.0.0 to 223.255.255.0 */
    ANSC_IPV4_ADDRESS               SecondaryDNS;               /**< It is a ANSC_IPV4_ADDRESS union type value that represents the Secondary DNS. The union members are defined as below:
                                                                     Dot - An unsigned character array of size 4.
                                                                     Value - A 32 bit unsigned integer value.
                                                                     The valid range is: 1.0.0.0 to 127.0.0.0, 128.0.0.0 to 191.255.0.0, 192.0.0.0 to 223.255.255.0 */
    CHAR                            DHCPOption3[64];            /**< DHCP Option 3. It is a 64 bytes character array that specifies the IP address of the default gateway(router) for the DHCP client to use for internet access and communication with devices outside the local network. */
    CHAR                            DHCPOption6[64];            /**< DHCP Option 6. It is a 64 bytes character array that specifies the IP Address of a DNS servers that the DNS client should use for domain name resolution. */
    CHAR                            DHCPOption7[64];            /**< DHCP Option 7. It is a 64 bytes character array that specifies the IP address of a log server that the DHCP client can use for logging purpose. */
    CHAR                            DHCPOption8[64];            /**< DHCP Option 8. It is a 64 bytes character array that specifies the IP address of a cookie server that the DHCP client can use to retrieve cookies. */
    CHAR                            PCVersion[64];              /**< PacketCable version. Example: "2.0" */
    CHAR                            MACAddress[64];             /**< The telephony IPv4 MAC address for this device */
    ANSC_IPV4_ADDRESS               PrimaryDHCPServer;          /**< It is a ANSC_IPV4_ADDRESS union type value that represents the Primary DHCP server. The union members are defined as below:
                                                                     Dot - An unsigned character array of size 4.
                                                                     Value - A 32 bit unsigned integer value.
                                                                     The valid range is: 1.0.0.0 to 127.0.0.0, 128.0.0.0 to 191.255.0.0, 192.0.0.0 to 223.255.255.0 */
    ANSC_IPV4_ADDRESS               SecondaryDHCPServer;        /**< It is a ANSC_IPV4_ADDRESS union type value that represents the Secondary DHCP server. The union members are defined as below:
                                                                     Dot - An unsigned character array of size 4.
                                                                     Value - A 32 bit unsigned integer value.
                                                                     The valid range is: 1.0.0.0 to 127.0.0.0, 128.0.0.0 to 191.255.0.0, 192.0.0.0 to 223.255.255.0 */
}
MTAMGMT_MTA_DHCP_INFO, *PMTAMGMT_MTA_DHCP_INFO;

/**
 * @brief Structure to hold all the DHCPv6 information for MTA.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_DHCPv6_INFO
{
    CHAR                            IPV6Address[INET6_ADDRSTRLEN];              /**< It is a 46 bytes character array represents the IPV6 Address.
                                                                                     The valid range is: 0000::/8, 2000::/3, FC00::/7, FE80::/10 and FF00::/8 */
    CHAR                            BootFileName[64];                           /**< Represents the Boot File Name. */
    CHAR                            FQDN[64];                                   /**< Represents the fully qualified domain name. */
    CHAR                            Prefix[INET6_ADDRSTRLEN];                   /**< It is a 46 bytes character array represents the Prefix. It is vendor specific. */
    CHAR                            Gateway[INET6_ADDRSTRLEN];                  /**< It is a 46 bytes character array that represents the Gateway.
                                                                                     The valid range is: 0000::/8, 2000::/3, FC00::/7, FE80::/10 and FF00::/8 */
    ULONG                           LeaseTimeRemaining;                         /**< Represents the Lease Time Remaining.*/
    CHAR                            RebindTimeRemaining[64];                    /**< Represents the Rebind Time Remaining.*/
    CHAR                            RenewTimeRemaining[64];                     /**< Represents the Renew Time Remaining.*/
    CHAR                            PrimaryDNS[INET6_ADDRSTRLEN];               /**< It is a 46 bytes character array that represents the Primary DNS.
*                                                                                    The valid range is: 0000::/8, 2000::/3, FC00::/7, FE80::/10 and FF00::/8 */
    CHAR                            SecondaryDNS[INET6_ADDRSTRLEN];             /**< It is a 46 bytes character array that represents the Secondary DNS.
*                                                                                    The valid range is: 0000::/8, 2000::/3, FC00::/7, FE80::/10 and FF00::/8 */
    CHAR                            DHCPOption3[64];                            /**< DHCP Option 3. It is a 64 bytes character array that provides information about the IPv6 address prefix to be used by the client for autoconfiguration.
                                                                                     The valid range is 1 to 128.*/
    CHAR                            DHCPOption6[64];                            /**< DHCP Option 6. It is a 64 bytes character array that supplies the IPv6 addresses of DNS servers that the DHCPv6 client should use for domain name resolution.
                                                                                     The valid range is: 0000::/8, 2000::/3, FC00::/7, FE80::/10 and FF00::/8*/
    CHAR                            DHCPOption7[64];                            /**< DHCP Option 7. It is a 64 bytes character array that provides a list of domain names that the DHCPv6 client can search when performing domain name resolution. It is vendor specific.*/
    CHAR                            DHCPOption8[64];                            /**< DHCP Option 8. It is a 64 bytes character array that conveys the maximum transmission unit (MTU) for the client's network interface. It is vendor specific.*/
    CHAR                            PCVersion[64];                              /**< Respresents the PacketCable version. Sample value: "2.0"*/
    CHAR                            MACAddress[64];                             /**< The telephony IPv6 MAC address for this device*/
    CHAR                            PrimaryDHCPv6Server[INET6_ADDRSTRLEN];      /**< It is a 46 bytes character array that represents the Primary DHCPv6 server. It is a server-specific value. */
    CHAR                            SecondaryDHCPv6Server[INET6_ADDRSTRLEN];    /**< It is a 46 bytes character array that represents the Secondary DHCPv6 Server. It is a server-specific value. */
}
MTAMGMT_MTA_DHCPv6_INFO, *PMTAMGMT_MTA_DHCPv6_INFO;

/**
 * @brief Structure to hold all the MTA service flow information.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_SERVICE_FLOW
{
    ULONG                           SFID;                        /**< Service Flow Id */
    CHAR                            ServiceClassName[256];       /**< Service Class Name*/
    CHAR                            Direction[16];               /**< MTA service Flow direction. Possible values are: Upstream, Downstream */
    ULONG                           ScheduleType;                /**< It is a unsigned long integer value that represents the MTA service Flow Schedule Type.  
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value.*/
    BOOLEAN                         DefaultFlow;                 /**< It is a boolean value that specifies the default flow of the Service Flow. */
    ULONG                           NomGrantInterval;            /**< It is a unsigned long integer value that represents the Nominal Grant Interval. It is the the nominal interval in microseconds between successive data grant opportunities on an upstream Service Flow
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           UnsolicitGrantSize;          /**< It is a unsigned long integer value that represents the Unsolicited Grant Size in bytes. 
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           TolGrantJitter;              /**< It is a unsigned long integer value that represents the Tolerated Grant Jitter. It is the maximum amount of time in microseconds that the transmission opportunities may be delayed from the nominal periodic schedule.
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           NomPollInterval;             /**< It is a unsigned long integer value that represents the Nominal Polling Interval. It is the nominal interval in microseconds between successive unicast request opportunities on an upstream Service Flow.
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           MinReservedPkt;              /**< It is a unsigned long integer value that represents The assumed minimum packet size in bytes for which the MinReservedRate will be provided.
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           MaxTrafficRate;              /**< It is a unsigned long integer value that represents the Maximum Sustained Traffic Rate allowed for this Service Flow in bits/sec. 
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           MinReservedRate;             /**< It is a unsigned long integer value that represents the guaranteed Minimum Reserved Traffic Rate in bits/sec. 
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           MaxTrafficBurst;             /**< It is a unsigned long integer value that represents the Maximum Traffic Burst in bytes. 
                                                                      The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    CHAR                            TrafficType[64];             /**< It is a 64-byte character array which represent whether the service flow is for SIP or RTP. */
    ULONG                           NumberOfPackets;             /**< The number of packets of the Service Flow */
}
MTAMGMT_MTA_SERVICE_FLOW, *PMTAMGMT_MTA_SERVICE_FLOW;

/**
 * @brief Structure to hold the MTA call info.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_CALLS
{
    CHAR                            Codec[64];                                             /**< Local side codec used for the call. It is a vendor-specific value. */
    CHAR                            RemoteCodec[64];                                       /**< Remote side codec used for the call. It is a vendor-specific value. */
    CHAR                            CallStartTime[64];                                     /**< Start time of a call.  Example value: 2000-01-01. */
    CHAR                            CallEndTime[64];                                       /**< End time of a call. Example value: 2000-01-01. */
    CHAR                            CWErrorRate[MTA_HAL_SHORT_VALUE_LEN];                  /**< ratio of useful signal to background noise. It is a vendor-specific value.*/
    CHAR                            PktLossConcealment[MTA_HAL_SHORT_VALUE_LEN];           /**< ratio of pkt lost to total expected. It is a vendor-specific value.*/
    BOOLEAN                         JitterBufferAdaptive;                                  /**< JBA used or not. */
    BOOLEAN                         Originator;                                            /**< Originating side of the call or not .*/
    ANSC_IPV4_ADDRESS               RemoteIPAddress;                                       /**< remote IP
                                                                                                It is a ANSC_IPV4_ADDRESS union type value that represents the Primary DHCP server. The union members are defined as below:
                                                                                                     Dot - An unsigned character array of size 4.
                                                                                                     Value - A 32 bit unsigned integer value.
                                                                                                The valid ranges for IPv4 addresses are: 1.0.0.0 to 127.0.0.0, 128.0.0.0 to 191.255.0.0, 192.0.0.0 to 223.255.255.0*/
    ULONG                           CallDuration;                                          /**< Length of the call in minutes. The value ranges from 0 to (2^32)-1. */
    CHAR                            CWErrors[MTA_HAL_SHORT_VALUE_LEN];                     /**< Code word errors on this channel. It is a vendor-specific value.*/
    CHAR                            SNR[MTA_HAL_SHORT_VALUE_LEN];                          /**< Signal to noise ratio * 256. It is a vendor-specific value.*/
    CHAR                            MicroReflections[MTA_HAL_SHORT_VALUE_LEN];             /**< Return loss measurement. It is a vendor-specific value.*/
    CHAR                            DownstreamPower[MTA_HAL_SHORT_VALUE_LEN];              /**< downstream power in dbmv. It is a vendor-specific value.*/
    CHAR                            UpstreamPower[MTA_HAL_SHORT_VALUE_LEN];                /**< upstream power in dbmv. It is a vendor-specific value.*/
    CHAR                            EQIAverage[MTA_HAL_SHORT_VALUE_LEN];                   /**< EQI average. It is a vendor-specific value.*/
    CHAR                            EQIMinimum[MTA_HAL_SHORT_VALUE_LEN];                   /**< EQI minimum. It is a vendor-specific value.*/
    CHAR                            EQIMaximum[MTA_HAL_SHORT_VALUE_LEN];                   /**< EQI maximum. It is a vendor-specific value.*/
    CHAR                            EQIInstantaneous[MTA_HAL_SHORT_VALUE_LEN];             /**< EQI instantaneous. It is a vendor-specific value. */
    CHAR                            MOS_LQ[MTA_HAL_SHORT_VALUE_LEN];                       /**< mean opinion score of listening quality. It ranges between 10-50. */
    CHAR                            MOS_CQ[MTA_HAL_SHORT_VALUE_LEN];                       /**< mean opinion score of conversational quality. It ranges between 10-50. */
    CHAR                            EchoReturnLoss[MTA_HAL_SHORT_VALUE_LEN];               /**< residual echo return loss, in db. It is a vendor-specific value. */
    CHAR                            SignalLevel[MTA_HAL_SHORT_VALUE_LEN];                  /**< voice signal relative level, in db. It is a vendor-specific value. */
    CHAR                            NoiseLevel[MTA_HAL_SHORT_VALUE_LEN];                   /**< noise relative level, in db. It is a vendor-specific value. */
    CHAR                            LossRate[MTA_HAL_SHORT_VALUE_LEN];                     /**< fraction of RTP data packet loss * 256. It is a vendor-specific value. */
    CHAR                            DiscardRate[MTA_HAL_SHORT_VALUE_LEN];                  /**< fraction of RTP data packet discarded * 256. It is a vendor-specific value. */
    CHAR                            BurstDensity[MTA_HAL_SHORT_VALUE_LEN];                 /**< fraction of bursting data packet * 256. It is a vendor-specific value. */
    CHAR                            GapDensity[MTA_HAL_SHORT_VALUE_LEN];                   /**< fraction of packets within inter-burst gap * 256. It is a vendor-specific value. */
    CHAR                            BurstDuration[MTA_HAL_SHORT_VALUE_LEN];                /**< mean duration of bursts, in milliseconds. It is a vendor-specific value. */
    CHAR                            GapDuration[MTA_HAL_SHORT_VALUE_LEN];                  /**< mean duration of gaps, in milliseconds. It is a vendor-specific value. */
    CHAR                            RoundTripDelay[MTA_HAL_SHORT_VALUE_LEN];               /**< most recent measured RTD, in milliseconds. It is a vendor-specific value. */
    CHAR                            Gmin[MTA_HAL_SHORT_VALUE_LEN];                         /**< local gap threshold. It is a vendor-specific value. */
    CHAR                            RFactor[MTA_HAL_SHORT_VALUE_LEN];                      /**< voice quality evaluation for this RTP session. It is a vendor-specific value. */
    CHAR                            ExternalRFactor[MTA_HAL_SHORT_VALUE_LEN];              /**< voice quality evaluation for segment on network external to this RTP session. It is a vendor-specific value. */
    CHAR                            JitterBufRate[MTA_HAL_SHORT_VALUE_LEN];                /**< adjustment rate of jitter buffer, in milliseconds. It is a vendor-specific value. */
    CHAR                            JBNominalDelay[MTA_HAL_SHORT_VALUE_LEN];               /**< nominal jitter buffer length, in milliseconds. It is a vendor-specific value. */
    CHAR                            JBMaxDelay[MTA_HAL_SHORT_VALUE_LEN];                   /**< maximum jitter buffer length, in milliseconds. It is a vendor-specific value. */
    CHAR                            JBAbsMaxDelay[MTA_HAL_SHORT_VALUE_LEN];                /**< absolute maximum delay, in milliseconds. It is a vendor-specific value. */
    CHAR                            TxPackets[MTA_HAL_SHORT_VALUE_LEN];                    /**< count of transmitted packets. It is a vendor-specific value. */
    CHAR                            TxOctets[MTA_HAL_SHORT_VALUE_LEN];                     /**< count of transmitted octet packets. It is a vendor-specific value. */
    CHAR                            RxPackets[MTA_HAL_SHORT_VALUE_LEN];                    /**< count of received packets. It is a vendor-specific value. */
    CHAR                            RxOctets[MTA_HAL_SHORT_VALUE_LEN];                     /**< count of received octet packets. It is a vendor-specific value. */
    CHAR                            PacketLoss[MTA_HAL_SHORT_VALUE_LEN];                   /**< count of lost packets. It is a vendor-specific value. */
    CHAR                            IntervalJitter[MTA_HAL_SHORT_VALUE_LEN];               /**< stat variance of packet interarrival time, in milliseconds. It is a vendor-specific value. */
    CHAR                            RemoteIntervalJitter[MTA_HAL_SHORT_VALUE_LEN];         /**< remote sie IntervalJitter. It is a vendor-specific value. */
    CHAR                            RemoteMOS_LQ[MTA_HAL_SHORT_VALUE_LEN];                 /**< remote side MOS_LQ. It is a vendor-specific value. */
    CHAR                            RemoteMOS_CQ[MTA_HAL_SHORT_VALUE_LEN];                 /**< remote side MOS_CQ. It is a vendor-specific value. */
    CHAR                            RemoteEchoReturnLoss[MTA_HAL_SHORT_VALUE_LEN];         /**< remote side EchoReturnLoss. It is a vendor-specific value. */
    CHAR                            RemoteSignalLevel[MTA_HAL_SHORT_VALUE_LEN];            /**< remote side SignalLevel. It is a vendor-specific value. */
    CHAR                            RemoteNoiseLevel[MTA_HAL_SHORT_VALUE_LEN];             /**< remote side NoiseLevel. It is a vendor-specific value. */
    CHAR                            RemoteLossRate[MTA_HAL_SHORT_VALUE_LEN];               /**< remote side LossRate. It is a vendor-specific value. */
    CHAR                            RemotePktLossConcealment[MTA_HAL_SHORT_VALUE_LEN];     /**< remote side PktLossConcealment. It is a vendor-specific value. */
    CHAR                            RemoteDiscardRate[MTA_HAL_SHORT_VALUE_LEN];            /**< remote side DiscardRate. It is a vendor-specific value. */
    CHAR                            RemoteBurstDensity[MTA_HAL_SHORT_VALUE_LEN];           /**< remote side BurstDensity. It is a vendor-specific value. */
    CHAR                            RemoteGapDensity[MTA_HAL_SHORT_VALUE_LEN];             /**< remote side GapDensity. It is a vendor-specific value. */
    CHAR                            RemoteBurstDuration[MTA_HAL_SHORT_VALUE_LEN];          /**< remote side BurstDuration. It is a vendor-specific value. */
    CHAR                            RemoteGapDuration[MTA_HAL_SHORT_VALUE_LEN];            /**< remote side GapDuration. It is a vendor-specific value. */
    CHAR                            RemoteRoundTripDelay[MTA_HAL_SHORT_VALUE_LEN];         /**< remote side RoundTripDelay. It is a vendor-specific value. */
    CHAR                            RemoteGmin[MTA_HAL_SHORT_VALUE_LEN];                   /**< remote side Gmin. It is a vendor-specific value. */
    CHAR                            RemoteRFactor[MTA_HAL_SHORT_VALUE_LEN];                /**< remote side RFactore. It is a vendor-specific value. */
    CHAR                            RemoteExternalRFactor[MTA_HAL_SHORT_VALUE_LEN];        /**< remote side ExternalRFactor. It is a vendor-specific value. */
    BOOLEAN                         RemoteJitterBufferAdaptive;                            /**< remote side JitterBufferAdaptive. It is a vendor-specific value. */
    CHAR                            RemoteJitterBufRate[MTA_HAL_SHORT_VALUE_LEN];          /**< remote side JitterBufRate. It is a vendor-specific value. */
    CHAR                            RemoteJBNominalDelay[MTA_HAL_SHORT_VALUE_LEN];         /**< remote side JBNominalDelay. It is a vendor-specific value. */
    CHAR                            RemoteJBMaxDelay[MTA_HAL_SHORT_VALUE_LEN];             /**< remote side JBMaxDelay. It is a vendor-specific value. */
    CHAR                            RemoteJBAbsMaxDelay[MTA_HAL_SHORT_VALUE_LEN];          /**< remote side JBAbsMaxDelay. It is a vendor-specific value. */
}
MTAMGMT_MTA_CALLS, *PMTAMGMT_MTA_CALLS;

/**
 * @brief Structure to hold MTA Line table entry information.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_LINETABLE_INFO
{
    ULONG                           InstanceNumber;             /**< It is a unsigned long integer value that represents the instance number. The value ranges from 0 to (2^32)-1. */
    ULONG                           LineNumber;                 /**< It is a unsigned long integer value that represents the line number. The value ranges from 0 to (2^32)-1. */
    ULONG                           Status;                     /**< It is a unsigned long integer value that defines the status. The value ranges from 0 to (2^32)-1. Possible Values: 1 = OnHook; 2 = OffHook */
    CHAR                            HazardousPotential[128];    /**< It is a character array that represents the Hazardous potential.
                                                                     It is a vendor-specific value. Possible Values: HEMF Test Passed, HEMF Test Failed, Not Started */
    CHAR                            ForeignEMF[128];            /**< It is a character array that represents the foreign EMF.
                                                                     It is a vendor-specific value. Possible Values: FEMF Test Passed, FEMF Test Failed, Not Started */
    CHAR                            ResistiveFaults[128];       /**< It is a character array that represents the resistive faults.
                                                                     It is a vendor-specific value. Possible Values: ResistiveFaults Test Passed, ResistiveFaults Test Failed, Not Started */
    CHAR                            ReceiverOffHook[128];       /**< It is a character array that represents the receiver off hook.
                                                                     It is a vendor-specific value. Possible Values: Off Hook Simulation Test Passed, Off Hook Simulation Test Failed, Not Started */
    CHAR                            RingerEquivalency[64];      /**< It is a character array that represents the Ringer equivalency.
                                                                     It is a vendor-specific value. Possible Values: Ringer Equivalency Test Passed, Ringer Equivalency Test Failed, Not Started */
    CHAR                            CAName[64];                 /**< It is a character array that represents the CA name.
                                                                     It is a vendor-specific value. */
    ULONG                           CAPort;                     /**< It is a unsigned long integer value that represents the CA port. The value ranges from 0 to (2^32)-1. */
    ULONG                           MWD;                        /**< It is a unsigned long integer value that represents the MWD. The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           CallsNumber;                /**< It is a unsigned long integer value that represents the calls number. The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    PMTAMGMT_MTA_CALLS              pCalls;                     /**< It is a structure PMTAMGMT_MTA_CALLS that defines the MTA calls. It is a vendor-specific value. */
    ULONG                           CallsUpdateTime;            /**< It is a unsigned long integer value that represents the update time of calls. The value ranges from 0 to (2^32)-1. It is a vendor-specific value. */
    ULONG                           OverCurrentFault;           /**< It is a unsigned long integer value that represents the over current fault. The value ranges from 0 to (2^32)-1. Sample Values: 1 = Normal,2 = Fault */
}
MTAMGMT_MTA_LINETABLE_INFO, *PMTAMGMT_MTA_LINETABLE_INFO;

/**
 * @brief Structure to hold the Call processing information.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_CALLP
{
    CHAR                            LCState[64];                  /**< It is a character array that represents the LC State.
                                                                       The value is: In Use, Idle, Out of Service */
    CHAR                            CallPState[64];               /**< It is a character array that represents the Call processing state.
                                                                       The value is: In Service, OOS. */
    CHAR                            LoopCurrent[64];              /**< It is a character array that represents the boosted loop current status.
                                                                       The value is: Normal, Boosted */
}
MTAMGMT_MTA_CALLP,  *PMTAMGMT_MTA_CALLP;

/**
 * @brief Structure to hold the DSX log entries.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_DSXLOG
{
    CHAR                            Time[64];           /**< It is a character array that represents the time.
                                                             It is vendor specific. */
    CHAR                            Description[128];   /**< It is a character array that represents the log description.
                                                             It is a vendor-specific value. */
    ULONG                           ID;                 /**< It is a unsigned long integer value that represents the ID.
                                                             The range is 0 to the (2^32)-1. It is a vendor-specific value. */
    ULONG                           Level;              /**< It is a unsigned long integer value that represents the log level.
                                                             The range is 0 to the (2^32)-1. It is a vendor-specific value. */
}
MTAMGMT_MTA_DSXLOG,  *PMTAMGMT_MTA_DSXLOG;

/**
 * @brief Structure to hold the log entries.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_MTALOG_FULL
{
    ULONG                           Index;              /**< It is a unsigned long integer value that represents the Index. The range is 0 to the (2^32)-1. Sample values are 1,2. */
    ULONG                           EventID;            /**< It is a unsigned long integer value that represents the eventID. The range is 0 to the (2^32)-1. Sample value are 1,2. */
    CHAR                            EventLevel[64];     /**< It is a 64 bytes character array that represents the event level. Sample are "1","2".*/
    CHAR                            Time[64];           /**< It is a 64 bytes character array that represents the time. Example value is: "1998-05-14".*/
    CHAR*                           pDescription;       /**< It is a character pointer to buffer that holds the log description. Sample values are: "this is a log for matLog1", "this is a log for matLog2". */
}
MTAMGMT_MTA_MTALOG_FULL,  *PMTAMGMT_MTA_MTALOG_FULL;

/**
 * @brief Structure to hold the battery information.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */
typedef  struct
_MTAMGMT_MTA_BATTERY_INFO
{
    CHAR                            ModelNumber[32];                /**< Character array that represents the Battery Model Number.
                                                                         It is vendor specific. */
    CHAR                            SerialNumber[32];               /**< Character array that represents the Battery Serial Number.
                                                                         It is vendor specific. */
    CHAR                            PartNumber[32];                 /**< Character array that represents the Battery Part Number.
                                                                         It is vendor specific. */
    CHAR                            ChargerFirmwareRevision[32];    /**< Character array that represents the Charger Firmware Revision.
                                                                         It is vendor specific. */
}
MTAMGMT_MTA_BATTERY_INFO,  *PMTAMGMT_MTA_BATTERY_INFO;

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
 * This enumeration is used to distinguish between different MTA Provisioning status.
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
 * TODO:
 *
 * 1. Extend the return codes by listing out the possible reasons of failure, to improve the interface in the future.
 *    This was reported during the review for header file migration to opensource github.
 * 2. Add return error cases for battery related functions with and without battery present.
 * 3. Plan to split the header files based on purpose of the APIs, for example, DHCP, battery etc.
 *
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
* @brief Get number of entries in the line table.
*
* @return ULONG - number of entries
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
*
*/
ULONG mta_hal_LineTableGetNumberOfEntries(void);

/**
* @brief Get entry of the line table at the given index
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
* @param[in] Index - it is an unsigned long integer that provides line number to perform the GR909 diagnostics on. The value ranges from 0 to (2^32)-1.
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
* @param[out] Count - it is an unsigned long integer that provides number of service flow entries, to be returned. The value ranges from 0 to (2^32)-1.
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
* @param[in] bBool - It is a boolean variable of 1 byte size, that contains value for DECT enabled or not, to be set.
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
* @param[in] bBool - It is a boolean pointer of 1 byte size, for enabled or not.
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
* @param[out] pPINString - It is a 128 bytes of character pointer that provides PIN value.
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
* @brief Retrieve the Call processing status info for the line number
* @param[in]  LineNumber - Unsigned long integer that provides Line number for which to retrieve info on Call processing status.
* @param[out]  pCallp - Call processing info, to be returned.

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
* @param[out] len - It is an unsigned long integer pointer of 4 bytes size, string length, to be returned. The range is 0 to the (2^32)-1.
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
* @param[out] len - It is an unsigned long integer pointer of 4 bytes size, string length, to be returned. The range is 0 to the (2^32)-1.
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
