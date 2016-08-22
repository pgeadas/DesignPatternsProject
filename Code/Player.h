#pragma once
interface class Factory;
interface class State;
ref class PlayerContext;
ref class ViewVisitor;

ref class Player : public Subject
{
	private:
		State^ actualState; //set as NotHit at the very beginning
		SpaceShip^ playerSpaceShip;
		PlayerContext^ context;
		Factory^ factory;
		int lifes;
		int energy;
		unsigned score;
		int shield;
		Rectangle clientR;

	public:
		void setClientR(Rectangle r);
		Rectangle getClientR();
		void setLifes(unsigned);
		void setEnergy(int);
		void setShield(unsigned);
		int getShield();
		void addShield(unsigned s);
		void decShield(unsigned s);
		void setSpaceShip(SpaceShip^);
		void setScore(unsigned);
		void addScore(unsigned);
		int getLifes();
		int getEnergy();
		SpaceShip^ getSpaceShip();
		int getScore();
		void setContext(PlayerContext^);
		PlayerContext^ getContext();
		void changeState(State^);
		virtual void Accept(Visitor^ v){}
};

void Player::setClientR(Rectangle r){
	this->clientR = r;
}
Rectangle Player::getClientR(){
	return this->clientR;
}


void Player::changeState(State^ s){
	this->actualState = s;
}


PlayerContext^ Player::getContext(){
	return this->context;
}

void Player::setContext(PlayerContext^ c){
	this->context = c;
}


void Player::setLifes(unsigned l){
	this->lifes = l;
}

void Player::setEnergy(int e){
	this->energy = e;
}

void Player::setSpaceShip(SpaceShip^ s){
	this->playerSpaceShip = s;
}

void Player::setScore(unsigned s){
	this->score = s;
}

void Player::addScore(unsigned s){
	this->score += s;
}

int Player::getLifes(){
	return this->lifes;
}
			
int Player::getEnergy(){
	return this->energy;
}
			
SpaceShip^ Player::getSpaceShip(){
	return this->playerSpaceShip;
}
			
int Player::getScore(){
	
	return this->score;
}

int Player::getShield(){
	return this->shield;
}

void Player::addShield(unsigned s){
	if(this->getShield()!=200){
		this->shield += s;
		if(this->shield>200){
			this->shield = 200;
		}
	}
}

void Player::decShield(unsigned s){
	if(this->getShield()!=0){
		this->shield -= s;
		if(this->shield <=0){
			this->shield=0;
		}
	}
}

void Player::setShield(unsigned s){
	this->shield = s;
}
