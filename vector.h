#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <algorithm>
#include <cstdlib>

namespace epc
{
   template <typename T, size_t N>
   class vector
   {
      public:
         vector() noexcept { }

         vector& operator=(const vector& p_vector)
         {
            if (&p_vector == this)
               return *this;

            vector temp(p_vector);
            swap(temp);

            return *this;  
         }

         vector(const vector& p_vector)
         {
            m_size = p_vector.size();
            m_capacity = p_vector.capacity();
            m_data = (T*)::operator new(m_capacity * sizeof(T));

            for (auto i = 0u; i < p_vector.size(); ++i)
               new (m_data + i) T(p_vector[i]);
         }

         ~vector()
         {
            clear(); // ending lifetime of original elements
            ::operator delete(m_data); // deallocation of original storage
         }

         T* data()
         { return m_data; }
         const T* data() const
         { return m_data; }

         T& operator[](size_t p_idx)
         { return m_data[p_idx]; }
         const T& operator[](size_t p_idx) const
         { return m_data[p_idx]; }

         void push_back(const T& p_data)
         {
            if (m_capacity == m_size) // reallocation
            {
                  if (m_capacity == 0)
                  {
                     m_data = (T*)::operator new(sizeof(T));
                     m_capacity = 1;
                  }
                  else
                  {
                     reallocation(m_capacity * 2);
                  }
            }

            new (m_data + m_size) T(p_data);
            ++m_size;
         }

         void swap(vector& p_other) noexcept
         {
            std::swap(m_capacity, p_other.m_capacity);
            std::swap(m_size, p_other.m_size);
            std::swap(m_data, p_other.m_data);
         }

         size_t capacity() const
         { return m_capacity; }
         size_t size() const
         { return m_size; }

         void reserve(size_t p_capacity)
         {
            // FIXME is it still okay?
            if (p_capacity <= m_capacity)
               return;

            reallocation(p_capacity);
         }

         void pop_back()
         {
            (m_data + m_size - 1)->~T();
            --m_size;
         }

         void clear()
         {
            for (; m_size > 0; --m_size)
               (m_data + m_size - 1)->~T();
         }

      private:
         void reallocation(size_t p_capacity)
         {                        
            T* tmp = (T*)::operator new(p_capacity * sizeof(T));

            for (auto i = 0u; i < m_size; ++i)
               new (tmp + i) T(*(m_data + i));

            for (auto i = m_size; i > 0; --i)
               (m_data + i - 1)->~T();

            ::operator delete(m_data); // deallocation of original storage

            m_data = tmp;
            m_capacity = p_capacity;
         }

         unsigned m_capacity = 0;
         unsigned m_size = 0;
         T* m_data = nullptr;
   };
}

#endif
