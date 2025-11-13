#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

template <typename T>
T leerNumero(const string& mensaje) {
    T valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) return valor; // si pudo leer un valor del tipo T, lo devuelve
        cin.clear(); // limpia el estado de error del flujo
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta la línea completa del buffer
        cout << "Entrada invalida. Intenta de nuevo.\n";
    }
}

struct Postre {
    int id;
    string nombre;
    float precio;
    int cantidad;
};

//funcion para omitir caracteres no deseados en la entrada
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Leer postres del archivo
vector<Postre> leerPostres() {
    vector<Postre> lista;
    ifstream archivo("postres.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, precio, cantidad;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, precio, ',');
        getline(ss, cantidad, ',');

        if (id != "" && nombre != "" && precio != "" && cantidad != "") {
            Postre p;
            p.id = stoi(id);
            p.nombre = nombre;
            p.precio = stof(precio);
            p.cantidad = stoi(cantidad);
            lista.push_back(p);
        }
    }

    archivo.close();
    return lista;
}

// Guardar postres en archivo
void guardarPostres(const vector<Postre>& lista) {
    ofstream archivo("postres.txt");
    for (auto &p : lista) {
        archivo << p.id << "," << p.nombre << "," << p.precio << "," << p.cantidad << "\n";
    }
    archivo.close();
}

// Mostrar postres
void mostrarPostres() {
    int null;
    auto lista = leerPostres();
    cout << "\nLista de postres disponibles:\n";
    cout << "----------------------------------------\n";
    for (auto &p : lista) {
        cout << "ID: " << p.id
             << " | Nombre: " << p.nombre
             << " | Precio: $" << p.precio
             << " | Cantidad: " << p.cantidad << endl;
    }
    cout << "----------------------------------------\n";
    cin >> null;
    system("clear");
}

