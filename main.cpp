#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <unordered_set>

#include <iomanip>//TBD

#include <functional>

#include <string>

#include <cmath>

#include <algorithm>

#include <cstdio>
#include <ctime>

#include <random>

#include <fstream>

#include "informed.hpp"
#include "point.hpp"
#include "line.hpp"
#include "lineset.hpp"
#include "solveset.hpp"
#include "generator.hpp"
#include "inout.hpp"

using namespace std;

int main(int argc, char** argv)
{
    InOut::CommandParser commands(argc, argv);

    commands.executeTask();

    return 0;
}

