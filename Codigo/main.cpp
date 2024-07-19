#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <ctime>
#include <sstream>

using namespace std;

// variables globales

const int MAX_CANDIDATOS = 100; // numero maximo de candidatos
const int MAX_VOTANTES = 100; // numero maximo de votantes

struct Candidato {
    string nombre;
    string partido;
    string plataforma;
    string domicilio;
    string fechaNacimiento;
    string correoElectronico;
};

struct Votante {
    string cedula;
    string nombre;
    string domicilio;
    string fechaVoto;
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
void mostrarError();
void agregarCandidato();
void registrarVoto();
void mostrarCandidatos();
bool cedulaRegistrada(const string& cedula);
string to_string(int number);
string obtenerFechaActual();
void mostrarResultados();
void mostrarRegistroVotantes();

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
    dibujarCuadrado(5, 5, 50, 22);
    gotoxy(12, 7);
    cout << "Menu Principal";
    setColor(10);
    gotoxy(10, 9);
    cout << "1. Ingresar Candidatos";
    gotoxy(10, 11);
    cout << "2. Votar";
    gotoxy(10, 13);
    cout << "3. Mostrar Resultados";
    gotoxy(10, 15);
    cout << "4. Ver Registro de Votantes";
    setColor(12);
    gotoxy(10, 17);
    cout << "5. Salir";
}

// permite mostrar mensaje de error personalizado
void mostrarError(const string& mensaje) {
    setColor(12); // Color rojo para el mensaje de error
    gotoxy(10, 23); // Ajusta segun el diseno
    cout << mensaje;
    setColor(15); // Restaurar color normal
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
    
    // variables para capturar entradas
    string input;

    // validacion y captura del nombre
    do {
        setColor(10);
        gotoxy(10, 9);
        cout << "Nombre: ";
        getline(cin, input);
        if (input.empty()) {
            mostrarError("El nombre no puede estar vacio.");
        }
    } while (input.empty());
    candidatos[numCandidatos].nombre = input;

    // validacion y captura del partido
    do {
        setColor(10);
        gotoxy(10, 11);
        cout << "Partido: ";
        getline(cin, input);
        if (input.empty()) {
            mostrarError("El partido no puede estar vacio.");
        }
    } while (input.empty());
    candidatos[numCandidatos].partido = input;

    // validacion y captura de la plataforma
    do {
        setColor(10);
        gotoxy(10, 13);
        cout << "Plataforma: ";
        getline(cin, input);
        if (input.empty()) {
            mostrarError("La plataforma no puede estar vacia.");
        }
    } while (input.empty());
    candidatos[numCandidatos].plataforma = input;

    // validacion y captura del domicilio
    do {
        setColor(10);
        gotoxy(10, 15);
        cout << "Domicilio: ";
        getline(cin, input);
        if (input.empty()) {
            mostrarError("El domicilio no puede estar vacio.");
        }
    } while (input.empty());
    candidatos[numCandidatos].domicilio = input;

    // validacion y captura de la fecha de nacimiento
    do {
        setColor(10);
        gotoxy(10, 17);
        cout << "Fecha de Nacimiento (DD/MM/AAAA): ";
        getline(cin, input);
        if (input.empty()) {
            mostrarError("La fecha de nacimiento no puede estar vacia.");
        }
    } while (input.empty());
    candidatos[numCandidatos].fechaNacimiento = input;

    // validacion y captura del correo electronico
    do {
        setColor(10);
        gotoxy(10, 19);
        cout << "Correo Electronico: ";
        getline(cin, input);
        if (input.empty()) {
            mostrarError("El correo electronico no puede estar vacio.");
        }
    } while (input.empty());
    candidatos[numCandidatos].correoElectronico = input;

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

// verifica si una cedula ya esta registrada
bool cedulaRegistrada(const string& cedula) {
    for (int i = 0; i < numVotantes; i++) {
        if (votantes[i].cedula == cedula) {
            return true;
        }
    }
    return false;
}

// convierte un entero a una cadena
string to_string(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}

// obtiene la fecha actual en formato DD/MM/AAAA
string obtenerFechaActual() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string day = to_string(ltm->tm_mday);
    string month = to_string(1 + ltm->tm_mon);
    string year = to_string(1900 + ltm->tm_year);
    
    if (day.length() < 2) day = "0" + day;
    if (month.length() < 2) month = "0" + month;

    return day + "/" + month + "/" + year;
}

