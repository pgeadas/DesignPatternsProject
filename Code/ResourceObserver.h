
using namespace System::Drawing;

interface class Strategy;
interface class StrategyPlayer;
ref class Context;
ref class Player;
ref class Resource;
ref class SpaceShip;
ref class Bullet;
ref class GuidedBullet;
ref class Trail;

//Visitor interface class
interface class Visitor{
public:
	virtual void VisitPlayer(Player^)=0;
	virtual void VisitResource(Resource^)=0;
	virtual void VisitSpaceShip(SpaceShip^)=0;
	virtual void VisitBullet(Bullet^)=0;
	virtual void VisitTrail(Trail^)=0;
	virtual void VisitGuidedBullet(GuidedBullet^)=0;
	virtual void setPaintStuff(Graphics^)=0;
};

//Resource Subject class
ref class ResourceSubject;

interface class ResourceObserver{
public:
	virtual void Update(ResourceSubject^)=0;
};

ref class ResourceSubject{
private:
	ArrayList^ observers;
public:
	void Attach(ResourceObserver^);
	void Detach(ResourceObserver^);
	void Notify();
protected:
	ResourceSubject(){this->observers = gcnew ArrayList();}
};

void ResourceSubject::Attach(ResourceObserver^ o) {
        this->observers->Add(o);
}

void ResourceSubject::Detach(ResourceObserver^ o) {
        this->observers->Remove(o);
}

void ResourceSubject::Notify () {
	System::Collections::IEnumerator^ i = this->observers->GetEnumerator();
      
	while(i->MoveNext()){
		static_cast<ResourceObserver^>(i->Current)->Update(this);
	}  
}