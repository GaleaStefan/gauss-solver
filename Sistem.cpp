#include "Sistem.h"
#include "Formatare.h"

Sistem::Sistem() : ecuatii(0), necunoscute(0), matrice(NULL), necPrincipale(NULL), compatibilitate(NECUNOSCUT)
{

}

Sistem::Sistem(int ecuatii, int necunoscute) : ecuatii(ecuatii), necunoscute(necunoscute), compatibilitate(NECUNOSCUT)
{
	this->AlocaMemorie();
}

Sistem::~Sistem()
{
	delete[] this->necPrincipale;

	for (int i = 0; i < this->ecuatii; i++)
	{
		delete[] this->matrice[i];
	}

	delete[] this->matrice;
}

void Sistem::AlocaMemorie()
{
	this->necPrincipale = new bool[necunoscute];
	for (int i = 0; i < this->necunoscute; i++)
	{
		this->necPrincipale[i] = false;
	}

	this->matrice = new float* [this->ecuatii];
	for (int i = 0; i < this->ecuatii; i++)
	{
		this->matrice[i] = new float[this->necunoscute + 1];
	}
}

std::istream& operator>>(std::istream& input, Sistem* sistem)
{
	if (sistem->matrice == NULL)
	{
		input >> sistem->ecuatii;
		input >> sistem->necunoscute;

		sistem->AlocaMemorie();
	}

	for (int i = 0; i < sistem->ecuatii; i++)
	{
		for (int j = 0; j <= sistem->necunoscute; j++)
		{
			input >> sistem->matrice[i][j];
		}
	}

	return input;
}

std::ostream& operator<<(std::ostream& output, const Sistem* const sistem)
{
	for (int i = 0; i < sistem->ecuatii; i++)
	{
		for (int j = 0; j <= sistem->necunoscute; j++)
		{
			output << sistem->matrice[i][j] << " ";
		}
		output << "\n";
	}

	return output;
}

void Sistem::InterschimbaLinii(int l1, int l2)
{
	for (int j = 0; j <= this->necunoscute; j++)
	{
		float aux = this->matrice[l1][j];
		this->matrice[l1][j] = this->matrice[l2][j];
		this->matrice[l2][j] = aux;
	}
}

void Sistem::InmultesteLinie(int linie, float coeficient)
{
	for (int j = 0; j <= this->necunoscute; j++)
	{
		this->matrice[linie][j] *= coeficient;
	}
}

void Sistem::AdaugaLinieLa(int linie, int adauga, float coeficient)
{
	for (int j = 0; j <= this->necunoscute; j++)
	{
		this->matrice[linie][j] += (coeficient * this->matrice[adauga][j]);
	}
}

void Sistem::AfiseazaSolutie()
{
	std::string solutie = "";

	switch (this->compatibilitate)
	{
		case INCOMPATIBIL:
		{
			solutie = "Nu exista solutii.\n";
			std::cout << "Sistemul este incompatibil\n";
			break;
		}
		case DETERMINAT:
		{
			solutie = "Solutia = S(";
			std::cout << "Sistemul este compatibil determinat\n";

			for (int necunoscuta = 0; necunoscuta < this->ecuatii; necunoscuta++)
			{
				solutie += Formatare::ConvertesteReal(this->matrice[necunoscuta][this->necunoscute]);
				
				if (necunoscuta < this->necunoscute - 1)
				{
					solutie += ", ";
				}
			}
			solutie += ")";

			break;
		}
		case NEDETERMINAT:
		{
			std::cout << "Sistemul este compatibil nedeterminat\n";
			solutie = "Solutia = S(";

			std::string * textNecunoscute = new std::string[this->necunoscute];

			for (int necunoscuta = 0; necunoscuta < this->necunoscute; necunoscuta++)
			{
				if (this->necPrincipale[necunoscuta] == false)
				{
					char litera = (char)('a' + necunoscuta);
					textNecunoscute[necunoscuta] = "";
					textNecunoscute[necunoscuta].insert(textNecunoscute[necunoscuta].end(), litera);
				}
			}

			for (int ecuatie = 0; ecuatie < this->ecuatii; ecuatie++)
			{
				int principala = -1;
				std::string temp = "";
				temp += Formatare::ConvertesteReal(this->matrice[ecuatie][this->necunoscute]);

				for (int necunoscuta = 0; necunoscuta < this->necunoscute; necunoscuta++)
				{
					if (this->matrice[ecuatie][necunoscuta] != 0)
					{
						if (this->necPrincipale[necunoscuta])
						{
							principala = necunoscuta;
						}
						else
						{
							float val = -(this->matrice[ecuatie][necunoscuta]);
							char litera = (char)('a' + necunoscuta);

							if (val > 0)
							{
								temp += "+";
							}

							temp += Formatare::ConvertesteReal(val);
							temp.insert(temp.end(), litera);
						}
					}
				}

				if (principala != -1)
				{
					textNecunoscute[principala] = temp;
				}
			}

			for (int i = 0; i < this->necunoscute; i++)
			{
				solutie += textNecunoscute[i];
				
				if (i < this->necunoscute - 1)
				{
					solutie += ", ";
				}
			}

			delete[] textNecunoscute;

			solutie += ")";
			break;
		}
		default:
		{
			return;
		}
	}

	std::cout << solutie;
}