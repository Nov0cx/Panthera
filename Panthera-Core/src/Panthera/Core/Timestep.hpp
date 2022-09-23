#ifndef PANTHERA_TIMESTEP_HPP
#define PANTHERA_TIMESTEP_HPP

namespace Panthera
{
    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
            : m_Seconds(time)
        {
        }

        operator float() const { return m_Seconds; }

        float GetSeconds() const { return m_Seconds; }
        float GetMilliseconds() const { return m_Seconds * 1000.0f; }
    private:
        float m_Seconds;
    };
}

#endif //PANTHERA_TIMESTEP_HPP
