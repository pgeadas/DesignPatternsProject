#pragma once

//abstract factory
interface class Factory {
public:
        virtual Bullet^ createBulletObject()=0;
		virtual SpaceShip^ createSpaceShipObject()=0;
		virtual EnemySpaceShip^ createEnemySpaceShipObject()=0;
		virtual Resource^ createResourceObject()=0;
		virtual HumanPlayer^ createHumanPlayer()=0;
		virtual CPUPlayer^ createCPUPlayer()=0;
};

//concrete factory 1
ref class RegularFactory : public Factory{	
public:
	RegularFactory(){}
	virtual Bullet^ createBulletObject(){
		return gcnew Bullet();
	}
	virtual SpaceShip^ createSpaceShipObject(){
		return gcnew SpaceShip();
	}

	virtual EnemySpaceShip^ createEnemySpaceShipObject(){
		return gcnew EnemySpaceShip();
	}

	virtual Resource^ createResourceObject(){
		return gcnew Resource();
	}
	virtual HumanPlayer^ createHumanPlayer(){
		return gcnew HumanPlayer();

	}
	virtual CPUPlayer^ createCPUPlayer(){
		return gcnew CPUPlayer();
	}
};

//concrete factory 2
ref class BigFactory : public Factory {
public:
	BigFactory(){}
	virtual Bullet^ createBulletObject(){
		return gcnew BigBullet();
	}
	virtual SpaceShip^ createSpaceShipObject(){
		return gcnew BigSpaceShip();
	}

	virtual EnemySpaceShip^ createEnemySpaceShipObject(){
		return gcnew BigEnemySpaceShip();
	}
	virtual Resource^ createResourceObject(){
		return gcnew BigResource();
	}
	virtual HumanPlayer^ createHumanPlayer(){
		return gcnew BigHumanPlayer();

	}
	virtual CPUPlayer^ createCPUPlayer(){
		return gcnew BigCPUPlayer();
		
	}
};


