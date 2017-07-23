EESchema Schematic File Version 2
LIBS:SolarZisterne_PCB-rescue
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
LIBS:mcp73871
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
L WeMos_mini-RESCUE-SolarZisterne_PCB U3
U 1 1 59516611
P 2300 4350
F 0 "U3" H 2300 4850 60  0000 C CNN
F 1 "WeMos_mini" H 2300 3850 60  0000 C CNN
F 2 "wemos_d1_mini:D1_mini_board" H 2850 3650 60  0001 C CNN
F 3 "" H 2850 3650 60  0000 C CNN
	1    2300 4350
	1    0    0    -1  
$EndComp
Text Notes 1000 5550 0    60   ~ 0
Pins D5, D6, D7, D8 werden durch SD Karte benutzt\nPins D1, D2 für Ultraschallsensor\nPins D3, D4 werden für I2C Sensoren benutzt\nI2C brauch keine Pull-Up Wiederstand die sind\nschon bei den Temp. Sensoren drin.\n
NoConn ~ 2800 4400
NoConn ~ 2800 4300
NoConn ~ 2800 4200
NoConn ~ 2800 4100
$Comp
L Jumper_NO_Small JP1
U 1 1 59516939
P 3350 4600
F 0 "JP1" H 3350 4680 50  0000 C CNN
F 1 "Sleep" H 3360 4540 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3350 4600 50  0001 C CNN
F 3 "" H 3350 4600 50  0001 C CNN
	1    3350 4600
	0    1    1    0   
$EndComp
$Comp
L MCP23008 U4
U 1 1 59516B77
P 4850 4350
F 0 "U4" H 4750 4975 50  0000 R CNN
F 1 "MCP23008" H 4750 4900 50  0000 R CNN
F 2 "Housings_DIP:DIP-18_W7.62mm_LongPads" H 4900 3700 50  0001 L CNN
F 3 "" H 5100 4950 50  0001 C CNN
	1    4850 4350
	1    0    0    -1  
$EndComp
$Comp
L MCP73871 U2
U 1 1 5953F190
P 4400 2250
F 0 "U2" H 3950 3050 60  0000 C CNN
F 1 "MCP73871" H 4650 3050 60  0000 C CNN
F 2 "Housings_DFN_QFN:QFN-20-1EP_4x4mm_Pitch0.5mm" H 4150 2300 60  0001 C CNN
F 3 "" H 4150 2300 60  0000 C CNN
	1    4400 2250
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x02 J3
U 1 1 5953F3A3
P 850 1450
F 0 "J3" H 850 1700 50  0000 C TNN
F 1 "Solar" V 700 1450 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_2pol" H 850 1225 50  0001 C CNN
F 3 "" H 825 1450 50  0001 C CNN
	1    850  1450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5953F443
P 1150 1750
F 0 "#PWR01" H 1150 1500 50  0001 C CNN
F 1 "GND" H 1150 1600 50  0000 C CNN
F 2 "" H 1150 1750 50  0001 C CNN
F 3 "" H 1150 1750 50  0001 C CNN
	1    1150 1750
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D1
U 1 1 5953F534
P 1350 1350
F 0 "D1" H 1350 1450 50  0000 C CNN
F 1 "1N5817" H 1350 1250 50  0000 C CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 1350 1350 50  0001 C CNN
F 3 "" H 1350 1350 50  0001 C CNN
	1    1350 1350
	-1   0    0    1   
$EndComp
$Comp
L CP C1
U 1 1 5953F5FE
P 1700 1550
F 0 "C1" H 1725 1650 50  0000 L CNN
F 1 "4700uF" H 1725 1450 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D16.0mm_P7.50mm" H 1738 1400 50  0001 C CNN
F 3 "" H 1700 1550 50  0001 C CNN
	1    1700 1550
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5953F621
P 2050 1550
F 0 "C2" H 2075 1650 50  0000 L CNN
F 1 "10uF" H 2075 1450 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 2088 1400 50  0001 C CNN
F 3 "" H 2050 1550 50  0001 C CNN
	1    2050 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5953F67E
P 1700 1750
F 0 "#PWR02" H 1700 1500 50  0001 C CNN
F 1 "GND" H 1700 1600 50  0000 C CNN
F 2 "" H 1700 1750 50  0001 C CNN
F 3 "" H 1700 1750 50  0001 C CNN
	1    1700 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5953F6A2
