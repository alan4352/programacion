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
struct Investigador {
char nombre[10];
char especialidad[20];
};
struct ProyectoInvestigacion {
char titulo[15];
Fecha fechaInicio;
Investigador lider;
int ID;
};

void crear();
void agregar();
void visualizar();
void visualizar_ordenado();
void ordBurbuja(ProyectoInvestigacion a[], int n);
void ordenar();
void crearProyecto();
void eliminar_registros();

int main() {
    int opc;
    do {
        printf("\n === MENU ===\n");
        printf("\n1. Crear Proyecto de investigación");
        printf("\n2. Agregar mas registros");
        printf("\n3. Visualizar registros existentes");
        printf("\n4. Ordenar");
        printf("\n5. Visualizar registros ordenados");
		printf("\n6. Eliminar registro");
        printf("\n7. Salir");
        printf("\nOpción: ");
        scanf("%i", &opc);
        switch (opc) {
            case 1: 
                crearProyecto();
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


void crearProyecto() {
    ProyectoInvestigacion proy;
    char continuar;
    fd = fopen("Proyecto_investigacion.dat", "wb");

    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de proyectos de investigacion **** \n");
        return;
    } else {
        printf("\n==> Creando Proyecto de Investigacion <==\n");
        do {
            cout << "\nEspecialidad del investigador: ";
            cin >> proy.lider.especialidad;
            cout << "Fecha (dia mes año): ";
            cin >> proy.fechaInicio.dia >> proy.fechaInicio.mes >> proy.fechaInicio.ano;
            cout << "Nombre del responsable: ";
            fflush(stdin);
            gets(proy.lider.nombre);
            cout << "Titulo del investigador: ";
            cin >> proy.titulo;
			cout << "ID del investigador: ";
            cin >> proy.ID;

            fwrite(&proy, sizeof(ProyectoInvestigacion), 1, fd);
            printf("\n>> Desea ingresar otro proyecto? (Si-s No-n): ");
            fflush(stdin);
            scanf("%c", &continuar);
        } while ((continuar == 's') || (continuar == 'S'));
    }
    fclose(fd);
}


void agregar() {
    char continuar;
    ProyectoInvestigacion proy;
    fd = fopen(direccion, "ab+");

         if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de proyectos de investigacion **** \n");
        return;
    } else {
        printf("\n==> Creando Proyecto de Investigacion <==\n");
        do {
             cout << "\nEspecialidad del investigador: ";
            cin >> proy.lider.especialidad;
            cout << "Fecha (dia mes año): ";
            cin >> proy.fechaInicio.dia >> proy.fechaInicio.mes >> proy.fechaInicio.ano;
            cout << "Nombre del responsable: ";
            gets(proy.lider.nombre);
            cout << "Titulo del investigador: ";
            cin >> proy.titulo;
			cout << "ID del investigador: ";
            cin >> proy.ID;
            
            fwrite(&proy, sizeof(ProyectoInvestigacion), 1, fd);
            printf("\n>> Desea ingresar otrao proyecto? (Si-s No-n): ");
            fflush(stdin);
            scanf("%c", &continuar);
        } while ((continuar == 's') || (continuar == 'S'));
    }
    fclose(fd);
}

void visualizar() {
    int registro = 0;
    ProyectoInvestigacion proy;
    fd = fopen(direccion, "rb");
    
    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo ***\n");
        return;
    } else {
        fread(&proy, sizeof(ProyectoInvestigacion), 1, fd);
        
        printf("\n ** Mostrando datos del archivo ProyectoInvestigacion **\n");
        printf("-------------------------------------------------------------\n");
        printf("|Reg.|    Nombre   | Especialidad |     Fecha     | titulo |\n");
        printf("-------------------------------------------------------------");
        
        while (!feof(fd)) {
            registro++;
            printf("\n|%4i", registro);
            printf("| %10s ", proy.lider.nombre);
            printf("| %2i ", proy.lider.especialidad);
        	printf("| %10s ", proy.fechaInicio);
            printf("| %2i ", proy.titulo);
            printf("| %2i ", proy.ID);
            fread(&proy, sizeof(ProyectoInvestigacion), 1, fd);
        }
    }
    fclose(fd);
}


