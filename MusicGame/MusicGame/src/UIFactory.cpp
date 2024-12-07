#include "UIFactory.h"
#include <fstream>
#include "Text.h"
#include "Button.h"
#include <iostream>
std::map<UIType, std::function<std::unique_ptr<UIElement>(const nlohmann::json&)>> UIFactory::mFactories;
UIFactory::UIFactory()
{
    RegisterElementTypes<Text>(UIType::Text);
    RegisterElementTypes<Button>(UIType::Button);
}

std::unique_ptr<UIElement> UIFactory::CreateElement(UIType uiType, const nlohmann::json& item)
{

		auto it = mFactories.find(uiType);
		if (it != mFactories.end()) {
			return it->second(item);
		}
		throw std::runtime_error("Unknown UI element type");
}

