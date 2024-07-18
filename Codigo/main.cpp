#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

// variables globales

const int MAX_CANDIDATOS = 100; // Numero maximo de candidatos

struct Candidato {
    string nombre;
    string partido;
    string plataforma;
    string domicilio;
    string fechaNacimiento;
    string correoElectronico;
};

Candidato candidatos[MAX_CANDIDATOS];
int votos[MAX_CANDIDATOS];
int numCandidatos = 0;

// prototipos de funciones
void gotoxy(int x, int y);
void setColor(int color);
void dibujarCuadrado(int x1, int y1, int x2, int y2);
void limpiarPantalla();
void showMenu();
void agregarCandidato();
void registrarVoto();
void mostrarResultados();
void mostrarCandidatos();

int main(int argc, char** argv) {
	return 0;
}
