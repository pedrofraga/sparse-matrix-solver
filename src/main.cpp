#include <iostream>
#include "methods/methods.h"

int main(int argc, char ** argv) {	

	for (size_t i = 1; i < argc; ++i) {
		std::string path = std::string(argv[i]);
		std::cout << "Parsing " << path << " " << std::endl;

		IOmanager * io = new IOmanager();
		std::pair<CSR*, Ellpack*> matrices = io->readFile(path);
		CSR * csr = matrices.first;
		Ellpack * ellpack = matrices.second;

		std::cout << "Sequential " << std::endl;
		sequentialCSR(csr);
		sequentialEllpack(ellpack);

		io->exportResults(SEQUENTIAL, path, csr, ellpack);
		csr->resetResults();
		ellpack->resetResults();

		std::cout << " >> OpenMP " << std::endl;
		openmpCSR(csr);
		openmpEllpack(ellpack);

		io->exportResults(OPENMP, path, csr, ellpack);
		csr->resetResults();
		ellpack->resetResults();

		std::cout << " >> CUDA " << std::endl;
		solveCuda(io, path, csr, ellpack);

		std::cout << "Done!" << std::endl << std::endl;

		delete csr;
		delete ellpack;
		delete io;
	}
}