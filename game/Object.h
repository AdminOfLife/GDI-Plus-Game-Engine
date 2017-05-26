class Object 
{
public:
	Object();
	virtual void UpdateObject(std::chrono::milliseconds dt) = 0;
	virtual void RenderObject(int screen_x, int screen_y) = 0;
	void GetPosition(int &_x, int &_y);
	~Object();
protected:
	int x;
	int y;
	int speed;
};

