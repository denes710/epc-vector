#define BOOST_TEST_MODULE practical5_test

#include <utility>

#include <boost/test/included/unit_test.hpp>

#include "vector.h"

#include "X.h"

BOOST_AUTO_TEST_CASE(empty_vector_test)
{
   X::reset();

   epc::vector<X, 0> v;

   BOOST_TEST( v.data() != nullptr );
   BOOST_TEST( v.size() == 0 );
   BOOST_TEST( v.capacity() == 0 );

   BOOST_TEST( X::constructed() == 0 );
}

BOOST_AUTO_TEST_CASE(growing_capcacity_test)
{
   X::reset();

   epc::vector<X, 0> v;
   BOOST_TEST( v.size() == 0 );
   BOOST_TEST( v.capacity() == 0 );

   v.push_back(1);
   BOOST_TEST( v.size() == 1 );
   BOOST_TEST( v.capacity() == 1 );

   v.push_back(2);
   BOOST_TEST( v.size() == 2 );
   BOOST_TEST( v.capacity() == 2 );

   v.push_back(3);
   BOOST_TEST( v.size() == 3 );
   BOOST_TEST( v.capacity() == 4 );

   v.push_back(4);
   BOOST_TEST( v.size() == 4 );
   BOOST_TEST( v.capacity() == 4 );
   
   v.push_back(5);
   BOOST_TEST( v.size() == 5 );
   BOOST_TEST( v.capacity() == 8 );
}

