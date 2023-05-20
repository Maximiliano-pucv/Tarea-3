#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "list.h"
#include "stack.h"
#include "hashMap.h"
#include "heap.h"


#define BARRA printf(" ------------------------------------------------------\n")
#define ENTER printf("\n");

typedef struct{
  char nombre[100];
  int prioridad;
  int visitado;
  int mostrado;
  List* precedentes;
}TareaInfo;

typedef struct
{
  int accion;
  char nombre[100];
  List *precedente;//hace referencia a que tarea precede si es que se hace tal accion

}TipoAccion;

void EstablecerTarea(List *lista,TareaInfo *accion)
{
  
  printf("Inserte el nombre de la tarea\n");
  
  TareaInfo *aux = (TareaInfo*)malloc(sizeof(TareaInfo));
  getchar();
  scanf("%99[^\n]s",aux ->nombre);
  
  aux ->precedentes = createList();
  
  printf("¿Cual es la prioridad de la tarea?\n");
  scanf("%i", &aux->prioridad);
  
  aux->visitado = 0;
  aux->mostrado = 0;
  
  accion = aux;
  
  printf("nombre = %s\nprioridad = %i\n", aux ->nombre, aux ->prioridad);//borra
    pushBack(lista, aux);
  
}

void* busqueda(char *cadena, List *lista){
  TareaInfo *aux = firstList(lista);
  while(aux != NULL){
    if(strcmp(cadena, aux -> nombre)== 0) return aux;
    aux = nextList(lista);
  }
  return NULL;
}

void EstablecerPrecedencia(List *lista)
{
  char tarea1[100],tarea2[100];
  printf("¿A que tarea le colocara una precedencia?\n");
  getchar();
  scanf("%99[^\n]s",tarea1);
  getchar();
  TareaInfo *listatarea1 = firstList(lista);
  
  bool encontrado = false;
  while((listatarea1 != NULL)&&(encontrado == false)){
    if(strcmp(listatarea1 -> nombre, tarea1)==0){
      encontrado = true;
      break;
    }
    listatarea1 = nextList(lista);
  }
  if(encontrado == true){
    printf("tarea 1 encontrado\n");
    bool encontrado2 = false;
    printf("¿Que tarea sera la precedencia?\n");
    scanf("%99[^\n]s",tarea2);
    getchar();
    TareaInfo *listatarea2 = firstList(lista);
    while((listatarea2 != NULL)&&(encontrado2 == false)){
      if(strcmp(listatarea2 -> nombre, tarea2)==0){
        encontrado2 = true;
        break;
      }
      listatarea2 = nextList(lista);
    }
      
    if(encontrado2 == true){
      pushBack(listatarea1 -> precedentes, listatarea2);
      printf("la operacion se realizo con exito\n");
    }else printf("la segunda tarea ingresada no se encuentra registrada\n");
  }else printf("la primera ingresada no se encuentra registrada\n");
  
}

void reiniciarConts(List * lista)
{
  TareaInfo *aux = firstList(lista);
  while(aux != NULL)
    {
      aux->mostrado--;
      aux->visitado--;
      aux = nextList(lista);
    }
}


