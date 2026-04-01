#include "Scene.h"
#include <memory>
#include <iostream>
#define PLAY_SOUND(e,scales,oct) \
    keys[e.key.code].setBuffer(buffers[currentOctave][scales]);\
    keys[e.key.code].play();

//std::vector<sf::Int16> generateSineWave(float frequency, float duration, unsigned sampleRate, float amplitude) {
//	const float twoPi = 6.28318530718f;
//	std::vector<sf::Int16> samples(static_cast<std::size_t>(duration * sampleRate));
//
//	for (std::size_t i = 0; i < samples.size(); ++i) {
//		float t = static_cast<float>(i) / sampleRate;
//		samples[i] = static_cast<sf::Int16>(amplitude * 32767 * std::sin(twoPi * frequency * t));
//	}
//
//	return samples;
//}


Scene::Scene(sf::RenderWindow& windowRef)
	:Entity(),
	_keyContext(
		windowRef,
		currentOctave,
		buffers,
		keys
	),
	usedKeys()
{
	PianoSoundGenerator::generatePianoBuffers(
		        buffers,
		        baseFrequency,
		        minOctave,
		        maxOctave,
		        sampleRate,
		        duration
		    );
	//float maxWidth = 600;

	//for (int i = 0; i < 7; i++)
	//{
	//	int a = i;
	//	std::unique_ptr<MusicKey> key = std::make_unique<MusicKey>(MusicKey::KeyType::Major, sf::Vector2f(xOffset+(i*100), 300), sf::Vector2f(maxWidth/7, 300), windowRef, [=]() {std::cout << "Worked" <<a<< std::endl; });
	//	entities.push_back(std::move(key));
	//}
	//xOffset = xOffset + (maxWidth / 7)/2;
	//for (int i = 0; i < 6; i++)
	//{
	//	int a = i;
	//	std::unique_ptr<MusicKey> key = std::make_unique<MusicKey>(MusicKey::KeyType::Minor, sf::Vector2f(xOffset +28 + (i * 100), 300), sf::Vector2f(maxWidth / 14, 150), windowRef, [=]() {std::cout << "Worked" << a << std::endl; });
	//	entities.push_back(std::move(key));
	//}
	float xOffset = 50;
	float maxWidth = 600;
	float currentWidth = maxWidth / 7;
	int i = 0;
	std::function<float(float)> posIncrement = [&](float a) {
		return (xOffset+(a*100));
	};



	CreateKey(MusicKey::KeyType::Major, sf::Keyboard::Key::Z, Scales::RATIO_C,"Sa", sf::Vector2f(posIncrement(i++), 300), sf::Vector2f(currentWidth, 300), _keyContext);
	CreateKey(MusicKey::KeyType::Major, sf::Keyboard::Key::X, Scales::RATIO_D,"Re", sf::Vector2f(posIncrement(i++), 300), sf::Vector2f(currentWidth, 300), _keyContext);
	CreateKey(MusicKey::KeyType::Major, sf::Keyboard::Key::C, Scales::RATIO_E,"Ga", sf::Vector2f(posIncrement(i++), 300), sf::Vector2f(currentWidth, 300), _keyContext);
	CreateKey(MusicKey::KeyType::Major, sf::Keyboard::Key::V, Scales::RATIO_F,"ma", sf::Vector2f(posIncrement(i++), 300), sf::Vector2f(currentWidth, 300), _keyContext);
	CreateKey(MusicKey::KeyType::Major, sf::Keyboard::Key::B, Scales::RATIO_G,"Pa", sf::Vector2f(posIncrement(i++), 300), sf::Vector2f(currentWidth, 300), _keyContext);
	CreateKey(MusicKey::KeyType::Major, sf::Keyboard::Key::N, Scales::RATIO_A,"Dha", sf::Vector2f(posIncrement(i++), 300), sf::Vector2f(currentWidth, 300), _keyContext);
	CreateKey(MusicKey::KeyType::Major, sf::Keyboard::Key::M, Scales::RATIO_B,"Ni", sf::Vector2f(posIncrement(i++), 300), sf::Vector2f(currentWidth, 300), _keyContext);


	currentWidth = maxWidth / 14;
	CreateKey(MusicKey::KeyType::Minor, sf::Keyboard::Key::S, Scales::RATIO_C_SHARP,"re", sf::Vector2f(125, 300), sf::Vector2f(currentWidth, 150), _keyContext);
	CreateKey(MusicKey::KeyType::Minor, sf::Keyboard::Key::D, Scales::RATIO_D_SHARP,"ga", sf::Vector2f(225, 300), sf::Vector2f(currentWidth, 150), _keyContext);
	CreateKey(MusicKey::KeyType::Minor, sf::Keyboard::Key::G, Scales::RATIO_F_SHARP,"Ma", sf::Vector2f(425, 300), sf::Vector2f(currentWidth, 150), _keyContext);
	CreateKey(MusicKey::KeyType::Minor, sf::Keyboard::Key::H, Scales::RATIO_G_SHARP,"dha", sf::Vector2f(525, 300), sf::Vector2f(currentWidth, 150), _keyContext);
	CreateKey(MusicKey::KeyType::Minor, sf::Keyboard::Key::J, Scales::RATIO_A_SHARP,"ni", sf::Vector2f(625, 300), sf::Vector2f(currentWidth, 150), _keyContext);



	//std::unique_ptr<MusicKey> key = std::make_unique<MusicKey>(sf::Vector2f(100, 300), sf::Vector2f(600, 300), windowRef, []() {std::cout << "Worked" << std::endl; });
	//musicKeys.insert(std::make_pair<sf::Keyboard::Key, std::unique_ptr<MusicKey>>(sf::Keyboard::Key::Z, std::move(key)));
	//entities.push_back(std::move(key));
}

