#include <iostream>
#include <cstdlib>
#include <locale>
#include <limits> // Includes DBL_Max
using namespace std;
int main(){
	setlocade(LC_ALL, "es_ES.UTF-8");
	int pass, opcion = 0, campos = 4, tamano = 4, i = 0, j=0;
	string c;
	string Lista_productos [tamano][campos] = {
	{"1", "Chocolate", "22", "20lts"},
	{"2", "Vainilla", "27", "18lts"},
	{"3", "Fresa", "29", "12lts"},
	{"4", "Menta", "26", "17lts"}
	};
	do{
		cout << "Ingresa el usuario: ";
		cin >> c;
		cout << "Ingresa la contrasena: ";
		cin >> pass;
		if((c == "Jefazo") && ( pass == 1234)){
			cout << "Elige la opción deseada \n" << "1.-Productos" << "\n" <<  "2.-Venta" << "\n" <<"3.-Empleados" << "Registro Ventas" << "\n" << "4.-Salir";
			cin >> opcion;
			switch(opcion){
				case 1: 
				cout << "Lista de Productos\n" << "ID |    Nombre  |      Precio     |     Cantidad   \n" ;
				for(i = 0; i < campos; i++){
					
					for(j = 0; j < tamano; j++){
						cout << Lista_productos[i][j] << " | "; 
					}
					cout << "\n";
				}
				cout << "Manipulacion de Productos \n" << "1.-Agregar Producto" << "\n" <<  "2.-Eliminar Producto" << "\n" <<"3.Modificar Producto-" << "\n" << "4.-Salir";
				
			
				break;
				
				case 2: 
				break;
				
				case 3: 
				break;
				
				default:
					cout << "Opcion invalida";
					break;
				
			}
		} else if((c == "chambeador") && (pass == 1234)){
			
		} else {
			cout << "Usuario y/o contrasena incorrecto";
		}
	}while(opcion != 4);
	
	return 0;
}
