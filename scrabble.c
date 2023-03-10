// CHIPER IOANA-CRISTINA 312CD

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "util/scrabble.h"
# include "util/print_board.h"


void scrieOrizontala (char matrice[15][15], char cuvant[],int lungime, int linie, int coloana);
void scrieVerticala (char matrice[15][15], char cuvant[],int lungime, int linie, int coloana);
int scor (int s[26],char word[15]);
void read_word (char i[25], char y[3], char x[3], char d[2], char w[15]);
int calculate_bonus (int y, int x, int dir, char w[15], int cond1, int cond2);
int check_cond_1 (char w[15], char s[3]);
int check_cond_2 (char w[15], char s[3]);


int main (){

    char game_board[15][15],string_bonus_1[3],string_bonus_2[3];
    char task_string[3],number_string[3],x_string[3],y_string[3],direction_string[2];
    char word[15], input[25];
    int number,task,condition_bonus_1=0, condition_bonus_2=0;
    int i,x,y,direction,bonus,word_length;
    int scor_player1=0,scor_player2=0;
    //             A B C D E F G H I J K L M N O P Q  R T S U V W X Y Z
    int scors[26]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    

    fgets(task_string, 3, stdin);
    task=atoi(task_string);
    
    memset(game_board,'.',sizeof(game_board));

    if(task == 0){
        print_board(game_board);
    }

    if(task == 1){
        fgets(number_string, 4, stdin);
        number = atoi(number_string);

        for (i = 0; i < number; i++){
            
            read_word(input, y_string, x_string, direction_string, word);
            x = atoi(x_string);
            y = atoi(y_string);
            direction = atoi(direction_string);

            word_length = strlen(word);
            if(direction == 1)
                scrieVerticala(game_board, word, word_length, y, x);
            else
                scrieOrizontala(game_board, word, word_length, y, x);
  
        }
        print_board(game_board);
    }

    if(task == 2){
        fgets(number_string, 4, stdin);
        number=atoi(number_string);

        for (i = 0; i < number; i++){
            
            read_word(input, y_string, x_string, direction_string, word);
            x = atoi(x_string);
            y = atoi(y_string);
            direction = atoi(direction_string);

            if(i%2 == 0)
                scor_player1 += scor(scors, word);
            else
                scor_player2 += scor(scors, word);
        }
        printf("Player 1: %d Points\n", scor_player1);
        printf("Player 2: %d Points", scor_player2);
    }

    if(task == 3){

        fgets(string_bonus_1, 3, stdin); getchar();
        fgets(string_bonus_2, 3, stdin); getchar();

        fgets(number_string, 4, stdin);
        number = atoi(number_string);

        for (i = 0; i < number; i++){
            condition_bonus_1 = 0;
            condition_bonus_2 = 0; 

            read_word(input, y_string, x_string, direction_string, word);
            x = atoi(x_string);
            y = atoi(y_string);
            direction = atoi(direction_string);

            word_length = strlen(word);
            condition_bonus_1 = check_cond_1(word, string_bonus_1);
            condition_bonus_2 = check_cond_2(word, string_bonus_2);
           
            bonus = calculate_bonus(y, x, direction, word, condition_bonus_1, condition_bonus_2);

            if(i%2 == 0)
                scor_player1 += scor(scors, word)*bonus;
            else
                scor_player2 += scor(scors, word)*bonus; 
        }
        printf("Player 1: %d Points\n",scor_player1);
        printf("Player 2: %d Points",scor_player2);
    }
    
    if(task==4){

        fgets(string_bonus_1, 3, stdin); getchar();
        fgets(string_bonus_2, 3, stdin); getchar();

        fgets(number_string, 4, stdin);
        number = atoi(number_string);

        char used_words[100][15];
        int aparitii_litere[26] = {0};

        for (i = 0; i < number; i++){

            condition_bonus_1 = 0;
            condition_bonus_2 = 0;
            fgets(input, 25, stdin);
            sscanf(input,"%d %d %d %s",&y,&x,&direction,word);

            /*read_word(input, y_string, x_string, direction_string, word);
            x = atoi(x_string);
            y = atoi(y_string);
            direction = atoi(direction_string);
*/
            int l, j;
            l = strlen(word);

            if(direction == 1)
                scrieVerticala(game_board, word, l, y, x);
            else
                scrieOrizontala(game_board, word, l, y, x);

            for(j = 0; j < l; j++){
                used_words[i][j] = word[j];
                aparitii_litere[word[j]-'A']++;
            }
            used_words[i][j] = '\0';
        }

        int am_gasit = 0,j;
        for(j = 0; j < NUM_WORDS && am_gasit ==0; j++){
            int i, ok = 0;
            
            //VERIFICAM DACA CUVANTUL A MAI FOST FOLOSIT
            //PRIN INTERMEDIUL VARIABILEI OK
            for(i = 0; i < number && ok==0; i++){
                if(strcmp(words[j], used_words[i]) == 0)
                    ok = 1;
            }
            int l2;
            l2 = strlen(words[j]);

            //CAUTAM IN MATRICE DOAR DACA OK=0 SI PRIMA LITERA EXISTA PE TABLA
            if(ok == 0 && aparitii_litere[words[j][0]-'A'] != 0){
                int linie, coloana;
                for(linie = 0; linie < 15 && am_gasit == 0; linie++){
                    for(coloana = 0; coloana < 15 && am_gasit == 0; coloana++){
                        if(game_board[linie][coloana] == words[j][0]){
                            int scris = 0, v, bun;
                            //VERIFICAM DACA CUVANTUL INCAPE PE ORIZONTALA
                            if(14-coloana >= l2-1){
                                bun = 0;
                                //VERIFICAM DACA SE INTERSECTEAZA CU ALTE CUVINTE
                                for(v = coloana+1; v < coloana+l2; v++)
                                    if(game_board[linie][v] != '.')
                                        bun = 1;
                                if(bun == 0){
                                    scrieOrizontala(game_board, words[j], l2, linie, coloana);
                                    am_gasit = 1;
                                    scris = 1;
                                }
                            }
                            //VERIFICAM DACA NU A FOST DEJA SCRIS ORIZONTAL
                            //SI DACA INCAPE PE VERTICALA
                            if(scris == 0 && 14-linie >= l2-1){
                                bun = 0;
                                //VERIFICAM DACA SE INTERSECTEAZA CU ALTE CUVINTE
                                for(v = linie+1; v < linie+l2 && bun == 0; v++)
                                    if(game_board[v][coloana] != '.')
                                        bun = 1;
                                if(bun == 0){
                                    scrieVerticala(game_board, words[j], l2, linie, coloana);
                                    am_gasit = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        print_board(game_board);
    }

    if(task==5){

        fgets(string_bonus_1, 3, stdin); getchar();
        fgets(string_bonus_2, 3, stdin); getchar();

        fgets(number_string, 4, stdin);
        number = atoi(number_string);

        char used_words[100][15];
        int aparitii_litere[26] = {0};

        for (i = 0; i < number; i++){

            condition_bonus_1 = 0;
            condition_bonus_2 = 0;
            read_word(input, y_string, x_string, direction_string, word);
            x = atoi(x_string);
            y = atoi(y_string);
            direction = atoi(direction_string);

            //CALCULAM PUNCTAJELE PENTRU FIECARE MUTARE DATA
            condition_bonus_1 = check_cond_1(word,string_bonus_1);
            condition_bonus_2 = check_cond_2(word,string_bonus_2);
            
            bonus = calculate_bonus(y, x, direction, word, condition_bonus_1, condition_bonus_2);

            if(i%2 == 0)
                scor_player1 += scor(scors, word)*bonus;
            else
                scor_player2 += scor(scors, word)*bonus;
            
            int l, j;
            l = strlen(word);

            if(direction == 1)
                scrieVerticala(game_board, word, l, y, x);
            else
                scrieOrizontala(game_board, word, l, y, x);

            //ACTUALIZAM CUVINTELE FOLOSITE SI LITERELE EXISTENTE PE TABLA
            for(j = 0; j < l; j++){
                used_words[i][j] = word[j];
                aparitii_litere[word[j]-'A']++;
            }
        }

        int j;// O VARIABILA CARE INDICA POZITIA IN words
        int max_j = -1, max_x = -1, max_y = -1, max_dir = -1, max_score = 0,max_l; 
        //max_* PARAMETRII CUVANTULUI CAUTAT
        int bonus_cuv = 1, cond1 = 0, cond2 = 0, scor_cuv;
    

        for(j = 0; j < NUM_WORDS; j++){
            int i, ok = 0;
            //VERIFICAM DACA CUVANTUL A MAI FOST FOLOSIT
            for(i = 0; i < number && ok == 0; i++){
                if(strcmp(words[j], used_words[i]) == 0)
                    ok = 1;
            }
            int l2;
            l2 = strlen(words[j]);

            //CAUTAM IN MATRICE DOAR DACA OK=0 SI PRIMA LITERA EXISTA PE TABLA
            if(ok == 0 && aparitii_litere[words[j][0]-'A'] != 0){
                int linie, coloana;
                for(linie = 0; linie < 15; linie++){
                    for(coloana = 0; coloana < 15; coloana++){
                        if(game_board[linie][coloana] == words[j][0]){
                            int v, bun;
                            //VERIFICAM DACA INCAPE PE ORIZONTALA
                            if(14-coloana >= l2-1){
                                bun = 0;
                                //VERIFICAM DACA SE INTERSECTEAZA CU ALTE CUVINTE
                                for(v = coloana+1; v < coloana+l2; v++)
                                    if(game_board[linie][v] != '.')
                                        bun = 1;
                                if(bun == 0){
                                    int word_l;
                                    cond1 = 0; cond2 = 0;
                                    word_l = strlen(words[j]);
                                    cond1 = check_cond_1(words[j], string_bonus_1);
                                    cond2 = check_cond_2(words[j], string_bonus_2);

                                    bonus_cuv = calculate_bonus(linie, coloana, 0, words[j], cond1, cond2);
                                    scor_cuv = scor(scors, words[j])*bonus_cuv;
                                    //DACA CUVANTUL GASIT ARE ACELASI PUNCTAJ CU CEL MEMORAT PANA ACUM
                                    //SE ALEGE CEL POZITIONAT CAT MAI STANGA SUS
                                    if(scor_cuv == max_score){
                                        if((linie < max_y) || (linie == max_y && coloana < max_x)){
                                            max_score = scor_cuv;
                                            max_x = coloana;
                                            max_y = linie;
                                            max_dir = 0;
                                            max_j = j;
                                            max_l = word_l;
                                        }
                                        
                                    }
                                    //DACA SE GASESTE PRIMUL CUVANT CARE POATE ADUCE VICTORIA SAU REMIZA,
                                    //SAU UN CUVANT CU PUNCTAJ MAI MARE, SE ACTUALIZEAZA PARAMETRII max_*
                                    if(scor_cuv > max_score && scor_cuv >= scor_player1 - scor_player2){
                                        max_score = scor_cuv;
                                        max_x = coloana;
                                        max_y = linie;
                                        max_dir = 0;
                                        max_j = j;
                                        max_l = word_l;
                                    }
                                    
                                }
                            }
                            //VERIFICAM DACA INCAPE PE VERTICALA
                            if(14-linie >= l2-1){
                                bun = 0;
                                //VERIFICAM DACA SE INTERSECTEAZA CU ALTE CUVINTE
                                for(v = linie+1; v < linie+l2 && bun == 0; v++)
                                    if(game_board[v][coloana] != '.')
                                        bun = 1;
                                if(bun == 0){
                                    int word_l; 
                                    cond1 = 0; cond2 = 0;
                                    word_l = strlen(words[j]);
                                    cond1 = check_cond_1(words[j], string_bonus_1);
                                    cond2 = check_cond_2(words[j], string_bonus_2);
                                    
                                    bonus_cuv = calculate_bonus(linie, coloana, 1, words[j], cond1, cond2);
                                    scor_cuv = scor(scors, words[j])*bonus_cuv;
                                    //DACA CUVANTUL GASIT ARE ACELASI PUNCTAJ CU CEL MEMORAT PANA ACUM
                                    //SE ALEGE CEL POZITIONAT CAT MAI STANGA SUS
                                    if(scor_cuv == max_score){
                                        if((linie < max_y) || (linie == max_y && coloana < max_x)){
                                            max_score = scor_cuv;
                                            max_x = coloana;
                                            max_y = linie;
                                            max_dir = 1;
                                            max_j = j;
                                            max_l = word_l;
                                        }
                                    }
                                    //DACA SE GASESTE PRIMUL CUVANT CARE POATE ADUCE VICTORIA SAU REMIZA
                                    //SAU UN CUVANT CU PUNCTAJ MAI MARE SE ACTUALIZEAZA PARAMETRII max_*
                                    if(scor_cuv > max_score && scor_cuv >= scor_player1 - scor_player2){
                                        max_score = scor_cuv;
                                        max_x = coloana;
                                        max_y = linie;
                                        max_dir = 1;
                                        max_j = j;
                                        max_l = word_l;
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }

        //SE VERIFICA DACA S-A GASIT UN CUVANT, DACA DA SE SCRIE PE TABLA
        if(max_j == -1)
            printf("Fail!");
        else{
            if(max_dir == 0){
                scrieOrizontala(game_board, words[max_j], max_l, max_y, max_x);
            }
            else{
                scrieVerticala(game_board, words[max_j], max_l, max_y, max_x);
            }
            print_board(game_board);
        }
    }

    if(task==6){

        fgets(string_bonus_1, 3, stdin); getchar();
        fgets(string_bonus_2, 3, stdin); getchar();

        fgets(number_string, 4, stdin);
        number = atoi(number_string);

        //VARIABILELE URMATOARE AU ACEEIASI SEMNIFICATIE CA LA TASK-URILE ANTERIOARE
        char used_words[100][15];
        int aparitii_litere[26] = {0};
        int j;
        int max_j=-1,max_x=-1,max_y=-1,max_dir=-1,max_score=0,max_l;
        int bonus_cuv=1,cond1=0,cond2=0,scor_cuv;

        for (i=0;i<number;i++){
            //REINITIALIZAM PARAMETRII max_* INAINTE DE FIECARE MUTARE
            max_j=-1,max_x=-1,max_y=-1,max_dir=-1,max_score=0;
            bonus_cuv=1,cond1=0,cond2=0,scor_cuv=0,max_l=-1;

            condition_bonus_1 = 0;
            condition_bonus_2 = 0;
            read_word(input, y_string, x_string, direction_string, word);
            x = atoi(x_string);
            y = atoi(y_string);
            direction = atoi(direction_string);

            word_length = strlen(word);
            condition_bonus_1 = check_cond_1(word, string_bonus_1);
            condition_bonus_2 = check_cond_2(word, string_bonus_2);
            
            bonus = calculate_bonus(y, x, direction, word, condition_bonus_1, condition_bonus_2);
            scor_player1 += scor(scors, word)*bonus;

            int l, i_tot;
            //i CONTORIZEAZA NUMARUL DE MISCARI ALE UNUI JUCATOR
            //i_tot CONTORIZEAZA NUMARUL TOTAL DE MISCARI
            l = strlen(word);

            if(direction == 1)
                scrieVerticala(game_board, word, l, y, x);
            else
                scrieOrizontala(game_board, word, l, y, x);

            //ACTUALIZAM CUVINTELE FOLOSITE PE MASURA CE SUNT PUSE PE TABLA
            for(j = 0; j <l ; j++){
                used_words[2*i][j] = word[j];
                aparitii_litere[word[j]-'A']++;
            }
            used_words[2*i][j]='\0';
            
            for(j = 0; j < NUM_WORDS; j++){
                
                int ok = 0;
                //VERIFICAM DACA CUVANTUL A MAI FOST FOLOSIT PANA ACUM
                for(i_tot = 0;i_tot <= 2*i+1 && ok==0; i_tot++){
                    if(strcmp(words[j], used_words[i_tot]) == 0)
                        ok = 1;
                }
                int l2;
                l2 = strlen(words[j]);
                //CAUTAM IN MATRICE DOAR DACA OK=0 SI PRIMA LITERA EXISTA PE TABLA
                if(ok == 0 && aparitii_litere[words[j][0]-'A'] != 0){
                    int linie, coloana;
                    for(linie =0 ; linie < 15 ; linie++){
                        for(coloana = 0; coloana < 15; coloana++){
                            if(game_board[linie][coloana] == words[j][0]){
                                int v, bun;
                                //VERIFICAM DACA POATE FI SCRIS PE ORIZONTALA
                                if(14 - coloana >= l2-1){
                                    bun = 0;
                                    for(v = coloana+1; v < coloana+l2; v++)
                                        if(game_board[linie][v] != '.')
                                            bun = 1;
                                    if(bun == 0){
                                        int word_l;
                                        cond1 = 0; cond2 = 0;
                                        word_l = strlen(words[j]);
                                        cond1 = check_cond_1(words[j], string_bonus_1);
                                        cond2 = check_cond_2(words[j], string_bonus_2);
                                        
                                        bonus_cuv = calculate_bonus(linie, coloana, 0, words[j], cond1, cond2);
                                        scor_cuv = scor(scors, words[j])*bonus_cuv;
                                        if(scor_cuv == max_score){
                                            if(linie < max_y || (linie == max_y && coloana < max_x)){
                                                max_score = scor_cuv;
                                                max_x = coloana;
                                                max_y = linie;
                                                max_dir = 0;
                                                max_j = j;
                                                max_l = word_l;
                                            }
                                        }
                                        if(scor_cuv > max_score ){
                                            max_score = scor_cuv;
                                            max_x = coloana;
                                            max_y = linie;
                                            max_dir = 0;
                                            max_j = j;
                                            max_l = word_l;
                                        }
                                    }
                                }
                                //VERIFICAM DACA POATE FI SCRIS PE VERTICALA
                                if(14 - linie >= l2-1){
                                    bun = 0;
                                    for(v = linie+1; v < linie+l2 && bun == 0; v++)
                                        if(game_board[v][coloana] != '.')
                                            bun = 1;
                                    if(bun == 0){
                                        int word_l; 
                                        cond1 = 0; cond2 = 0;
                                        word_l = strlen(words[j]);
                                        cond1 = check_cond_1(words[j], string_bonus_1);
                                        cond2 = check_cond_2(words[j], string_bonus_2);
                                         
                                        bonus_cuv = calculate_bonus(linie, coloana, 1, words[j], cond1, cond2);
                                        scor_cuv = scor(scors, words[j])*bonus_cuv;
                                        if(scor_cuv == max_score){
                                            if(linie < max_y || (linie == max_y && coloana < max_x)){
                                                max_score = scor_cuv;
                                                max_x = coloana;
                                                max_y = linie;
                                                max_dir = 1;
                                                max_j = j;
                                                max_l = word_l;
                                            }
                                        }
                                        if(scor_cuv > max_score){
                                            max_score = scor_cuv;
                                            max_x = coloana;
                                            max_y = linie;
                                            max_dir = 1;
                                            max_j = j;
                                            max_l = word_l;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } 

                //printf("%s",words[max_j]);
            }
            l = strlen(words[max_j]);
            //ACTUALIZAM CUVINTELE FOLOSITE SI LITERELE AFLATE PE TABLA
            //DUPA FIECARE MUTARE A JUCATORULUI 2
            for(j = 0; j < l; j++){
                used_words[2*i+1][j] = words[max_j][j];
                aparitii_litere[words[max_j][j]-'A']++;
            }
            used_words[2*i+1][j] = '\0';
            if(max_dir == 0){
                scrieOrizontala(game_board, words[max_j], max_l, max_y, max_x);
            }
            else{
                scrieVerticala(game_board, words[max_j], max_l, max_y, max_x);
            }
            //ACTUALIZAM SCORUL JUCATORULUI 2
            scor_player2+=max_score;
            //printf("\npl1:%d  pl2:%d",scor_player1,scor_player2);
        }
        print_board(game_board);
        if(scor_player1 > scor_player2){
            printf("Player 1 Won!");
        }else{
            printf("Player 2 Won!");
        }
    }
    return 0;
}

void scrieOrizontala(char matrice[15][15], char cuvant[],int lungime, int linie, int coloana){
    int i;
    for(i=0;i<lungime;i++){
        matrice[linie][coloana+i]=cuvant[i];
    }
}
void scrieVerticala(char matrice[15][15], char cuvant[],int lungime, int linie, int coloana){
    int i;
    for(i=0;i<lungime;i++){
        matrice[linie+i][coloana]=cuvant[i];
    }
}
int scor(int s[26],char word[15]){
    int l,i,scor=0;
    l=strlen(word);
    for(i=0;i<l;i++){
        scor+=s[word[i]-'A'];
    }
    return scor;
}
void read_word(char i[25], char y[3], char x[3], char d[2], char w[15]){
    int length, j, k;
    
    fgets(i, 25, stdin);
    length = strlen(i);
    i[length-1] = '\0';
    length = strlen(i);
    j = 0; k = 0;
    while(i[j] != ' ')
        y[k++] = i[j++];
    y[k] = '\0';
    k = 0; j++;

    while(i[j] != ' ')
        x[k++] = i[j++];
    x[k] = '\0';
    k = 0; j++;

    while(i[j] != ' ')
        d[k++] = i[j++];
    d[k] = '\0';
    k = 0; j++;

    while(j < length )
        w[k++] = i[j++];
    w[k] = '\0';
}
int calculate_bonus(int y, int x, int dir, char w[15], int cond1, int cond2){
    int k, l, bonus=1;
    l = strlen(w);
    if(dir == 1){
        for(k = 0; k < l; k++){
            if(bonus_board[y+k][x] == 1 && cond1 == 1)
                bonus *= 2;
            if(bonus_board[y+k][x] == 2 && cond2 == 1)
                bonus *= 3;
        }
    }
    if(dir == 0){
        for(k = 0; k < l; k++){
            if(bonus_board[y][x+k] == 1 && cond1 == 1)
                bonus *= 2;
            if(bonus_board[y][x+k] == 2 && cond2 == 1)
                bonus *= 3;
        }
    }
    return bonus;
}
int check_cond_1 (char w[15], char s[3]){
    if (strstr(w, s))
        return 1;
    return 0;
}
int check_cond_2(char w[15], char s[3]){
    int l;
    l = strlen(w);
    if (w[l-1] == s[1])
        if(w[l-2] == s[0]){
            return 1;
        }
    return 0;
}

