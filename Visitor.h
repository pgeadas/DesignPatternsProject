ref class Player;
ref class HumanPlayer;
ref class Context;
/*interface class Visitor{
public:
	virtual void VisitPlayer(Player^)=0;
};
//due to circular dependencies, its declared in "Resource Observer" 
*/


/*interface class Element{ (Player, Bullet, SpaceShip, Resources...)
public:
	virtual void Accept(Visitor^)=0;
};*/

ref class VisitorCommonFuncs{
public:
	void SpaceShipScreen(SpaceShip^ s, Rectangle rect){
		
		/**make the world circular**/
		if (s->getY() < rect.Top - s->getSize()/2)
		{
			s->setY(rect.Height);	
		}
		else if(s->getY() > rect.Height  )
		{
			s->setY(rect.Top );
		}
		else if (s->getX() < rect.Left - s->getSize()/2 )
		{
			s->setX(rect.Width - s->getSize()/2);
			
		}
		else if(s->getX() > rect.Width - s->getSize()/2 )
		{
			s->setX(rect.Left - s->getSize()/2);
		}
		/**end**/		
	}

	void BulletScreen(Bullet^ bul, Rectangle rect){
	/*eliminate the bullet, if it's out of the screen*/
		if (bul->getY() <= rect.Top  )
		{
			bul->setOnScreen(false);	
		}
		else if(bul->getY() >= rect.Height )
		{
			bul->setOnScreen(false);
		}
		else if (bul->getX() <= rect.Left )
		{
			bul->setOnScreen(false);	
		}
		else if(bul->getX() >= rect.Width )
		{
			bul->setOnScreen(false);
		}
		/**end*/
	}

	void ResourceScreen(Resource^ r, Rectangle rect){
		//checks if the resource is on the screen, if not, sets another position to spawn
		if(r->getY() > rect.Height ){
			r->setPos(rect.Left+(rand()%rect.Width),2);
		}
		while(r->getX()>rect.Width){
			r->setPos(rect.Left+(rand()%rect.Width),2);
		}
		/**end	*/
	}
};


ref class DetailedVisitor : public VisitorCommonFuncs, public Visitor{
	private:
		System::Drawing::Graphics^ g;
		Strategy^ aux;
		static Strategy^ Explosion;
		
	public:
		DetailedVisitor(){}	

		void setExplosionStrategy(Strategy^ e){
			this->Explosion = e;
		}

	virtual void setPaintStuff(System::Drawing::Graphics^ graph){
		this->g = graph;
	}

	virtual void VisitPlayer(Player^ p){
		p->getContext()->DrawStrategy(p,this->g,p->getClientR());
	}

	virtual void VisitResource(Resource^ r){
		this->ResourceScreen(r, r->getClientR());

		//draw trail
		r->drawTrails(this);

		if(!r->getHit()){
			// Draw using the choosen Strategy
			r->getContext()->DrawStrategy(r,this->g);

			/** draw the direction line **/
			//center of the circle
			PointF center = PointF((float)r->getX()+r->getSize()/2,(float)r->getY()+r->getSize()/2); 
			g->DrawLine(Pens::Red,center,r->getH());

			//update position
			r->setPos(r->getX()+(cos(r->getRadians())*RESOURCE_VELOCITY),r->getY()+(sin(r->getRadians())*RESOURCE_VELOCITY));
		}else{
			 this->aux = r->getContext()->getStrategy();
			 r->getContext()->setContext(Explosion);
	
			r->getContext()->DrawStrategy(r,this->g);
			r->getContext()->setContext(aux);
		
			r->setPos(r->getClientR().Left+(rand()%r->getClientR().Width),2); 
				
			while(r->getX()>r->getClientR().Width){
				r->setPos(r->getClientR().Left+(rand()%r->getClientR().Width),2);
			}

			r->setHit(false);
		}

	}

	virtual void VisitSpaceShip(SpaceShip^ s){
		g->SmoothingMode = Drawing2D::SmoothingMode::HighQuality;
		
		this->SpaceShipScreen(s,s->getClientR());
	
		//draw trail
		s->drawTrails(this);

		if(!s->getHit()){
	
			 s->getContext()->DrawStrategy(s,g);
			 
			/** draw the direction line **/
			//center of the circle
			PointF center = PointF((float)s->getX()+s->getSize()/2,(float)s->getY()+s->getSize()/2); 
			//ponto em cima da linha do circulo, correspondente aos graus actuais
			g->DrawLine(Pens::Red,center,s->getH());

			//s->updatePos();
			
		 }else{
			this->aux = s->getContext()->getStrategy();
			s->getContext()->setContext(Explosion);
			s->getContext()->DrawStrategy(s,this->g);
			s->getContext()->setContext(aux);
			s->setX(rand()%s->getClientR().Width);
			s->setY(s->getClientR().Bottom);
			s->setGrades(rand()%360);
			s->setHit(false);
		 }
	}

	virtual void VisitBullet(Bullet^ bul){
		g->SmoothingMode = Drawing2D::SmoothingMode::HighQuality;

		//Checks if the bullet is on the screen
		this->BulletScreen(bul,bul->getClientR());

		// Draw using the choosen Strategy
		bul->getContext()->DrawStrategy(bul,g);

		/** draw the direction line **/
		//center of the circle
		PointF center = PointF((float)bul->getX()+bul->getSize()/2,(float)bul->getY()+bul->getSize()/2); 
		g->DrawLine(Pens::Red,center,bul->getH());

		//Draw trail 
		bul->drawTrails(this);

		//update position
		bul->setPos(bul->getX()+(cos(bul->getRadians())*BULLET_VELOCITY),bul->getY()+(sin(bul->getRadians())*BULLET_VELOCITY));

	}
	virtual void VisitTrail(Trail^ t){
		g->DrawEllipse(Pens::Yellow,(float)t->getCenter().X,(float)t->getCenter().Y,(float)t->getSize(),(float)t->getSize());
				
	}

	virtual void VisitGuidedBullet(GuidedBullet^ gb){
		gb->getContext()->DrawStrategy(gb,g);
		gb->drawTrails(this);
	}
};


