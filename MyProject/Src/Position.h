class Position{
	private:
		cDevDigital &endSchalter_;
		cDevDigital &incSchalter_;
		volatile int ctr;
	
		bool checkInc;					/*Fuer den Fall, dass diese Methode zu schnell 
														 *aufgerufen wird, muss der Knopf immer einmal deaktiviert werden, 
														 *bevor mit der Inkrementierung fortgefahren werden darf.*/
		bool checkDec;
	public:
		Position(cDevDigital &end,cDevDigital &inc)
			:endSchalter_(end), incSchalter_(inc)
		{
			ctr = 0;
			checkInc = true;
			checkDec = true;
		}
		bool isEnd()
		{
			if(endSchalter_.get() == 1)
			{
				return true;
			}else
			{
				return false;
			}
		}
		void inc()	//Move right
		{
			if((incSchalter_.get() == 1)  &&(checkInc == true))		
			{
				checkInc = false;
				ctr+=1;
			}else if((incSchalter_.get() == 0) && (checkInc == false))
			{
				checkInc = true;
			}
		}
		void dec()	//Move left
		{
			if((incSchalter_.get() == 1) && (checkDec == true))		
			{
				checkDec = false;
				ctr-=1;
			}else if((incSchalter_.get() == 0) && (checkDec == false))
			{
				checkDec = true;
			}
		}
		int getPos()
		{
			return this->ctr;
		}
		void setPos(int x)
		{
			this->ctr=x;
		}
		bool getCheckInc()
		{
			return checkInc;
		}
};
