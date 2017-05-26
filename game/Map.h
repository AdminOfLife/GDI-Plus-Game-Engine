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

	/* 맵 데이터, 확정되면 struct로 묶기 */
	UINT mapId;
	std::wstring mapName;
	Gdiplus::Image *tileSet;
	int size_x;
	int size_y;
	/*	아래는 tile 데이터 구조가 확립되면 바꿉니다. */
	std::vector<std::vector<int>> tile;
	std::vector<std::vector<int>> passable;

	/*	맵 로드 시 타일을 그리는 함수	*/
	void DrawTile();
};

extern Map *map;
/*	actor를 기준으로 화면이 구성됩니다.
actor를 변경하면 시점 변경이 가능합니다. */
extern Object* actor;
extern std::map<UINT, std::vector<Object*>> object;