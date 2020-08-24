#include <stdio.h>//Estandar (printf, scanf, NULL)
#include <stdlib.h>//Estandar (srand, rand) y varias macros,declaraciones y funciones
#include <windows.h>//Nos permite cambiar el color
#include <time.h> //Para generar numero aleatorios destintos segun el tiempo (srand(time())
#include <locale.h>//Permite que los acentos se visualicen por pantalla.
#define  nombreFichero "hundir.txt"//Definimos nombreFichero para referirnos al fichero

// Posiciones: '0'=desocupado | '1'=Hay barco | '2'=Barco destruido  / '3' =Agua

struct estadisticas
{
   
int destruidosoponente;
int destruidosjugador;

};

void SetColor(int Color);//Establece el color
int menuinicial(int resu);//Da las opciones en el menu principal a elegir y las recibe
void imprimir(char nombre[50]);// Funcion que imprime el tablero de juego y los caracteres (~ # X 0)
void iniciar(char nombre[50]);// Rellena con '0' el array y coloca los barcos de la cpu y sus jugadas
void pedir(int *opcion1, int *opcion2,char nombre[50]);//Pide las coordenadas al jugador
int submenu();//Opcion de continuar, nueva partida , salir o hacer que no se vuelva a mostrar el mensaje
int estadisticas(struct estadisticas E);//Guarda las puntuaciones en un fichero
void again();//Funcion de volver a jugar o salir
int i, j, k, jugador[6][10], oponente[6][10], opcion1, opcion2, puntajejugador=0, puntajeoponente=0; // Variables globales

