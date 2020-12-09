#include "Game.h"
#include<iostream>
#include <glm.hpp>
#include <time.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <math.h>


Game::Game()
{
	
}

Game::~Game()
{
}

void Game::Init()
{
	std::cout << " Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	resourceManager = ResourceManager::GetPtr();
	
	auto resourceManger = ResourceManager::GetPtr();
	resourceManger->Add(ResourceType::GUILine, "Line");

	resourceManger->Wait();
	player = new Player();

	LoadShaders();

	

	resourceManger->Load();
	m_image = (Graphic::GUILine*) resourceManager->GetElement("Line");
	srand(time(NULL));
	gui = new Graphic::GUI(m_image, player->GetCamera(), shaderManager);
	

	

	
}

void Game::LoadShaders()
{
	shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(player->GetCamera());
	shaderManager->LoadShaders("gui", "Assets/Shaders/gui.vert", "Assets/Shaders/gui.frag");

}

void Game::Draw()
{
	shaderManager->draw();
}

void Game::Update(unsigned int delta)
{
	
	
	double agl = 0;
	
	
	/*for (int i = 0; i < 200; i++)
		m_image->PutPixel(rand() % 1024, rand() % 1024, rand() % 255, rand() % 255, rand() % 255, 255);*/

	for (int i = 0; i < 1024; i++) {
		m_image->PutPixel((i *cos(agl) -(512 *sin(agl))), (i* sin(agl) + (512 *cos (agl))),255,0,0,255);//corregir 
	}

	for (int i = 0; i < 1024; i++) {
		m_image->PutPixel((i * sin(agl) + (512 * cos(agl))), (i * cos(agl) - (512 * sin(agl))), 255, 0, 0, 255);//corregir
	}
	
	
	//DrawCircunferencia(100,200,100);
	DrawlineBressenham(100, 100, 400, 200);
	//x´= c*x y´=d*y (vertice 200 * 200)
	//CurvasdeBesier(200, 200 , 200, 300 , 300, 300 , 300, 200);
	m_image->Load();
}

bool Game::MouseInput(int x, int y, bool leftbutton)
{
	if (x != -1 || y != -1)
		player->GetCamera()->mouseControl(x, y);
	return false;
}

bool Game::Input(std::map<int, bool> keys)
{
	player->GetCamera()->keyControl(keys, platform->GetDeltaTime());
	
	return false;
}

void Game::Close()
{
	std::cout << " Close Init" << std::endl;
}
void Game::Pendiente() {
	float poY = 200;
	float poX = 200;
	float poYb = 400;
	float poXb = 200;
	float X = (poX, poY);
	float Y = (poXb, poYb);
	float c;
	float primeraop;
	float segundaop;
	float m;

	primeraop = poYb - poY;// Yb-Ya
	segundaop = poXb - poX;// Xb-Xa
	m = primeraop / segundaop;// (Yb-Ya)/(Xb-Xa)
	c = poY - (m * poX);
	if (m>1) {

	}

}

void Game::DrawlineDDA(float XA, float YA, float XB, float YB) {
	float X = XA;
	float Y = YA;
	float i=0;
	float DENO;
	float dx;
	float dy;
	float Xinc;
	float Yinc;

	dy = YB - YA;
	dx = XB - XA;
	if (dy <dx) {
		DENO = dx;
	}
	else if (dy >= dx) {
		DENO = dy;
	}
	Xinc = dx / DENO;
	Yinc = dy / DENO;
	for (int i = 0; i < DENO; i++) {

		m_image->PutPixel(X, Y, 255, 0, 0, 255);
	}
	
}

void Game::DrawlineBres(float XA, float YA, float XB, float YB){
	float dx;
	float dy;
	float p;
	float x;
	float y;
	float i = 0;

	dx = XB-XA;
	dy = YB - YA;
	p = (2 * dy) - dx;

	x = XA;
	y = YA;
	for (i; i < dx; i++) {
		if (p<0) {
			x = x + 1;
			y = y;
			p = p + (2 * dy);

		}
		else {
			x = x + 1;
			y = y + 1;
			p = p + (2 * dy) - (2 * dx);
		}
		m_image->PutPixel(x, y, 255, 0, 0, 255);
	}
	

}

