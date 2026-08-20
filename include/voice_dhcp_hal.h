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

#ifndef VOICE_DHCP_HAL_H
#define VOICE_DHCP_HAL_H

/**
 * @file voice_dhcp_hal.h
 * @brief Vendor-neutral Voice System HAL for PacketCable/VoIP bring-up.
 *
 * This interface lets a voice component:
 *  - register callbacks (subscribe to interface updates, set firewall rules, fetch certs)
 *  - receive interface/DHCP information snapshots via a single notify call
 *  - expose PacketCable capability TLVs for DHCP option construction
 *
 * All strings are NUL-terminated. Empty string == "not provided".
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---------- sizes (tunable) ---------- */
#define VOICE_IFNAME_LEN         32      /* e.g., "eth0.310" */
#define VOICE_IPV4_ADDR_LEN      16      /* "255.255.255.255" + NUL */
#define VOICE_IPV6_ADDR_LEN      128     /* textual IPv6 (with scope, if any) */
#define VOICE_IPVX_ADDR_LEN      VOICE_IPV6_ADDR_LEN
#define VOICE_STRMAX_32          33      /* 32 chars + NUL */
#define VOICE_STRMAX_128         129     /* 128 chars + NUL */
#define VOICE_CERT_LEN           4096    /* PEM buffers */

/* ---------- firewall rule ---------- */
/** Ingress rule bound to a single interface. */
typedef struct
{
  uint8_t  enable;                               /* 1=enable, 0=disable */
  char     filterName[VOICE_STRMAX_32];          /* rule name */
  char     ifName[VOICE_IFNAME_LEN];             /* interface */
  char     protocol[VOICE_STRMAX_32];            /* "UDP" | "TCP" | "TCP or UDP" */
  uint32_t destinationPort;                      /* local destination port */
  char     sourceIPAddress[VOICE_IPVX_ADDR_LEN]; /* source IP (v4/v6 text) */
  char     sourceNetMask[VOICE_IPVX_ADDR_LEN];   /* source mask/prefix (text) */
} VoiceFirewallRuleType;

/* ---------- interface info snapshot ---------- */
/**
 * Snapshot of IPv4/IPv6 + DHCP parameters for a subscribed interface.
 * Fields align with common PacketCable provisioning flows.
 */
typedef struct
{
  char    intfName[VOICE_IFNAME_LEN];
  uint8_t isPhyUp;                                  /* link state (1=up) */

  /* DHCPv4 */
  uint8_t isIpv4Up;                                 /* IPv4 address valid */
  char    ipv4Addr[VOICE_IPV4_ADDR_LEN];            /* IP or CIDR, e.g., "192.0.2.10/24" */
  char    v4NextServerIp[VOICE_IPV4_ADDR_LEN];      /* BOOTP siaddr */
  char    v4ServerHostName[VOICE_STRMAX_128];       /* BOOTP sname or opt 66 */
  char    v4BootFileName[VOICE_STRMAX_128];         /* BOOTP file or opt 67 */
  char    v4DnsServers[VOICE_IPV4_ADDR_LEN*4];      /* opt 6, comma-separated */
  char    v4LogServerIp[VOICE_IPV4_ADDR_LEN];       /* opt 7 (syslog), if present */
  char    v4HostName[VOICE_STRMAX_128];             /* opt 12 */
  char    v4DomainName[VOICE_STRMAX_128];           /* opt 15 */
  char    v4ProvServer[VOICE_STRMAX_128];           /* PacketCable v4: Opt122 subopt 3 (IPv4/FQDN) */

  /* DHCPv6 */
  uint8_t isIpv6Up;                                 /* at least one global IPv6 present */
  char    ipv6GlobalAddr[VOICE_IPV6_ADDR_LEN];      /* preferred global address */
  char    v6TftpServerIp[VOICE_IPV6_ADDR_LEN];      /* Opt17 subopt 32 (IPv6) */
  char    v6TftpFileName[VOICE_STRMAX_128];         /* Opt17 subopt 33 */
  char    v6SyslogServerIp[VOICE_IPV6_ADDR_LEN];    /* Opt17 subopt 34 (IPv6) */
  char    v6ProvServerIp[VOICE_STRMAX_128];         /* Opt17 subopt 2171:3 (IPv6/FQDN/IPv4 as text) */
  char    v6DnsServers[VOICE_IPV6_ADDR_LEN*4];      /* opt 23, comma-separated */
  char    v6DomainName[VOICE_STRMAX_128];           /* opt 24 (first decoded name) */
  char    v6ClientFqdn[VOICE_STRMAX_128];           /* opt 39 (decoded FQDN) */
} VoiceInterfaceInfoType;

