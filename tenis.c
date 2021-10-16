#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structura pentru jucator:
typedef struct Player { 
   char *last_name;
   char *first_name;
   int score;
} Player;
 
//Structura pentru tara:
typedef struct Country {
   char *name;
   int nr_players;
   int global_score;
   Player *players;
} Country; 


struct Elem {
    Country* country;
    struct Elem *next, *prev;
};
typedef struct Elem countryNode;

//ADAUGA UN NOD LA FINALUL LISTEI
void addAtEnd(countryNode **head, Country *aux) {

    countryNode *new_countryNode = (countryNode*)malloc(sizeof(countryNode));

    new_countryNode->country = aux;
    
    countryNode *last_countryNode = (*head)->prev;

    new_countryNode->next = *head;
    new_countryNode->prev = last_countryNode;
    last_countryNode->next = new_countryNode;
    (*head)->prev = new_countryNode;
}

void printCountries_In_File(countryNode **head, FILE *file_r) { ////PARCURGE LISTA SI O AFISEAZA IN FISIER
        countryNode* headcopy;
        headcopy = *head;

        while(headcopy->next != *head) {
           fprintf(file_r, "%s\n", headcopy->next->country->name);
           headcopy = headcopy->next;
        }
}

void eliminateCountry(countryNode **head, int indice) { ////ELIMINA O TARA DIN LISTA IN FUNCTIE DE POZITIA SCORULUI MINIM
    countryNode *headcopy;                              ////CALCULATA CU FUNCTIA indice_minim()
    headcopy = *head;
    countryNode *aux;

    int p = 0;

    do { //PARCURG LISTA PANA AJUNG LA POZITIA DORITA
        p++;
        aux = headcopy;
        headcopy = headcopy->next;
    } while (headcopy->next != *head && p < indice+1);

    if(p == indice+1) { //CAND AJUNG LA POZITIA DORITA FAC LEGATURILE INTRE NODURI 
        aux->next = headcopy->next;
        (headcopy->next)->prev = aux;
        free(headcopy);//ELIBEREZ NODUL DE STERS
        return;
     }
}

int indice_minim(float *score_vector, int nr_country) { ////PARCURGE VECTORUL DE SCORURI SI RETURNEAZA POZITIA MINIMULUI
    float min_score = 999999;
    int indice, i;

    for(i = 0; i < nr_country; i++) {
        if(score_vector[i] < min_score) {
            min_score = score_vector[i];
            indice = i;                  //POZITIA MINIMULUI
        }
    }
    return indice;
}

int is_power_of_two(int n) ////VERIFIC DACA UN NUMAR ESTE PUTERE DE 2 
{
    while( n != 1) {      
        if(n % 2 != 0)////DACA RESTUL IMPARTIRII LA 2 NU ESTE 0 ATUNCI NR NU ESTE PUTERE DE 2 SI SE RETURNEAZA 0
            return 0;
        n = n / 2;      ////IMPARTIM NUMARUL LA 2 PANA CAND REZULATUL VA FI 1 
    }
    return 1;
}

        ////////////CERINTA 3/////////////

struct Elem2 { ////STRUCTURA PENTRU STIVA CU TIP DE DATA "nod de lista"
    countryNode *stack_country;
    struct Elem2 *stack_next;
};
typedef struct Elem2 Stack_CountryNode;

void push(Stack_CountryNode**top, countryNode *country) { //ADAUGA IN STIVA UN NOD, RESPECTIV O TARA
    Stack_CountryNode* newNode=(Stack_CountryNode*)malloc(sizeof(Stack_CountryNode));  
    newNode->stack_country = country;
    newNode->stack_next = *top;
    *top = newNode;
}

int StackisEmpty(Stack_CountryNode* top){
    return top==NULL;
}

countryNode* pop(Stack_CountryNode**top) { //SCOATE DIN STIVA CATE O TARA 
    if (StackisEmpty(*top)) exit(1); 
    Stack_CountryNode *temp = (*top);
    countryNode *aux = temp->stack_country; 
    *top=(*top)->stack_next;
    free(temp);
    return aux;
}

