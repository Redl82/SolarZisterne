EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ESP8266
LIBS:wemos_mini
LIBS:SolarZisterne_PCB-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L WeMos_mini U?
U 1 1 59516611
P 9250 1800
F 0 "U?" H 9250 2300 60  0000 C CNN
F 1 "WeMos_mini" H 9250 1300 60  0000 C CNN
F 2 "" H 9800 1100 60  0000 C CNN
F 3 "" H 9800 1100 60  0000 C CNN
	1    9250 1800
	1    0    0    -1  
$EndComp
Text Notes 8250 950  0    60   ~ 0
Pins D5, D6, D7, D8 werden durch SD Karte beansprucht\nPins D2, D1 werden für I2C Sensoren benutzt\nweitere 3 Pins für MCP73871 Solar Charger\nweitere 2 Pins für Ultraschallsensor
NoConn ~ 9750 1850
NoConn ~ 9750 1750
NoConn ~ 9750 1650
NoConn ~ 9750 1550
Wire Wire Line
	8750 1950 8050 1950
Wire Wire Line
	8750 1850 8050 1850
Text Notes 7850 2000 0    60   ~ 0
SDA\nSCL
$Comp
L Jumper_NO_Small JP?
U 1 1 59516939
P 10000 2050
F 0 "JP?" H 10000 2130 50  0000 C CNN
F 1 "Jumper_NO_Small" H 10010 1990 50  0000 C CNN
F 2 "" H 10000 2050 50  0001 C CNN
F 3 "" H 10000 2050 50  0001 C CNN
	1    10000 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	10000 2150 9750 2150
Wire Wire Line
	10000 1950 9750 1950
$Comp
L MCP23008 U?
U 1 1 59516B77
P 6750 2000
F 0 "U?" H 6650 2625 50  0000 R CNN
F 1 "MCP23008" H 6650 2550 50  0000 R CNN
F 2 "" H 6800 1350 50  0001 L CNN
F 3 "" H 7000 2600 50  0001 C CNN
	1    6750 2000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
