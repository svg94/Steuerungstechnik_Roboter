//AGGREGATION
class Motor {
	private:
		cDevDigital &richtung0_;
		cDevDigital &richtung1_;
		
	public:
		Motor(cDevDigital &r0,cDevDigital &r1)
	: richtung0_(r0), richtung1_(r1)
		{
		}	//Initialisierung des Motors mit Pins für Drehrichtung
		void moveLeft()
		{														//IF-PRESSED PAUSED -> THEN PAUSE
			richtung1_.set(0);
			richtung0_.set(1);
		}	//Richtung 0 = Set(1)
		void moveRight()
		{
			richtung0_.set(0);
			richtung1_.set(1);
		} //Richtung 1 = Set(1)
		void stop()
		{
			richtung1_.set(0);
			richtung0_.set(0);
		}	//Set 0
		
};