void Scene::PollEvents(const sf::Event& e)
{
    Entity::PollEvents(e);

    if (e.type == sf::Event::KeyPressed)
    {
        // 1. Handle system keys first
        switch (e.key.code)
        {
        case sf::Keyboard::Up:
            if (currentOctave < maxOctave) ++currentOctave;
            std::cout << "CurrentOctave: " << currentOctave << std::endl;
            break;
        case sf::Keyboard::Down:
            if (currentOctave > minOctave) --currentOctave;
            std::cout << "CurrentOctave: " << currentOctave << std::endl;
            break;
        case sf::Keyboard::LShift:
            // Only increment if it's a fresh press to avoid auto-repeat bugs
            if (usedKeys.find(sf::Keyboard::LShift) == usedKeys.end()) {
                if (currentOctave < maxOctave) ++currentOctave;
                std::cout << "CurrentOctave: " << currentOctave << std::endl;
            }
            break;
        default:
            break;
        }

        // 2. Handle piano keys (ignore OS auto-repeats)
    	if (usedKeys.find(e.key.code) == usedKeys.end())
    	{
    		usedKeys.emplace(e.key.code);

    		// 1. Check if the key code is wild
    		std::cout << "Pressed Key Code: " << e.key.code << std::endl;

    		if (musicKeys.find(e.key.code) != musicKeys.end())
    		{
    			std::cout << "SUCCESS: Key found in musicKeys map!" << std::endl;
    			musicKeys[e.key.code]->PlaySound(MusicKey::Keyboard);
    		}
    		else
    		{
    			std::cout << "ERROR: Key was NOT found in musicKeys map (Registration Failed)!" << std::endl;
    		}
    	}
    }
    else if (e.type == sf::Event::KeyReleased)
    {
        // 1. Safely remove the key from tracking
        usedKeys.erase(e.key.code);

        // 2. Stop the sound
        if (musicKeys.find(e.key.code) != musicKeys.end())
        {
            musicKeys[e.key.code]->StopSound();
        }

        // 3. Handle LShift release
        if (e.key.code == sf::Keyboard::LShift)
        {
            if (currentOctave > minOctave) --currentOctave;
            std::cout << "CurrentOctave: " << currentOctave << std::endl;
        }
    }

    // Propagate events to children (no need to loop twice for major/minor, just pass it down)
    for (auto& keyPair : musicKeys)
    {
        keyPair.second->PollEvents(e);
    }
}

void Scene::Update()
{
	Entity::Update();
	//for (auto& key : musicKeys)
	//{
	//	key.second->Update();
	//}
	for (auto& key : musicKeys)
	{
		if (key.second->GetKeyType() == MusicKey::KeyType::Major)
		{
			key.second->Update();
		}
	}

	// Then, handle minor keys
	for (auto& key : musicKeys)
	{
		if (key.second->GetKeyType() == MusicKey::KeyType::Minor)
		{
			key.second->Update();
		}
	}

}

void Scene::Render(sf::RenderTarget& target) const
{
	Entity::Render(target);
	for (auto& key : musicKeys)
	{
		if (key.second->GetKeyType() == MusicKey::KeyType::Major)
		{
			key.second->Render(target);
		}
	}

	// Then, handle minor keys
	for (auto& key : musicKeys)
	{
		if (key.second->GetKeyType() == MusicKey::KeyType::Minor)
		{
			key.second->Render(target);
		}
	}
}

void Scene::CreateKey(MusicKey::KeyType keyType, sf::Keyboard::Key sfKey, Scales scale ,std::string keyName, sf::Vector2f pos, sf::Vector2f size, const KeyContext& context)
{
		auto key = std::make_unique<MusicKey>(keyType,sfKey,scale,keyName,pos, size, context);
		musicKeys.emplace(sfKey, std::move(key));
	
}

