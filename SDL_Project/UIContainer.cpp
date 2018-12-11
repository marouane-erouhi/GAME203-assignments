#include "UIContainer.h"

UIContainer::UIContainer() {}

void UIContainer::OnCreate() {
	m_elements = std::unordered_map<std::string, UIElement*>();
}

void UIContainer::OnDestroy() {
	for (auto it : m_elements) {
		it.second->OnDestroy();
	}
	m_elements.clear();
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
	if (m_elements.find(newEll->getId()) != m_elements.end()) {
		std::cout << "UI Element collision: " << newEll->getId() << std::endl;
		return false; 
	}
	newEll->OnCreate();
	m_elements.insert({newEll->getId(), newEll});
	return true;
}

UIElement * UIContainer::getElement(const char * id) {
	auto temp = m_elements.find(id);
	if (temp == m_elements.end()){
		std::cout << "UI Elements not found " << id << std::endl;
		return nullptr;//if not found
	}
	return temp->second;
}

UIContainer * UIContainer::BlockBreakerUIFactory(SDL_Renderer * renderer_) {
	auto a = new UIContainer();

	TextUIElement* scoreText = new TextUIElement("scoreText", "Score: 0", renderer_, MATH::Vec3(0, 380, 0));
	scoreText->setFontSize(12);
	scoreText->setColor({ 255,100,100 });//TODO: color not working

	TextUIElement* lives = new TextUIElement("livesText", "Lives: 3", renderer_, MATH::Vec3(-300, 380, 0));
	lives->setFontSize(12);
	lives->setColor({ 0,100,100 });//TODO: color not working

	a->AddElement(scoreText);
	a->AddElement(lives);

	return a;
}
