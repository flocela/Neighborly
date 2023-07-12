#ifndef RUNMETRICS_H
#define RUNMETRICS_H

#include <unordered_map>
#include <unordered_set>

#include "City.h"
#include "House.h"
#include "Resident.h"

class RunMetrics
{

public: 

    RunMetrics (
        const std::unordered_map<const House*, std::unordered_set<const House*>>& adjacentHousesPerHouse,
        int seedNumber,
        std::string simulatorName
    );
    RunMetrics () = delete;
    RunMetrics (const RunMetrics& o) = default;
    RunMetrics (RunMetrics&& o) noexcept = default;
    RunMetrics& operator= (const RunMetrics& o) = default;
    RunMetrics& operator= (RunMetrics&& o) noexcept = default;
    ~RunMetrics () noexcept = default;

    void setSeedNumber (int seedNumber);

    int getSeedNumber () const;

    std::unordered_map<const House*, const Resident*> getResidentsPerHouse() const;
    
    std::unordered_map<int, int> getNumOfResidentsPerGroupId () const;

    // returns sum of each resident's disparate neighbors. Note,
    // total number of disparate neighobrs for a group may be less than
    // returned value because two members of the group may both be counting
    // the same disparate neighbor.
    std::unordered_map<int, int> getNumOfDiffNeighborsPerGroupId () const;

    // returns the sum of each resident's happiness
    std::unordered_map<int, double> getHappinessSumPerGroupId() const;
    
    std::unordered_map<int, const Resident*> getResidentExamplePerGroupId() const;

    int getRunNumber () const;

    std::string getSimulator () const;

    void updateMetrics(
        int run,
        std::unordered_map<const House*, const Resident*> residentsPerHouse
    );

private:

    int _run_num = -1;
    const std::unordered_map<const House*, std::unordered_set<const House*>>& _adj_houses;
    int _seed_number = 0;
    std::string _simulator_name = "";
    

    std::unordered_map<const House*, const Resident*> _residents_per_house{};
    std::unordered_map<int, int> _num_of_residents_per_group_id{};
    std::unordered_map<int, int> _num_of_diff_neighbors_per_group_id{};
    std::unordered_map<int, double> _happiness_sum_per_group_id{};
    std::unordered_map<int, const Resident*> _resident_example_per_group_id{};
    
};

#endif
