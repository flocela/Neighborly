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

    RunMetrics (const City* city);
    RunMetrics () = delete;
    RunMetrics (const RunMetrics& o) = default;
    RunMetrics (RunMetrics&& o) noexcept = default;
    RunMetrics& operator= (const RunMetrics& o) = default;
    RunMetrics& operator= (RunMetrics&& o) noexcept = default;
    ~RunMetrics () = default;

    std::unordered_map<const House*, const Resident*> getResidentsPerHouse() const;
    std::unordered_map<int, int> getNumOfResidentsPerGroupId () const;
    std::unordered_map<int, int> getNumOfDiffNeighborsPerGroupId () const;
    std::unordered_map<int, double> getHappinessSumPerGroupId() const;
    std::unordered_map<int, const Resident*> getResidentExamplePerGroupId() const;

    void updateMetrics(
        int run,
        std::unordered_map<const House*, const Resident*> residentsPerHouse
    );

private:

    const City* _city;
    std::unordered_map<const House*, std::unordered_set<const House*>> _adj_houses;

    std::unordered_map<const House*, const Resident*> _residents_per_house{};
    std::unordered_map<int, int> _num_of_residents_per_group_id{};
    std::unordered_map<int, int> _num_of_diff_neighbors_per_group_id{};
    std::unordered_map<int, double> _happiness_sum_per_group_id{};
    std::unordered_map<int, const Resident*> _resident_example_per_group_id{};
    
};

#endif
