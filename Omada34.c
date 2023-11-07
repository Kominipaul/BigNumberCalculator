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

typedef struct Node {
    int num;
    struct Node *next;
    struct Node *prev;
} Node;


int digits_only(const char *s) {
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }
    return 1;
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
    Node* tmp = *head_ref;
    int size = 0;
    while (tmp != NULL)
    {
        ++size;
        tmp = tmp->next;
    }
    return size;
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
       printf("The List is empty\n");
       return;
    }

    while (tmp->next != NULL) tmp = tmp->next;

    while (tmp != NULL) {
        printf("%d", tmp->num);
        tmp = tmp->prev;
    }
}

int is_empty(Node** head_ref) {
    return *head_ref == NULL;
}

void add(char *num1, char *num2, char *result) {
    Node* S1 = NULL;    //CREATE 3 LISTS
    Node* S2 = NULL;
    Node* S3 = NULL;

    int len1 = strlen(num1);        //GET THE NUMBERS LENGHT
    int len2 = strlen(num2);

    for (int i = 0; i < len1; i++) { //PUSH EVERY NUMBER TO THE LIST/STACK WITH PUSH() 
        push(&S1, num1[i] - '0');    //MAKING THEM INTEGERS WIHT ""( - '0' )""
    }

    for (int i = 0; i < len2; i++) {
        push(&S2, num2[i] - '0');
    }

    int rem = 0;

    while (!is_empty(&S1) || !is_empty(&S2)) {  //WHILE THE STACK ISNT EMPTY
        int n1 = is_empty(&S1) ? 0 : pop(&S1);  //POP THE NUMBERS
        int n2 = is_empty(&S2) ? 0 : pop(&S2);

        int sum = n1 + n2 + rem;    // ADD NUMBERS WITH THE REMENDER
        push(&S3, sum % 10);        // PUSH TO STACK3 THE MOD
        rem = sum / 10;             // HOLD THE DIV TO THE REMENDER
    }
    if (rem != 0) push(&S3, rem);   // AND LAST IF WE HAVE REM ADD IT TO STACK3

    while (!is_empty(&S3)) {
        char N = pop(&S3) + '0';
        char char_str[2] = {N, '\0'};
        strcat(result, char_str);
    }

}

