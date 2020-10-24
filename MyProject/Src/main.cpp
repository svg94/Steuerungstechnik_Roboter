//*******************************************************************
#include "lib.h"
#include "Module/RTOS.h"
#include "Peripheral/Disp_DIP204spi.h"

#include "robo.h"
//*******************************************************************
#if defined _MCU_TYPE_STM32L1XX
  #include "configSTM32L1xx.h"
#elif defined _MCU_TYPE_VIRTUAL
  #include "configVirtual.h"
#else
  #error "Device type not defined"
#endif

//*******************************************************************
#include "Task_Example.h"
#include "RTOS_Task_Example.h"

//*******************************************************************

//*******************************************************************
cTaskHandler  taskHandler ( &timerSlow ); 
cTask_Example task_Example( taskHandler );

//*******************************************************************
const unsigned NUM_OF_RTOS_TASKS = 3;
cRTOS_RR<NUM_OF_RTOS_TASKS>  rtos( 1000/*time per task [ms]*/ );
cRtosTask_Example            rtos_task_Example( rtos );

//*******************************************************************
int ctrMode = 0;		//ZUM TESTEN UM EINZELNE MOTOREN ANZUSTEUERN
int main(void)
{
  int num = 0;
  cHwRTC::Properties clock;
	int resetctr = 0;				//F�r den Display-clear, wenn man den Strom deaktiviert.
  while(1)
  {
		
		
		
		
    //-- Real-Time-Clock (RTC) --------------------------------------
    if( rtc.get( clock ) )
      disp.printf( 0,0,0, "RTC: %02d:%02d:%02d", 
                          clock.hour, 
                          clock.minute, 
                          clock.second );
    else
      disp.printf( 0,0,0, "---");
    
    /*//-- Timer-Task und RTOS-Task -----------------------------------
    disp.printf(1,0,20,"Timer-Task: %d",   task_Example.cnt );
    disp.printf(2,0,20,"RTOS-Task:  %.1f", rtos_task_Example.sec );*/

    //-- Encoder (Drehknopf bzw. Tasten) ----------------------------
    switch( enc.get() )
    {
        case cDevControlEncoder::LEFT:     num -= 1; break;
        case cDevControlEncoder::RIGHT:    num += 1; break;
        case cDevControlEncoder::CTRL_DWN: num  = 0; break;
        default:                                     break;
    }
    //disp.printf(3,0,20,"Encoder:%d", num );

    //-- Digital-I/O (Tasten und LED) -------------------------------
    if( btnA.getEvent() == cDevDigital::ACTIVATED )
    {
      enable.toggle();
			disp.printf( 1,0,10, "Strom-An");
			resetctr = 0;
		}
		if(enable.get() == 0){
				if(resetctr == 0){
					disp.clear();
					resetctr+=1;
				}
			
			disp.printf( 1,0,0, "Strom-Aus");
		}
		
    //led0.set( btnB.get() );
		//roboter.goToNullPosition(true);
		if( btnB.getEvent() == cDevDigital::ACTIVATED )		//START ROUTINE AUF KNOPFDRUCK
    {
			disp.printf(1,0,17,"Routine: Start");
			roboter.routine();
			//g.grab(14,disp,4);
    }
		if(btnC.getEvent() ==cDevDigital::ACTIVATED)
		{
			roboter.goToNullPosition(true);
		}
		/// ZUSATZFUNKTION:_SELBST-STEUERN
		if( btnD.getEvent() == cDevDigital::ACTIVATED )
		{
			m1.stop();
			m2.stop();
			m3.stop();
			m4.stop();
			ctrMode= (ctrMode )%4+1;
			if(ctrMode==0){ctrMode = 1;}
			disp.printf(0,17,20,"M:%d", ctrMode);
		}
		if(num > 0){
			switch(ctrMode) {
				case 1 : m1.moveRight();
									
             break;       
				case 2 : m2.moveRight();
             break;
				case 3: m3.moveRight();
							break;
				case 4: m4.moveRight();
							break;
			}
		}else if(num < 0){
			switch(ctrMode) {
				case 1 : m1.moveLeft();
             break;       
				case 2 : m2.moveLeft();
             break;
				case 3: m3.moveLeft();
						break;
				case 4: m4.moveLeft();

						break;
			}
		}else{
			m1.stop();
			m2.stop();
			m3.stop();
			m4.stop();
		}
		
  }
}

//EOF
