#pragma once
#define MAX_LAYER_LEVEL 3
class Map
{
public:
	Map();
	Gdiplus::Bitmap *tileBitmap;
	void Transition(int id);
	void Spawn(Object* _object);
	void Update(std::chrono::milliseconds dt);
	void Render();
	~Map();
private:
	void Load(int id);
	void Unload();

	int screen_x;
	int screen_y;

	/* 맵 데이터, 확정되면 struct로 묶기 */
	/* 데이터 구조가 확립되면 바꿉니다. */
	int mapId;
	std::wstring mapName;
	Gdiplus::Image *tileSet;
	WCHAR tileSetPath[255];
	int size_x;
	int size_y;
	int tile_x;
	int tile_y;
	// tileData[layer][x][y]
	int ***tileData;
	// 이동정보 추후 추가
	//std::vector<std::vector<int>> passable;

	/*	맵 로드 시 타일을 그리는 함수	*/
	void DrawTile();
	bool loaded;
};

extern Map *map;
/*	actor를 기준으로 화면이 구성됩니다.
	actor를 변경하면 시점 변경이 가능합니다. */
extern Character* actor;
extern std::map<UINT, std::vector<Object*>> object;