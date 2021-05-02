#include<iostream>
using namespace std;
#include "rect.hpp"

Rect::Rect(int length, int breadth) :length_(length), breadth_(breadth) {}
bool operator<(const Rect& lhs, const Rect& rhs) // if area is lesser or not
{
  return (lhs.length_ * lhs.breadth_) < (rhs.length_ * rhs.breadth_);
}
bool operator==(const Rect& lhs, const Rect& rhs) // if area are equal
{
  return (lhs.length_ * lhs.breadth_) == (rhs.length_ * rhs.breadth_);
}
bool operator!=(const Rect& lhs, const Rect& rhs)
{
  return !(lhs==rhs);
}

ostream& operator<<(ostream& o,const Rect& rect)
{
  return o << "lenght : " << rect.length_ << " breadth : " << rect.breadth_;
}
