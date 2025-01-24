#include "CGeneticAlgorithm.h"
#include <limits>

using namespace NGroupingChallenge;
using namespace std;

CGeneticAlgorithm::CGeneticAlgorithm(int iPopSize, double dCrossProb, double dMutProb, CGroupingEvaluator& cEvaluator)
    : i_pop_size(iPopSize), d_cross_prob(dCrossProb), d_mut_prob(dMutProb), d_time_limit_seconds(d_DEFAULT_TIME), c_evaluator(cEvaluator), d_best_fitness(numeric_limits<double>::max())
{
    d_time_limit_seconds = d_DEFAULT_TIME;
}

void CGeneticAlgorithm::vSetTimeLimit(double dTimeLimitSeconds)
{
    d_time_limit_seconds = dTimeLimitSeconds;
}

double CGeneticAlgorithm::dGetTimeLimit() const
{
    return d_time_limit_seconds;
}

void CGeneticAlgorithm::vInitialize(mt19937& cRandomEngine)
{
    v_population.clear();
    v_population.reserve(i_pop_size);

    int i_min_value = c_evaluator.iGetLowerBound();
    int i_max_value = c_evaluator.iGetUpperBound();
    int i_genotype_size = c_evaluator.iGetNumberOfPoints();

    for (int i = 0; i < i_pop_size; i++)
    {
        CIndividual c_ind(i_genotype_size, i_min_value, i_max_value, cRandomEngine);
        double d_fit = c_ind.dCalculateFitness(c_evaluator);

        if (d_fit < d_best_fitness)
        {
            d_best_fitness = d_fit;
            c_best_individual = c_ind;
        }

        v_population.push_back(c_ind);
    }
}

void CGeneticAlgorithm::vRunIteration(mt19937& cRandomEngine)
{
    vector<CIndividual> v_new_population;
    v_new_population.reserve(i_pop_size);

    while (v_new_population.size() < i_pop_size)
    {
        int i_parent1_index = iSelectBetweenTwoSpecies(v_population, cRandomEngine);
        int i_parent2_index = iSelectBetweenTwoSpecies(v_population, cRandomEngine);

        CIndividual& c_parent1 = v_population[i_parent1_index];
        CIndividual& c_parent2 = v_population[i_parent2_index];

        pair<CIndividual, CIndividual> c_children =
            c_parent1.cCrossover(c_parent2, d_cross_prob, cRandomEngine);

        v_new_population.push_back(c_children.first);
        if (v_new_population.size() < i_pop_size)
        {
            v_new_population.push_back(c_children.second);
        }
    }

    int i_min_value = c_evaluator.iGetLowerBound();
    int i_max_value = c_evaluator.iGetUpperBound();

    for (size_t i = 0; i < v_new_population.size(); i++)
    {
        v_new_population[i].vMutate(d_mut_prob, i_min_value, i_max_value, cRandomEngine);
    }

    for (size_t i = 0; i < v_new_population.size(); i++)
    {
        double d_fit = v_new_population[i].dCalculateFitness(c_evaluator);

        if (d_fit < d_best_fitness)
        {
            d_best_fitness = d_fit;
            c_best_individual = v_new_population[i];
        }
    }

    v_population = v_new_population;
}

int CGeneticAlgorithm::iSelectBetweenTwoSpecies(const vector<CIndividual>& vPopulation, mt19937& cRandomEngine)
{
    uniform_int_distribution<int> c_distribution(i_INT_DIST_LOWER, vPopulation.size() - i_INT_DIST_SUBSTR);

    int i_index1 = c_distribution(cRandomEngine);
    int i_index2 = c_distribution(cRandomEngine);

    double d_fit1 = vPopulation[i_index1].dGetFitness();
    double d_fit2 = vPopulation[i_index2].dGetFitness();

    if (d_fit1 < d_fit2)
    {
        return i_index1;
    }
    else
    {
        return i_index2;
    }
}