P 2050 1750
F 0 "#PWR03" H 2050 1500 50  0001 C CNN
F 1 "GND" H 2050 1600 50  0000 C CNN
F 2 "" H 2050 1750 50  0001 C CNN
F 3 "" H 2050 1750 50  0001 C CNN
	1    2050 1750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR04
U 1 1 5953F76A
P 1700 1100
F 0 "#PWR04" H 1700 950 50  0001 C CNN
F 1 "VCC" H 1700 1250 50  0000 C CNN
F 2 "" H 1700 1100 50  0001 C CNN
F 3 "" H 1700 1100 50  0001 C CNN
	1    1700 1100
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 5953FC67
P 3550 1250
F 0 "#PWR05" H 3550 1100 50  0001 C CNN
F 1 "VCC" H 3550 1400 50  0000 C CNN
F 2 "" H 3550 1250 50  0001 C CNN
F 3 "" H 3550 1250 50  0001 C CNN
	1    3550 1250
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5953FCBF
P 3300 1000
F 0 "R1" V 3380 1000 50  0000 C CNN
F 1 "270K" V 3300 1000 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3230 1000 50  0001 C CNN
F 3 "" H 3300 1000 50  0001 C CNN
	1    3300 1000
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5953FD3B
P 3300 1400
F 0 "R2" V 3380 1400 50  0000 C CNN
F 1 "100K" V 3300 1400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3230 1400 50  0001 C CNN
F 3 "" H 3300 1400 50  0001 C CNN
	1    3300 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5953FD87
P 3300 1600
F 0 "#PWR06" H 3300 1350 50  0001 C CNN
F 1 "GND" H 3300 1450 50  0000 C CNN
F 2 "" H 3300 1600 50  0001 C CNN
F 3 "" H 3300 1600 50  0001 C CNN
	1    3300 1600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 5953FDBA
P 3300 750
F 0 "#PWR07" H 3300 600 50  0001 C CNN
F 1 "VCC" H 3300 900 50  0000 C CNN
F 2 "" H 3300 750 50  0001 C CNN
F 3 "" H 3300 750 50  0001 C CNN
	1    3300 750 
	1    0    0    -1  
$EndComp
Text Label 2850 1900 0    60   ~ 0
PG
Text Label 2850 2000 0    60   ~ 0
STAT2
Text Label 2850 2100 0    60   ~ 0
STAT1
$Comp
L VCC #PWR08
U 1 1 5954001C
P 3400 2200
F 0 "#PWR08" H 3400 2050 50  0001 C CNN
F 1 "VCC" H 3400 2350 50  0000 C CNN
F 2 "" H 3400 2200 50  0001 C CNN
F 3 "" H 3400 2200 50  0001 C CNN
	1    3400 2200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR09
U 1 1 59540201
P 4850 2900
F 0 "#PWR09" H 4850 2650 50  0001 C CNN
F 1 "GND" H 4850 2750 50  0000 C CNN
F 2 "" H 4850 2900 50  0001 C CNN
F 3 "" H 4850 2900 50  0001 C CNN
	1    4850 2900
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 59540417
P 5750 2550
F 0 "R5" V 5830 2550 50  0000 C CNN
F 1 "1K" V 5750 2550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5680 2550 50  0001 C CNN
F 3 "" H 5750 2550 50  0001 C CNN
	1    5750 2550
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 59540679
P 5500 2550
F 0 "R4" V 5580 2550 50  0000 C CNN
F 1 "100K" V 5500 2550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5430 2550 50  0001 C CNN
F 3 "" H 5500 2550 50  0001 C CNN
	1    5500 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 595406BF
P 5500 2900
F 0 "#PWR010" H 5500 2650 50  0001 C CNN
F 1 "GND" H 5500 2750 50  0000 C CNN
F 2 "" H 5500 2900 50  0001 C CNN
F 3 "" H 5500 2900 50  0001 C CNN
	1    5500 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 595406EE
P 5750 2900
F 0 "#PWR011" H 5750 2650 50  0001 C CNN
F 1 "GND" H 5750 2750 50  0000 C CNN
F 2 "" H 5750 2900 50  0001 C CNN
F 3 "" H 5750 2900 50  0001 C CNN
	1    5750 2900
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 59540928
P 5900 2100
F 0 "R3" V 5980 2100 50  0000 C CNN
F 1 "220" V 5900 2100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5830 2100 50  0001 C CNN
F 3 "" H 5900 2100 50  0001 C CNN
	1    5900 2100
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 595409CE
P 6150 2550
F 0 "R6" V 6230 2550 50  0000 C CNN
F 1 "150K" V 6150 2550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6080 2550 50  0001 C CNN
F 3 "" H 6150 2550 50  0001 C CNN
	1    6150 2550
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 59540A46
P 6350 2550
F 0 "R7" V 6430 2550 50  0000 C CNN
F 1 "10K" V 6350 2550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6280 2550 50  0001 C CNN
F 3 "" H 6350 2550 50  0001 C CNN
	1    6350 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 59540A97
