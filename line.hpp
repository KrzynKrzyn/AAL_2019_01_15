#ifndef LINE_HPP_INCLUDED
#define LINE_HPP_INCLUDED

bool double_equals(double a, double b, double epsilon)
{
    return std::abs(a - b) < epsilon;
}

double round_double(double a, double decimals)
{
    int cx = 10 * decimals * a;
    a = (double)cx / (10 * decimals);

    return a;
}

class Line : public Informed<std::list<Point>::iterator>
{
    public:
        double x_slope, y_slope;
        Point pin;

        Point normalizedPin() const
        {
            double x, y;

            if(x_slope > std::abs(y_slope))
            {
                x = 0;
                y = pin.Y() - (y_slope/x_slope) * pin.X();
            }
            else
            {
                y = 0;
                x = pin.X() - (x_slope/y_slope) * pin.Y();
            }

            return Point(x,y);
        }

        std::pair<double,double> normalizedSlope() const
        {
            double x, y, r;

            r = std::sqrt(x_slope*x_slope + y_slope*y_slope);

            x = x_slope / r;
            y = y_slope / r;

            return std::pair<double,double>(x,y);
        }

    public:
        int solveSize;
        bool solveTested;

        bool doesBelong(const Point p) const
        {
            return double_equals(x_slope * (p.Y()-pin.Y()), y_slope * (p.X()-pin.X()), 0.000001); //std::numeric_limits<double>::epsilon()
        }

        bool isIdentical(const Line l) const
        {
            if(double_equals(y_slope*l.x_slope, x_slope*l.y_slope, 0.000001))
                return this->doesBelong(l.pin);

            return false;
        }

        bool operator==(const Line &other) const
        {
            return isIdentical(other);
        }

        Line(Point p1, Point p2)
        {
            x_slope = std::abs(p1.X() - p2.X());
            y_slope = (p1.X() > p2.X()) ? p1.Y()-p2.Y() : p2.Y()-p1.Y();

            pin = p1;
        }
};

namespace std {
/*
  template <>
  struct hash<Line>
  {
    std::size_t operator()(const Line& l) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      return (   (hash<double>()(l.x_slope)
               ^ (hash<double>()(l.y_slope) << 1)) >> 1)
               ^ ((hash<double>()(l.pin.X()) << 1)
               ^ (hash<double>()(l.pin.Y())));
    }
  };
  */
  template <>
  struct hash<Line>
  {
    std::size_t operator()(const Line& l) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      Point npin = l.normalizedPin();
      std::pair<double, double> nslope = l.normalizedSlope();

      npin = Point(round_double(npin.X(),6), round_double(npin.Y(),6));
      nslope = std::pair<double,double>(round_double(nslope.first,6), round_double(nslope.second,6));

      return (   (hash<double>()(nslope.first)
               ^ (hash<double>()(nslope.second) << 1)) >> 1)
               ^ ((hash<double>()(npin.X()) << 1)
               ^ (hash<double>()(npin.Y())));
    }
  };

  template <>
  struct hash<list<Line>::iterator>
  {
    std::size_t operator()(const list<Line>::iterator &line) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      Line l = *line;

      return (hash<Line>()(l));
    }
  };

}

#endif // LINE_HPP_INCLUDED
