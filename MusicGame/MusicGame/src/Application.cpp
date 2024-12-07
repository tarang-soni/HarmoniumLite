//#include <iostream>
//#include<SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <vector>
//#include <cmath>
//#include <unordered_map>
//#include "Core.h"
//
//
//
//
//float baseFrequency = 240;
//int minOctave = 1;
//int maxOctave = 3;
//int currentOctave = 1;
//enum class Scales {
//    RATIO_C=0,        // C
//    RATIO_C_SHARP,  // C# (Db)
//    RATIO_D,        // D
//    RATIO_D_SHARP,  // D# (Eb)
//    RATIO_E,        // E
//    RATIO_F,        // F
//    RATIO_F_SHARP,  // F# (Gb)
//    RATIO_G,        // G
//    RATIO_G_SHARP,  // G# (Ab)
//    RATIO_A,        // A
//    RATIO_A_SHARP,  // A# (Bb)
//    RATIO_B,        // B
//};
//const float FREQUENCY_RATIOS[] = {
//    1.0f,            // RATIO_C
//    16.0f / 15.0f,   // RATIO_C_SHARP
//    9.0f / 8.0f,     // RATIO_D
//    6.0f / 5.0f,     // RATIO_D_SHARP
//    5.0f / 4.0f,     // RATIO_E
//    4.0f / 3.0f,     // RATIO_F
//    45.0f / 32.0f,   // RATIO_F_SHARP
//    3.0f / 2.0f,     // RATIO_G
//    8.0f / 5.0f,     // RATIO_G_SHARP
//    5.0f / 3.0f,     // RATIO_A
//    9.0f / 5.0f,     // RATIO_A_SHARP
//    15.0f / 8.0f,    // RATIO_B
//};
//std::vector<std::vector<sf::Int16>> sineWaves;
//std::unordered_map<int,std::unordered_map <Scales, sf::SoundBuffer>> buffers;
//std::unordered_map<sf::Keyboard::Key,sf::Sound> keys;
//
//std::vector<sf::Int16> generateSineWave(float frequency, float duration, unsigned sampleRate, float amplitude) {
//    const float twoPi = 6.28318530718f;
//    std::vector<sf::Int16> samples(static_cast<std::size_t>(duration * sampleRate));
//
//    for (std::size_t i = 0; i < samples.size(); ++i) {
//        float t = static_cast<float>(i) / sampleRate;
//        samples[i] = static_cast<sf::Int16>(amplitude * 32767 * std::sin(twoPi * frequency * t));
//    }
//
//    return samples;
//}
//
//#define PLAY_SOUND(e,scales,oct) \
//    keys[e.key.code].setBuffer(buffers[currentOctave][scales]);\
//    keys[e.key.code].play();
//class PianoSoundGenerator {
//public:
//    static std::vector<sf::Int16> generatePianoSound(float frequency, float duration, unsigned sampleRate) {
//        std::vector<sf::Int16> samples(static_cast<size_t>(duration * sampleRate));
//
//        // More complex harmonic structure mimicking a real piano
//        struct Harmonic {
//            float multiplier;  // Frequency multiplier
//            float amplitude;   // Amplitude of the harmonic
//            float phase;       // Phase offset
//        };
//
//        // Expanded and more nuanced harmonic series
//        const std::vector<Harmonic> harmonics = {
//            {1.0f, 1.0f, 0.0f},       // Fundamental frequency
//            {2.0f, 0.5f, 0.1f},        // Second harmonic (stronger)
//            {3.0f, 0.3f, 0.2f},        // Third harmonic
//            {4.0f, 0.2f, 0.3f},        // Fourth harmonic
//            {5.0f, 0.15f, 0.4f},       // Fifth harmonic
//            {6.0f, 0.1f, 0.5f},        // Sixth harmonic
//            {7.0f, 0.08f, 0.6f},       // Seventh harmonic
//            {8.0f, 0.06f, 0.7f}        // Eighth harmonic
//        };
//
//        // More sophisticated envelope parameters
//        const float attackTime = 0.005f;     // Very quick initial attack
//        const float decayTime = 0.1f;        // Faster decay
//        const float sustainLevel = 0.4f;     // Moderate sustain
//        const float releaseTime = 0.3f;      // Controlled release
//
//        // Noise and inharmonicity parameters
//        const float noiseLevel = 0.05f;      // Subtle mechanical noise
//        const float inharmonicityFactor = 0.001f;  // Slight frequency variation
//
//        // Maximum amplitude to prevent clipping
//        const float MAX_AMPLITUDE = 0.8f;
//
//        // Advanced windowing function with more natural curve
//        auto windowFunction = [&](float t, float duration) {
//            // Raised cosine window with smoother transition
//            return 0.5f * (1.0f - std::cos(PI * t / duration));
//            };
//
//        // Noise generator
//        auto generateNoise = []() {
//            return (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
//            };
//
//        for (size_t i = 0; i < samples.size(); ++i) {
//            float t = static_cast<float>(i) / sampleRate;
//
//            // Generate sound with rich harmonics
//            float sample = 0.0f;
//
//            for (const Harmonic& harmonic : harmonics) {
//                // Add slight inharmonicity (natural piano imperfection)
//                float instantFreq = frequency * harmonic.multiplier *
//                    (1.0f + inharmonicityFactor * harmonic.multiplier);
//
//                // Generate sine wave with phase offset
//                float harmonicSample = std::sin(2.0f * PI * instantFreq * t + harmonic.phase);
//
//                // Apply harmonic amplitude
//                sample += harmonicSample * harmonic.amplitude;
//            }
//
//            // Add subtle mechanical noise
//            sample += generateNoise() * noiseLevel;
//
//            // Envelope calculation with more nuanced shaping
//            float envelope;
//            if (t < attackTime) {
//                // Very quick, smooth attack
//                envelope = windowFunction(t, attackTime);
//            }
//            else if (t < (attackTime + decayTime)) {
//                // More exponential decay to sustain level
//                float decayProgress = (t - attackTime) / decayTime;
//                envelope = 1.0f - (1.0f - sustainLevel) * std::pow(decayProgress, 2.0f);
//            }
//            else if (t < (duration - releaseTime)) {
//                // Sustain phase
//                envelope = sustainLevel;
//            }
//            else {
//                // Smoother, more gradual release
//                float releaseProgress = (t - (duration - releaseTime)) / releaseTime;
//                envelope = sustainLevel * std::exp(-3.0f * releaseProgress);
//            }
//
//            // Apply envelope
//            sample *= envelope;
//
//            // Advanced soft clipping for warmth
//            sample = std::tanh(sample * 1.5f);
//
//            // Convert to 16-bit integer with controlled amplitude
//            samples[i] = static_cast<sf::Int16>(sample * 32767.0f * MAX_AMPLITUDE);
//        }
//
//        return samples;
//    }
//
//    // Helper function to generate buffers for different frequencies
//    static void generatePianoBuffers(
//        std::unordered_map<int, std::unordered_map<Scales, sf::SoundBuffer>>& buffers,
//        float baseFrequency,
//        int minOctave,
//        int maxOctave,
//        unsigned sampleRate = 44100,
//        float duration = 2.0f
//    ) {
//        auto freqLength = sizeof(FREQUENCY_RATIOS) / sizeof(float);
//
//        for (int j = minOctave; j <= maxOctave; ++j) {
//            for (int i = 0; i < freqLength; ++i) {
//                // Calculate frequency for each octave
//                float freq = baseFrequency * std::pow(2.0f, j - 1) * FREQUENCY_RATIOS[i];
//
//                // Generate piano-like sound
//                auto samples = generatePianoSound(freq, duration, sampleRate);
//
//                // Load into sound buffer
//                buffers[j][(Scales)i] = sf::SoundBuffer();
//                if (!buffers[j][(Scales)i].loadFromSamples(samples.data(), samples.size(), 1, sampleRate)) {
//                    std::cerr << "Failed to load sound buffer for octave " << j
//                        << ", scale " << i << std::endl;
//                }
//            }
//        }
//    }
//};
//int main()
//{
//    float duration = 2.0f;          // Duration in seconds
//    unsigned sampleRate = 44100;    // Standard audio sample rate
//    float amplitude = 0.5f;         // Amplitude (0.0 to 1.0)
//
//    auto freqLength = sizeof(FREQUENCY_RATIOS) / sizeof(float);
//    sineWaves.clear(); // Clear any existing waves
//    PianoSoundGenerator::generatePianoBuffers(
//        buffers,
//        baseFrequency,
//        minOctave,
//        maxOctave,
//        sampleRate,
//        duration
//    );
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//
//    // Keep the program running until the sound is done
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            switch (event.type)
//            {
//            case sf::Event::Closed:
//                window.close();
//                break;
//            case sf::Event::KeyPressed:
//                if ((event.key.code != sf::Keyboard::Up )&&(event.key.code != sf::Keyboard::Down)) {
//
//                    if (keys.find(event.key.code) == keys.end()) 
//                    {
//                        keys[event.key.code] = sf::Sound();
//                    
//                    }
//                    else 
//                    {
//                        continue;
//                    }
//                }
//                switch (event.key.code)
//                {
//                case sf::Keyboard::Up:
//                    if (currentOctave < maxOctave) {
//                        ++currentOctave;
//                    }
//                    std::cout << "CurrentOctave: " << currentOctave << std::endl;
//                    break;
//                case sf::Keyboard::Down:
//                    if (currentOctave > minOctave) {
//                        --currentOctave;
//                    }
//                    std::cout << "CurrentOctave: " << currentOctave << std::endl;
//                    break;
//                case sf::Keyboard::LShift:
//                    //PLAY_SOUND(event Scales::RATIO_C_SHARP);
//                    if (currentOctave < maxOctave) {
//                        ++currentOctave;
//                    }
//                    std::cout << "CurrentOctave: " << currentOctave << std::endl;
//                    break;
//
//                case sf::Keyboard::Z:
//                    //PLAY_SOUND(event,Scales::RATIO_C);//sa
//                    keys[event.key.code].setBuffer(buffers[currentOctave][Scales::RATIO_C]); \
//                        keys[event.key.code].play();
//
//                    break;
//                case sf::Keyboard::S:
//                    PLAY_SOUND(event, Scales::RATIO_C_SHARP); //re komal
//
//                    break;
//                case sf::Keyboard::X:
//                    PLAY_SOUND(event, Scales::RATIO_D); //re
//                    break;
//                case sf::Keyboard::D :
//                    PLAY_SOUND(event, Scales::RATIO_D_SHARP);   //ga komal
//
//                    break;
//                case sf::Keyboard::C:
//                    PLAY_SOUND(event, Scales::RATIO_E);//ga
//                    break;
//                case sf::Keyboard::V:
//                    PLAY_SOUND(event, Scales::RATIO_F); //ma
//                    break;
//                case sf::Keyboard::G:
//                    PLAY_SOUND(event, Scales::RATIO_F_SHARP);   //ma tivra
//                    break;
//                case sf::Keyboard::B:
//                    PLAY_SOUND(event, Scales::RATIO_G); //pa
//                    break;
//                case sf::Keyboard::H:
//                    PLAY_SOUND(event, Scales::RATIO_G_SHARP);   //dha komal
//                    break;
//                case sf::Keyboard::N:
//                    PLAY_SOUND(event, Scales::RATIO_A); //dha
//                    break;
//                case sf::Keyboard::J:
//                    PLAY_SOUND(event, Scales::RATIO_A_SHARP);
//                    break;
//                case sf::Keyboard::M:
//                    PLAY_SOUND(event, Scales::RATIO_B);
//                    break;
//
//                default:
//                    break;
//                }
//                break;
//            case sf::Event::KeyReleased:
//                if (keys.find(event.key.code) != keys.end())
//                {
//                    keys[event.key.code].stop();
//                    keys.erase(event.key.code);
//                }
//                
//                else
//                {
//                    continue;
//                }
//                switch (event.key.code)
//                {
//                case sf::Keyboard::LShift:
//                    if (currentOctave > minOctave) {
//                        --currentOctave;
//                    }
//                    std::cout << "CurrentOctave: " << currentOctave << std::endl;
//                    break;
//                default:
//                    break;
//                }
//            }
//        }
//
//
//
//            window.clear();
//            window.draw(shape);
//            window.display();
//        }
//        return 0;
//    }