#define CATCH_CONFIG_MAIN

#include "test.h"
#include "../src/methods/methods.h"
#include <string>

double * readArray(std::string filename);
bool equalSolution(double * &b, double * &y, int &m);

TEST_CASE( "Testing solver with cavity10", "[Solver]" ) {
	std::string path = "matrices/cavity10.mtx";
	double * b = readArray("matrices/b_folder/cavity10_x.mtx");
	int m;

	std::cout << "Parsing " << path << " ";
	IOmanager * io = new IOmanager();
	std::pair<CSR*, Ellpack*> matrices = io->readFile(path);
	CSR * csr = matrices.first;
	Ellpack * ellpack = matrices.second;
	m = csr->getRows();
	
	std::cout << std::endl;

	csr->x = readArray("matrices/b_folder/cavity10_b.mtx");
	ellpack->x = readArray("matrices/b_folder/cavity10_b.mtx");

	std::cout << "Sequential ";
	sequentialCSR(csr);
	sequentialEllpack(ellpack);

	REQUIRE(equalSolution(b, csr->y, m));
	REQUIRE(equalSolution(b, ellpack->y, m));

	io->exportResults(SEQUENTIAL, path, csr, ellpack);
	csr->resetResults();
	ellpack->resetResults();
	std::cout << std::endl;

	std::cout << "OpenMP ";
	openmpCSR(csr);
	openmpEllpack(ellpack);

	REQUIRE(equalSolution(b, csr->y, m));
	REQUIRE(equalSolution(b, ellpack->y, m));

	io->exportResults(OPENMP, path, csr, ellpack);
	csr->resetResults();
	ellpack->resetResults();
	std::cout << std::endl;

	std::cout << "CUDA ";
	solveCuda(io, path, csr, ellpack);

	REQUIRE(equalSolution(b, csr->y, m));
	REQUIRE(equalSolution(b, ellpack->y, m));
	std::cout << std::endl; 

	delete csr;
	delete ellpack;
	delete io;
}


TEST_CASE( "Testing solver with PR02R", "[Solver]" ) {
	std::string path = "matrices/PR02R.mtx";
	double * b = readArray("matrices/b_folder/PR02R_b.mtx");
	int m;

	std::cout << "Parsing " << path << " ";
	IOmanager * io = new IOmanager();
	std::pair<CSR*, Ellpack*> matrices = io->readFile(path);
	CSR * csr = matrices.first;
	Ellpack * ellpack = matrices.second;
	m = csr->getRows();
	
	std::cout << std::endl;

	csr->x = readArray("matrices/b_folder/PR02R_x.mtx");
	ellpack->x = readArray("matrices/b_folder/PR02R_x.mtx");

	std::cout << "Sequential ";
	sequentialCSR(csr);
	sequentialEllpack(ellpack);

	REQUIRE(equalSolution(b, csr->y, m));
	REQUIRE(equalSolution(b, ellpack->y, m));

	io->exportResults(SEQUENTIAL, path, csr, ellpack);
	csr->resetResults();
	ellpack->resetResults();
	std::cout << std::endl;

	std::cout << "OpenMP ";
	openmpCSR(csr);
	openmpEllpack(ellpack);

	REQUIRE(equalSolution(b, csr->y, m));
	REQUIRE(equalSolution(b, ellpack->y, m));

	io->exportResults(OPENMP, path, csr, ellpack);
	csr->resetResults();
	ellpack->resetResults();
	std::cout << std::endl;

	std::cout << "CUDA ";
	solveCuda(io, path, csr, ellpack);

	REQUIRE(equalSolution(b, csr->y, m));
	REQUIRE(equalSolution(b, ellpack->y, m));
	std::cout << std::endl; 

	delete csr;
	delete ellpack;
	delete io;
}