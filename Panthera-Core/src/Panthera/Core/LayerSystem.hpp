#ifndef PANTHERA_LAYERSYSTEM_HPP
#define PANTHERA_LAYERSYSTEM_HPP

#include "ppch.hpp"
#include "Timestep.hpp"

namespace Panthera
{
    class Layer
    {
    public:
        virtual void OnEnable() {}
        virtual void OnDisable() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnGui() {}
    };

    class LayerStack
    {
    public:
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopOverlay(Layer* overlay);

        void OnUpdate(Timestep ts);
        void OnGui();

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        uint32_t m_LayerInsertIndex = 0;
    };
}

#endif //PANTHERA_LAYERSYSTEM_HPP