void SetColor(int Color)
{
   
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (Color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
 return;
}

int menuinicial(int resu)
{
    SetColor(11);
   
    printf("\n\n\t    ~BATALLA NAVAL~\n\n\t\t#\n\t\t#|\n\t\t#|#\n\t\t#|##\n\t\t#|###\n\t\t#|####");
    printf("\n\t\t#|#####\n\t\t#|######\n\t#########################\n\t _______________________");
    printf("\n\t  ####/)###############\n\t   ###(/##############\n\t    #################\n\t     ###############");
    printf("\n\n\n\t-Pulsa 1 e Intro para JUGAR\n\n\t-Pulsa 2 e Intro para SALIR\n\n\n\tDame tu opción: ");
    scanf("%d", &resu);//Escanea la respuesta
    system("cls");
    return resu;//Me devuleve el resultado el cual usaremos en el swith del main
   
}

void imprimir(char nombre[50]) // Funcion que imprime el tablero de juego
{  
   
int l = 0;//Es para inicializar el array que enumera

printf("\t   ");//Posicionar el array acorde al tablero

    for (l = 1;l <= 9;l++)
    {
        printf("%i  ",l);//Enumera X
    }


    // Imprime tablero del OPONENTE(CPU)
        for (i = 0;i < 5;i++) //FILA Y
        {  
           
            printf("\n\n\t%d", i+1);//Enumera Y
       
            for (j = 1;j <= 9;j++)//FILA X
     
            {
                if (oponente[i][j] == 3)//Si es agua
                {
                    SetColor(10);
                    printf("  #");
                    SetColor(11);
                }
                else
                {
                    if (oponente[i][j] == 2) // Imprime 'X' si vale 2 (Hundido)
                    {SetColor(12);
                        printf("  X");
                        SetColor(11);
                    }
                    else
                
                    {
                        printf("  ~");//Lo deja por defecto hasta que sea modificado por los anteriores(X # 0)
                    }
                   
                }                                    
            }
        
            if (i == 3)
            {
                SetColor(15);
                printf("\tBOSS");//Escribe Oponente
                SetColor(11);
            }else if (jugador[i][j] == 1)//Ya que 1 es el valor de los barcos y en el tablero del jugador se muestra con 0
                    {
                        SetColor(5);
                        printf("  O");
                        SetColor(11);
                    }
            else
            {
                if(i == 1)
                {
                    SetColor(14);
                    printf("\tBarcos destruidos por oponente : %d", puntajeoponente);//Suma puntos
                    SetColor(11);            
                }
            }
        }

     SetColor(15);
    printf("\n\n\t_____________________________\n\n");
    SetColor(11);
    printf("\t   ");
   
    for (l = 1;l <= 9;l++)//Genera los numeros que enumeran
    {
        printf("%i  ",l);//Enumera X
    }
    //IMPRIME EL TABLERO DEL JUGADOR
    for (i = 0;i < 5;i++) // FILA Y ademas de generar los numeros que enumeran
    {
        printf("\n\n\t%d", i+1);//Enumera Y
       
        for (j = 1;j <= 9;j++)//FILA X
        {
            if (jugador[i][j] == 3)//Imprime '#' si vale 3 (Agua)
            {
                SetColor(10);
                printf("  #");
                SetColor(11);
            }
            else
            {
                if (jugador[i][j] == 2) // Imprime 'X' si vale 2 || 'O' si vale 1 (Destruido)
                {
                    SetColor(12);
                    printf("  X");
                    SetColor(11);
                }
                else
                {
                    if (jugador[i][j] == 1)//Ya que 1 es el valor de los barcos y en el tablero del jugador se muestra con 0
                    {
                        SetColor(5);
                        printf("  O");
                        SetColor(11);
                    }
                    else
                    {
                        printf("  ~");//Lo deja por defecto hasta que sea modificado por los anteriores(X # 0)
                    }
                }
            }
        }
        if (i == 3)
        {
            SetColor(15);
            printf("\t%s",nombre);//Imprime el nombre del Jugador
            SetColor(11);
        }
        else
        {
            if (i == 1)
            {
                SetColor(14);
                printf("\tBarcos destruidos por el jugador : %d", puntajejugador);//Imprime el nombre del Jugador
                SetColor(11);
            }
        }
    }
 
    printf("\n\n");
}

void iniciar(char nombre[50]) // Rellena con '0' el array y coloca los barcos
{

    for (i = 1;i <= 5;i++) // Llena todo con '0'
    {
        for (j = 1;j <= 9;j++)
        {
            jugador[i][j] = 0;
            oponente[i][j] = 0;
        }
    }
    SetColor(5);
    printf("\n\n Dame las coordenadas de tus barcos~\n\n");
    SetColor(11);
    //Genera posiciones aleatoria segun el reloj (devolviendola en segundos dando una valor distinto) del PC
    //Null deshabilita la capacidad de devolver inf incesaria (como la hora)
    srand(time(NULL));
   
    for (k = 1;k <= 5;k++) // Distribuye los barcos //K se encarga de hacer la numeracion de los barcos(Numero de los barcos(coordenada))
    {
        imprimir(nombre);  //Llama a la funcion imprimir
        // Distribuye los barcos oponentes(CPU)//1+Numero aleatorio % del numero max del array j= min+rand()%max
        i = 1+rand()%5;
        j = 1+rand()%9;
        while (oponente[i][j] == 1)//Si hay un barco vuelve da otro valor
        {
            i = 1+rand()%5;
            j = 1+rand()%9;
        }
        oponente[i][j]=1; // La posicion de los barcos valdra 1
       
        //PIDE COORDENADA X
        printf("\n\tX%d = ", k);
        fflush(stdin);
        scanf("%d", &opcion2);
        while (opcion2 < 1 || opcion2 > 9)
        {
            printf("    Escoje un valor válido ( 1 a 9 )\n\n\tX%d = ", k);
            fflush(stdin);
            scanf("%d", &opcion2);
        }
       
        //PIDE COORDENADA Y
        printf("\n\tY%d = ", k);
        fflush(stdin);
        scanf("%d", &opcion1);
        while (opcion1 < 1 || opcion1 > 5)
        {
            printf("\n    Escoje un valor válido ( 1 a 5 )\n\n\tY%d = ", k);
            fflush(stdin);
            scanf("%d", &opcion1);
        }
                         
        if(jugador[opcion1-1][opcion2] == 1)//Si ya hay barco
        {
            printf("\n Ese valor ya existe...");
            system("cls");
            k = k-1;
        }
        jugador[opcion1-1][opcion2] = 1;//Asigna el barco
                       
        system("cls");
                                                         
    }  
     
}

void pedir(int *opcion1, int *opcion2,char nombre[50])
{
   
       do
       {
       imprimir(nombre);//Llama a la funcion imprimir(tablero y colocaciones)
       //Pide Coordenada X
       SetColor(13);
       printf(" Es tu turno! Dame la posición que deseas atacar~\n\n");//Pide la coordenada X para atacar
       SetColor(11);
       printf("\tX = ");
       fflush(stdin);
       scanf("%d", opcion2);
       
       while (*opcion2 < 1 || *opcion2 > 9)//En caso de que el valor no este dentro de la matriz
       {
           printf("\n    Escoje un valor válido ( 1 a 9 )\n\n\tX = ");
           fflush(stdin);
           scanf("%d", opcion2);
       }
       //Pide Coordenada Y
       printf("\tY = ");
       fflush(stdin);
       scanf("%d", opcion1);
       
       while (*opcion1 < 1 || *opcion1 > 5)//En caso de que el valor no este dentro de la matriz
       {
           printf("\n    Escoje un valor válido ( 1 a 5 )\n\n\tY = ");
           fflush(stdin);
           scanf("%d", opcion1);
       }
       if (oponente[*opcion1-1][*opcion2] != 0)//0 ya es un barco
       {
        system("cls");
        printf("Esta casilla ya esta ocupada, vuelva a introducir coordenada\n");
       
       }
       
       }while (oponente[*opcion1-1][*opcion2] != 0 && oponente[*opcion1-1][*opcion2] != 1);
   

   
   
}

int submenu()
{
  int opcion = 0;
 
  printf("Menu del juego\n");
  do
  {
 
  printf("1.Continuar\n2.Empezar partida nueva\n3.Salir\n4.No quiero que vuelva a aparecer por pantalla este mensaje: ");
  fflush(stdin);
  scanf("%i",&opcion);
 
  }while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4);
 
  switch (opcion)
  {
 
   case 1://Continua
   return 0;
   break;
   
   case 2://Partida Nueva  
   system("cls");
   return main();
   break;
     
   case 3://Sale
   printf("\n\n\n~~~~~~~~~~Saliendo~~~~~~~~~~\n\n\n");
   exit(0);
   break;
   
   case 4://No vuelve a mostrar
   return 5;
   break;
   }
 
 
 }