P 6150 2900
F 0 "#PWR012" H 6150 2650 50  0001 C CNN
F 1 "GND" H 6150 2750 50  0000 C CNN
F 2 "" H 6150 2900 50  0001 C CNN
F 3 "" H 6150 2900 50  0001 C CNN
	1    6150 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 59540ACF
P 6350 2900
F 0 "#PWR013" H 6350 2650 50  0001 C CNN
F 1 "GND" H 6350 2750 50  0000 C CNN
F 2 "" H 6350 2900 50  0001 C CNN
F 3 "" H 6350 2900 50  0001 C CNN
	1    6350 2900
	1    0    0    -1  
$EndComp
Text Notes 5800 3300 0    60   ~ 0
Nochmal Checken bei welcher Temp\ndas Laden unterbraochen wird!\n
$Comp
L Screw_Terminal_1x02 J4
U 1 1 59541EB9
P 7150 2000
F 0 "J4" H 7150 2250 50  0000 C TNN
F 1 "Akku" V 7000 2000 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_2pol" H 7150 1775 50  0001 C CNN
F 3 "" H 7125 2000 50  0001 C CNN
	1    7150 2000
	-1   0    0    1   
$EndComp
$Comp
L C C5
U 1 1 5954258E
P 6550 2050
F 0 "C5" H 6575 2150 50  0000 L CNN
F 1 "10uF" H 6575 1950 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 6588 1900 50  0001 C CNN
F 3 "" H 6550 2050 50  0001 C CNN
	1    6550 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 595425EA
P 6550 2250
F 0 "#PWR015" H 6550 2000 50  0001 C CNN
F 1 "GND" H 6550 2100 50  0000 C CNN
F 2 "" H 6550 2250 50  0001 C CNN
F 3 "" H 6550 2250 50  0001 C CNN
	1    6550 2250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR016
U 1 1 59544F20
P 2950 3900
F 0 "#PWR016" H 2950 3750 50  0001 C CNN
F 1 "+3.3V" H 2950 4040 50  0000 C CNN
F 2 "" H 2950 3900 50  0001 C CNN
F 3 "" H 2950 3900 50  0001 C CNN
	1    2950 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 595451B9
P 1300 4150
F 0 "#PWR017" H 1300 3900 50  0001 C CNN
F 1 "GND" H 1300 4000 50  0000 C CNN
F 2 "" H 1300 4150 50  0001 C CNN
F 3 "" H 1300 4150 50  0001 C CNN
	1    1300 4150
	1    0    0    -1  
$EndComp
NoConn ~ 1800 4600
NoConn ~ 1800 4700
NoConn ~ 1800 4000
$Comp
L CONN_01X06-RESCUE-SolarZisterne_PCB J1
U 1 1 59546730
P 2400 1000
F 0 "J1" H 2400 1350 50  0000 C CNN
F 1 "Erzeugung" V 2500 1000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 2400 1000 50  0001 C CNN
F 3 "" H 2400 1000 50  0001 C CNN
	1    2400 1000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5954691E
P 1850 900
F 0 "#PWR018" H 1850 650 50  0001 C CNN
F 1 "GND" H 1850 750 50  0000 C CNN
F 2 "" H 1850 900 50  0001 C CNN
F 3 "" H 1850 900 50  0001 C CNN
	1    1850 900 
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR019
U 1 1 59547AC5
P 2150 700
F 0 "#PWR019" H 2150 550 50  0001 C CNN
F 1 "+3.3V" H 2150 840 50  0000 C CNN
F 2 "" H 2150 700 50  0001 C CNN
F 3 "" H 2150 700 50  0001 C CNN
	1    2150 700 
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06-RESCUE-SolarZisterne_PCB J2
U 1 1 59547D30
P 6700 1250
F 0 "J2" H 6700 1600 50  0000 C CNN
F 1 "Verbrauch" V 6800 1250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 6700 1250 50  0001 C CNN
F 3 "" H 6700 1250 50  0001 C CNN
	1    6700 1250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR020
