

ref class PlayerContext;
interface class Visitor;
ref class ViewVisitor;

ref class HumanPlayer: public Player, public ResourceObserver{
public:
	HumanPlayer(){}

	virtual void Accept(Visitor^ v) override {v->VisitPlayer(this);}

	virtual void Update(ResourceSubject^ s){

		Resource^ res = static_cast<Resource^>(s);
		Bullet^ b;
		double h;
		double cO;
		double cA;
		cO = pow((this->getSpaceShip()->getCenter().X- res->getCenter().X +res->getSize()/2 ),2);
		cA = pow((this->getSpaceShip()->getCenter().Y- res->getCenter().Y +res->getSize()/2 ),2);
		h = sqrt(cO+cA);

		//colisions of spaceship with resources
		if( (h - (this->getSpaceShip()->getSize()/2) - res->getSize()/2) <=3)
		{
			this->addShield(50);
			res->setPos(5000 ,res->getClientR().Height-1); //4000 para so aparecer na janela visivel de vez em quando
		}

		//player bullets with resources
		for(int i=0;i< this->getSpaceShip()->getBullets()->Count;i++){
			b= static_cast<Bullet^>(this->getSpaceShip()->getBullets()[i]);
			cO = pow( (res->getX() - b->getX() + res->getSize()/2 ),2);
			cA = pow((res->getY() + res->getSize()/2 - b->getY() ),2);
			h = sqrt(cO+cA);

			if(h - (res->getSize()/2) - b->getSize()/2 <= 2){	
				b->setOnScreen(false);
				static_cast<Resource^>(res)->setHit(true);
				
			}	
		
		}

	}
};


