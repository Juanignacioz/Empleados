#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MODIFICADO "modificado.dat"

struct empleados{

int legajo;
char nombre[20];
char categoria;
float sueldo;
int activo;

};

void crear (FILE *archivo);
void alta(FILE *archivo);
void listadedatos(FILE *archivo);
void buscar(FILE *archivo);
void modificar(FILE *archivo);
void actualizar(FILE *archivo);
void BajaL(FILE *archivo);
void BajaF(FILE *archivo);



int main(){
int op;

    FILE *archivo;

    do{
    //printf ("\t\t SELECCIONE ALGUNA DE LAS SIGUIENTES OPCIONES\n");
    printf("\n");
    printf("\t\t 1: Crear un Archivo\n");
    printf("\t\t 2: alta \n");
    printf("\t\t 3: Listar datos \n");
    printf("\t\t 4: Buscar por Legajo o por Nombre\n");
    printf("\t\t 5: Modificar Categoria y Sueldo\n");
    printf("\t\t 6: Actualizar Sueldos\n");
    printf("\t\t 7: Baja Logica\n");
    printf("\t\t 8: Baja fisica\n");
    printf("\t\t 0:INGRESE 0 SI DESEA SALIR DEL PROGRAMA\n.");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t\tINGRESE LA OPCION QUE DESEA EJECUTAR\n");
    printf("\t\t");
    scanf("%d",&op);

    switch(op){

case 1:
    crear (archivo);

    break;
case 2:
    alta(archivo);
    break;
case 3:
    listadedatos(archivo);
    break;
case 4:
    buscar(archivo);
    break;
case 5:
    modificar(archivo);
    break;
case 6:
    actualizar(archivo);
    break;
case 7:
    BajaL(archivo);
    break;
case 8:
    BajaF(archivo);
    break;
case 0:
    break;

    }
    }while(op > 0 || op < 8);

    return 0;
}


void crear (FILE *archivo){
struct empleados datos={0,"0",'0',0,0};
    int i,cantempleado;

   if ( ( archivo = fopen( "empleados.dat", "wb" ) ) == NULL ){
      printf( "Error al crear el archivo\n" );
   }
   else {
    printf("Archivo creado correctamente.\n");
    }
    do{
    printf("Cantidad de empleados: ");
    scanf("%d",&cantempleado);
    fflush(stdin);
    if(cantempleado <= 0){
        printf("Error: Una cantidad no puede ser negativa\n");
    }
    }while(cantempleado <= 0);
    for(i=0;i<cantempleado;i++){
        fwrite(&datos,sizeof(struct empleados),1,archivo);
    }
    fclose(archivo);
    printf("\n");
}

void alta(FILE *archivo){
    struct empleados datos, data;
    int legajo;

    if((archivo = fopen("empleados.dat","r+b"))==NULL){
        printf("ERROR ,NO SE PUDO ABRIR EL ARCHIVO");
        exit(-1);
    };
      printf("INGRESE 0 PARA NO CARGAR MAS EMPLEADOS.\n");

    do{
    do{
        printf("Ingrese Numero de Legajo del empleado:\n");
        scanf("%d",&datos.legajo);
        fflush(stdin);
        if (datos.legajo< 0){
            printf("Error: El legajo tiene que ser mayor a 0\n");
        }
    }while(datos.legajo < 0);

    if(datos.legajo != 0){


    printf("Ingrese el nombre del empleado\n");
    gets(datos.nombre);
    fflush(stdin);
    do{
    printf("Ingrese la categoria A , B , C:\n");
    scanf("%c",&datos.categoria);
    fflush(stdin);
    if(datos.categoria != 'A' && datos.categoria != 'B' && datos.categoria != 'C' && datos.categoria != 'a' && datos.categoria != 'b' && datos.categoria != 'c' ){
        printf("INTENTE NUEVAMENTE\n");
    }
    }while(datos.categoria != 'a' && datos.categoria != 'A' && datos.categoria != 'b' && datos.categoria != 'B' && datos.categoria != 'C' && datos.categoria != 'c' );

    printf("INGRESE EL SALARIO DEL EMPLEADO:\n");
    scanf("%f",&datos.sueldo);
    fflush(stdin);

    do{
    printf("\t\t selecione una opcion:\n");
    printf("\t\t 0 empleado baja\n");
    printf("\t\t 1 empleado activo\n");
    scanf("%d",&datos.activo);
    fflush(stdin);
    }while(datos.activo != 0 && datos.activo != 1);

    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(datos.legajo-1)*sizeof(struct empleados),SEEK_CUR);
    fread(&data,sizeof(struct empleados),1,archivo);
    if(data.legajo == 0){
    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(datos.legajo-1)*sizeof(struct empleados),SEEK_CUR);
    fwrite(&datos,sizeof(struct empleados),1,archivo);
    }
    else{
        printf("Esta posicion ya se encuentra cargada \n");
    }
    }
    }while(datos.legajo != 0);
    fclose(archivo);

    return;
}

