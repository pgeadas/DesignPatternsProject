#pragma once
ref class SpaceShip: public MobileObject
{
	private:
		bool hit;
		ArrayList^ bullets; 
		PointF center,h;
		Bullet^ b;
		Strategy^ bulletStrategy;
		GuidedBullet^ gb;

	public:
			SpaceShip(double, double, int, int); //pos x,y;size;gravity
			SpaceShip();
			virtual void Accept(Visitor^ v) override {v->VisitSpaceShip(this);}
			void shoot(Bullet^);
			void MoveLeft();
			void MoveRight();
			void slowDown();
			void accelerate();
			void addBullet(int, Bullet^);
			void addGuidedBullet(int, GuidedBullet^);
			ArrayList^ getBullets();
			void setBullets();
			void updatePos();
			void setHit(bool);
			bool getHit();
			Strategy^ getBulletStrategy();
			void setBulletStrategy(Strategy^);
			GuidedBullet^ getGB();

};

GuidedBullet^ SpaceShip::getGB(){
	return gb;
}

SpaceShip::SpaceShip(){
	this->setPos(rand()%600,rand()%600);
	this->setSize(50);
	this->gb = gcnew GuidedBullet();
	this->setTrailSize(20);
	this->setCount(0);
	this->setGrades(-90); //spaceship starts pointed to North
	this->setVelocity(3);
	this->setBulletStrategy(gcnew DrawWhiteEllipseAlgorithm());
	this->setBullets();
	this->setContext(gcnew Context(gcnew DrawRedEllipseAlgorithm()));
	this->setHit(false);
	this->setTrails();
}

SpaceShip::SpaceShip(double x_pos, double y_pos, int _size, int _velocity)
{
	this->setPos(x_pos,y_pos);
	this->setSize(_size);
	this->setTrailSize(20);
	this->setCount(0);
	this->setGrades(-90); //spaceship starts pointed to North
	this->setVelocity(_velocity);
	this->setBulletStrategy(gcnew DrawWhiteEllipseAlgorithm());
	this->setBullets();
	this->setContext(gcnew Context(gcnew DrawRedEllipseAlgorithm()));
	this->setHit(false);
	this->setTrails();
}


Strategy^ SpaceShip::getBulletStrategy(){
	return this->bulletStrategy;
}

void SpaceShip::setBulletStrategy(Strategy^ s){
	this->bulletStrategy = s;
}


void SpaceShip::setHit(bool b){
	this->hit = b;
}

bool SpaceShip::getHit(){
	return this->hit;
}

void SpaceShip::setBullets(){
	this->bullets = gcnew ArrayList();
}

void SpaceShip::addGuidedBullet(int grades, GuidedBullet^ b){

	b->setPos(this->getX()+(this->getSize()/2)-(b->getSize()/2),this->getY()+(this->getSize()/2)-(b->getSize()/2));
	b->setGrades(grades);
	this->gb = b;
}

void SpaceShip::addBullet(int grades, Bullet^ b)
{
	b->setClientR(this->getClientR());
	b->setPos(this->getX()+(this->getSize()/2)-(b->getSize()/2),this->getY()+(this->getSize()/2)-(b->getSize()/2));
	b->setGrades(grades);
	this->bullets->Add(b);
}

void SpaceShip::MoveLeft()
{
	this->setGrades((this->getGrades()-10) % 360);
}

void SpaceShip::MoveRight()
{
	this->setGrades((this->getGrades()+10) % 360);
}

ArrayList^ SpaceShip::getBullets()
{
	return this->bullets;
}

void SpaceShip::accelerate() 
{
	if(this->getVelocity()<MAX_VELOCITY)
		this->setVelocity(this->getVelocity()+1);
}

void SpaceShip::slowDown()
{
	if(this->getVelocity()>MIN_VELOCITY)
		this->setVelocity(this->getVelocity()-1);
}

void SpaceShip::updatePos(){
	//update position
	this->setPos(this->getX()+(cos(this->getRadians())*this->getVelocity()),this->getY()+(sin(this->getRadians())*this->getVelocity()));
}

void SpaceShip::shoot(Bullet^ b)
{
	this->addBullet(this->getGrades(), b);		
}


ref class BigSpaceShip : public SpaceShip{
public:
	BigSpaceShip();
};

BigSpaceShip::BigSpaceShip(){
	this->setSize(75);
}


ref class EnemySpaceShip : public SpaceShip{
private: 
	int counter;
	int playerGrades;
public:
	EnemySpaceShip();
	void updatePos();
	void addCounter();
	int getCounter();
	void setPlayerGrades(int);
	int getPlayerGrades();
};

void EnemySpaceShip::updatePos(){
	//update position
	this->setPos(this->getX()+(cos(this->getRadians())*this->getVelocity()),this->getY()+(sin(this->getRadians())*this->getVelocity()));
}

void EnemySpaceShip::addCounter(){
	this->counter++;
	this->counter = this->counter%9999999;
}

int EnemySpaceShip::getCounter(){
	return this->counter;
}

int EnemySpaceShip::getPlayerGrades(){
	return this->playerGrades;
}

void EnemySpaceShip::setPlayerGrades(int i){
	this->playerGrades = i;
}

EnemySpaceShip::EnemySpaceShip(){
	this->setSize(50);
	this->setHit(false);
	this->setPos(rand()%1000,rand()%1000);
	this->setGrades(rand()%360);
	this->setContext(gcnew Context(gcnew DrawGreenEllipseAlgorithm()));
	this->setTrails();
	counter=0;
}

ref class BigEnemySpaceShip : public EnemySpaceShip{
public:
	BigEnemySpaceShip();
};

BigEnemySpaceShip::BigEnemySpaceShip(){
	this->setHit(false);
	this->setSize(75);
	this->setTrails();
}