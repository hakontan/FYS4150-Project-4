# include <iostream>
# include <fstream>
//# include <mpi.h> 
# include <armadillo>
# include <ctime>
# include <random>
# include <cmath> 

using std::cout;
using std::exp;
using std::endl;


inline int periodic_index(int i, int N)
{
    return (i + N) % N;
}

double E_init(arma::imat lattice)
{
    int E = 0;
    double peri_index_i;
    double peri_index_j;
    int N_row = lattice.n_rows;
    int N_col = lattice.n_cols;
    for (int i = 0; i < N_row; i++) {
        peri_index_i = periodic_index(i - 1, N_row);
    for (int j = 0; j < N_col; j++) {
        peri_index_j = periodic_index(j - 1, N_col);
        E += lattice(i, j) * (lattice(peri_index_i, j) +
             lattice(i, peri_index_j));
    }}
    E *= - 1;
    return E;
}

double M_init(arma::imat lattice)
{
    return arma::sum(arma::sum(lattice, 0));
}

arma::imat lattice (int N)
{   
    arma::arma_rng::set_seed(clock());
    arma::imat lattice = arma::randi<arma::imat>(N, N, arma::distr_param(0,1));
    for (int i=0; i < N; i++) {
    for (int j=0; j < N; j++) {
        if (lattice(i,j) == 0) 
        {
            lattice(i,j) = -1;
        }
    }}
    return lattice;
}

void metropolis(int MC, int N, double T, arma::vec &E, arma::vec &M)
/*
----------
MC: int
    Number of Monte Carlo samples
N: int 
    Dimension of lattice
T: double
    Temperature in units k_B * T / J
E: arma::vec
    Vector of energies
M: arma::vec
    Vector of magnetic moments
*/
{   std::mt19937_64 generator;
    std::uniform_int_distribution<int> distribution(0, N - 1);
    std::uniform_real_distribution<double> accepting(0, 1);
    int i_samp;
    int j_samp;
    double delta_E;
    double Boltz_factor; 
    arma::imat matrix = lattice(N);
    E(0) = E_init(matrix);
    M(0) = M_init(matrix);
    double _E = E(0); 
    double _M = M(0);
    for (int i = 0; i < MC; i++){
        for (int j = 0; j < N * N; j++){  
            i_samp = distribution(generator);
            j_samp = distribution(generator);
            delta_E = 2 * matrix(i_samp, j_samp)
                        *(matrix(periodic_index(i_samp + 1, N), j_samp)
                        + matrix(periodic_index(i_samp - 1, N), j_samp)
                        + matrix(i_samp, periodic_index(j_samp + 1, N))
                        + matrix(i_samp, periodic_index(j_samp - 1, N)));

            Boltz_factor = exp( - delta_E / T);
            //cout << delta_E << " " << Boltz_factor << " " << accepting(generator) << endl;
            if (Boltz_factor >= accepting(generator))
            {   
                //cout << delta_E << endl;
                matrix(i_samp, j_samp) *= - 1;
                _E += delta_E;
                _M += 2 * matrix(i_samp, j_samp);
            }
        }
        E(i) = _E;
        M(i) = _M;
    }
}


int main ()
{   
    int N = 2;
    int MC = 1e6;
    double T = 1.0;
    arma::vec E = arma::zeros<arma::vec>(MC);
    arma::vec M = arma::zeros<arma::vec>(MC);
    metropolis(MC, N, T, E, M);
    //E.print();
    cout << arma::mean(E) << endl;
    return 0;
}