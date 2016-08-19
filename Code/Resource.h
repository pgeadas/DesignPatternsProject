ref class Resource : public MobileObject {
	private:
		bool hit;

public:
	Resource();
	void setHit(bool);
	bool getHit();
	virtual void Accept(Visitor^ v) override { v->VisitResource(this);}
};

void Resource::setHit(bool b){
	this->hit = b;
}

bool Resource::getHit(){
	return this->hit;
}

Resource::Resource(){
	this->setSize(30);
	this->setTrailSize(10);
	this->setCount(0);
	this->setTrails();
	this->setContext(gcnew Context(gcnew DrawBrownEllipseAlgorithm()));
}

ref class BigResource : public Resource {
public:
	BigResource();

};


BigResource::BigResource(){
	this->setSize(40);
	this->setTrailSize(10);
	this->setCount(0);
	this->setTrails();
	this->setContext(gcnew Context(gcnew DrawBrownEllipseAlgorithm()));

}