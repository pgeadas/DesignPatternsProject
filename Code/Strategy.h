#pragma once
//#include "MobileObject.h"

interface class Strategy {
	public: 
		virtual void Draw(MobileObject^, Graphics^)=0;
};
ref class DrawSmallExplosionAlgorithm : public Strategy {
public:
	DrawSmallExplosionAlgorithm(){}
	virtual void Draw(MobileObject^ mo, Graphics^ g){
		
		g->DrawEllipse(Pens::Yellow, mo->GetQuarterFrame());
		g->DrawEllipse(Pens::Red, mo->GetHalfFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetDoubleFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetHalfFrame());
		g->DrawEllipse(Pens::Red, mo->GetDoubleFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetHalfFrame());
		g->DrawEllipse(Pens::Red, mo->GetQuarterFrame());
	}

};

ref class DrawBigExplosionAlgorithm : public Strategy {
public:
	DrawBigExplosionAlgorithm(){}
	virtual void Draw(MobileObject^ mo, Graphics^ g){
		g->DrawEllipse(Pens::Yellow, mo->GetQuarterFrame());
		g->DrawEllipse(Pens::Red, mo->GetHalfFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetDoubleFrame());
		g->DrawEllipse(Pens::Red, mo->GetQuarterFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetHalfFrame());

		g->DrawEllipse(Pens::Yellow, mo->GetDoubleFrame());
		g->DrawEllipse(Pens::Red, mo->GetHalfFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetQuarterFrame());
		g->DrawEllipse(Pens::Red, mo->GetDoubleFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetHalfFrame());

		g->DrawEllipse(Pens::Yellow, mo->GetQuarterFrame());
		g->DrawEllipse(Pens::Red, mo->GetHalfFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetDoubleFrame());
		g->DrawEllipse(Pens::Red, mo->GetQuarterFrame());
		g->DrawEllipse(Pens::Yellow, mo->GetHalfFrame());

		g->DrawEllipse(Pens::Red, mo->GetDoubleFrame());
	}

};


ref class DrawBrownEllipseAlgorithm : public Strategy {
public:
	DrawBrownEllipseAlgorithm(){}

	virtual void Draw(MobileObject^ mo, Graphics^ g){
		//Draw an Elipse 
		g->DrawEllipse(Pens::Brown, mo->GetFrame());
	}
};


ref class DrawWhiteEllipseAlgorithm : public Strategy {
private:
	int count;
public:
	DrawWhiteEllipseAlgorithm(){count=0;}
	virtual void Draw(MobileObject^ mo, Graphics^ g){
		g->DrawEllipse(Pens::White, mo->GetFrame());
	}
};


ref class DrawRedEllipseAlgorithm : public Strategy {
private:
	int count;
public:
		DrawRedEllipseAlgorithm(){count=0;}
		virtual void Draw(MobileObject^ mo, Graphics^ g){
			g->DrawEllipse(Pens::Red, mo->GetFrame());
	}
};

ref class DrawGreenEllipseAlgorithm : public Strategy {
	
public:
		DrawGreenEllipseAlgorithm(){}
		virtual void Draw(MobileObject^ mo, Graphics^ g){
			g->DrawEllipse(Pens::Green, mo->GetFrame());
	}
};

ref class DrawOrangeEllipseAlgorithm : public Strategy {
	
public:
		DrawOrangeEllipseAlgorithm(){}
		virtual void Draw(MobileObject^ mo, Graphics^ g){
			g->DrawEllipse(Pens::Orange, mo->GetFrame());
	}
};

ref class DrawRedRectangleAlgorithm : public Strategy {
	
public:
		DrawRedRectangleAlgorithm(){}
		virtual void Draw(MobileObject^ mo, Graphics^ g){
			g->DrawRectangle(Pens::Red,mo->GetFrame());
	}
};


ref class Context {
private:
	Strategy^ strategy;
public:
	Context(Strategy^ s){
		this->strategy = s;
	}
	void setContext(Strategy^ s){
		this->strategy = s;
	}
	Strategy^ getStrategy(){
		return this->strategy;
	}
	void DrawStrategy(MobileObject^ mo, Graphics^ g){
		this->strategy->Draw(mo, g);
	}
};