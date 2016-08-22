#pragma once
//#include "Player.h"

//fazer variar o tipo d elementos desenhados, imagens ou rectangulos
interface class StrategyPlayer {
	public: 
		virtual void Draw(Player^ p, Graphics^ g,Rectangle r )=0;
};


ref class DrawDetailedShapesAlgorithm : public StrategyPlayer {
	
public:
	DrawDetailedShapesAlgorithm(){}
	virtual void Draw(Player^ p, Graphics^ g,Rectangle r){
		Font^ f = gcnew System::Drawing::Font("Times New Roman",12);
		PointF point = PointF(r.Width-290,r.Height-200-2);

		//outer box
		g->DrawRectangle(Pens::AntiqueWhite,r.Width-300,r.Height-215,298,200);

		g->DrawString("Energy",f,Brushes::Green,point);
		g->DrawRectangle(Pens::Green,r.Width-210,r.Height-200,200,20);
		g->FillRectangle(Brushes::Green,r.Width-210,r.Height-200,p->getEnergy(),20);

		point = PointF(r.Width-290,r.Height-160-2);
		g->DrawString("Lifes",f,Brushes::Blue,point);

		for(int i=0;i < (int)p->getLifes();i++){
			g->DrawRectangle(Pens::Blue,r.Width-210+(i*44),r.Height-160,20,20);
			g->FillRectangle(Brushes::Blue,r.Width-210+(i*44),r.Height-160,20,20);
		}

		point = PointF(r.Width-290,r.Height-120-2);
		g->DrawString("Shield",f,Brushes::Brown,point);

		g->DrawRectangle(Pens::Brown,r.Width-210,r.Height-120,200,20);
		g->FillRectangle(Brushes::Brown,r.Width-210,r.Height-120,p->getShield(),20);
		
		point = PointF(r.Width-290,r.Height-70-2);
		g->DrawString("Score",f,Brushes::AntiqueWhite,point);

		g->DrawRectangle(Pens::Green,r.Width-210,r.Height-70-2,p->getScore(),20);
		g->FillRectangle(Brushes::Green,r.Width-210,r.Height-70-2,p->getScore(),20);
	}
};


ref class DrawSimpleAlgorithm : public StrategyPlayer {
	
public:
	DrawSimpleAlgorithm(){}
	virtual void Draw(Player^ p, Graphics^ g,Rectangle r){
		Font^ f = gcnew System::Drawing::Font("Times New Roman",12);
		PointF point = PointF(r.Width-290,r.Height-200-2);

		g->DrawRectangle(Pens::AntiqueWhite,r.Width-300,r.Height-215,298,200);

		g->DrawString("Energy",f,Brushes::Green,point);
		point = PointF(r.Width-150,r.Height-200-2);
		g->DrawString(p->getEnergy().ToString(),f,Brushes::Green,point);

		point = PointF(r.Width-290,r.Height-160-2);
		g->DrawString("Lifes",f,Brushes::Blue,point);
		point = PointF(r.Width-150,r.Height-160-2);
		g->DrawString(p->getLifes().ToString(),f,Brushes::Blue,point);
		
		point = PointF(r.Width-290,r.Height-120-2);
		g->DrawString("Shield",f,Brushes::Brown,point);

		point = PointF(r.Width-150,r.Height-120-2);
		g->DrawString(p->getShield().ToString(),f,Brushes::Brown,point);

		point = PointF(r.Width-290,r.Height-70-2);
		g->DrawString("Score",f,Brushes::AntiqueWhite,point);

		point = PointF(r.Width-150,r.Height-70-2);
		g->DrawString(p->getScore().ToString(),f,Brushes::AntiqueWhite,point);
	}
};

ref class DrawCPUSAlgorithm : public StrategyPlayer {
	
public:
	DrawCPUSAlgorithm(){}
	virtual void Draw(Player^ p, Graphics^ g,Rectangle r){
		
		Font^ f = gcnew System::Drawing::Font("Times New Roman",12);
		PointF point = PointF(p->getSpaceShip()->getX(),p->getSpaceShip()->getY());

		g->DrawString(p->getEnergy().ToString(),f,Brushes::Green,point);
		
		point = PointF(p->getSpaceShip()->getX()-5,p->getSpaceShip()->getY()-10);

		g->DrawString(p->getShield().ToString(),f,Brushes::Brown,point);
	}
};



ref class DrawDetailedImagesAlgorithm : public StrategyPlayer {
	
public:
	DrawDetailedImagesAlgorithm(){}
	virtual void Draw(Player^ p, Graphics^ g,Rectangle r){}
};

ref class PlayerContext {
private:
	StrategyPlayer^ strategy;

public:
	PlayerContext(StrategyPlayer^ s){
		this->strategy = s;
	}

	void setContext(StrategyPlayer^ s){
		this->strategy = s;
	}

	void DrawStrategy(Player^ p, Graphics^ g,Rectangle r){
		this->strategy->Draw(p, g,r);
	}
};