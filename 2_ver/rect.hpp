#ifndef RECT_H
#define RECT_H

class Rect
{
  private:
    int length_;
    int breadth_;
  public:
    Rect(int = 0, int = 0);
    friend bool operator<(const Rect& , const Rect&);
    friend bool operator==(const Rect& , const Rect&);
    friend bool operator!=(const Rect& , const Rect&);
    friend ostream& operator<<(ostream& ,const Rect&);
};
#endif
