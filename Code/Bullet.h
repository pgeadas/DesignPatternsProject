#pragma once


ref class Bullet: public MobileObject{
	private:
		bool onScreen;

	public:
		Bullet();
		Bullet(int);
		void setOnScreen(bool);
		bool isOnScreen();
		void updatePos();

		virtual void Accept(Visitor^ v) override {v->VisitBullet(this);}
};

Bullet::Bullet(){
	this->setSize(10);
	this->setTrailSize(5);
	this->setCount(0);
	this->setTrails();
	this->setOnScreen(true);
}

Bullet::Bullet(int size){
	this->setSize(size);
	this->setTrailSize(5);
	this->setCount(0);
	this->setTrails();
	this->setOnScreen(true);
}

void Bullet::updatePos(){
	//update position
	this->setPos(this->getX()+(cos(this->getRadians())*this->getVelocity()),this->getY()+(sin(this->getRadians())*this->getVelocity()));
}


void Bullet::setOnScreen(bool b){
	this->onScreen = b;
}

bool Bullet::isOnScreen(){
	return this->onScreen;
}


ref class GuidedBullet : public Bullet{
public:
	GuidedBullet();
	void updatePos(double, double);
	void updatePos();
	virtual void Accept(Visitor^ v) override {v->VisitGuidedBullet(this);}


};

GuidedBullet::GuidedBullet(){
	this->setSize(10);
	this->setTrailSize(5);
	this->setCount(0);
	this->setTrails();
	this->setOnScreen(false);

}


void GuidedBullet::updatePos(double x, double y){
	//update position
	this->addX(x);
	this->addY(y);
}

void GuidedBullet::updatePos(){
	//update position
	this->setPos(this->getX()+(cos(this->getRadians())*this->getVelocity()),this->getY()+(sin(this->getRadians())*this->getVelocity()));
}


ref class BigBullet : public Bullet{
public:
	BigBullet();
};

BigBullet::BigBullet(){
	this->setSize(20);

}