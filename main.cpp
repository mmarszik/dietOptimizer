#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <cassert>

//constexpr static int PRICE_COLUMN = 0;

using TSuperRnd = std::ranlux48;
using TRnd = std::mt19937_64;

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

class Weights {
private:
    double tooLittle;
    double tooMany;

public:

};

class Diet {
private:
    double eval;
    std::vector<double> foodsAmount;
    std::vector<double> ingredientsSum;
    std::vector<double> partalsEvals;


private:

    void makeIngredientsSum(
        const std::vector<FoodProduct>& foodsTable
    ) {
        assert( foodsAmount.size() == foodsTable.size() );
        for( size_t i=0 ; i<ingredientsSum.size() ; i++ ) {
            ingredientsSum[i] = 0;
            for( const auto &food : foodsTable ) {
                ingredientsSum[i] += food.getIngredient(i) * foodsAmount[i];
            }
        }
    }

    void makePartailEvals() {

    }

    void fullEvaluate(
        const std::vector<double>& requirements,
        const std::vector<Weights>& weights
    ) {

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
        const std::vector<Weights>& weights
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

