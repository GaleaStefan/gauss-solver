#pragma once
#include <iostream>
#include <string>

enum Compatibilitate
{
	DETERMINAT,
	NEDETERMINAT,
	INCOMPATIBIL,
	NECUNOSCUT
};

class Sistem 
{
	public:
		int ecuatii;
		int necunoscute;
		float** matrice;
		bool* necPrincipale;
		Compatibilitate compatibilitate;

		Sistem();
		Sistem(int ecuatii, int necunoscute);
		~Sistem();

		void AlocaMemorie();
		void InterschimbaLinii(int l1, int l2);
		void InmultesteLinie(int linie, float coeficient);
		void AdaugaLinieLa(int linie, int adauga, float coeficient);
		void AfiseazaSolutie();

		friend std::istream& operator>>(std::istream& input, Sistem* sistem);
		friend std::ostream& operator<<(std::ostream& input, const Sistem *const sistem);
};