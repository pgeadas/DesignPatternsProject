#pragma once

interface class Strategy;
interface class Visitor;

ref class Trail{
private:
	PointF c;
	int size;
	bool paint;
	
public:
	Trail(double, double);
	int getSize();
	void refreshPos(double,double);
	PointF getCenter();
	virtual void Accept(Visitor^ v){ v->VisitTrail(this);}

};


void Trail::refreshPos(double x, double y){
	this->c.X=x;
	this->c.Y=y;
}


int Trail::getSize(){
	return this->size;
}

Trail::Trail(double x, double y){
	this->c = PointF(x,y);
	this->size=6;
	this->paint = true;
}

PointF Trail::getCenter(){
	return this->c;

}


ref class  MobileObject : public ResourceSubject
{
	
	private:
		int size;  
		int velocity; 
		int  grades; //orientation of the object
		unsigned trailSize;//size of the trail that the objects will left
		ArrayList^ trails;
		int count;
		double x,y;
		PointF center;
		PointF h;
		Context^ context;
		Trail^ t;
		Rectangle clientR;
		Strategy^ st;

	public:
		void setClientR(Rectangle r);
		Rectangle getClientR();
		void setPos(double, double);
		double getY();
		void setY(double);
		double getX();
		void setX(double);
		int getSize();
		void setSize(int);
		int getVelocity();
		void setVelocity(int);
		double getRadians();
		int getGrades();
		void setGrades(int);
		int getTrailSize();
		void setTrailSize(unsigned);
		Rectangle GetFrame();
		Rectangle GetHalfFrame();
		Rectangle GetQuarterFrame();
		Rectangle GetDoubleFrame();
		ArrayList^ getTrails();
		void setTrails();
		void setCount(int);
		int getCount();
		void drawTrails(Visitor^);
		Context^ getContext();
		void setContext(Context^);
		PointF getCenter();
		void setH();
		PointF getH();
		void addX(double);
		void addY(double);
		virtual void Accept(Visitor^){}

};

void MobileObject::addX(double x){
	this->setX(this->getX()+x);
}

void MobileObject::addY(double y){
	this->setY(this->getY()+y);
}

void MobileObject::setH(){
	this->h = PointF((float)this->getX()+this->getSize()/2+(cos(this->getRadians())*this->getSize()/2),(float)this->getY()+this->getSize()/2+(sin(this->getRadians())*this->getSize()/2));
}

PointF MobileObject::getH(){
	return PointF((float)this->getX()+this->getSize()/2+(cos(this->getRadians())*this->getSize()/2),(float)this->getY()+this->getSize()/2+(sin(this->getRadians())*this->getSize()/2));
}

void MobileObject::setClientR(Rectangle r){
	this->clientR = r;
}
Rectangle MobileObject::getClientR(){
	return this->clientR;
}

PointF MobileObject::getCenter(){
	return this->center;
}

void MobileObject::setContext(Context^ c){
	this->context = c;
}

Context^ MobileObject::getContext(){
	return this->context;
}


void MobileObject::drawTrails(Visitor^ v){
	
		for(int i=0;i<this->getTrailSize();i++){
					t = static_cast<Trail^>(this->getTrails()[i]);
					t->Accept(v);
		}
		
		this->getTrails()->RemoveAt(count%this->getTrailSize());
		this->getTrails()->Add(gcnew Trail(this->getX()+(this->getSize()/2)-(t->getSize()/2),this->getY()+(this->getSize()/2)-(t->getSize()/2)));
			
		this->count++;
		this->count=this->count%this->getTrailSize();
}

ArrayList^ MobileObject::getTrails(){
	return this->trails;
}

void MobileObject::setTrails(){
	this->trails = gcnew ArrayList();
	for(int i=0;i<this->getTrailSize();i++){
		this->trails->Add(gcnew Trail(this->getX()+(this->getSize()/2),this->getY()+(this->getSize()/2)));
	}
}

int MobileObject::getCount(){
	return this->count;
}

void MobileObject::setCount(int c){
	this->count = c;
}

int MobileObject::getTrailSize(){
	return this->trailSize;
}

void MobileObject::setTrailSize(unsigned trail){
	this->trailSize = trail;
}


double MobileObject::getRadians(){
	return this->getGrades()*PI/180;
}

int MobileObject::getGrades(){
	return this->grades;
}

void MobileObject::setGrades(int g){
	this->grades = g;
}

//define gravity (will influence the velocity of the objects)
int MobileObject::getVelocity(){
	return this->velocity;
}

void MobileObject::setVelocity(int v){
	this->velocity = v;
}


//Define position
void MobileObject::setPos(double x, double y)
{
	this->center.X = x ;
	this->center.Y = y ;
}

double MobileObject::getY() 
{
	return this->center.Y;
}

double MobileObject::getX()
{
	return this->center.X ;
}

void MobileObject::setX(double x)
{
	this->center.X = x ;
}

void MobileObject::setY(double y)
{
	this->center.Y = y;
}


int MobileObject::getSize()
{
	return size;
}

void MobileObject::setSize(int _size){
	this->size = _size;
}


Rectangle MobileObject::GetFrame(){
	     Rectangle *rect = new Rectangle((float)this->getX(), (float)this->getY(), (float)this->getSize(), (float)this->getSize());
		 return *rect;
}

Rectangle MobileObject::GetHalfFrame(){
	     Rectangle *rect = new Rectangle((float)this->getX()+(float)this->getSize()/4, (float)this->getY()+(float)this->getSize()/4, (float)this->getSize()/2, (float)this->getSize()/2);
		 return *rect;
}

Rectangle MobileObject::GetQuarterFrame(){
	     Rectangle *rect = new Rectangle((float)this->getX()+(float)this->getSize()/4, (float)this->getY()+(float)this->getSize()/4, (float)this->getSize()/4, (float)this->getSize()/4);
		 return *rect;
}

Rectangle MobileObject::GetDoubleFrame(){
	     Rectangle *rect = new Rectangle((float)this->getX()-(float)this->getSize()/2, (float)this->getY()-(float)this->getSize()/2, (float)this->getSize()*2, (float)this->getSize()*2);
		 return *rect;
}