#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 1000

/*
ΠΑΟΥΛΙΝ ΚΟΜΙΝΙ
2022 2021 00090
dit21090@go.uop.gr
*/

/*
ΚΟΥΤΑΝΤΟΣ ΒΑΣΙΛΕΙΟΣ
2022 2021 ΧΧΧΧΧ
dit210@go.uop.gr
*/

typedef struct Node {
    int num;
    struct Node *next;
    struct Node *prev;
} Node;


int digits_only(const char *s) {    //this function flags if the string has anything but digits
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }
    return 1;
}

int get_next(Node** head_ref) {
    Node* tmp = *head_ref;      //CREATE TMP
    if (tmp->next != NULL) {    //IF LAST NODE
        int number = tmp->num;  //GET NUMBER
        tmp = tmp->next;        //SET HEAD = TO TMP
        *head_ref = tmp;
        return number;          //GET THE NUMBER
    } else {
        int number = tmp->num;
        while (tmp->prev != NULL)   //THE SAME BUT WITH A LOOP
        {
            tmp = tmp->prev;
        }
        *head_ref = tmp;
        return number;
    }
}

void push(Node** head_ref, int num) {

    Node* new_node = (Node*) malloc(sizeof(Node));  //CREATE NEW NODE

    new_node->num = num;    //PASS DATA 

    if(*head_ref == NULL) {
        *head_ref = new_node;   //CHECK IF THIS IS THE FISRT NODE
        new_node->next = NULL;  // SET ALL TO NULL
        new_node->prev = NULL;
    } else {
        new_node->next = *head_ref;         //IF NOT FIRST SET NEW NODE NEXT TO HEAD
        *head_ref = new_node;               //MOVE HEAD TO NEW NODE
        new_node->next->prev = *head_ref;   //POINT OLD NODE PREV TO NEWNODE
        new_node->prev = NULL;              
    }
}

int pop_last(Node** head_ref) {
    if (head_ref == NULL){
        printf("Empty");    //CHECK FOR EMPTY LIST
    }
    Node* tmp = *head_ref;  //CREATE TMP

    while (tmp->next->next != NULL) {   // GO TO THE END
        tmp = tmp->next;
    }
    Node* tmp2 = tmp;   //CREATE TMP2
    tmp = tmp->next;    //MOVE TMP TO NEXT
    int num = tmp->num; //STORE THE NEMBER TO A NUM 
    tmp2->next = NULL;  //SET TMP2 TO NULL
    free(tmp);
    return num;         
}

int pop(Node** head_ref) {

    if(*head_ref == NULL){
        printf("List is empty");    //CHECK IF LIST IS EMPTY
        return -1;
    }
    Node* tmp1 = *head_ref;         //CREATE 2 TMPS POINTED TO HEAD
    Node* tmp2 = *head_ref;
    tmp1 = tmp1->next;              //MOVE TMP1 TO NEXT
    *head_ref = tmp1;               //SET HEAD TO TMP1
    int num = tmp2->num;            //GET NUM
    free(tmp2);                     //FREE TMP2 (LAST HEAD)
    return num;                     //RETURN THE DATA (NUMBER)
}

int listLength(Node** head_ref ) {
    Node* tmp = *head_ref;      //CREATE TMP
    int size = 0;
    while (tmp != NULL)         //LOOP TO THE END
    {
        ++size;                 //ADD ONE TO THE COUNTER
        tmp = tmp->next;        
    }
    return size;                //GET THE SIZE OF THE LIST
}

void deallocate(Node** head_ref) {
    Node* tmp = *head_ref;      //CREATE TMP POINTED TO HEAD
    while (tmp != NULL) {
        Node* aux = tmp;        //USE WHILE LOOP TO GO THE END
        tmp = tmp->next;
        free(aux);
    }
    *head_ref = NULL;
}

void swap(char *str1, char *str2) {
    char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
    strcpy(temp, str1);         //CREATE A TMP AND USE IT TO SWAP THE STINGS
    strcpy(str1, str2);
    strcpy(str2, temp);
    free(temp);
}

void show_StE(Node** head_ref) {
    Node *tmp = *head_ref;      //CREATE TMP
    if (*head_ref == NULL)      //CHECH IF EMPTY
    {
       printf("The List is empty\n");
       return;
    }
    while (tmp != NULL) {   //PRINT FROM START TO END 
        printf("%d", tmp->num);
        tmp = tmp->next;
    }
}

