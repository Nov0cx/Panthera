#ifndef PANTHERA_STRINGBASE_HPP
#define PANTHERA_STRINGBASE_HPP

#include <memory>
#include <cinttypes>
#include <string>
#include <cassert>
#include <vector>

namespace Panthera
{
    namespace StringUtils
    {
        template<typename T>
        std::size_t GetLength(const T* str)
        {
            if (!str)
                return 0;
            return std::char_traits<T>::length(str);
        }

        template<typename T>
        void Copy(T* dest, const T* src, std::size_t length)
        {
            for (std::size_t i = 0; i < length; i++)
            {
                if (src[i] == '\0')
                    break;
                dest[i] = src[i];
            }
        }

        template<typename T>
        bool Equals(const T* str1, const T* str2)
        {
            return std::char_traits<T>::compare(str1, str2, GetLength(str1)) == 0;
        }

        template<typename T>
        T ToLower(T c)
        {
            if (c >= 'A' && c <= 'Z')
                return c + 32;
            return c;
        }

        template<typename T>
        T ToUpper(T c)
        {
            if (c >= 'a' && c <= 'z')
                return c - 32;
            return c;
        }
    }

    template<typename T>
    class StringBase
    {
    public:
        using Iterator = T*;

    public:
        StringBase()
        {
            Set((const T*)"");
        }

        StringBase(const T *str)
        {
            Set(str);
        }

        StringBase(const StringBase<T> &str)
        {
            Set(str.m_Data);
        }

        StringBase(StringBase<T> &&moved)
        {
            Set(moved.m_Data);
            delete[] moved.m_Data;
            moved.m_Data = nullptr;
            moved.m_Length = 0;
        }

        StringBase(const std::basic_string<T> &str)
        {
            Set(str.c_str());
        }

        StringBase(const std::basic_string<T> &&moved)
        {
            Set(moved.c_str());
        }

        ~StringBase()
        {
            if (m_Data != nullptr)
                delete[] m_Data;
        }

        inline StringBase<T>& operator=(const StringBase<T> &str)
        {
            Set(str.m_Data);
            return *this;
        }

        inline StringBase<T>& operator=(StringBase<T> &&moved)
        {
            Set(moved.m_Data);
            delete[] moved.m_Data;
            moved.m_Data = nullptr;
            moved.m_Length = 0;
            return *this;
        }

        inline StringBase<T>& operator=(const T *str)
        {
            Set(str);
            return *this;
        }

        inline StringBase<T>& operator=(const std::basic_string<T> &str)
        {
            Set(str.c_str());
            return *this;
        }

        inline StringBase<T>& operator=(const std::basic_string<T> &&moved)
        {
            Set(moved.c_str());
            return *this;
        }

        inline void Append(const T *str)
        {
            const auto oldLength = m_Length;
            const auto oldData = m_Data;

            m_Length = oldLength + StringUtils::GetLength(str);
            m_Data = new T[m_Length + 1];

            StringUtils::Copy(m_Data, oldData, oldLength);
            StringUtils::Copy(m_Data + oldLength, str, m_Length - oldLength);
            m_Data[m_Length] = '\0';

            delete[] oldData;
        }

        inline void Append(StringBase<T> toAppend)
        {
            Append(toAppend.m_Data);
        }

        inline void Append(const std::basic_string<T> &str)
        {
            Append(str.c_str());
        }

        inline StringBase<T> operator+=(const T *str)
        {
            Append(str);
            return *this;
        }

        inline StringBase<T> operator+=(const StringBase<T> &str)
        {
            Append(str);
            return *this;
        }

        inline StringBase<T> operator+=(const std::basic_string<T> &str)
        {
            Append(str);
            return *this;
        }

        inline StringBase<T> operator+(const T *str)
        {
            StringBase<T> newStr = *this;
            newStr.Append(str);
            return newStr;
        }

        inline StringBase<T> operator+(const StringBase<T> &str)
        {
            StringBase<T> newStr = *this;
            newStr.Append(str);
            return newStr;
        }

        inline StringBase<T> operator+(const std::basic_string<T> &str)
        {
            StringBase<T> newStr = *this;
            newStr.Append(str);
            return newStr;
        }

        inline Iterator Find(const T c)
        {
            for (int64_t i = 0; i < m_Length; i++)
            {
                if (m_Data[i] == c)
                    return m_Data + i;
            }
            return end();
        }

