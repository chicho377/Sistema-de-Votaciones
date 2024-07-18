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

// permite agregar un candidato a la lista
void agregarCandidato() {
	// verificacion de cantidad maxima
    if (numCandidatos >= MAX_CANDIDATOS) {
        cerr << "No se pueden agregar mas candidatos." << endl;
        return;
    }
    
    limpiarPantalla();
    setColor(11);
    dibujarCuadrado(5, 5, 70, 22);
    gotoxy(10, 7);
    cout << "Ingreso de Candidatos";
    
    setColor(10);
    gotoxy(10, 9);
    cout << "Nombre: ";
    cin.ignore();
    getline(cin, candidatos[numCandidatos].nombre);
    
    gotoxy(10, 11);
    cout << "Partido: ";
    getline(cin, candidatos[numCandidatos].partido);
    
    gotoxy(10, 13);
    cout << "Plataforma: ";
    getline(cin, candidatos[numCandidatos].plataforma);
    
    setColor(14);
    gotoxy(10, 15);
    cout << "Domicilio: ";
    getline(cin, candidatos[numCandidatos].domicilio);
    
    gotoxy(10, 17);
    cout << "Fecha de Nacimiento (DD/MM/AAAA): ";
    getline(cin, candidatos[numCandidatos].fechaNacimiento);
    
    setColor(15);
    gotoxy(10, 19);
    cout << "Correo Electronico: ";
    getline(cin, candidatos[numCandidatos].correoElectronico);
    
    votos[numCandidatos] = 0;
    numCandidatos++;

    setColor(11);
    gotoxy(10, 21);
    cout << "Candidato agregado exitosamente!" << endl;
}

// muestra la lista de candidatos
void mostrarCandidatos() {
    limpiarPantalla();
    setColor(11);
    dibujarCuadrado(5, 5, 70, 15 + numCandidatos);
    gotoxy(10, 7);
    cout << "Lista de Candidatos:";
    for (int i = 0; i < numCandidatos; i++) {
        setColor(10);
        gotoxy(10, 9 + i);
        cout << i << ". " << candidatos[i].nombre << " (" << candidatos[i].partido << ")";
    }
}

// permite registrar un voto para un candidato
void registrarVoto() {
    mostrarCandidatos();
    int indice;
    gotoxy(10, 9 + numCandidatos + 1);
    setColor(11);
    cout << "Ingrese el indice del candidato: ";
    setColor(14);
    cin >> indice;
    
    if (indice >= 0 && indice < numCandidatos) {
        votos[indice]++;
        setColor(11);
        gotoxy(10, 11 + numCandidatos + 1);
        cout << "Voto registrado exitosamente!" << endl;
    } else {
        setColor(12);
        gotoxy(10, 11 + numCandidatos + 1);
        cerr << "Indice de candidato invalido." << endl;
    }
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
