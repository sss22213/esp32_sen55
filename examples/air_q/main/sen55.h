#ifndef __SEN55_H__
#define __SEN55_H__
#include <stdio.h>
#include <stdint.h>
#include "driver/i2c_master.h"

#define FAN_FAILURE 4
#define LASER_FAILURE   5
#define RHT_COMMUNICATION_ERROR 6
#define GAS_SENSOR_ERROR    7
#define FAN_CLEARNING_ACTIVE  19
#define FAN_IS_NOT_READY   20
#define FAN_SPEED   21

typedef struct {
    uint16_t pm1_0;
    uint16_t pm2_5;
    uint16_t pm4_0;
    uint16_t pm10;
    uint16_t humidity;
    uint16_t temperature;
    uint16_t voc;
    uint16_t nox;
} sen55_output_st;

typedef struct {
    i2c_master_bus_config_t i2c_mst_config;
    i2c_device_config_t dev_cfg;
    i2c_master_bus_handle_t bus_handle;
    i2c_master_dev_handle_t dev_handle;
    int io_scl;
    int io_sda;
    sen55_output_st sen55_output;
    uint16_t command;
    uint8_t cmd_len;
} sen55_dev_st;

typedef enum {
    START_MEASURE = 0x21,
    STOP_MEASURE = 0x104,
    READ_DATA_READY_FLAG = 0x202,
    READ_MEASURE_VALUE = 0x3c4,
    START_FAN_CLEARNING = 0x5607,
    READ_WRITE_TEMPERATURE = 0x60B,
    READ_WRITE_WARM_PARM = 0x60C6,
    READ_WRITE_AUTO_CLEARNING_INTERVAL = 0x8004,
    READ_PRODUCT_NAME = 0xD014,
    READ_SN = 0xD033,
    READ_FW_VERSION = 0xD100,
    READ_DEVICE_STATUS = 0xD206,
    CLEAR_DEVICE_STATUS = 0xD210,
    RESRT = 0xD304,
} sne55_cmd_e;  


#endif