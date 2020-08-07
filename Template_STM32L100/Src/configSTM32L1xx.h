//*******************************************************************
// STM32L1xx
//*******************************************************************

//-------------------------------------------------------------------
cSystem sys;

//-------------------------------------------------------------------
cHwPinConfig::MAP cHwPinConfig::table[] = 
{
  // ADC
  ADC12_IN2_PA_2,
  
  // DAC
  DAC_OUT1_PA_4,
  
  // I2C
  I2C2_SCL_PB_10,
  I2C2_SDA_PB_11,

  // SPI
  SPI2_MOSI_PB_15,
  SPI2_MISO_PB_14,
  SPI2_SCK_PB_13,

  // Timer
  TIM2_CH1_ETR_PA_0,
  TIM2_CH2_PA_1,
  TIM2_CH3_PA_2,
  TIM2_CH4_PA_3,

  TIM3_CH1_PB_4,
  TIM3_CH2_PB_5,
  TIM3_CH3_PB_0,
  TIM3_CH4_PB_1,

  TIM4_CH1_PB_6,
  TIM4_CH2_PB_7,
  TIM4_CH3_PB_8,
  TIM4_CH4_PB_9,

  // UART
  USART1_TX_PA_9,
  USART1_RX_PA_10,

  USART3_TX_PC_10,
  USART3_RX_PC_11,

  END_OF_TABLE
};

//- Timer------------------------------------------------------------
cHwTimer_N  timerFast( cHwTimer_N::TIM_4,  1000/*us*/ );
cHwTimer_N  timerSlow( cHwTimer_N::TIM_2, 10000/*us*/ );
cHwTimer_N  timerPWM ( cHwTimer_N::TIM_3, 16382/*us*/ );

//- Digital Port ----------------------------------------------------
cHwPort_N   portA( cHwPort_N::PA );
cHwPort_N   portB( cHwPort_N::PB );
cHwPort_N   portC( cHwPort_N::PC );
cHwPort_N   portD( cHwPort_N::PD );

//- Analog Input ----------------------------------------------------
cHwADC_0    adc0( &timerFast );
cHwADC     &adc = adc0;

//- Display ---------------------------------------------------------
cHwSPImaster_N       spi2      ( cHwSPImaster_N::SPI_2, 
                                 cHwSPImaster::CR_500kHz, 
                                 cHwSPImaster::CPOL_H_CPHA_H );
cHwSPImaster::Device spiDisplay( spi2, portB, 12 );
cHwDisp_DIP204spi    dispHw      ( spiDisplay );

cDevDisplayChar  disp( dispHw );

//- Joystick --------------------------------------------------------
cDevDigital    btnRight( portA, 1, cDevDigital::InPU, 1 );
cDevDigital    btnLeft ( portA, 8, cDevDigital::InPU, 1 );
cDevDigital    btnCtrl ( portA,15, cDevDigital::InPU, 1 );

cDevControlEncoderRotaryKnob enc( &btnLeft, &btnRight, &btnCtrl, &timerFast );

//- Button ----------------------------------------------------------
cDevDigital    btnA    ( portC, 0,cDevDigital::InPU, 1 );
cDevDigital    btnB    ( portC, 1,cDevDigital::InPU, 1 );
cDevDigital    btnC    ( portC, 6,cDevDigital::InPU, 1 );
cDevDigital    btnD    ( portC, 7,cDevDigital::InPU, 1 );

//- Schalter --------------------------------------------------------
//Inkrement(i) ; End(e)
cDevDigital i1 (portA,3,cDevDigital::InPU,0);
cDevDigital i2 (portA,7,cDevDigital::InPU,0);
cDevDigital i3 (portC,3,cDevDigital::InPU,0);	//1
cDevDigital i4 (portC,5,cDevDigital::InPU,0);
cDevDigital e1 (portA,2,cDevDigital::InPU,1);
cDevDigital e2 (portA,6,cDevDigital::InPU,0);
cDevDigital e3 (portC,2,cDevDigital::InPU,0);
cDevDigital e4 (portC,4,cDevDigital::InPU,0);

//- LED und Freischalten H-Brücke -----------------------------------------
cDevDigital    led0    ( portC, 8, cDevDigital::Out, 0 );
cDevDigital    enable  ( portD, 2, cDevDigital::Out, 0 );

//START MY IMPLEMENTATION
//- DC-Motor ---------------------------------------------------------
cDevDigital			motor1L(portB, 4, cDevDigital::Out,0);		//Anti-Clockwise
cDevDigital			motor1R(portB, 5, cDevDigital::Out,0);		//Clockwise
Motor m1(motor1L,motor1R);
cDevDigital			motor2L(portB, 0, cDevDigital::Out,0);		//Anti-Clockwise
cDevDigital			motor2R(portB, 1, cDevDigital::Out,0);		//Clockwise
Motor m2(motor2L,motor2R);
cDevDigital			motor3L(portB, 6, cDevDigital::Out,0);		//Anti-Clockwise
cDevDigital			motor3R(portB, 7, cDevDigital::Out,0);		//Clockwise
Motor m3(motor3L,motor3R);
cDevDigital			motor4L(portB, 8, cDevDigital::Out,0);		//Anti-Clockwise
cDevDigital			motor4R(portB, 9, cDevDigital::Out,0);		//Clockwise
Motor m4(motor4L, motor4R);

//- Position		(END,INC)
Position p1(e1,i1);
Position p2(e2,i2);
Position p3(e3,i3);
Position p4(e4,i4);

//- Achsen und Greifer (Pos,Motor)
Achse winkel(p1,m1);
Achse radius(p2,m2);
Achse hoehe(p3,m3);
Greifer g(p4,m4);

//- IndustrieRoboter (winkel, radius, hoehe, greifer)
InduRoboter roboter(winkel, radius, hoehe, g,disp);

//END MY IMPLEMENTATION

//- Real Time Clock (RTC) -------------------------------------------
cHwRTC_0       rtc0;
cHwRTC        &rtc = rtc0;

//EOF