void ordBurbuja(ProyectoInvestigacion a[], int n) {
    int pasada, j;
    for (pasada = 0; pasada < n - 1; pasada++) {
        /* bucle externo controla la cantidad de pasadas */
        for (j = 0; j < n - pasada - 1; j++) {
            if (a[j].ID > a[j + 1].ID) { // Cambia este campo para ordenar por número
                /* elementos desordenados, es necesario intercambio */
                ProyectoInvestigacion aux = a[j];
                a[j] = a[j + 1];
                a[j + 1] = aux;
            }
        }
    }
}

void ordenar() {
    ProyectoInvestigacion *proyectos = NULL; // Cambiar nullptr a NULL
    int count = 0;

    fd = fopen(direccion, "rb");
    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de proyecto de investigacion **** \n");
        return;
    }

    // Contar el número de registros
    fseek(fd, 0, SEEK_END);
    count = ftell(fd) / sizeof(ProyectoInvestigacion);
    fseek(fd, 0, SEEK_SET);

    // Asignar memoria para leer los registros
    proyectos = new ProyectoInvestigacion[count];
    fread(proyectos, sizeof(ProyectoInvestigacion), count, fd);
    fclose(fd);

    // Llamar al método de ordenamiento burbuja
    ordBurbuja(proyectos, count); // Asegúrate de pasar ambos argumentos

    // Guardar las órdenes ordenadas en un nuevo archivo
    fd_ordenado = fopen(direccion_ordenado, "wb");
    if (fd_ordenado == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de órdenes ordenadas **** \n");
        delete[] proyectos; // Liberar memoria
        return;
    }

    fwrite(proyectos, sizeof(ProyectoInvestigacion), count, fd_ordenado);
    fclose(fd_ordenado);
    delete[] proyectos; // Liberar memoria

    printf("\nÓrdenes de trabajo ordenadas exitosamente.\n");
}

void visualizar_ordenado() {
    ProyectoInvestigacion proy;
    fd_ordenado = fopen(direccion_ordenado, "rb");

    if (fd_ordenado == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de órdenes ordenadas **** \n");
        return;
    }
    printf("\n==> Visualizando Ordenes de Trabajo Ordenadas <==\n");
    while (fread(&proy, sizeof(ProyectoInvestigacion), 1, fd_ordenado)) {
        cout << "Numero de orden: " << proy.lider.especialidad << ", "
             << "Fecha: " << proy.fechaInicio.dia << "/" 
             << proy.fechaInicio.mes << "/" << proy.fechaInicio.ano << ", "
             << "Responsable: " << proy.lider.nombre << ", "
             << "ID: " << proy.ID << endl  << ", "
              << "Titulo: " << proy.titulo;
    }
    fclose(fd_ordenado);
}
void eliminar_registros() {
    int ID;
    cout << "Ingrese la ID de la investigacion: ";
    cin >> ID;

    // Abrir el archivo y contar registros
    fd = fopen(direccion, "rb");
    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de órdenes de trabajo **** \n");
        return;
    }

    // Contar el número de registros
    fseek(fd, 0, SEEK_END);
    int count = ftell(fd) / sizeof(ProyectoInvestigacion);
    fseek(fd, 0, SEEK_SET);

    // Crear un arreglo para almacenar los registros existentes
    ProyectoInvestigacion *proyectos = new ProyectoInvestigacion[count];
    fread(proyectos, sizeof(ProyectoInvestigacion), count, fd);
    fclose(fd);

    // Eliminar el registro correspondiente
    bool encontrado = false;
    for (int i = 0; i < count; i++) {
        if (proyectos[i].ID == ID) {
            encontrado = true;
            // Desplazar los registros hacia la izquierda
            for (int j = i; j < count - 1; j++) {
                proyectos[j] = proyectos[j + 1];
            }
            count--; // Reducir el conteo de registros
            break; // Salir del bucle al encontrar el registro
        }
    }

    if (!encontrado) {
        cout << "Registro no encontrado." << endl;
        delete[] proyectos; // Liberar memoria
        return;
    }

    // Guardar los registros restantes en el archivo
    fd = fopen(direccion, "wb");
    if (fd == NULL) {
        printf("\n*** Error al tratar de abrir el archivo de órdenes de trabajo **** \n");
        delete[] proyectos; // Liberar memoria
        return;
    }

    fwrite(proyectos, sizeof(ProyectoInvestigacion), count, fd);
    fclose(fd);
    delete[] proyectos; // Liberar memoria

    cout << "Registro eliminado exitosamente." << endl;
}
