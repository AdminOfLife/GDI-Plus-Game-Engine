#include "stdafx.h"

Map *map = nullptr;
Character* actor = nullptr;
std::map<UINT, std::vector<Object*>> object;

Map::Map()
{
	loaded = false;
	tileData = nullptr;
	tileSet = nullptr;
	tileBitmap = nullptr;
	screen_x = 0;
	screen_y = 0;
}

void Map::DrawTile()
{
	if (tileSet == nullptr)
		return;
	if (tileData == nullptr)
		return;
	if (tileBitmap == nullptr)
		return;

	Gdiplus::Graphics tileGraphics(tileBitmap);
	/*
		아래는 타일이 없는 영역의 바탕 색 지정을 위한 코드
		Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 255, 255));
		tileGraphics.FillRectangle(&whiteBrush, 0, 0, size_x, size_y);
	*/
	int divisor = tileSet->GetWidth() / 32;
	for (int layer = 0; layer < MAX_LAYER_LEVEL; layer++)
	{
		for (int x = 0; x < tile_x; x++)
		{
			for (int y = 0; y < tile_y; y++)
			{
				if (tileData[layer][x][y] == -1)
					continue;
				tileGraphics.DrawImage(tileSet, Gdiplus::Rect(x * 32, y * 32, 32, 32),
					tileData[layer][x][y] % divisor * 32, tileData[layer][x][y] / divisor * 32, 32, 32, Gdiplus::Unit::UnitPixel);
			}
		}
	}
}

void Map::Transition(int id)
{
	Unload();
	Load(id);
	DrawTile();
}

void Map::Load(int id)
{
	if (loaded)
		return;
	mapId = id;
	
	// 추후 비동기 io 로 변경
	// 맵 데이터 struct화 한 뒤 binary로 읽을 예정
	
	char dataPath[255];
	int tileSetId;
	sprintf(dataPath, "Map/Map%04d.mapinfo", mapId);
	std::wifstream inFile(dataPath);
	inFile.imbue(std::locale(inFile.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));

	if (inFile.fail())
	{
		MessageBox(0, "맵을 찾을 수 없습니다.", "오류", MB_OK);
		return;
	}
	inFile >> mapId;
	inFile >> mapName;
	inFile >> tileSetId;
	swprintf(tileSetPath, L"Map/tiles/%d.tile", tileSetId);
	tileSet = ResourceManager<Gdiplus::Image>::Load(tileSetPath);
	inFile >> tile_x;
	inFile >> tile_y;

	size_x = tile_x * 32;
	size_y = tile_y * 32;
	tileBitmap = new Gdiplus::Bitmap(size_x, size_y);

	tileData = new int**[MAX_LAYER_LEVEL];
	for (int i = 0; i < MAX_LAYER_LEVEL; i++)
	{
		tileData[i] = new int*[tile_x];
		for (int j = 0; j < tile_x; j++)
		{
			tileData[i][j] = new int[tile_y];
			for (int k = 0; k < tile_y; k++)
			{
				inFile >> tileData[i][j][k];
			}
		}
	}
}

void Map::Unload()
{
	if (!loaded)
		return;
	if (tileData != nullptr)
	{
		for (int i = 0; i < MAX_LAYER_LEVEL; i++)
		{
			for (int j = 0; j < tile_x; j++)
			{
				delete[] tileData[i][j];
			}
			delete[] tileData[i];
		}
		delete[] tileData;
		tileData = nullptr;
	}

	if (tileBitmap != nullptr)
	{
		delete tileBitmap;
		tileBitmap = nullptr;
	}

	if (tileSet != nullptr)
	{
		ResourceManager<Gdiplus::Image>::Unload(tileSetPath);
		tileSet = nullptr;
	}
}

void Map::Spawn(Object * _object)
{
	object[mapId].push_back(_object);
}


void Map::Update(std::chrono::milliseconds dt)
{
	std::vector<Object*> mapObject = object[mapId];
	for (auto const &entity : mapObject)
	{
		entity->UpdateObject(dt);
	}

	if (actor != nullptr)
	{
		int actor_x, actor_y;
		int screen_width = scene->GetWidth(), screen_height = scene->GetHeight();
		actor->GetPosition(actor_x, actor_y);

		screen_x = actor_x - screen_width / 2;
		screen_y = actor_y - screen_height / 2;

		if (screen_x < 0)
			screen_x = 0;
		if (screen_y < 0)
			screen_y = 0;
		if (screen_x > size_x - screen_width)
			screen_x = size_x - screen_width;
		if (screen_y > size_y - screen_height)
			screen_y = size_y - screen_height;
		if (size_x < screen_width)
			screen_x = (size_x - screen_width) / 2;
		if (size_y < screen_height)
			screen_y = (size_y - screen_height) / 2;
	}
}

void Map::Render()
{
	std::vector<Object*> mapObject = object[mapId];
	scene->GetGraphics()->DrawImage(tileBitmap, 0, 0, screen_x, screen_y, scene->GetWidth(), scene->GetHeight(), Gdiplus::Unit::UnitPixel);
	for (auto const &entity : mapObject)
	{
		entity->RenderObject(screen_x, screen_y);
	}
}

Map::~Map()
{
}
