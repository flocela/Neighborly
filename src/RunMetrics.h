#ifndef RUNMETRICS_H
#define RUNMETRICS_H

#include <unordered_map>
#include <unordered_set>

#include "City.h"
#include "House.h"
#include "Resident.h"
#include "ResPerHouse.h"
#include "SetOfHousesPerHouse.h"

// Contains output data from a simulation run.
class RunMetrics
{

public: 

    RunMetrics (const SetOfHousesPerHouse& adjacentHousesPerHouse);
    RunMetrics () = delete;
    RunMetrics (const RunMetrics& o) = default;
    RunMetrics (RunMetrics&& o) noexcept = default;
    RunMetrics& operator= (const RunMetrics& o) = default;
    RunMetrics& operator= (RunMetrics&& o) noexcept = default;
    ~RunMetrics () noexcept = default;

    const ResPerHouse& getResidentsPerHouse() const;
    
    const std::unordered_map<int, int>& getNumOfResidentsPerGroupId () const;

    // Returns the sum of each resident's disparate neighbors per group. Found
    // by creating a total sum for each group. The sum of each resident's 
    // disparate neighbors is taken and added to the total sum for the group.
    // Note disparate neighbors may be counted twice. If neighbors A and B
    // are of group 1, and they both share neighbor C of group 2. Then neighbor
    // C will be added to the sum of group 1's diparate neighbors twice.
    const std::unordered_map<int, int>& getNumOfDiffNeighborsPerGroupId () const;

    // Returns the sum of each resident's happiness per group.
    const std::unordered_map<int, double>& getHappinessSumPerGroupId() const;

    int getRunNumber () const;

    void updateMetrics(
        int run,
        const ResPerHouse residentsPerHouse
    );

private:

    const SetOfHousesPerHouse& _adj_houses;

    int _run_num = -1;
    ResPerHouse _residents_per_house{};
    std::unordered_map<int, int> _num_of_residents_per_group_id{};
    std::unordered_map<int, int> _num_of_diff_neighbors_per_group_id{};
    std::unordered_map<int, double> _happiness_sum_per_group_id{};
    
};

#endif