void sub(char *num1, char *num2, char *result) {
    Node* S1 = NULL;    //CREATE 3 LISTS
    Node* S2 = NULL;
    Node* S3 = NULL;

    int len1 = strlen(num1);            //GET THE NUMBERS LENGHT
    int len2 = strlen(num2);

    if (len1 < len2) {
        swap(num1,num2);               //swap(str1,str2) : SWAPS THE 2 STRINGS
    } else if (len1 == len2) { 
        if(strcmp(num1, num2) < 0)      //WE CHECK AGAIN WHICH NUMBER IS BIGGER CAUSE OF CASE EX. 1-9
        swap(num1,num2);
    }

    for (int i = 0; i < len1; i++) {    //PUSH EVERY NUMBER TO THE LIST/STACK WITH PUSH() 
        push(&S1, num1[i] - '0');       //MAKING THEM INTEGERS WIHT ""( - '0' )""
    }

    for (int i = 0; i < len2; i++) {
        push(&S2, num2[i] - '0');
    }

    int borrow = 0;

    while (!is_empty(&S1) || !is_empty(&S2)) {  //WHILE THE STACK ISNT EMPTY
        int n1 = is_empty(&S1) ? 0 : pop(&S1);  //POP THE NUMBERS
        int n2 = is_empty(&S2) ? 0 : pop(&S2);

        int diff = n1 - n2 - borrow;            //SUBTRACT THE NUMBER WITH THE BORROW

        if (diff < 0) {                         //CHECK THE DIFF 
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        push(&S3, diff);    // PUSH THE DIFF
    }

    while (!is_empty(&S3)) {
        char N = pop(&S3) + '0';
        char char_str[2] = {N, '\0'};
        strcat(result, char_str);
    }
}

/*
void mult(char *num1, char *num2, char *result) {
    Node* S1 = NULL;    //CREATE 3 LISTS
    Node* S2 = NULL;
    Node* S3 = NULL;

    int len1 = strlen(num1);    //GET THE NUMBERS LENGHT
    int len2 = strlen(num2);

    for (int i = 0; i < len1; i++) {    //PUSH EVERY NUMBER TO THE LIST/STACK WITH PUSH() 
        push(&S1, num1[i] - '0');       //MAKING THEM INTEGERS WIHT ""( - '0' )""
    }

    for (int i = 0; i < len2; i++) {
        push(&S2, num2[i] - '0');
    }

    while (!is_empty(&S2)) {
        int n1 = is_empty(&S1) ? 0 : pop(&S1);  //POP THE NUMBERS
        int n2 = is_empty(&S2) ? 0 : pop(&S2);

        int mult, ext
        while (S1->next != NULL) {
            mult = n1 * n2 + ext;
            push(&S3, mult % 10);        // PUSH TO STACK3 THE MOD
            ext = mult / 10;             // HOLD THE DIV TO THE REMENDER
        }
        
    }
    
    int lenS1 = listLength(&S1);
    int lenS2 = listLength(&S2);

    for(int i=0; i<lenS1;i++) {
        for(int j=0; j<lenS2;j++) {

            int p = is_empty(&S1) ? 0 : pop(&S1);  //POP THE NUMBERS
            int q = is_empty(&S2) ? 0 : pop(&S2);

            ans[i+j]+=p*q;
            ans[i+j+1]=ans[i+j+1]+ans[i+j]/10;
            ans[i+j]%=10;
        }
    }
       
}
*/


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
            if(!digits_only(num1) || !digits_only(num2)) {
                printf("\nOnly Number pls\n\n");
            }
        } while (!digits_only(num1) || !digits_only(num2));


        
        //CHECK WHAT OPTION USER WANTS. CALL THE APPROPRIATE FUNC AND PRINT RESULTS.
        if (option == 1) {
            if (flag1 == 1 && flag2 == 1) {
                strcat(result, "-");
                add(num1, num2, result);

            } else if (flag2 == 1) {
                strcat(result, "+");
                sub(num1, num2, result);

            } else if (flag1 == 1) {
                strcat(result, "-");
                sub(num1, num2, result);
                
            } else {
                strcat(result, "+");
                add(num1, num2, result);
            }
            printf("(%s) + (%s) = %s", str1, str2, result);

        }else if (option == 2) {
            int str1_len = strlen(num1);
            int str2_len = strlen(num2);

            int str1smaller = 0;

            if(str1_len < str1_len) {
                str1smaller = 1;
            }else if (str1_len == str2_len) { 
                if(strcmp(num1, num2) < 0)      //WE CHECK AGAIN WHICH NUMBER IS BIGGER CAUSE OF CASE EX. 1-9
                str1smaller = 1;
            }
    
            if (flag1 == 1 && flag2 == 1) {
                if(str1smaller) {
                    strcat(result, "+");
                } else strcat(result, "-");
                sub(num1, num2, result);

            } else if (flag2 == 1) {
                if(str1smaller) {
                    strcat(result, "+");
                } else strcat(result, "+");
                add(num1, num2, result);


            } else if (flag1 == 1) {
                if(str1smaller) {
                    strcat(result, "-");
                } else strcat(result, "-");
                add(num1, num2, result);

            } else {
                if(str1smaller) {
                    strcat(result, "-");
                } else strcat(result, "+");
                sub(num1, num2, result);
            }
            printf("(%s) - (%s) = %s", str1, str2, result);

        }else if (option == 3) {


        }
        fflush(stdin);  // CLEAN THE BUFFER FOR ANY REMANING \N ECT.
        memset(result, 0, sizeof(result));
    }

}
