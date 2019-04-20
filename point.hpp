#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED

class Line;

class Point : public Informed<std::list<Line>::iterator>
{
    private:
        double x, y;

    public:
        int solveLineNo = 0;

        double X() const { return x; }
        double Y() const { return y; }

        Point():
            x(0), y(0) {}
/*
        Point(const Point &p):
            x(p.x), y(p.y) {}*/

        Point(double nx, double ny):
            x(nx), y(ny) {}
};

std::ostream& operator<<(std::ostream& os, const Point& obj)
{
    os << obj.X() << '\t' << obj.Y();

    return os;
}

#endif // POINT_HPP_INCLUDED