//FUNCTIE PENTRU ADAUGAREA IN STIVA TOATE NODURILE/TARILE DIN LISTA 
void AddCountries_In_stack(countryNode **head, Stack_CountryNode **stackTop) {
        countryNode* headcopy;
        headcopy = *head;

        while(headcopy->next != *head) {//PARCURG LISTA 
            push(*(&stackTop), headcopy->next);
            headcopy = headcopy->next;
        }
}

////COADA DE MECIURI////
struct Elem3 {
    Player* players;
    struct Elem3 *next_queue;
};
typedef struct Elem3 queueNode;

struct Q {
    queueNode *front, *rear;
};
typedef struct Q Queue;

Queue *createQueue() {//CREAZA CODA DE MECIURI
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
        return NULL;

    q->front = q->rear = NULL;

    return q;
}

void enQueue(Queue *q, Player *players) {//ADAUGA UN MECI IN COADA-vector de 2 jucatori
    queueNode *newNode = (queueNode *)malloc(sizeof(queueNode));
    newNode->players = (Player*)malloc(2*sizeof(Player));
    newNode->players = players;
    newNode->next_queue = NULL;

    if (q->rear == NULL) {
        q->rear = newNode;
    }
    else {
        (q->rear)->next_queue = newNode;
        (q->rear) = newNode;
    }
    if (q->front == NULL)
        q->front = q->rear;
}

int queueisEmpty(Queue*q) {
    return (q->front==NULL);
} 

Player* deQueue_player(Queue *q) {//RETURNEAZA VECTOR DE 2 JUCATORI 
    queueNode *aux;
    Player *d = (Player*)malloc(sizeof(Player)*2);
    if (queueisEmpty(q)) exit(1);
    aux = q->front;
    d = aux->players;
    q->front=(q->front)->next_queue;
    free(aux);
    return d;
}

////////////////////CERINTA 4////////////////////////
struct N{//NOD ARBORE
    Player player;
    struct N *left, *right;
};
typedef struct N NodeBST;

NodeBST* newNode(Player new_player) { 
    NodeBST* node = (NodeBST*)malloc(sizeof(NodeBST));
    node->player = new_player;
    node->left = node->right = NULL;
    return node;
}

Player compare_players (Player player1, Player player2){ //RETURNEAZA JUCATORUL FAVORIT DPDV LEXICOGRAFIC
    int i1 = strcmp(player1.first_name, player2.first_name);
    if(i1 < 0) return player1;
    if(i1 > 0) return player2;
    if(i1 == 0){
        int i2 = strcmp(player1.last_name, player2.last_name);
        if(i2 < 0) return player1;
        if(i2 > 0) return player2;
    }
}

NodeBST* insert(NodeBST* node, Player new_player) { //ADAUGA UN JUCATOR IN BST IN FUNCTIE DE SCOR 
    if (node == NULL) 
        return newNode(new_player);

    if (new_player.score < node->player.score) 
        node->left = insert(node->left, new_player);
    else if (new_player.score > node->player.score)
        node->right = insert(node->right, new_player);
        else if(new_player.score == node->player.score){
            Player chose_player = compare_players(new_player, node->player);
            node->player = chose_player;
        }
    return node;
}

void reverse_inorder(NodeBST *root, FILE* file_r) {//AM MODIFICAT FUNCTIA DE PARCURGERE IN INORDINE
        if (root){                                 //ASTFEL INCAT SA PARURCURGA ARBORELE IN ORDINE INVERSA
        reverse_inorder(root->right, file_r);              //ADICA IN ORDINEA CRESCATORE A SCORURILOR  
        fprintf(file_r,"%s %s %d\n",root->player.first_name, root->player.last_name, root->player.score);
        reverse_inorder(root->left, file_r);
    }
}

