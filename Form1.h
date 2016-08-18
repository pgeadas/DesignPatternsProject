#pragma once

#include "stdafx.h"
#include<string.h>
#include<cassert>
#include<iostream>
#include <vcclr.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#using <mscorlib.dll>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>


#include "ResourceObserver.h"
#include "MobileObject.h"
#include "Strategy.h"
#include "Bullet.h"
#include "Resource.h"
#include "SpaceShip.h"
#include "Observer.h"

#include "Player.h"
#include "StrategyPlayer.h"
#include "Players.h"

#include "Factory.h"
#include "Visitor.h"
#include "State.h"


namespace ProjectoNEW {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

public ref class Form1 : public System::Windows::Forms::Form
{
	
private: 
	HumanPlayer^ p; 
	CPUPlayer^ cpu;
	EnemySpaceShip^ e;
	Graphics^ g;
	Bullet^ b;
	Bullet^ bb;

	Factory^ bigFactory;
	Factory^ regularFactory;

	Strategy^ greenSpaceShipStrategy;
	Strategy^ redSpaceShipStrategy;
	Strategy^ detailedResource;
	Strategy^ simpleResource;
	Strategy^ detailedBullet;
	Strategy^ simpleBullet;
	Strategy^ bulletStrategy;
	Strategy^ rectangleAlgorithm;

	Visitor^ dv;
	Visitor^ actualVisitor;
	Visitor^ sv;
	Visitor^ doubleVV;

	StrategyPlayer^ detailedStrategy;
	StrategyPlayer^ simpleStrategy;

	Strategy^ Explosion;
	Strategy^ aux;

	Resource^ shield;

	static int color = 0;
	static int detail = 0;
	static int ENEMIES = 4;
	static int fact = 0;
	static Factory^ factory = gcnew BigFactory();
	static ArrayList^ CPUPlayers = gcnew ArrayList();

public:
	Form1(void)
	{
		InitializeComponent();
		SetStyle(ControlStyles::UserPaint, true);
		SetStyle(ControlStyles::AllPaintingInWmPaint, true);
		SetStyle(ControlStyles::OptimizedDoubleBuffer, true);
	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~Form1()
	{
		if (components)
		{
			delete components;
		}
	}


private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container ^components;


private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  pe) {

	 g = pe->Graphics;

	 this->dv->setPaintStuff(g);
	 this->sv->setPaintStuff(g);
	 this->actualVisitor->setPaintStuff(g);


	 //desenha o shield

	this->shield->Accept(actualVisitor);
	shield->Notify();


	//chama o visitor pa desenhar o player
	this->p->Accept(actualVisitor);
	this->p->Notify();

	//desenha a nave do player
	this->p->getSpaceShip()->Accept(actualVisitor);
	this->p->getSpaceShip()->updatePos();

	
	if(this->p->getSpaceShip()->getGB()->isOnScreen()){
		//this->p->getSpaceShip()->getGB()->getContext()->DrawStrategy(this->p->getSpaceShip()->getGB(),g);
		this->p->getSpaceShip()->getGB()->Accept(actualVisitor);
	}


	//desenha as bullets (iterator)
	for(int i=0;i<this->p->getSpaceShip()->getBullets()->Count;i++){
		b = static_cast<Bullet^>(this->p->getSpaceShip()->getBullets()[i]);
		if(b->isOnScreen()){
			b->Accept(actualVisitor);
		}
		else{
			this->p->getSpaceShip()->getBullets()->Remove(b);
		}
	}


	//desenha as naves dos cpus
	 for(int i=0;i<this->CPUPlayers->Count;i++){
		 double cO,cA,h;
		 cpu = static_cast<CPUPlayer^>(this->CPUPlayers[i]);
		 //cpu->Accept(actualVisitor);
		 cpu->Notify();
		 e = static_cast<EnemySpaceShip^>(cpu->getSpaceShip());
		 e->Accept(actualVisitor);

		 for(int j=0;j<e->getBullets()->Count;j++){
			b = static_cast<Bullet^>(e->getBullets()[j]);
			if(b->isOnScreen()){
				b->Accept(actualVisitor);
			}
			else{
				e->getBullets()->Remove(b);
			 }
		}

		 e->updatePos();
		 e->addCounter();
		 if(e->getCounter() % (50 + rand()%150) == 0 ){
			 bb = this->factory->createBulletObject();
			 this->bb->setContext(gcnew Context(this->bulletStrategy));

			//e->addBullet(e->getPlayerGrades(),bb);
			 e->shoot(bb);
			 
		 }
	 }

	 
	 Thread::Sleep(15);
	
	 Invalidate(this->ClientRectangle);
}


private: System::Void Key_Down(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		 switch(e->KeyCode)
	 {

		 case Keys::J:
			 this->p->getSpaceShip()->setPos(rand()%this->ClientRectangle.Width,rand()%this->ClientRectangle.Height);
			 break;
		 case Keys::G:
			 if(!this->p->getSpaceShip()->getGB()->isOnScreen()){
				this->p->getSpaceShip()->getGB()->setPos(this->p->getSpaceShip()->getX()+(this->p->getSpaceShip()->getSize()/2)-(this->p->getSpaceShip()->getGB()->getSize()/2),this->p->getSpaceShip()->getY()+(this->p->getSpaceShip()->getSize()/2)-(this->p->getSpaceShip()->getGB()->getSize()/2));
				this->p->getSpaceShip()->getGB()->setGrades(this->p->getSpaceShip()->getGrades());
				this->p->getSpaceShip()->getGB()->setOnScreen(true);
				this->p->getSpaceShip()->getGB()->setClientR(this->ClientRectangle);
			 }
			 break;
		 case Keys::T:
			 this->p->getSpaceShip()->getContext()->setContext(this->rectangleAlgorithm);
			 break;
		case Keys::F:
			if(fact%2 == 1){
				 this->factory = bigFactory;
			}else{
				this->factory = regularFactory;
			}
			fact++;
			 break;
		 case Keys::Left:
			 this->p->getSpaceShip()->MoveLeft();
			 break;
		 case Keys::Right:
			 this->p->getSpaceShip()->MoveRight();
			 break;
		 case Keys::Up:
			 this->p->getSpaceShip()->accelerate();
			 break;
		 case Keys::Down:
			 this->p->getSpaceShip()->slowDown();
			 break;
		 case Keys::Q:
			 this->p->getSpaceShip()->setVelocity(MAX_VELOCITY);
			 break;
		 case Keys::E:
			 this->p->getSpaceShip()->setVelocity(MIN_VELOCITY);
			 break;
		 case Keys::A:
			this->p->getSpaceShip()->MoveLeft();
			break;
		 case Keys::S:
			 this->p->getSpaceShip()->slowDown();
			 break;
		case Keys::W:
			 this->p->getSpaceShip()->accelerate();
			 break;
	    case Keys::D:
			 this->p->getSpaceShip()->MoveRight();
			 break;
		case Keys::C:
			if(color%2 == 1){
				this->p->getSpaceShip()->getContext()->setContext(this->redSpaceShipStrategy);
			}else{
				this->p->getSpaceShip()->getContext()->setContext(this->greenSpaceShipStrategy);
			}
			color++;
			 break;
		case Keys::L:
			if(detail%3 == 2){
				this->p->getSpaceShip()->setClientR(this->ClientRectangle);
				this->p->getContext()->setContext(this->detailedStrategy);
				this->shield->setClientR(this->ClientRectangle);

				for(int i=0;i<ENEMIES;i++){
					cpu = static_cast<CPUPlayer^>((CPUPlayers[i]));
					cpu->getSpaceShip()->setClientR(this->ClientRectangle);
				}
				/*this->shield->getContext()->setContext(this->detailedResource);
				this->p->getSpaceShip()->getContext()->setContext(this->redSpaceShipStrategy);
				for(int i=0;i<this->CPUPlayers->Count;i++){
					cpu = static_cast<CPUPlayer^>(this->CPUPlayers[i]);
					static_cast<EnemySpaceShip^>(cpu->getSpaceShip())->getContext()->setContext(this->greenSpaceShipStrategy);
				}*/
				this->actualVisitor = this->dv;
			}else if(detail%3 == 0){
				this->p->getSpaceShip()->setClientR(this->ClientRectangle);
				this->p->getContext()->setContext(this->simpleStrategy);
				this->shield->setClientR(this->ClientRectangle);

				for(int i=0;i<ENEMIES;i++){
					cpu = static_cast<CPUPlayer^>((CPUPlayers[i]));
					cpu->getSpaceShip()->setClientR(this->ClientRectangle);
				}
				/*this->shield->getContext()->setContext(this->simpleResource);
				this->p->getSpaceShip()->getContext()->setContext(this->redSimpleSpaceShipStrategy);
				for(int i=0;i<this->CPUPlayers->Count;i++){
					cpu = static_cast<CPUPlayer^>(this->CPUPlayers[i]);
					static_cast<EnemySpaceShip^>(cpu->getSpaceShip())->getContext()->setContext(this->greenSimpleSpaceShipStrategy);
				}*/
				this->actualVisitor = this->sv;
			}else{
				this->actualVisitor = this->doubleVV;
			}
			detail++;
			break;
		 default:
			 break;
		 }
		 }






#pragma region Windows Form Designer generated code
 /// <summary>
 /// Required method for Designer support - do not modify
 /// the contents of this method with the code editor.
 /// </summary>
 void InitializeComponent(void)
 {
	 this->SuspendLayout();
	 // 
	 // Form1
	 // 
	 this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
	 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	 this->BackColor = System::Drawing::Color::Black;
	 this->ClientSize = System::Drawing::Size(1104, 694);
	 this->DoubleBuffered = true;
	 this->Name = L"SpaceWars Pro v1.0";
	 this->Text = L"SpaceWars Pro v1.0";
	 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
	 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
	 this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::mouse_Click);
	 this->Resize += gcnew System::EventHandler(this, &Form1::On_Resize);
	 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Key_Down);
	 this->ResumeLayout(false);

 }
