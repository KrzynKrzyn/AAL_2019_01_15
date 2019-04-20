#ifndef GENERATOR_HPP_INCLUDED
#define GENERATOR_HPP_INCLUDED

namespace Generator
{
    //static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(time(NULL)); //Standard mersenne_twister_engine seeded with rd()

    list<Point> generateGrid(int col, int row)
    {
        list<Point> ret;

        for(int i=0;i<col;i++)for(int j=0;j<row;j++)
        ret.push_back(Point(i,j));

        return ret;
    }

    list<Point> generateLine(Point p1, Point p2, int n)
    {
        list<Point> ret;

        double x_step = (p2.X() - p1.X()) / n;
        double y_step = (p2.Y() - p1.Y()) / n;

        for(int i=0; i<n; ++i) ret.push_back(Point(p1.X() + x_step*i, p1.Y() + y_step*i));

        return ret;
    }

    list<Point> generateSparse(size_t min_n, size_t max_n, size_t lines_no)
    {
        std::uniform_int_distribution<> lines_xy(-65536/8, 65536/8);
        std::uniform_int_distribution<> no_points(std::min(min_n, max_n), std::max(min_n, max_n));

        list<Point> ret, temp;

        for(size_t i=0; i<lines_no; ++i)
        {
            temp = generateLine( Point(lines_xy(gen), lines_xy(gen)), Point(lines_xy(gen), lines_xy(gen)), no_points(gen));
            ret.splice(ret.begin(), temp);
        }

        return ret;
    }

    list<Point> generateSparseGrid(int col, int row, int n)
    {
        if(n > col*row) n = col*row;

        std::uniform_int_distribution<> rand_n;
        vector<bool> grid(col * row, true);
        list<Point> ret;

        for(int i=0;i<n;i++)
        {
            rand_n = std::uniform_int_distribution<>(0, col*row-1-i);
            int new_coord = rand_n(gen);
            int j = 0;

            while(true)
            {
                if(grid[j] == true)
                {
                    --new_coord;
                    if(new_coord < 0) break;
                }
                ++j;
            }

            ret.push_back(Point(j/row, j%row));
            grid[j] = false;
        }

        return ret;
    }

    list<Point> generateSparseGrid(int col, int row, double density)
    {
        return generateSparseGrid(col, row, static_cast<int>(col*row*density));
    }

    list<Point> generateComb(int col, int row)
    {
        list<Point> ret = generateGrid(col, row);
        std::uniform_int_distribution<> dis(-65536/8, 65536/8);

        for(int i=0;i<col;i++)
        {
            ret.push_back(Point(i,dis(gen)));
            //ret.push_back(Point(i,dis(gen)));
        }

        return ret;
    }

    list<Point> generateStaircase(int stair_length, int stair_height, int offset, int stair_n)
    {
        list<Point> ret;

        for(int k=0; k<stair_n; ++k)
        for(int i=0; i<stair_length; ++i)
        for(int j=0; j<stair_height; ++j)
            ret.push_back( Point(i + k*offset, j + k*stair_height) );

        return ret;
    }

    list<Point> generateDiamond(int col, int row, int indent_up_left, int indent_down_right)
    {
        list<Point> ret;

        indent_down_right = col+row - indent_down_right - 2;

        for(int i=0;i<col;i++)for(int j=0;j<row;j++)
        {
            if(i+j < indent_up_left)
                continue;

            if(i+j > indent_down_right)
                continue;

            ret.push_back(Point(i,j));
        }

        return ret;
    }

    class DensifyableSparseGrid
    {
        private:
            int col;
            int row;

            list<Point> points;
            vector<bool> available;

        public:
            list<Point> getGrid() const
            {
                return points;
            }

            void incrementDensity(int n)
            {
                if(points.size()+n > col*row) n = col*row - points.size();

                std::uniform_int_distribution<> rand_n;

                for(int i=0;i<n;i++)
                {
                    rand_n = std::uniform_int_distribution<>(0, col*row-1-points.size());
                    int new_coord = rand_n(gen);
                    int j = 0;

                    while(true)
                    {
                        if(available[j] == true)
                        {
                            --new_coord;
                            if(new_coord < 0) break;
                        }
                        ++j;
                    }

                    points.push_back(Point(j/row, j%row));
                    available[j] = false;
                }
            }

            DensifyableSparseGrid(int columns, int rows):
                col(columns),
                row(rows),
                points(generateSparseGrid(col, row, 0)),
                available(col * row, true) {}
    };

    class SpiralSparseGrid
    {
        private:
            std::bernoulli_distribution rand_bool;

            list<Point> points;
            Point last;

            int nx;
            int ny;

        public:
            list<Point> getGrid() const
            {
                return points;
            }

            int getLayer()
            {
                return std::max(std::abs(last.X()), std::abs(last.Y()));
            }

            void increment()
            {
                while(true)
                {
                    if((std::abs(last.X()) == this->getLayer() && nx != 0) ||
                       (std::abs(last.Y()) == this->getLayer() && ny != 0))
                    {
                        if(nx != 0)
                        {
                            ny = -nx;
                            nx = 0;
                        }
                        else if(ny != 0 && (std::abs(last.X()) != std::abs(last.Y()) || ny < 0))
                        {
                            nx = ny;
                            ny = 0;
                        }
                    }

                    last = Point(last.X()+nx, last.Y()+ny);
                    if(rand_bool(gen)) break;
                }

                points.push_back(last);
            }

            void increment(int n)
            {
                for(int i=0; i<n; ++i) this->increment();
            }

            SpiralSparseGrid(double chance):
                rand_bool(std::bernoulli_distribution(chance)),
                last(Point(0,0)),
                nx(0),
                ny(1)
                {}
    };
};

#endif // GENERATOR_HPP_INCLUDED