void listadedatos(FILE *archivo){
struct empleados datos;
int op;
int i=0,cant;

    if((archivo = fopen("empleados.dat","rb"))==NULL){
        printf("No se puede abrir el archivo");
        exit(-1);
    };
    do{
    printf("INGRSE LA OPCION DESEADA\n\n");
    printf("Ingrese 1 si quiere ver solo los empleados Activos.\n");
    printf("Ingrese 0 si quiere todos los empleados empleados\n ");
    scanf("%d",&op);
    fflush(stdin);

    }while(op != 0 && op != 1);

    switch(op){
case 1:

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    while(i<cant){
        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);
        if(datos.activo==1){
            printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
        }
        i++;
    }

break;

case 0:

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    for(i=0;i<cant;i++){
        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);
        printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    }

    break;

    }


    fclose(archivo);
return;
}



void buscar(FILE *archivo){
struct empleados datos;
int op;
int j,cant,i;
char nombre[20];
    if((archivo = fopen("empleados.dat","rb"))==NULL){
        printf("No se puede abrir el archivo");
        exit(-1);
    }

    do{
    printf("INGRESE LA OPCION DESEADA:\n");
    printf("Ingrese 1 si quiere buscar por legajo\n");
    printf("Ingrese 2 si quiere buscar por Nombre\n");
    scanf("%d",&op);
    fflush(stdin);
    }while(op != 1 && op != 2);


switch (op){
case 1:
    printf("Ingresar numero de legajo");
    scanf("%d",&j);
    fflush(stdin);

    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(j-1)*sizeof(struct empleados),SEEK_CUR);

    fread(&datos,sizeof(struct empleados),1,archivo);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    break;
case 2:

    printf("Ingrese el nombre del empleado a buscar: \n");
    gets(nombre);
    fflush(stdin);

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    while(i<cant){
        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);
        if((strcmp(nombre,datos.nombre))==0){
            printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
        }
        i++;
    }
    break;
}
    fclose(archivo);
return ;
}



void modificar(FILE *archivo){
struct empleados datos;
int op, j, cant, i,seg;
float sueldomodificado;
char nombre[20], categoria;

if((archivo = fopen("empleados.dat","r+b"))==NULL){
    printf("No se puede abrir el archivo");
    exit(-1);
}
    printf("Selecione una opcion:\n");
    printf("1. Modificar un campo y buscar por Numero de legajo\n");
    printf("2. Modificar un campo y buscar por Nombre de empleado\n");
    scanf("%d",&op);

    switch (op){

    case 1:
    printf("Ingresar numero de legajo:\n");
    scanf("%d",&j);
    fflush(stdin);

    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(j-1)*sizeof(struct empleados),SEEK_CUR);

    fread(&datos,sizeof(struct empleados),1,archivo);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    do{
    printf("\n");
    printf("Para continuar con la modificacion \nIngrese 1 por SI 2 por NO \n");
    scanf("%d",&seg);
    fflush(stdin);
    }while(seg != 1 && seg !=2);

    if(seg == 1){
        fseek(archivo,-sizeof(struct empleados),SEEK_CUR);
        printf("ingrese el Nuevo sueldo:\n");
        scanf("%f",&sueldomodificado);
        fflush(stdin);
        datos.sueldo = sueldomodificado;

        printf("ingrese la nueva Categoria:\n");
        scanf("%c",&categoria);
        fflush(stdin);
        datos.categoria = categoria;

        fwrite(&datos,sizeof(struct empleados),1,archivo);


    }

    break;
    case 2:

    printf("Ingrese el nombre del empleado a modificar: \n");
    gets(nombre);
    fflush(stdin);

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);


    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    while(i<cant){

        fseek(archivo,0,SEEK_SET);
        fseek(archivo,i*sizeof(struct empleados),SEEK_CUR);
        fread(&datos,sizeof(struct empleados),1,archivo);
        if((strcmp(nombre,datos.nombre))==0){
            printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
            do{
            printf("\n");
            printf("Para continuar con la modifciacion\nIngrese 1 por SI 2 por NO \n");
            scanf("%d",&seg);
            fflush(stdin);
    }while(seg != 1 && seg !=2);

    if(seg == 1){
        fseek(archivo,-sizeof(struct empleados),SEEK_CUR);
        printf("ingrese la nueva Categoria:\n");
        scanf("%c",&categoria);
        fflush(stdin);
        datos.categoria = categoria;

        printf("ingrese el Nuevo sueldo:\n");
        scanf("%f",&sueldomodificado);
        fflush(stdin);
        datos.sueldo = sueldomodificado;

        fwrite(&datos,sizeof(struct empleados),1,archivo);
    }
        }
        i++;
    }
    break;
    }
 fclose(archivo);
