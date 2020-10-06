

struct Point
{
  int x{ 0 }, y{ 0 };

  Point(){}
  
  Point(const int x, const int y) : x{x}, y{y} {}

  Point (const Point &obj)
  {
      x = obj.x;
      y = obj.y;
  }
};

struct Line
{
  Point *start, *end;
  
  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
  }

  ~Line()
  {
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
      Point *newStart = new Point(*start);
      Point *newEnd = new Point(*end);
      return Line{newStart, newEnd};
  }
};

int main () 
{

}