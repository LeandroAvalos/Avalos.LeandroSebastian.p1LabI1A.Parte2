#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "tipo.h"
#include "color.h"
#include "bicicleta.h"
#include <string.h>
#include <ctype.h>

int inicializarBiciletas(eBicicleta bicicletas[], int tamBic)
{
    int todoOk = 0;

    if(bicicletas != NULL && tamBic > 0)
    {
        for(int i = 0; i < tamBic; i++)
        {
             bicicletas[i].isEmpty = 1;
        }
        todoOk = 1;
    }
    return todoOk;
}

int buscarLibreBicicleta(eBicicleta biciletas[], int tamBic)
{
    int indice = -1;

    if(biciletas != NULL && tamBic > 0)
    {
        for(int i = 0; i < tamBic; i++)
        {
            if(biciletas[i].isEmpty == 1)
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}

int buscarBicicletaId(eBicicleta bicicleta[], int tamBic , int idBici)
{
    int seEncontro = -1;

    if(bicicleta != NULL && tamBic > 0)
    {
        for(int i = 0; i < tamBic; i++)
        {
            if(bicicleta[i].id == idBici && bicicleta[i].isEmpty == 0)
            {
                seEncontro = i;
                break;
            }
        }
    }
    return seEncontro;
}

int altaBicicleta(eBicicleta bicicletas[], int tamBic, eTipo tipos[],int tamTipo, eColor colores[], int tamColor, int* pIdBicicleta)
{
    int todoOk = 0;
    int indice;
    eBicicleta auxBicicleta;

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0 && pIdBicicleta != NULL)
    {
        system("cls");
        printf("              *** Alta Bicicleta ***                  \n");
        printf("------------------------------------------------------\n");
        indice = buscarLibreBicicleta(bicicletas, tamBic);
        if(indice == - 1)
        {
            printf("No hay lugar en el sistema\n");
        }
        else
        {
            auxBicicleta.id = *pIdBicicleta;
            (*pIdBicicleta)++;

            pedirCadena(auxBicicleta.marca, "Ingrese la marca de la bicicleta (hasta 20 caracteres)\n", "Error. Ingrese nuevamente la marca de la bicicleta (hasta 20 caracteres)\n", 20);
            strcpy(bicicletas[indice].marca, auxBicicleta.marca);

            mostrarTipos(tipos, tamTipo);
            pedirEntero(&auxBicicleta.idTipo, "Ingrese el ID del tipo deseado.\n", "Error. Ingrese nuevamente el ID del tipo deseado\n", 1000, 1003);
            bicicletas[indice].idTipo = auxBicicleta.idTipo;

            mostrarColores(colores, tamColor);
            pedirEntero(&auxBicicleta.idColor, "Ingrese el ID del color deseado.\n", "Error. Ingrese nuevamente el ID del color deseado\n", 5000, 5004);
            bicicletas[indice].idColor = auxBicicleta.idColor;

            pedirCaracter(&auxBicicleta.material, "Ingrese el material de la bicicleta(c: Carbono, a: Aluminio)\n", "Error. Ingrese nuevamente el material de la bicicleta(c: Carbono, a: Aluminio)\n",'c', 'a');
            auxBicicleta.material = toupper(auxBicicleta.material);
            bicicletas[indice].material = auxBicicleta.material;

            auxBicicleta.isEmpty = 0;

            bicicletas[indice] = auxBicicleta;
            printf("Alta Exitosa!!!\n");
            todoOk = 1;
        }
    }
    return todoOk;
}

int bajaBicicleta(eBicicleta bicicletas[], int tamBic , eTipo tipos[],int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int idBicicleta;
    int indiceBicicleta;
    char respuestaBorrar;

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0)
    {
        system("cls");
        printf("              *** Baja de Bicicleta ***                           \n");
        printf("------------------------------------------------------------------\n");
        mostrarBicicletas(bicicletas, tamBic, colores, tamColor, tipos, tamTipo);
        printf("\nIngrese su ID: \n");
        scanf("%d", &idBicicleta);

        indiceBicicleta = buscarBicicletaId(bicicletas, tamBic , idBicicleta);

        if(indiceBicicleta == -1)
        {
            printf("El ID ingresado no existe.\n");
        }
        else
        {
            printf("---------------------------------------------------------------\n");
            printf("Id     |Marca            |Tipo             |Color     |Material\n");
            printf("---------------------------------------------------------------\n\n");
            mostrarBicicleta(bicicletas[indiceBicicleta], colores, tamColor, tipos, tamTipo);

            printf("\nEsta seguro que desea borrar a esta bicicleta del sistema? (s: SI y n: NO)\n");
            fflush(stdin);
            scanf("%c", &respuestaBorrar);
            respuestaBorrar = tolower(respuestaBorrar);
            while(respuestaBorrar != 's' && respuestaBorrar != 'n')
            {
                printf("\nError. Ingrese nuevamente la opcion correcta. Esta seguro que desea borrar a esta bicicleta del sistema? (s: SI y n: NO)\n");
                fflush(stdin);
                scanf("%c", &respuestaBorrar);
            }

            if(respuestaBorrar == 's')
            {
                bicicletas[indiceBicicleta].isEmpty = 1;
                todoOk = 1;
                printf("Baja Exitosa!!!!\n");
            }
            else
            {
                printf("Se ha cancelado la baja.\n");
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int modificarBicleta(eBicicleta bicicletas[], int tamBic , eTipo tipos[],int tamTipo, eColor colores[], int tamColor)
{
	int todoOk = 0;
	int idBicicleta;
	int indiceBicicleta;
	char confirmacion;
	int opcion;
	eBicicleta auxBicicleta;

	if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0)
	{
		system("cls");
		printf("             *** Modificar Bicicleta ***                          \n");
		printf("------------------------------------------------------------------\n");
		mostrarBicicletas(bicicletas, tamBic, colores, tamColor, tipos, tamTipo);
		printf("\n\n");
		printf("Ingrese su ID: \n");
		scanf("%d", &idBicicleta);

		indiceBicicleta = buscarBicicletaId(bicicletas, tamBic , idBicicleta);

		if(indiceBicicleta == -1)
		{
			printf("El ID ingresado no existe.\n");
		}
		else
		{
			printf("---------------------------------------------------------------\n");
            printf("Id     |Marca            |Tipo             |Color     |Material\n");
            printf("---------------------------------------------------------------\n");

			mostrarBicicleta(bicicletas[indiceBicicleta], colores, tamColor, tipos, tamTipo);

			printf("\nEsta es la bicicleta que desea modificar? (s: SI y n: NO)\n");
			fflush(stdin);
			scanf("%c", &confirmacion);
			while(confirmacion != 's' && confirmacion != 'n')
            {
                printf("\nError. Ingrese nuevamente la opcion correcta. Esta es la bicicleta que desea modificar? (s: SI y n: NO)\n");
                fflush(stdin);
                scanf("%c", &confirmacion);
            }
			if(confirmacion == 's')
			{
                opcion = menuDeModificaciones();
                switch(opcion)
                {
                    case 1:
                        mostrarTipos(tipos, tamTipo);
                        pedirEntero(&auxBicicleta.idTipo, "Ingrese el ID del tipo deseado.\n", "Error. Ingrese nuevamente el ID del tipo deseado\n", 1000, 1003);
                        bicicletas[indiceBicicleta].idTipo = auxBicicleta.idTipo;
                        printf("Modificacion Exitosa!!!\n");
                        break;
                    case 2:
                        pedirCaracter(&auxBicicleta.material, "Ingrese el material de la bicicleta(c: Carbono, a: Aluminio)\n", "Error. Ingrese nuevamente el material de la bicicleta(c: Carbono, a: Aluminio)\n",'c', 'a');
                        bicicletas[indiceBicicleta].material = auxBicicleta.material;
                        printf("Modificacion exitosa!!!\n");
                        break;
                    case 3:
                        printf("Se ha cancelado la modificacion.\n");
                        break;
                    default:
                        printf("Opcion Invalida!!!\n");
                        break;
                }
			}
			else
            {
                printf("Se ha cancelado la modificacion.\n");
            }
		}
		todoOk = 1;
	}
	return todoOk;
}

void mostrarBicicleta(eBicicleta unaBicicleta, eColor colores[], int tamColor, eTipo tipos[], int tamTipo)
{
    char descColor[20];
    char descTipo[20];

    cargarDescripcionColor(colores, tamColor, unaBicicleta.idColor, descColor);
    cargarDescripcionTipo(tipos, tamTipo, unaBicicleta.idTipo, descTipo);

    printf("%-8d%-18s%-18s%-14s%-8c\n",
           unaBicicleta.id,
           unaBicicleta.marca,
           descTipo,
           descColor,
           unaBicicleta.material);
}

int mostrarBicicletas(eBicicleta bicicletas[], int tamBic, eColor colores[], int tamColor, eTipo tipos[], int tamTipo)
{
    int todoOk = 0;
    int flag = 1;

    if(bicicletas != NULL && tamBic > 0 && colores != NULL && tamColor > 0 && tipos != NULL && tamTipo > 0)
    {
        printf("            *** Listado de Bicicletas ***\n");
        printf("------------------------------------------------------------------\n");
        printf("Id     |Marca            |Tipo             |Color        |Material\n");
        printf("------------------------------------------------------------------\n");

        ordenarBicicletasTipoYMaterial(bicicletas, tamBic, tipos, tamTipo);
        for(int i = 0; i < tamBic; i++)
        {
            if(bicicletas[i].isEmpty == 0)
            {
                mostrarBicicleta(bicicletas[i], colores, tamColor, tipos, tamTipo);
                flag = 0;
            }
        }
        if(flag)
        {
            printf("     No hay bicicletas para mostrar\n");
        }
        todoOk = 1;
    }
    return todoOk;
}

int ordenarBicicletasTipoYMaterial(eBicicleta bicicletas[], int tamBic, eTipo tipos[], int tamTipo)
{
    int todoOk = 0;
    eBicicleta auxBicicleta;
    char descTipo1[20];
    char descTipo2[20];

    if(bicicletas != NULL && tamBic > 0)
    {
        for(int i = 0; i < tamBic - 1; i++)
        {
            for(int j = i + 1; j < tamBic; j++)
            {
                cargarDescripcionTipo(tipos, tamTipo, bicicletas[i].idTipo, descTipo1);
                cargarDescripcionTipo(tipos, tamTipo, bicicletas[j].idTipo, descTipo2);
                if((strcmp(descTipo1, descTipo2) > 0) || (strcmp(descTipo1, descTipo2) == 0 && bicicletas[i].material > bicicletas[j].material))
                {
                    auxBicicleta = bicicletas[i];
                    bicicletas[i] = bicicletas[j];
                    bicicletas[j] = auxBicicleta;
                }
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int validarIdBicicleta(eBicicleta bicicletas[], int tamBic, int idBicicleta)
{
    int todoOk = 0;

    if(bicicletas != NULL && tamBic > 0)
    {
        for(int i = 0; i < tamBic; i++)
        {
            if(bicicletas[i].id == idBicicleta && bicicletas[i].isEmpty == 0)
            {
                todoOk = 1;
                break;
            }
        }
    }
    return todoOk;
}

int mostrarBicicletasColorSeleccionado(eBicicleta bicicletas[], int tamBic, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int idColor;
    int flag = 1;
    char descripcion[20];

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0)
    {
        system("cls");
        printf("              *** Listado de Cada color ***                      \n");
        printf("------------------------------------------------------------------\n");

        mostrarColores(colores, tamColor);
        pedirEntero(&idColor, "Ingrese el ID del color deseado.\n", "Error. Ingrese nuevamente el ID del color deseado\n", 5000, 5004);

        printf("\nId     |Marca            |Tipo             |Color        |Material\n");
        printf("--------------------------------------------------------------------\n");

        cargarDescripcionColor(colores, tamColor, idColor, descripcion);

        for(int i = 0; i < tamBic; i++)
        {
            if(bicicletas[i].idColor == idColor && bicicletas[i].isEmpty == 0)
            {
                mostrarBicicleta(bicicletas[i], colores, tamColor,tipos,tamTipo);
                flag = 0;
            }
        }

        if(flag)
        {
            system("cls");
            printf("No hay bicicletas de color %s para mostrar.\n", descripcion);
        }
        todoOk = 1;
    }
    return todoOk;
}

int mostrarBicicletasTipoSeleccionado(eBicicleta bicicletas[], int tamBic, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int idTipo;
    int flag = 1;
    char descripcion[20];

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0)
    {
        system("cls");
        printf("             *** Listado de Cada Tipo ***                      \n");
        printf("------------------------------------------------------------------\n");

        mostrarTipos(tipos, tamTipo);
        pedirEntero(&idTipo, "Ingrese el ID del tipo deseado.\n", "Error. Ingrese nuevamente el ID del tipo deseado\n", 1000, 1003);

        printf("\nId     |Marca            |Tipo             |Color        |Material\n");
        printf("--------------------------------------------------------------------\n");

        cargarDescripcionTipo(tipos, tamTipo, idTipo, descripcion);

        for(int i = 0; i < tamBic; i++)
        {
            if(bicicletas[i].idTipo == idTipo && bicicletas[i].isEmpty == 0)
            {
                mostrarBicicleta(bicicletas[i], colores, tamColor,tipos,tamTipo);
                flag = 0;
            }
        }

        if(flag)
        {
            system("cls");
            printf("No hay bicicletas de tipo %s para mostrar mostrar.\n", descripcion);
        }
        todoOk = 1;
    }
    return todoOk;
}

int mostrarBicicletasSeparadasTipo(eBicicleta bicicletas[], int tamBic, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    char descripcion[20];


    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0)
    {
        system("cls");
        printf("       *** Listado de Bicicletas Separadas por Tipo ***\n");
        printf("---------------------------------------------------------------\n");

        for(int i = 0; i < tamTipo; i++)
        {
            cargarDescripcionTipo(tipos, tamTipo, tipos[i].id, descripcion);
            printf("Tipos: %s\n\n",descripcion);
            mostrarBicicletasIdTipo(bicicletas, tamBic, tipos, tamTipo, colores, tamColor, tipos[i].id);
        }

        todoOk = 1;
    }
    return todoOk;
}


int mostrarBicicletasIdTipo(eBicicleta bicicletas[], int tamBic, eTipo tipos[], int tamTipo, eColor colores[], int tamColor, int idTipo)
{
    int todoOk = 0;
    int flag = 1;
    char descripcion[20];

    if(bicicletas != NULL && tamBic > 0 && tipos != NULL && tamTipo > 0 && colores != NULL && tamColor > 0)
    {
        printf("Id     |Marca            |Tipo             |Color     |Material\n");
        printf("---------------------------------------------------------------\n");
        cargarDescripcionTipo(tipos, tamTipo, idTipo, descripcion);

        for(int i = 0; i < tamBic; i++)
        {
            if(bicicletas[i].isEmpty == 0 && bicicletas[i].idTipo == idTipo)
            {
                mostrarBicicleta(bicicletas[i], colores, tamColor,tipos,tamTipo);
                flag = 0;
            }
        }

        if(flag == 1)
        {
            printf("No hay bicicletas de tipo %s para mostrar\n",descripcion);
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int cantidadBicicletasColorTipoSeleccionado(eBicicleta bicicletas[], int tamBic, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int idColor;
    int idTipo;
    int contador = 0;
    char descripcionColor[20];
    char descripcionTipo[20];

    if(bicicletas != NULL && tipos != NULL && colores != NULL && tamBic > 0 && tamTipo > 0 && tamColor > 0)
    {
        mostrarColores(colores, tamColor);
        pedirEntero(&idColor, "Ingrese el ID del color deseado.\n", "Error. Ingrese nuevamente el ID del color deseado\n", 5000, 5004);

        mostrarTipos(tipos, tamTipo);
        pedirEntero(&idTipo, "Ingrese el ID del tipo deseado.\n", "Error. Ingrese nuevamente el ID del tipo deseado\n", 1000, 1003);

        system("cls");
        printf("      *** Informe cantidad de Bicicletas de cada tipo y color***\n");

        cargarDescripcionColor(colores, tamColor, idColor,descripcionColor);
        cargarDescripcionTipo(tipos, tamTipo, idTipo, descripcionTipo);

        printf("\nId     |Marca            |Tipo             |Color     |Material\n");
        printf("---------------------------------------------------------------\n");

        for(int i = 0; i < tamBic; i++)
        {
            if(bicicletas[i].idColor == idColor && bicicletas[i].isEmpty == 0 && bicicletas[i].idTipo == idTipo)
            {
                contador++;
                mostrarBicicleta(bicicletas[i], colores, tamColor, tipos, tamTipo);
            }
        }

        if(contador == 0)
        {
            printf("\nNo hay bicicletas de color %s y de tipo %s para mostrar\n",descripcionColor, descripcionTipo);
        }
        else
        {
            printf("\nHay %d bicicleta(s) de color %s y de tipo %s\n", contador, descripcionColor, descripcionTipo);
        }

        printf("\n");

        todoOk = 1;
    }
    return todoOk;
}

int coloresMasElegidos(eBicicleta bicicletas[], int tamBic, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int contadores[5] = {0};
    int mayorCantColores;

    if(bicicletas != NULL && tipos != NULL && colores != NULL && tamBic > 0 && tamTipo > 0 && tamColor > 0)
    {
        system("cls");
        printf("  *** Colores mas elegidos***\n");
        printf("---------------------------------\n");
        for(int i = 0; i < tamColor; i++)
        {
            for(int j = 0; j < tamBic; j++)
            {
                if(bicicletas[j].idColor == colores[i].id && bicicletas[j].isEmpty == 0)
                {
                    contadores[i]++;
                }
            }
        }

        for(int i = 0; i < tamColor; i++)
        {
            if(i == 0 || mayorCantColores < contadores[i])
            {
                mayorCantColores = contadores[i];
            }
        }

        for(int i = 0; i < tamColor; i++)
        {
            if(contadores[i] == mayorCantColores)
            {
                printf("El color mas elegido es: %s\n", colores[i].nombreColor);
            }
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int cantidadBicicletasMaterial(eBicicleta bicicletas[], int tamBic, eTipo tipos[], int tamTipo, eColor colores[], int tamColor)
{
    int todoOk = 0;
    int contadorCarbono = 0;
    int contadorAluminio = 0;

    if(bicicletas != NULL && tipos != NULL && colores != NULL && tamBic > 0 && tamTipo > 0 && tamColor > 0)
    {
        printf("\nId     |Marca            |Tipo             |Color     |Material\n");
        printf("---------------------------------------------------------------\n");
        ordenarBicicletasTipoYMaterial(bicicletas, tamBic, tipos, tamTipo);
        for(int i = 0; i < tamBic; i++)
        {
            if(bicicletas[i].isEmpty == 0 && bicicletas[i].material == 'C')
            {
                contadorCarbono++;
                mostrarBicicleta(bicicletas[i], colores, tamColor, tipos, tamTipo);
            }
            else if(bicicletas[i].isEmpty == 0 && bicicletas[i].material == 'A')
            {
                contadorAluminio++;
                mostrarBicicleta(bicicletas[i], colores, tamColor, tipos, tamTipo);
            }
        }
        printf("\n");

        if(contadorCarbono > contadorAluminio)
        {
            printf("\nHay mas bicicletas de carbono, con un total de: %d\n", contadorCarbono);
        }
        else if(contadorCarbono == contadorAluminio)
        {
            printf("\nHay la misma cantidad de bicicletas de carbono como de aluminio, con un total de: %d y %d\n", contadorCarbono, contadorAluminio);
        }
        else
        {
            printf("Hay mas bicicletas de aluminio, con un total de: %d\n", contadorAluminio);
        }

        todoOk = 1;
    }
    return todoOk;
}
