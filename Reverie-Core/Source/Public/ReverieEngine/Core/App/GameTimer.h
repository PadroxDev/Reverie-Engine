#pragma once

#include "ReverieEngine/Core/stdafx.h"

namespace ReverieEngine::Core::App
{
    class GameTimer
    {
    public:
        GameTimer();

        void Initialize();
        void Tick();
        void Reset();

        template<typename T = float>
        T GetDeltaTime() const { return static_cast<T>(m_deltaTime); }
        
        template<typename T = float>
        T GetTotalTime() const { return static_cast<T>(m_totalTime);}

        float GetFPS() const { return m_fps; }
        
    private:
        
        LARGE_INTEGER m_previousTime;
        LARGE_INTEGER m_currentTime;
        LARGE_INTEGER m_frequency;
        double m_deltaTime;
        double m_totalTime;
        float m_fps;
    };
}