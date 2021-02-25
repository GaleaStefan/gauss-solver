#include <iostream>
#include "RezolvareSistem.h"

int main()
{
	Sistem* sistem;
	RezolvareSistem* rezolvare;
	int nrEcuatii, nrNecunoscute;

	std::cout << "----Date de intrare----\n";
	std::cout << "Nr Ecuatii: ";
	std::cin >> nrEcuatii;

	std::cout << "Nr Necunonscute: ";
	std::cin >> nrNecunoscute;

	sistem = new Sistem(nrEcuatii, nrNecunoscute);
	std::cout << "Matrice: ";
	std::cin >> sistem;

	std::cout << "\n\n----Rezolvarea sistemului----\n";
	rezolvare = new RezolvareSistem(sistem);
	rezolvare->RezolvaSistemul();

	std::cout << "\n\n----Solutia sistemului----\n";
	sistem->AfiseazaSolutie();

	std::cout << "\n\n";

	delete sistem;
	delete rezolvare;
}