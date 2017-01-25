/*
	psoc 
	
 */
#include "contiki.h"

#include "ti-lib.h"
#include "psoc.h"
#include"board-i2c.h"

/* Sensor selection/deselection */

#define SENSOR_SELECT()     board_i2c_select(BOARD_I2C_INTERFACE_0, PSOC_ADDR)
#define SENSOR_DESELECT()   board_i2c_deselect()

/*---------------------------------------------------------------------------*/
static bool success = true;
extern uint8_t int_flag;
/*---------------------------------------------------------------------------*/
// Private functions:
/*---------------------------------------------------------------------------*/
/**
 * \brief       Initialise the PSoC driver
 * \return      True if I2C operation successful
 */

bool
sensor_init(void)
{
  SENSOR_SELECT();
  // Check if the PSoC is available
  success = true;
  SENSOR_DESELECT();
  return success;
}

bool 
PS0C_read(uint8_t* value, uint8_t len) 
{
  bool valid;
  if(success){
    SENSOR_SELECT();
	// read data from PSoC
    success = board_i2c_read(value, len);
	SENSOR_DESELECT(); 
  }
	
  valid = success;
  if(success){
    printf("PSoC rd success ");
  }
  else{
    printf("PSoC rd success ");
  }
  success = true;
return valid;
}

bool
PSOC_write(uint8_t* value, uint8_t len) 
{
  bool valid;
  if(success){
  	SENSOR_SELECT();
	// Write data from PSoC
    success = board_i2c_write(value, len);
	SENSOR_DESELECT(); 
  }
  if(success){
    printf("PSoC wr success ");
  }
  else{
	printf("PSoC wr failed ");
  }
	
  valid = success;
  success = true;
	
return valid;
}

bool 
PSOC_write_read(uint8_t* wr_data, uint8_t* rd_data, uint8_t len)
{
  bool valid;
  success = PSOC_write(wr_data, len);
  
  printf("%d test ", int_flag);
  while(!int_flag){
  	printf("%d", int_flag);
  }
  
  if(int_flag && success){
  	success = PS0C_read(rd_data, len);
  }
  
  int_flag = 0;
  valid = success;
  success = true;
return valid;
}
