#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

#include "GroupingEvaluator.h"
#include <vector>
#include <random>
#include <utility>

using namespace std;

namespace NGroupingChallenge
{
    class CIndividual
    {
    public:
        CIndividual();

        CIndividual(int iGenotypeSize,
            int iMinGeneValue,
            int iMaxGeneValue,
            mt19937& cRandomEngine);

        CIndividual(const vector<int>& vGenotype);

        const vector<int>& vGetGenotype() const { return v_genotype; }

        double dCalculateFitness(CGroupingEvaluator& cEvaluator);
        double dGetFitness() const { return d_fitness; }

        pair<CIndividual, CIndividual> cCrossover(const CIndividual& cOther,
            double dCrossProb,
            mt19937& cRandomEngine) const;

        void vMutate(double dMutProb,
            int iMinGeneValue,
            int iMaxGeneValue,
            mt19937& cRandomEngine);

    private:
        vector<int> v_genotype;

        double d_fitness;
        double d_BEFORE_CALCULATIONS = 0.0;
        double d_REAL_DIST_LOWER = 0.0;
        double d_REAL_DIST_UPPER = 1.0;

        int i_INT_DIST_LOWER = 1;
    };
}

#endif
