ref class Subject;
ref class Player;
ref class HumanPlayer;

interface class State{
	virtual void drawState(Player^);
	virtual void changeState(Player^, State^);
};


ref class PlayerShoot : public State{
public:
	PlayerShoot(){}
	virtual void drawState(Player^ p){
	}

	virtual void changeState(Player^ p, State^ s){}
};

ref class PlayerNotShoot : public State{
public:
	PlayerNotShoot(){}
	virtual void drawState(Player^ p){}

	virtual void changeState(Player^ p, State^ s){}
};


