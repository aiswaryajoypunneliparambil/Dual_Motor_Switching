/* 
 * File:   eeprom.h
 * Author: PO Joy
 *
 * Created on 26 June, 2021, 12:02 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include "Initialiazation.h"

void EEPROM_Write(int,char);		/* Write byte to EEPROM */
char EEPROM_Read(int);				/* Read byte From EEPROM */

int Data_read;

#endif	/* EEPROM_H */

