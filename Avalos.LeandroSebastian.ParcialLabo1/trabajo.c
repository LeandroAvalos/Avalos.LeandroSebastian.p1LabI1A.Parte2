#include <stdio.h>
#include <stdlib.h>
#include "fecha.h"
#include "trabajo.h"
#include "servicio.h"
#include "color.h"
#include "bicicleta.h"
#include "tipo.h"
#include "inputs.h"

int inicializarTrabajo(eTrabajo trabajos[], int tamTrab)
{
    int todoOk = 0;

    if(trabajos != NULL && tamTrab > 0)
    {
        for(int i = 0; i < tamTrab; i++)
        {
             trabajos[i].isEmpty = 1;
        }
        todoOk = 1;
    }
    return todoOk;
}

int buscarLibreTrabajo(eTrabajo trabajos[], int tamTrab)
{
    int indice = -1;

    if(trabajos != NULL && tamTrab > 0)
    {
        for(int i = 0; i < tamTrab; i++)
        {
            if(trabajos[i].isEmpty == 1)
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}

int altaTrabajo(eTrabajo trabajos[], int tamTrab , eServicio servicios[], int tamServ ,eBicicleta bicicletas[], int tamBic, eTipo tipos[],int tamTipo, eColor colores[], int tamColor, int* pIdTrabajo)
{
    int todoOk = 0;
    int indice;
    eTrabajo auxTrabajo;

    if(trabajos != NULL && tamTrab > 0 && servicios != NULL && tamServ > 0 && bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0 && pIdTrabajo != NULL)
    {
        system("cls");
        printf("                 *** Alta Trabajo ***                             \n");
        printf("------------------------------------------------------------------\n");
        indice = buscarLibreTrabajo(trabajos, tamTrab);
        if(indice == - 1)
        {
            printf("No hay lugar en el sistema\n");
        }
        else
        {
            auxTrabajo.id = *pIdTrabajo;
            (*pIdTrabajo)++;

            mostrarBicicletas(bicicletas, tamBic, colores, tamColor, tipos, tamTipo);
            printf("\nIngrese el Id de la bicicleta: \n");
            scanf("%d", &auxTrabajo.idBicicleta);
            fflush(stdin);
            while(!validarIdBicicleta(bicicletas, tamBic, auxTrabajo.idBicicleta))
            {
                printf("Error. Ingrese el Id de la bicicleta nuevamente: \n");
                scanf("%d", &auxTrabajo.idBicicleta);
                fflush(stdin);
            }
            trabajos[indice].idBicicleta = auxTrabajo.idBicicleta;

            mostrarServicios(servicios, tamServ);
            pedirEntero(&auxTrabajo.idServicio, "Ingrese el ID del servicio deseado.\n", "Error. Ingrese nuevamente el ID del servicio deseado\n", 20000, 20003);
            trabajos[indice].idServicio = auxTrabajo.idServicio;


            validarFecha(&auxTrabajo.fecha);

            auxTrabajo.isEmpty = 0;

            trabajos[indice] = auxTrabajo;
            todoOk = 1;
            printf("Alta de trabajo Exitosa!!!\n");
        }
        todoOk = 1;
    }
    return todoOk;
}

void mostrarUnTrabajo(eTrabajo unTrabajo, eBicicleta bicicletas[], int tamBic, eServicio servicios[], int tamServ, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    char descripcionServicio[20];
    char descripcionTipo[20];
    char descripcionColor[20];
    int indiceBiciAMostrar;


    if(bicicletas != NULL && tamBic > 0 && servicios != NULL && tamServ > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0)
    {
        indiceBiciAMostrar=buscarBicicletaId(bicicletas, tamBic, unTrabajo.idBicicleta);
        cargarDescripcionServicio(servicios, tamServ, unTrabajo.idServicio, descripcionServicio);
        cargarDescripcionColor(colores, tamColor, bicicletas[indiceBiciAMostrar].idColor, descripcionColor);
        cargarDescripcionTipo(tipos, tamTipo, bicicletas[indiceBiciAMostrar].idTipo, descripcionTipo);


        printf("%-15d%-16d%-15s%-18s%-11s%-16c%-15s%02d/%02d/%d\n",
        unTrabajo.id,
        bicicletas[indiceBiciAMostrar].id,
        bicicletas[indiceBiciAMostrar].marca,
        descripcionTipo,
        descripcionColor,
        bicicletas[indiceBiciAMostrar].material,
        descripcionServicio,
        unTrabajo.fecha.dia,
        unTrabajo.fecha.mes,
        unTrabajo.fecha.anio);

    }
}

int mostrarTrabajos(eTrabajo trabajos[], int tamTrab, eBicicleta bicicletas[], int tamBic, eServicio servicios[], int tamServ, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int flag = 1;
    int indiceBici;

    if(trabajos != NULL && tamTrab > 0 && bicicletas != NULL && tamBic > 0 && servicios != NULL && tamServ > 0 && colores != NULL && tamColor > 0 && tipos != NULL && tamTipo > 0)
    {
        system("cls");
        printf("     *** Listado de Trabajos ***\n");
        printf("--------------------------------------------------------------------------------------------------------------------\n");
        printf("IdTrabajo     |IdBici         |Marca         |Tipo             |Color     |Material       |Servicio      |DD/MM/AAAA\n");
        printf("--------------------------------------------------------------------------------------------------------------------\n");

        ordenarBicicletasTipoYMaterial(bicicletas, tamBic, tipos, tamTipo);
        for(int i = 0; i < tamTrab; i++)
        {
            indiceBici = buscarBicicletaId(bicicletas, tamBic, trabajos[i].idBicicleta);
            if(trabajos[i].isEmpty == 0 && bicicletas[indiceBici].isEmpty == 0)
            {
                mostrarUnTrabajo(trabajos[i], bicicletas, tamBic, servicios, tamServ, tipos, tamTipo, colores, tamColor);
                flag = 0;
            }
        }
        if(flag)
        {
            printf("     No hay trabajos para mostrar\n");
        }
        todoOk = 1;
    }
    return todoOk;
}

int mostrarTrabajosBicicletas(eTrabajo trabajos[], int tamTrab, eBicicleta bicicletas[], int tamBic, eServicio servicios[], int tamServ, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int flag = 1;
    int idBicicleta;

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0 && trabajos != NULL && tamTrab > 0 && servicios != NULL && tamServ > 0)
    {
        system("cls");
        printf("      *** Listado de trabajos a una bicicleta ***                 \n");
        printf("------------------------------------------------------------------\n");

        mostrarBicicletas(bicicletas, tamBic, colores, tamColor, tipos, tamTipo);
        printf("\nIngrese el Id de la bicicleta: \n");
        scanf("%d", &idBicicleta);
        fflush(stdin);
        while(!validarIdBicicleta(bicicletas, tamBic, idBicicleta))
        {
            printf("Error. Ingrese el Id de la bicicleta nuevamente: \n");
            scanf("%d", &idBicicleta);
            fflush(stdin);
        }

        printf("\nIdTrabajo     |IdBici         |Marca         |Tipo             |Color     |Material       |Servicio      |DD/MM/AAAA\n");
        printf("----------------------------------------------------------------------------------------------------------------------\n");

        for(int i = 0; i < tamTrab; i++)
        {
            if(trabajos[i].idBicicleta == idBicicleta && trabajos[i].isEmpty == 0)
            {
                mostrarUnTrabajo(trabajos[i], bicicletas, tamBic, servicios, tamServ, tipos, tamTipo, colores,tamColor);
                flag = 0;
            }
        }

        if(flag)
        {
            printf("No hay trabajos para mostrar.\n");
        }
        todoOk = 1;
    }
    return todoOk;
}

int sumarServiciosDeBicicletas(eTrabajo trabajos[], int tamTrab, eBicicleta bicicletas[], int tamBic, eServicio servicios[], int tamServ, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int flag = 1;
    int idBicicleta;
    int acumImportes = 0;

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0 && trabajos != NULL && tamTrab > 0 && servicios != NULL && tamServ > 0)
    {
        system("cls");
        printf("  *** Listado de Total gastado en servicios por bicicletas ***    \n");
        printf("------------------------------------------------------------------\n");

        mostrarBicicletas(bicicletas, tamBic, colores, tamColor, tipos, tamTipo);
        printf("\nIngrese el Id de la bicicleta: \n");
        scanf("%d", &idBicicleta);
        fflush(stdin);
        while(!validarIdBicicleta(bicicletas, tamBic, idBicicleta))
        {
            printf("Error. Ingrese el Id de la bicicleta nuevamente: \n");
            scanf("%d", &idBicicleta);
            fflush(stdin);
        }

        printf("\nIdTrabajo     |IdBici         |Marca         |Tipo             |Color     |Material       |Servicio      |DD/MM/AAAA\n");
        printf("----------------------------------------------------------------------------------------------------------------------\n");

        for(int i = 0; i < tamTrab; i++)
        {
            for(int j = 0; j < tamServ ; j++)
            {
                if(trabajos[i].idBicicleta == idBicicleta && trabajos[i].isEmpty == 0 && trabajos[i].idServicio == servicios[j].id)
                {
                    acumImportes += servicios[j].precio;
                    mostrarUnTrabajo(trabajos[i], bicicletas, tamBic, servicios, tamServ, tipos, tamTipo, colores,tamColor);
                    flag = 0;
                }
            }
        }

        if(flag)
        {
            printf("A esta bicicleta no se le realizo ningun servicio.\n");
        }
        else
        {
            printf("\nLa suma de los importes de los servicios que recibio esta bicicleta es: $%d\n", acumImportes);
        }

        todoOk = 1;
    }
    return todoOk;
}

