ref class Subject;

interface class Observer{
public:
	virtual void Update(Subject^)=0;
};

ref class Subject{
private:
	ArrayList^ observers;
public:
	void Attach(Observer^);
	void Detach(Observer^);
	void Notify();
protected:
	Subject(){this->observers = gcnew ArrayList();}
};


void Subject::Attach(Observer^ o) {
        this->observers->Add(o);
}

void Subject::Detach(Observer^ o) {
        this->observers->Remove(o);
}

void Subject::Notify () {
	System::Collections::IEnumerator^ i = this->observers->GetEnumerator();
      
	while(i->MoveNext()){
		static_cast<Observer^>(i->Current)->Update(this);
	}    
}