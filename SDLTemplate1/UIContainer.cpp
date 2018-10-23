#include "UIContainer.h"

UIContainer::UIContainer() {}

void UIContainer::OnCreate() {
	m_elements = std::unordered_map<std::string, UIElement*>();
}

void UIContainer::OnDestroy() {
	for (auto it : m_elements) {
		it.second->OnDestroy();
	}
}

void UIContainer::Render(MATH::Matrix4 projectionMatrix) {
	for (auto it : m_elements) {
		it.second->Render(projectionMatrix);
	}
}

void UIContainer::Update(float delta) {
}

bool UIContainer::AddElement(UIElement * newEll) {
	//check if it already exists
	if (m_elements.find(newEll->getId()) != m_elements.end())	return false;
	newEll->OnCreate();
	m_elements.insert({newEll->getId(), newEll});
	return true;
}

UIElement * UIContainer::getElement(const char * id) {
	auto temp = m_elements.find(id);
	if (temp == m_elements.end())	return nullptr;//if not found
	return temp->second;
}

void UIContainer::HandleEvents(SDL_Event event) {
	//register an event to the ui
	//then register a function for that event
}


UIContainer * UIContainer::Dota2UIFactory(SDL_Renderer* renderer) {
	auto a = new UIContainer();
	a->AddElement(
		new ImageUIElement("minimap", "images/dota2/minimap.png", renderer, MATH::Vec3(-4.1f,-3.3f,1.0f))
	);
	a->AddElement(
		new ImageUIElement("character_attr", "images/dota2/character_attr.png", renderer, MATH::Vec3(0,-4.5f,1.0f) )
	);
	a->AddElement(
		new ImageUIElement("shop_button", "images/dota2/shop_button.png", renderer, MATH::Vec3(4.5f,-4.6f,1.0f))
	);
	auto t = new ImageUIElement("shop", "images/dota2/shop.png", renderer, MATH::Vec3(3.15f, 0.6f, 1.0f));
	t->setEnable(false);
	a->AddElement(
		t
	);

	auto p = new TextUIElement("instructions", "Press 's' to open/close the shop", renderer, MATH::Vec3(-1.5, 4.0f, 1.0f));
	p->setFontSize(12);
	p->setColor({ 255,100,100 });//TODO: color not working
	a->AddElement(
		p
	);

	return a;
}

UIContainer * UIContainer::OverwatchUIFactory(SDL_Renderer * renderer) {
	auto a = new UIContainer();
	
	a->AddElement(
		new ImageUIElement("crosshair", "images/overwatch/crosshair.png", renderer, MATH::Vec3())
	);
	auto b = new ImageUIElement("character_portrait", "images/overwatch/character_portrait.png", renderer, MATH::Vec3(-3.3f, -3.8f, 1.0f));
	a->AddElement(
		b
	);

	a->AddElement(
		new TextUIElement("ult_counter", "0%", renderer, MATH::Vec3(0.0f,-2.0f,1.0f))
	);
	auto c = new ImageUIElement("ult_full", "images/overwatch/full_ult.png", renderer, MATH::Vec3(0.0f, -2.0f, 1.0f));
	c->setEnable(false);//disabled by default
	a->AddElement(c);

	auto d = new TextUIElement("instructions", "Press 'space' to charge ULT, Then press 'E' to use it", renderer, MATH::Vec3(-1.5, 4.0f, 1.0f));
	d->setFontSize(16);
	a->AddElement(
		d
	);

	return a;
}
