EESchema Schematic File Version 4
EELAYER 30 0
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
L promicro:ProMicro U1
U 1 1 5DF4F12B
P 5500 3550
F 0 "U1" H 5500 4587 60  0000 C CNN
F 1 "ProMicro" H 5500 4481 60  0000 C CNN
F 2 "" H 5600 2500 60  0000 C CNN
F 3 "" H 5600 2500 60  0000 C CNN
	1    5500 3550
	1    0    0    -1  
$EndComp
$Comp
L personal_custom:TM1637-4Digit7SegmentDisplay U3
U 1 1 5DF553A2
P 2400 3250
F 0 "U3" H 2458 3365 50  0000 C CNN
F 1 "TM1637-4Digit7SegmentDisplay" H 2458 3274 50  0000 C CNN
F 2 "" H 2400 3350 50  0001 C CNN
F 3 "" H 2400 3350 50  0001 C CNN
	1    2400 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5DF56959
P 6650 3600
F 0 "D1" H 6643 3816 50  0000 C CNN
F 1 "LED" H 6643 3725 50  0000 C CNN
F 2 "" H 6650 3600 50  0001 C CNN
F 3 "~" H 6650 3600 50  0001 C CNN
	1    6650 3600
	-1   0    0    -1  
$EndComp
Text GLabel 6450 3100 2    50   Input ~ 0
VCC
Wire Wire Line
	6200 3100 6450 3100
Text GLabel 6450 2900 2    50   Input ~ 0
GND
Wire Wire Line
	6450 2900 6200 2900
Text GLabel 3750 1750 1    50   Input ~ 0
VCC
Text GLabel 3850 2850 3    50   Input ~ 0
GND
Wire Wire Line
	3850 2850 3850 2700
Wire Wire Line
	3750 1900 3750 1750
Wire Wire Line
	3350 2200 3250 2200
Text GLabel 2850 3800 3    50   Input ~ 0
VCC
Text GLabel 3000 3800 3    50   Input ~ 0
GND
Wire Wire Line
	2750 3700 2850 3700
Wire Wire Line
	2850 3700 2850 3800
Wire Wire Line
	2750 3600 3000 3600
Wire Wire Line
	3000 3600 3000 3800
$Comp
L Device:LED D2
U 1 1 5DF6C5B7
P 6650 4000
F 0 "D2" H 6643 4216 50  0000 C CNN
F 1 "LED" H 6643 4125 50  0000 C CNN
F 2 "" H 6650 4000 50  0001 C CNN
F 3 "~" H 6650 4000 50  0001 C CNN
	1    6650 4000
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5DF6F006
P 6650 4400
F 0 "D3" H 6643 4616 50  0000 C CNN
F 1 "LED" H 6643 4525 50  0000 C CNN
F 2 "" H 6650 4400 50  0001 C CNN
F 3 "~" H 6650 4400 50  0001 C CNN
	1    6650 4400
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 5DF6F898
P 6650 4800
F 0 "D4" H 6643 5016 50  0000 C CNN
F 1 "LED" H 6643 4925 50  0000 C CNN
F 2 "" H 6650 4800 50  0001 C CNN
F 3 "~" H 6650 4800 50  0001 C CNN
	1    6650 4800
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5DF7AA73
P 7100 3600
F 0 "R1" V 7307 3600 50  0000 C CNN
F 1 "100Ω" V 7216 3600 50  0000 C CNN
F 2 "" V 7030 3600 50  0001 C CNN
F 3 "~" H 7100 3600 50  0001 C CNN
	1    7100 3600
	0    1    -1   0   
$EndComp
Text Notes 6300 5600 0    50   ~ 0
Assume LEDs all have:\nVf = 3.2V\nIf = 20mA\n= 90Ω (using 100Ω)\n\nPro Micro\nMax current per pin = 40mA\nRecommended current per pin = 20mA
Wire Wire Line
	6800 3600 6950 3600
$Comp
L Device:R R2
U 1 1 5DF803CB
P 7100 4000
F 0 "R2" V 7307 4000 50  0000 C CNN
F 1 "100Ω" V 7216 4000 50  0000 C CNN
F 2 "" V 7030 4000 50  0001 C CNN
F 3 "~" H 7100 4000 50  0001 C CNN
	1    7100 4000
	0    1    -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5DF81071
P 7100 4400
F 0 "R3" V 7307 4400 50  0000 C CNN
F 1 "100Ω" V 7216 4400 50  0000 C CNN
F 2 "" V 7030 4400 50  0001 C CNN
F 3 "~" H 7100 4400 50  0001 C CNN
	1    7100 4400
	0    1    -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 5DF81077
P 7100 4800
F 0 "R4" V 7307 4800 50  0000 C CNN
F 1 "100Ω" V 7216 4800 50  0000 C CNN
F 2 "" V 7030 4800 50  0001 C CNN
F 3 "~" H 7100 4800 50  0001 C CNN
	1    7100 4800
	0    1    -1   0   
$EndComp
Wire Wire Line
	6800 4000 6950 4000
Wire Wire Line
	6950 4400 6800 4400
Wire Wire Line
	6800 4800 6950 4800
Text GLabel 7550 3600 2    50   Input ~ 0
GND
Wire Wire Line
	7250 3600 7400 3600
