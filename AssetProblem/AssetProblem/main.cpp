#include <ctime>
#include <math.h>
#include <cstdlib>
#include <iostream>
using namespace std;

#define POP_SIZE 10
#define GENE_SIZE 20
#define PARENT_SIZE 2
#define BUDGET 40000
#define MAX_PRICE 63550
#define MIN_PRICE 0

//constants
const int ITEMS[GENE_SIZE] = {
    1500, 5000, 20000, 5000, 4500,
    4000, 3700, 1200, 1200, 2000,
    1200, 500, 5000, 1800, 1000,
    900, 350, 2000, 1200, 1500
};

int chromosome[POP_SIZE][GENE_SIZE];
double fitness[POP_SIZE];
int parent[PARENT_SIZE][GENE_SIZE];
int children[PARENT_SIZE][GENE_SIZE];

// normalize both budget and accumulated price to get a rational fitness value
double normalizePrice(int x) {
    double normalizedValue = double(x - MIN_PRICE) / (MAX_PRICE - MIN_PRICE);
    return normalizedValue;
}

void printChromosome() {
    for (int i=0; i<POP_SIZE; i++) {
        cout << "Chromosome " << i+1 << ": ";
        for (int j=0; j<GENE_SIZE; j++) cout << chromosome[i][j] << " ";
        cout << endl;
    }
}

void initializeChromosome() {
    for (int i=0; i<POP_SIZE; i++) {
        for (int j=0; j<GENE_SIZE; j++) chromosome[i][j] = rand() % 2;
    }
}

// goal 1 - maximize number of items (number of 1s in the gene pool)
// goal 2 - total price should be as closed as budget
// goal 3 - prioritize certain items
// currently goals are not associated with weight (importance), review later
void evaluateChromosome() {
    cout << "********************\t Evaluate Chromosome \t********************\n";
    for (int i = 0; i < POP_SIZE; i++) {
        int accPrice = 0;
        double  f1 = 0.0, f2 = 0.0, f3 = 0.0, nItems = 0.0, totalPriority = 0;
        
        for (int j = 0; j < GENE_SIZE; j++) {
            if (chromosome[i][j] == 1) {
                nItems++;
                accPrice += ITEMS[j];
                totalPriority += (GENE_SIZE - j);
            }
        }
        
        f1 = 1.0 / (fabs(normalizePrice(BUDGET) - normalizePrice(accPrice)) + 1);
        f2 = nItems / GENE_SIZE;
        f3 = totalPriority / (GENE_SIZE * (GENE_SIZE+1) / 2);

        fitness[i] = (f1 + f2 + f3) / 3;
        
        cout << "Chromo " << i+1 << "\tPrice: RM " << accPrice << "\tItems: " << nItems << " \tPriority: " << totalPriority <<  " \tFitness: " << fitness[i] << endl;
    }
    cout << endl;
}

void parentSelection() {
    cout << "********************\t Parent Selection \t********************\n";
    int player1, player2, bestPlayer;
    for (int i=0; i<PARENT_SIZE; i++) {
        
        //randomly choose chromosome[0-19]
        player1 = rand() % POP_SIZE;
        player2 = rand() % POP_SIZE;
        
        // make sure both player are different
        while (player1 == player2) {
            player1 = rand() % POP_SIZE;
            player2 = rand() % POP_SIZE;
        }
        
        cout << "\nPARENT " << i + 1 << " :\n";
        cout << "\tPlayer 1 : Chromo[" << player1 + 1 << "]\tFitness : " << fitness[player1] << " \n";
        cout << "\tPlayer 2 : Chromo[" << player2 + 1 << "]\tFitness : " << fitness[player2] << " \n";
        
        // find out who is the best player by comparing fitness
        if (fitness[player1] > fitness[player2]) bestPlayer = player1; else bestPlayer = player2;
        cout << "\tWinning player ---> Chromo[" << bestPlayer + 1 << "]\n";
        
        // allocate gene of best player to the parent array
        for (int j=0; j<POP_SIZE; j++) {
            for (int k=0; k<GENE_SIZE; k++) parent[i][k] = chromosome[bestPlayer][k];
        }
    }
}

int main(int argc, const char * argv[]) {
    srand ( unsigned ( time(0) ) ); // enable randomness in our program
    initializeChromosome();
    evaluateChromosome();
    parentSelection();
    return 0;
}
