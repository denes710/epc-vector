#ifndef X_H
#define X_H

#include <cstdlib>
#include <new>
#include <utility>

class X
{
   static unsigned long
      constructed_,
//    default_constructed_,
      int_constructed_,
      copy_constructed_,
      move_constructed_,
      copy_assigned_,
      move_assigned_,
      destructed_,
      alive_;

   static std::pair<bool, int>
//    default_constructor_throws_,
      int_constructor_throws_,
      copy_constructor_throws_,
      copy_assignment_throws_;

   int i_;

public:
// X();
   X() = delete;
   X(int i);
   X(const X& other);
   X(X&& other) noexcept;
   X& operator=(const X& other);
   X& operator=(X&& other) noexcept;
   ~X(); 

   operator int() const;
/*
   static void* operator new(std::size_t count)
   {
      return ::operator new(count);
   }

   static void* operator new[](std::size_t count)
   {
      return ::operator new[](count);
   }

   static void operator delete(void* ptr)
   {
      ::operator delete(ptr);
   }

   static void operator delete[](void* ptr)
   {
      ::operator delete[](ptr);
   }
*/
/*
   static void operator delete(void* ptr, std::size_t size)
   {
      ::operator delete(ptr, size);
   }

   static void operator delete[](void* ptr, std::size_t size)
   {
      ::operator delete[](ptr, size);
   }
*/

   static unsigned long constructed();
// static unsigned long default_constructed();
   static unsigned long int_constructed();
   static unsigned long copy_constructed();
   static unsigned long move_constructed();
   static unsigned long copy_assigned();
   static unsigned long move_assigned();
   static unsigned long destructed();
   static unsigned long alive();

   static void reset();

// static void set_default_constructor_throw_n(int);
   static void set_int_constructor_throw_n(int);
   static void set_copy_constructor_throw_n(int);
   static void set_copy_assignment_throw_n(int);

   static void reset_exceptions();
};

#endif
