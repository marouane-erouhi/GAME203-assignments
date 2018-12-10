//#include "TextUIElement.h"
//#include <iostream>
//TextUIElement::TextUIElement(const char* id,const char * text, SDL_Renderer* renderer, MATH::Vec3 pos)
//	: text(text), renderer(renderer){
//	this->id = id;
//	this->pos = pos;
//}
//
//void TextUIElement::OnCreate() {
//	font = TTF_OpenFont(fontName, pointSize);
//	color = { 255,255,0 };//yellow
//}
//
//void TextUIElement::OnDestroy() {
//	SDL_FreeSurface(textSurface);
//	SDL_DestroyTexture(textTexture);
//	TTF_CloseFont(font);
//}
//
//void TextUIElement::Render(MATH::Matrix4 projectionMatrix) {
//	if (!enabled)	return;
//	screenCoords = projectionMatrix * pos;
//	
//	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
//	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//
//	SDL_Rect Message_rect; //create a rect
//	Message_rect.w = pointSize * text.size(); // controls the width of the rect
//	Message_rect.h = pointSize*2; // controls the height of the rect
//
//	Message_rect.x = screenCoords.x - (Message_rect.w / 2);
//	Message_rect.y = screenCoords.y - (Message_rect.h / 2);
//	
//	SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);
//}
//
//void TextUIElement::Update(float delta) {
//}
//
//void TextUIElement::setText(std::string newText) {
//	text = newText;
//}
//
//void TextUIElement::setFontSize(int x) {
//	delete font;
//	pointSize = x;
//	font = TTF_OpenFont(fontName, pointSize);
//}
//
//void TextUIElement::setColor(SDL_Color newColor) {
//	color = newColor;
//}
//
//void TextUIElement::setSize(int newSize) {
//	pointSize = newSize;
//}
