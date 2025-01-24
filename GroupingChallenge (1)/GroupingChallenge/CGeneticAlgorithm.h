#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include "CIndividual.h"
#include "GroupingEvaluator.h"
#include <vector>
#include <random>

using namespace std;

namespace NGroupingChallenge
{
    class CGeneticAlgorithm
    {
    public:
        CGeneticAlgorithm(int iPopSize,
            double dCrossProb,
            double dMutProb,
            CGroupingEvaluator& cEvaluator);

        void vSetTimeLimit(double dTimeLimitSeconds);
        void vInitialize(mt19937& cRandomEngine);
        void vRunIteration(mt19937& cRandomEngine);

        const CIndividual& cGetBestIndividual() const { return c_best_individual; }

        double dGetBestFitness() const { return d_best_fitness; }
        double dGetTimeLimit() const;

    private:
        int iSelectBetweenTwoSpecies(const vector<CIndividual>& vPopulation,
            mt19937& cRandomEngine);

        int i_pop_size;
        int i_INT_DIST_LOWER = 0;
        int i_INT_DIST_SUBSTR = 1;

        double d_cross_prob;
        double d_mut_prob;
        double d_time_limit_seconds;
        double d_best_fitness;
        double d_DEFAULT_TIME = 30.0;

        CGroupingEvaluator& c_evaluator;

        vector<CIndividual> v_population;

        CIndividual c_best_individual;
    };
}

#endif
