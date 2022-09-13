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

        StringBase(const T chr)
        {
            m_Length = 1;
            m_Data = new T[m_Length + 1];
            m_Data[0] = chr;
            m_Data[m_Length] = 0;
        }

        StringBase(const StringBase<T> &other)
        {
            m_Data = other.m_Data;
            m_Length = other.m_Length;
        }

        StringBase(StringBase<T> &&other) noexcept
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

        inline StringBase<T> &operator=(const T* str)
        {
            m_Length = std::char_traits<T>::length(str);
            m_Data = new T[m_Length + 1];
            std::char_traits<T>::copy(m_Data, str, m_Length);
            m_Data[m_Length] = 0;
            return *this;
        }

        inline StringBase<T> &operator=(const StringBase<T> &other)
        {
            m_Data = other.m_Data;
            m_Length = other.m_Length;
            return *this;
        }

        inline StringBase<T> &operator=(StringBase<T> &&other) noexcept
        {
            m_Data = other.m_Data;
            m_Length = other.m_Length;
            return *this;
        }

        inline StringBase<T> &operator=(const std::basic_string<T> &str)
        {
            m_Data = str.data();
            m_Length = str.length();
            return *this;
        }

        inline StringBase<T> &operator=(std::basic_string<T> &&str) noexcept
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

        inline void Append(const StringBase<T>& other)
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

        inline void Contains(const StringBase<T>& other) const
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

        inline std::size_t FindFirst(const StringBase<T>& other) const
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

        inline std::size_t FindLast(const StringBase<T>& other) const
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

        inline StringBase<T> SubString(std::size_t start, std::size_t end) const
        {
            T* newStr = new T[end - start];
            std::memcpy(newStr, m_Data + start, end - start);
            return StringBase(newStr);
        }

        inline StringBase<T> SubString(std::size_t start) const
        {
            T* newStr = new T[Length() - start];
            std::memcpy(newStr, m_Data + start, Length() - start);
            return StringBase(newStr);
        }

        inline bool operator==(const StringBase<T>& other) const
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

        inline void ToLower()
        {
            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] >= 'A' && m_Data[i] <= 'Z')
                    m_Data[i] += 32;
            }
        }

        inline void ToUpper()
        {
            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] >= 'a' && m_Data[i] <= 'z')
                    m_Data[i] -= 32;
            }
        }

        inline bool EqualsIgnoreCase(const StringBase<T>& other) const
        {
            if (Length() != other.Length())
                return false;

            for (std::size_t i = 0; i < Length(); i++)
            {
                if (m_Data[i] != other.m_Data[i])
                {
                    if (m_Data[i] >= 'A' && m_Data[i] <= 'Z')
                    {
                        if (m_Data[i] + 32 != other.m_Data[i])
                            return false;
                    }
                    else if (m_Data[i] >= 'a' && m_Data[i] <= 'z')
                    {
                        if (m_Data[i] - 32 != other.m_Data[i])
                            return false;
                    }
                    else
                        return false;
                }
            }

            return true;
        }

        inline bool IsEmpty() const
        {
            return Length() == 0 || m_Data == nullptr || m_Data[0] == '\0';
        }

        inline operator bool() const
        {
            return !IsEmpty();
        }

        inline bool operator!=(const StringBase<T>& other) const
        {
            return *this != other;
        }

        inline operator std::basic_string<T>() const
        {
            return std::basic_string<T>(m_Data, m_Length);
        }

        inline operator T*()
        {
            return m_Data;
        }

        inline operator const T*() const
        {
            return m_Data;
        }

        inline StringBase<T> operator + (const StringBase<T>& other) const
        {
            return StringBase<T>(*this) += other;
        }

        inline StringBase<T> operator + (const T* str) const
        {
            return StringBase<T>(*this) += StringBase<T>(str);
        }

        inline StringBase<T> operator + (T chr) const
        {
            return StringBase<T>(*this) += StringBase<T>(chr);
        }

        inline StringBase<T> operator + (const std::basic_string<T>& str) const
        {
            return StringBase<T>(*this) += StringBase<T>(str);
        }

        inline StringBase<T> operator += (const StringBase<T>& other)
        {
            Append(other);
            return *this;
        }

        inline StringBase<T> operator += (const T* str)
        {
            Append(StringBase<T>(str));
            return *this;
        }


        inline StringBase<T> operator += (T chr)
        {
            Append(StringBase<T>(chr));
            return *this;
        }

        inline StringBase<T> operator += (const std::basic_string<T>& str)
        {
            Append(StringBase<T>(str));
            return *this;
        }

        inline T operator [] (std::size_t index) const
        {
            return m_Data[index];
        }

        inline T& operator [] (std::size_t index)
        {
            return m_Data[index];
        }

        inline static consteval StringBase<T> ToString(int32_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static consteval StringBase<T> ToString(uint32_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static consteval StringBase<T> ToString(int64_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static consteval StringBase<T> ToString(uint64_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static consteval StringBase<T> ToString(float value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static consteval StringBase<T> ToString(double value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static consteval StringBase<T> ToString(long double value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static consteval StringBase<T> ToString(bool value)
        {
            return StringBase<T>(value ? "true" : "false");
        }

        inline static consteval StringBase<T> ToString(char value)
        {
            return StringBase<T>(value);
        }

        inline static consteval StringBase<T> ToString(wchar_t value)
        {
            return StringBase<T>(value);
        }

        inline static consteval StringBase<T> ToString(char16_t value)
        {
            return StringBase<T>(value);
        }

        inline static consteval StringBase<T> ToString(char32_t value)
        {
            return StringBase<T>(value);
        }

        inline static consteval StringBase<T> ToString(const std::string& value)
        {
            return StringBase<T>(value);
        }
    private:
        T *m_Data;
        std::size_t m_Length;
    };

    using String = StringBase<char>;
    using WString = StringBase<wchar_t>;
    using U16String = StringBase<char16_t>;
    using U32String = StringBase<char32_t>;
    using U8String = StringBase<char8_t>;
}

#endif //PANTHERA_STRINGBASE_HPP
