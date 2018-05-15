/**Definir una estructura que represente una persona, con los campos nombre, edad, dni y un
flag de estado.
Hacer un programa que defina un array de 20 ítems de esta estructura y con un menú como el
siguiente:
1. Agregar una persona
2. Borrar una persona
3. Imprimir lista ordenada por nombre
4. Imprimir gráfico de edades
Se utilizará el campo de estado para indicar si el ítem del array esta ocupado o no.
El gráfico deberá ser un gráfico de barras en donde se agruparán 3 barras:
• Menores de 18
• De 19 a 35
• Mayores de 35.
En el eje Y se marcarán la cantidad de personas en el grupo, y en el eje X el grupo
Ejemplo:
*
* *
* * *
* * *
* * *
* * *
 <18 19-35 >35
Gráfico para una estadística de 6 personas con edad menor a 18, 4 personas con edades entre
19 y 35, y 5 personas con edades mayores a 35.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "utn.h"
#define QTY_Persona 20

typedef struct {
    char nombre[50];
    int dni;
    int edad;
    int estado;
}persona;

void inicializarPersonas(persona arrayDePersonas[],int cantidadDeElementos, int valor);
int buscarPrimerOcurrencia(persona arrayDePersonas[],int cantidadDeElementos, int valor);
void graficosEdades(persona lista[], int tam);



int main()
{
    persona arrayDePersonas[QTY_Persona];
    persona auxiliarPersona;
    char auxiliarNombreStr[50];
    char auxiliarDniStr[50];
    char auxiliarEdadStr[1];
    int aux_Dni;
    int aux_Edad;

    int indiceLugarLibre;
    int indiceResultadoBusqueda;
    int opcion=0;

    int i,j;

    inicializarPersonas(arrayDePersonas,QTY_Persona,-1);/**SE INDICA CON -1 QUE ESA POSICION ESTA VACIA*/
    while(opcion !=6 )
    {
        opcion=getInt("\n\n\n1 - AGREGAR PERSONA\n2 - BORRAR PERSONA\n3 - MODIFICAR POR DNI\n4 - LISTAR \n5 - ORDENAR\n6 - SALIR\n\n ");
        switch(opcion)
        {
            case 1:
                    indiceLugarLibre = buscarPrimerOcurrencia(arrayDePersonas,QTY_Persona,-1);
                    if(indiceLugarLibre == -1)
                    {
                        printf("\n\nNO QUEDAN LUGARES LIBRES!!\n");
                        break;
                    }
                    printf("\nALTA\n");
                    if(!getStringLetras("Ingrese el nombre: ",auxiliarNombreStr))
                    {
                        printf("EL NOMBRE DEBE ESTAR COMPUESTO SOLO POR LETRAS \n");
                        break;
                    }
                    if(!getStringNumeros("Ingrese Dni: ",auxiliarDniStr))
                    {
                        printf("El DNI DEBE SER NUMERICO: \n");
                        break;
                    }
                    aux_Dni = atoi(auxiliarDniStr);
                    if(buscarPrimerOcurrencia(arrayDePersonas,QTY_Persona,aux_Dni)!=-1)
                    {
                        printf("\n\nEL DNI YA EXISTE!!!\n");
                        break;
                    }
                    if(!getStringNumeros("Ingrese Edad ",auxiliarEdadStr))
                    {
                        printf("LA EDAD DEBE SER NUMERICA: \n");
                    }
                    aux_Edad = atoi(auxiliarEdadStr);

                    strcpy(arrayDePersonas[indiceLugarLibre].nombre,auxiliarNombreStr);
                    arrayDePersonas[indiceLugarLibre].dni = aux_Dni;
                    arrayDePersonas[indiceLugarLibre].edad =aux_Edad;
                    break;

            case 2:
                if (!getStringNumeros("Ingrese el DNI a dar de baja: ",auxiliarDniStr))
                {
                    printf("El DNI DEBE SER NUMERICO \n ");
                    break;
                }
                indiceResultadoBusqueda = buscarPrimerOcurrencia(arrayDePersonas,QTY_Persona,atoi(auxiliarDniStr));
                if (indiceResultadoBusqueda == -1)
                {
                    printf("\n\nNO SE ENCUENTRA ESE DNI\n");
                    break;
                }
                arrayDePersonas[indiceResultadoBusqueda].dni = -1;
                break;

            case 3:
                if (!getStringNumeros("Ingrese el DNI a modificar: ",auxiliarDniStr))
                {
                    printf("EL DNI DEBE SER NUMERICO ");
                    break;
                }
                indiceResultadoBusqueda = buscarPrimerOcurrencia(arrayDePersonas,QTY_Persona,atoi(auxiliarDniStr));
                if(indiceResultadoBusqueda == -1)
                {
                    printf("NO SE ENCUENTRA ESE DNI ");
                    break;
                }
                if(!getStringLetras("Ingrese el nombre: ",auxiliarNombreStr))//si el dni existe, le pedimos el nombre
                {
                    printf("El NOMBRE DEBE ESTAR COMPUESTO SOLO POR LETRAS\n");
                    break;
                }
                strcpy(arrayDePersonas[indiceResultadoBusqueda].nombre,auxiliarNombreStr);
                break;

            case 4:

                graficosEdades(arrayDePersonas,QTY_Persona);
                break;
            case 5:
                printf("\nORDENAR\n");
                for(i=0; i <QTY_Persona - 1;i++)
                {
                    if(arrayDePersonas[i].dni == -1)
                    {
                        continue;
                    }
                    for(j=i+1;j<QTY_Persona;j++)
                    {
                        if(arrayDePersonas[j].dni == -1)
                        {
                            continue;
                        }
                        if(strcmp(arrayDePersonas[i].nombre,arrayDePersonas[j].nombre)>0)
                        {
                            auxiliarPersona = arrayDePersonas[j];
                            arrayDePersonas[j] =arrayDePersonas[i];
                            arrayDePersonas[i]=auxiliarPersona;

                        }
                    }
                }
                break;

        }
    }



    return 0;
}
void inicializarPersonas(persona arrayDePersonas[],int cantidadDeElementos, int valor)//recibe el array de personas, la cantidad de elementos que tiene el array y valor con el cual va a ser inicializado;
{
    int i;
    for(i=0;i<cantidadDeElementos;i++)//recorro con un for desde cero hasta cantidad de elementos
    {
        arrayDePersonas[i].dni = valor;//en el array de personas en la posicion i que va a ir tomando los diferentes valores, accedo al dni de cada persona y en el coloco el valor que recibe por parametro
        //utilizo el -1 para indicar las posiciones libres
    }
}
int buscarPrimerOcurrencia(persona arrayDePersonas[],int cantidadDeElementos, int valor)
{
    int i;
    for(i=0;i<cantidadDeElementos;i++)
    {
        if(arrayDePersonas[i].dni == valor)
        {
            return i;
        }
    }
    return -1;
}
/** \brief graico donde se muestra las edades de las personas de altas
 * \param   lista es el vector de estructura a ser explorado
 * \param tam es tamaño del vector lista
 * \return  void
 *
 */
void graficosEdades(persona lista[], int tam)
{
    int contador18=0;
    int contador19a35=0;
    int contador35=0;
    char item = '*';

    printf("------grafico de edades -------");

    system("cls");

    for(int i = 0; i<tam; i++ )
    {
        if(lista[i].edad <19 && lista[i].estado==0)
        {
            contador18++;
            printf("%c\n", item);
        }
        else if(lista[i].edad >18 && lista[i].edad <36 && lista[i].estado==0)
        {
            contador19a35++;
            printf("          %c\n",item);
        }
        else if(lista[i].edad>35 && lista[i].estado==0)
        {
            contador35++;
            printf("                     %c\n",item);
        }
    }

    printf("<18      19-35      >35\n");

}
