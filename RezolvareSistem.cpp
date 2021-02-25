#include "RezolvareSistem.h"
#include "Formatare.h"
#include <string>

RezolvareSistem::RezolvareSistem(Sistem* s) : sistem(s)
{

}

int RezolvareSistem::GasesteNecunoscuta(int ecuatie, int necunoscuta)
{
	if (sistem->matrice[ecuatie][necunoscuta])
	{
		return ecuatie;
	}

	for (int ec = ecuatie + 1; ec < sistem->ecuatii; ec++)
	{
		if (sistem->matrice[ec][necunoscuta])
		{
			return ec;
		}
	}

	return -1;
}

void RezolvareSistem::CreeazaZerouri(int coloana, int linie, int& operatii)
{
	for (int ec = 0; ec < sistem->ecuatii; ec++)
	{
		if (ec != linie)
		{
			float coeficient = -(sistem->matrice[ec][coloana]);
			std::cout << operatii++ << ". " << "Linia_" << ec + 1 << " <-- " << "Linia_" << ec + 1 << " + " << coeficient << "Linia_" << linie + 1 << "\n";
			

			sistem->AdaugaLinieLa(ec, linie, coeficient);
			std::cout << this->sistem << std::endl;
		}
	}
}

Compatibilitate RezolvareSistem::DeterminaCompatibilitate()
{
	bool doarZerouri = true;

	// Verifica daca ultima ecuatie este una imposibila
	for (int i = 0; i < sistem->necunoscute; i++)
	{
		if (sistem->matrice[sistem->ecuatii - 1][i] != 0.0)
		{
			doarZerouri = false;
			break;
		}
	}

	if (doarZerouri == true && sistem->matrice[sistem->ecuatii - 1][sistem->necunoscute] != 0.0)
	{
		return INCOMPATIBIL;
	}

	// Verifica daca toate necunoscutele sunt principale
	int ecuatie;

	for (ecuatie = 0; ecuatie < sistem->ecuatii; ecuatie++)
	{
		if (sistem->matrice[ecuatie][ecuatie] != 1.0)
		{
			return NEDETERMINAT;
		}
	}

	// Ne asiguram ca toate necunoscutele sunt principale
	if (ecuatie - 1 < sistem->necunoscute - 1)
	{
		return NEDETERMINAT;
	}

	return DETERMINAT;
}

void RezolvareSistem::RezolvaSistemul()
{
	int necunoscuta = 0;
	int operatii = 1;

	for (int ecuatie = 0; ecuatie < sistem->ecuatii; ecuatie++)
	{
		// Cauta pivot
		int linieNec = this->GasesteNecunoscuta(ecuatie, necunoscuta);

		if (linieNec >= 0)
		{
			if (linieNec != ecuatie)
			{
				// Daca necunoscuta nu se afla in ecuatia curenta dar se afla in alta ecuatie
				std::cout << operatii++ << ". " << "Linia_" << ecuatie + 1 << " <---> " << "Linia_" << linieNec + 1 << "\n";
				
				sistem->InterschimbaLinii(ecuatie, linieNec);
				std::cout << this->sistem << std::endl;
			}
		}
		else
		{
			// Daca nicio ecuatie nu mai contine necunoscuta
			if (necunoscuta == sistem->necunoscute - 1)
			{
				break;
			}
			else
			{
				// Mutam pivotul la dreapta
				ecuatie--;
				necunoscuta++;
				continue;
			}
		}

		if (sistem->matrice[ecuatie][necunoscuta] != 1.0)
		{
			// Daca pivotul e =/= 0
			float coeficient = 1 / sistem->matrice[ecuatie][necunoscuta];

			std::cout << operatii++ << ". " << "Linia_" << ecuatie + 1 << " <-- " << coeficient << "Linia_" << ecuatie + 1 << "\n";
			
			sistem->InmultesteLinie(ecuatie, coeficient);
			std::cout << this->sistem << std::endl;
		}

		// Creeaza 0-uri pe coloana pivotului
		this->CreeazaZerouri(necunoscuta, ecuatie, operatii);

		// Treci la urmatoarea necunoscuta
		necunoscuta++;

		//std::cout << sistem;
	}

	sistem->compatibilitate = this->DeterminaCompatibilitate();

	if (sistem->compatibilitate == NEDETERMINAT)
	{
		this->DetNecunoscutePrincipale();
	}
}

void RezolvareSistem::DetNecunoscutePrincipale()
{
	int ecuatie = 0;

	for (int nec = 0; nec < sistem->necunoscute; nec++)
	{
		if (sistem->matrice[ecuatie][nec] == 1)
		{
			sistem->necPrincipale[nec] = true;
			
			if (ecuatie == sistem->ecuatii - 1)
			{
				return;
			}
			ecuatie++;
		}
	}
}