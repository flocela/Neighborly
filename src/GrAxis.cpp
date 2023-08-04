#include "GrAxis.h"

using namespace std;
GrAxis::GrAxis (unique_ptr<Axis> axis): _axis{move(axis)}
{}