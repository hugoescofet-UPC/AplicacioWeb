#include <iostream>
using namespace std;

class SessioUsuari {
private:
	string nomUsuari;
	int tempsLlimitSegons;
	bool activa;

public:
	// Per defecte
	SessioUsuari() : nomUsuari("convidat"), tempsLlimitSegons(300), activa(true) {}

	// Parametritzat
	explicit SessioUsuari(string m) : nomUsuari(m), tempsLlimitSegons(600), activa(true) {}

	// Parametritzat complet
	SessioUsuari(string m, int limitInicial) {
		nomUsuari = m;
		if (limitInicial == 0)
		{
			tempsLlimitSegons = 60;
		}
		else
		{
			tempsLlimitSegons = limitInicial;
		}
		activa = true;
	}

	string getNomUsuari() const {
		return nomUsuari;
	}

	bool isActiva() const {
		return activa;
	}

	void ampliarTemps(int segons) {
		if (segons > 0)
		{
			tempsLlimitSegons += segons;
		}
	}

	void tancarSessio() {
		activa = false;
	}

	~SessioUsuari() {
		if (activa)
		{
			activa = false;
			cout << "[AUDITORIA] La sessio de '" << nomUsuari << "' s'ha tancat automaticament en sortir d'ambit." << endl;
		}
	}
};

int main() {
	{
		SessioUsuari Guest;
		cout << "El nom de l'usuari actual es: '" << Guest.getNomUsuari() << "'" << endl;
		Guest.ampliarTemps(400);
		Guest.tancarSessio();
		if (Guest.isActiva())
		{
			cout << "El nom de l'usuari actual es: '" << Guest.getNomUsuari() << "'" << endl;
			Guest.ampliarTemps(600);
		}
	}
	{
		SessioUsuari Usuari1("Pablo");
		cout << "El nom de l'usuari actual es: '" << Usuari1.getNomUsuari() << "'" << endl;
		Usuari1.ampliarTemps(-500);
	}
	{
		SessioUsuari Usuari2("Laura", 0);
		cout << "El nom de l'usuari actual es: '" << Usuari2.getNomUsuari() << "'" << endl;
		Usuari2.ampliarTemps(10500);
		if (Usuari2.isActiva())
		{
			Usuari2.tancarSessio();
		}
	}
}