Wire Wire Line
	7250 4000 7400 4000
Wire Wire Line
	7400 4000 7400 3600
Connection ~ 7400 3600
Wire Wire Line
	7400 3600 7550 3600
Wire Wire Line
	7250 4400 7400 4400
Wire Wire Line
	7400 4400 7400 4000
Connection ~ 7400 4000
Wire Wire Line
	7250 4800 7400 4800
Wire Wire Line
	7400 4800 7400 4400
Connection ~ 7400 4400
$Comp
L Switch:SW_Push SW4
U 1 1 5DF90E50
P 5200 4800
F 0 "SW4" H 5200 5085 50  0000 C CNN
F 1 "SW_LED" H 5200 4994 50  0000 C CNN
F 2 "" H 5200 5000 50  0001 C CNN
F 3 "~" H 5200 5000 50  0001 C CNN
	1    5200 4800
	1    0    0    -1  
$EndComp
Text GLabel 5650 4400 2    50   Input ~ 0
GND
$Comp
L Switch:SW_Push SW1
U 1 1 5DF940D0
P 5200 4400
F 0 "SW1" H 5200 4685 50  0000 C CNN
F 1 "SW_EDIT" H 5200 4594 50  0000 C CNN
F 2 "" H 5200 4600 50  0001 C CNN
F 3 "~" H 5200 4600 50  0001 C CNN
	1    5200 4400
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5DF94ADD
P 5200 5200
F 0 "SW2" H 5200 5485 50  0000 C CNN
F 1 "SW_HR" H 5200 5394 50  0000 C CNN
F 2 "" H 5200 5400 50  0001 C CNN
F 3 "~" H 5200 5400 50  0001 C CNN
	1    5200 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3600 4700 3600
Wire Wire Line
	4700 4400 5000 4400
Wire Wire Line
	4800 3700 4600 3700
Wire Wire Line
	4600 4800 5000 4800
Wire Wire Line
	4500 5200 5000 5200
Wire Wire Line
	5400 4400 5500 4400
Wire Wire Line
	5400 4800 5500 4800
Wire Wire Line
	5500 4800 5500 4400
Connection ~ 5500 4400
Wire Wire Line
	5500 4400 5650 4400
Wire Wire Line
	5400 5200 5500 5200
Wire Wire Line
	5500 5200 5500 4800
Connection ~ 5500 4800
Text Notes 4350 5850 0    50   ~ 0
All switch pins should have their\npinMode set to INPUT_PULLUP
$Comp
L Switch:SW_Push SW3
U 1 1 5DF9BFD8
P 5200 5600
F 0 "SW3" H 5200 5885 50  0000 C CNN
F 1 "SW_MIN" H 5200 5794 50  0000 C CNN
F 2 "" H 5200 5800 50  0001 C CNN
F 3 "~" H 5200 5800 50  0001 C CNN
	1    5200 5600
	1    0    0    -1  
$EndComp
$Comp
L Timer_RTC:DS3231M U2
U 1 1 5DF51B64
P 3850 2300
F 0 "U2" H 3400 2800 50  0000 C CNN
F 1 "DS3231M" H 3400 2700 50  0000 C CNN
F 2 "Package_SO:SOIC-16W_7.5x10.3mm_P1.27mm" H 3850 1700 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231.pdf" H 4120 2350 50  0001 C CNN
	1    3850 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3700 6500 4000
Wire Wire Line
	6400 3800 6400 4400
Wire Wire Line
	6400 4400 6500 4400
Wire Wire Line
	6300 3900 6300 4800
Wire Wire Line
	6300 4800 6500 4800
Wire Wire Line
	3150 2100 3150 3200
Wire Wire Line
	3350 2100 3150 2100
Text Notes 3050 2500 2    50   ~ 0
Pull-up resistors are not needed for\nthe I2C bus, since the ProMicro\nautomatically switches to\nINPUT_PULLUP mode when using I2C
Wire Wire Line
	4700 3600 4700 4400
Wire Wire Line
	4600 3700 4600 4800
Wire Wire Line
	4400 5600 5000 5600
Wire Wire Line
	5400 5600 5500 5600
Wire Wire Line
	5500 5600 5500 5200
Connection ~ 5500 5200
Wire Wire Line
	6300 3900 6200 3900
Wire Wire Line
	6200 3800 6400 3800
Wire Wire Line
	6500 3700 6200 3700
Wire Wire Line
	6200 3600 6500 3600
Text Notes 4350 4750 2    50   ~ 0
SW_LED, SW_HR, SW_MIN\nuses interrupt pins (7, RX0, TX1)\n(interrupt pins: RX0, TX1, 2, 3, 7)
Wire Wire Line
	3250 2200 3250 3300
Wire Wire Line
	3150 3200 4800 3200
Wire Wire Line
	3250 3300 4800 3300
Wire Wire Line
	2750 3400 4800 3400
Wire Wire Line
	2750 3500 4800 3500
Wire Wire Line
	4500 2900 4800 2900
Wire Wire Line
	4500 2900 4500 5200
Wire Wire Line
	4800 2800 4400 2800
Wire Wire Line
	4400 2800 4400 5600
$EndSCHEMATC
