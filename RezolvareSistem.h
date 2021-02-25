#pragma once
#include "Sistem.h"

class RezolvareSistem 
{
	public:
		Sistem* sistem;

		RezolvareSistem(Sistem* s);

		int GasesteNecunoscuta(int ecuatie, int necunoscuta);
		void CreeazaZerouri(int coloana, int linie, int& op);
		void RezolvaSistemul();
		void DetNecunoscutePrincipale();
		//void AfiseazaSolutii();
		Compatibilitate DeterminaCompatibilitate();
};
