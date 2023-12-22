# MTA HAL Documentation

## Acronyms

- `MTA` \- Media Terminal Adapter
- `DECT` \- Digital Enhanced Cordless Telecommunications
- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture
- `DSX` \- Digital Signal Cross-connect

## Description
The diagram below describes a high-level software architecture of the MTA(Media Terminal Adapter) HAL module stack.

![MTA HAL Architecture Diag](images/mta_hal_architecture.png)

MTA HAL is an abstraction layer implemented to abstract the underlying MTA hardware and interact with the underlying voice vendor software through a standard set of APIs. An MTA can deliver Home Phone service in addition to High speed internet.

## Component Runtime Execution Requirements

### Initialization and Startup

The below mentioned APIs initialize the MTA HAL layers/code. MTA client module should call the mentioned APIs initially during bootup/initialization.

- `mta_hal_InitDB()`
- `mta_hal_start_provisioning()`

3rd party vendors will implement appropriately to meet operational requirements. This interface is expected to block if the hardware is not ready.

## Threading Model

The interface is not thread safe.

Any module which is invoking the MTA HAL API should ensure calls are made in a thread safe manner.

Vendors can create internal threads/events to meet their operation requirements.  These should be responsible to synchronize between the calls, events and cleaned up on closure.

## Process Model

All API's are expected to be called from multiple process.

## Memory Model

The client is responsible to allocate and deallocate memory for necessary APIs as specified in API Documentation.
Different 3rd party vendors allowed to allocate memory for internal operational requirements. In this case 3rd party implementations should be responsible to de-allocate internally.

TODO:
State a footprint requirement. Example: This should not exceed XXXX KB.

## Power Management Requirements

The HAL is not involved in any of the power management operation.
Any power management state transitions MUST not affect the operation of the HAL.

## Asynchronous Notification Model

There are no asynchronous notifications.

## Blocking calls

The APIs are expected to work synchronously and should complete within a time period commensurate with the complexity of the operation and in accordance with any relevant MTA specification. 
Any calls that can fail due to the lack of a response from connected device should have a timeout period in accordance with any API documentation.
The upper layers will call this API from a single thread context, this API should not suspend.

TODO:
As we state that they should complete within a time period, we need to state what that time target is, and pull it from the spec if required. Define the timeout requirement.

## Internal Error Handling

All the MTA HAL APIs should return error synchronously as a return argument. HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

There is no requirement for HAL to persist any setting information. The caller is responsible to persist any settings related to MTA feature.

## Nonfunctional requirements

Following non functional requirement should be supported by the component.

## Logging and debugging requirements

MTA HAL component should log all the error and critical informative messages, preferably using printf, syslog which helps to debug/triage the issues and understand the functional flow of the system.

The logging should be consistence across all HAL components.

If the vendor is going to log then it has to be logged in `xxx_vendor_hal.log` file name which can be placed in `/rdklogs/logs/` or `/var/tmp/` directory.

Logging should be defined with log levels as per Linux standard logging.

## Memory and performance requirements

The component should not contributing more to memory and CPU utilization while performing normal operations and commensurate with the operation required.

## Quality Control

MTA HAL implementation should pass checks using any third party tools like `Coverity`, `Black duck`, `Valgrind` etc. without any issue to ensure quality.

There should not be any memory leaks/corruption introduced by HAL and underneath 3rd party software implementation.

## Licensing

MTA HAL implementation is expected to released under the Apache License 2.0.

## Build Requirements

The source code should be able to be built under Linux Yocto environment and should be delivered as a shared library named as `libhal_mta.so`

## Variability Management

Changes to the interface will be controlled by versioning, vendors will be expected to implement to a fixed version of the interface, and based on SLA agreements move to later versions as demand requires.

Each API interface will be versioned using [Semantic Versioning 2.0.0](https://semver.org/), the vendor code will comply with a specific version of the interface.

## Platform or Product Customization

None

# Interface API Documentation

All HAL function prototypes and datatype definitions are available in `mta_hal.h` file.
  1.  Components/Processes must include `mta_hal.h` to make use of MTA HAL capabilities
  2.  Components/Processes must include linker dependency for `libhal_mta.so`.

## Theory of operation and key concepts

Covered as per "Description" sections in the API documentation.

### UML Diagrams

## Sequence Diagram

```mermaid
sequenceDiagram
participant Client Module
participant MTA HAL
participant Vendor Software
Note over Client Module: Init once during bootup, Needed for Dependent API's. <br> Ignore this if caller doesn't have any Dependent API's
Client Module->>MTA HAL: mta_hal_Initxxxxx()
MTA HAL->>Vendor Software: 
Vendor Software->>MTA HAL: 
MTA HAL->>Client Module: return

Client Module->>MTA HAL: mta_hal_start_provisioning()
MTA HAL->>Vendor Software: 
Vendor Software->>MTA HAL: 
MTA HAL->>Client Module: return

Client Module->>MTA HAL: mta_hal_Getxxxxx()
MTA HAL->>Vendor Software: 
Vendor Software->>MTA HAL: 
MTA HAL->>Client Module: return

Client Module->>MTA HAL: mta_hal_Setxxxxx()
MTA HAL->>Vendor Software: 
Vendor Software->>MTA HAL: 
MTA HAL->>Client Module: return
```