void MostrarTareas(List *lista)
{
  Heap *heap = createHeap();//monticulo para ordenar las prioridades
  
  List *resultado = createList();//lo que dice el nombre, la lista ordenada (solo diosito sabe como se logro)
  
  TareaInfo * auxlista = firstList(lista);
  TareaInfo * precedente = NULL;
  TareaInfo * auxmostrado = NULL;
  while(true)
  {
    while(auxlista != NULL)
      {
        precedente = firstList(auxlista->precedentes);
        if(precedente == NULL && auxlista->visitado == 0)
        {
          auxlista->visitado++;
          heap_push(heap,auxlista,auxlista->prioridad);
        }
        else if(precedente!= NULL && auxlista->visitado == 0)
        {
          while(precedente != NULL)
            {
              if(precedente->mostrado == 0)
              {
                break;
              }
              precedente = nextList(auxlista->precedentes);
            }
          if(precedente == NULL)
          {
            auxlista->visitado++;
            heap_push(heap, auxlista, auxlista->prioridad);
          }
        }
        auxlista = nextList(lista);
        
        
      }
    if(heap_top(heap) == NULL)
    {
      break;
    }
    auxmostrado = heap_top(heap);
    auxmostrado->mostrado++;
    pushBack(resultado,auxmostrado);
    heap_pop(heap);
    auxlista = firstList(lista);
  }
  TareaInfo *auxresultados = firstList(resultado);
  while(auxresultados != NULL)
    {
      printf("Nombre : %s , Prioridad : %i",auxresultados->nombre,auxresultados->prioridad);
      if(firstList(auxresultados->precedentes) != NULL)
      {
        TareaInfo *PrecedR = firstList(auxresultados->precedentes);
        printf(" , Precedente ");
        while(PrecedR != NULL)
          {
            printf("%s ",PrecedR->nombre);
            PrecedR = nextList(auxresultados->precedentes);
          }
      }
      printf("\n");
      auxresultados = nextList(resultado);
    }
  printf("operacion hecha con exito\n");
  reiniciarConts(lista);
}  



void MarcarTarea (List * lista){
  char lectura[100];
  int pregunta;
  printf("que tarea desea marcar como completada?\n");
  getchar();
  scanf("%99[^\n]s", lectura);

  TareaInfo *tareamain = firstList(lista);
  
  bool encontrado = false;
  while(tareamain != NULL){
    TareaInfo *subtarea = firstList(tareamain->precedentes);
    while(subtarea != NULL){
      if(strcmp( subtarea-> nombre, lectura)==0){
        popCurrent(tareamain -> precedentes);
        encontrado = true;
        
      }
      subtarea = nextList(tareamain -> precedentes);
    }
    
    tareamain = nextList(lista);
  }
  TareaInfo *tareamain2 = firstList(lista);
  while(tareamain2 != NULL){
    if(strcmp( tareamain2-> nombre, lectura)==0){
      popCurrent(lista);
      encontrado = true;
    }
    tareamain2 = nextList(lista);
  }
  
  if(encontrado == true){
    printf("la tarea a sido completada con exito\n");
  }else printf("El elemento ingresado no se encuentra refistrado\n");
  
}
//borrar antes de entregar
void mirar (List * lista){
  TareaInfo *listamain = firstList(lista);
  while(listamain != NULL){
    printf("%s,%i \n",listamain-> nombre, listamain -> prioridad);
    printf("precedentes:\n");
    TareaInfo * listapre = firstList(listamain -> precedentes);
    while(listapre != NULL){
      printf("---%s\n",listapre -> nombre);
      
      listapre = nextList(listamain -> precedentes);
    }
    ENTER;
    listamain = nextList(lista);
  }
}
//importar datos
const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){
        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }
    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }
    return NULL;
}

List *importar(){
  List *listaaux;
  char archivo[100];
  printf("¿Qué archivo desea importar?\n");
  getchar();
  scanf("%99[^\n]",archivo);
  getchar();
  FILE *fp = fopen (archivo, "r");
  if(fp == NULL){
    printf("el archivo no existe\n");
    return NULL; 
  } 
  char linea[1024];
  int i;
  fgets (linea, 1023, fp);
  
  listaaux = createList();
  while (fgets (linea, 1023, fp) != NULL){
    i=0;
    TareaInfo *datos = malloc(sizeof(TareaInfo));
    char *aux = (char*)get_csv_field(linea, i);
    while(aux != NULL){
      aux = (char*)get_csv_field(linea, i);
      if(datos -> precedentes == NULL) datos -> precedentes = createList();
      if(i == 0){
        strcpy(datos -> nombre, aux);
      }else if(i == 1){
        datos ->prioridad = atoi(aux);
      }else{
        if(aux != NULL){
          pushFront(datos -> precedentes, aux);
        }
      }
      i++;
    }
    datos->mostrado = 0;
    datos->visitado = 0;
    pushFront( listaaux, datos);
  }
  printf("importacion exitosa\n");
  return listaaux;
}