ref class SimpleVisitor : public VisitorCommonFuncs, public Visitor{
	private:
		System::Drawing::Graphics^ g;
		Strategy^ aux;
		static Strategy^ Explosion;
	public:
		SimpleVisitor(){}

		void setExplosionStrategy(Strategy^ e){
			this->Explosion = e;
		}

	virtual void setPaintStuff(System::Drawing::Graphics^ graph){
		this->g = graph;
	}

	virtual void VisitPlayer(Player^ p){
	
		p->getContext()->DrawStrategy(p,this->g,p->getClientR());
	}

	virtual void VisitResource(Resource^ r){

		this->ResourceScreen(r, r->getClientR());

		if(!r->getHit()){
			// Draw using the choosen Strategy
			r->getContext()->DrawStrategy(r,this->g);
			r->setPos(r->getX()+(cos(r->getRadians())*RESOURCE_VELOCITY),r->getY()+(sin(r->getRadians())*RESOURCE_VELOCITY));
		}else{
			this->aux = r->getContext()->getStrategy();
			r->getContext()->setContext(Explosion);
			r->getContext()->DrawStrategy(r,this->g);
			r->getContext()->setContext(aux);
			r->setHit(false);
	
			r->setPos(r->getClientR().Left+(rand()%r->getClientR().Width),2); 
			
			while(r->getX()>r->getClientR().Width){
				r->setPos(r->getClientR().Left+(rand()%r->getClientR().Width),2);
			}
		}
		
	}

	virtual void VisitSpaceShip(SpaceShip^ s){

			g->SmoothingMode = Drawing2D::SmoothingMode::HighQuality;
			
			this->SpaceShipScreen(s,s->getClientR());

			if(!s->getHit()){	

				 s->getContext()->DrawStrategy(s,g);

			 }else{
				this->aux = s->getContext()->getStrategy();
				s->getContext()->setContext(Explosion);
				s->getContext()->DrawStrategy(s,this->g);
				s->getContext()->setContext(aux);
				s->setX(rand()%s->getClientR().Width);
				s->setY(s->getClientR().Bottom);
				s->setGrades(rand()%360);
				s->setHit(false);
			 }
	}

	virtual void VisitBullet(Bullet^ bul){
		g->SmoothingMode = Drawing2D::SmoothingMode::HighQuality;
		//check if the bullet is on the screen
		this->BulletScreen(bul,bul->getClientR());

		// Draw using the choosen Strategy
		bul->getContext()->DrawStrategy(bul,g);

		//update position
		bul->setPos(bul->getX()+(cos(bul->getRadians())*BULLET_VELOCITY),bul->getY()+(sin(bul->getRadians())*BULLET_VELOCITY));

	}

	virtual void VisitTrail(Trail^ t){}

	virtual void VisitGuidedBullet(GuidedBullet^ gb){
		gb->getContext()->DrawStrategy(gb,g);
	}

};


