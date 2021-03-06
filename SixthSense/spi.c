/*
 * spi.c
 *
 * Created: 1/28/2012 8:44:59 PM
 *  Author: Nikola
 */ 

#include <avr/io.h>
#include "spi.h"
#include "avr.h"

/*void startSPI(void)
{
	SPCR = 0x52;    // 01010010 - Master Mode, Enable SPI, Clock at Fosc/8
	SPSR = 0x00;    // Clear the status register
	
}

unsigned char SPI_transmit(unsigned char data)
{
	SPDR = data;
	
	while (!(SPSR & (1<<SPIF)));
	
	unsigned char out_data = SPDR;
	return data;
}

unsigned char SPI_receive(void)
{
	unsigned char data;
	
	SPDR = 0xff;
	
	while(!(SPSR & 0x80));
	data = SPDR;
	
	return data;
}*/

//code example for initializing SPI as master
void SPI_MasterInit(void)
{
	// Set SS, MOSI and SCK output, all others input
	// DDRB = (1 << DDB4) | (1 << DDB5) | (1 << DDB7); 
	DDRB |= 0xB0; // 1011 0000 -> 0xA0
	// enable SPI, Master, set the clock rate fck/16
	SPCR = 0x50; // 0101 0010 SPI Enabled, MSB transmitted first, Master Enabled, Fosc/16 (naturally) or Fosc/8 depending on SPI2x
	deselect();
	//flashSuccess();	
}
unsigned char SPI_MasterTransmit(char data)
{
	// start transmission
	SPDR = data;
	// wait for transmission to complete
	while (!(SPSR & 0x80));
	return SPDR;
	//flashSuccess();
}
// code example for initializing SPI as slave
void SPI_SlaveInit(void)
{
	// set MISO output, all others input
	// DDRB = (1 << DDB6);
	DDRB |= 0x40 ; // 0100 0000 -> 0x40
	// enable SPI
	SPCR = 0x61; // 0110 0001 SPI Enabled, MSB transmitted first, Fosc/16 (naturally) or Fosc/8 depending on SPI2x	
}
unsigned char SPI_SlaveReceive(void)
{
	unsigned char data;
	// wait for complete transmission
	while (!(SPSR & 0x80));
	// return data register
	data = SPDR;
	return data;
}

void select()
{
	CLR_BIT(PORTB, 4);
}

void deselect()
{
	SET_BIT(PORTB, 4);
}
