

#include "my_service.h"


typedef struct blkMRingServiceTag
{
    uint16_t conn_handle; 
    uint16_t service_handle; 
	bool isNotifyAvailable;
	bool isIndicateAvailable;
	bool IndicateConfirmStatus;
	bool isPairValid;
    ble_gatts_char_handles_t write_char_handle; 
	ble_gatts_char_handles_t write_norsp_char_handle;
	ble_gatts_char_handles_t indicate_char_handle;
	ble_gatts_char_handles_t notify_char_handle;
	ble_gatts_char_handles_t read_char_handle;
    ble_gatts_char_handles_t indi_char_handle;
}my_service;

static my_service  MyService;



void MYServicesInit(void)
{
	uint32_t       err_code;
    
    //add Nordic vendor-specific base UUID.
    ble_uuid128_t  p_vs_uuid = MY_BLE_EEG_VENDOR_BASE_UUID;
    uint8_t 	p_uuid_type;

    err_code = sd_ble_uuid_vs_add(&p_vs_uuid, &p_uuid_type);
    if (err_code != NRF_SUCCESS) 
    {
        //NRF_LOG_INFO("add base UUID error");
    }
  
    //add service uuid
    ble_uuid_t service_uuid;
    service_uuid.type = BLE_UUID_TYPE_BLE;
    service_uuid.uuid = MY_BLE_EEG_SERVICE_UUID;
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &MyService.service_handle);//此处不能用‘->’
    	
	// add writechar	
    MYAddWriteChar();
    MYAddIdicateChar();
/*
uint32_t sd_ble_gatts_service_add	(uint8_t type,ble_uuid_t const *p_uuid,uint16_t * 	p_handle )
*/
/*   
uint32_t sd_ble_uuid_vs_add	(ble_uuid128_t const * 	p_vs_uuid,uint8_t * p_uuid_type )	
*/
}


void MYAddWriteChar(void)
{
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t cccd_md;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(ble_gatts_char_md_t));
	memset(&attr_char_value, 0, sizeof(ble_gatts_attr_t));
	memset(&cccd_md, 0, sizeof(ble_gatts_attr_md_t));
	memset(&attr_md, 0, sizeof(ble_gatts_attr_md_t));
	
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);

	cccd_md.vloc = BLE_GATTS_VLOC_STACK;
	char_md.p_cccd_md = &cccd_md;
	char_md.char_props.notify = 0;
	char_md.char_props.write = 1;
	char_md.char_props.read = 0;
	char_md.char_props.indicate = 0;
	char_md.char_props.write_wo_resp = 0;
	char_md.p_char_pf = NULL;
	char_md.p_user_desc_md = NULL;
	char_md.p_sccd_md = NULL;

	attr_md.rd_auth = 0;
	attr_md.wr_auth = 0;
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;

	ble_uuid_t val_uuid;
	val_uuid.type = BLE_UUID_TYPE_BLE;
	val_uuid.uuid = MY_BLE_EEG_CTRL_CHAR_UUID;

	attr_char_value.p_uuid = &val_uuid;
	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len=sizeof(uint8_t);
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = 20;

	sd_ble_gatts_characteristic_add(MyService.service_handle, &char_md, &attr_char_value,&MyService.write_char_handle);
}


void MYAddIdicateChar(void)
{
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t cccd_md;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(ble_gatts_char_md_t));
	memset(&attr_char_value, 0, sizeof(ble_gatts_attr_t));
	memset(&cccd_md, 0, sizeof(ble_gatts_attr_md_t));
	memset(&attr_md, 0, sizeof(ble_gatts_attr_md_t));
	
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);

	cccd_md.vloc = BLE_GATTS_VLOC_STACK;
	char_md.p_cccd_md = &cccd_md;
	char_md.char_props.notify = 0;
	char_md.char_props.write = 0;
	char_md.char_props.read = 0;
	char_md.char_props.indicate = 1;
	char_md.char_props.write_wo_resp = 0;
	char_md.p_char_pf = NULL;
	char_md.p_user_desc_md = NULL;
	char_md.p_sccd_md = NULL;

	attr_md.rd_auth = 0;
	attr_md.wr_auth = 0;
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;

	ble_uuid_t val_uuid;
	val_uuid.type = BLE_UUID_TYPE_BLE;
	val_uuid.uuid = MY_BLE_EEG_DATA_CHAR_UUID;

	attr_char_value.p_uuid = &val_uuid;
	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len=sizeof(uint8_t);
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = 20;

	sd_ble_gatts_characteristic_add(MyService.service_handle, &char_md, &attr_char_value,&MyService.indi_char_handle);
}







//add description
/*
static uint16_t add_char_desp(uint16_t char_handle, uint8_t *desp, uint8_t desp_len)
{
	uint32_t   err_code; // Variable to hold return codes from library and softdevice functions
    ble_gatts_attr_md_t    descr_params;
    memset(&descr_params, 0, sizeof(descr_params));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&descr_params.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&descr_params.write_perm);

    descr_params.vloc  = BLE_GATTS_VLOC_STACK;
    descr_params.rd_auth = 0;
    descr_params.wr_auth = 0;
    descr_params.vlen    = 0;
    
    ble_uuid_t          attr_uuid;
    attr_uuid.uuid      = BLE_UUID_DESCRIPTOR_CHAR_USER_DESC;
	attr_uuid.type		= BLE_UUID_TYPE_VENDOR_BEGIN;
//    ble_uuid128_t       base_uuid = {0x00, 0x00, 0xfa, 0xb2, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5f, 0x9b, 0x34, 0xfb}; // 128-bit base UUID
//    err_code = sd_ble_uuid_vs_add(&base_uuid, &attr_uuid.type);
//    APP_ERROR_CHECK(err_code); 
    
    
//    uint8_t attr_value[]  = "Your User description";
//    const uint16_t attr_len   = sizeof(attr_value);
    uint8_t *attr_value = desp;
	const uint16_t attr_len = desp_len;
	
    ble_gatts_attr_t    attr;
    memset(&attr, 0, sizeof(attr));
    
    attr.init_len       = attr_len;
    attr.max_len        = attr_len;
    attr.init_offs      = 0;
    attr.p_value        = attr_value;
    attr.p_attr_md      = &descr_params;
    attr.p_uuid         = &attr_uuid;
    uint16_t descr_handle;
    //err_code = sd_ble_gatts_descriptor_add(mringService.write_char_handle.value_handle, &attr, &descr_handle);
	err_code = sd_ble_gatts_descriptor_add(char_handle, &attr, &descr_handle);

	APP_ERROR_CHECK(err_code);

	return descr_handle;
}*/