ref class DoubleViewVisitor : public VisitorCommonFuncs, public Visitor{
	private:
		Visitor^ simpleV;
		Visitor^ detailedV;
		System::Drawing::Graphics^ g;
		Strategy^ aux;
		static StrategyPlayer^ simple = gcnew DrawSimpleAlgorithm();
		static StrategyPlayer^ detailed = gcnew DrawDetailedShapesAlgorithm();
		static Strategy^ Explosion;

	public:
		DoubleViewVisitor(Visitor^ sV, Visitor^ dV){
			this->simpleV = sV;
			this->detailedV = dV;
		}


	virtual void setPaintStuff(System::Drawing::Graphics^ graph){
		this->g = graph;
	}

	virtual void VisitPlayer(Player^ p){
	//simple
		Rectangle *rect = new Rectangle(0,0,p->getClientR().Width/2,p->getClientR().Height);
	
		p->getContext()->setContext(detailed);
		p->getContext()->DrawStrategy(p,this->g,*rect);

		this->g->DrawLine(Pens::AntiqueWhite,p->getClientR().Width/2,0,p->getClientR().Width/2,p->getClientR().Height);
	//detailed
		Rectangle *rect2 = new Rectangle(p->getClientR().Width/2,0,p->getClientR().Width,p->getClientR().Height);
		p->getContext()->setContext(simple);
		p->getContext()->DrawStrategy(p,this->g,*rect2);


	}

	virtual void VisitResource(Resource^ r){
		
		Rectangle *rect = new Rectangle(0,0,r->getClientR().Width/2,r->getClientR().Height);
		Rectangle *rect2 = new Rectangle(r->getClientR().Width/2,0,r->getClientR().Width,r->getClientR().Height);
		
		r->setClientR(*rect);

		r->Accept(this->simpleV);

		r->setClientR(*rect2);

		r->setPos(r->getX()+r->getClientR().Width/2,r->getY()+0);

		r->Accept(this->detailedV);
		
		r->setPos(r->getX()-r->getClientR().Width/2,r->getY()+0);

	}

	virtual void VisitSpaceShip(SpaceShip^ s){
	

		Rectangle *rect = new Rectangle(0,0,s->getClientR().Width/2,s->getClientR().Height);
		Rectangle *rect2 = new Rectangle(s->getClientR().Width/2,0,s->getClientR().Width,s->getClientR().Height);

		s->setClientR(*rect);

		s->Accept(this->simpleV);

		s->setClientR(*rect2);

		s->setPos(s->getX()+s->getClientR().Width/2,s->getY()+0);

		s->Accept(this->detailedV);

		s->setPos(s->getX()-s->getClientR().Width/2,s->getY()+0);
			
	}

	virtual void VisitBullet(Bullet^ bul){
		g->SmoothingMode = Drawing2D::SmoothingMode::HighQuality;

		Rectangle *rect = new Rectangle(0,0,bul->getClientR().Width/2,bul->getClientR().Height);
		Rectangle *rect2 = new Rectangle(bul->getClientR().Width/2,0,bul->getClientR().Width,bul->getClientR().Height);

		bul->setClientR(*rect);

		bul->Accept(this->simpleV);

		//check if the bullet is on the screen
		bul->setClientR(*rect2);

		//update position
		bul->setPos(bul->getClientR().Width/2+bul->getX(),bul->getY());

		bul->Accept(this->detailedV);

		//update position
		bul->setPos(-bul->getClientR().Width/2+bul->getX(),bul->getY());

	}

	virtual void VisitTrail(Trail^ t){
	/* another way of drawing the trail...
			
			t = static_cast<Trail^>(this->getTrails()[count%this->getTrailSize()]);
			t->refreshPos(this->getX()+(this->getSize()/2)-(t->getSize()/2),this->getY()+(this->getSize()/2)-(t->getSize()/2));
			
			
			for(int i=0;i<this->getTrailSize();i++){
				if(i%2==0 || i%3==0 || i%5==0){
					t = static_cast<Trail^>(this->getTrails()[i]);
					t->refreshPos(this->getX()+(this->getSize()/2)-(t->getSize()/2),this->getY()+(this->getSize()/2)-(t->getSize()/2));
			
				}
			
			}
			

			this->count++;
			this->count=this->count%this->getTrailSize();*/
	
	}

		virtual void VisitGuidedBullet(GuidedBullet^ gb){
			Rectangle *rect = new Rectangle(0,0,gb->getClientR().Width/2,gb->getClientR().Height);
		Rectangle *rect2 = new Rectangle(gb->getClientR().Width/2,0,gb->getClientR().Width,gb->getClientR().Height);

		gb->setClientR(*rect);

		gb->Accept(this->simpleV);

		//check if the bullet is on the screen
		gb->setClientR(*rect2);

		//update position
		gb->setPos(gb->getClientR().Width/2+gb->getX(),gb->getY());


		gb->Accept(this->detailedV);

		//update position
		gb->setPos(-gb->getClientR().Width/2+gb->getX(),gb->getY());


	}

};