void show_EtS(Node** head_ref) {
    Node *tmp = *head_ref;
    if (*head_ref == NULL)
    {
       printf("The List is empty\n");   //IF EMPTY
       return;
    }

    while (tmp->next != NULL) tmp = tmp->next; // GO THE END

    while (tmp != NULL) {           //LOOP TO START
        printf("%d", tmp->num);     //PRINT NUMBERS
        tmp = tmp->prev;
    }
}

int is_empty(Node** head_ref) {
    return *head_ref == NULL;   //CHECK IF LIST IS EMPTY
}

void filltheDLL(Node** N, char *num) {
 
    int len1 = strlen(num);        //GET THE NUMBERS LENGHT

    for (int i = 0; i < len1; i++) { //PUSH EVERY NUMBER TO THE LIST/STACK WITH PUSH() 
        push(N, num[i] - '0');    //MAKING THEM INTEGERS WIHT ""( - '0' )""
    }
}

void DLLtoString(Node** RESULT, char* result) { //DOUBLE LINK LIST TO STRING
    while (!is_empty(RESULT)) { 
        char N = pop(RESULT) + '0';     //POP THE ITEAM TO A CHAR
        char char_str[2] = {N, '\0'};   // ADD THE END CHARACTER
        strcat(result, char_str);       //ADD THE CHAT TO THE MAIN STRING
    }
}

void add(Node** NUM1, Node** NUM2, Node** RESULT) {

    int rem = 0;

    while (!is_empty(NUM1) || !is_empty(NUM2)) {  //WHILE THE STACK ISNT EMPTY
        int n1 = is_empty(NUM1) ? 0 : pop(NUM1);  //POP THE NUMBERS
        int n2 = is_empty(NUM2) ? 0 : pop(NUM2);

        int sum = n1 + n2 + rem;    // ADD NUMBERS WITH THE REMENDER
        push(RESULT, sum % 10);        // PUSH TO STACK3 THE MOD
        rem = sum / 10;             // HOLD THE DIV TO THE REMENDER
    }
    if (rem != 0) push(RESULT, rem);   // AND LAST IF WE HAVE REM ADD IT TO STACK3

}

