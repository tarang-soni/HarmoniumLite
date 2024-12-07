#pragma once
#include "GameObject.h"
#include <functional>
#include "KeyContext.h"
#include "Text.h"

class MusicKey :
    public GameObject
{
public:
    enum KeyType {
        Major,
        Minor
    };
    enum KeyPressType {
        None,
        Keyboard,
        Mouse
    };
    MusicKey(KeyType type, sf::Keyboard::Key key, Scales scale, std::string keyName,sf::Vector2f pos,sf::Vector2f size,KeyContext context);
    void PollEvents(const sf::Event& e) override;
    void Update() override;
    void Render(sf::RenderTarget& target)const override;
    void PlaySound(KeyPressType keyPressType);
    void StopSound();
    KeyType GetKeyType()const { return _keyType; }
private:
    void CreateRect();
    bool IsHover();
public:
    bool isPlaying;
private:

    sf::Color _defaultColor;
    sf::Color _pressedColor;
    sf::RectangleShape _rect;
    sf::Vector2f _size;
    std::string _keyName;
    Text _txt;
    KeyType _keyType;
    //std::function<void()> onClickEvent;
    KeyContext _context;
    Scales _scale;
    sf::Keyboard::Key _keyboardKey;
    KeyPressType _keyPressType;
    static bool _isMousePressed;
};

