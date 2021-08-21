#pragma once
namespace minigin
{
    template <typename T>
    class ServiceLocator
    {
    public:
        static T* getService() { return m_Service; }

        static void provide(T* service)
        {
            m_Service = service;
        }

    private:
        static T* m_Service;
    };
}