U 1 1 595489A4
P 6450 950
F 0 "#PWR020" H 6450 800 50  0001 C CNN
F 1 "+3.3V" H 6450 1090 50  0000 C CNN
F 2 "" H 6450 950 50  0001 C CNN
F 3 "" H 6450 950 50  0001 C CNN
	1    6450 950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 59548AB7
P 5850 1150
F 0 "#PWR021" H 5850 900 50  0001 C CNN
F 1 "GND" H 5850 1000 50  0000 C CNN
F 2 "" H 5850 1150 50  0001 C CNN
F 3 "" H 5850 1150 50  0001 C CNN
	1    5850 1150
	1    0    0    -1  
$EndComp
Text Label 1500 4400 0    60   ~ 0
Trig
Text Label 1500 4500 0    60   ~ 0
Echo
Text Label 1500 4200 0    60   ~ 0
SCL
Text Label 1500 4300 0    60   ~ 0
SDA
Text Label 4000 4150 0    60   ~ 0
STAT2
Text Label 4000 4250 0    60   ~ 0
STAT1
Text Label 5450 4350 0    60   ~ 0
SCL
Text Label 5450 4450 0    60   ~ 0
SDA
$Comp
L +3.3V #PWR022
U 1 1 5954B7EF
P 4850 3650
F 0 "#PWR022" H 4850 3500 50  0001 C CNN
F 1 "+3.3V" H 4850 3790 50  0000 C CNN
F 2 "" H 4850 3650 50  0001 C CNN
F 3 "" H 4850 3650 50  0001 C CNN
	1    4850 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5954B8BD
P 4850 5150
F 0 "#PWR023" H 4850 4900 50  0001 C CNN
F 1 "GND" H 4850 5000 50  0000 C CNN
F 2 "" H 4850 5150 50  0001 C CNN
F 3 "" H 4850 5150 50  0001 C CNN
	1    4850 5150
	1    0    0    -1  
$EndComp
NoConn ~ 5350 4050
Text Notes 4300 5500 0    60   ~ 0
Schaltung im BB überprüfen
Text Notes 7250 900  0    60   ~ 0
Vielleciht noch gegen Buck \nConverter austauschen
Text Label 2000 950  0    60   ~ 0
SCL
Text Label 2000 1050 0    60   ~ 0
SDA
Text Label 6300 1200 0    60   ~ 0
SCL
Text Label 6300 1300 0    60   ~ 0
SDA
$Comp
L Screw_Terminal_1x04 J5
U 1 1 5954D9DF
P 6600 4350
F 0 "J5" H 6600 4800 50  0000 C TNN
F 1 "Ultraschall Sensor" V 6450 4350 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_4pol" H 6600 3925 50  0001 C CNN
F 3 "" H 6575 4550 50  0001 C CNN
	1    6600 4350
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR024
U 1 1 5954DD9B
P 6300 3950
F 0 "#PWR024" H 6300 3800 50  0001 C CNN
F 1 "+3.3V" H 6300 4090 50  0000 C CNN
F 2 "" H 6300 3950 50  0001 C CNN
F 3 "" H 6300 3950 50  0001 C CNN
	1    6300 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 5954DDEB
P 6300 4750
F 0 "#PWR025" H 6300 4500 50  0001 C CNN
F 1 "GND" H 6300 4600 50  0000 C CNN
F 2 "" H 6300 4750 50  0001 C CNN
F 3 "" H 6300 4750 50  0001 C CNN
	1    6300 4750
	1    0    0    -1  
$EndComp
Text Label 6150 4250 0    60   ~ 0
Trig
Text Label 6150 4450 0    60   ~ 0
Echo
$Comp
L CONN_01X10 J8
U 1 1 5954FE39
P 10850 4400
F 0 "J8" H 10850 4950 50  0000 C CNN
F 1 "Erweiterung" V 10950 4400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10_Pitch2.54mm" H 10850 4400 50  0001 C CNN
F 3 "" H 10850 4400 50  0001 C CNN
	1    10850 4400
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR026
U 1 1 5955031D
P 10600 3900
F 0 "#PWR026" H 10600 3750 50  0001 C CNN
F 1 "+3.3V" H 10600 4040 50  0000 C CNN
F 2 "" H 10600 3900 50  0001 C CNN
F 3 "" H 10600 3900 50  0001 C CNN
	1    10600 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 59550430