        inline Iterator Find(const T *str)
        {
            const auto length = StringUtils::GetLength(str);
            for (uint32_t i = 0; i < m_Length; i++)
            {
                if (m_Data[i] == str[0])
                {
                    bool found = true;
                    for (uint32_t j = 0; j < length; j++)
                    {
                        if (m_Data[i + j] != str[j])
                        {
                            found = false;
                            break;
                        }
                    }

                    if (found)
                        return m_Data + i;
                }
            }

            return end();
        }

        inline Iterator Find(const StringBase<T> &str)
        {
            return Find(str.m_Data);
        }

        inline Iterator Find(const std::basic_string<T> &str)
        {
            return Find(str.c_str());
        }

        inline Iterator FindLast(const T *str)
        {
            const auto length = StringUtils::GetLength(str);
            for (uint32_t i = m_Length - 1; i >= 0; i--)
            {
                if (m_Data[i] == str[0])
                {
                    bool found = true;
                    for (uint32_t j = 0; j < length; j++)
                    {
                        if (m_Length - i < length)
                        {
                            found = false;
                            break;
                        }
                        if (m_Data[i + j] != str[j])
                        {
                            found = false;
                            break;
                        }
                    }

                    if (found)
                        return m_Data + i;
                }
            }

            return end();
        }

        inline Iterator FindLast(const StringBase<T> &str)
        {
            return FindLast(str.m_Data);
        }

        inline Iterator FindLast(const std::basic_string<T> &str)
        {
            return FindLast(str.c_str());
        }

        inline StringBase<T> Substring(uint32_t start, uint32_t length)
        {
            if (start >= m_Length)
                return StringBase<T>();

            if (start + length > m_Length)
                length = m_Length - start;

            T *data = new T[length + 1];
            StringUtils::Copy(data, m_Data + start, length);
            data[length] = '\0';

            StringBase<T> str(data);
            delete[] data;
            return str;
        }

        inline StringBase<T> Substring(uint32_t start)
        {
            return Substring(start, m_Length - start);
        }
        
        inline StringBase<T> Substring(Iterator start, Iterator end)
        {
            return Substring(start - m_Data, end - start);
        }
        
        inline StringBase<T> Substring(Iterator start)
        {
            return Substring(start - m_Data, m_Length - (start - m_Data));
        }

        inline StringBase<T> Substring(const T *str)
        {
            const auto index = Find(str);
            if (index == -1)
                return StringBase<T>();

            return Substring(index + StringUtils::GetLength(str));
        }

        inline StringBase<T> Substring(const StringBase<T> &str)
        {
            return Substring(str.m_Data);
        }

        inline StringBase<T> Substring(const std::basic_string<T> &str)
        {
            return Substring(str.c_str());
        }

        inline StringBase<T> SubstringLast(const T *str)
        {
            const auto index = FindLast(str);
            if (index == end())
                return StringBase<T>();

            return Substring(begin(), index);
        }

        inline StringBase<T> SubstringLast(const StringBase<T> &str)
        {
            return SubstringLast(str.m_Data);
        }

        inline StringBase<T> SubstringLast(const std::basic_string<T> &str)
        {
            return SubstringLast(str.c_str());
        }

        inline StringBase<T> SubstringBefore(const T *str)
        {
            const auto index = Find(str);
            if (index == end())
                return StringBase<T>();

            return Substring(0, index);
        }

        inline StringBase<T> SubstringBefore(const StringBase<T> &str)
        {
            return SubstringBefore(str.m_Data);
        }

        inline StringBase<T> SubstringBefore(const std::basic_string<T> &str)
        {
            return SubstringBefore(str.c_str());
        }

        inline StringBase<T> SubstringBeforeLast(const T *str)
        {
            const auto index = FindLast(str);
            if (index == end())
                return StringBase<T>();

            return Substring(0, index);
        }

        inline StringBase<T> SubstringBeforeLast(const StringBase<T> &str)
        {
            return SubstringBeforeLast(str.m_Data);
        }

        inline StringBase<T> SubstringBeforeLast(const std::basic_string<T> &str)
        {
            return SubstringBeforeLast(str.c_str());
        }

