#ifndef INOUT_HPP_INCLUDED
#define INOUT_HPP_INCLUDED

using std::list;
using std::string;

namespace InOut
{

list<Point> readPoints()
{
    double x, y;
    list<Point> ret;

    while(std::cin >> x >> y) ret.push_front(Point(x, y));

    return ret;
}

class InputParser
{
    public:
        std::vector <std::string> tokens;

    public:
        const std::string& getCmdOption(const std::string &option) const
        {
            std::vector<std::string>::const_iterator itr;
            itr = std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }

        bool cmdOptionExists(const std::string &option) const
        {
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }

        InputParser(int &argc, char **argv)
        {
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
};

class CommandParser
{
    private:
        InputParser input;

        class Command
        {
            private:
                string command;
                string help;

            public:
                string getCommand() const
                {
                    return command;
                }

                string getHelp() const
                {
                    return help;
                }

                Command() {}

                Command(string ncommand, string nhelp):
                    command(ncommand), help(nhelp) {}
        };

        Command mode;
        Command generate;

        Command columns;
        Command rows;
        Command indent_left;
        Command indent_right;
        Command nmin;
        Command nmax;

        Command number;
        Command density;

        Command repetitions;
        Command iterations;
        Command step;

        Command lines;
        Command points;
        Command time;

        bool areCmdPresent(std::initializer_list<Command> cmd_list);
        template<class T> T cmdValue(Command c);

        void runSingleInstance(list<Point> points, bool lines_info, bool points_info, bool time_info);
        void runMultipleInstances(double d, int repetitions, int step, int iterations);

    public:
        void executeTask();

        void printHelp(std::initializer_list<Command> help_list)
        {
            for(Command i : help_list) std::cout << i.getCommand() << '\t' << i.getHelp() << '\n';
        }

        void printHelp(Command help)
        {
            printHelp({help});
        }