int estadisticas(struct estadisticas E)
{
   
   
    //Comprueba que se abre el fichero correctamente
    if(nombreFichero == NULL)
    {
        printf("Error al abrir hundir.txt");
        return -1;
    }
   
    //abre un fichero para guardar la partida, si existe una ya guardada
    FILE *outStream = fopen ("hundir.txt", "w");



    fprintf (outStream, "+===================================================+\n");
    fprintf (outStream, "|             Estadísticas de la partida            |\n");
    fprintf (outStream, "+---------------------------------------------------+\n");
    fprintf (outStream, "| CPU     : %d Barcos destruidos                    |\n", E.destruidosjugador);
    fprintf (outStream, "+---------------------------------------------------+\n");
    fprintf (outStream, "| Jugador : %d Barcos destruidos                    |\n", E.destruidosoponente);
    fprintf (outStream, "+===================================================+");
   
       
    //Comprueba que se cierra el fichero correctamente
    if( fclose(outStream) == EOF)
    {
        printf("Error al cerrar hundir.txt");
        return -1;
    }
        printf("La partida se ha guardado correctamente\n");
        system("PAUSE");
}

void again()
{
    char again;
     do
     {
     printf("Quieres volver a jugar? s/n\n");
     fflush(stdin);
     scanf("%c", &again);
        if(again == 's')//Vuelve al menu
        {
            system("cls");
            puntajeoponente=0;
            puntajejugador=0;
            main(0);
           
        }
            else if (again == 'n')//Sale
            {
                system("cls");
                printf("\n\n\n~~~~~~~~~~Saliendo~~~~~~~~~~\n\n\n");
                exit(0);
            }
                if (again != 's' && 'n')
                {
                    printf("La opción es incorrecta\n");
                }
     }while (again != 's' && again != 'n');
   
}