        inline void Remove(uint32_t start, uint32_t length)
        {
            assert(start <= m_Length);
            assert(start + length <= m_Length);

            if (start + length > m_Length)
                length = m_Length - start;

            for (uint32_t i = start; i < m_Length - length; i++)
                m_Data[i] = m_Data[i + length];

            m_Length -= length;
            m_Data[m_Length] = '\0';
        }
        
        inline void Remove(Iterator start, Iterator end)
        {
            Remove(start - m_Data, end - start);
        }
        
        inline void Remove(Iterator start)
        {
            Remove(start - m_Data, m_Length - (start - m_Data));
        }

        inline void RemoveAll(const T *str)
        {
            const auto length = StringUtils::GetLength(str);
            for (uint32_t i = 0; i < m_Length; i++)
            {
                if (m_Data[i] == str[0])
                {
                    bool found = true;
                    for (uint32_t j = 0; j < length; j++)
                    {
                        if (m_Data[i + j] != str[j])
                        {
                            found = false;
                            break;
                        }
                    }

                    if (found)
                    {
                        Remove(i, length);
                        i--;
                    }
                }
            }
        }

        inline void RemoveAll(const StringBase<T> &str)
        {
            RemoveAll(str.m_Data);
        }

        inline void Replace(const T *str, const T *replace)
        {
            const auto length = StringUtils::GetLength(str);
            const auto replaceLength = StringUtils::GetLength(replace);

            for (uint32_t i = 0; i < m_Length; i++)
            {
                if (m_Data[i] == str[0])
                {
                    bool found = true;
                    for (uint32_t j = 0; j < length; j++)
                    {
                        if (m_Data[i + j] != str[j])
                        {
                            found = false;
                            break;
                        }
                    }

                    if (found)
                    {
                        if (replaceLength > length)
                        {
                            const auto diff = replaceLength - length;
                            const auto newLength = m_Length + diff;
                            T *newData = new T[newLength + 1];
                            StringUtils::Copy(newData, m_Data, i);
                            StringUtils::Copy(newData + i, replace, replaceLength);
                            StringUtils::Copy(newData + i + replaceLength, m_Data + i + length, m_Length - i - length);
                            newData[newLength] = '\0';

                            delete[] m_Data;
                            m_Data = newData;
                            m_Length = newLength;
                        }
                        else
                        {
                            StringUtils::Copy(m_Data + i, replace, replaceLength);
                            if (replaceLength < length)
                                Remove(i + replaceLength, length - replaceLength);
                        }
                    }
                }
            }
        }

        inline bool Contains(const T *str)
        {
            return Find(str) != end();
        }

        inline bool Contains(const StringBase<T> &str)
        {
            return Find(str) != end();
        }

        inline bool Contains(const std::basic_string<T> &str)
        {
            return Find(str) != end();
        }

        inline bool Equals(const T *str)
        {
            return Equals(StringBase<T>(str));
        }

        inline bool Equals(const StringBase<T> &str)
        {
            if (m_Length != str.m_Length)
                return false;

            for (uint32_t i = 0; i < m_Length; i++)
            {
                if (m_Data[i] != str.m_Data[i])
                    return false;
            }

            return true;
        }

        inline bool Equals(const std::basic_string<T> &str)
        {
            return Equals(str.c_str());
        }

        inline StringBase<T> ToLower()
        {
            StringBase<T> str(m_Data);
            for (uint32_t i = 0; i < m_Length; i++)
                str.m_Data[i] = StringUtils::ToLower(str.m_Data[i]);
            return str;
        }

        inline StringBase<T> ToUpper()
        {
            StringBase<T> str(m_Data);
            for (uint32_t i = 0; i < m_Length; i++)
                str.m_Data[i] = StringUtils::ToUpper(str.m_Data[i]);
            return str;
        }

        inline StringBase<T> Copy()
        {
            return StringBase<T>(m_Data);
        }

        inline const StringBase<T> Copy() const
        {
            return StringBase<T>(m_Data);
        }

        inline bool operator==(const T *str)
        {
            return Equals(str);
        }

        inline bool operator==(const StringBase<T> &str)
        {
            return Equals(str);
        }

        inline bool operator==(const std::basic_string<T> &str)
        {
            return Equals(str);
        }

        inline bool operator!=(const T *str)
        {
            return !Equals(str);
        }

        inline bool operator!=(const StringBase<T> &str)
        {
            return !Equals(str);
        }

        inline bool operator!=(const std::basic_string<T> &str)
        {
            return !Equals(str);
        }

