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
            m_data = new T [m_capacity];

            try
            {
               for (auto i = 0u; i < p_vector.size(); ++i)
                  m_data[i] = p_vector[i];
            }
            catch (const std::exception& p_e)
            {
               std::cerr << "Error: " << p_e.what() << '\n';

               delete[] m_data;
               throw;
            }
         }

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
                     m_data = new T[1];
                     m_capacity = 1;
                  }
                  else
                  {
                     reallocation(m_capacity * 2);
                  }
            }

            m_data[m_size] = p_data;
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
            if (p_capacity <= m_capacity)
               return;

            reallocation(p_capacity);
         }

         void pop_back()
         { --m_size; } 

         void clear() { }

      private:
         void reallocation(size_t p_capacity)
         {                        
            T* tmp = new T[p_capacity];

            try
            {
               for (auto i = 0u; i < m_size; ++i)
                  tmp[i] = m_data[i];

               delete[] m_data;
               m_data = tmp;
               
               m_capacity = p_capacity;               
            }
            catch(const std::exception& p_e)
            {               
               std::cerr << "Error: " << p_e.what() << '\n';

               delete[] tmp;
               throw;
            }
         }

         unsigned m_capacity = 0;
         unsigned m_size = 0;
         T* m_data = nullptr;
   };
}

#endif