        CommandParser(int &argc, char **argv): input(argc, argv)
        {
            mode = Command("-m",
                            "Set mode to be run:\n\t1 - get points from standard input\n\t2 - generate points with embedded generator\n\t3 - run complexity experiment");

            generate = Command("-g",
                                string("Set generator mode:")
                               +string("\n\tgrid - generate grid")
                               +string("\n\tsgrid - generate sparse grid")
                               +string("\n\tsparse - generate sparse lines of points")
                               +string("\n\tcomb - generate grid with additional points along y-axis")
                               +string("\n\tdiamond - generate grid with indents in upper-left and lower-right corners"));

            columns = Command("-col", "Sets number of columns");
            rows = Command("-row", "Sets number of rows");

            indent_left = Command("-il", "Sets the size of the upper-left indent");
            indent_right = Command("-ir", "Sets the size of the lower-right indent");

            nmin = Command("-nmin", "Sets the minimum number of points in the line");
            nmax = Command("-nmax", "Sets the maximum number of points in the line");

            number = Command("-n", "Sets the number of points (in the case of 'sparse' - number of lines)");
            density = Command("-d", "Sets density of points in generated set. Accepts floating point within 0 - 1 range.");

            repetitions = Command("-r", "Sets the number of repetitions (how many instances of the problem will be solved)");
            iterations = Command("-i", "Sets the number of iterations (how many times 'increment by step' will be called)");
            step = Command("-step", "Sets the size of a step between iterations (how many points will be added between each iteration)");

            lines = Command("-lines", "Short summary of generated lines will be shown (optional)");
            points = Command("-points", "Short summary of inputed points will be shown (optional)");
            time = Command("-time", "Execution time of each task will be shown (optional)");
        }
};

template<> int CommandParser::cmdValue(Command c)
{
    return std::atoi(input.getCmdOption(c.getCommand()).c_str());
}

template<> double CommandParser::cmdValue(Command c)
{
    return std::atof(input.getCmdOption(c.getCommand()).c_str());
}

template<> bool CommandParser::cmdValue(Command c)
{
    return input.cmdOptionExists( c.getCommand() );
}

template<> std::string CommandParser::cmdValue(Command c)
{
    return input.getCmdOption(c.getCommand());
}

bool CommandParser::areCmdPresent(std::initializer_list<Command> cmd_list)
{
    for(Command cmd : cmd_list)
        if(!input.cmdOptionExists(cmd.getCommand())) return false;

    return true;
}

void CommandParser::runSingleInstance(list<Point> points, bool linegen_info, bool points_info, bool time_info)
{
    std::clock_t start;
    double duration;

    if(time_info) start = std::clock();
    Solution::PlaneXY collection = Solution::generateLines(points);
    if(time_info) duration = ( std::clock() - start );

    if(points_info || linegen_info || time_info) std::cout << '\n';

    if(points_info)
    {
        std::cout << "Points size: " << collection.points.size() << '\n';

        std::ofstream points_file;
        points_file.open("points.txt");

        for(Point p : collection.points)
            points_file << p.X() << '\t' << p.Y() <<'\n';//TBD p.size

        points_file.close();
    }

    if(linegen_info)
    {
        std::cout << "Lines size: " << '\n';
        for(size_t i=0; i<collection.lines.size(); ++i) std::cout << i << '\t';
        std::cout << '\n';

        std::cout << collection << '\n';
    }

    if(time_info) std::cout << "Execution time: " << duration << '\n';

    std::cout << '\n';

    if(time_info) start = std::clock();
    int solution = Solution::findMinCover(collection);
    if(time_info) duration = ( std::clock() - start );

    std::cout << "MinCover: " << solution << '\n';
    if(time_info) std::cout << "Execution time: " << duration << '\n';

    std::cout << '\n';

    if(time_info) start = std::clock();
    int unique_counter = Solution::countUniqueSolutions(collection, solution);
    if(time_info) duration = ( std::clock() - start );

    std::cout << "UniqueSolutions: " << unique_counter << " (" << Solution::countSolutionCombinations(solution, unique_counter) << ")" << '\n';
    if(time_info) std::cout << "Execution time: " << duration << '\n';
}

namespace Experiment
{
    template<class T>
    vector<T> concludeResults(const vector<vector<T>>& results, int repetitions, int iterations)
    {
        vector<T> ret;

        for(int i=0;i<iterations;++i)
        {
            int value = 0;

            for(int j=0;j<repetitions;++j) value += results[j][i];
            value /= repetitions;

            ret.push_back(value);
        }

        return ret;
    }

};

void CommandParser::runMultipleInstances(double d, int repetitions, int step, int iterations)
{
    list<Point> points;

    vector< vector<int> > line_gen(repetitions, vector<int>());
    vector< vector<int> > min_cover(repetitions, vector<int>());
    vector< vector<int> > unique_solutions(repetitions, vector<int>());

    vector< vector<size_t> > lines_number(repetitions, vector<size_t>());
    vector< vector<int> > k_solution(repetitions, vector<int>());


    std::clock_t start;
    double duration;

    for(int j=0;j<repetitions;++j)
    {
        Generator::SpiralSparseGrid test_grid(d);

        for(int i=0;i<iterations;++i)
        {
            test_grid.increment(step);
            points = test_grid.getGrid();

            start = std::clock();
            PlaneXY plane = Solution::generateLines(points);
            duration = ( std::clock() - start );
//beep boop bob
            std::cout << duration << '\t';
            line_gen[j].push_back(duration);

            lines_number[j].push_back(plane.countLines());

            start = std::clock();
            int solution = Solution::findMinCover(plane);
            duration = ( std::clock() - start );

            std::cout << duration << '\t';
            std::cout << solution << '\t';
            min_cover[j].push_back(duration);
            k_solution[j].push_back(solution);

            start = std::clock();
            int unique_counter = Solution::countUniqueSolutions(plane, solution);
            duration = ( std::clock() - start );

            std::cout << duration << '\t';
            std::cout << unique_counter << '\t' << '\n';
            unique_solutions[j].push_back(duration);
        }

        std::cout << '\n';
    }

    std::cout << '\n' << "LinesNumber: " << '\t';
    vector<size_t> results_line = Experiment::concludeResults<size_t>(lines_number, repetitions, iterations);
    for(size_t r : results_line) std::cout << r << '\t';

    std::cout << '\n' << '\n' << "LineGen: " << '\t';
    vector<int> results_gen = Experiment::concludeResults<int>(line_gen, repetitions, iterations);
    for(size_t r : results_gen) std::cout << r << '\t';

    std::cout << '\n' << "LineGen model: " << '\t';
    for(int i=0;i<iterations;++i) std::cout << (int) m1Complexity(step*(i+1), 0.000011) << '\t';


    std::cout << '\n' << '\n' << "Solutions: " << '\t';
    vector<int> results_solution = Experiment::concludeResults<int>(k_solution, repetitions, iterations);
    for(size_t r : results_solution) std::cout << r << '\t';

    std::cout << '\n' << '\n' << "MinCover: " << '\t';
    vector<int> results_cover = Experiment::concludeResults<int>(min_cover, repetitions, iterations);
    for(size_t r : results_cover) std::cout << r << '\t';

    double normal_mc = std::pow(1.8, (double)results_solution[1 + results_solution.size()/2]) / results_cover[1 + results_solution.size()/2];
    std::cout << '\n' << "MinCov model: " << '\t';
    for(int i=0;i<iterations;++i) std::cout << (int)(std::pow(1.8, (double)results_solution[i]) / normal_mc) << '\t';

    std::cout << '\n' << '\n' << "Unique: " << '\t';
    vector<int> results_unique = Experiment::concludeResults<int>(unique_solutions, repetitions, iterations);
    for(size_t r : results_unique) std::cout << r << '\t';

    double normal_us = std::pow(1.8, (double)results_solution[1 + results_solution.size()/2]) / results_unique[1 + results_solution.size()/2];
    std::cout << '\n' << "UnqSol model: " << '\t';
    for(int i=0;i<iterations;++i) std::cout << (int)(std::pow(1.8, (double)results_solution[i]) / normal_us) << '\t';
}

void CommandParser::executeTask()
{
    if(cmdValue<int>(mode) == 1 || cmdValue<int>(mode) == 2)
    {
        list<Point> points_list;

        if(cmdValue<int>(mode) == 1) points_list = readPoints();
        else
        {
            if(cmdValue<std::string>(generate) == "grid")
            {
                if(!areCmdPresent({columns, rows}))
                {
                    printHelp({columns, rows});
                    return;
                }

                points_list = Generator::generateGrid(cmdValue<int>(columns), cmdValue<int>(rows));
            }
            else if(cmdValue<std::string>(generate) == "sparse")
            {
                if(!areCmdPresent({nmax, nmin, number}))
                {
                    printHelp({nmax, nmin, number});
                    return;
                }

                points_list = Generator::generateSparse(cmdValue<int>(nmin), cmdValue<int>(nmax), cmdValue<int>(number));
            }
            else if(cmdValue<std::string>(generate) == "sgrid")
            {
                if(!areCmdPresent({columns, rows}) || (!areCmdPresent({number}) && !areCmdPresent({density})) )
                {
                    printHelp({columns, rows, number, density});
                    return;
                }

                if(areCmdPresent({number}))
                    points_list = Generator::generateSparseGrid(cmdValue<int>(columns), cmdValue<int>(rows), cmdValue<int>(number));

                if(areCmdPresent({density}))
                    points_list = Generator::generateSparseGrid(cmdValue<int>(columns), cmdValue<int>(rows), cmdValue<double>(density));
            }
            else if(cmdValue<std::string>(generate) == "comb")
            {
                if(!areCmdPresent({columns, rows}))
                {
                    printHelp({columns, rows});
                    return;
                }

                points_list = Generator::generateComb(cmdValue<int>(columns), cmdValue<int>(rows));
            }
            else if(cmdValue<std::string>(generate) == "diamond")
            {
                if(!areCmdPresent({columns, rows, indent_left, indent_right}))
                {
                    printHelp({columns, rows, indent_left, indent_right});
                    return;
                }

                points_list = Generator::generateDiamond(cmdValue<int>(columns), cmdValue<int>(rows), cmdValue<int>(indent_left), cmdValue<int>(indent_right));
            }
            else
            {
                printHelp({generate});
                return;
            }
        }

        this->runSingleInstance(points_list, cmdValue<bool>(lines), cmdValue<bool>(points), cmdValue<bool>(time));
    }

    else if(cmdValue<int>(mode) == 3)
    {
        if(!areCmdPresent({density, repetitions, iterations, step}))
        {
            printHelp({density, repetitions, iterations, step});
            return;
        }

        this->runMultipleInstances(cmdValue<double>(density), cmdValue<int>(repetitions), cmdValue<int>(step), cmdValue<int>(iterations));
    }

    else printHelp({mode, lines, points, time});
}
};


#endif // INOUT_HPP_INCLUDED
