class Scene 
{
public:
	Scene(HWND hWnd);
	Gdiplus::Graphics *GetGraphics();
	void Update(std::chrono::milliseconds dt);
	void Render();
	int GetWidth();
	int GetHeight();
	~Scene();
private:
	int width, height;
	Gdiplus::Graphics *outGraphics;
	Gdiplus::Graphics *bufGraphics;
	Gdiplus::Bitmap *bitmap;
	Gdiplus::SolidBrush *whiteBrush;
};

extern Scene *scene;

// �������� �����Ǵ� �Լ�
void StartEvent();