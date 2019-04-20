#ifndef INFORMED_HPP_INCLUDED
#define INFORMED_HPP_INCLUDED

using std::vector;

template<class T>
class Informed
{
    private:
        vector<T> container;

    public:
        void insertData(T p) { container.push_back(p); }
        T& getData(int index) { return container[index]; }
        size_t size() const { return container.size(); }
};

#endif // INFORMED_HPP_INCLUDED