int mostrarBicicletasPorServicio(eTrabajo trabajos[], int tamTrab, eBicicleta bicicletas[], int tamBic, eServicio servicios[], int tamServ, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int idServicio;
    int flag = 1;

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0 && trabajos != NULL && tamTrab > 0 && servicios != NULL && tamServ > 0)
    {
        system("cls");
        printf("        *** Listado de Bicicletas por servicios ***                      \n");
        printf("--------------------------------------------------------------------------------\n");

        mostrarServicios(servicios, tamServ);
        pedirEntero(&idServicio, "Ingrese el ID del servicio deseado.\n", "Error. Ingrese nuevamente el ID del servicio deseado\n", 20000, 20003);

        printf("\nIdTrabajo     |IdBici         |Marca         |Tipo             |Color     |Material       |Servicio      |DD/MM/AAAA\n");
        printf("----------------------------------------------------------------------------------------------------------------------\n");

        for(int i = 0; i < tamTrab; i++)
        {
            if(trabajos[i].idServicio == idServicio && trabajos[i].isEmpty == 0)
            {
                mostrarUnTrabajo(trabajos[i], bicicletas, tamBic, servicios, tamServ, tipos, tamTipo, colores,tamColor);
                flag = 0;
            }
        }

        if(flag)
        {
            printf("No hay servicios para mostrar.\n");
        }
        todoOk = 1;
    }
    return todoOk;
}

