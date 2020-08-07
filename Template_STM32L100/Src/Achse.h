class Achse{
	private:
		Position &pos_;
		Motor &m_;
		int actu;
	public:
		Achse(Position &p, Motor &mo)
			:pos_(p), m_(mo)
		{
		}
	
		void goToNullPosition(cDevDisplayChar &disp)
		{
			while(getPos().isEnd() == false)
			{
				disp.printf(2,0,17,"Pos: %d",this->getPos().getPos());
				move(1);		//Move Left
			}
			this->getPos().setPos(0);
			disp.printf(2,0,17,"Pos: %d",this->getPos().getPos());
			stop();
		}
		bool isOnNullPosition(){
			if(getPos().isEnd() == true)
			{
				return true;
			}
			return false;
		}
		void moveToPos(int pos, cDevDisplayChar &disp,int name)
		{
			actu = this->getPos().getPos();
			while(actu < pos){
				actu = this->getPos().getPos();
				if(actu == pos)
				{
					stop();
				}else if(actu < pos)
				{
					this->getM().moveLeft();
					this->getPos().inc();
					actu = this->getPos().getPos();
					disp.printf(2,0,17,"Pos%d: %d",name,this->getPos().getPos());
				}/*else if(actu > pos)
				{
					//move(1);
					//this->getPos().inc();
					//disp.printf(3,0,17,"Pos: %d",14);
				}*/
			}
			stop();
		}
		void move(int direction){
			if(direction == 0)
			{
				this->getPos().inc();
				this->getM().moveLeft();
			}else if(direction == 1)
			{
				this->getPos().dec();
				this->getM().moveRight();
			}else
			{
				return;
			}
		}
		void stop(){
			this->getM().stop();
		}
		Motor getM(){
			return m_;
		}
		Position& getPos(){
			return this->pos_;
		}
		
};
