#include "UIManager.h"
//#include "JSONFileLoader.h"
UIManager * UIManager::instance;
UIManager * UIManager::getInstance() {
	if (!instance)	instance = new UIManager();
	return instance;
}

UIManager::UIManager() {}

UIContainer * UIManager::getUI() {
	return this->currentUI;
}

bool UIManager::setUI(const char * uiName, SDL_Renderer* renderer_) {
	if (uiName == "blockBreakerUI") {
		currentUI = UIContainer::BlockBreakerUIFactory(renderer_);
	}
	return false;
}