#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char archMisiones[]="archivoMisiones";
const char archAstronauta[]="archivoAstronautas";
const char archNaves[]="archivoNave";
typedef struct
{
    int id;
    char nombre[30];
    char apellido[30];
    char apodo[30];
    int edad;
    char nacionalidad[30];
    char especialidad[30];//
    int horasAcumuladas;
    int misiones[30];
    int horasEEI;
    int estado;//1-activo/2-inactivo
} stAstronauta;
typedef struct
{
    int id;
    char nave[20];
    int vuelosRealizados;
    int horasDeVuelo;
    int estado;
} nave;
typedef struct
{
    int id;
    int idNave;
    int estado; //(1. Listo, 2. En vuelo, 3. Retornada, 4. Cancelada, 0. Fallida)
    char destino[30]; //(EEI, Órbita terrestre, Luna, etc)
    char cargamento[40]; //(Satélite, Insumos para la EEI, el Auto de Elon Musk, etc)
    int idAstronauta;
    char detalleMision[50];
} misiones;
///MISIONES
void nuevaMision();
misiones cargarIdMision(misiones aux);
misiones asignarNave(misiones aux);
misiones cargarEstadoMision(misiones aux);
misiones cargarDestinoyCargamento(misiones aux);
misiones asignarAstronauta(misiones aux);
void mostrarMisiones();
void mostrarUnaMision(misiones aux);
void menuMisiones();
///NAVES
nave cargarId (nave A);
void cargarNave ();
nave cargarTipo (nave B);
nave cantidadVuelos (nave C);
nave horasVuelo (nave D);
nave Estado (nave E);
void mostrarDatos();
void mostrarNave(nave F);
void darDeAlta(int id);
void enMision(int id);
void darDeBaja (int id);
void modificacion ();
void consultaId ();
void menuNaves();
///ASTRONAUTAS
void cargarAstronautas();
stAstronauta cargarIndividual(stAstronauta astronauta);
stAstronauta cargarNombre(stAstronauta astronauta);
stAstronauta cargarEdad(stAstronauta astronauta);
stAstronauta cargarNacionalidad(stAstronauta astronauta);
stAstronauta cargarEspecialidad(stAstronauta astronauta);
stAstronauta cargarHoras(stAstronauta astronauta);
stAstronauta cargarEstado(stAstronauta astronauta);
void mostrarAstronautas();
void mostrarIndividual(stAstronauta astronauta);
void darAlta(int identificacion);
void darBaja(int identificacion);
void unAstronauta();
void modificarUnAstronauta();
void menuAstronauta();