        inline T& operator[](uint32_t index)
        {
            return m_Data[index];
        }

        inline const T& operator[](uint32_t index) const
        {
            return m_Data[index];
        }

        inline T* Get()
        {
            return m_Data;
        }

        inline const T* Get() const
        {
            return m_Data;
        }

        inline T* GetOwned()
        {
            T *data = new T[m_Length + 1];
            StringUtils::Copy(data, m_Data, m_Length);
            data[m_Length] = '\0';
            return data;
        }

        inline const T* GetOwned() const
        {
            return GetOwned();
        }

        inline uint32_t GetLength() const
        {
            return m_Length;
        }

        inline std::size_t GetSize() const
        {
            return sizeof(this);
        }

        inline operator T*()
        {
            return m_Data;
        }

        inline operator const T*() const
        {
            return m_Data;
        }

        inline operator std::basic_string<T>()
        {
            return std::basic_string<T>(m_Data);
        }

        inline operator const std::basic_string<T>() const
        {
            return std::basic_string<T>(m_Data);
        }

        inline void Clear()
        {
            if (m_Data != nullptr)
                delete[] m_Data;
            m_Data = nullptr;
            m_Length = 0;
        }

        inline bool IsEmpty() const
        {
            return m_Length == 0 || m_Data == nullptr || m_Data[0] == '\0';
        }

        inline Iterator begin()
        {
            return m_Data;
        }

        inline Iterator end()
        {
            return m_Data + m_Length;
        }

        inline const Iterator cbegin() const
        {
            return m_Data;
        }

        inline const Iterator cend() const
        {
            return m_Data + m_Length;
        }

        inline uint32_t IteratorToIndex(Iterator it)
        {
            return it - m_Data;
        }

        inline T operator [] (Iterator it)
        {
            return *it;
        }

        inline const T operator [] (const Iterator it) const
        {
            return *it;
        }

        inline Iterator IndexToIterator(uint32_t index)
        {
            return m_Data + index;
        }

        inline Iterator IndexToIterator(uint32_t index) const
        {
            return m_Data + index;
        }

        inline static StringBase<T> Empty()
        {
            return StringBase<T>();
        }

        inline static StringBase<T> From(const T *str)
        {
            return StringBase<T>(str);
        }

        inline static StringBase<T> From(const StringBase<T> &str)
        {
            return StringBase<T>(str);
        }

        inline static StringBase<T> From(const std::basic_string<T> &str)
        {
            return StringBase<T>(str);
        }

        inline static StringBase<T> From(uint64_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(int64_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(uint32_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(int32_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(uint16_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(int16_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(uint8_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(int8_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(float value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(double value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(long double value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(bool value)
        {
            return StringBase<T>(value ? "true" : "false");
        }

        inline static StringBase<T> From(char value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(wchar_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(char16_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(char32_t value)
        {
            return StringBase<T>(std::to_string(value));
        }

        inline static StringBase<T> From(void *value)
        {
            return StringBase<T>(std::to_string((uint64_t)value));
        }

        inline static std::vector<StringBase<T>> Split(StringBase<T> &str, T delimiter)
        {
            std::vector<StringBase<T>> result;
            Iterator pos = str.end();
            while ((pos = str.Find(delimiter)) != str.end())
            {
                result.push_back(str.Substring(0, pos));
                str = str.Substring(pos + 1);
            }
            result.push_back(str);

            return result;
        }
    private:
        inline void Set(const T *str)
        {
            if (m_Data)
                delete[] m_Data;
            m_Length = StringUtils::GetLength(str);
            if (m_Length <= 0)
            {
                m_Data = nullptr;
                return;
            }
            m_Data = new T[m_Length + 1];
            StringUtils::Copy(m_Data, str, m_Length);
            m_Data[m_Length] = '\0';
        }
    private:
        T *m_Data = nullptr;
        uint32_t m_Length;
    };

    using String = StringBase<char>;
    using WString = StringBase<wchar_t>;
    using U16String = StringBase<char16_t>;
    using U32String = StringBase<char32_t>;
}

namespace std
{
    template<typename T>
    struct hash<Panthera::StringBase<T>>
    {
        std::size_t operator()(const Panthera::StringBase<T> &str) const
        {
            return std::hash<std::basic_string<T>>()(str);
        }
    };
}

#endif //PANTHERA_STRINGBASE_HPP
