#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

#define POP_SIZE 5
#define GENE_SIZE 20
#define BUDGET 40000

//constants
const int ITEMS[GENE_SIZE] = {
    1500, 5000, 20000, 5000, 4500,
    4000, 3700, 1200, 1200, 2000,
    1200, 500, 5000, 1800, 1000,
    900, 350, 2000, 1200, 1500
};

int chromosome[POP_SIZE][GENE_SIZE];
double fitness[POP_SIZE];

void printChromosome() {
    for (int i=0; i<POP_SIZE; i++) {
        cout << "Chromosome " << i+1 << ": ";
        for (int j=0; j<GENE_SIZE; j++) {
            cout << chromosome[i][j] << " ";
        }
        cout << endl;
    }
}

void initializeChromosome() {
    for (int i=0; i<POP_SIZE; i++) {
        for (int j=0; j<GENE_SIZE; j++) {
            chromosome[i][j] = rand() % 2;
        }
    }
}

// goal 1 - maximize number of items (number of 1s in the gene pool)
// goal 2 - total price should be as closed as budget
void evaluateChromosome() {
    for (int i = 0; i < POP_SIZE; i++) {
        int accPrice = 0, nItems = 0, totalPriority = 0;
        for (int j = 0; j < GENE_SIZE; j++) {
            if (chromosome[i][j] == 1) {
                nItems++;
                accPrice += ITEMS[j];
                totalPriority += (GENE_SIZE - j);
            }
        }

        fitness[i] = 1.0 / (abs(BUDGET - accPrice) + nItems + totalPriority);

        cout << "Price: RM " << accPrice << " Fitness: " << fitness[i] << endl;
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    srand ( unsigned ( time(0) ) ); // enable randomness in our program
    initializeChromosome();
    // printChromosome();
    evaluateChromosome();
    return 0;
}