int mostrarServiciosPorFecha(eTrabajo trabajos[], int tamTrab, eBicicleta bicicletas[], int tamBic, eServicio servicios[], int tamServ, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    char descripcion[20];
    int flag = 1;
    eTrabajo auxTrabajo;
    int contador = 0;
    int indiceBici;

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0 && trabajos != NULL && tamTrab > 0 && servicios != NULL && tamServ > 0)
    {
        system("cls");
        printf("               *** Listado Servicios por fecha ***                      \n");
        printf("------------------------------------------------------------------------\n");

        validarFecha(&auxTrabajo.fecha);

        printf("\n|Servicio      |DD/MM/AAAA\n");
        printf("----------------------------\n");



        for(int i = 0; i < tamTrab; i++)
        {
            indiceBici = buscarBicicletaId(bicicletas, tamBic, trabajos[i].idBicicleta);
            if(trabajos[i].fecha.dia == auxTrabajo.fecha.dia && trabajos[i].fecha.mes == auxTrabajo.fecha.mes && trabajos[i].fecha.anio == auxTrabajo.fecha.anio && trabajos[i].isEmpty == 0 && bicicletas[indiceBici].isEmpty == 0)
            {
                cargarDescripcionServicio(servicios, tamServ, trabajos[i].idServicio, descripcion);
                contador++;
                printf("%s          %02d/%02d/%d\n",descripcion, auxTrabajo.fecha.dia, auxTrabajo.fecha.mes, auxTrabajo.fecha.anio);
                flag = 0;
            }
        }

        if(flag)
        {
            system("cls");
            printf("No hay servicios para mostrar en esta fecha.\n");
        }
        else
        {
            printf("\nEn esta fecha se realizaron %d servicio(s).\n",contador);
        }

        todoOk = 1;
    }
    return todoOk;
}
