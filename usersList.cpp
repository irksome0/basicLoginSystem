#include "pch.h"
#include "usersList.h"
#if __has_include("usersList.g.cpp")
#include "usersList.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::LoginSystem::implementation
{
    int32_t usersList::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void usersList::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void usersList::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