return;
}


void actualizar(FILE *archivo){
struct empleados datos;
int cant,i,porcen;
char cate;
float sueldomodificado;

if((archivo = fopen("empleados.dat","r+b"))==NULL){
    printf("No se puede abrir el archivo");
    exit(-1);
}
    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");


    fseek(archivo,0,SEEK_SET);
    for(i=0; i<cant; i++){
        fseek(archivo,i*sizeof(struct empleados),SEEK_CUR);
        fread(&datos,sizeof(struct empleados),1,archivo);
        fseek(archivo,0,SEEK_SET);
        printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    }

    do{
    printf("Ingrese la categoria a modificar\n");
    cate=getch();
    fflush(stdin);
    }while(cate != 'A' && cate != 'B' && cate != 'C' && cate != 'a' && cate != 'b' && cate != 'c' );

    do{
    printf("ingrese el porcentaje a modificar del sueldo\n");
    scanf("%d",&porcen);
    fflush(stdin);
    }while(porcen < 0 );

    fseek(archivo,0,SEEK_END);
    cant = ftell(archivo)/sizeof (struct empleados);
    fseek(archivo,0,SEEK_SET);

    for(i= 0; i<cant; i++){
        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);

    if(datos.categoria == cate){
        datos.sueldo = datos.sueldo * (1+porcen/100.0);

        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fwrite(&datos,sizeof(struct empleados),1,archivo);
        fseek(archivo,0,SEEK_SET);

    }

    }


fclose(archivo);
return;
}


void BajaL(FILE *archivo){
struct empleados datos;
int j,seg,cant,i;

if((archivo = fopen("empleados.dat","r+b"))==NULL){
    printf("No se puede abrir el archivo");
    exit(-1);
}

    printf("Ingresar numero de legajo");
    scanf("%d",&j);
    fflush(stdin);

    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(j-1)*sizeof(struct empleados),SEEK_CUR);

    fread(&datos,sizeof(struct empleados),1,archivo);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    fseek(archivo,-sizeof(struct empleados),SEEK_CUR);

    if(datos.activo == 1){
        printf("Para continuar con la modificacion el campo Activo?\n 1.SI\n 2. NO\n");
        scanf("%d",&seg);
        if(seg == 1){
        datos.activo = 0;
        fwrite(&datos,sizeof(struct empleados),1,archivo);
        }
    }
    else{
        printf("Error: El campo Activo esta en 0\n");
    }

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);
    fseek(archivo,0,SEEK_SET);
    for(i =0 ;i<cant;i++){
    if(datos.activo == 1){
    fread(&datos,sizeof(struct empleados),1,archivo);
    printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
    }
    }



fclose(archivo);
return;
}

void BajaF(FILE *archivo){
struct empleados datos;
int i, cant;
FILE *modificado;

    if((archivo = fopen("empleados.dat","r+b"))==NULL){
    printf("No se puede abrir el archivo");
    exit(-1);
}


    if((modificado = fopen("modificado.dat","w+b"))==NULL){
    printf("No se puede abrir el archivo");
    exit(-1);
    }
     else {
    printf("Archivo creado exitosamente.\n");
    }

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);
    fseek(archivo,0,SEEK_SET);
    for(i=0; i<cant; i++){
        fread(&datos,sizeof(struct empleados),1,archivo);
        if(datos.activo == 1){
        fwrite(&datos,sizeof(struct empleados),1,modificado);
        }
    }

    fseek(modificado,0,SEEK_END);
    cant=ftell(modificado)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    for(i=0;i<cant;i++){
        fseek(modificado,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);
        printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    }




fclose(modificado);
fclose(archivo);
return;
}