// permite registrar un voto para un candidato
void registrarVoto() {
    limpiarPantalla();
    setColor(11);
    dibujarCuadrado(5, 5, 70, 25);
    
    Votante votante;
    gotoxy(10, 7);
    cout << "Ingrese sus datos para votar";
    
    // Validacion y captura de la cedula
    do {
        setColor(10);
        gotoxy(10, 9);
        cout << "Cedula: ";
        cin.ignore();
        getline(cin, votante.cedula);
        if (votante.cedula.empty()) {
            mostrarError("La cedula no puede estar vacia.");
        }
    } while (votante.cedula.empty());

    if (cedulaRegistrada(votante.cedula)) {
        mostrarError("Error: Este votante ya ha votado.");
        return;
    }
    
    // Validacion y captura del nombre
    do {
        setColor(10);
        gotoxy(10, 11);
        cout << "Nombre: ";
        getline(cin, votante.nombre);
        if (votante.nombre.empty()) {
            mostrarError("El nombre no puede estar vacio.");
        }
    } while (votante.nombre.empty());

    // Validacion y captura del domicilio
    do {
        setColor(10);
        gotoxy(10, 13);
        cout << "Domicilio: ";
        getline(cin, votante.domicilio);
        if (votante.domicilio.empty()) {
            mostrarError("El domicilio no puede estar vacio.");
        }
    } while (votante.domicilio.empty());

    votante.fechaVoto = obtenerFechaActual();
    
    mostrarCandidatos();
    int indice;
    gotoxy(10, 15 + numCandidatos);
    setColor(11);
    cout << "Ingrese el indice del candidato: ";
    setColor(14);
    cin >> indice;
    
    if (indice >= 0 && indice < numCandidatos) {
        votos[indice]++;
        votantes[numVotantes] = votante;
        numVotantes++;
        setColor(11);
        gotoxy(10, 17 + numCandidatos);
        cout << "Voto registrado exitosamente!" << endl;
    } else {
        mostrarError("Indice de candidato invalido.");
    }
}

// muestra los resultados de las votaciones
void mostrarResultados() {
    int totalVotos = 0;
    for (int i = 0; i < numCandidatos; i++) {
        totalVotos += votos[i];
    }

    int maxVotos = 0;
    int ganador = -1;
    for (int i = 0; i < numCandidatos; i++) {
        if (votos[i] > maxVotos) {
            maxVotos = votos[i];
            ganador = i;
        }
    }

    limpiarPantalla();
    setColor(11);
    dibujarCuadrado(5, 5, 70, 20);
    setColor(10);
    if (ganador != -1) {
        gotoxy(10, 7);
        cout << "El ganador es: " << candidatos[ganador].nombre << " con " << maxVotos << " votos." << endl;
    }

    for (int i = 0; i < numCandidatos; i++) {
        double porcentaje = (totalVotos > 0) ? (static_cast<double>(votos[i]) / totalVotos) * 100 : 0;
        setColor(14);
        gotoxy(10, 9 + i);
        cout << "Candidato: " << candidatos[i].nombre 
             << ", Votos: " << votos[i] 
             << ", Porcentaje: " << fixed << setprecision(2) << porcentaje << "%" << endl;
    }
}

// muestra el registro de votantes con sus respectivos datos
void mostrarRegistroVotantes() {
    limpiarPantalla();
    setColor(11);
    dibujarCuadrado(5, 5, 70, 10 + numVotantes);
    gotoxy(10, 7);
    cout << "Registro de Votantes:";
    for (int i = 0; i < numVotantes; i++) {
        setColor(10);
        gotoxy(10, 9 + i);
        cout << "Cedula: " << votantes[i].cedula 
             << ", Nombre: " << votantes[i].nombre 
             << ", Domicilio: " << votantes[i].domicilio 
             << ", Fecha de Voto: " << votantes[i].fechaVoto << endl;
    }
}

int main(int argc, char** argv) {
	// funcionalidad del menu
	 int opcion;

    do {
        limpiarPantalla();
        mostrarMenu();
        gotoxy(10, 17);
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
