#include "CIndividual.h"
#include <algorithm>
#include <limits>

using namespace NGroupingChallenge;
using namespace std;

CIndividual::CIndividual() : d_fitness(d_BEFORE_CALCULATIONS)
{

}

CIndividual::CIndividual(int iGenotypeSize, int iMinGeneValue, int iMaxGeneValue, mt19937& cRandomEngine) : d_fitness(d_BEFORE_CALCULATIONS)
{
    uniform_int_distribution<int> c_distribution(iMinGeneValue, iMaxGeneValue);

    v_genotype.resize(iGenotypeSize);

    for (int i = 0; i < iGenotypeSize; i++)
    {
        v_genotype[i] = c_distribution(cRandomEngine);
    }
}

CIndividual::CIndividual(const vector<int>& vGenotype) : v_genotype(vGenotype), d_fitness(d_BEFORE_CALCULATIONS)
{

}

double CIndividual::dCalculateFitness(CGroupingEvaluator& cEvaluator)
{
    d_fitness = cEvaluator.dEvaluate(v_genotype);

    return d_fitness;
}

pair<CIndividual, CIndividual> CIndividual::cCrossover(const CIndividual& cOther, double dCrossProb, mt19937& cRandomEngine) const
{
    uniform_real_distribution<double> c_real_dist(d_REAL_DIST_LOWER, d_REAL_DIST_UPPER);

    double d_rand = c_real_dist(cRandomEngine);
    if (d_rand >= dCrossProb)
    {
        return pair<CIndividual, CIndividual>(*this, cOther);
    }

    int i_size = v_genotype.size();

    uniform_int_distribution<int> c_int_dist(i_INT_DIST_LOWER, i_size - i_INT_DIST_LOWER);
    int i_where_cut = c_int_dist(cRandomEngine);

    vector<int> v_child1;
    vector<int> v_child2;

    v_child1.reserve(i_size);
    v_child2.reserve(i_size);

    for (int i = 0; i < i_where_cut; i++)
    {
        v_child1.push_back(v_genotype[i]);
    }
    for (int i = i_where_cut; i < i_size; i++)
    {
        v_child1.push_back(cOther.v_genotype[i]);
    }

    for (int i = 0; i < i_where_cut; i++)
    {
        v_child2.push_back(cOther.v_genotype[i]);
    }
    for (int i = i_where_cut; i < i_size; i++)
    {
        v_child2.push_back(v_genotype[i]);
    }

    return pair<CIndividual, CIndividual>(CIndividual(v_child1), CIndividual(v_child2));
}

void CIndividual::vMutate(double dMutProb, int iMinGeneValue, int iMaxGeneValue, mt19937& cRandomEngine)
{
    uniform_real_distribution<double> c_real_dist(d_REAL_DIST_LOWER, d_REAL_DIST_UPPER);
    uniform_int_distribution<int> c_int_dist(iMinGeneValue, iMaxGeneValue);

    for (size_t i = 0; i < v_genotype.size(); i++)
    {
        double d_rand = c_real_dist(cRandomEngine);

        if (d_rand < dMutProb)
        {
            v_genotype[i] = c_int_dist(cRandomEngine);
        }
    }
}
