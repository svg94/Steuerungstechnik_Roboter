#define MITGREIFER true
#define WINKEL1 32	
#define RADIUS1 42	
#define HOEHE1 40		
#define WINKEL2 32
#define RADIUS2 42
#define HOEHE2 83		
#define WINKEL_END 62
#define RADIUS_END 37
#define HOEHE_END 57
#define HOEHE_END_2 43			//Um roten Kreis fallen zu lassen, muss die Hoehe im Wert niedriger sein.
#define GRAB_HUELSE	13
#define GRAB_KREIS  14
class InduRoboter{
	private:
		Achse &a0_;
		Achse &a1_;
		Achse &a2_;
		Greifer &g_;
		cDevDisplayChar &disp_;
	public:
	
		InduRoboter(Achse &ac0, Achse &ac1, Achse &ac2, Greifer &gr,cDevDisplayChar &displ)
			:a0_(ac0), a1_(ac1),a2_(ac2),g_(gr),disp_(displ)
		{
		}
		
		void MoveToPos(int winkel, int radius, int hoehe)
		{
			disp_.printf(1,0,17,"Ziel: %d, %d, %d",winkel, radius, hoehe);
			disp_.printf(3,0,20,"Pos1:%d, 2:%d, 3:%d",0,0,0);
			a0_.moveToPos(winkel,disp_,1);
			disp_.printf(3,0,20,"Pos1:%d, 2:%d, 3:%d",a0_.getPos().getPos(),a1_.getPos().getPos(),a2_.getPos().getPos());
			a2_.moveToPos(hoehe,disp_,3);		//Hoehe vor Radius, damit der Roboter keine Regale trifft.
			disp_.printf(3,0,20,"Pos1:%d, 2:%d, 3:%d",a0_.getPos().getPos(),a1_.getPos().getPos(),a2_.getPos().getPos());
			a1_.moveToPos(radius,disp_,2);
			disp_.printf(3,0,20,"Pos1:%d, 2:%d, 3:%d",a0_.getPos().getPos(),a1_.getPos().getPos(),a2_.getPos().getPos());
		}
		void routine()			//1.Versuch Roboter geht immer nach jedem Schritt in NullPosition, um keine weiteren Regale aus Versehen zu treffen. Nachteil: Deutlich längere Laufzeit.
		{
			disp_.printf(0,0,20,"Routine: Start");
			goToNullPosition(MITGREIFER);
			disp_.printf(0,0,20,"Routine: Working...");
			MoveToPos(WINKEL1, RADIUS1, HOEHE1);					//1.Lager
			g_.grab(GRAB_HUELSE,disp_,4);
			goToNullPosition(!MITGREIFER);
			MoveToPos(WINKEL_END,RADIUS_END,HOEHE_END);					//ENDLager
			g_.release(disp_);
			goToNullPosition(!MITGREIFER);
			MoveToPos(WINKEL2,RADIUS2,HOEHE2);					//2.Lager
			g_.grab(GRAB_KREIS,disp_,4);
			goToNullPosition(!MITGREIFER);
			MoveToPos(WINKEL_END,RADIUS_END,HOEHE_END_2);
			g_.release(disp_);
			goToNullPosition(!MITGREIFER);
			disp_.printf(1,0,17,"Routine: Finished");
			disp_.printf(0,0,20,"");		//Clearing display
		}
		
		bool isOnNullPosition(bool mitGreifer)				
		{
			bool isOnNull;
			if(mitGreifer == true){
				isOnNull = (a0_.isOnNullPosition() 
						& a1_.isOnNullPosition() 
							& a2_.isOnNullPosition() 
								& g_.isOnNullPosition());
		  }else
			{
				isOnNull = (a0_.isOnNullPosition() 
						&& a1_.isOnNullPosition() 
							&& a2_.isOnNullPosition());
			}
			if(isOnNull)
			{
				return true;
			}
			return false;
		}
		void goToNullPosition(bool mitGreifer)
		{
			if(isOnNullPosition(mitGreifer) == true)			
			{
				return;
			}else
			{
				disp_.printf(1,0,20,"Ziel: %d, %d, %d",0, 0, 0);
				a1_.goToNullPosition(disp_);				//RADIUS, HOEHE, WINKEL in dieser Reihenfolge, um Regale nicht zu treffen.
				disp_.printf(3,0,20,"Pos1:%d, 2:%d, 3:%d",a0_.getPos().getPos(),a1_.getPos().getPos(),a2_.getPos().getPos());
				a2_.goToNullPosition(disp_);
				disp_.printf(3,0,20,"Pos1:%d, 2:%d, 3:%d",a0_.getPos().getPos(),a1_.getPos().getPos(),a2_.getPos().getPos());
				a0_.goToNullPosition(disp_);
				disp_.printf(3,0,20,"Pos1:%d, 2:%d, 3:%d",a0_.getPos().getPos(),a1_.getPos().getPos(),a2_.getPos().getPos());
				if(mitGreifer == true){
					g_.goToNullPosition(disp_);
				}
			}
			return;
		}
		
};
