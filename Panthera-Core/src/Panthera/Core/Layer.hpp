#ifndef PANTHERA_LAYER_HPP
#define PANTHERA_LAYER_HPP

#include <cinttypes>
#include "Pointer.hpp"
#include <vector>
#include "Event.hpp"
#include "Timestep.hpp"

namespace Panthera
{
    class LayerStack;

    // from my old engine
    class Layer
    {
    public:
        virtual void OnStart() = 0;

        virtual void OnUpdate(Timestep ts) = 0;

        virtual void OnEvent(Event& event) = 0;
        //virtual void OnImGuiRender() = 0;
        virtual void OnEnd() = 0;

        inline virtual void SetActive(bool active)
        {
            if (m_IsActive == active) return;

            if (active) OnStart();
            else OnEnd();

            m_IsActive = active;
        }

        [[nodiscard]] inline virtual bool IsActive() const
        {
            return m_IsActive;
        }

        [[nodiscard]] inline virtual uint16_t GetID() const
        {
            return m_ID;
        }
    private:
        friend class LayerStack;
        uint16_t m_ID = 0;
        bool m_IsActive = false;
    };

    class LayerStack
    {
    public:
        LayerStack() = default;

        ~LayerStack();

        void OnUpdate(Timestep ts);

        void OnEvent(Event &event);

        void OnImGuiUpdate();

        uint16_t PushLayer(Ref <Layer> layer);

        uint16_t PushLayout(Ref <Layer> layout);

        Ref <Layer> GetLayer(uint16_t id);

        inline std::vector <Ref<Layer>> &GetStack()
        {
            return m_Layers;
        }

    private:
        std::vector <Ref<Layer>> m_Layers;
        int m_LayerPosition = 0;
        uint16_t m_NextLayerID = 0;
    };
}

#endif //PANTHERA_LAYER_HPP
