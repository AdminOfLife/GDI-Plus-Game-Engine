#pragma once
class Character : public Object
{
public:
	Character();
	~Character();
	virtual void UpdateObject(std::chrono::milliseconds dt);
	virtual void RenderObject(int screen_x, int screen_y);
	void SetPosition(int _x, int _y);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Stop();
protected:
	Gdiplus::Image *spriteSet;
	InputComponent InputComponent;
	BOOL isMoving;
	BOOL movinvoid[4];
	UINT direction;
	UINT frameIndex;
};
