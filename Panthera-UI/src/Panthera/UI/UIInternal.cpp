#include "UIInternal.hpp"

namespace Panthera::UI::Internal
{
    Data *Data::Instance;

    void Data::Init()
    {
        Instance = new Data();
        Instance->Windows = tsl::sparse_map<const char*, Ref<Window>>();
    }
}