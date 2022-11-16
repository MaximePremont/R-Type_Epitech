/* Unit testing for outcomes
(C) 2013-2022 Niall Douglas <http://www.nedproductions.biz/> (7 commits)


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifdef _MSC_VER
#pragma warning(disable : 4702)  // unreachable code
#endif

#include <boost/outcome.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>

BOOST_OUTCOME_AUTO_TEST_CASE(works_outcome_udts, "Tests that the outcome works as intended with user-defined types")
{
  using namespace BOOST_OUTCOME_V2_NAMESPACE;
  // No default constructor, no copy/move, no assignment
  {
    struct udt
    {
      int a;
      explicit udt(int _a)
          : a(_a)
      {
      }
      udt() = delete;
      udt(const udt &) = delete;
      udt(udt &&) = delete;
      udt &operator=(const udt &) = delete;
      udt &operator=(udt &&) = delete;
      ~udt() = default;
    };
    outcome<udt> foo(in_place_type<udt>, 5);
    BOOST_CHECK(5 == foo.value().a);
  }
#ifndef BOOST_NO_EXCEPTIONS
  // Emplace construct, throws during move and copy
  {
    struct udt
    {
      std::string a;
      explicit udt(std::string _a)
          : a(std::move(_a))
      {
      }
      udt() = delete;
      udt(const udt & /*unused*/) { throw std::logic_error("copy"); }
      udt(udt && /*unused*/) noexcept(false) { throw std::logic_error("move"); }  // NOLINT
      udt &operator=(const udt & /*unused*/) { throw std::logic_error("copy"); }
      udt &operator=(udt && /*unused*/) noexcept(false) { throw std::logic_error("move"); }  // NOLINT
      ~udt() { a.clear(); }
    };
    static_assert(!std::is_default_constructible<udt>::value, "udt is default constructible");
    static_assert(std::is_copy_constructible<udt>::value, "udt is not copy constructible");
    static_assert(std::is_move_constructible<udt>::value, "udt is not move constructible");
    static_assert(!std::is_default_constructible<outcome<udt>>::value, "outcome<udt> is default constructible");
    static_assert(std::is_copy_constructible<outcome<udt>>::value, "outcome<udt> is not copy constructible");
    static_assert(std::is_move_constructible<outcome<udt>>::value, "outcome<udt> is not move constructible");
    // Emplace constructs
    outcome<udt> foo(in_place_type<udt>, "niall");
    BOOST_CHECK("niall" == foo.value().a);
    try
    {
      auto foo2(foo);  // NOLINT
      BOOST_CHECK(false);
    }
    catch(const std::logic_error &e)
    {
      BOOST_CHECK(!strcmp(e.what(), "copy"));
    }
    catch(...)
    {
      BOOST_CHECK(false);
    }
    BOOST_CHECK("niall" == foo.value().a);
    try
    {
      auto foo2(std::move(foo));
      BOOST_CHECK(false);
    }
    catch(const std::logic_error &e)
    {
      BOOST_CHECK(!strcmp(e.what(), "move"));
    }
    catch(...)
    {
      BOOST_CHECK(false);
    }
    BOOST_CHECK("niall" == foo.value().a);  // NOLINT
    // Does throwing during copy assignment work?
    {
      outcome<udt> foo2(in_place_type<udt>, "douglas");
      try
      {
        foo2 = foo;
        BOOST_CHECK(false);
      }
      catch(const std::logic_error &e)
      {
        BOOST_CHECK(!strcmp(e.what(), "copy"));
        BOOST_CHECK(foo2.value().a == "douglas");
      }
      catch(...)
      {
        BOOST_CHECK(false);
      }
      BOOST_CHECK("niall" == foo.value().a);
    }
    // Does throwing during move assignment work?
    {
      outcome<udt> foo2(in_place_type<udt>, "douglas");
      try
      {
        foo2 = std::move(foo);
        BOOST_CHECK(false);
      }
      catch(const std::logic_error &e)
      {
        BOOST_CHECK(!strcmp(e.what(), "move"));
        BOOST_CHECK(foo2.value().a == "douglas");
      }
      catch(...)
      {
        BOOST_CHECK(false);
      }
      BOOST_CHECK("niall" == foo.value().a);  // NOLINT
    }
  }
#endif
}
