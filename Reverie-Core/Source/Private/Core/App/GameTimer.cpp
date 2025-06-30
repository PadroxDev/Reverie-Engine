#include "pch.h"
#include "Core/App/GameTimer.h"

using namespace ReverieEngine::Core;

GameTimer::GameTimer() :
    m_previousTime({ }),
    m_currentTime({ }),
    m_frequency { },
    m_deltaTime(0),
    m_totalTime(0),
    m_fps(0.f)
{ }

void GameTimer::Initialize()
{
    QueryPerformanceFrequency(&m_frequency);
    QueryPerformanceCounter(&m_previousTime);
}

void GameTimer::Tick()
{
    QueryPerformanceCounter(&m_currentTime);
    
    m_deltaTime = static_cast<double>(m_currentTime.QuadPart - m_previousTime.QuadPart) /
                  static_cast<double>(m_frequency.QuadPart);
    
    m_totalTime += m_deltaTime;
    m_fps = 1.0f / static_cast<float>(m_deltaTime);

    m_previousTime = m_currentTime;
}

void GameTimer::Reset()
{
    m_previousTime = { };
    m_currentTime = { };
    m_frequency = { };
    m_deltaTime = 0;
    m_totalTime = 0;

    Initialize();
}