//RETURNEAZA NUMARUL DE JUCATORI CUPRINSI INTRE ALTI 2 JUCATORI
//FUNCTIA ESTE PRELUATA DE PE www.geeksforgeeks.com SI MODIFICATA PENTRU
//NEVOILE CERINTEI 
int count_players_between(NodeBST *root, Player player1, Player player2) {
    static int count_players = 0;
    if(root == NULL)
        return 0; 

    if(player1.score < root->player.score) 
        count_players_between(root->left, player1, player2); 

    if(player1.score < root->player.score && player2.score > root->player.score) {
        count_players++;
    }

    if (player2.score > root->player.score) 
        count_players_between(root->right, player1, player2); 
    return count_players;
} 

int player_exist(NodeBST *root, Player player) {//RETURNEAZA 0 DACA JUCATORUL NU EXISTA IN BST SI 1 DACA EXISTA
        static int ver = 0;
        if (root){
            player_exist(root->right, player);
            //PARCURGE SI COMPARA NUMELE JUCATORILOR 
            if(strcmp(player.first_name, root->player.first_name) == 0 && strcmp(player.last_name, root->player.last_name) == 0)
                ver = 1;
            player_exist(root->left, player);
        }
    return ver;
}


int main(int argc, char *argv[])
{
    char *cerinte, *date, *rezultate;
    cerinte = argv[1];
    date = argv[2];
    rezultate = argv[3];

    FILE *file_c, *file_d, *file_r;
    file_c = fopen(cerinte, "rt");
    file_d = fopen(date, "rt");


    int c1, c2, c3, c4, c5;
    fscanf(file_c, "%d %d %d %d %d", &c1, &c2, &c3, &c4, &c5);
    fclose(file_c);
    countryNode *head = (countryNode*)malloc(sizeof(countryNode)); //CREEZ LISTA CIRCULARA CU SANTINELA//
    head->next = head;
    head->prev = head;

    int nr_country;
    fscanf(file_d, "%d", &nr_country); //CITESC NUMARUL DE TARI

        /////////////////CERINTA 1///////////////
    if(c1 == 1) {
        int i, j;
        Country *aux; 
        char lenth1[20], lenth2[20],lenth3[20]; //FOLOSESC PENTRU CITIREA INITIALA A DATELOR SI PENTRU
                                            //ALOCAREA DINAMICA A VALORILOR DIN STRUCTURI
 
        for(i = 0; i < nr_country; i++) {

        	aux = (Country*)malloc(sizeof(Country));
            fscanf(file_d, "%d", &aux->nr_players); //CITESC NUMARUL DE JUCATORI DIN FIECARE TARA
           	aux->players = (Player*)malloc(sizeof(Player)*(aux->nr_players));

            fscanf(file_d, "%s", lenth1); //CITESC NUMELE TARII
            aux->name = (char*)malloc((sizeof(char)*strlen(lenth1))+1);
            strcpy(aux->name,lenth1);

            for(j = 0; j < aux->nr_players; j++) {
                fscanf(file_d, "%s %s %d", lenth2, lenth3, &aux->players[j].score);      ////CITESC NUME, PRENUME(IN lenth2 SI lenth3) SI SCORUL FIECARUI JUCATOR
                aux->players[j].first_name = (char*)malloc((sizeof(char)*strlen(lenth2))+1); ////ALOC SPATIU DE LUNGIME PARTICULARA
                aux->players[j].last_name = (char*)malloc((sizeof(char)*strlen(lenth3))+1);
                strcpy(aux->players[j].first_name, lenth2); ////copiezz in aux numele si prenumele din lenth2,3
                strcpy(aux->players[j].last_name, lenth3);
            }
            addAtEnd(&head, aux); //DUPA CE AM CITIT TOATE DATELE DESPRE O TARA, O ADAUG IN LISTA SI POCESUL SE REPETA DE "nr_counntry" ORI
        }
        fclose(file_d);
    }

        /////////////////CERINTA 2///////////////
    if(c2 == 1) {
        int i, j, h;
        float *score_vector, *score_sum;
        score_vector = (float*)malloc(sizeof(float)*nr_country);
        score_sum = (float*)malloc(sizeof(float)*nr_country);
        countryNode* headcopy;
        headcopy = head;

        for(i = 0; i < nr_country; i++) {
            score_sum[i] = 0;
            for(j = 0; j < headcopy->next->country->nr_players; j++) {
                score_sum[i] = score_sum[i] + headcopy->next->country->players[j].score;
            }
            score_vector[i] = score_sum[i]/headcopy->next->country->nr_players;
            headcopy = headcopy->next;
        }

        float min_score = 999999;
        int indice;
        float *aux_score;

        while(1) {

            indice = indice_minim(score_vector, nr_country); ////AFLU POZITIA VALORII MINIME DIN VECTORUL DE SCORURI
            eliminateCountry(&head, indice);                 ////ELIMIN NODUL DE PE POZITIA AFLATA MAI SUS

            aux_score = (float*)malloc(sizeof(float)*(nr_country));//aux-ul il aloc cu 1 in minus

            for(j = 0; j < indice; j++) {           //ELIMIN VALOAREA MINIMA DIN VECTORUL DE SCORURI
                aux_score[j] = score_vector[j];     //FOLOSINDU-MA DE UN VECTOR AUXILIAR
            }
            for(j = indice; j < nr_country; j++) {
                aux_score[j] = score_vector[j+1];
            }

            nr_country--; ////DECREMENTEZ NUMARUL DE TARI DEOARECE AM ELIMINAT O TARA DIN LISTA

            score_vector = realloc(score_vector, sizeof(float)*nr_country); //REALOC SPATIU PENTRU VECTORII
            score_sum = realloc(score_sum, sizeof(float)*nr_country);       //FOLOSITI PENTRU SCORURILE INITIALE
            
            for(h = 0; h < nr_country; h++) {    //COPIEZ TERMEN CU TERMEN ELEMENTELE DIN
                score_vector[h] = aux_score[h];  // aux_score IN score_vector
            }

            int k;
            k = is_power_of_two(nr_country);  ////DACA DUPA ELIMINARE SI DECREMENTAREA NUMARULUI DE TARI, ACESTA
            if(k == 1) {                      //// ESTE PUTERE DE 2, CICLUL WHILE SE OPRESTE 
                break;
            }
        }

        free(aux_score);
        free(score_vector);
        free(score_sum);
    }

    file_r = fopen(rezultate, "wt");            
    printCountries_In_File(&head, file_r);      

        //////////////CERINTA 3//////////////////

    if(c3 == 1) {
        Stack_CountryNode *stackTop = (Stack_CountryNode*)malloc(sizeof(Stack_CountryNode)); //CREEZ STIVA
        Stack_CountryNode *stack_winner = (Stack_CountryNode*)malloc(sizeof(Stack_CountryNode)); //CREEZ STIVA WINNER
        Stack_CountryNode *stack_BST = (Stack_CountryNode*)malloc(sizeof(Stack_CountryNode)); //CREEZ STIVA PE CARE O VOI FOLOSI PENTRU CERINTA 4


        AddCountries_In_stack(&head, &stackTop);//ADAUG NODURILE IN STIVA
        free(head); //ELIBEREZ/STERG LISTA DE CARE NU MAI AM NEVOIE
        countryNode *country_play1 = malloc(sizeof(countryNode)*nr_country);
        countryNode *country_play2 = malloc(sizeof(countryNode)*nr_country);
        country_play1->country->global_score = 0;
        country_play2->country->global_score = 0;

        int nr_etapa = 1;
        int winner = nr_country;
        while(winner != 1){
            country_play1 = realloc(country_play1, sizeof(countryNode));
            country_play2 = realloc(country_play2, sizeof(countryNode));


            int contor = nr_country;
            int i1, i2, i3;


            fprintf(file_r, "\n====== ETAPA %d ======\n\n", nr_etapa);
            nr_etapa++;

            while(contor != 0) {
                Queue* q;
                q = createQueue();
                country_play1 = pop(&stackTop); //SCOT DIN STIVA CATE 2 TARI
                country_play2 = pop(&stackTop);

                fprintf(file_r, "%s %d ----- %s %d", country_play1->country->name, country_play1->country->global_score,
                country_play2->country->name, country_play2->country->global_score);

                for(i1 = 0; i1 < country_play1->country->nr_players; i1++) {      //CREEZ MECIURILE CU JUCATORII CELOR 2 TARI
                    for(i2 = 0; i2 < country_play2->country->nr_players; i2++) {  //SI LE ADAUG IN COADA DE MECIURI
                        Player *game_players = (Player*)malloc(2*sizeof(Player));
                        game_players[0] = country_play1->country->players[i1];
                        game_players[1] = country_play2->country->players[i2];
                        enQueue(q, game_players);
                    }
                }

                int local_score1 = 0;
                int local_score2 = 0;
                int k1,k2;
                int max_score1 = 0;
                int max_score2 = 0;

                while(!queueisEmpty(q)) {//JUCAREA MECIURILOR SI CALCULAREA SCORURILOR 
                    for(k1 = 0; k1 < country_play1->country->nr_players; k1++) {
                        for(k2 = 0; k2 < country_play2->country->nr_players; k2++) {
                            Player *country_q_player = (Player*)malloc(2*sizeof(Player));
                            country_q_player = deQueue_player(q);//SCOT DIN COADA VECTOR DE 2 TARI//
                            
                            //AFISEZ IN FISIER MECIURILE//
                            fprintf(file_r, "\n%s %s %d vs %s %s %d", country_q_player[0].first_name, country_q_player[0].last_name, 
                                    country_play1->country->players[k1].score, country_q_player[1].first_name, country_q_player[1].last_name,
                                    country_play2->country->players[k2].score);
                            
                            if(max_score1 < country_play1->country->players[k1].score)//RETIN SCORUL MAXIM AL JUCATORILOR PENTRU
                                max_score1 = country_play1->country->players[k1].score;//FIECARE TARA
                            if(max_score2 < country_play1->country->players[k2].score)
                                max_score2 = country_play2->country->players[k2].score;

                            //CALCULEZ SCORURILE/MECI
                            if(country_play1->country->players[k1].score > country_play2->country->players[k2].score) {
                                country_play1->country->players[k1].score += 5;
                                local_score1 = local_score1 + 3;
                            }else if(country_play1->country->players[k1].score < country_play2->country->players[k2].score){
                                    country_play2->country->players[k2].score += 5;
                                    local_score2 = local_score2 + 3;
                                }else if(country_play1->country->players[k1].score == country_play2->country->players[k2].score){
                                    country_play1->country->players[k1].score += 2;
                                    country_play2->country->players[k2].score += 2;
                                    local_score1 = local_score1 + 1;
                                    local_score2 = local_score2 + 1;
                                }
                        }
                    }
                }

                if(local_score1 == local_score2) {//ADAUGAREA IN STIVA WINNER A TARILOR CASTIGATOARE
                                                  //SI CREAREA STIVEI PENTRU CERINTA 4 CU ULTIMELE 4 TARI
                    if(max_score1 > max_score2) {
                        push(&stack_winner, country_play1);
                        if(winner == 4) push(&stack_BST, country_play2);//(PENTRU BST)IN PENULTIMA ETAPA, TARILE CARE NU SE CALIFICA LE ADAUG IN STIVA
                        if(winner == 2) {push(&stack_BST, country_play2);push(&stack_BST, country_play1);}//IN ULTIMA ETAPA ADAUG AMBELE TARI ---adalog pasii urmatori
                        }
                    if(max_score1 < max_score2){
                        push(&stack_winner, country_play2);
                        if(winner == 4) push(&stack_BST, country_play1);
                        if(winner == 2) {push(&stack_BST, country_play1);push(&stack_BST, country_play2);}
                    }
                    if(max_score1 == max_score2) {
                        push(&stack_winner, country_play1);
                        if(winner == 4) push(&stack_BST, country_play2);
                        if(winner == 2) {push(&stack_BST, country_play2);push(&stack_BST, country_play1);}
                    }
                }
                if(local_score1 > local_score2) {
                    push(&stack_winner, country_play1);
                    if(winner == 4) push(&stack_BST, country_play2);
                    if(winner == 2) {push(&stack_BST, country_play2);push(&stack_BST, country_play1);}
                }
                if(local_score1 < local_score2) {
                    push(&stack_winner, country_play2);
                    if(winner == 4) push(&stack_BST, country_play1);
                    if(winner == 2) {push(&stack_BST, country_play1);push(&stack_BST, country_play2);}
                }

                country_play1->country->global_score += local_score1;
                country_play2->country->global_score += local_score2;
                fprintf(file_r, "\n\n");
                
                contor = contor - 2;
                free(q);
            }
            fprintf(file_r, "=== WINNER ===");
            stackTop = NULL;
            countryNode *country_winner; 
            for(i3 = 0; i3 < nr_country/2; i3++){//AFISEZ STIVA WINNER SI SCOT ELEMENTELE DIN EA, ADAUGANDU-LE IN STIVA INITIALA
                country_winner = pop(&stack_winner);
                fprintf(file_r, "\n%s --- %d", country_winner->country->name, country_winner->country->global_score);
                push(&stackTop, country_winner);
            }

            nr_country = nr_country/2;
            fprintf(file_r, "\n");
            winner = winner/2;
        }


        //////////////CERINTA 4///////////////
        NodeBST *bst_players = NULL;//CREEZ BST-ul
        if(c4 == 1){
            int i4, i5;
            countryNode *country_final;
            fprintf(file_r, "\n====== CLASAMENT JUCATORI ======\n");
            for(i4 = 0; i4 < 4; i4++){
                country_final = pop(&stack_BST);
                for(i5 = 0; i5 < country_final->country->nr_players; i5++){
                    bst_players = insert(bst_players, country_final->country->players[i5]);
                }
            }
            reverse_inorder(bst_players, file_r);//AFISEZ JUCATORII IN ORDINEA SCORURILOR
        }

        if(c5 == 1) {
            file_c = fopen(cerinte, "rt");
            char lenth_first1[20], lenth_last1[20], lenth_first2[20], lenth_last2[20];
            int score_src1, score_src2;
            fscanf(file_c, "%*[^\n]\n");//Sare peste prima linie

            fscanf(file_c, "%s %s %d", lenth_first1, lenth_last1, &score_src1);
            fscanf(file_c, "%s %s %d", lenth_first2, lenth_last2, &score_src2);

            Player player_src1, player_src2;

            player_src1.first_name = malloc(sizeof(char)*strlen(lenth_first1));
            player_src1.first_name = lenth_first1;
            player_src1.last_name = malloc(sizeof(char)*strlen(lenth_last1));
            player_src1.last_name = lenth_last1;
            player_src1.score = score_src1;

            player_src2.first_name = malloc(sizeof(char)*strlen(lenth_first2));
            player_src2.first_name = lenth_first2;
            player_src2.last_name = malloc(sizeof(char)*strlen(lenth_last2));
            player_src2.last_name = lenth_last2;
            player_src2.score = score_src2;

            if(!player_exist(bst_players,player_src2)) {
                fprintf(file_r, "\n%s %s nu poate fi identificat!", player_src2.first_name, player_src2.last_name);
            } else if(!player_exist(bst_players, player_src1)) {
                fprintf(file_r, "\n%s %s nu poate fi identificat!", player_src1.first_name, player_src1.last_name);
            }else{
                int count_players;
                if(player_src1.score < player_src2.score){
                    count_players = count_players_between(bst_players, player_src1, player_src2);
                    fprintf(file_r, "\n%d", count_players);
                }else if(player_src1.score > player_src2.score){
                    count_players = count_players_between(bst_players, player_src2, player_src1);
                    fprintf(file_r, "\n%d", count_players);
                }
            }

            fclose(file_c);
        }
    free(stackTop);
    free(stack_winner);
    free(stack_BST);
    free(country_play1);
    free(country_play2);
    }
    fclose(file_r);

    return 0;
}
