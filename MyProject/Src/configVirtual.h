//*******************************************************************
// Virtual
//*******************************************************************

//-------------------------------------------------------------------
cSystem sys;

//-------------------------------------------------------------------
cNetWin  net;
cNetUDP  udp( net );
cNetTCP  tcp( net );

cNetAddr<4> server = {127,0,0,1};

//- Timer------------------------------------------------------------
cHwTimer_MCU   timerFast(  1000/*us*/ );
cHwTimer_MCU   timerSlow( 10000/*us*/ );
cHwTimer      &timerPWM = timerSlow;

//- Digital Port ----------------------------------------------------
cHwPort_Virtual port( server,1000);

//- Analog Input ----------------------------------------------------
cHwADC_Virtual adc0( server, 1002, &timerSlow);
cHwADC         &adc = adc0;

//- Display ---------------------------------------------------------
cHwDispChar_Virtual dispHw( server, 1001 );
cDevDisplayChar     disp  ( dispHw );

//- Joystick --------------------------------------------------------
cDevDigital    btnLeft ( port, 0,cDevDigital::In, 0 );
cDevDigital    btnCtrl ( port, 1,cDevDigital::In, 0 );
cDevDigital    btnRight( port, 2,cDevDigital::In, 0 );
cDevControlEncoderJoystick enc( &btnLeft, &btnRight, &btnCtrl, &timerSlow, 120 );

//- Button ----------------------------------------------------------
cDevDigital    btnA    ( port, 5,cDevDigital::In, 0 );
cDevDigital    btnB    ( port, 6,cDevDigital::In, 0 );

//- LED -------------------------------------------------------------
cDevDigital    led0    ( port, 8, cDevDigital::Out, 0 );
cDevDigital    enable  ( port, 9, cDevDigital::Out, 0 );

//- Real Time Clock (RTC) -------------------------------------------
cHwRTC_0       rtc0;
cHwRTC        &rtc = rtc0;

//EOF
