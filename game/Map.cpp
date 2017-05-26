#include "stdafx.h"

Map *map = nullptr;
Object* actor = nullptr;
std::map<UINT, std::vector<Object*>> object;

Map::Map()
{
	tileSet = nullptr;
	tileBitmap = nullptr;
	screen_x = 0;
	screen_y = 0;
	Load(L"ff");
}

void Map::DrawTile()
{
	if (tileSet == nullptr)
		return;
	Gdiplus::Graphics tileGraphics(tileBitmap);
	Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 255, 255));
	tileGraphics.FillRectangle(&whiteBrush, 0, 0, size_x, size_y);

	for (int x = 0; x < size_x / 32; x++)
	{
		for (int y = 0; y < size_y / 32; y++)
		{
			tileGraphics.DrawImage(tileSet, Gdiplus::Rect(x * 32, y * 32, 32, 32), 0, 0, 32, 32, Gdiplus::Unit::UnitPixel);
			if (rand()%100 < 10)
				tileGraphics.DrawImage(tileSet, Gdiplus::Rect(x * 32, y * 32, 32, 32), 32, 0, 32, 32, Gdiplus::Unit::UnitPixel);
		}
	}
}

void Map::Transition(UINT id)
{
	mapId = id;

	DrawTile();

}

void Map::Load(std::string name)
{
	std::string spritePath("Map/");
	spritePath += name;
	std::string dataPath;
	// 추후 비동기 io 로 변경
	// 임시로 설정
	size_x = 2048;
	size_y = 1536;

	tileSet = ResourceManager<Gdiplus::Image>::Load(L"map/1/tiles/");

	if (tileBitmap != nullptr)
		delete tileBitmap;

	tileBitmap = new Gdiplus::Bitmap(size_x, size_y);
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
