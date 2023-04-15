#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defino estructuras
struct {
    int TareaID; //Numerado en ciclo iterativo 
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

//Defino funciones y procedeiminetos
void inicializarNull(Tarea **arreglo, int cantidad);
void cargarTareas(Tarea **arreglo, int cantidad, char *buff);
void mostrarTarea(Tarea *arreglo);
Tarea* BuscaTareaPorPalabra(Tarea **arreglo, int cantidad, char *comparar);
Tarea* BuscaTareaPorId(Tarea **arreglo, int cantidad, int comparar);

int main(){
    //Declaracion variables
    int cantTareas, respuesta, j=0, consultarID;
    Tarea **TareasPendientes, **TareasRealizadas, *buscada;
    char *buff= (char *) malloc(sizeof(char) * 500), *consultarClave;

    //Apartado 1
    puts("------º------º------º------º------º------");
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);

    //Apartado 2
    TareasPendientes = (Tarea **) malloc(sizeof(Tarea *) * cantTareas);
    inicializarNull(TareasPendientes, cantTareas);

    //Apartado 3
    puts("------º------º------º------º------º------");
    cargarTareas(TareasPendientes, cantTareas, buff);

    //Apartado 4
    TareasRealizadas = (Tarea **) malloc(sizeof(Tarea *) * cantTareas);
    inicializarNull(TareasRealizadas, cantTareas);
    for (int i = 0; i < cantTareas; i++)
    {
        puts("------ Tarea ------");
        mostrarTarea(TareasPendientes[i]);
        printf("Tarea Realizada? (0=no, 1=si): ");
        scanf("%d", &respuesta);
        if (respuesta)
        {
            TareasRealizadas[j] = TareasPendientes[i];
            TareasPendientes[i] = NULL;
            j++;
        }   
    }

    //Apartado 5
    puts("------ Tareas Realizadas ------");
    for (int i = 0; TareasRealizadas[i] != NULL && i < cantTareas; i++)
    {
        mostrarTarea(TareasRealizadas[i]);
    }
    puts("------ Tareas Pendientes ------");
    for (int i = 0; i < cantTareas; i++)
    {
        if (TareasPendientes[i] != NULL)
        {
            mostrarTarea(TareasPendientes[i]);
        }
    }

    //Apartado 9
    puts("------ Consultar Tarea ------");
    printf("Ingrese el ID de la tarea: ");
    scanf("%d", &consultarID);
    buscada = BuscaTareaPorId(TareasRealizadas, cantTareas, consultarID);
    mostrarTarea(buscada);
    printf("Ingrese la palabra clave: ");
    gets(consultarClave);
    buscada = BuscaTareaPorPalabra(TareasRealizadas, cantTareas, consultarClave);
    mostrarTarea(buscada);

    //Libero reserva de memoria
    free(buff);
    for (int i = 0; i < cantTareas; i++)
    {
        free(TareasPendientes[i]);
        free(TareasRealizadas[i]);
    }
    free(TareasPendientes);
    free(TareasRealizadas);

    return 0;
}
//Desarrollo funciones y procedimientos
void inicializarNull(Tarea **arreglo, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        arreglo[i] = NULL;
    }
}
void cargarTareas(Tarea **arreglo, int cantidad, char *buff)
{
    for (int i = 0; i < cantidad; i++)
    {
        puts("------ Tarea ------");
        arreglo[i] = (Tarea *) malloc(sizeof(Tarea));
        arreglo[i]->TareaID = i+1;
        fflush(stdin);
        printf("Ingrese descripcion: ");
        gets(buff);
        arreglo[i]->Descripcion = (char *) malloc(sizeof(char) * (strlen(buff)+1));
        strcpy(arreglo[i]->Descripcion, buff);
        printf("Ingrese la duracion (10-100): ");
        scanf("%d", &arreglo[i]->Duracion);
    }
}
void mostrarTarea(Tarea *arreglo)
{
    printf("TareaID: %d\n", arreglo->TareaID);
    printf("Descripcion: %s\n", arreglo->Descripcion);
    printf("Duracion: %d\n", arreglo->Duracion);  
}
Tarea* BuscaTareaPorId(Tarea **arreglo, int cantidad, int comparar){
    Tarea *aux = NULL;
    for (int i = 0; i < cantidad && aux == NULL; i++)
    {
        if (arreglo[i]->TareaID == comparar)
        {
            aux = arreglo[i];
        }
    }
    return aux;
}
Tarea* BuscaTareaPorPalabra(Tarea **arreglo, int cantidad, char *comparar)
{
    Tarea *aux = NULL;
    for (int i = 0; i < cantidad && aux == NULL; i++)
    {
        if (strstr(arreglo[i]->Descripcion,comparar) != NULL)
        {
            aux = arreglo[i];
        }
    }
    return aux;
}