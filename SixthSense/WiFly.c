/*
 * WiFly.c
 *
 * Created: 3/3/2012 1:00:07 PM
 *  Author: Laptop
 */ 

#include "WiFly.h"
#include "main.h"

/*void WiFlyInit()
{
	
	enterCommandMode();
	flashLED(YELLOW);
	transmitCommand((unsigned char*)"set wlan ssid SixthSenseServer");
	transmitData((unsigned char*)"set wlan passphrase sixthsense");
	transmitCommand((unsigned char*)"set ftp address 192.168.1.1");
	transmitCommand((unsigned char*)"set ftp user root");
	transmitCommand((unsigned char*)"set ftp password admin");
	transmitCommand((unsigned char*)"save");
	transmitCommand((unsigned char*)"reboot");
}*/

void enterCommandMode()
{
	exitCommandMode();
	endLine();
	print((unsigned char*)"$$$");
	endLine();
}

void exitCommandMode()
{
	endLine();
	println((unsigned char*)"exit");
	
}

void endLine()
{
	print((unsigned char*)"\r\n");
	wait_avr(DELAY);
}

void println(unsigned char str[])
{
	print(str);
	endLine();
	
}

void print(unsigned char str[])
{
	int i;
	for (i = 0; i < strlen((char*)str); i++)
	{
		//write(str[i]);
		USART_Transmit(str[i]);
	}
	wait_avr(DELAY);
}

void printNoWait(unsigned char str[])
{
	int i;
	for (i = 0; i < strlen((char*)str); i++)
	{
		//write(str[i]);
		USART_Transmit(str[i]);
	}
}

void openFTP(unsigned char *filename)
{
	enterCommandMode();
	println((unsigned char*)"set comm close .txt");
	println((unsigned char*)"set ftp timer 480");
	printNoWait((unsigned char*) "ftp put ");
	println(filename);
	
	unsigned char temp = USART_Receive();
	while (temp != (unsigned char)'-') temp = USART_Receive();
}

void closeFTP()
{
	wait_avr(500);
	println((unsigned char*)".txt");
	exitCommandMode();
}