#pragma endregion

private: System::Void mouse_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 b = this->factory->createBulletObject();
			 this->b->setContext(gcnew Context(this->bulletStrategy));
			 this->p->getSpaceShip()->shoot(b);
			 //this->p->getSpaceShip()->setContext(gcnew Context(this->simpleBullet));
			
 }



private: System::Void On_Resize(System::Object^  sender, System::EventArgs^  e) {
			 if(this->p != nullptr){
				this->p->setClientR(this->ClientRectangle);
				this->p->getSpaceShip()->setClientR(this->ClientRectangle);
				this->shield->setClientR(this->ClientRectangle);
				for(int i=0;i<ENEMIES;i++){
					 cpu = static_cast<CPUPlayer^>((CPUPlayers[i]));
					cpu->getSpaceShip()->setClientR(this->ClientRectangle);
				}
			 }
		 }
 private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		//Explosion = gcnew DrawSmallExplosionAlgorithm();
		Explosion = gcnew DrawBigExplosionAlgorithm();

		bigFactory = factory;
		regularFactory = gcnew RegularFactory();	  
			  
		dv = gcnew DetailedVisitor();
		static_cast<DetailedVisitor^>(dv)->setExplosionStrategy(Explosion);

		sv = gcnew SimpleVisitor();
		static_cast<SimpleVisitor^>(sv)->setExplosionStrategy(Explosion);

		doubleVV = gcnew DoubleViewVisitor(dv,sv);
		

		actualVisitor = dv;
		

		//player strategys
		detailedStrategy = gcnew DrawDetailedShapesAlgorithm();
		simpleStrategy = gcnew DrawSimpleAlgorithm();

		//spaceship
		greenSpaceShipStrategy = gcnew DrawGreenEllipseAlgorithm();
		redSpaceShipStrategy = gcnew DrawRedEllipseAlgorithm();
		rectangleAlgorithm = gcnew DrawRedRectangleAlgorithm();
	
		//simple or detailed bullet
		detailedBullet = gcnew DrawWhiteEllipseAlgorithm();