// Agregar postre
void agregarPostre() {
    vector<Postre> lista = leerPostres();
    Postre p;

    cout << "\nAgregar nuevo postre:\n";
    p.id = leerNumero<int>("ID: ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el salto de línea antes de getline

    cout << "Nombre: ";
    getline(cin, p.nombre);

    p.precio = leerNumero<float>("Precio: ");
    p.cantidad = leerNumero<int>("Cantidad: ");

    lista.push_back(p);
    guardarPostres(lista);

    cout << "Postre agregado correctamente.\n";
    system("clear");
}

// Modificar postre
void modificarPostre() {
    auto lista = leerPostres();
    int idBuscar;
    bool encontrado = false;
    idBuscar = leerNumero<int>("\nIngrese el ID del postre a modificar: ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto &p : lista) {
        if (p.id == idBuscar) {
            encontrado = true;
            cout << "\nPostre encontrado:\n";
            cout << "Nombre actual: " << p.nombre << endl;
            cout << "Precio actual: " << p.precio << endl;
            cout << "Cantidad actual: " << p.cantidad << endl;

            cout << "\nNuevo nombre (enter para dejar igual): ";
            string nuevoNombre;
            getline(cin, nuevoNombre);
            if (!nuevoNombre.empty()) p.nombre = nuevoNombre;

            float nuevoPrecio;
            nuevoPrecio = leerNumero<float>("\nNuevo precio (0 para dejar igual: \n");
            if (nuevoPrecio != 0) p.precio = nuevoPrecio;

            int nuevaCantidad;
            nuevaCantidad = leerNumero<int>("\nNueva cantidad (-1 para dejar igual: \n");
            if (nuevaCantidad != -1) p.cantidad = nuevaCantidad;
            
            break;
        }
    }

    if (encontrado) {
        guardarPostres(lista);
        cout << "Postre modificado correctamente.\n";
        system("clear");
    } else {
        cout << "No se encontró el postre con ese ID.\n";
        system("clear");
    }
}

// Eliminar postre
void eliminarPostre() {
    auto lista = leerPostres();
    int id;
    bool eliminado = false;
    id = leerNumero<int>("\nIngerese el ID del postre a eliminar: \n");

    vector<Postre> nuevaLista;
    for (auto &p : lista) {
        if (p.id == id) {
            eliminado = true;
            cout << "Postre eliminado: " << p.nombre << endl;
            continue;
        }
        nuevaLista.push_back(p);
    }

    guardarPostres(nuevaLista);

    if (eliminado)
        cout << "Postre eliminado correctamente.\n";
    else
        cout << "No se encontró el postre.\n";
}

// Comprar postre
void comprarPostre() {
    auto lista = leerPostres();
    int id, cantidadCompra;
    bool encontrado = false;

    id = leerNumero<int>("\nIngrese el ID del postre a comprar: \n");
    cantidadCompra = leerNumero<int>("\nCantidad a comprar: \n");

    for (auto &p : lista) {
        if (p.id == id) {
            encontrado = true;
            if (cantidadCompra <= p.cantidad) {
                p.cantidad -= cantidadCompra;
                cout << "\nCompra realizada correctamente.\n";
                cout << "Total a pagar: $" << p.precio * cantidadCompra << endl;
            } else {
                cout << "No hay suficiente cantidad.\n";
            }
            break;
        }
    }

    if (encontrado) {
        guardarPostres(lista);
    } else {
        cout << "No se encontró el postre.\n";
    }
}

// Menú administrador
void menuAdmin() {
    int op;
    do {
        op = leerNumero<int>("\n--- MENU ADMINISTRADOR ---\n 1. Ver postres\n 2. Agregar postre\n 3. Modificar postre\n 4. Eliminar postre\n 0. salir\n Opcion:\n");
        switch (op) {
            case 1: mostrarPostres(); break;
            case 2: agregarPostre(); break;
            case 3: modificarPostre(); break;
            case 4: eliminarPostre(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción no válida.\n"; system("clear");
        }
    } while (op != 0);
}

// Menú comprador
void menuComprador() {
    int op;
    do {
        op = leerNumero<int>("\n--- MENU COMPRADOR ---\n 1. Ver menú de postres\n 2. Comprar postre\n 0. Salir\n");
        system("clear");
        switch (op) {
            case 1: mostrarPostres(); break;
            case 2: comprarPostre(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (op != 0);
}

// Programa principal
int main() {
    string usuario, password;

    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contraseña: ";
    cin >> password;

    if (usuario == "admin" && password == "12345678") {
        menuAdmin();
    } else if (usuario == "comprador" && password == "abc123") {
        menuComprador();
    } else {
        cout << "Usuario o contraseña incorrectos.\n";
    }

    return 0;
}#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

template <typename T>
T leerNumero(const string& mensaje) {
    T valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) return valor; // si pudo leer un valor del tipo T, lo devuelve
        cin.clear(); // limpia el estado de error del flujo
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta la línea completa del buffer
        cout << "Entrada invalida. Intenta de nuevo.\n";
    }
}

struct Postre {
    int id;
    string nombre;
    float precio;
    int cantidad;
};

//funcion para omitir caracteres no deseados en la entrada
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Leer postres del archivo
vector<Postre> leerPostres() {
    vector<Postre> lista;
    ifstream archivo("postres.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, precio, cantidad;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, precio, ',');
        getline(ss, cantidad, ',');

        if (id != "" && nombre != "" && precio != "" && cantidad != "") {
            Postre p;
            p.id = stoi(id);
            p.nombre = nombre;
            p.precio = stof(precio);
            p.cantidad = stoi(cantidad);
            lista.push_back(p);
        }
    }

    archivo.close();
    return lista;
}

// Guardar postres en archivo
void guardarPostres(const vector<Postre>& lista) {
    ofstream archivo("postres.txt");
    for (auto &p : lista) {
        archivo << p.id << "," << p.nombre << "," << p.precio << "," << p.cantidad << "\n";
    }
    archivo.close();
}

// Mostrar postres
void mostrarPostres() {
    int null;
    auto lista = leerPostres();
    cout << "\nLista de postres disponibles:\n";
    cout << "----------------------------------------\n";
    for (auto &p : lista) {
        cout << "ID: " << p.id
             << " | Nombre: " << p.nombre
             << " | Precio: $" << p.precio
             << " | Cantidad: " << p.cantidad << endl;
    }
    cout << "----------------------------------------\n";
    cin >> null;
    system("clear");
}

// Agregar postre
void agregarPostre() {
    vector<Postre> lista = leerPostres();
    Postre p;

    cout << "\nAgregar nuevo postre:\n";
    p.id = leerNumero<int>("ID: ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el salto de línea antes de getline

    cout << "Nombre: ";
    getline(cin, p.nombre);

    p.precio = leerNumero<float>("Precio: ");
    p.cantidad = leerNumero<int>("Cantidad: ");

    lista.push_back(p);
    guardarPostres(lista);

    cout << "Postre agregado correctamente.\n";
    system("clear");
}

// Modificar postre
void modificarPostre() {
    auto lista = leerPostres();
    int idBuscar;
    bool encontrado = false;
    idBuscar = leerNumero<int>("\nIngrese el ID del postre a modificar: ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto &p : lista) {
        if (p.id == idBuscar) {
            encontrado = true;
            cout << "\nPostre encontrado:\n";
            cout << "Nombre actual: " << p.nombre << endl;
            cout << "Precio actual: " << p.precio << endl;
            cout << "Cantidad actual: " << p.cantidad << endl;

            cout << "\nNuevo nombre (enter para dejar igual): ";
            string nuevoNombre;
            getline(cin, nuevoNombre);
            if (!nuevoNombre.empty()) p.nombre = nuevoNombre;

            float nuevoPrecio;
            nuevoPrecio = leerNumero<float>("\nNuevo precio (0 para dejar igual: \n");
            if (nuevoPrecio != 0) p.precio = nuevoPrecio;

            int nuevaCantidad;
            nuevaCantidad = leerNumero<int>("\nNueva cantidad (-1 para dejar igual: \n");
            if (nuevaCantidad != -1) p.cantidad = nuevaCantidad;
            
            break;
        }
    }

    if (encontrado) {
        guardarPostres(lista);
        cout << "Postre modificado correctamente.\n";
        system("clear");
    } else {
        cout << "No se encontró el postre con ese ID.\n";
        system("clear");
    }
}

// Eliminar postre
void eliminarPostre() {
    auto lista = leerPostres();
    int id;
    bool eliminado = false;
    id = leerNumero<int>("\nIngerese el ID del postre a eliminar: \n");

    vector<Postre> nuevaLista;
    for (auto &p : lista) {
        if (p.id == id) {
            eliminado = true;
            cout << "Postre eliminado: " << p.nombre << endl;
            continue;
        }
        nuevaLista.push_back(p);
    }

    guardarPostres(nuevaLista);

    if (eliminado)
        cout << "Postre eliminado correctamente.\n";
    else
        cout << "No se encontró el postre.\n";
}

// Comprar postre
void comprarPostre() {
    auto lista = leerPostres();
    int id, cantidadCompra;
    bool encontrado = false;

    id = leerNumero<int>("\nIngrese el ID del postre a comprar: \n");
    cantidadCompra = leerNumero<int>("\nCantidad a comprar: \n");

    for (auto &p : lista) {
        if (p.id == id) {
            encontrado = true;
            if (cantidadCompra <= p.cantidad) {
                p.cantidad -= cantidadCompra;
                cout << "\nCompra realizada correctamente.\n";
                cout << "Total a pagar: $" << p.precio * cantidadCompra << endl;
            } else {
                cout << "No hay suficiente cantidad.\n";
            }
            break;
        }
    }

    if (encontrado) {
        guardarPostres(lista);
    } else {
        cout << "No se encontró el postre.\n";
    }
}

// Menú administrador
void menuAdmin() {
    int op;
    do {
        op = leerNumero<int>("\n--- MENU ADMINISTRADOR ---\n 1. Ver postres\n 2. Agregar postre\n 3. Modificar postre\n 4. Eliminar postre\n 0. salir\n Opcion:\n");
        switch (op) {
            case 1: mostrarPostres(); break;
            case 2: agregarPostre(); break;
            case 3: modificarPostre(); break;
            case 4: eliminarPostre(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción no válida.\n"; system("clear");
        }
    } while (op != 0);
}

// Menú comprador
void menuComprador() {
    int op;
    do {
        op = leerNumero<int>("\n--- MENU COMPRADOR ---\n 1. Ver menú de postres\n 2. Comprar postre\n 0. Salir\n");
        system("clear");
        switch (op) {
            case 1: mostrarPostres(); break;
            case 2: comprarPostre(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (op != 0);
}

// Programa principal
int main() {
    string usuario, password;

    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contraseña: ";
    cin >> password;

    if (usuario == "admin" && password == "12345678") {
        menuAdmin();
    } else if (usuario == "comprador" && password == "abc123") {
        menuComprador();
    } else {
        cout << "Usuario o contraseña incorrectos.\n";
    }

    return 0;
}
