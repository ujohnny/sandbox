#include <vector>
#include <iostream>
#include <iterator>

typedef std::string Commit;
typedef std::vector< Commit > Repo;

bool checkTestsSuccess(const Commit& c)
{
  if (c == "d0c2ce99" || c == "01f87797")
  {
    return true;
  }
  else
  {
    return false;
  }
}

Commit bisect(const Repo::const_iterator& begin, const Repo::const_iterator& end)
{
  int distance = std::distance( begin, end );
  if (distance == 2)
  {
    if ( checkTestsSuccess( *(begin + 1) ) == true )
    {
      // it means that there're no commits which have broken tests
      return "";
    }
    else
    {
      return checkTestsSuccess( *begin ) ? *(begin + 1) : *begin;
    }
  }

  Repo::const_iterator center = begin + distance / 2;
  Repo::const_iterator last = end - 1;

  bool beginPassed = checkTestsSuccess( *begin );
  bool centerPassed = checkTestsSuccess( *center );
  bool lastPassed = checkTestsSuccess( *last );

  Commit res;

  if (beginPassed == centerPassed == true)
  {
    res = bisect(center, end);
  }
  else
  {
    res = bisect(begin, center + 1);
  }

  return res;
}

int main()
{
  Repo r;
  r.push_back("d0c2ce99");
  r.push_back("01f87797");
  r.push_back("6b9483d9");
  r.push_back("685b6af0");
  r.push_back("c7458c0e");

  std::cout << bisect(r.begin(), r.end()) << std::endl;

  return 0;
}
