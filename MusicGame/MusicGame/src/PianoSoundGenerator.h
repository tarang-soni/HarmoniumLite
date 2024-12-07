#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include<unordered_map>
#include "Core.h"
#include "Scales.h"
class PianoSoundGenerator {
public:
    static std::vector<sf::Int16> generatePianoSound(float frequency, float duration, unsigned sampleRate) {
        std::vector<sf::Int16> samples(static_cast<size_t>(duration * sampleRate));

        // More complex harmonic structure mimicking a real piano
        struct Harmonic {
            float multiplier;  // Frequency multiplier
            float amplitude;   // Amplitude of the harmonic
            float phase;       // Phase offset
        };

        // Expanded and more nuanced harmonic series
        const std::vector<Harmonic> harmonics = {
            {1.0f, 1.0f, 0.0f},       // Fundamental frequency
            {2.0f, 0.5f, 0.1f},        // Second harmonic (stronger)
            {3.0f, 0.3f, 0.2f},        // Third harmonic
            {4.0f, 0.2f, 0.3f},        // Fourth harmonic
            {5.0f, 0.15f, 0.4f},       // Fifth harmonic
            {6.0f, 0.1f, 0.5f},        // Sixth harmonic
            {7.0f, 0.08f, 0.6f},       // Seventh harmonic
            {8.0f, 0.06f, 0.7f}        // Eighth harmonic
        };

        // More sophisticated envelope parameters
        const float attackTime = 0.005f;     // Very quick initial attack
        const float decayTime = 0.1f;        // Faster decay
        const float sustainLevel = 0.4f;     // Moderate sustain
        const float releaseTime = 0.3f;      // Controlled release

        // Noise and inharmonicity parameters
        const float noiseLevel = 0.05f;      // Subtle mechanical noise
        const float inharmonicityFactor = 0.001f;  // Slight frequency variation

        // Maximum amplitude to prevent clipping
        const float MAX_AMPLITUDE = 0.8f;

        // Advanced windowing function with more natural curve
        auto windowFunction = [&](float t, float duration) {
            // Raised cosine window with smoother transition
            return 0.5f * (1.0f - std::cos(PI * t / duration));
            };

        // Noise generator
        auto generateNoise = []() {
            return (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
            };

        for (size_t i = 0; i < samples.size(); ++i) {
            float t = static_cast<float>(i) / sampleRate;

            // Generate sound with rich harmonics
            float sample = 0.0f;

            for (const Harmonic& harmonic : harmonics) {
                // Add slight inharmonicity (natural piano imperfection)
                float instantFreq = frequency * harmonic.multiplier *
                    (1.0f + inharmonicityFactor * harmonic.multiplier);

                // Generate sine wave with phase offset
                float harmonicSample = std::sin(2.0f * PI * instantFreq * t + harmonic.phase);

                // Apply harmonic amplitude
                sample += harmonicSample * harmonic.amplitude;
            }

            // Add subtle mechanical noise
            sample += generateNoise() * noiseLevel;

            // Envelope calculation with more nuanced shaping
            float envelope;
            if (t < attackTime) {
                // Very quick, smooth attack
                envelope = windowFunction(t, attackTime);
            }
            else if (t < (attackTime + decayTime)) {
                // More exponential decay to sustain level
                float decayProgress = (t - attackTime) / decayTime;
                envelope = 1.0f - (1.0f - sustainLevel) * std::pow(decayProgress, 2.0f);
            }
            else if (t < (duration - releaseTime)) {
                // Sustain phase
                envelope = sustainLevel;
            }
            else {
                // Smoother, more gradual release
                float releaseProgress = (t - (duration - releaseTime)) / releaseTime;
                envelope = sustainLevel * std::exp(-3.0f * releaseProgress);
            }

            // Apply envelope
            sample *= envelope;

            // Advanced soft clipping for warmth
            sample = std::tanh(sample * 1.5f);

            // Convert to 16-bit integer with controlled amplitude
            samples[i] = static_cast<sf::Int16>(sample * 32767.0f * MAX_AMPLITUDE);
        }

        return samples;
    }

    // Helper function to generate buffers for different frequencies
    static void generatePianoBuffers(
        std::unordered_map<int, std::unordered_map<Scales, sf::SoundBuffer>>& buffers,
        float baseFrequency,
        int minOctave,
        int maxOctave,
        unsigned sampleRate = 44100,
        float duration = 1.0f
    ) {
        auto freqLength = sizeof(FREQUENCY_RATIOS) / sizeof(float);

        for (int j = minOctave; j <= maxOctave; ++j) {
            for (int i = 0; i < freqLength; ++i) {
                // Calculate frequency for each octave
                float freq = baseFrequency * std::pow(2.0f, j - 1) * FREQUENCY_RATIOS[i];

                // Generate piano-like sound
                auto samples = generatePianoSound(freq, duration, sampleRate);

                // Load into sound buffer
                buffers[j][(Scales)i] = sf::SoundBuffer();
                if (!buffers[j][(Scales)i].loadFromSamples(samples.data(), samples.size(), 1, sampleRate)) {
                    std::cerr << "Failed to load sound buffer for octave " << j
                        << ", scale " << i << std::endl;
                }
            }
        }
    }
};