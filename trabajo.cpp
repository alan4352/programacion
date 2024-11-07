#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

FILE *fd;
FILE *fd_ordenado;
char direccion[] = "datos.dat";
char direccion_ordenado[] = "ordenado.dat";

struct Fecha {
    int dia;
    int mes;
    int ano;
};

struct Empleado {
    char nombre[10];
    int id;
};

struct OrdenTrabajo {
    int numero;
    Fecha fecha;
    Empleado responsable;
};

void crear();
void agregar();
void visualizar();
void visualizar_ordenado();
void ordBurbuja(OrdenTrabajo a[], int n);
void ordenar_archivo();
void crearOrdenTrabajo();

int main() {
    int opc;
    do {
        printf("\n === MENU ===\n");
        printf("\n1. Crear Orden de Trabajo");
        printf("\n2. Agregar mas registros");
        printf("\n3. Visualizar registros existentes");
        printf("\n4. Ordenar");
        printf("\n5. Visualizar registros ordenados");
        printf("\n6. Salir");
        printf("\nOpción: ");
        scanf("%i", &opc);
        switch (opc) {
            case 1: 
                crearOrdenTrabajo();
                break;
            case 2: 
                agregar();
                break;
            case 3: 
                visualizar();
                break;
            case 4: 
                
                break;
            case 5:
            	
            	break;
            default:
                opc = 6;
                break;
        }
    } while (opc != 6);
    return 0;
}


void crearOrdenTrabajo() {
    OrdenTrabajo orden;
    char continuar;
    fd = fopen("orden_trabajo.dat", "wb");

    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de órdenes de trabajo **** \n");
        return;
    } else {
        printf("\n==> Creando Orden de Trabajo <==\n");
        do {
            cout << "\nNumero de orden: ";
            cin >> orden.numero;
            cout << "Fecha (dia mes año): ";
            cin >> orden.fecha.dia >> orden.fecha.mes >> orden.fecha.ano;
            cout << "Nombre del responsable: ";
            fflush(stdin);
            gets(orden.responsable.nombre);
            cout << "ID del responsable: ";
            cin >> orden.responsable.id;

            fwrite(&orden, sizeof(OrdenTrabajo), 1, fd);
            printf("\n>> Desea ingresar otra orden de trabajo? (Si-s No-n): ");
            fflush(stdin);
            scanf("%c", &continuar);
        } while ((continuar == 's') || (continuar == 'S'));
    }
    fclose(fd);
}


void agregar() {
    char continuar;
    OrdenTrabajo orden;
    fd = fopen(direccion, "ab+");

        if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de órdenes de trabajo **** \n");
        return;
    } else {
        printf("\n==> Creando Orden de Trabajo <==\n");
        do {
            cout << "\nNumero de orden: ";
            cin >> orden.numero;
            cout << "Fecha (dia mes año): ";
            cin >> orden.fecha.dia >> orden.fecha.mes >> orden.fecha.ano;
            cout << "Nombre del responsable: ";
            fflush(stdin);
            gets(orden.responsable.nombre);
            cout << "ID del responsable: ";
            cin >> orden.responsable.id;

            fwrite(&orden, sizeof(OrdenTrabajo), 1, fd);
            printf("\n>> Desea ingresar otra orden de trabajo? (Si-s No-n): ");
            fflush(stdin);
            scanf("%c", &continuar);
        } while ((continuar == 's') || (continuar == 'S'));
    }
    fclose(fd);
}

void visualizar() {
    int registro = 0;
    OrdenTrabajo orden;
    fd = fopen(direccion, "rb");
    
    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo ***\n");
        return;
    } else {
        fread(&orden, sizeof(OrdenTrabajo), 1, fd);
        
        printf("\n ** Mostrando datos del archivo OrdenTrabajo **\n");
        printf("---------------------------------------------------\n");
        printf("|Reg.|    Nombre   | Id |     Fecha     | Numero |\n");
        printf("---------------------------------------------------");
        
        while (!feof(fd)) {
            registro++;
            printf("\n|%4i", registro);
            printf("| %10s ", orden.responsable.nombre);
            printf("| %2i ", orden.responsable.id);
        	printf("| %10s ", orden.fecha);
            printf("| %2i ", orden.numero);
            fread(&orden, sizeof(OrdenTrabajo), 1, fd);
        }
    }
    fclose(fd);
}

void Ordenar(OrdenTrabajo a[], int n){
	int pasada, j, comparacion;
	OrdenTrabajo aux;
	for(pasada = 0; pasada < n - 1; pasada++){
		for(j = 0; j < n - pasada - 1; j++){
			comparacion = strcmp(a[j].responsable.nombre, a[j + 1].responsable.nombre);
			if (comparacion > 0){
				aux = a[j];
				a[j] = a[j + 1];
				a[j + 1] = aux;
			}
		}
	}
}