P 10600 4900
F 0 "#PWR027" H 10600 4650 50  0001 C CNN
F 1 "GND" H 10600 4750 50  0000 C CNN
F 2 "" H 10600 4900 50  0001 C CNN
F 3 "" H 10600 4900 50  0001 C CNN
	1    10600 4900
	1    0    0    -1  
$EndComp
Text Label 10350 4050 0    60   ~ 0
SDA
Text Label 10350 4150 0    60   ~ 0
SCL
Text Label 10350 4250 0    60   ~ 0
Analog1
Text Label 10350 4350 0    60   ~ 0
GPB3
Text Label 10350 4450 0    60   ~ 0
GPB4
Text Label 10350 4550 0    60   ~ 0
GPB5
Text Label 10350 4650 0    60   ~ 0
GPB6
Text Label 10250 4750 0    60   ~ 0
GPB7
Text Label 4000 4350 0    60   ~ 0
GPB3
Text Label 4000 4450 0    60   ~ 0
GPB4
Text Label 4000 4550 0    60   ~ 0
GPB5
Text Label 4000 4650 0    60   ~ 0
GPB6
Text Label 4000 4750 0    60   ~ 0
GPB7
Text Label 2850 4600 0    60   ~ 0
Analog1
Text Label 4000 4050 0    60   ~ 0
PG
$Comp
L Screw_Terminal_1x04 J6
U 1 1 5956BB47
P 7500 4350
F 0 "J6" H 7500 4800 50  0000 C TNN
F 1 "Externer Temperatur Sensor" V 7350 4350 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_4pol" H 7500 3925 50  0001 C CNN
F 3 "" H 7475 4550 50  0001 C CNN
	1    7500 4350
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR028
U 1 1 5956BC5D
P 7200 3950
F 0 "#PWR028" H 7200 3800 50  0001 C CNN
F 1 "+3.3V" H 7200 4090 50  0000 C CNN
F 2 "" H 7200 3950 50  0001 C CNN
F 3 "" H 7200 3950 50  0001 C CNN
	1    7200 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 5956BCB3
P 6900 4300
F 0 "#PWR029" H 6900 4050 50  0001 C CNN
F 1 "GND" H 6900 4150 50  0000 C CNN
F 2 "" H 6900 4300 50  0001 C CNN
F 3 "" H 6900 4300 50  0001 C CNN
	1    6900 4300
	1    0    0    -1  
$EndComp
Text Label 7050 4450 0    60   ~ 0
SCL
Text Label 7050 4650 0    60   ~ 0
SDA
$Comp
L +3.3V #PWR030
U 1 1 5956C1F1
P 7850 4050
F 0 "#PWR030" H 7850 3900 50  0001 C CNN
F 1 "+3.3V" H 7850 4190 50  0000 C CNN
F 2 "" H 7850 4050 50  0001 C CNN
F 3 "" H 7850 4050 50  0001 C CNN
	1    7850 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR031
U 1 1 5956C24A
P 7950 4300
F 0 "#PWR031" H 7950 4050 50  0001 C CNN
F 1 "GND" H 7950 4150 50  0000 C CNN
F 2 "" H 7950 4300 50  0001 C CNN
F 3 "" H 7950 4300 50  0001 C CNN
	1    7950 4300
	1    0    0    -1  
$EndComp
Text Label 8050 4350 0    60   ~ 0
SCL
Text Label 8050 4450 0    60   ~ 0
SDA
$Comp
L PWR_FLAG #FLG032
U 1 1 59581FAF
P 10750 800
F 0 "#FLG032" H 10750 875 50  0001 C CNN
F 1 "PWR_FLAG" H 10750 950 50  0000 C CNN
F 2 "" H 10750 800 50  0001 C CNN
F 3 "" H 10750 800 50  0001 C CNN
	1    10750 800 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR033
U 1 1 59582029
P 10750 900
F 0 "#PWR033" H 10750 650 50  0001 C CNN
F 1 "GND" H 10750 750 50  0000 C CNN
F 2 "" H 10750 900 50  0001 C CNN
F 3 "" H 10750 900 50  0001 C CNN
	1    10750 900 
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 J7
U 1 1 5973EB30
P 8550 4400
F 0 "J7" H 8550 4750 50  0000 C CNN
F 1 "Interner Temperatur Sensor" V 8650 4400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 8550 4400 50  0001 C CNN
F 3 "" H 8550 4400 50  0001 C CNN
	1    8550 4400
	1    0    0    -1  
