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

	/* �� ������, Ȯ���Ǹ� struct�� ���� */
	/* ������ ������ Ȯ���Ǹ� �ٲߴϴ�. */
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
	// �̵����� ���� �߰�
	//std::vector<std::vector<int>> passable;

	/*	�� �ε� �� Ÿ���� �׸��� �Լ�	*/
	void DrawTile();
	bool loaded;
};

extern Map *map;
/*	actor�� �������� ȭ���� �����˴ϴ�.
	actor�� �����ϸ� ���� ������ �����մϴ�. */
extern Character* actor;
extern std::map<UINT, std::vector<Object*>> object;