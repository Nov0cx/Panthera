#ifndef PANTHERA_POINTER_HPP
#define PANTHERA_POINTER_HPP

#include <atomic>

namespace Panthera
{
    class RefData
    {
    public:
        void IncreaseReferenceCount() { ++m_RefCount; }
        void DecreaseReferenceCount() { --m_RefCount; }
        uint32_t GetReferenceCount() const { return m_RefCount.load(); }

    private:
        std::atomic<uint32_t> m_RefCount = 0;
    };

    template<typename T>
    class Ref
    {
    public:
        Ref()
                : m_Ptr(nullptr), m_Storage(nullptr)
        {
        }

        Ref(std::nullptr_t)
                : m_Ptr(nullptr), m_Storage(nullptr)
        {
        }

        Ref(T* ptr)
                : m_Ptr(ptr)
        {
            m_Storage = new RefData();
            m_Storage->IncreaseReferenceCount();
        }

        Ref(const Ref<T>& other)
                : m_Ptr(other.m_Ptr), m_Storage(other.m_Storage)
        {
            IncreaseReferenceCount();
        }

        Ref(Ref<T>&& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            m_Storage = other.m_Storage;
            other.m_Ptr = nullptr;
            other.m_Storage = nullptr;
        }

        template<typename Other>
        Ref(const Ref<Other>& other)
        {
            m_Ptr = static_cast<T*>(other.m_Ptr);
            m_Storage = other.m_Storage;
            IncreaseReferenceCount();
        }

        template<typename Other>
        Ref(Ref<Other>&& other) noexcept
        {
            m_Ptr = static_cast<T*>(other.m_Ptr);
            m_Storage = other.m_Storage;
            other.m_Ptr = nullptr;
            other.m_Storage = nullptr;
        }

        ~Ref()
        {
            DecreaseReferenceCount();
        }

        Ref& operator=(std::nullptr_t)
        {
            DecreaseReferenceCount();
            m_Storage = nullptr;
            m_Ptr = nullptr;
            return *this;
        }

        Ref& operator=(const Ref<T>& other)
        {
            other.IncreaseReferenceCount();
            DecreaseReferenceCount();

            m_Ptr = other.m_Ptr;
            m_Storage = other.m_Storage;
            return *this;
        }

        Ref& operator=(Ref<T>&& other) noexcept
        {
            DecreaseReferenceCount();

            m_Ptr = other.m_Ptr;
            m_Storage = other.m_Storage;
            other.m_Ptr = nullptr;
            other.m_Storage = nullptr;

            return *this;
        }

        template<typename Other>
        Ref& operator=(const Ref<Other>& other)
        {
            other.IncreaseReferenceCount();
            DecreaseReferenceCount();

            m_Ptr = static_cast<T*>(other.m_Ptr);
            m_Storage = other.m_Storage;

            return *this;
        }

        template<typename Other>
        Ref& operator=(Ref<Other>&& other) noexcept
        {
            DecreaseReferenceCount();

            m_Ptr = static_cast<T*>(other.m_Ptr);
            m_Storage = other.m_Storage;
            other.m_Ptr = nullptr;
            other.m_Storage = nullptr;

            return *this;
        }

        operator bool() { return m_Ptr != nullptr && m_Storage != nullptr; }
        operator bool() const { return m_Ptr != nullptr && m_Storage != nullptr; }

        T* operator->() { return m_Ptr; }
        const T* operator->() const { return m_Ptr; }

        T& operator*() { return *m_Ptr; }
        const T& operator*() const { return *m_Ptr; }

        T* Get() { return m_Ptr; }
        const T* Get() const { return m_Ptr; }

        void Reset(T* InPtr = nullptr)
        {
            DecreaseReferenceCount();
            m_Ptr = InPtr;
            m_Storage = new RefData();
            m_Storage->IncreaseReferenceCount();
        }

        T* Release()
        {
            delete m_Storage;
            return m_Ptr;
        }

        bool operator==(const Ref<T>& other) const { return m_Ptr == other.m_Ptr; }
        bool operator!=(const Ref<T>& other) const { return m_Ptr != other.m_Ptr; }

        template<typename Other>
        Ref<Other> As() const { return Ref<Other>(*this); }

    public:
        template<typename... Args>
        static Ref<T> Create(Args&&... args)
        {
            return Ref<T>(new T(std::forward<Args>(args)...));
        }

    private:
        void IncreaseReferenceCount() const
        {
            if (m_Storage)
                m_Storage->IncreaseReferenceCount();
        }

        void DecreaseReferenceCount() const
        {
            if (!m_Storage)
                return;

            m_Storage->DecreaseReferenceCount();

            // Free the object and the storage if reference count is 0
            if (m_Storage->GetReferenceCount() == 0)
            {
                delete m_Ptr;
                m_Ptr = nullptr;

                delete m_Storage;
                m_Storage = nullptr;
            }
        }

    private:
        template<class Other>
        friend class Ref;

        mutable T* m_Ptr;
        mutable RefData* m_Storage;
    };

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return Ref<T>::Create(std::forward<Args>(args)...);
    }
}

#endif //PANTHERA_POINTER_HPP