$EndComp
NoConn ~ 8350 4550
$Comp
L GS2 J13
U 1 1 5973EDF2
P 10250 4950
F 0 "J13" H 10350 5100 50  0000 C CNN
F 1 "GS2" H 10350 4801 50  0000 C CNN
F 2 "Connectors:GS2" V 10324 4950 50  0001 C CNN
F 3 "" H 10250 4950 50  0001 C CNN
	1    10250 4950
	1    0    0    -1  
$EndComp
$Comp
L GS2 J12
U 1 1 5973EF60
P 9950 4950
F 0 "J12" H 10050 5100 50  0000 C CNN
F 1 "GS2" H 10050 4801 50  0000 C CNN
F 2 "Connectors:GS2" V 10024 4950 50  0001 C CNN
F 3 "" H 9950 4950 50  0001 C CNN
	1    9950 4950
	1    0    0    -1  
$EndComp
$Comp
L GS2 J11
U 1 1 5973EFC6
P 9650 4950
F 0 "J11" H 9750 5100 50  0000 C CNN
F 1 "GS2" H 9750 4801 50  0000 C CNN
F 2 "Connectors:GS2" V 9724 4950 50  0001 C CNN
F 3 "" H 9650 4950 50  0001 C CNN
	1    9650 4950
	1    0    0    -1  
$EndComp
$Comp
L GS2 J10
U 1 1 5973F052
P 9300 4950
F 0 "J10" H 9400 5100 50  0000 C CNN
F 1 "GS2" H 9400 4801 50  0000 C CNN
F 2 "Connectors:GS2" V 9374 4950 50  0001 C CNN
F 3 "" H 9300 4950 50  0001 C CNN
	1    9300 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 5973F0E8
P 10250 5150
F 0 "#PWR034" H 10250 4900 50  0001 C CNN
F 1 "GND" H 10250 5000 50  0000 C CNN
F 2 "" H 10250 5150 50  0001 C CNN
F 3 "" H 10250 5150 50  0001 C CNN
	1    10250 5150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 5973F14D
P 9950 5150
F 0 "#PWR035" H 9950 4900 50  0001 C CNN
F 1 "GND" H 9950 5000 50  0000 C CNN
F 2 "" H 9950 5150 50  0001 C CNN
F 3 "" H 9950 5150 50  0001 C CNN
	1    9950 5150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR036
U 1 1 5973F1B2
P 9650 5150
F 0 "#PWR036" H 9650 4900 50  0001 C CNN
F 1 "GND" H 9650 5000 50  0000 C CNN
F 2 "" H 9650 5150 50  0001 C CNN
F 3 "" H 9650 5150 50  0001 C CNN
	1    9650 5150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 5973F217
P 9300 5150
F 0 "#PWR037" H 9300 4900 50  0001 C CNN
F 1 "GND" H 9300 5000 50  0000 C CNN
F 2 "" H 9300 5150 50  0001 C CNN
F 3 "" H 9300 5150 50  0001 C CNN
	1    9300 5150
	1    0    0    -1  
$EndComp
$Comp
L GS2 J9
U 1 1 5973F52B
P 8950 4950
F 0 "J9" H 9050 5100 50  0000 C CNN
F 1 "GS2" H 9050 4801 50  0000 C CNN
F 2 "Connectors:GS2" V 9024 4950 50  0001 C CNN
F 3 "" H 8950 4950 50  0001 C CNN
	1    8950 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 5973F59A
P 8950 5150
F 0 "#PWR038" H 8950 4900 50  0001 C CNN
F 1 "GND" H 8950 5000 50  0000 C CNN
F 2 "" H 8950 5150 50  0001 C CNN
F 3 "" H 8950 5150 50  0001 C CNN
	1    8950 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4500 1500 4500
Wire Wire Line
	1500 4400 1800 4400
Wire Wire Line
	3350 4700 2800 4700
Wire Wire Line
	3350 4500 2800 4500
Wire Wire Line
	1150 1750 1150 1550
Wire Wire Line
	1150 1550 1050 1550
Wire Wire Line
	1200 1350 1050 1350
Wire Wire Line
	1500 1350 2050 1350
Wire Wire Line
	1700 1350 1700 1400
Wire Wire Line
	2050 1250 2050 1400
Connection ~ 1700 1350
Wire Wire Line
	1700 1750 1700 1700
Wire Wire Line
	2050 1750 2050 1700
Connection ~ 2050 1350
Wire Wire Line
	3550 1250 3550 1700
Wire Wire Line
	3550 1600 3700 1600
Wire Wire Line
	3550 1700 3700 1700
