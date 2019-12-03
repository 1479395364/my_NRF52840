
#ifndef __MY_SERVICE__H__
#define __MY_SERVICE__H__

#include "ble.h"
#include <string.h>
#include <stdint.h>
#include "ble_types.h"
#include "app_error.h"
#include "nrf_log.h"

#include "ble_srv_common.h"

/*
43549913-81c6-4f8c-80b5-12b8674fd203
d1c2f625-c202-4c3e-ad48-1c2916a91b62
3abecc6a-658c-45e9-bb10-3d595fcf19c8
0f9ea364-6d9e-4b77-99e8-cd7c3bc8fbc3
a189a09b-6742-4f7d-9368-5bfa911a6825
*/

#define MY_BLE_EEG_SERVICE_UUID             0xFEE0 

#define MY_BLE_EEG_CTRL_CHAR_UUID			0xFEE1 
#define MY_BLE_EEG_DATA_CHAR_UUID			0xFEE2 
#define MY_BLE_EEG_READ_CHAR_UUID			0xFEE3 


/**@brief Nordic vendor-specific base UUID.
 */
#define MY_BLE_EEG_VENDOR_BASE_UUID                 \
{{                                                  \
    0x1A, 0x08, 0xE0, 0x89, 0xA5, 0x80, 0xEB, 0xB0, \
    0xE9, 0x11, 0x6A, 0x8B, 0x00, 0x00, 0x6A, 0xF8  \
}}



void MYServicesInit(void);
void MYAddWriteChar(void);
void MYAddIdicateChar(void);

#endif