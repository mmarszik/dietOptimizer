#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <cassert>

//constexpr static int PRICE_COLUMN = 0;

using TSuperRnd = std::ranlux48;
using TRnd = std::mt19937_64;

//one product of food (100g), e.g. cheese, meat, beans, etc
class FoodProduct {
private:
    std::string name;
    std::vector<double> ingredients;

public:
    const std::string& getName() const {
        return name;
    }
    const std::vector<double>& getInredients() const {
        return ingredients;
    }
    double getIngredient(const size_t i) const {
        return ingredients[i];
    }
    size_t getSize() const {
        return  ingredients.size();
    }
};

//The wrapper for minimal and maximal amout of food
class Constraint {
private:
    double min;
    double max;

public:

    double getMin() const {
        return min;
    }

    double getMax() const {
        return max;
    }
};

//The penal for overflow and deficency of one ingedient
class Penal {
private:
    double deficency;
    double overflow;

public:
    double getDeficency() const { return deficency; }
    double getOverflow() const { return overflow; }
};

//The whole daily diet, in other words amount of each food product
class Diet {
private:
    double eval;                               //the evaluate of current diet (the lower value is better)
    std::vector<double> foodsAmount;           //the number of food products, units is [100g]
    std::vector<double> ingredientsSum;        //optimizing reasons: current sum of ingredients (proteins, fats, carbohydrates, but also prices, etc)
    std::vector<double> partalsEvals;          //optimizing reasons: partail evaluate for each in ingredient


private:

    static void makeFullIngredientsSum(
        const std::vector<FoodProduct>& foodsTable,
        const std::vector<double> &foodsAmount,
        std::vector<double> &ingredientsSum
    ) {
        assert( foodsAmount.size() == foodsTable.size() );
        assert( foodsTable.size() > 0 );
        assert( foodsTable[0].getSize() == ingredientsSum.size() );
        for( size_t i=0 ; i<ingredientsSum.size() ; i++ ) {
            ingredientsSum[i] = 0;
            for( const auto &food : foodsTable ) {
                ingredientsSum[i] += food.getIngredient(i) * foodsAmount[i];
            }
        }
    }

    static void makeFullPartailEvals(
        const std::vector<double>& requirements,
        const std::vector<double>& ingredientsSum,
        std::vector<double>& partalsEvals
    ) {
        assert( requirements.size() == ingredientsSum.size() );
        assert( requirements.size() == partalsEvals.size() );
        for( size_t i=0 ; i<requirements.size() ; i++ ) {
            partalsEvals[i] = requirements[i] - ingredientsSum[i];
        }
    }

    static double fullEvaluate(
        std::vector<double>& partalsEvals,
        const std::vector<Penal>& penals
    ) {
        assert( partalsEvals.size() == penals.size() );
        double eval = 0;
        for( size_t i=0 ; i<partalsEvals.size() ; i++ ) {
            const double tmp = partalsEvals[i];
            const double penal =  partalsEvals[i] <= 0 ?  penals[i].getDeficency() : penals[i].getOverflow();
            eval += tmp * tmp * penal;
        }
        return eval;
    }


public:

    void init(
        TSuperRnd &rnd,
        const std::vector<Constraint>& constraint,
        const std::vector<FoodProduct>& foodsTable
    ) {
        assert( foodsTable.size() > 0 );
        assert( constraint.size() == foodsTable.size() );

        foodsAmount.resize( foodsTable.size() );
        ingredientsSum.resize( foodsTable[0].getSize() );
        partalsEvals.resize( foodsTable[0].getSize() );

        for( size_t i=0 ; i<foodsAmount.size() ; i++ ) {
            std::uniform_real_distribution d( constraint[i].getMin(),constraint[i].getMax());
            foodsAmount[i] = d(rnd);
        }
        makeIngredientsSum( foodsTable );
    }

    void chaos(
        const std::vector<Constraint>& constraint
    ) {

    }

    void evaluate(
        const std::vector<double>& requirements,
        const std::vector<Penal>& weights
    ) {

        for( size_t i=0 ; i<requirements.size() ; i++ ) {

        }
    }
};


class TheSpecimen {
private:
    Diet diet;
    Diet best;
};



int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

