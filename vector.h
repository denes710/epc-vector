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
            : m_size(p_vector.size())
            , m_capacity(p_vector.capacity())
            , m_data((T*)::operator new(m_capacity * sizeof(T)), SDeleter(m_size))
         {
            for (auto i = 0u; i < p_vector.size(); ++i)
               new (m_data.get() + i) T(p_vector[i]);
         }

         ~vector() = default;

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
            if (m_capacity == m_size) // reallocation
            {
                  if (m_capacity == 0)
                  {
                     m_data.reset((T*)::operator new(m_capacity * sizeof(T)));
                     m_capacity = 1;
                  }
                  else
                  {
                     reallocation(m_capacity * 2);
                  }
            }

            new (m_data.get() + m_size) T(p_data);
            ++m_size;
         }

         void swap(vector& p_other) noexcept
         {
            std::swap(m_capacity, p_other.m_capacity);
            std::swap(m_size, p_other.m_size);

            T* tmp = m_data.release();
            m_data.reset(p_other.m_data.release());
            p_other.m_data.reset(tmp);
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
         void reallocation(size_t p_capacity)
         {                        
            T* tmp = (T*)::operator new(p_capacity * sizeof(T));

            for (auto i = 0u; i < m_size; ++i)
               new (tmp + i) T(*(m_data.get() + i));

            m_data.reset(tmp); 
            m_capacity = p_capacity;
         }

         struct SDeleter
         {
            SDeleter(unsigned& p_size)
               : m_size(p_size)
            {}

            void operator()(T* p_ptr)
            {
               if (p_ptr == nullptr)
                  return;

               for (auto i = m_size.get(); i > 0; --i)
                  (p_ptr + i - 1)->~T();

               ::operator delete(p_ptr); // deallocation of original storage
            }

            std::reference_wrapper<unsigned> m_size;
         };

         unsigned m_capacity = 0;
         unsigned m_size = 0;
         using TUPtr = std::unique_ptr<T[], SDeleter>;
         TUPtr m_data = TUPtr(nullptr, SDeleter(m_size));
   };
}

#endif