/* ---------- certificate bundle ---------- */
typedef struct
{
  char localSipCertPrivKey[VOICE_CERT_LEN];        /* PEM private key */
  char localSipCertContents[VOICE_CERT_LEN];       /* PEM client cert (chain) */
  char trustedCaSipCertContents[VOICE_CERT_LEN];   /* PEM CA bundle */
} VoiceCertificateInfoType;

/* ---------- PacketCable capability TLVs ---------- */
/**
 * Capability advert used to build:
 *  - DHCPv4 Option 60 (Vendor Class)
 *  - DHCPv6 Option 17 suboption 35 (vendor capabilities)
 */
typedef struct
{
  uint8_t  pktcblVersion;       /* Subopt  1 */
  uint8_t  numEndpoints;        /* Subopt  2 */
  uint8_t  tgtSupport;          /* Subopt  3 */
  uint8_t  httpDownload;        /* Subopt  4 */
  uint8_t  nvramInfoStorage;    /* Subopt  9 */
  uint8_t  supportedCodecs[3];  /* Subopt 11 (up to 3) */
  uint8_t  silenceSuppression;  /* Subopt 12 */
  uint8_t  echoCancellation;    /* Subopt 13 */
  uint8_t  ugsAd;               /* Subopt 15 */
  uint8_t  ifIndexStart;        /* Subopt 16 */
  uint16_t supportedProvFlow;   /* Subopt 18 */
  uint8_t  t38Version;          /* Subopt 19 */
  uint8_t  t38ErrorCorrection;  /* Subopt 20 */
  uint8_t  rfc2833;             /* Subopt 21 */
  uint8_t  voiceMetrics;        /* Subopt 22 */
  uint8_t  supportedMibs[3];    /* Subopt 23 */
  uint8_t  multiGrants;         /* Subopt 24 */
  uint8_t  v_152;               /* Subopt 25 */
  uint8_t  certBootstrapping;   /* Subopt 26 */
  uint8_t  ipAddrProvCap;       /* Subopt 38 (IPv6) */
} VoicePktcCapabilitiesType;

/* ---------- callback signatures (synchronous) ---------- */
typedef uint8_t (*VOICE_CB_SUBS_IF_INFO)    (char *ifName, uint8_t enable);
typedef uint8_t (*VOICE_CB_SET_FIREWALL_RULE)(VoiceFirewallRuleType *rule);
typedef uint8_t (*VOICE_CB_GET_CERT_INFO)   (VoiceCertificateInfoType *certs);

/* ---------- public API ---------- */
/** Initialize the Voice HAL at startup. Returns 1 on success. */
uint8_t voice_hal_init(void);

/**
 * Register mandatory callbacks. Calls are synchronous (must return before continuing).
 * The Voice HAL may defer notifications until callbacks are registered.
 */
uint8_t voice_hal_register_cb(VOICE_CB_SUBS_IF_INFO    cbSubIfInfo,
                              VOICE_CB_SET_FIREWALL_RULE cbSetFwRule,
                              VOICE_CB_GET_CERT_INFO   cbGetCertInfo);

/** Notify the voice component that a subscribed interface has new info. */
uint8_t voice_hal_interface_info_notify(VoiceInterfaceInfoType *info);

/** Provide PacketCable capability advert to build DHCP options. */
uint8_t voice_hal_get_pktc_capabilities(VoicePktcCapabilitiesType *cap);

#ifdef __cplusplus
}
#endif
#endif /* VOICE_DHCP_HAL_H */