void sub(Node** NUM1, Node** NUM2, Node** RESULT) {

    int borrow = 0;

    while (!is_empty(NUM1) || !is_empty(NUM2)) {  //WHILE THE STACK ISNT EMPTY
        int n1 = is_empty(NUM1) ? 0 : pop(NUM1);  //POP THE NUMBERS
        int n2 = is_empty(NUM2) ? 0 : pop(NUM2);

        int diff = n1 - n2 - borrow;            //SUBTRACT THE NUMBER WITH THE BORROW

        if (diff < 0) {                         //CHECK THE DIFF 
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        push(RESULT, diff);    // PUSH THE DIFF
    }
}


void mult(Node** NUM1, Node** NUM2, Node** RESULT) {

    int lenS1 = listLength(NUM1);
    int lenS2 = listLength(NUM2);
    int k = 0, rem = 0;
    int ans[lenS1+lenS2];

    for(int i=0; i<lenS1; i++) {

        int num1 = get_next(NUM1);

        for(int j=0; j<lenS2; j++) {

            int num2 = get_next(NUM2);
            int sum = num1 * num2 + rem;
            push(RESULT, sum % 10);
            rem = sum / 10;
        }
        if (rem > 0){
            push(RESULT, rem);
        }
        for (int j = 0; j < k; j++) {
            push(RESULT,0);
        }

        k++; 
    }
    show_StE(RESULT);
    rem = 0;
    int sum = 0;
    while (!is_empty(RESULT))
    {
        sum = sum * 10 + pop_last(RESULT) + rem;
        rem = sum / 10;
        sum %= 10;
    }
    if (rem > 0) {
        printf("%d", rem);
    }
    while (sum > 0) {
        printf("%d", sum % 10);
        sum /= 10;
    }
       
}

//MAIN #########################################################################

void main() {
    int option;
    while (option != 0)
    {
        do {
            //MENU A WHILE UNTIL YOU GET A 1,2,3 OR 0 TO END
            printf("\n\n0.Exit\n1.Addition\n2.Subtraction\n3.Multiplication\n\n");
            scanf("%d", &option);
            fflush(stdin);
            if (option == 0) exit(1);
            if (option < 0 || option > 3) printf("\nNot Valid Option\n");
        } while (option < 0 || option > 3);
        
        //CREATE THE STRING FOR THE NUMBERS
        char str1[MAX_SIZE], str2[MAX_SIZE], num1[MAX_SIZE], num2[MAX_SIZE];
        char result[MAX_SIZE] = "";
        int flag1 = 0, flag2 = 0;
        Node* NUM1 = NULL;
        Node* NUM2 = NULL;
        Node* RESULTS = NULL;

        do
        {
            //A WHILE LOOP UNTIL WE GET TO NUMBERS
            printf("Enter the first number: ");
            scanf("%s",&str1);
            printf("Enter the second number: ");
            scanf("%s",&str2);
            strcpy(num1,str1);
            strcpy(num2,str2);

            if (num1[0] == '-') {
                memmove(num1, num1+1, strlen(num1));
                flag1 = 1;
            } else if (num1[0] == '+')
            {
                memmove(num1, num1+1, strlen(num1));
            }
            
            if (num2[0] == '-') {
                memmove(num2, num2+1, strlen(num2));
                flag2 = 1;
            } else if (num2[0] == '+')
            {
                memmove(num2, num2+1, strlen(num2));
            }
            
            //digits_only() : IS FUNC THAT CHECH IS WE HAVE ONLY DIGITS
            if (!digits_only(num1) || !digits_only(num2)) {
                printf("\nOnly Number pls\n\n");
            }
        } while (!digits_only(num1) || !digits_only(num2));

        filltheDLL(&NUM1, num1);
        filltheDLL(&NUM2, num2);
        
        //CHECK WHAT OPTION USER WANTS. CALL THE APPROPRIATE FUNC AND PRINT RESULTS.
        if (option == 1) {
            if (flag1 == 1 && flag2 == 1) {
                strcat(result, "-");
                add(&NUM1, &NUM2, &RESULTS);

            } else if (flag2 == 1) {
                strcat(result, "+");
                sub(&NUM1, &NUM2, &RESULTS);

            } else if (flag1 == 1) {
                strcat(result, "-");
                sub(&NUM1, &NUM2, &RESULTS);
                
            } else {
                strcat(result, "+");
                add(&NUM1, &NUM2, &RESULTS);

            }
            DLLtoString(&RESULTS, result);
            printf("(%s) + (%s) = %s", str1, str2, result);

        } else if (option == 2) {
            int str1_len = listLength(&NUM1);
            int str2_len = listLength(&NUM2);

            int str1smaller = 0;

            if (str1_len < str1_len) {
                str1smaller = 1;
            } else if (str1_len == str2_len) { 
                if(strcmp(num1, num2) < 0)      //WE CHECK AGAIN WHICH NUMBER IS BIGGER CAUSE OF CASE EX. 1-9
                str1smaller = 1;
            }
    
            if (flag1 == 1 && flag2 == 1) {
                if (str1smaller) {
                    strcat(result, "+");
                    sub(&NUM2, &NUM1, &RESULTS);
                } else {
                    strcat(result, "-");
                    sub(&NUM1, &NUM2, &RESULTS);
                }
                
            } else if (flag2 == 1) {
                strcat(result, "+");
                add(&NUM1, &NUM2, &RESULTS);

            } else if (flag1 == 1) {
                strcat(result, "-");
                add(&NUM1, &NUM2, &RESULTS);
  
            } else {
                if (str1smaller) {
                    strcat(result, "-");
                    sub(&NUM2, &NUM1, &RESULTS);
                } else {
                    strcat(result, "+");
                    sub(&NUM1, &NUM2, &RESULTS);
                }
                
            }
            DLLtoString(&RESULTS, result);
            printf("(%s) - (%s) = %s", str1, str2, result);

        } else if (option == 3) {
            if (flag1 != flag2) {
                strcat(result, "-");
            } else {
                strcat(result, "+");
            }
            mult(&NUM1, &NUM2, &RESULTS);
            DLLtoString(&RESULTS, result);
            printf("(%s) * (%s) = %s", str1, str2, result);

        }
        fflush(stdin);  // CLEAN THE BUFFER FOR ANY REMANING \N ECT.
        memset(result, 0, sizeof(result));
    }

}
