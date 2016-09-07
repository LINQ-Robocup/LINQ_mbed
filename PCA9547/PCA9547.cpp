/**
 *  PCA9547 library
 *
 *  @author  Tedd OKANO
 *  @version 0.2
 *  @date    Feb-2015
 *
 *  PCA9547: an I2C bus multiplexer control library
 *
 *  PCA9547 is an I2C multiplexer which enables to select 1:8 multiplexed I2C bus.
 *  The multiplexer is useful for deviding I2C bus to avoiding slave address conflict and separating capacitive loads.
 *
 *  For more information about PCA9547:
 *    http://www.nxp.com/documents/data_sheet/PCA9547.pdf
 *
 */

#include "PCA9547.h"

PCA9547::PCA9547( PinName sda, PinName scl, char i2c_address )
    : i2c_p( new I2C( sda, scl ) ), i2c( *i2c_p ), i2c_addr( i2c_address )
{
    //  do nothing.
    //  leave it in default state.
}

PCA9547::PCA9547( I2C &i2c_, char i2c_address )
    : i2c_p( NULL ), i2c( i2c_ ), i2c_addr( i2c_address )
{
    //  do nothing.
    //  leave it in default state.
}

PCA9547::~PCA9547()
{
    if ( NULL != i2c_p )
        delete  i2c_p;
}

void PCA9547::select( char channel )
{
    char    data    = 0x08 | channel;

    i2c.write( i2c_addr, &data, 1 );
}

void PCA9547::disable( void )
{
    char    data    = 0x00;

    i2c.write( i2c_addr, &data, 1 );
}
