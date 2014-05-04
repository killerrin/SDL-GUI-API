#include "GridLayer.h"
using namespace GuiAPI;


//SDL_Texture *tiletexture = GUIHelper::LoadPNGTexture("Resources/Tiles/grassAndRock.png");
//GUI::AddTexture("TileTexture", tiletexture);


//GUI::GetGuiContainer("MainMenu")->AddGuiElement("TileTest", new GridSquare(GUI::GetTexture("TileTexture"), GUIHelper::RectHelper(64, 0, 32, 32), GUIHelper::RectHelper(10, 10, 32, 32)));


GridLayer::GridLayer() {}

//Art layers
//GridLayer::GridLayer(SDL_Texture* _tileTexture, GridLayer _gridLayer, GridSquare _gridSquares[]){
//	Active = true;
//	Enabled = true;
//	rows = _gridLayer.rows;
//	columns = _gridLayer.columns;
//
//	layer = std::vector<GridSquare*>();
//
//	unsigned int counter = 0;
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < columns; j++) {
//			_gridSquares[counter].xPos = i;
//			_gridSquares[counter].yPos = j;
//			layer.push_back(new GridSquare(_tileTexture, _gridSquares[counter], _gridLayer.tileSize, _gridLayer.tileSize));
//			counter++;
//		}
//	}
//}
//
////GridLayers that require no art
//GridLayer::GridLayer(GridLayer _gridLayer, GridSquare _gridSquares[]){
//	Active = true;
//	Enabled = true;
//	rows = _gridLayer.rows;
//	columns = _gridLayer.columns;
//
//	layer = std::vector<GridSquare*>();
//
//	unsigned int counter;
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < columns; j++) {
//			layer.push_back(new GridSquare(_gridSquares[counter], 32, 32));
//			counter++;
//		}
//	}
//}

GridLayer::~GridLayer(void) { }

void GridLayer::Update(double time){
	for (size_t i = 0; i < layer.size(); i++){
		layer.at(i)->Update(time);
	}
}
void GridLayer::Draw(){
	for (size_t i = 0; i < layer.size(); i++){
		layer.at(i)->Draw();
	}
}

//void GridLayer::HandleMouseMotionEvent(SDL_MouseMotionEvent e)
//{
//	if (!Active) return;
//	if (!Enabled) return;
//
//	for (size_t i = 0; i < layer.size(); i++){
//		layer.at(i)->HandleMouseMotionEvent(e);
//	}
//}
//void GridLayer::HandleMouseDownEvent(SDL_MouseButtonEvent e)
//{
//	if (!Active) return;
//	if (!Enabled) return;
//
//	for (size_t i = 0; i < layer.size(); i++){
//		layer.at(i)->HandleMouseDownEvent(e);
//	}
//}
//void GridLayer::HandleMouseUpEvent(SDL_MouseButtonEvent e)
//{
//	if (!Active) return;
//	if (!Enabled) return;
//
//	for (size_t i = 0; i < layer.size(); i++){
//		layer.at(i)->HandleMouseUpEvent(e);
//	}
//}
//void GridLayer::HandleMouseClickEvent()
//{
//	if (!Active) return;
//	if (!Enabled) return;
//
//	for (size_t i = 0; i < layer.size(); i++){
//		layer.at(i)->HandleMouseClickEvent();
//	}
//}
