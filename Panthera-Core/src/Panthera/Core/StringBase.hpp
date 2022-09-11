#ifndef PANTHERA_STRINGBASE_HPP
#define PANTHERA_STRINGBASE_HPP

#include <memory>
#include <cinttypes>
#include <string>

namespace Panthera
{
    template<typename T>
    class StringBase
    {
    public:
        StringBase() = default;
        StringBase(const T *str)
        {
            m_Length = std::char_traits<T>::length(str);
            m_Data = new T[m_Length + 1];
            std::char_traits<T>::copy(m_Data, str, m_Length);
            m_Data[m_Length] = 0;
        }

        StringBase(const StringBase &other)
        {
            m_Data = other.m_Data;
            m_Length = other.m_Length;
        }

        StringBase(StringBase &&other) noexcept
        {
            m_Data = other.m_Data;
            m_Length = other.m_Length;
        }

        StringBase(const std::basic_string<T> &str)
        {
            m_Data = str.data();
            m_Length = str.length();
        }

        StringBase(std::basic_string<T> &&str) noexcept
        {
            m_Data = str.data();
            m_Length = str.length();
        }

        StringBase(const std::basic_string<T> &str, size_t pos, size_t len = std::basic_string<T>::npos)
        {
            m_Data = str.substr(pos, len).data();
            m_Length = str.substr(pos, len).length();
        }

        inline StringBase &operator=(const T* str)
        {
            m_Length = std::char_traits<T>::length(str);
            m_Data = new T[m_Length + 1];
            std::char_traits<T>::copy(m_Data, str, m_Length);
            m_Data[m_Length] = 0;
            return *this;
        }

        inline StringBase &operator=(const StringBase &other)
        {
            m_Data = other.m_Data;
            m_Length = other.m_Length;
            return *this;
        }

        inline StringBase &operator=(StringBase &&other) noexcept
        {
            m_Data = other.m_Data;
            m_Length = other.m_Length;
            return *this;
        }

        inline StringBase &operator=(const std::basic_string<T> &str)
        {
            m_Data = str.data();
            m_Length = str.length();
            return *this;
        }

        inline StringBase &operator=(std::basic_string<T> &&str) noexcept
        {
            m_Data = str.data();
            m_Length = str.length();
            return *this;
        }

        ~StringBase()
        {
        }

        inline const T *CStr() const
        {
            return m_Data;
        }

        inline T* Str()
        {
            return m_Data;
        }

        inline std::size_t Length() const
        {
            return m_Length;
        }

        inline void Append(const StringBase& other)
        {
            T* newStr = new T[Length() + other.Length()];
            std::memcpy(newStr, m_Data, Length());
            std::memcpy(newStr + Length(), other.m_Data, other.Length());
            delete m_Data;
            m_Data = newStr;
            m_Length += other.Length();
        }

        inline void Contains(T chr) const
        {
            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] == chr)
                    return true;
            }

            return false;
        }

        inline void Contains(const StringBase& other) const
        {
            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] == other.m_Data[0])
                {
                    for (std::size_t j = 0; j < other.Length(); j++)
                    {
                        if (m_Data[i + j] != other.m_Data[j])
                            break;

                        if (j == other.Length() - 1)
                            return true;
                    }
                }
            }

            return false;
        }

        inline void Replace(T chr, T newChr)
        {
            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] == chr)
                    m_Data[i] = newChr;
            }
        }

        inline std::size_t FindFirst(T chr) const
        {
            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] == chr)
                    return i;
            }

            return -1;
        }

        inline std::size_t FindLast(T chr) const
        {
            for (std::size_t i = Length() - 1; i >= 0; i--)
            {
                if (m_Data[i] == chr)
                    return i;
            }

            return -1;
        }

        inline std::size_t FindFirst(const StringBase& other) const
        {
            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] == other.m_Data[0])
                {
                    for (std::size_t j = 0; j < other.Length(); j++)
                    {
                        if (m_Data[i + j] != other.m_Data[j])
                            break;

                        if (j == other.Length() - 1)
                            return i;
                    }
                }
            }

            return -1;
        }

        inline std::size_t FindLast(const StringBase& other) const
        {
            for (std::size_t i = Length() - 1; i >= 0; i--)
            {
                if (m_Data[i] == other.m_Data[0])
                {
                    for (std::size_t j = 0; j < other.Length(); j++)
                    {
                        if (m_Data[i + j] != other.m_Data[j])
                            break;

                        if (j == other.Length() - 1)
                            return i;
                    }
                }
            }

            return -1;
        }

        inline StringBase SubString(std::size_t start, std::size_t end = Length()) const
        {
            T* newStr = new T[end - start];
            std::memcpy(newStr, m_Data + start, end - start);
            return StringBase(newStr);
        }

        inline bool operator==(const StringBase& other) const
        {
            if (Length() != other.Length())
                return false;

            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] != other.m_Data[i])
                    return false;
            }

            return true;
        }

        inline bool operator!=(const StringBase& other) const
        {
            return *this != other;
        }

        inline operator std::basic_string<T>() const
        {
            return std::basic_string<T>(m_Data, m_Length);
        }

        inline operator const T*() const
        {
            return m_Data;
        }
    private:
        T *m_Data;
        std::size_t m_Length;
    };

    using String = StringBase<char>;
}

#endif //PANTHERA_STRINGBASE_HPP
