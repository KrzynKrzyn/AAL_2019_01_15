#ifndef LINESET_HPP_INCLUDED
#define LINESET_HPP_INCLUDED

using std::list;
using std::vector;

namespace Solution
{

struct PlaneXY
{
    std::unordered_set<Line> duplicate_set;//TBD

    vector< list<Line> > lines;
    list<Point> points;

    size_t countLines();
    void enlargeTrunk(size_t size);

    void bondPoints(list<Line>::iterator subject);
    bool isDuplicate(const Line &subject) const;
    void push_front(Line &subject);

    void propagateOff(Line l);
    void propagateOn(Line l);

    void transferTo(list<Line> &tlines, Line &l);
    void transferFrom(list<Line> &tlines, Line &l);
    void transferFrom(list<Line> &tlines);
};

size_t PlaneXY::countLines()
{
    size_t counter = 0;

    for(list<Line> lst : lines) counter += lst.size();

    return counter;
}

void PlaneXY::enlargeTrunk(size_t size)
{
    for(size_t i=lines.size(); i<=size; ++i)
        lines.push_back(list<Line>());
}

void PlaneXY::bondPoints(list<Line>::iterator subject)
{
    for(size_t h=0; h<subject->size(); ++h)
    {
        subject->getData(h)->insertData(subject);
        subject->getData(h)->solveLineNo++;
    }
}

void PlaneXY::push_front(Line &subject)
{
    enlargeTrunk(subject.size());

    subject.solveSize = subject.size();
    subject.solveTested = false;

    lines[subject.size()].push_front(subject);

    bondPoints(lines[subject.size()].begin());

    duplicate_set.insert(subject);//TBD
}

bool PlaneXY::isDuplicate(const Line &subject) const
{
    //for(size_t i=0; i<lines.size(); ++i) for(Line duplicate_test : lines[i])
    //    if(subject.isIdentical(duplicate_test)) return true;

    if(duplicate_set.find(subject) != duplicate_set.end()) return true;//TBD

    return false;
}

void PlaneXY::propagateOff(Line l)
{
    for(size_t i=0; i<l.size(); ++i)
    {
        if(l.getData(i)->solveLineNo-- != l.getData(i)->size()) continue;

        for(size_t j=0; j<l.getData(i)->size(); ++j)
        {
            if(l.getData(i)->getData(j)->solveTested == true) continue;

            int branch = l.getData(i)->getData(j)->solveSize--; //look into that

            lines[branch].splice(lines[branch-1].begin(), lines[branch-1], l.getData(i)->getData(j));
        }
    }
}

void PlaneXY::propagateOn(Line l)
{
    for(size_t i=0; i<l.size(); ++i)
    {
        if(++l.getData(i)->solveLineNo != l.getData(i)->size()) continue;

        for(size_t j=0; j<l.getData(i)->size(); ++j)
        {
            if(l.getData(i)->getData(j)->solveTested == true) continue;

            int branch = l.getData(i)->getData(j)->solveSize++;

            lines[branch].splice(lines[branch+1].begin(), lines[branch+1], l.getData(i)->getData(j));
        }
    }
}

void PlaneXY::transferTo(list<Line> &tlines, Line &l)
{
    l.solveTested = true;
    lines[l.solveSize].splice(tlines.begin(), tlines ,lines[l.solveSize].begin());
}

void PlaneXY::transferFrom(list<Line> &tlines, Line &l)
{
    l.solveTested = false;
    tlines.splice(lines[l.solveSize].begin(), lines[l.solveSize], tlines.begin());
}

void PlaneXY::transferFrom(list<Line> &tlines)
{
    while(tlines.size() != 0)
    {
        Line &l = *tlines.begin();
        this->transferFrom(tlines, l);
    }
}

}

std::ostream& operator<<(std::ostream& os, const Solution::PlaneXY& obj)
{
    for(size_t i=0; i<obj.lines.size(); ++i)
    os << obj.lines[i].size() << '\t';

    return os;
}

#endif // LINESET_HPP_INCLUDED