int main()
{
    int numero;
    char control = 's';

    while(control=='s')
    {
        printf("\n\t\t---MENU PRINCIPAL---");
        printf("\n\tIngrese el numero de la opcion que desee\n");
        printf("\n1.Menu de astronautas");
        printf("\n2.Menu de naves");
        printf("\n3.Menu de misiones\n");
        scanf("%i", &numero);
        switch (numero)
        {
        case 1:
            menuAstronauta();
            break;

        case 2:
            menuNaves();
            break;
        case 3:
            menuMisiones();
        default:
            printf("\n\t---El valor que ingreso no se encuentra entre las opciones disponibles-- ");
        }
        printf("\n\t---Si desea volver al menu principal ingrese 's'---");
        fflush(stdin);
        scanf("%c", &control);
    }
    return 0;
}
///ASTRONAUTAS
void menuAstronauta()
{
    int opcion, identificacion;
    char control='s';
    while(control=='s')
    {
        printf("\n\t\t----MENU DE ASTRONAUTAS----\n");
        printf("\n\tIngrese el numero de la opcion que desee\n");
        //opciones
        printf("\n1.Cargar astronautas");
        printf("\n2.Mostrar listado de astronautas");
        printf("\n3.Dar de alta un astronauta");
        printf("\n4.Dar de baja un astronaua");
        printf("\n5.Consultar datos de un astronauta");
        printf("\n6.Modificacion de datos de un astronauta\n");
        scanf("%i", &opcion);

        switch(opcion)
        {
        case 1://carga de astronautas
            cargarAstronautas();
            break;
        case 2://mostrar listado de astronautas y datos
            mostrarAstronautas();
            break;
        case 3://Dar de alta un astronauta a partir de su id
            printf("\nIngrese el ID del astronauta que desea dar de alta: ");//id de busqueda
            scanf("%i", &identificacion);
            darAlta(identificacion);
            break;
        case 4://Dar de baja un astronauta a partir de su id
            printf("\nIngrese el ID del astronauta que desea dar de baja: ");//id de busqueda
            scanf("%i", &identificacion);
            darBaja(identificacion);
            break;
        case 5://busca un astronauta por su id y muestra sus datos
            unAstronauta();
            break;
        case 6://da la posibilidad de modificar datos particculares de un astronauta
            modificarUnAstronauta();
            break;
        default:
            printf("\n\t---El valor que ingreso no se encuentra entre las opciones disponibles-- ");
        }
        ///Volver al menu
        printf("\n\t---Si desea volver al menu de astronautas ingrese 's'---\n");
        fflush(stdin);
        scanf("%c", &control);
    }
}
void cargarAstronautas()///carga de astronautas mientras el usuario desee
{
    FILE*arch=fopen(archAstronauta,"rb");//Se abre en "rb" para comprobar la existencia del archivo
    stAstronauta astronauta;
    char control='s';

    if(arch==NULL)//el archivo no tiene datos
    {
        printf("Se ingresaran datos por primera vez\n");
        arch=fopen(archAstronauta,"wb");
    }
    else//el archivo tiene datos
    {
        fclose(arch);
        printf("\nSe agregaran datos al archNaves");
        arch=fopen(archAstronauta,"ab");
    }

    if(arch!=NULL)//se pudo abrir el archNaves en escritura
    {
        while(control=='s')
        {
            astronauta = cargarIndividual(astronauta);
            astronauta = cargarNombre(astronauta);
            astronauta = cargarEdad(astronauta);
            astronauta = cargarNacionalidad(astronauta);
            astronauta = cargarEspecialidad(astronauta);
            astronauta = cargarHoras(astronauta);
            astronauta = cargarEstado(astronauta);
            fwrite(&astronauta,sizeof(stAstronauta),1,arch);

            printf("\nSi desea cargar otro astronauta presione 's': ");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(arch);
    }
    else//el arch no se pudo abrir en escritura
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---\n");
}
stAstronauta cargarIndividual(stAstronauta astronauta)///carga del ID
{
    FILE*arch=fopen(archAstronauta,"rb");//modo lectura
    stAstronauta aux = astronauta;

    if(arch!=NULL)//se pudo abrir el archivo (hay datos)
    {
        //verificacion de id (ARREGLAR)
        printf("\nIngrese el ID: ");
        scanf("%i", &aux.id);
        while(fread(&astronauta,sizeof(stAstronauta),1,arch)>0)//lee el archivo
        {
            if(aux.id==astronauta.id)//si el id ya existe no es valido y se pide nuevamente
            {
                printf("\nID NO VALIDO\n");
                printf("\nIngrese el ID: ");
                scanf("%i", &aux.id);
            }
        }
        astronauta.id=aux.id;
        fclose(arch);
    }
    else//no se pudo abrir el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
    return astronauta;
}
stAstronauta cargarNombre(stAstronauta astronauta)///carga el nombre, apellido y apodo
{
        printf("\nIngrese el NOMBRE: ");
        fflush(stdin);
        scanf("%s", astronauta.nombre);
        printf("\nIngrese el APELLIDO: ");
        fflush(stdin);
        scanf("%s", astronauta.apellido);
        printf("\nIngrese el APODO: ");
        fflush(stdin);
        scanf("%s", astronauta.apodo);
        return astronauta;
}
stAstronauta cargarEdad(stAstronauta astronauta)///carga la edad
{
        //verificacion de edad
        printf("\nIngrese la EDAD: ");
        scanf("%i", &astronauta.edad);
        while(astronauta.edad<18)//si es menor de 18 años la edad no es valida y se pide nuevamente
        {
            printf("\nEDAD NO VALIDA\n");
            printf("\nIngrese la EDAD: ");
            scanf("%i", &astronauta.edad);
        }
        return astronauta;
}
stAstronauta cargarNacionalidad(stAstronauta astronauta)///carga nacionalidad
{
        printf("\nIngrese la NACIONALIDAD: ");
        fflush(stdin);
        scanf("%s", astronauta.nacionalidad);
        return astronauta;
}
stAstronauta cargarEspecialidad(stAstronauta astronauta)///carga espacialidad
{
        printf("\nIngrese la ESPECIALIDAD: ");
        fflush(stdin);
        scanf("%s", astronauta.especialidad);
        return astronauta;
}
stAstronauta cargarHoras(stAstronauta astronauta)///carga horas de vuelo y horas eei
{
        printf("\nIngrese las HORAS DE VUELO: ");
        scanf("%i", &astronauta.horasAcumuladas);
        printf("\nIngrese las HORAS EN EEI: ");
        scanf("%i", &astronauta.horasEEI);
        return astronauta;
}
stAstronauta cargarEstado(stAstronauta astronauta)///carga estado
{
    printf("\nIngrese el ESTADO del astronauta |1 activo/2 inactivo|");
    scanf("%i", &astronauta.estado);
    //verificacion del estado
    while(astronauta.estado!=1 && astronauta.estado!=2)//si no es lo que se habilita no se ingresa y se pide nuevamente
    {
        printf("\nESTADO NO VALIDO");
        printf("\nIngrese el ESTADO del astronauta |1 activo/2 inactivo|");
        scanf("%i", &astronauta.estado);
    }
    return astronauta;
}
/*void cargarMisiones(int id)
{
    FILE*arch=fopen(archMisiones,"r+b");
    misiones a;;
    int flag=0;
    if(arch!=NULL)
    {
        while(flag==0 && fread(&a,sizeof(misiones),1,arch)>0)
        {
            if(id==a.idAstronauta)
            {
                a.misiones
            }
        }
    }
}*/
void mostrarAstronautas()///muestra listado de astronautas
{
    FILE*archi=fopen(archAstronauta,"rb");//modo lectura
    stAstronauta astronautas;

    if(archi!=NULL)//hay datos
    {
        while(fread(&astronautas,sizeof(stAstronauta),1,archi)>0)//se lee el archivo
        {
            mostrarIndividual(astronautas);//funcion de muestra
        }
        fclose(archi);
    }
    else//no hay datos
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
void mostrarIndividual(stAstronauta astronauta)///muestra de un solo astronauta
{
    printf("\n------------------------");
    printf("\nID: %i", astronauta.id);
    printf("\nNOMBRE Y APELLIDO: %s %s", astronauta.nombre,astronauta.apellido);
    printf("\nAPODO: %s",astronauta.apodo);
    printf("\nEDAD: %i",astronauta.edad);
    printf("\nNACIONALIDAD: %s",astronauta.nacionalidad);
    printf("\nESPECIALIDAD: %s",astronauta.especialidad);
    printf("\nHORAS DE VUELO: %i",astronauta.horasAcumuladas);
    printf("\nHORAS EN EEI: %i",astronauta.horasEEI);
    printf("\nESTADO: ");
    if(astronauta.estado==1)
        printf("activo\n");
    else
        printf("inactivo\n");
    printf("------------------------");
}
void darAlta(int identificacion)///dar de alta un astronauta buscado por su ID
{
    FILE*arch=fopen(archAstronauta,"r+b");//modo lectura y escritura
    stAstronauta astronauta;
    int flag=0;

    if(arch!=NULL)//se abrio el archivo
    {
        while(flag==0 && fread(&astronauta,sizeof(stAstronauta),1,arch)>0)// se lee el archivo, si se encuentra el id corta el while
        {
            if(astronauta.id==identificacion)//busqueda id
            {
                if(astronauta.estado==2)//solo si el astronauta esta de baja se puede dar de alta
                {
                    printf("\nSe dara de alta al astronauta: %s %s\n ",astronauta.nombre,astronauta.apellido);
                    astronauta.estado=1;

                    fseek(arch,sizeof(stAstronauta)*(-1),SEEK_CUR);
                    fwrite(&astronauta,sizeof(stAstronauta),1,arch);//escritura en el archNaves
                    flag=1;
                }
                else
                {
                    printf("\nEl astronauta ya estaba dado de alta\n");
                    flag=1;
                }
            }
        }
        fclose(arch);
    }
    else//no se pudo abrir el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
void darBaja(int identificacion)///dar de baja un astronauta buscado por su ID
{
    FILE*arch=fopen(archAstronauta,"r+b");//modo lectura y escritura
    stAstronauta astronauta;
    int flag=0;

    if(arch!=NULL)//se pudo abrir el archivo
    {
        while(flag==0 && fread(&astronauta,sizeof(stAstronauta),1,arch)>0)//se lee el archivo, si se encuentra el id se corta el while
        {
            if(astronauta.id==identificacion)
            {
                if(astronauta.estado==1)//solo si el astronauta esta dado de alta se pude dar de baja
                {
                    astronauta.estado=2;
                    printf("\nEl astronauta: %s %s esta ahora inactivo \n",astronauta.nombre,astronauta.apellido);

                    fseek(arch,(-1)*sizeof(stAstronauta),SEEK_CUR);
                    fwrite(&astronauta,sizeof(stAstronauta),1,arch);//se escribe en el archivo
                    flag=1;
                }
                else
                {
                    printf("\nEl astronauta ya esta dado de baja\n");
                    flag=1;
                }
            }
        }
        fclose(arch);
    }
    else//no se abrio el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
void unAstronauta()///mostrar los datos de un astronauta buscado por su ID
{
    FILE * arch = fopen(archAstronauta,"rb");//modo lectura
    stAstronauta astronauta;
    char control = 's';
    int identificacion;

    if(arch!=NULL)//se abrio el archivo
    {
        while(control=='s')
        {
            int flag=0;
            printf("\nIngrese el ID del astronauta que desea consultar: ");//id de busqueda
            scanf("%i", &identificacion);
            while(flag==0 && fread(&astronauta,sizeof(stAstronauta),1,arch)>0)//se lee el archivo, cuando se encuentra el id se corta el while
            {
                if(astronauta.id==identificacion)
                {
                    mostrarIndividual(astronauta);//funcion de muestra
                    flag=1;
                }
            }
            if(flag==0)
            {
                printf("\nEl ID ingresado no corresponde a ningun astronauta\n");
            }

            printf("\nSi desea continuar con la busqueda presione 's'. En caso contrario presione cualquier tecla\n");
            fflush(stdin);
            scanf("%c", &control);
            fseek(arch,0,SEEK_SET);
        }
        fclose(arch);
    }
    else//no se pudo abrir el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
void modificarUnAstronauta()///modifica un dato elegido de un astronauta buscado por su ID
{
    FILE * arch=fopen(archAstronauta,"r+b");//modo lectura y escritura
    stAstronauta astronauta;
    int identificacion,flag=0,modificar,hVuelos=0, hEEI=0;

    if(arch!=NULL)//se abrio el archivo
    {
        printf("\nIngrese el ID del astronauta: ");//id de busqueda
        scanf("%i", &identificacion);

        while(flag==0 && fread(&astronauta,sizeof(stAstronauta),1,arch)>0)//se lee el archivo, si se encuentra el id el while se corta
        {
            if(astronauta.id==identificacion)
            {
                printf("\n %s %s\n",astronauta.nombre,astronauta.apellido);
                printf("\nIngrese el numero correspondiente a lo que desea modificar: ");
                //opciones para modificar campos especificos
                printf("\n1.Modificar NOMBRE, APELLIDO y APODO");
                printf("\n2.Modificar EDAD");
                printf("\n3.Modificar NACIONALIDAD");
                printf("\n4.Modificar ESPECIALIDAD");
                printf("\n5.Modificar Horas DE VUELOS Y HORAS EN EEI");
                printf("\n");
                scanf("%i", &modificar);
                switch(modificar)
                {
                case 1://modifica los nombres
                    astronauta=cargarNombre(astronauta);
                    break;
                case 2://modifica la edad
                    astronauta=cargarEdad(astronauta);
                    break;
                case 3://modifica la nacionalidad
                    astronauta=cargarNacionalidad(astronauta);
                    break;
                case 4://modifica la especialidad
                    astronauta=cargarEspecialidad(astronauta);
                    break;
                case 5://agrega horas de vuelo y en eei
                    printf("\nIngrese la cantidad de horas de vuelo que se incrementaran: ");
                    scanf("%i", &hVuelos);
                    printf("\nIngrese la cantidad de horas en EEI");
                    scanf("%i", &hEEI);

                    astronauta.horasAcumuladas=astronauta.horasAcumuladas + hVuelos;
                    astronauta.horasEEI=astronauta.horasEEI + hEEI;

                    printf("\nLa cantidad de horas de vuelo realizadas es de: %i",astronauta.horasAcumuladas);
                    printf("\nLa cantidad de horas en EEI es de: %i",astronauta.horasEEI);
                    break;
                default:
                    printf("\n\t---El valor que ingreso no se encuentra en las opciones disponibles---");
                }
                fseek(arch,(-1)*sizeof(stAstronauta),SEEK_CUR);
                fwrite(&astronauta,sizeof(stAstronauta),1,arch);//escritura en el archivo
                flag=1;
            }
        }
        fclose(arch);
    }
    else//no se pudo abrir el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
///NAVES
void menuNaves()
{
    int numero,id;
    char continuar = 's';

    while (continuar == 's')
    {
        printf("\n\t\t---MENU DE NAVES---");
        printf("\n\tIngrese el numero de la opcion que desee\n");
        //opciones
        printf("\n1.Cargar la nave");
        printf("\n2.Mostrar listado de naves");
        printf("\n3.Dar de alta una nave");
        printf("\n4.Dar de baja una nave");
        printf("\n5.Modificar un dato de la nave");
        printf("\n6.Consultar datos de una nave\n");
        scanf("%i", &numero);

        switch (numero)
        {
        case 1://carga de naves
            cargarNave();
            break;
        case 2://muestra listado de naves
            mostrarDatos();
            break;
        case 3://pone una nave en "lista para su uso"
            printf("\nIngrese el ID de la nave que quiere dar de alta: ");//id de busqueda
            scanf("%i", &id);
            darDeAlta(id);
            break;
        case 4://pone una nave en "de baja"
            printf("\nIngrese el id de la nave que quiere dar de baja: ");//id de busqueda
            scanf("%i", &id);
            darDeBaja(id);
            break;
        case 5://opcion de modificar un dato de una nave
            modificacion();
            break;
        case 6://muestra una nave buscada por id
            consultaId();
            break;
        default:
            printf("\n\t---El valor que ingreso no se encuentra entre las opciones disponibles-- ");
        }
        printf("\n\t---Si desea volver al menu de naves ingrese 's'---\n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
}
void cargarNave ()///carga naves mientras el usuario desee
{
    char continuar = 's';
    nave aux;
    FILE*arch=fopen(archNaves,"rb");//Se abre el archivo en "rb" para comprobar la existencia del archivo

    if(arch==NULL)//el archivo no tiene datos
    {
        printf("Se ingresaran datos por primera vez\n");
        arch=fopen(archNaves,"wb");
    }
    else//el archNaves tiene datos
    {
        fclose(arch);
        printf("\nSe agregaran datos al archivo");
        arch=fopen(archNaves,"ab");
    }

    if (arch != NULL)//se pudo abrir el archNaves en esritura
    {
        while (continuar == 's')
        {
            aux = cargarId(aux);
            aux = cargarTipo(aux);
            aux = cantidadVuelos(aux);
            aux = horasVuelo(aux);
            aux = Estado(aux);
            fwrite(&aux, sizeof(nave), 1, arch);//escritura en el archivo

            printf("\n\t---Si desea cargar otra nave ingrese 's'---");
            fflush(stdin);
            scanf("%c", &continuar);
        }
    }
    else//no se pudo abrir el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---\n");
}
nave cargarId (nave A)///carga ID
{
    int id;
    FILE * arch = fopen(archNaves, "rb");//modo lectura

    if (arch != NULL)//se pudo abrir el archivo
    {
        printf("\nIngrese el ID: ");
        scanf("%i", &id);

        while (fread(&A, sizeof (nave), 1, arch)> 0)//se lee el archivo
        {
            if (id == A.id)
            {
                printf("\nID NO VALIDO");
                printf("\nIngrese el ID");
                scanf("%i", &id);
            }
        }
        A.id = id;
        fclose(arch);
    }
    else
        printf("\n\t\t---Hubo un ERROR al abrir el archNaves---\n");
    return A;
}
nave cargarTipo (nave B)///carga el TIPO DE NAVE
{
    char tipo [20];

    printf("\nIngrese TIPO DE NAVE (Starship, Falcon 9 o Falcon Heavy): ");
    fflush(stdin);
    gets(tipo);

    while (strcmpi(tipo, "starship")!=0 && strcmpi(tipo, "falcon 9")!=0 && strcmpi(tipo, "falcon heavy")!=0)//si no ingresa as opciones validas se vuelve a pedir el ingreso del dato
    {
        printf("\nTIPO DE NAVE NO VALIDO");
        printf("\nIngrese TIPO DE NAVE: ");
        fflush(stdin);
        gets(tipo);
    }
    strcpy(B.nave, tipo);
    return B;
}
nave cantidadVuelos (nave C)///carga la CANTIDAD DE VUELOS REALIZADOS
{
    printf("\nIngrese la CANTIDAD DE VUELOS: ");
    scanf("%i", &C.vuelosRealizados);
    return C;
}
nave horasVuelo (nave D)///carga las HORAS DE VUELOS ACUMULADAS
{
    printf("\nIngrese las HORAS DE VUELO: ");
    scanf("%i", &D.horasDeVuelo);
    return D;
}
nave Estado (nave E)///carga el ESTADO de una nave
{
    printf("\nIngrese el ESTADO de la nave (0- mantenimiento 1- Lista para su uso 2- Actualmente en mision 3- De baja): ");
    scanf("%i", &E.estado);

    while (E.estado != 0 && E.estado != 1 && E.estado != 2 && E.estado != 3)//si no se ingresa un valor valido se pide nuevamente
    {
        printf("\nESTADO NO VALIDO");
        printf("\nIngrese el ESTADO de la nave (0- mantenimiento 1- Lista para su uso 2- Actualmente en misión 3- De baja): ");
        scanf("%i", &E.estado);
    }
    return E;
}
void mostrarDatos()///muestra el listado de naves
{
    FILE * arch = fopen(archNaves, "rb");//modo lectura
    nave aux;
    if (arch != NULL)//se pudo abrir el archivo
    {
        while (fread(&aux, sizeof (nave), 1, arch) > 0)//lee el archivo
        {
            mostrarNave(aux);//funcion de muestra
        }
        fclose(arch);
    }
    else//no se pudo abrir el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
void mostrarNave(nave F)///muestra una sola nave
{
    printf("\n------------------------");
    printf("\nID: %i", F.id);
    printf("\nTIPO DE NAVE: %s",F.nave);
    printf("\nCANTIDAD DE VUELOS: %i", F.vuelosRealizados);
    printf("\nHORAS DE VUELO: %i", F.horasDeVuelo);
    printf("\nESTADO: ");
    if(F.estado==0)
        printf("En mantenimiento\n");
    else if(F.estado==1)
        printf("Lista para su uso\n");
    else if(F.estado==2)
        printf("Actualmente en mision\n");
    else if(F.estado==3)
    printf("De baja\n");
    printf("------------------------");
}
void darDeAlta(int id) ///pone una nave en "lista para su uso"
{
    int flag = 0;
    FILE * arch = fopen(archNaves, "r+b");//modo lectura y escritura
    nave aux;
    if (arch != NULL)//se pudo abrir el archivo
    {
        while (flag == 0 && fread (&aux, sizeof(nave), 1, arch) > 0)//lee el archivo, si encuentra el id el whise se corta
        {
            if (id == aux.id)
            {
                if (aux.estado == 0 || aux.estado == 3)//solo se da de alta si la nave esta en estado "mantenimiento" y "de baja"
                {
                    printf("\nSe dara de alta la nave: %s",aux.nave);
                    aux.estado = 1;//cambio de estado a "lista para su uso"
                    fseek(arch, sizeof(nave)*-1, SEEK_CUR);
                    fwrite(&aux, sizeof(nave), 1, arch);// escritura en el archivo
                    flag = 1;
                }
                else
                {
                    printf("\nSu nave no puede darse de alta");
                    flag=1;
                }
            }
        }
        fclose(arch);
    }
    else//no se pudo abrir el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
void enMision(int id)
{
    int flag = 0;
    FILE * arch = fopen(archNaves, "r+b");//modo lectura y escritura
    nave aux;
    if (arch != NULL)//se pudo abrir el archivo
    {
        while (flag == 0 && fread (&aux, sizeof(nave), 1, arch) > 0)//lee el archivo si encuentra el id el while se corta
        {
            if (id == aux.id)
            {
                aux.estado=2;
                printf("\nLa nave %i, %s, esta actualmente en mision",aux.id,aux.nave),
                fseek(arch, sizeof(nave)*-1, SEEK_CUR);
                fwrite(&aux, sizeof(nave), 1, arch);// escritura en el archivo
                flag = 1;
            }
        }
        fclose(arch);
    }
}
void darDeBaja (int id)///pone una nave en "de baja"
{
    int flag = 0;
    FILE * arch = fopen(archNaves, "r+b");//modo lectura y escritura
    nave aux;
    if (arch != NULL)//se pudo abrir el archivo
    {
        while (flag == 0 && fread (&aux, sizeof(nave), 1, arch) > 0)//lee el archivo si encuentra el id el while se corta
        {
            if (id == aux.id)
            {
                if (aux.estado == 0 || aux.estado == 1)//solo en los estados 0 y 1 se puede dar de baja
                {
                    printf("Se dara de baja la nave: %s",aux.nave);
                    aux.estado = 3;//cambio de estado a "de baja"
                    fseek(arch, sizeof(nave)*-1, SEEK_CUR);
                    fwrite(&aux, sizeof(nave), 1, arch);//escritura en el archivo
                    flag = 1;
                }
                else
                {
                    printf("\nSu nave no puede darse de baja");
                    flag=1;
                }
            }
        }
        fclose(arch);
    }
    else//no se pudo abrir el archivo
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
void modificacion ()///modifica un dato de una nave
{
    int id, num, horasExtraVuelo, cantidadExtraVuelo, flag = 0;
    nave aux;

    FILE * arch = fopen(archNaves, "r+b");//modo lectura y escritura
    if (arch != NULL)//se pudo abrir el archivo
    {
        printf("\nIngrese el ID de la nave: ");//id de busqueda
        scanf("%i", &id);
        while (flag == 0 && fread (&aux, sizeof(nave), 1, arch) > 0)//lee el archivo y si encuentra el id el while se corta
        {
            if (id == aux.id)
            {
                printf("\nNAVE: %s\n",aux.nave);
                printf("\nIngrese el numero correspondiente a lo que desea modificar: ");
                //opciones de modificacion de un campo
                printf("\n1.Cantidad de vuelos realizados");
                printf("\n2.Horas de vuelo realizadas\n");
                scanf("%i", &num);
                switch(num)
                {
                case 1://modificacion de vuelo realizados
                    printf("\nIngrese la cantidad de vuelos realizados extra: ");
                    scanf("%i", &cantidadExtraVuelo);
                    aux.vuelosRealizados = aux.vuelosRealizados + cantidadExtraVuelo;

                    printf("\nLa cantidad de vuelos realizados actualmente es de: %i", aux.vuelosRealizados);
                    break;
                case 2://modificacion cantidad de horas de vuelo
                    printf("\nIngrese la cantidad de horas realizados extra: ");
                    scanf("%i", &horasExtraVuelo);
                    aux.horasDeVuelo = aux.horasDeVuelo + horasExtraVuelo;

                    printf("\nLa cantidad de vuelos realizados actualmente es de: %i", aux.horasDeVuelo);
                    break;
                default:
                    printf("\n\t---El valor que ingreso no se encuentra en las opciones disponibles---");
                }
                fseek(arch, sizeof(nave)*-1, SEEK_CUR);
                fwrite(&aux, sizeof(nave), 1, arch);//escritura en el archivo
                flag = 1;
            }
        }
        fclose(arch);
    }
    else//no se pudo abrir el archNaves
       printf("\n\t\t---Hubo un ERROR al abrir el archNaves---");
}
void consultaId ()///muestra una nave
{
    int id, flag = 0;
    nave aux;

    FILE * arch = fopen(archNaves, "rb");//modo lectura
    if (arch != NULL)//se pudo abrir el archivo
    {
        printf("\nIngrese el ID de la nave que quiere consultar: ");//id de busqueda
        scanf("%i", &id);

        while (flag == 0 && fread (&aux, sizeof(nave), 1, arch) > 0)//lee el archivo si encuentra el id el while se corta
        {
            if (id == aux.id)
            {
                mostrarNave(aux);//funcion de muestra
                flag = 1;
            }
        }
        fclose(arch);
    }
    else//no se pudo abrir el archivo
       printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
///MISIONES
void menuMisiones()
{
    int opcion;
    char control='s';
    while(control=='s')
    {
        printf("\n\t\t---MENU DE MISIONES---");
        printf("\n\tIngrese el numero de la opcion que desee");
        printf("\n1.Cargar misiones");
        printf("\n2.Mostrar misiones");
        printf("\n3.Dar de alta una mision");
        printf("\n4.Dar de baja una mision");
        printf("\n5.Modificar el estado de la mision\n");
        scanf("%i",&opcion);
        switch(opcion)
        {
        case 1://cargar misiones nuevas
            nuevaMision();
            break;
        case 2://mostrar todas las misiones
            mostrarMisiones();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            printf("\n\t---El valor que ingreso no se encuentra entre las opciones disponibles-- ");
        }
        printf("\n\t\t---Si desea volver al menu de misiones ingrese 's'---\n");
        fflush(stdin);
        scanf("%c",&control);
    }
}
void nuevaMision()
{
    char control='s';
    misiones aux;
    FILE*arch=fopen(archMisiones,"rb");
    if(arch==NULL)
    {
        printf("\nSe ingresaran datos por primera vez");
        arch=fopen(archMisiones,"wb");
    }
    else
    {
        printf("\nSe agregaran datos al archivo");
        fclose(arch);
        arch=fopen(archMisiones,"ab");
    }
    if(arch!=NULL)
    {
        while(control=='s')
        {
            aux=cargarIdMision(aux);
            aux=asignarNave(aux);
            aux=cargarEstadoMision(aux);
            aux=cargarDestinoyCargamento(aux);
            aux=asignarAstronauta(aux);
            printf("\nDetalles de la mision: ");
            fflush(stdin);
            gets(aux.detalleMision);

            fwrite(&aux,sizeof(misiones),1,arch);
            printf("\n\t---Si desea cargar otra mision ingrese 's'---");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(arch);
    }
    else
        printf("\n\t\t---Hubo un ERROR al abrir el archNaves---\n");
}
misiones cargarIdMision(misiones aux)
{
    FILE*arch=fopen(archMisiones,"rb");
    int id;
    if(arch!=NULL)
    {
        printf("\nIngrese el ID:");
        scanf("%i", &id);
        while(fread(&aux,sizeof(misiones),1,arch)>0)
        {
            if(id==aux.id)
            {
                printf("\nID NO VALIDO");
                printf("\nIngrese el ID:");
                scanf("%i", &id);
            }
        }
        aux.id=id;
        fclose(arch);
    }
    return aux;
}
misiones asignarNave(misiones aux)
{
    FILE*arch=fopen(archNaves,"rb");
    int id;
    if(arch!=NULL)
    {
        nave a;
        printf("Las naves disponibles que puede asignar son: ");
        while(fread(&a, sizeof(nave), 1, arch)>0)
        {
            printf("...");
            if(a.estado==1)
            {
               printf("\n-------------------");
               printf("\nId nave: %i",a.id);
               printf("\nTipo nave: %s",a.nave);
               printf("\n-------------------");
            }
        }
        fclose(arch);
        printf("\nIngrese el ID de la nave que asignara: ");
        scanf("%i", &aux.idNave);
        id=aux.idNave;
        enMision(id);
    }
    else
        printf("\nNo hay naves disponibles para asignar");
    return aux;
}
misiones cargarEstadoMision(misiones aux)
{
    printf("\nIngrese el ESTADO de la mision |0.Listo, 1.En vuelo, 2.Retornada, 3.Cancelada, 4.Fallida||");
    scanf("%i", &aux.estado);
    while(aux.estado!=0 && aux.estado!=1 && aux.estado!=2 && aux.estado!=3 && aux.estado!=4)
    {
        printf("\nESTADO NO VALIDO");
        printf("\nIngrese el ESTADO de la mision |0.Listo, 1.En vuelo, 2.Retornada, 3.Cancelada, 4.Fallida|");
        scanf("%i", &aux.estado);
    }
    return aux;
}
misiones cargarDestinoyCargamento(misiones aux)
{
    printf("\nIngrese el DESTINO de la mision: ");
    fflush(stdin);
    gets(aux.destino);
    printf("\nIngrese el CARGAMENTO de la mision: ");
    fflush(stdin);
    gets(aux.cargamento);
    return aux;
}
misiones asignarAstronauta(misiones aux)
{
    FILE*arch=fopen(archAstronauta,"rb");
    int id;
    if(arch!=NULL)
    {
        stAstronauta a;
        printf("\nLos astronautas disponibles para la mision son: ");
        while(fread(&a,sizeof(stAstronauta),1,arch)>0)
        {
            if(a.estado==1)
            {
                printf("\n------------------");
                printf("\nNobre y apellido: %s %s",a.nombre,a.apellido);
                printf("\nId: %i",a.id);
                printf("\n------------------");
            }
        }
        fclose(arch);
        printf("\nIngrese el ID del astronauta que asignara: ");
        scanf("%i", &aux.idAstronauta);
        id=aux.idAstronauta;
        darBaja(id);
    }
    else
        printf("\nNo hay astronautas disponibles para asignar");
    return aux;
}
void mostrarMisiones()
{
    FILE*arch=fopen(archMisiones,"rb");
    misiones a;
    if(arch!=NULL)
    {
        while(fread(&a,sizeof(misiones),1,arch)>0)
        {
            mostrarUnaMision(a);
        }
        fclose(arch);
    }
    else
        printf("\n\t\t---Hubo un ERROR al abrir el archivo---");
}
void mostrarUnaMision(misiones aux)
{
    printf("\n------------------------");
    printf("\nID MISION: %i",aux.id);
    printf("\nID NAVE: %i", aux.idNave);
    printf("\nID ASTRONAUTA: %i",aux.idAstronauta);
    printf("\nDESTINO: %s",aux.destino);
    printf("\nCARGAMENTO: %s",aux.cargamento);
    printf("\nESTADO: ");
    if(aux.estado==0)
        printf("Listo\n");
    else if(aux.estado==1)
        printf("En vuelo\n");
    else if(aux.estado==2)
        printf("Retornada\n");
    else if(aux.estado==3)
        printf("Cancelada\n");
    else if(aux.estado==4)
        printf("Fallida\n");
    printf("DETALLE DE MISION: %s",aux.detalleMision);
    printf("\n------------------------");
}
