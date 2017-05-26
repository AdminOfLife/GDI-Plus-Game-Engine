#include "stdafx.h"

Scene *scene;

Scene::Scene(HWND hWnd)
	: width(SCREEN_WIDTH), height(SCREEN_HEIGHT)
{
	whiteBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255));
	outGraphics = new Gdiplus::Graphics(hWnd);
	bitmap = new Gdiplus::Bitmap(width, height);
	bufGraphics = new Gdiplus::Graphics(bitmap);
	map = new Map;
}

Gdiplus::Graphics * Scene::GetGraphics()
{
	return bufGraphics;
}

void Scene::Update(std::chrono::milliseconds dt)
{
	bufGraphics->FillRectangle(whiteBrush, 0, 0, width, height);
	map->Update(dt);
	map->Render();
}

void Scene::Render()
{
	outGraphics->DrawImage(bitmap, 0, 0);
}

int Scene::GetWidth()
{
	return width;
}

int Scene::GetHeight()
{
	return height;
}

Scene::~Scene()
{
}
