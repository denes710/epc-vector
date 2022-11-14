#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <algorithm>
#include <cstdlib>
#include <memory>

namespace epc
{
   template <typename T, size_t N>
   class vector
   {
      public:
         vector() noexcept
         {}

         vector& operator=(const vector& p_vector)
         {
            if (&p_vector == this)
               return *this;

            vector temp(p_vector);
            swap(temp);

            return *this;  
         }

         vector(const vector& p_vector)
         { initialize_from(p_vector); }

         ~vector()
         {} // union destruction is non-trivial

         T* data()
         { return m_data.get(); }
         const T* data() const
         { return m_data.get(); }

         T& operator[](size_t p_idx)
         { return m_data[p_idx]; }
         const T& operator[](size_t p_idx) const
         { return m_data[p_idx]; }

         void push_back(const T& p_data)
         {
            if (capacity() == m_size) // reallocation
            {
                  if (capacity() == 0)
                  {
                     m_capacity = 1;
                     m_data.reset((T*)::operator new(m_capacity * sizeof(T)));
                  }
                  else
                  {
                     reallocation(is_short() ? N * 2 : m_capacity * 2);
                  }
            }

            new (m_data.get() + m_size) T(p_data);

            ++m_size;
         }

         void swap(vector& p_other)
         {
            if (is_short() && p_other.is_short())
            {
               std::swap(m_size, p_other.m_size);
               std::swap(m_buffer, p_other.m_buffer);
            }
            else if (!is_short() && !p_other.is_short())
            {
               std::swap(m_size, p_other.m_size);

               T* tmp = m_data.release();
               m_data.reset(p_other.m_data.release());
               p_other.m_data.reset(tmp);
            }
            else
            {
               vector tmp(p_other);
               p_other.initialize_from(*this);
               initialize_from(tmp);
            }
         }

         size_t capacity() const
         { return is_short() ? N : m_capacity; }
         size_t size() const
         { return m_size; }

         void reserve(size_t p_capacity)
         {
            if (p_capacity <= capacity())
               return;

            reallocation(p_capacity);
         }

         void pop_back()
         {
            (m_data.get() + m_size - 1)->~T();
            --m_size;
         }

         void clear()
         {
            for (; m_size > 0; --m_size)
               (m_data.get() + m_size - 1)->~T();
         }

      private:
         struct SDeleter
         {
            SDeleter(unsigned& p_size, T* p_buffer)
               : m_size(p_size)
               , m_buffer(p_buffer)
            {}

            void operator()(T* p_ptr)
            {
               if (p_ptr == nullptr)
                  return;

               for (auto i = m_size.get(); i > 0; --i)
                  (p_ptr + i - 1)->~T();

               if (p_ptr != m_buffer)
                  ::operator delete(p_ptr); // deallocation of original storage
            }

            std::reference_wrapper<unsigned> m_size;
            const T* m_buffer;
         };

         void reallocation(size_t p_capacity)
         {
            T* tmp = (T*)::operator new(p_capacity * sizeof(T));

            for (auto i = 0u; i < m_size; ++i)
               new (tmp + i) T(*(m_data.get() + i));

            m_data.reset(tmp);
            m_capacity = p_capacity;
         }

         bool is_short() const
         { return m_data.get() == m_buffer; }

         void initialize_from(const vector& p_vector)
         {
            if (p_vector.is_short())
            {
               m_data.reset(m_buffer);
            }
            else
            {
               m_data.reset((T*)::operator new(p_vector.capacity() * sizeof(T)));
               m_capacity = p_vector.capacity();
            }

            for (auto i = 0u; i < p_vector.size(); ++i)
               new (m_data.get() + i) T(p_vector[i]);

            m_size = p_vector.size();
         }

         union
         {
            unsigned m_capacity;
            T m_buffer[N];
         };

         unsigned m_size = 0;
         using TUPtr = std::unique_ptr<T[], SDeleter>;
         TUPtr m_data = TUPtr(m_buffer, SDeleter(m_size, m_buffer));
   };
}

#endif
