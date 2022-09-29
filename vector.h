#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <cstdlib>

namespace epc
{
   template <typename T, size_t N>
   class vector
   {
      public:
         vector() noexcept { }

         vector(const vector&) { }
         vector& operator=(const vector&) { }

         ~vector()
         {
            if (m_data)
                  delete[] m_data;
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
                     m_capacity = 1;
                     m_data = new T[m_capacity];
                  }
                  else
                  {
                     m_capacity = m_capacity * 2;
                     T* tmp = new T[m_capacity];

                     for (auto i = 0u; i < m_size; ++i)
                        tmp[i] = m_data[i];

                     delete[] m_data;
                     m_data = tmp;
                  }
            }

            m_data[m_size++] = p_data;
         }

         size_t capacity() const
         { return m_capacity; }
         size_t size() const
         { return m_size; }

         void reserve(size_t) { }

         void pop_back() { } 

         void clear() { }

         void swap(vector&) noexcept { }

      private:
         unsigned m_capacity = 0;
         unsigned m_size = 0;
         T* m_data = nullptr;
   };
}

#endif
