#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_map>
#include "PianoSoundGenerator.h"
#include<memory>
#include <functional>
#include "KeyContext.h"
#include "MusicKey.h"
#include <unordered_set>

class Scene :
    public Entity
{
public:
	Scene(sf::RenderWindow& windowRef);
	void PollEvents(const sf::Event& e) override;
	void Update() override;
	void Render(sf::RenderTarget& target)const override;

private:
    void CreateKey(MusicKey::KeyType keyType, sf::Keyboard::Key key, Scales scale, std::string keyName, sf::Vector2f pos,sf::Vector2f size,const KeyContext& context);

    KeyContext _keyContext;

	float baseFrequency = 60;
    const int minOctave = 1;
    const int maxOctave = 6;
    int currentOctave = 1;

    std::vector<std::vector<sf::Int16>> sineWaves;
    std::unordered_map<int,std::unordered_map <Scales, sf::SoundBuffer>> buffers;
    std::unordered_map<sf::Keyboard::Key,sf::Sound> keys;

    float duration = 2.0f;          // Duration in seconds
    unsigned sampleRate = 44100;    // Standard audio sample rate
    float amplitude = 0.5f;         // Amplitude (0.0 to 1.0)
    std::unordered_map<sf::Keyboard::Key, std::unique_ptr<MusicKey>> musicKeys;
    std::unordered_set<sf::Keyboard::Key> usedKeys;


};

