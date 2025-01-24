#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "CGeneticAlgorithm.h"
#include <random>
#include <chrono>
#include <iostream>

using namespace NGroupingChallenge;
using namespace std;
using namespace std::chrono;

int main()
{
    CGaussianGroupingEvaluatorFactory c_evaluator_factory(5, 100, 5);

    for (int i = 0; i < 10; i++)
    {
        c_evaluator_factory.cAddDimension(-100, 100, 1.0, 1.0);
    }

    CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);

    random_device c_seed_gen;
    mt19937 c_random_engine(c_seed_gen());

    CGeneticAlgorithm c_ga(20, 0.6, 0.1, *pc_evaluator);

    //c_ga.vSetTimeLimit(800);

    c_ga.vInitialize(c_random_engine);

    bool b_is_running = true;
    double d_previous_best_fitness = numeric_limits<double>::max();
    int i_gen_count = 0;
    steady_clock::time_point tp_start = steady_clock::now();
    while (b_is_running)
    {
        c_ga.vRunIteration(c_random_engine);
        i_gen_count++;
        double d_current_best_fitness = c_ga.dGetBestFitness();

        if (d_current_best_fitness < d_previous_best_fitness)
        {
            cout << "Found better fitness: " << d_current_best_fitness << " - at generation: " << i_gen_count << endl;
            d_previous_best_fitness = d_current_best_fitness;
        }

        steady_clock::time_point tp_now = steady_clock::now();
        double d_elapsed_sec = duration<double>(tp_now - tp_start).count();

        if (d_elapsed_sec >= c_ga.dGetTimeLimit())
        {
            b_is_running = false;
            cout << "Time limit achieved: " << c_ga.dGetTimeLimit() << " seconds" << endl;
        }
    }

    cout << "Best fitness found: " << c_ga.dGetBestFitness() << endl;

    const CIndividual& c_best = c_ga.cGetBestIndividual();
    const vector<int>& v_best_gen = c_best.vGetGenotype();

    cout << "Gene of the best specie: ";
    for (size_t i = 0; i < v_best_gen.size(); i++)
    {
        cout << v_best_gen[i];
    }
    cout << endl;

    delete pc_evaluator;

    return 0;
}
