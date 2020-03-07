#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dict
{
    struct dict *left, *right;
    char word[20], meaning[100];
};
struct dict *root = NULL;

typedef struct dict dictionary;
dictionary *insert();
void search();
void view(dictionary *);
int check(char[], char[]);

int check(char a[], char b[])
{
    int i, j, c;
    for(i = 0, j= 0; a[i]!= '\0' && b[i]!= '\0'; i++, j++)
    {
        if(a[i]>b[j])
        {
            c = 1;
            break;
        }
        else if(a[i]<b[i])
        {
            c = -1;
            break;
        }
        else
        {
            c = 0;
        }
    }
    return c;
}

void search()
{
    char w[20];
    printf("Enter the word you want to search\n");
    scanf("%s", w);
    dictionary *ptr;
    ptr = root;
    int flag = 0;
    while(ptr!=NULL && flag == 0)
    {
        if(check(w, ptr->word) == 1)
            ptr = ptr->right;
        else if(check(w, ptr->word) == -1)
            ptr = ptr->left;
        else
            flag = 1;
    }
    if(flag == 0 && ptr!=NULL)
    {
        printf("Word not found");
    }
    else
    {
        printf("Your word: \n");
        puts(w);
        printf("\nMeaning of the word: \n");
        puts(ptr->meaning);
        printf("\n");
    }
}

dictionary *insert()
{
    dictionary *temp;
    temp = (dictionary *)malloc(sizeof(dictionary));
    temp ->left = NULL;
    temp ->right = NULL;
    printf("Enter word to be inserted in the dictionary\n");
    fflush(stdin);
    gets(temp->word);
    printf("Enter the meaning of the word\n");
    fflush(stdin);
    gets(temp->meaning);
    dictionary *ptr, *parent;
    ptr = root;
    int flag = 0;
    if(root == NULL)
    {
        root = temp;
        return root;
    }
    else
    {
        while(ptr!=NULL && flag == 0)
        {
            if(check(temp->word, ptr->word) == 1)
            {
                parent = ptr;
                ptr = ptr->right;
            }
            else if(check(temp->word, ptr->word) == -1)
            {
                parent = ptr;

                ptr = ptr->left;
            }
            else
            {
                flag = 1;
                printf("Word Already Exists in the dictionary\n");
                break;
            }
        }
    }
    if(flag == 0 && ptr == NULL)
    {
        if(check(parent->word, temp->word)==1)
            parent->left = temp;
        else
            parent->right = temp;
    }
    return root;
}

void view(dictionary *ptr)
{
    if(root == NULL)
        printf("Empty dictionary\n");
    else
    {
        if(ptr!=NULL)
        {
            view(ptr->left);
            printf("%s \t %s\n", ptr -> word, ptr->meaning);
            view(ptr->right);
        }
    }
}

int main()
{
    int choice;
    do
    {
        printf("Enter\n 1. To insert a new word in the dictionary\n 2. To search a word in the dictionary\n");
        printf(" 3. To view all words in the dictionary\n 4. to exit\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            root = insert();
            break;
        case 2:
            search();
            break;
        case 3:
            printf("Word \t Meaning\n");
            view(root);
            break;
        }
    }while(choice!=4);
    return 0;
}
