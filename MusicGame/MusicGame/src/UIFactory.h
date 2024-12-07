#pragma once
#include "UIElement.h"
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <nlohmann/json.hpp>
#include "CallbackRegistry.h"
#include "Button.h"
#include <iostream>
#include <fstream>
class UIFactory
{
public:
	typedef std::unique_ptr<UIElement> Ptr;

	static std::map<UIType, std::function<Ptr(const nlohmann::json&)>> mFactories;
public:
	UIFactory();
	template<typename T>
	void RegisterElementTypes(UIType type);
	static std::unique_ptr<UIElement> CreateElement(UIType uiType,const nlohmann::json& item);

    template<typename T>
    static std::vector<std::unique_ptr<UIElement>> CreateAllElements(
        const char* screenType,
        const char* filePath,
        T& callbackOwner)  // Add a reference to the object containing callbacks
    {
        std::vector<std::unique_ptr<UIElement>> elements;
        try {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                throw std::runtime_error("Cannot open file: " + std::string(filePath));
            }
            nlohmann::json data = nlohmann::json::parse(file);
            if (data.find(screenType) == data.end()) {
                throw std::runtime_error("Screen type not found: " + std::string(screenType));
            }
            auto& screenItems = data[screenType]["uiElements"];
            for (auto& item : screenItems)
            {
                if (item.contains("type")) {
                    std::string strType = item["type"];
                    UIType type = stringToUIType(strType);

                    // Special handling for buttons
                    if (type == UIType::Button && item.contains("callback")) {
                        std::string callbackName = item["callback"];

                        // Use reflection-like approach to get the method
                        auto element = CreateButtonWithCallback(item, callbackOwner, callbackName);
                        if (element) {
                            elements.push_back(std::move(element));
                        }
                    }
                    else {
                        // Standard element creation
                        auto element = CreateElement(type, item);
                        if (element) {
                            elements.push_back(std::move(element));
                        }
                        else {
                            std::cerr << "Unknown UIType: " << strType << std::endl;
                        }
                    }
                }
                else {
                    std::cerr << "Missing 'type' field in UI element" << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error in CreateAllElements: " << e.what() << std::endl;
        }
        return elements;
    }
    template<typename T>
    static std::unique_ptr<UIElement> CreateButtonWithCallback(
        const nlohmann::json& item,
        T& callbackOwner,
        const std::string& callbackName)
    {
        auto button = CreateElement(UIType::Button, item);

        if (button) {
            auto buttonPtr = dynamic_cast<Button*>(button.get());
            if (buttonPtr) {
                auto callback = CallbackRegistry<T>::GetCallback(callbackOwner, callbackName);
                if (callback) {
                    buttonPtr->SetOnClick(callback);
                }
            }
        }

        return button;
    }

    static UIType stringToUIType(const std::string& typeStr) {
        static const std::map<std::string, UIType> stringToEnumMap = {
            {"Button", UIType::Button},
            {"Text", UIType::Text},

        };

        auto it = stringToEnumMap.find(typeStr);
        if (it != stringToEnumMap.end()) {
            return it->second;
        }
        return UIType::Unknown; // Default value if not found
    }
};

//static std::unique_ptr<UIElement> UIFactory::CreateElement(UIType uiType,Properties props)
//{
//	static_assert(std::is_base_of<UIElement, T>::value || std::is_same<UIElement, T>::value,
//		"T must be UIElement or derive from UIElement");
//	return std::make_unique<T>(props);
//}

template<typename T>
inline void UIFactory::RegisterElementTypes(UIType type)
{
	mFactories[type] = [](const nlohmann::json& item) {
		return std::make_unique<T>(item);
		};
}
