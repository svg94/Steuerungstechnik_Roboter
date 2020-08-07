class Greifer : public Achse{
private:
		int act;
	public:
		Greifer(Position &p, Motor &mtr)
			: Achse(p, mtr)
		{}
		void grab(int wieFest,cDevDisplayChar &disp,int name)
		{
			moveToPos(wieFest,disp,4);
		}
		void release(cDevDisplayChar &disp)
		{
			goToNullPosition(disp);
		}

	
};
