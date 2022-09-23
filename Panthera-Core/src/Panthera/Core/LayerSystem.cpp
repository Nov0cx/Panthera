#include "LayerSystem.hpp"

namespace Panthera
{

    void LayerStack::PushLayer(Layer *layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
        layer->OnEnable();
    }

    void LayerStack::PopLayer(Layer *layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
        if (it != m_Layers.begin() + m_LayerInsertIndex)
        {
            layer->OnDisable();
            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PushOverlay(Layer *overlay)
    {
        m_Layers.emplace_back(overlay);
        overlay->OnEnable();
    }

    void LayerStack::PopOverlay(Layer *overlay)
    {
        auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
        if (it != m_Layers.end())
        {
            overlay->OnDisable();
            m_Layers.erase(it);
        }
    }

    void LayerStack::OnUpdate(Timestep ts)
    {
        for (Layer *layer : m_Layers)
        {
            layer->OnUpdate(ts);
        }
    }

    void LayerStack::OnGui()
    {
        for (Layer *layer : m_Layers)
        {
            layer->OnGui();
        }
    }

    LayerStack::~LayerStack()
    {
        auto copy = m_Layers;
        for (Layer *layer : copy)
        {
            auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
            if (it != m_Layers.end())
            {
                layer->OnDisable();
                m_Layers.erase(it);
                m_LayerInsertIndex--;
            }
            delete layer;
        }
    }
}