Connection ~ 3550 1600
Wire Wire Line
	3300 750  3300 850 
Wire Wire Line
	3300 1150 3300 1250
Wire Wire Line
	3300 1550 3300 1600
Wire Wire Line
	3700 1800 3450 1800
Wire Wire Line
	3450 1800 3450 1200
Wire Wire Line
	3450 1200 3300 1200
Connection ~ 3300 1200
Wire Wire Line
	3700 1900 2850 1900
Wire Wire Line
	3700 2000 2850 2000
Wire Wire Line
	3700 2100 2850 2100
Wire Wire Line
	3400 2200 3700 2200
Wire Wire Line
	3700 2300 3550 2300
Wire Wire Line
	3550 2200 3550 2500
Connection ~ 3550 2200
Wire Wire Line
	3550 2400 3700 2400
Connection ~ 3550 2300
Wire Wire Line
	3550 2500 3700 2500
Connection ~ 3550 2400
Wire Wire Line
	5100 2850 4400 2850
Wire Wire Line
	4850 2850 4850 2900
Wire Wire Line
	5050 2500 5100 2500
Wire Wire Line
	5100 2400 5100 2850
Connection ~ 4850 2850
Wire Wire Line
	5050 2400 5100 2400
Connection ~ 5100 2500
Wire Wire Line
	4400 2850 4400 2800
Wire Wire Line
	5500 2700 5500 2900
Wire Wire Line
	5500 2400 5500 2300
Wire Wire Line
	5500 2300 5050 2300
Wire Wire Line
	5750 2400 5750 2200
Wire Wire Line
	5750 2200 5050 2200
Wire Wire Line
	5750 2900 5750 2700
Wire Wire Line
	5050 2100 5750 2100
Wire Wire Line
	6050 2100 6350 2100
Wire Wire Line
	6150 2100 6150 2400
Wire Wire Line
	6350 2100 6350 2400
Connection ~ 6150 2100
Wire Wire Line
	6150 2700 6150 2900
Wire Wire Line
	6350 2700 6350 2900
Wire Wire Line
	6550 2250 6550 2200
Wire Wire Line
	5050 1800 6800 1800
Wire Wire Line
	5050 1900 5150 1900
Wire Wire Line
	5150 1800 5150 2000
Connection ~ 5150 1800
Wire Wire Line
	5150 2000 5050 2000
Connection ~ 5150 1900
Wire Wire Line
	6550 1900 6550 1800
Connection ~ 6550 1800
Wire Wire Line
	5050 1600 6500 1600
Wire Wire Line
	6800 1600 7600 1600
Wire Wire Line
	5050 1700 5150 1700
Wire Wire Line
	5150 1700 5150 1600
Connection ~ 5150 1600
Wire Wire Line
	2950 3900 2950 4000
Wire Wire Line
	2950 4000 2800 4000
Wire Wire Line
	1300 4100 1300 4150
Wire Wire Line
	2050 1250 2200 1250
Wire Wire Line
	2200 1150 1700 1150
Wire Wire Line
	1700 1150 1700 1100
Wire Wire Line
	2200 850  1850 850 
Wire Wire Line
	1850 850  1850 900 
Wire Wire Line
	2200 750  2150 750 
Wire Wire Line
	2150 750  2150 700 
Wire Wire Line
	6500 1600 6500 1500
Wire Wire Line
	6500 1400 6350 1400
Wire Wire Line
	6350 1400 6350 1700
Wire Wire Line
	6350 1700 6800 1700
Wire Wire Line
	6800 1700 6800 1600
Wire Wire Line
	6500 1000 6450 1000
Wire Wire Line
	6450 1000 6450 950 
Wire Wire Line
	6500 1100 5850 1100
Wire Wire Line
	5850 1100 5850 1150
Wire Wire Line
	1800 4300 1500 4300
Wire Wire Line
	1800 4200 1500 4200
Wire Wire Line
	4350 4050 4000 4050
Wire Wire Line
	4350 4150 4000 4150
Wire Wire Line
	4350 4250 4000 4250
Wire Wire Line
	5350 4350 5450 4350
Wire Wire Line
	5350 4450 5450 4450
Wire Wire Line
	4850 3650 4850 3750
Wire Wire Line
	4850 5050 4850 5150
Wire Wire Line
	5400 4850 5350 4850
Wire Wire Line
	5400 4650 5400 5100
Wire Wire Line
	5400 5100 4850 5100
Connection ~ 4850 5100
Wire Wire Line
	5350 4750 5400 4750
