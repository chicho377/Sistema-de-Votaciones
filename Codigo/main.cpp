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
void mostrarMenu();
void agregarCandidato();
void registrarVoto();
void mostrarResultados();
void mostrarCandidatos();

/* funciones

 funciones de utilidad*/

// mueve el cursor a la posicion (x, y) en la consola
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// cambia el color del texto en la consola
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// dibuja un cuadro en la consola en las coordenadas (x1, y1) y (x2, y2)
void dibujarCuadrado(int x1, int y1, int x2, int y2) {
    for (int x = x1; x <= x2; x++) {
        gotoxy(x, y1);
        cout << (char)205;
        gotoxy(x, y2);
        cout << (char)205;
    }
    for (int y = y1; y <= y2; y++) {
        gotoxy(x1, y);
        cout << (char)186;
        gotoxy(x2, y);
        cout << (char)186;
    }
    gotoxy(x1, y1);
    cout << (char)201;
    gotoxy(x2, y1);
    cout << (char)187;
    gotoxy(x1, y2);
    cout << (char)200;
    gotoxy(x2, y2);
    cout << (char)188;
}

// limpia la pantalla de la consola
void limpiarPantalla() {
    system("cls");
}

// funciones principales

// muestra el menu principal
void mostrarMenu() {
    setColor(11);
    dibujarCuadrado(5, 5, 50, 20);
    gotoxy(12, 7);
    cout << "Menu Principal";
    setColor(10);
    gotoxy(10, 9);
    cout << "1. Ingresar Candidatos";
    gotoxy(10, 11);
    cout << "2. Votar";
    gotoxy(10, 13);
    cout << "3. Mostrar Resultados";
    setColor(12);
    gotoxy(10, 15);
    cout << "4. Salir";
}

int main(int argc, char** argv) {
	// funcionalidad del menu
	 int opcion;

    do {
        limpiarPantalla();
        mostrarMenu();
        gotoxy(10, 15);
        setColor(14);
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarCandidato();
                break;
            case 2:
                registrarVoto();
                break;
            case 3:
                mostrarResultados();
                break;
            case 4:
                gotoxy(10, 17);
                setColor(12);
                cout << "Saliendo del sistema.\n";
                break;
            default:
                gotoxy(10, 17);
                setColor(12);
                cout << "Opcion invalida. Intente nuevamente.\n";
        }

        if (opcion != 4) {
            gotoxy(10, 19);
            setColor(15);
            system("pause");
        }

    } while (opcion != 4);

    return 0;
}
