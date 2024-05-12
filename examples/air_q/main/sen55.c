#include "sen55.h"

/**
 * @brief 
 * 
 * @param dev 
 */
static inline void send_command( sen55_dev_st *dev )
{
    i2c_master_transmit(dev->dev_handle, (uint8_t*)(&dev->command), dev->cmd_len, -1);
}

/**
 * @brief 
 * 
 * @param dev 
 */
static inline void start_measure( sen55_dev_st *dev )
{
    dev->command = START_MEASURE;
    dev->cmd_len = 1;

    send_command(dev);
}

/**
 * @brief 
 * 
 * @param dev 
 */
static inline void stop_measure( sen55_dev_st *dev )
{
    dev->command = 0x104;
    dev->cmd_len = 2;

    send_command(dev);
}


/**
 * @brief 
 * 
 * @param dev 
 */
static inline void i2c_init( sen55_dev_st *dev )
{
    dev->i2c_mst_config.scl_io_num = dev->io_scl;
    dev->i2c_mst_config.scl_io_num = dev->io_sda;
    dev->i2c_mst_config.clk_source = I2C_CLK_SRC_DEFAULT;
    dev->i2c_mst_config.i2c_port = I2C_NUM_0;
    dev->i2c_mst_config.glitch_ignore_cnt = 7;
    dev->i2c_mst_config.flags.enable_internal_pullup = true;

    // Follow sen55 spec, page 14, chap 6 Operation and Communication through the I2C Interface.
    dev->dev_cfg.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    dev->dev_cfg.device_address = 0x69;
    dev->dev_cfg.scl_speed_hz = 100000;

    i2c_new_master_bus(&(dev->i2c_mst_config), &(dev->bus_handle));

    i2c_master_bus_add_device(dev->bus_handle, &(dev->dev_cfg), &(dev->dev_handle));
}

/**
 * @brief 
 * 
 * @param dev 
 */
static inline void hwlowlevel_init( sen55_dev_st *dev )
{
    i2c_init(dev);
}

/**
 * @brief 
 * 
 * @param io_scl 
 * @param io_sda 
 * @return sen55_dev* 
 */
sen55_dev_st *sen55_init( int io_scl, int io_sda )
{   
    sen55_dev_st *dev = (sen55_dev_st*)calloc(sizeof(sen55_dev_st), 1);
    if (!dev) {
        return NULL;
    }
    
    dev->io_scl = io_scl;
    dev->io_sda = io_sda;

    hwlowlevel_init(dev);


    return dev;
}
