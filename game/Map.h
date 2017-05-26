class Map
{
public:
	Map();
	Gdiplus::Bitmap *tileBitmap;
	void Load(std::wstring filePath);
	void Spawn(Object* _object);
	void Update(std::chrono::milliseconds dt);
	void Render();
	~Map();
private:
	int screen_x;
	int screen_y;

	/* �� ������, Ȯ���Ǹ� struct�� ���� */
	UINT mapId;
	std::wstring mapName;
	Gdiplus::Image *tileSet;
	int size_x;
	int size_y;
	/*	�Ʒ��� tile ������ ������ Ȯ���Ǹ� �ٲߴϴ�. */
	std::vector<std::vector<int>> tile;
	std::vector<std::vector<int>> passable;

	/*	�� �ε� �� Ÿ���� �׸��� �Լ�	*/
	void DrawTile();
};

extern Map *map;
/*	actor�� �������� ȭ���� �����˴ϴ�.
actor�� �����ϸ� ���� ������ �����մϴ�. */
extern Object* actor;
extern std::map<UINT, std::vector<Object*>> object;