ref class CPUPlayer : public Player, public Observer, public ResourceObserver{
	static double H_MIN = 99999999;
	static Strategy^ shielded = gcnew DrawOrangeEllipseAlgorithm();
	static Strategy^ aux = gcnew DrawGreenEllipseAlgorithm();
public:
	CPUPlayer(){}
	virtual void Accept(Visitor^ v) override {v->VisitPlayer(this);}
	
	virtual void Update(ResourceSubject^ s){

		Resource^ res = static_cast<Resource^>(s);
		Bullet^ b;
		double h;
		double cO;
		double cA;
		cO = pow((this->getSpaceShip()->getCenter().X- res->getCenter().X +res->getSize()/2 ),2);
		cA = pow((this->getSpaceShip()->getCenter().Y- res->getCenter().Y +res->getSize()/2 ),2);
		h = sqrt(cO+cA);

		//enemies with resources
		if( (h - (this->getSpaceShip()->getSize()/2) - res->getSize()/2) <=3)
		{
			this->addShield(50);
			this->getSpaceShip()->getContext()->setContext(shielded);
			res->setPos(5000 ,res->getClientR().Height-1); 
		}


		//enemy bullets with resources
		for(int i=0;i< this->getSpaceShip()->getBullets()->Count;i++){
			b= static_cast<Bullet^>(this->getSpaceShip()->getBullets()[i]);
			cO = pow( (res->getX() - b->getX() + res->getSize()/2 ),2);
			cA = pow((res->getY() + res->getSize()/2 - b->getY() ),2);
			h = sqrt(cO+cA);

			if(h - (res->getSize()/2) - b->getSize()/2 <= 2){	
				b->setOnScreen(false);
				static_cast<Resource^>(res)->setHit(true);
			}	
		
		}

	}

	virtual void Update(Subject^ s){
		Player^ human = static_cast<Player^>(s);
		Bullet^ b; 

		double h;
		double cO;
		double cA;

		if(this->getShield()<=0){
			this->getSpaceShip()->getContext()->setContext(aux);
		}

		//enemy bullets with players
		for(int i=0;i< this->getSpaceShip()->getBullets()->Count;i++){
			b= static_cast<Bullet^>(this->getSpaceShip()->getBullets()[i]);
			cO = pow( (human->getSpaceShip()->getX() +human->getSpaceShip()->getSize()/2 - b->getX() ),2);
			cA = pow((human->getSpaceShip()->getY() +human->getSpaceShip()->getSize()/2 - b->getY() ),2);
			h = sqrt(cO+cA);

			if(h - (human->getSpaceShip()->getSize()/2) - b->getSize()/2 <= 3){
				
				if(human->getShield()>0){
					human->decShield(25);
				}else{
					human->setEnergy(human->getEnergy()-20);
				}
				b->setOnScreen(false); 
			}	
		
		}


		//guided bullet
		if(human->getSpaceShip()->getGB()->isOnScreen()){ //if bullet is not fired, skip the math
			
			cO = pow((this->getSpaceShip()->getCenter().X+this->getSpaceShip()->getSize()/2-human->getSpaceShip()->getGB()->getX()),2);
			cA = pow((this->getSpaceShip()->getCenter().Y+this->getSpaceShip()->getSize()/2-human->getSpaceShip()->getGB()->getY()),2);
			h = sqrt(cO+cA);

			if(H_MIN>h){ //chase the closest spaceship
				H_MIN = h;
				cO = this->getSpaceShip()->getCenter().X+this->getSpaceShip()->getSize()/2-human->getSpaceShip()->getGB()->getX();
				cA = this->getSpaceShip()->getCenter().Y+this->getSpaceShip()->getSize()/2-human->getSpaceShip()->getGB()->getY();

				human->getSpaceShip()->getGB()->addX((cO*this->getSpaceShip()->getVelocity()*2/h));//h/cA
				human->getSpaceShip()->getGB()->addY((cA*this->getSpaceShip()->getVelocity()*2/h));//h/cO
				
			}

			H_MIN+=20;


			if(h - (this->getSpaceShip()->getSize()/2) - human->getSpaceShip()->getGB()->getSize()/2 <=1){
				H_MIN=9999999;
				if(this->getShield()>0){
				this->decShield(50);
			}
			else{
				this->setEnergy(this->getEnergy()-20); 
			}

			human->getSpaceShip()->getGB()->setOnScreen(false);
			}

		}

		cO = pow((this->getSpaceShip()->getCenter().X-human->getSpaceShip()->getCenter().X),2);
		cA = pow((this->getSpaceShip()->getCenter().Y-human->getSpaceShip()->getCenter().Y),2);
		h = sqrt(cO+cA);


		//spaceship colisions
		if( (h - (this->getSpaceShip()->getSize()/2) - human->getSpaceShip()->getSize()/2) <=3)
		{
			if(this->getShield()>0){
				this->decShield(50);
			}else{
				this->setEnergy(this->getEnergy()-20); 
			}


			if(human->getShield()>0){
				human->decShield(50);
			}else{
				human->setEnergy(human->getEnergy()-20);
			}

			if(human->getSpaceShip()->getX() > this->getSpaceShip()->getX() ){
				if(human->getSpaceShip()->getY() > this->getSpaceShip()->getY() ){
					this->getSpaceShip()->setGrades(210 + rand()%20);
					human->getSpaceShip()->setGrades(45 + rand()%20);
			
				}else{
					this->getSpaceShip()->setGrades(-210 +rand()%20);
					human->getSpaceShip()->setGrades(-45 + rand()%20);
				}
			}else{
				if(human->getSpaceShip()->getY() >= this->getSpaceShip()->getY() ){
					this->getSpaceShip()->setGrades(-30 + rand()%20);
					human->getSpaceShip()->setGrades(130 + rand()%20);
				}else{
					this->getSpaceShip()->setGrades(30 + rand()%20);
					human->getSpaceShip()->setGrades(-130 + rand()%20);
				}
			}

		}

		//player bullets with enemy spaceships colisions
		for(int i=0;i< human->getSpaceShip()->getBullets()->Count;i++){
			b= static_cast<Bullet^>(human->getSpaceShip()->getBullets()[i]);
			cO = pow( (this->getSpaceShip()->getX() +this->getSpaceShip()->getSize()/2 - b->getX() ),2);
			cA = pow((this->getSpaceShip()->getY() +this->getSpaceShip()->getSize()/2 - b->getY() ),2);
			h = sqrt(cO+cA);

			if(h - (this->getSpaceShip()->getSize()/2) - b->getSize()/2 <= 3){
				
				if(this->getShield()>0){
					this->decShield(50);
				}else{
					this->setEnergy(this->getEnergy()-40);
					
				}
				b->setOnScreen(false); 
				
			}	
		
		}


		if(human->getEnergy()<=1){
			human->setEnergy(200);
			human->setLifes(human->getLifes()-1);
			human->getSpaceShip()->setX(rand()%human->getSpaceShip()->getClientR().Width);
			human->getSpaceShip()->setY(rand()%human->getSpaceShip()->getClientR().Width);
			human->getSpaceShip()->setHit(true);

		}

		if(this->getEnergy()<=1){
			this->setEnergy(40);
			this->setShield(0);
			this->getSpaceShip()->setHit(true);
			this->getSpaceShip()->setVelocity(3);
			human->addScore(1);
			
		}


	}
};


ref class BigCPUPlayer : public CPUPlayer{
public:
	BigCPUPlayer(){}

};



ref class BigHumanPlayer : public HumanPlayer{
public:
	BigHumanPlayer(){}
};