int main() // Inicia el programa (main)
{
    setlocale(LC_CTYPE, "Spanish"); //Función que permite que los acentos se visualicen por pantalla.
    int res;//Switch case
      int probabilidadcpu;//Almacena los valores correspondientes a la probabilidad de la CPU
    float dificultadcpu = 0.1; //Establece dificultad de la cpu de acertar
    char nombre[50]; //Almacena el nombre
    int opcionsubmenu = 0; //Contador poder hacer que el menu no vuelva a aparecer
    struct estadisticas E;////Estructura estado en la que almacenamos los valores de destruidosoponente y destruidosjugador
    E.destruidosoponente=0;//Variable que almacena la puntuacion del oponente
    E.destruidosjugador=0;//Variable que almacena la puntuacion del jugador

    SetColor(11);
   
    res = menuinicial(res); //El main recibe la respuesta dada el la funcion menuinicial
 
    switch (res) // Eliges la opcion Jugar o Salir
    {
       
       case 1:
       {
        printf("Dame tu nombre:\n");
        scanf("%s",&nombre);
        system("cls");
        iniciar(nombre); // Llama a la funcion iniciar
       
           do
           {
               
               system("cls"); // Limpia la pantalla
               
               pedir(&opcion1,&opcion2,nombre);//Llama a la funcion pedir
               
               system("cls");
               imprimir(nombre);
               //Se asignan las X #
               if (oponente[opcion1-1][opcion2] == 1)//Si hay un barco
               {
                   oponente[opcion1-1][opcion2] = 2;//Asigna 'X' en el tablero
                   E.destruidosoponente = E.destruidosoponente;//Añade en 1 al contador
                   puntajejugador = puntajejugador+1;//Suma un punto al marcador del jugador
                   estadisticas(E);//Llama a la funcion estadisiticas para guardar los resultados despues de cada acierto
                   SetColor(10);
                   printf("\n Has acertado!!\n\n");
                   SetColor(11);
               }
               else
               {
                    oponente[opcion1-1][opcion2] = 3;
                   printf("\n Has fallado...\n\n");
                   
               }
               
               system("PAUSE");
               system("cls");
               
               if (E.destruidosoponente == 5)//Si se destruyen todos los barcos del oponente
               {
                    system("cls");
                   printf("\n\n\n\n\t\t\t%s HA GANADO!!",nombre);
                   system("PAUSE");
                   system("cls");
                   again();//Llama a la funcion again para ofrecer la opcion de jugar de nuevo
               }                                                                
               imprimir(nombre);
           
               if(opcionsubmenu != 5)//si devuelve algo distindo de 5 se realiza la opcion
                {
                   
                opcionsubmenu = submenu();
               
                }
               printf(" Turno del oponente!~\n\n");
               
               
            //CPU----------------------------------------------------------------------------------------------------------
           
               dificultadcpu = dificultadcpu+0.1;//Asegura que la cpu tiene el minimo de dificultad a pesar de si modificas el valor inicia(min=0.1)
                               
               srand(time(NULL));//Genera posiciones aleatoria segun el reloj (devolviendola en segundos dando una valor distinto)de la PC
                //Null deshabilita la capacidad de devolver inf incesaria (como la hora)
                               
               probabilidadcpu = rand()%5;//la probabilidad de acertar es aleatoria pero tiene que ser divisible por 5
                               
               if (probabilidadcpu > dificultadcpu)//Puede fallar o acertar
               {
                //1+numero aleatorio % max del array / min+rand()%max
                   i = 1+rand()%5;
                   j = 1+rand()%9;
                   while (jugador[i][j] == 2)//Cuando se le acierte a un barco no vuelva a disparar a ese barco(a cualquier sitio excepto a donde haya un 2)
                   {
                       i = 1+rand()%5;
                       j = 1+rand()%9;
                   }
                   
               }
               else
               {
                   while (jugador[i][j] == 2 || jugador[i][j] != 1)//Falla siempre si la probabilidad es menor que la dificultad falla siempre
                   {
                       i = rand()%5;
                       j = 1+rand()%9;
                   }
                 
               }
               
               
               //Guarda las coordenadas
               opcion1 = i;
               opcion2 = j;
               system("cls");
               imprimir(nombre);
               
                //Se asignan las X #
               if (jugador[opcion1][opcion2] == 1)
               {
                   
                    jugador[opcion1][opcion2] = 2;
                    E.destruidosjugador = E.destruidosjugador;
                    puntajeoponente = puntajeoponente+1;//Suma puntos
                    SetColor(10);
                    printf("\n El oponente ha acertado!!\n\n");
                    SetColor(11);
                    system("PAUSE");
                    estadisticas(E);
               }
               else
               {
                jugador[i][j] = 3;
                   printf("\n El oponente ha fallado...\n\n");
                   system("PAUSE");
               }
               if(E.destruidosjugador == 5)//Si destruyen los barcos del jugador
               {    
                   system("cls");                                                
                   printf("\n\n\n\n\t\t\tHAS PERDIDO!!\n");
                   system("PAUSE");
                   system("cls");
                   again();//LLama a la funcion again para ofrecer la opcion de volver a jugar
               
               }

               if (E.destruidosoponente == 5 || E.destruidosjugador == 5)//Cuando los barcos destruidos son iguales a 5 se termina el do while
               {
                   E.destruidosoponente = 5; E.destruidosjugador = 5;
               }
             
               
               
           }
           while(E.destruidosoponente<5 || E.destruidosjugador<5);//Mientras no haya 5 barcos destruidos no se sale
       }
       case 2://Salir del menu principal
        {
           printf("\n\n\n~~~~~~~~~~Saliendo~~~~~~~~~~\n\n\n");
           exit(0);//sale del programa
        }
       
        default://Valor !=1 y !=2
        {
            fflush(stdin);
            printf("ERROR, elija una opcion válida\n");
            system("PAUSE");//Espera
            system("cls");
            return main();//vuelve al menu
        }
   
    } // Termina switch(res)
                 
} // Termina el programa (main)