//		simpleBullet = gcnew DrawWhiteBulletSimpleAlgorithm();
		this->bulletStrategy = detailedBullet;


		//cria um player da factory e inicializa os seus componentes
		p = this->factory->createHumanPlayer();
		p->setLifes(5);
		p->setEnergy(200);
		p->setShield(0);
		p->setScore(0);
		p->setSpaceShip(factory->createSpaceShipObject());
		p->getSpaceShip()->setClientR(this->ClientRectangle);
		p->setContext(gcnew PlayerContext(detailedStrategy));
		p->setClientR(this->ClientRectangle);
		this->p->getSpaceShip()->addGuidedBullet(this->p->getSpaceShip()->getGrades(), gcnew GuidedBullet());
		this->p->getSpaceShip()->getGB()->setContext(gcnew Context(this->bulletStrategy));
		this->p->getSpaceShip()->getGB()->setClientR(this->ClientRectangle);
		
		//resource (cria-se 1 de cada, e de x em x tempo mete-se a cair)
		shield = this->factory->createResourceObject();
		shield->setPos(rand()%500,2); //4000 para so aparecer na janela visivel de vez em quando
		shield->setGrades(90);
		shield->Attach(p);
	
		/** Example to switch a strategy **/
		//shield->getContext()->setContext(gcnew DrawWhiteEllipseAlgorithm());
		shield->setClientR(this->ClientRectangle);
		
		for(int i=0;i<ENEMIES;i++){
			cpu = this->factory->createCPUPlayer();
			//cpu->setClientR(this->ClientRectangle);
			cpu->setEnergy(40);
			p->setShield(0);
			cpu->setSpaceShip((factory->createEnemySpaceShipObject()));
			cpu->getSpaceShip()->setClientR(this->ClientRectangle);
			cpu->setContext(gcnew PlayerContext(gcnew DrawCPUSAlgorithm()));
			p->Attach(static_cast<Observer^>(cpu)); //atach das naves inimigas no observer (nave do jogador)
			CPUPlayers->Add(cpu);
		}
	
		//atach das naves inimigas no observer (naves inimigas) DrawCPUSAlgorithm()
		for(int i=0;i<ENEMIES;i++){
			cpu = static_cast<CPUPlayer^>((CPUPlayers[i]));
			shield->Attach(cpu);
			this->p->getSpaceShip()->getGB()->Attach(cpu);
			for(int j=0;j<ENEMIES;j++){
				if(j!=i){
					cpu->Attach(static_cast<Observer^>(CPUPlayers[j])); //atach das outras naves , para deteccao de colisoes entre cpus

				}
			}
			
		}
		
			 
 }

};



}

