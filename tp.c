#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>

typedef struct 
{
    int x;
    int y;
} Pair;


int findIndex(int **array, size_t size, int target)
{
    int i = 0;
    while((i < size) && (array[0][i] != target)) i++;
    return (i < size) ? (i) : (-1);
}

int main(int argc, char *argv[]) 
{
    if (argc != 2)
    {
        printf("Uso: ./tp input.txt\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!\n");
        return 2;
    }
  
    int ** matriz;
    int i = 0;
    int num_arr[6];
    int num;
    int nl;
    int counter = 1;
    int num_linhas_colunas = 0;
    int pnum = 0;
    int snum = 0;
    int arr_size = 0;

    bool space = false;
    bool plinha = true;

    while (true)
    {
        nl = fgetc(file);
        
        if ((nl == 32 && space) || (nl == 13 && space) || (nl == EOF))
        {
            for (int j = 0; j < arr_size; j++)
            {
                num = 10 * num +  num_arr[j];
            }
            arr_size = 0;
            space = false;
            if (num_linhas_colunas == 0)
            {
                num_linhas_colunas = num + 1;
                matriz = (int **) malloc(sizeof(int *) * num_linhas_colunas);
                for (int j = 0; j < num_linhas_colunas; j++)
                {
                    matriz[j] = (int *) malloc(sizeof(int) * num_linhas_colunas);
                }
            }
            else if (plinha)
            {
                matriz[0][counter] = num;
                matriz[counter][0] = num;
                counter++;
                if (nl == 13)
                {
                    plinha = false;
                    counter = 1;
                }
            }
            else
            {
                if (counter == 1)
                {
                    pnum = num;
                    counter++;
                }
                else if (nl == 13 || nl == EOF)
                {
                    pnum = findIndex(matriz, num_linhas_colunas, pnum);
                    snum = findIndex(matriz, num_linhas_colunas, num);
                    matriz[pnum][snum] = 1;
                    counter = 1;
                    if (nl == EOF)
                    {
                        break;
                    }
                }
            }
        }
        else if (nl != 10 && nl != 13)
        {
            if (!space)
            {
                num = 0;
                num_arr[arr_size] = nl - '0';
                arr_size++;
                space = true;
            }
            else
            {
                num_arr[arr_size] = nl - '0';
                arr_size++;
            }
        }
        
    }
    fclose(file);

    Pair ** props;

    props = (Pair **) malloc(sizeof(Pair *) * 6);
    for (int j = 0; j < 6; j++)
    {
        props[j] = (Pair *) malloc(sizeof(Pair) * (num_linhas_colunas * num_linhas_colunas));
    }

    int col_prop_ref = 0;
    //reflexiva
    for (i = 1; i < num_linhas_colunas; i++)
    {
        if (matriz[i][i] != 1)
        {
            props[0][col_prop_ref].x = matriz[0][i];
            props[0][col_prop_ref].y = matriz[0][i];
            col_prop_ref++;
        }
    }

    int col_prop_antref = 0;
    //irreflexiva
    for (i = 1; i < num_linhas_colunas; i++)
    {
        if (matriz[i][i] == 1)
        {
            props[1][col_prop_antref].x = matriz[0][i];
            props[1][col_prop_antref].y = matriz[0][i];
            col_prop_antref++;
        }
    }
    
    int col_prop_sim = 0;
    //simetrica
    for (i = 1; i < num_linhas_colunas; i++)
    {
        for (int j = 1; j < num_linhas_colunas; j++)
        {
            if (matriz[i][j] != matriz[j][i])
            {
                if (matriz[j][i] == 1)
                {
                    bool rep = false;
                    for (int aux = 0; aux < col_prop_sim; aux++)
                    {
                        if ((props[2][aux].x == matriz[0][i] && props[2][aux].y == matriz[0][j]))
                        {
                            rep = true;
                        }
                    }
                    if (!rep)
                    {
                        props[2][col_prop_sim].x = matriz[0][i];
                        props[2][col_prop_sim].y = matriz[0][j];
                        col_prop_sim++;
                    }
                }
                else
                {
                    bool rep = false;
                    for (int aux = 0; aux < col_prop_sim; aux++)
                    {
                        if ((props[2][aux].x == matriz[0][j] && props[2][aux].y == matriz[0][i]))
                        {
                            rep = true;
                        }
                    }
                    if (!rep)
                    {
                        props[2][col_prop_sim].x = matriz[0][j];
                        props[2][col_prop_sim].y = matriz[0][i];
                        col_prop_sim++;
                    }
                }
                
            }
        }
    }

    int col_prop_antsim = 0;
    //antisimetrica
    for (i = 1; i < num_linhas_colunas; i++)
    {
        for (int j = 1; j < num_linhas_colunas; j++)
        {
            if (matriz[i][j] == matriz[j][i] && i != j && matriz[i][j] != 0)
            {
                bool rep = false;
                for (int aux = 0; aux < col_prop_antsim; aux++)
                {
                    if (props[3][aux].x == matriz[0][j] && props[3][aux].y == matriz[0][i])
                    {
                        rep = true;
                    }
                }
                if (!rep)
                {
                    props[3][col_prop_antsim].x = matriz[0][i];
                    props[3][col_prop_antsim].y = matriz[0][j];
                    col_prop_antsim++;
                }
            }
        }
    }

    int col_prop_assim = 0;
    //assimetrica
    for (i = 1; i < num_linhas_colunas; i++)
    {
        for (int j = 1; j < num_linhas_colunas; j++)
        {
            if (matriz[i][j] == matriz[j][i] && matriz[i][j] != 0)
            {
                props[4][col_prop_assim].x = matriz[0][i];
                props[4][col_prop_assim].y = matriz[0][j];
                col_prop_assim++;
            }
        }
    }

    int col_prop_trans = 0;
    //transitiva
    for (i = 1; i < num_linhas_colunas; i++)
    {
        for (int z = 1; z < num_linhas_colunas; z++)
        {
            for (int j = 1; j < num_linhas_colunas; j++)
            {
                if (matriz[j][z] == 1 && matriz[i][j] == 1 && matriz[i][z] != 1)
                {
                    bool rep = false;
                    for (int aux = 0; aux < col_prop_trans; aux++)
                    {
                        if (props[5][aux].x == matriz[0][i] && props[5][aux].y == matriz[0][z])
                        {
                            rep = true;
                        }
                    }
                    if (!rep)
                    {
                        props[5][col_prop_trans].x = matriz[0][i];
                        props[5][col_prop_trans].y = matriz[0][z];
                        col_prop_trans++;
                    }
                }
            }
        }
    }

    if (col_prop_ref == 0)
    {
        printf("Reflexiva: V\n");
    }
    else
    {
        printf("Reflexiva: F\n");
        for (int j = 0; j < col_prop_ref; j++)
        {
            printf("(%d,%d); ", props[0][j].x, props[0][j].y);
        }
        printf("\n");
    }
    
    if (col_prop_antref == 0)
    {
        printf("Irreflexiva: V\n");
    }
    else
    {
        printf("Irreflexiva: F\n");
        for (int j = 0; j < col_prop_antref; j++)
        {
            printf("(%d,%d); ", props[1][j].x, props[1][j].y);
        }
        printf("\n");
    }

    if (col_prop_sim == 0)
    {
        printf("Simétrica: V\n");
    }
    else
    {
        printf("Simétrica: F\n");
        for (int j = 0; j < col_prop_sim; j++)
        {
            printf("(%d,%d); ", props[2][j].x, props[2][j].y);
        }
        printf("\n");
    }
    
    if (col_prop_antsim == 0)
    {
        printf("Anti-simétrica: V\n");
    }
    else
    {
        printf("Anti-simétrica: F\n");
        for (int j = 0; j < col_prop_antsim; j++)
        {
            printf("(%d,%d); (%d,%d); ", props[3][j].x, props[3][j].y, props[3][j].y, props[3][j].x);
        }
        printf("\n");
    }

    if (col_prop_assim == 0)
    {
        printf("Assimétrica: V\n");
    }
    else
    {
        printf("Assimétrica: F\n");
    }

    if (col_prop_trans == 0)
    {
        printf("Transitiva: V\n");
    }
    else
    {
        printf("Transitiva: F\n");
        for (int j = 0; j < col_prop_trans; j++)
        {
            printf("(%d,%d); ", props[5][j].x, props[5][j].y);
        }
        printf("\n");
    }
    

    if (col_prop_ref == 0 && col_prop_sim == 0 && col_prop_trans == 0)
    {
        printf("Relação de equivalência: V\n");
    }
    else
    {
        printf("Relação de equivalência: F\n");
    }
    

    if (col_prop_ref != 0 || col_prop_antsim != 0 || col_prop_trans != 0)
    {
        printf("Relação de ordem parcial: F\n");
    }
    else
    {
        printf("Relação de ordem parcial: V\n");
    }

    if (col_prop_trans != 0)
    {
        for (i = 1; i < num_linhas_colunas; i++)
        {
            for (int z = 1; z < num_linhas_colunas; z++)
            {
                for (int j = 1; j < num_linhas_colunas; j++)
                {
                    
                    if (matriz[j][z] == 1 && matriz[i][j] == 1 && matriz[i][z] != 1)
                    {
                        matriz[i][z] = 1;
                    }
                }
            }
        }
        
    }

    printf("Fecho transitivo da relação: ");
    for (i = 1; i < num_linhas_colunas; i++)
    {
        for (int j = 1; j < num_linhas_colunas; j++)
        {
            if (matriz[i][j] == 1)
            {
                printf("(%d,%d); ", matriz[0][i], matriz[0][j]);
            }
        }
    }
    printf("\n");
    
    return 0;
}