//funciones para deshacer acciones

void borrarTarea(List* lista, TareaInfo*accion)
{
  while(lista != NULL)
  {
    if(busqueda(accion->nombre,lista) != NULL)
    {
      popCurrent(lista);
      printf("Tarea hecha con exito\n");
      return;
    }
    nextList(lista);
  }
}






int main(void) {
  //printf("Hello World\n");
  int seleccion;
  int Cant_Tarea = 0;//por alguna razon debe de existir
  List *lista =NULL;
  TareaInfo *accion = NULL;
  int numAccion = 0;
  while(true){
    BARRA;
    printf("|             💻¿QUÉ ACCIÓN DESEA REALIZAR?💻         |\n");
    BARRA;
    printf("|1. Agregar Tarea                                      |\n");
    printf("|2. Establecer precedencia entre tareas                |\n");
    printf("|3. Mostrar tareas por hacer                           |\n");
    printf("|4. Marcar tarea como completada (nombre)              |\n");
    printf("|5. Deshacer última acción                             |\n");
    printf("|6. Cargar datos de tareas desde un archivo de texto   |\n");
    printf("|7. Funcion defalult pa los desarrolladores            |\n");
    printf("|0. Terminar                                           |\n");
    BARRA;
     
    scanf("%i", &seleccion);

    switch(seleccion){

      case 1:
        ENTER;
        BARRA;
        printf("                    Agregar Tarea\n");
        BARRA;
        ENTER;
        if(lista == NULL)
        {
          lista = createList();
        }
        if(accion == NULL)
        {
          accion = (TareaInfo*)malloc(sizeof(TareaInfo));
        }
        EstablecerTarea(lista,accion);
        
        numAccion = 1;
        Cant_Tarea++;
        
      break;
      
      case 2:
        ENTER;
        BARRA;
        printf("          Establecer precedencia entre tareas\n");
        BARRA;
        ENTER;
        
        if((Cant_Tarea <2))
        {
          printf("No hay 2 o mas tareas para establecer precedencia entre ellas\n");
          break;
        }
        EstablecerPrecedencia(lista);
        
        
      break;
      
      case 3:
        ENTER;
        BARRA;
        printf("                Mostrar tareas por hacer\n");
        BARRA;
        ENTER;
        MostrarTareas(lista);
      break;
      
      case 4:
        ENTER;
        BARRA;
        printf("         Marcar tarea como completada (nombre)\n");
        MarcarTarea(lista);
        BARRA;
        ENTER;
      break;
      
      case 5:
        ENTER;
        BARRA;
        printf("                Deshacer última acción \n");
        BARRA;
        ENTER;
      break;
        
      case 6:
        ENTER;
        BARRA;
        printf("    Cargar datos de tareas desde un archivo de texto\n");
        lista = importar();
        Cant_Tarea =3;
        BARRA;
        ENTER;
      break;
      
      case 0:
        if(lista != NULL)
        {
          cleanList(lista);
        }
        printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
        printf("░░██████░░██████░░░█████░░░██████░██░░█████░░███████░\n");
        printf("░██░░░░░░░██░░░██░██░░░██░██░░░░░░██░██░░░██░██░░░░░░ \n");
        printf("░██░░░███░██████░░███████░██░░░░░░██░███████░███████░ \n");
        printf("░██░░░░██░██░░░██░██░░░██░██░░░░░░██░██░░░██░░░░░░██░ \n");
        printf("░░██████░░██░░░██░██░░░██░░██████░██░██░░░██░███████░ \n");
        printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
        printf("\n");  
        return 0;
      break;
      //funcion borrar despues
      case 7:
        ENTER;
        BARRA;
        printf("    Funcion defalult pa los desarrolladores\n");
        BARRA;
        ENTER;
        mirar(lista);
      break;
      
      default:
      ENTER;
      BARRA;
      printf("Seleccione un numero mostrado en el menu para continuar\n");
      BARRA;
      ENTER;
      break;
    }
  }
  return 0;
}