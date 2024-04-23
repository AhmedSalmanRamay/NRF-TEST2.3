
#include "ble_cus.h"


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_cus       Custom service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    ble_cus_evt_t                 evt;

  
    // writing to the accel characteristic (cccd)
     if (p_evt_write->handle == p_cus->accel_level_char_handles.cccd_handle)
   {
      if (ble_srv_is_notification_enabled(p_evt_write->data))
      {
          evt.evt_type = BLE_ACCEL_LEVEL_CHAR_NOTIFICATIONS_ENABLED;
      }
      else
      {
          evt.evt_type = BLE_ACCEL_LEVEL_CHAR_NOTIFICATIONS_DISABLED;
      }

      p_cus->evt_handler(p_cus, &evt);
   }
   // writing to the accel characteristic (cccd)
     if (p_evt_write->handle == p_cus->accel1_level_char_handles.cccd_handle)
   {
      if (ble_srv_is_notification_enabled(p_evt_write->data))
      {
          evt.evt_type = BLE_ACCEL1_LEVEL_CHAR_NOTIFICATIONS_ENABLED;
      }
      else
      {
          evt.evt_type = BLE_ACCEL1_LEVEL_CHAR_NOTIFICATIONS_DISABLED;
      }

      p_cus->evt_handler(p_cus, &evt);
   }
    // writing to the accel characteristic (cccd)
     if (p_evt_write->handle == p_cus->accel2_level_char_handles.cccd_handle)
   {
      if (ble_srv_is_notification_enabled(p_evt_write->data))
      {
          evt.evt_type = BLE_ACCEL2_LEVEL_CHAR_NOTIFICATIONS_ENABLED;
      }
      else
      {
          evt.evt_type = BLE_ACCEL2_LEVEL_CHAR_NOTIFICATIONS_DISABLED;
      }

      p_cus->evt_handler(p_cus, &evt);
   }
}


/**@brief Function for handling the Custom servie ble events.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_cus_t * p_cus = (ble_cus_t *) p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_WRITE:
            on_write(p_cus, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}



uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init )
{

    uint32_t                  err_code;
    ble_uuid_t                ble_uuid;
    ble_add_char_params_t     add_char_params;

/* Adding the service */

    // Initialize service structure.
    p_cus->evt_handler               = p_cus_init->evt_handler;
    p_cus->conn_handle               = BLE_CONN_HANDLE_INVALID;

    // Add the Custom ble Service UUID
    ble_uuid128_t base_uuid =  CUS_SERVICE_UUID_BASE;
    err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_cus->uuid_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = CUS_SERVICE_UUID;

    // Add the service to the database
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_cus->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

/* Adding the service characteristics */

  
    // Add the acce characteristic.
//uint16_t leng;
    uint8_t acc_char_init_value [] = {};

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = ACCEL_LEVEL_CHAR_UUID;
    add_char_params.uuid_type         = p_cus->uuid_type;

    add_char_params.init_len          =1 ;// (in bytes)
    add_char_params.max_len           =1;
    add_char_params.p_init_value      = acc_char_init_value;

    add_char_params.char_props.read   = 1;
    add_char_params.char_props.notify = 1;

    add_char_params.read_access       = SEC_OPEN;
    add_char_params.cccd_write_access = SEC_OPEN;

    err_code = characteristic_add(p_cus->service_handle,
                                  &add_char_params,
                                  &p_cus->accel_level_char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    /////

       // Add the acce characteristic.
//uint16_t leng;
    uint8_t acc1_char_init_value [] = {};

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = ACCEL1_LEVEL_CHAR_UUID;
    add_char_params.uuid_type         = p_cus->uuid_type;

    add_char_params.init_len          =1 ;// (in bytes)
    add_char_params.max_len           =1;
    add_char_params.p_init_value      = acc1_char_init_value;

    add_char_params.char_props.read   = 1;
    add_char_params.char_props.notify = 1;

    add_char_params.read_access       = SEC_OPEN;
    add_char_params.cccd_write_access = SEC_OPEN;

    err_code = characteristic_add(p_cus->service_handle,
                                  &add_char_params,
                                  &p_cus->accel1_level_char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
        // Add the acce characteristic.
//uint16_t leng;
    uint8_t acc2_char_init_value [] = {};

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = ACCEL2_LEVEL_CHAR_UUID;
    add_char_params.uuid_type         = p_cus->uuid_type;

    add_char_params.init_len          =1 ;// (in bytes)
    add_char_params.max_len           =1;
    add_char_params.p_init_value      = acc2_char_init_value;

    add_char_params.char_props.read   = 1;
    add_char_params.char_props.notify = 1;

    add_char_params.read_access       = SEC_OPEN;
    add_char_params.cccd_write_access = SEC_OPEN;

    err_code = characteristic_add(p_cus->service_handle,
                                  &add_char_params,
                                  &p_cus->accel2_level_char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}


uint32_t ble_cus_accel_level_update(ble_cus_t * p_cus,  uint8_t accel_level, uint16_t conn_handle)
{
    ble_gatts_hvx_params_t params;
    uint16_t len = sizeof(accel_level);

    memset(&params, 0, sizeof(params));
    params.type   = BLE_GATT_HVX_NOTIFICATION;
    params.handle = p_cus->accel_level_char_handles.value_handle;
    params.p_data = &accel_level;
    params.p_len  = &len;

    return sd_ble_gatts_hvx(conn_handle, &params);
}
uint32_t ble_cus_accel1_level_update(ble_cus_t * p_cus,  uint8_t accel_level, uint16_t conn_handle)
{
    ble_gatts_hvx_params_t params;
    uint16_t len = sizeof(accel_level);

    memset(&params, 0, sizeof(params));
    params.type   = BLE_GATT_HVX_NOTIFICATION;
    params.handle = p_cus->accel1_level_char_handles.value_handle;
    params.p_data = &accel_level;
    params.p_len  = &len;

    return sd_ble_gatts_hvx(conn_handle, &params);
}


uint32_t ble_cus_accel2_level_update(ble_cus_t * p_cus,  uint8_t accel_level, uint16_t conn_handle)
{
    ble_gatts_hvx_params_t params;
    uint16_t len = sizeof(accel_level);

    memset(&params, 0, sizeof(params));
    params.type   = BLE_GATT_HVX_NOTIFICATION;
    params.handle = p_cus->accel2_level_char_handles.value_handle;
    params.p_data = &accel_level;
    params.p_len  = &len;

    return sd_ble_gatts_hvx(conn_handle, &params);
}