void Game::DrawlineBresmay(float XA, float YA, float XB, float YB) {
	float dx;
	float dy;
	float p;
	float x;
	float y;
	float i = 0;
	dx = XB - XA;
	dy = YB - YA;
	
	x = XA;
	y = YA;
	p = (2 * dx) - dy;
	
	for (i; i < dy; i++) {
		m_image->PutPixel(x, y, 255, 0, 0, 255);
		if (p < 0) {
			x = x;
			y = y + 1;
			p = p + (2 * dx);

		}
		else {
			x = x + 1;
			y = y + 1;
			p = p + (2 * dx) - (2 * dy);
			
		}
		
		
	}
}

void Game::DrawlineBressenham(float XA, float YA, float XB, float YB) 
{
	float dx;
	float dy;
	float p;
	float p2;
	float x;
	float y;
	float i = 0;
	dx = XB - XA;
	dy = YB - YA;

	x = XA;
	y = YA;
	p = (2 * dx) - dy;
	p2 = (2 * dy) - dx;
	for (i; i < dx; i++) {
		m_image->PutPixel(x, y, 255, 0, 0, 255);
		if (p2 < 0) {
			x = x + 1;
			y = y;
			p2 = p2 + (2 * dy);

		}
		else {
			x = x + 1;
			y = y + 1;
			p2 = p2 + (2 * dy) - (2 * dx);
		}
		
	}
	for (i; i < dy; i++) {
		m_image->PutPixel(x, y, 255, 0, 0, 255);
		if (p < 0) {
			x = x;
			y = y + 1;
			p = p + (2 * dx);

		}
		else {
			x = x + 1;
			y = y + 1;
			p = p + (2 * dx) - (2 * dy);

		}


	}
}


void Game::DrawCircunferencia(float XC,float YC, float r) {
	float x;
	float y;
	float p;
	x = 0;
	y = r;
	p = 1 - r;
	
	while (x <= y)
	{
		m_image->PutPixel(x+100, y+100, 255, 0, 0, 255);//mi +100 va a ser mi offset
		m_image->PutPixel(x+100, -y+100, 255, 0, 0, 255);//
		m_image->PutPixel(-x+100, y+100, 255, 0, 0, 255);
		m_image->PutPixel(-x+100,-y+100 , 255, 0, 0, 255);
		m_image->PutPixel(y + 100, x + 100, 255, 0, 0, 255);
		m_image->PutPixel(-y + 100, x + 100, 255, 0, 0, 255);
		m_image->PutPixel(y + 100, -x + 100, 255, 0, 0, 255);
		m_image->PutPixel(-y + 100, -x + 100, 255, 0, 0, 255);
		if (p<0) {
			x = x + 1;
			y = y;
			p = p + (2 * x) + 3;

		}
		else if (p>0) {
			x = x + 1;
			y = y - 1;
			p = p + ((2 * x) - (2 * y)) + 5;
		}
	}
}

void Game::CurvasdeBesier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 ) {
	float u = 0;
	float inc = 0.001f;
	float rotacX = 0;
	float rotacY = 0;

	while (u<=1)
	{
		rotacX = x4 * u * u * u + 3 * x3 * u * u * (1 - u) + 3 * x2 * u * (1 - u) * (1 - u) + x1 * (1 - u) * (1 - u) * (1 - u);
		rotacY = y4 * u * u * u + 3 * y3 * u * u * (1 - u) + 3 * y2 * u * (1 - u) * (1 - u) + y1 * (1 - u) * (1 - u) * (1 - u);
		u += inc;
		m_image->PutPixel(rotacX, rotacY, 255, 0, 0, 255);
	}
	
	//200,200/200,300/300,300/300,200

}