Connection ~ 5400 4850
Wire Wire Line
	5350 4650 5400 4650
Connection ~ 5400 4750
Wire Wire Line
	5350 3950 5400 3950
Wire Wire Line
	5400 3950 5400 3700
Wire Wire Line
	5400 3700 4850 3700
Connection ~ 4850 3700
Wire Wire Line
	2200 950  2000 950 
Wire Wire Line
	2200 1050 2000 1050
Wire Wire Line
	6500 1200 6300 1200
Wire Wire Line
	6500 1300 6300 1300
Wire Wire Line
	6400 4250 6150 4250
Wire Wire Line
	6400 4450 6150 4450
Wire Wire Line
	6400 4650 6300 4650
Wire Wire Line
	6300 4650 6300 4750
Wire Wire Line
	6400 4050 6300 4050
Wire Wire Line
	6300 4050 6300 3950
Wire Wire Line
	10650 4750 10250 4750
Wire Wire Line
	9950 4650 10650 4650
Wire Wire Line
	9650 4550 10650 4550
Wire Wire Line
	9300 4450 10650 4450
Wire Wire Line
	8950 4350 10650 4350
Wire Wire Line
	10650 4250 10350 4250
Wire Wire Line
	10650 4150 10350 4150
Wire Wire Line
	10650 4050 10350 4050
Wire Wire Line
	10650 3950 10600 3950
Wire Wire Line
	10600 3950 10600 3900
Wire Wire Line
	10650 4850 10600 4850
Wire Wire Line
	10600 4850 10600 4900
Wire Wire Line
	4350 4350 4000 4350
Wire Wire Line
	4350 4450 4000 4450
Wire Wire Line
	4350 4550 4000 4550
Wire Wire Line
	4350 4650 4000 4650
Wire Wire Line
	4350 4750 4000 4750
Wire Wire Line
	2800 4600 2850 4600
Wire Wire Line
	7300 4250 6900 4250
Wire Wire Line
	6900 4250 6900 4300
Wire Wire Line
	7300 4050 7200 4050
Wire Wire Line
	7200 4050 7200 3950
Wire Wire Line
	7300 4450 7050 4450
Wire Wire Line
	7300 4650 7050 4650
Wire Wire Line
	8350 4250 7950 4250
Wire Wire Line
	7950 4250 7950 4300
Wire Wire Line
	8350 4150 7850 4150
Wire Wire Line
	7850 4050 7850 4650
Wire Wire Line
	8350 4350 8050 4350
Wire Wire Line
	8350 4450 8050 4450
Wire Wire Line
	1800 4100 1300 4100
Wire Wire Line
	10750 900  10750 800 
Wire Wire Line
	7850 4650 8350 4650
Connection ~ 7850 4150
Wire Wire Line
	9950 4650 9950 4750
Wire Wire Line
	9650 4550 9650 4750
Wire Wire Line
	9300 4450 9300 4750
Wire Wire Line
	8950 4350 8950 4750
$Comp
L CONN_01X04 J14
U 1 1 5974EB50
P 7800 1550
F 0 "J14" H 7800 1800 50  0000 C CNN
F 1 "Buck-Conv D24V5F3" V 7900 1550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 7800 1550 50  0001 C CNN
F 3 "" H 7800 1550 50  0001 C CNN
	1    7800 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 5974ECAC
P 7500 1800
F 0 "#PWR039" H 7500 1550 50  0001 C CNN
F 1 "GND" H 7500 1650 50  0000 C CNN
F 2 "" H 7500 1800 50  0001 C CNN
F 3 "" H 7500 1800 50  0001 C CNN
	1    7500 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1700 7600 1700
Wire Wire Line
	7500 1500 7500 1800
Wire Wire Line
	7600 1500 7500 1500
Connection ~ 7500 1700
$Comp
L +3.3V #PWR040
U 1 1 5974EF13
P 7500 1300
F 0 "#PWR040" H 7500 1150 50  0001 C CNN
F 1 "+3.3V" H 7500 1440 50  0000 C CNN
F 2 "" H 7500 1300 50  0001 C CNN
F 3 "" H 7500 1300 50  0001 C CNN
	1    7500 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1400 7500 1400
Wire Wire Line
	7500 1400 7500 1300
Wire Wire Line
	6800 1800 6800 2100
Wire Wire Line
	6800 2100 6950 2100
Wire Wire Line
	6900 1700 6900 1900
Wire Wire Line
	6900 1900 6950 1900
$EndSCHEMATC
