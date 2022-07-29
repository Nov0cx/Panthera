#include "Layer.hpp"

namespace Panthera
{

    LayerStack::~LayerStack()
    {
        for (auto& layer : m_Layers)
        {
            layer->OnEnd();
        }
    }

    void LayerStack::OnUpdate(/*Timestep ts*/) const
    {
        for (auto& layer : m_Layers)
        {
            if (layer->IsActive())
            {
                layer->OnUpdate(/*ts*/);
            }
        }
    }

    void LayerStack::OnEvent(/*Event &event*/) const
    {
        for (auto& layer : m_Layers)
        {
            if (layer->IsActive())
            {
                //layer->OnEvent(event);
            }
        }
    }

    void LayerStack::OnImGuiUpdate() const
    {
        for (auto& layer : m_Layers)
        {
            if (layer->IsActive())
            {
                //layer->OnImGuiRender();
            }
        }
    }

    uint16_t LayerStack::PushLayer(Ref <Layer> layer)
    {
        m_Layers.insert(m_Layers.begin() + m_LayerPosition, layer);
        m_LayerPosition++;

        layer->m_ID = m_NextLayerID++;

        layer->OnStart();

        return layer->GetID();
    }

    uint16_t LayerStack::PushLayout(Ref <Layer> layout)
    {
        return NULL;
    }

    Ref <Layer> LayerStack::GetLayer(uint16_t id)
    {
        return NULL;
    }

}