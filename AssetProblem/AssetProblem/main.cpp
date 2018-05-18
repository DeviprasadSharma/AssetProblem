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
#define CROSSOVER_PROB 1.0

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

void copyParent() {
    for (int i=0; i<PARENT_SIZE; i++) {
        for (int j=0; j<GENE_SIZE; j++) children[i][j] = parent[i][j];
    }
}

void printParent() {
    for (int i=0; i<PARENT_SIZE; i++) {
        cout << "Parent   " << i+1 << " : ";
        for (int j=0; j<GENE_SIZE; j++) cout << parent[i][j] << " ";
        cout << endl;
    }
}

void printChildren() {
    for (int i=0; i<PARENT_SIZE; i++) {
        cout << "Children " << i+1 << " : ";
        for (int j=0; j<GENE_SIZE; j++) cout << children[i][j] << " ";
        cout << endl;
    }
}

void initializeChromosome() {
    for (int i=0; i<POP_SIZE; i++) {
        for (int j=0; j<GENE_SIZE; j++) chromosome[i][j] = rand() % 2;
    }
}

// goal 1 - total price should be as closed as budget
// goal 2 - maximize number of items (number of 1s in the gene pool)
// goal 3 - prioritize certain items
// currently goals are not associated with weight (importance), review later
void evaluateChromosome() {
    cout << "********************\t Evaluate Chromosome Begin \t********************\n";
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
    cout << "********************\t Evaluate Chromosome End \t********************\n\n\n";
}

void parentSelection() {
    cout << "********************\t Parent Selection Begin \t********************";
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
        
        cout << "\nParent   " << i + 1 << " :\n";
        cout << "\tPlayer 1 : Chromo[" << player1 + 1 << "]\tFitness : " << fitness[player1] << " \n";
        cout << "\tPlayer 2 : Chromo[" << player2 + 1 << "]\tFitness : " << fitness[player2] << " \n";
        
        // find out who is the best player by comparing fitness
        if (fitness[player1] > fitness[player2]) bestPlayer = player1; else bestPlayer = player2;
        cout << "\n\tWinning player ---> Chromo[" << bestPlayer + 1 << "]\n";
        
        // allocate gene of best player to the parent array
        for (int j=0; j<POP_SIZE; j++) {
            for (int k=0; k<GENE_SIZE; k++) parent[i][k] = chromosome[bestPlayer][k];
        }
    }
    
    cout << endl;
    printParent();
    cout << "********************\t Parent Selection Begin \t********************\n\n\n";
}

void crossover() {
    cout << "********************\t Crossover Parent Begin \t********************\n";
    
    double cProb = ( rand() % 11 ) / 10.0;
    cout << "Crossover Probability : " << cProb << endl;
    
    copyParent();
    
    if (cProb < CROSSOVER_PROB) {
        int cPoint = rand() % GENE_SIZE;
        cout << "Crossover did happen at point " << cPoint+1 << endl;
        
        for (int i=cPoint+1; i<GENE_SIZE; i++) {
            children[0][i] = parent[1][i];
            children[1][i] = parent[0][i];
        }
    } else {
        cout << "Crossover did not happen" << endl;
    }
    
    printChildren();
    cout << "********************\t Crossover Parent End \t********************\n\n\n";
}

int main(int argc, const char * argv[]) {
    srand ( unsigned ( time(0) ) ); // enable randomness in our program
    initializeChromosome();
    evaluateChromosome();
    parentSelection();
    crossover();
    return 0;
}
