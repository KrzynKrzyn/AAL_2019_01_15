#ifndef SOLVESET_HPP_INCLUDED
#define SOLVESET_HPP_INCLUDED

using std::list;
using std::vector;
using Solution::PlaneXY;

int choose(int n, int k)
{
    if(k == 0) return 1;
    return (n * choose(n - 1, k - 1)) / k;
}

unsigned long long factorial(int n)
{
    unsigned long long ret=1LL;

    for(;n>0;--n) ret *= n;

    return ret;
}

unsigned long long pairCombinations(int n)
{
    n += n%2;
    return factorial(n) / (factorial(n/2) * pow(2, n/2));
}

inline int ceilDiv(int a, int b)
{
    return (a + b - 1) / b;
}

double m1Complexity(int n, double normalization)
{
    return n * n * n * normalization;//87000
}

namespace Solution
{
    PlaneXY generateLines(list<Point> p);

    int findMinCover(PlaneXY& plane, int n, int k);
    int findMinCover(PlaneXY& plane);

    int countUniqueSolutions(PlaneXY& plane, int n, int k);
    int countUniqueSolutions(PlaneXY& plane, int solution);

    unsigned long long countSolutionCombinations(int solution, int unique_solutions);
};

PlaneXY Solution::generateLines(list<Point> p)
{
    PlaneXY plane;
    plane.points = p;

    if(plane.points.size() <= 2) return plane;

    list<Point>::iterator i=plane.points.begin(), j=plane.points.begin();

    while(true)
    {
        if(++j == plane.points.end())
        {
            if(++i == --plane.points.end()) return plane;

            j = i;
            ++j;
        }

        Line subject(*i, *j);

        if(plane.isDuplicate(subject)) continue;

        subject.insertData(i);
        subject.insertData(j);

        auto n = j;
        ++n;
        for(; n != plane.points.end(); ++n)
            if(subject.doesBelong(*n)) subject.insertData(n);

        if(subject.size() > 2) plane.push_front(subject);
    }
}

int Solution::findMinCover(PlaneXY& plane)
{
    int lonepoints = 0, two_alone = 0;
    std::unordered_set<list<Line>::iterator> candidate, eligible;

    for(Point &p: plane.points) if(p.size() == 0) ++lonepoints;
    for(Point &p: plane.points) if(p.size() == 1)
    {
        if(candidate.find(p.getData(0)) != candidate.end()) eligible.insert(p.getData(0));
        else candidate.insert(p.getData(0));
    }

    for(list<Line>::iterator l : eligible)
    {
        two_alone += (*l).solveSize;
        plane.propagateOff(*l);
    }
//std::cout << lonepoints << " <> " << two_alone << std::endl;
    int solution = findMinCover(plane,
                                plane.points.size() - two_alone - lonepoints + (lonepoints % 2),
                                ceilDiv(plane.points.size(), 2))
                                + lonepoints/2 + eligible.size();

    for(list<Line>::iterator l : eligible) plane.propagateOn(*l);

    return solution;
}

int Solution::findMinCover(PlaneXY& plane, int n, int k)
{
    if(n <= 0) return 0;
    else if(k <= 0) return -1;

    int ret = -1;
    int limit = ceilDiv(n, k);

    if(limit <= 2)
    {
        ret = ceilDiv(n, 2);
        k = ret - 1;
        if(k <= 0) return ret;
        limit = ceilDiv(n, k);
    }

    list<Line> tlines;

    for(int i=plane.lines.size()-1; i>=limit; --i)
    while(!plane.lines[i].empty())
    {
        Line &l = *plane.lines[i].begin();
        plane.transferTo(tlines, l);

        plane.propagateOff(l);
        int tempret = findMinCover(plane, n-l.solveSize, k-1);
        plane.propagateOn(l);

        if(tempret >= 0)
        {
            ret = tempret + 1;
            k = ret - 1;
            if(k <= 0)
            {
                plane.transferFrom(tlines);
                return ret;
            }
            limit = ceilDiv(n, k);
        }
    }

    plane.transferFrom(tlines);

    return ret;
}

int Solution::countUniqueSolutions(PlaneXY& plane, int solution)
{
    return countUniqueSolutions(plane, plane.points.size(), solution);
}

int Solution::countUniqueSolutions(PlaneXY& plane, int n, int k)
{
    if(n <= 0) return 1;
    else if(k <= 0) return 0;

    int limit = ceilDiv(n, k);
    if(limit <= 2) return pairCombinations(n);//return 1;//

    int ret = 0;

    list<Line> tlines;

    for(int i=plane.lines.size()-1; i >= limit; --i)
    while(!plane.lines[i].empty())
    {
        Line &l = *plane.lines[i].begin();
        plane.transferTo(tlines, l);

        plane.propagateOff(l);
        ret += countUniqueSolutions(plane, n-l.solveSize, k-1);
        plane.propagateOn(l);
    }

    plane.transferFrom(tlines);

    return ret;
}

unsigned long long Solution::countSolutionCombinations(int solution, int unique_solutions)
{
    return factorial(solution) * unique_solutions;
}

void printLines(const PlaneXY& plane)
{
    for(size_t g=0; g<plane.lines.size(); g++)
    {
        std::cout << "======================= SIZE " << g << " =======================" << std::endl << std::endl;

        for(Line l : plane.lines[g])
        {
            std::cout << l.solveSize << " -- " << l.x_slope << ',' << l.y_slope << " :";
            for(size_t i=0; i<l.size(); i++) std::cout << '(' << l.getData(i)->X() << ',' << l.getData(i)->Y() << ')' << ' ';
            std::cout << std::endl;
        }
    }

    std::cout << "======================= END LINES =======================" << std::endl << std::endl;
}

#endif // SOLVESET_HPP_INCLUDED
