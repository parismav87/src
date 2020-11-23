#ifndef MOVE_H_
#define MOVE_H_


class Move{

private:
	int x1, y1, x2, y2;
	int score;
	int type;
public:
	Move(int x1, int y1, int x2, int y2, int score, int type);
	int getScore();
	void getCoordinates(int coords[]);
	int getType();
};


Move::Move(int x1, int y1, int x2, int y2, int score, int type){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->score = score;
	this->type = type;
}

int Move::getScore(){
	return this->score;
}

void Move::getCoordinates(int coords[]){
	coords[0] = this->x1;
	coords[1] = this->y1;
	coords[2] = this->x2;
	coords[3] = this->y2;
}

int Move::getType(){
	return this->type;
}


#endif /* MOVE_H_ */