BOOST_AUTO_TEST_CASE(clean_up_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;

      for (int i = 1; i < 8; i++)
         v.push_back(i);
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(correct_values_test)
{
   X::reset();

   epc::vector<X, 0> v;

   v.push_back(1);
   BOOST_TEST( v[0] == 1 );
   BOOST_TEST( *v.data() == 1 );

   v.push_back(2);
   BOOST_TEST( v[0] == 1 );
   BOOST_TEST( v[1] == 2 );
   BOOST_TEST( *(v.data() + 1) == 2 );

   v.push_back(3);
   BOOST_TEST( v[0] == 1 );
   BOOST_TEST( v[1] == 2 );
   BOOST_TEST( v[2] == 3 );
   BOOST_TEST( *(v.data() + 2) == 3 );
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      auto temp = v.data();

      epc::vector<X, 0> v_copy(v);

      BOOST_TEST( v_copy.data() != v.data() );

      BOOST_TEST( v.data() == temp );
      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );

      BOOST_TEST( v_copy.size() == 3 );
      BOOST_TEST( v_copy[0] == 1 );
      BOOST_TEST( v_copy[1] == 2 );
      BOOST_TEST( v_copy[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(copy_constructor_excpetion_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.push_back(1);

      X::set_copy_constructor_throw_n(1);
      X::set_copy_assignment_throw_n(1);

      bool propagated = false;

      try
      {
         epc::vector<X, 0> v_copy(v);
      }
      catch (...)
      {
         propagated = true;
      }

      BOOST_TEST( propagated == true );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(copy_assignment_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      auto temp = v.data();

      epc::vector<X, 0> v_copy;
      v_copy.push_back(4);
      v_copy.push_back(5);

      v_copy = v;

      BOOST_TEST( v_copy.data() != v.data() );

      BOOST_TEST( v.data() == temp );
      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );

      BOOST_TEST( v_copy.size() == 3 );
      BOOST_TEST( v_copy[0] == 1 );
      BOOST_TEST( v_copy[1] == 2 );
      BOOST_TEST( v_copy[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(self_copy_assignment_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      v = v;

      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(copy_assignment_exception_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.push_back(1);

      X::set_copy_constructor_throw_n(1);
      X::set_copy_assignment_throw_n(1);

      bool propagated = false;

      try
      {
         epc::vector<X, 0> v_copy;
         v_copy = v;
      }
      catch (...)
      {
         propagated = true;
      }

      BOOST_TEST( propagated == true );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(swap_content_test)
{
   X::reset();

   {
      epc::vector<X, 0> va;
      va.push_back(1);
      va.push_back(2);

      epc::vector<X, 0> vb;
      vb.push_back(3);
      vb.push_back(4);
      vb.push_back(5);

      va.swap(vb);

      BOOST_TEST( va.size() == 3 );
      BOOST_TEST( va[0] == 3 );
      BOOST_TEST( va[1] == 4 );
      BOOST_TEST( va[2] == 5 );
         
      BOOST_TEST( vb.size() == 2 );
      BOOST_TEST( vb[0] == 1 );
      BOOST_TEST( vb[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(swap_noexcept_test)
{
   X::reset();

   {
      epc::vector<X, 0> va;
      va.push_back(1);
      va.push_back(2);

      epc::vector<X, 0> vb;
      vb.push_back(3);
      vb.push_back(4);
      vb.push_back(5);

      auto constructed = X::constructed();

//      X::set_default_constructor_throw_n(1);
      X::set_int_constructor_throw_n(1);
      X::set_copy_constructor_throw_n(1);
      X::set_copy_assignment_throw_n(1);

      bool problem = false;

      try
      {
         va.swap(vb);
      }
      catch (...)
      {
         problem = true;
      }

      BOOST_TEST( problem == false );

      BOOST_TEST( X::constructed() == constructed );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );

   X::reset_exceptions();
}

BOOST_AUTO_TEST_CASE(reserve_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.reserve(1);

      BOOST_TEST( v.capacity() == 1 );
      BOOST_TEST( v.size() == 0 );

      v.push_back(1);

      BOOST_TEST( v.capacity() == 1 );
      BOOST_TEST( v.size() == 1 );
      BOOST_TEST( v[0] == 1 );

      v.reserve(3);

      BOOST_TEST( v.capacity() == 3 );
      BOOST_TEST( v.size() == 1 );
      BOOST_TEST( v[0] == 1 );

      v.push_back(2);
      v.push_back(3);
      
      BOOST_TEST( v.capacity() == 3 );
      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(reserve_exception_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;

//      X::set_default_constructor_throw_n(1);

      try
      {
         v.reserve(1);
      }
      catch(...)
      { }
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );

   X::reset_exceptions();

   X::reset();

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );

   X::reset_exceptions();
}

BOOST_AUTO_TEST_CASE(pop_back_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      auto capacity = v.capacity();
      auto destructed = X::destructed();
      
      v.pop_back();

      BOOST_TEST( v.capacity() == capacity );
      BOOST_TEST( v.size() == 2 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( X::destructed() == destructed + 1);
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_move_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);

      epc::vector<X, 2> v_move(std::move(v));

      BOOST_TEST( v_move.size() == 2 );

      BOOST_TEST( v_move[0] == 1 );
      BOOST_TEST( v_move[1] == 2 );

      BOOST_TEST( v.size() == 0 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(long_move_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      epc::vector<X, 2> v_move(std::move(v));

      BOOST_TEST( v_move.size() == 3 );

      BOOST_TEST( v_move[0] == 1 );
      BOOST_TEST( v_move[1] == 2 );
      BOOST_TEST( v_move[2] == 3 );

      BOOST_TEST( v.size() == 0 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(lvalue_push_back_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      X x1(1);
      X x2(2);

      v.push_back(x1);
      v.push_back(x2);

      BOOST_TEST( v.size() == 2 );

      BOOST_TEST( X::copy_constructed() == 2 );
      BOOST_TEST( X::move_constructed() == 0 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(rvalue_push_back_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(X(1));
      v.push_back(X(2));

      BOOST_TEST( v.size() == 2 );

      BOOST_TEST( X::copy_constructed() == 0 );
      BOOST_TEST( X::move_constructed() == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}


BOOST_AUTO_TEST_CASE(emplace_back_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.emplace_back(1);
      v.emplace_back(2);

      BOOST_TEST( v.size() == 2 );

      BOOST_TEST( X::int_constructed() == 2 );
      BOOST_TEST( X::copy_constructed() == 0 );
      BOOST_TEST( X::move_constructed() == 0 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(new_reserve_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.emplace_back(1);
      v.emplace_back(2);
      v.emplace_back(3);

      BOOST_TEST( X::copy_constructed() == 0 );
      BOOST_TEST( X::move_constructed() == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(push_back_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.reserve(2);

      auto data = v.data();

      v.push_back(1);
      v.push_back(2);

      BOOST_TEST( v.data() == data );
      BOOST_TEST( v.size() == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(clear_test)
{
   X::reset();

   {
      epc::vector<X, 0> v;
      v.reserve(2);

      v.push_back(1);
      v.push_back(2);

      auto destructed = X::destructed();

      v.clear();

      BOOST_TEST( v.size() == 0 );
      BOOST_TEST( v.capacity() == 2 );
      BOOST_TEST( X::destructed() == destructed + 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_vector_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);

      BOOST_TEST( v.size() == 2 );
      BOOST_TEST( v.capacity() == 2 );

      unsigned char* begin = reinterpret_cast<unsigned char*>(&v);
      unsigned char* end = begin + sizeof(v);

      unsigned char* data = reinterpret_cast<unsigned char*>(v.data());

      BOOST_TEST(( (data >= begin) && (data < end) ));
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(long_vector_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      unsigned char* begin = reinterpret_cast<unsigned char*>(&v);
      unsigned char* end = begin + sizeof(v);

      unsigned char* data = reinterpret_cast<unsigned char*>(v.data());

      BOOST_TEST(( (data < begin) || (data >= end) ));
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_copy_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);

      epc::vector<X, 2> v_copy(v);

      BOOST_TEST( v_copy.size() == 2 );

      BOOST_TEST( v_copy[0] == 1 );
      BOOST_TEST( v_copy[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(long_copy_test)
{
   X::reset();

   {
      epc::vector<X, 2> v;

      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      epc::vector<X, 2> v_copy(v);

      BOOST_TEST( v_copy.size() == 3 );

      BOOST_TEST( v_copy[0] == 1 );
      BOOST_TEST( v_copy[1] == 2 );
      BOOST_TEST( v_copy[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(long_long_swap_test)
{
   X::reset();

   {
      epc::vector<X, 2> v1;

      v1.push_back(1);
      v1.push_back(2);
      v1.push_back(3);

      epc::vector<X, 2> v2;

      v2.push_back(4);
      v2.push_back(5);
      v2.push_back(6);
      v2.push_back(7);

      v1.swap(v2);

      BOOST_TEST( v1.size() == 4 );
      BOOST_TEST( v2.size() == 3 );

      BOOST_TEST( v1[0] == 4 );
      BOOST_TEST( v1[1] == 5 );
      BOOST_TEST( v1[2] == 6 );
      BOOST_TEST( v1[3] == 7 );

      BOOST_TEST( v2[0] == 1 );
      BOOST_TEST( v2[1] == 2 );
      BOOST_TEST( v2[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_short_swap_test)
{
   X::reset();

   {
      epc::vector<X, 2> v1;

      v1.push_back(1);
      v1.push_back(2);

      epc::vector<X, 2> v2;

      v2.push_back(3);

      v1.swap(v2);

      BOOST_TEST( v1.size() == 1 );
      BOOST_TEST( v2.size() == 2 );

      BOOST_TEST( v1[0] == 3 );

      BOOST_TEST( v2[0] == 1 );
      BOOST_TEST( v2[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(short_long_swap_test)
{
   X::reset();

   {
      epc::vector<X, 2> v1;

      v1.push_back(1);
      v1.push_back(2);

      epc::vector<X, 2> v2;
      
      v2.push_back(3);
      v2.push_back(4);
      v2.push_back(5);

      v1.swap(v2);

      BOOST_TEST( v1.size() == 3 );
      BOOST_TEST( v2.size() == 2 );

      BOOST_TEST( v1[0] == 3 );
      BOOST_TEST( v1[1] == 4 );
      BOOST_TEST( v1[2] == 5 );

      BOOST_TEST( v2[0] == 1 );
      BOOST_TEST( v2[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}
