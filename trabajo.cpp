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
void ordenar();
void crearOrdenTrabajo();
void eliminar_registros();

int main() {
    int opc;
    do {
        printf("\n === MENU ===\n");
        printf("\n1. Crear Orden de Trabajo");
        printf("\n2. Agregar mas registros");
        printf("\n3. Visualizar registros existentes");
        printf("\n4. Ordenar");
        printf("\n5. Visualizar registros ordenados");
		printf("\n6. Eliminar registro");
        printf("\n7. Salir");
        printf("\nOpci�n: ");
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
                ordenar();
                break;
            case 5:
            	visualizar_ordenado();
            	break;
            case 6:
            	eliminar_registros();
            default:
                opc = 7;
                break;
        }
    } while (opc != 7);
    return 0;
}


void crearOrdenTrabajo() {
    OrdenTrabajo orden;
    char continuar;
    fd = fopen("orden_trabajo.dat", "wb");

    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de �rdenes de trabajo **** \n");
        return;
    } else {
        printf("\n==> Creando Orden de Trabajo <==\n");
        do {
            cout << "\nNumero de orden: ";
            cin >> orden.numero;
            cout << "Fecha (dia mes a�o): ";
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
        printf("\n*** Error al tratar de abrir el archivo de �rdenes de trabajo **** \n");
        return;
    } else {
        printf("\n==> Creando Orden de Trabajo <==\n");
        do {
            cout << "\nNumero de orden: ";
            cin >> orden.numero;
            cout << "Fecha (dia mes a�o): ";
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

/*void ordenar(OrdenTrabajo a[], int n){
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
*/

void ordBurbuja(OrdenTrabajo a[], int n) {
    int pasada, j;
    for (pasada = 0; pasada < n - 1; pasada++) {
        /* bucle externo controla la cantidad de pasadas */
        for (j = 0; j < n - pasada - 1; j++) {
            if (a[j].numero > a[j + 1].numero) { // Cambia este campo para ordenar por n�mero
                /* elementos desordenados, es necesario intercambio */
                OrdenTrabajo aux = a[j];
                a[j] = a[j + 1];
                a[j + 1] = aux;
            }
        }
    }
}

void ordenar() {
    OrdenTrabajo *ordenes = NULL; // Cambiar nullptr a NULL
    int count = 0;

    fd = fopen(direccion, "rb");
    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de �rdenes de trabajo **** \n");
        return;
    }

    // Contar el n�mero de registros
    fseek(fd, 0, SEEK_END);
    count = ftell(fd) / sizeof(OrdenTrabajo);
    fseek(fd, 0, SEEK_SET);

    // Asignar memoria para leer los registros
    ordenes = new OrdenTrabajo[count];
    fread(ordenes, sizeof(OrdenTrabajo), count, fd);
    fclose(fd);

    // Llamar al m�todo de ordenamiento burbuja
    ordBurbuja(ordenes, count); // Aseg�rate de pasar ambos argumentos

    // Guardar las �rdenes ordenadas en un nuevo archivo
    fd_ordenado = fopen(direccion_ordenado, "wb");
    if (fd_ordenado == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de �rdenes ordenadas **** \n");
        delete[] ordenes; // Liberar memoria
        return;
    }

    fwrite(ordenes, sizeof(OrdenTrabajo), count, fd_ordenado);
    fclose(fd_ordenado);
    delete[] ordenes; // Liberar memoria

    printf("\n�rdenes de trabajo ordenadas exitosamente.\n");
}

void visualizar_ordenado() {
    OrdenTrabajo orden;
    fd_ordenado = fopen(direccion_ordenado, "rb");

    if (fd_ordenado == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de �rdenes ordenadas **** \n");
        return;
    }
    printf("\n==> Visualizando Ordenes de Trabajo Ordenadas <==\n");
    while (fread(&orden, sizeof(OrdenTrabajo), 1, fd_ordenado)) {
        cout << "Numero de orden: " << orden.numero << ", "
             << "Fecha: " << orden.fecha.dia << "/" 
             << orden.fecha.mes << "/" << orden.fecha.ano << ", "
             << "Responsable: " << orden.responsable.nombre << ", "
             << "ID: " << orden.responsable.id << endl;
    }
    fclose(fd_ordenado);
}
void eliminar_registros() {
    int numeroOrden;
    cout << "Ingrese el n�mero de orden a eliminar: ";
    cin >> numeroOrden;

    // Abrir el archivo y contar registros
    fd = fopen(direccion, "rb");
    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de �rdenes de trabajo **** \n");
        return;
    }

    // Contar el n�mero de registros
    fseek(fd, 0, SEEK_END);
    int count = ftell(fd) / sizeof(OrdenTrabajo);
    fseek(fd, 0, SEEK_SET);

    // Crear un arreglo para almacenar los registros existentes
    OrdenTrabajo *ordenes = new OrdenTrabajo[count];
    fread(ordenes, sizeof(OrdenTrabajo), count, fd);
    fclose(fd);

    // Eliminar el registro correspondiente
    bool encontrado = false;
    for (int i = 0; i < count; i++) {
        if (ordenes[i].numero == numeroOrden) {
            encontrado = true;
            // Desplazar los registros hacia la izquierda
            for (int j = i; j < count - 1; j++) {
                ordenes[j] = ordenes[j + 1];
            }
            count--; // Reducir el conteo de registros
            break; // Salir del bucle al encontrar el registro
        }
    }

    if (!encontrado) {
        cout << "Registro no encontrado." << endl;
        delete[] ordenes; // Liberar memoria
        return;
    }

    // Guardar los registros restantes en el archivo
    fd = fopen(direccion, "wb");
    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de �rdenes de trabajo **** \n");
        delete[] ordenes; // Liberar memoria
        return;
    }

    fwrite(ordenes, sizeof(OrdenTrabajo), count, fd);
    fclose(fd);
    delete[] ordenes; // Liberar memoria

    cout << "Registro eliminado exitosamente." << endl;
}
