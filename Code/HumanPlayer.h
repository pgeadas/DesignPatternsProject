
ref class HumanPlayer : public Player{
protected:
	PlayerContext^ context;
	Factory^ factory;
public:
	HumanPlayer();
	HumanPlayer(unsigned,unsigned, Factory^); //initial lifes and energy	
	HumanPlayer(Factory^);
	PlayerContext^ getContext();
	void draw(Graphics^, Rectangle);
	void setFactory(Factory^);
	Factory^ getFactory();
};



HumanPlayer::HumanPlayer(unsigned lifes, unsigned energy, Factory^ fact){
	this->setFactory(fact);
	this->setLifes(lifes);
	this->setEnergy(energy);
	this->setSpaceShip(static_cast<SpaceShip^>(fact->createSpaceShipObject()));
	this->setScore(0);
	this->context = gcnew PlayerContext(gcnew DrawShapesAlgorithm());
}

HumanPlayer::HumanPlayer(Factory^ fact){
	this->setFactory(fact);
	this->setLifes(5);
	this->setEnergy(200);
	this->setSpaceShip(static_cast<SpaceShip^>(fact->createSpaceShipObject()));
	this->setScore(0);
	this->context = gcnew PlayerContext(gcnew DrawShapesAlgorithm());
}

void HumanPlayer::setFactory(Factory^ fact){
	this->factory = fact;
}

Factory^ HumanPlayer::getFactory(){
	return this->factory;
}


PlayerContext^ HumanPlayer::getContext(){
	return this->context;
}

void HumanPlayer::draw(Graphics^ g, Rectangle r){
/*	// Create image.
	Image^ newImage = Image::FromFile("hp.bmp");
// Create Point for upper-left corner of image.
PointF ulCorner = PointF( 100, 100);
// Draw image to screen.
g->DrawImage(newImage, ulCorner);*/
	this->getContext()->DrawStrategy(this,g,r);

}

ref class BigHumanPlayer : public HumanPlayer{
public:
	BigHumanPlayer(Factory^);
	BigHumanPlayer();
};

BigHumanPlayer::BigHumanPlayer(Factory^ fact){
	this->setFactory(fact);
	this->setLifes(10);
	this->setEnergy(200);
	this->setSpaceShip(static_cast<SpaceShip^>(fact->createSpaceShipObject()));
	this->setScore(0);
	this->context = gcnew PlayerContext(gcnew DrawShapesAlgorithm());
}

BigHumanPlayer::BigHumanPlayer(){

}