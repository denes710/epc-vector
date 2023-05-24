#include "X.h"

#include <stdexcept>

unsigned long X::constructed_ = 0;
//unsigned long X::default_constructed_ = 0;
unsigned long X::int_constructed_ = 0;
unsigned long X::copy_constructed_ = 0;
unsigned long X::move_constructed_ = 0;
unsigned long X::copy_assigned_ = 0;
unsigned long X::move_assigned_ = 0;
unsigned long X::destructed_ = 0;
unsigned long X::alive_ = 0;

//std::pair<bool, int> X::default_constructor_throws_{false, 0};
std::pair<bool, int> X::int_constructor_throws_{false, 0};
std::pair<bool, int> X::copy_constructor_throws_{false, 0};
std::pair<bool, int> X::copy_assignment_throws_{false, 0};

/*
X::X() : i_(-1)
{
   if ((default_constructor_throws_.first) && (--default_constructor_throws_.second == 0))
      throw std::runtime_error("default constructor");

   constructed_++;
   default_constructed_++;
   alive_++;
}
*/

X::X(int i) : i_(i)
{
   if ((int_constructor_throws_.first) && (--int_constructor_throws_.second == 0))
      throw std::runtime_error("int constructor");

   constructed_++;
   int_constructed_++;
   alive_++;
}

X::X(const X& other) : i_(other.i_)
{
   if ((copy_constructor_throws_.first) && (--copy_constructor_throws_.second == 0))
      throw std::runtime_error("copy constructor");

   constructed_++;
   copy_constructed_++;
   alive_++;
}

X::X(X&& other) noexcept : i_(other.i_)
{
   constructed_++;
   move_constructed_++;
   alive_++;
}

X& X::operator=(const X& other)
{
   if ((copy_assignment_throws_.first) && (--copy_assignment_throws_.second == 0))
      throw std::runtime_error("copy assignment operator");

   copy_assigned_++;
   i_ = other.i_;
   return *this;
}

X& X::operator=(X&& other) noexcept
{
   move_assigned_++;
   i_ = other.i_;
   return *this;
}

X::~X() 
{
   alive_--;
   destructed_++;
}

X::operator int() const { return i_; }

unsigned long X::constructed() { return constructed_; }
//unsigned long X::default_constructed() { return default_constructed_; }
unsigned long X::int_constructed() { return int_constructed_; }
unsigned long X::copy_constructed() { return copy_constructed_; }
unsigned long X::move_constructed() { return move_constructed_; }
unsigned long X::copy_assigned() { return copy_assigned_; }
unsigned long X::move_assigned() { return move_assigned_; }
unsigned long X::destructed() { return destructed_; }
unsigned long X::alive() { return alive_; }

void X::reset()
{
   constructed_ = 0;
// default_constructed_ = 0;
   int_constructed_ = 0;
   copy_constructed_ = 0;
   move_constructed_ = 0;
   copy_assigned_ = 0;
   move_assigned_ = 0;
   destructed_ = 0;
   alive_ = 0;
}

/*
void X::set_default_constructor_throw_n(int n)
{
   default_constructor_throws_ = {true, n};
}
*/

void X::set_int_constructor_throw_n(int n)
{
   int_constructor_throws_ = {true, n};
}

void X::set_copy_constructor_throw_n(int n)
{
   copy_constructor_throws_ = {true, n};
}

void X::set_copy_assignment_throw_n(int n)
{
   copy_assignment_throws_ = {true, n};
}

void X::reset_exceptions()
{
// default_constructor_throws_ = {false, 0};
   int_constructor_throws_ = {false, 0};
   copy_constructor_throws_ = {false, 0};
   copy_assignment_throws_ = {false, 0};
}
