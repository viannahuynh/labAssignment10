#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct Trie
{
    int flag;
    struct Trie *children[26];
}Trie;

// makes new node
struct Trie* newNode()
{
    struct Trie *newNode = NULL;
    newNode = (struct Trie*)calloc(1,sizeof(struct Trie));
    return newNode;
}

void insert(struct Trie **ppTrie, char *word)
{
    // if there is node make one
    if (*ppTrie == NULL)
    {
        *ppTrie = newNode();
    }

    int length = strlen(word);
    Trie * temp = *ppTrie;
    // goes through each string
    for (int i = 0; i < length; i ++)
    {
        // gets the ASCII and minuses it by a ASCII val
        int index = word[i] - 'a';
        if ((temp)->children[index]== NULL)
        {
            (temp)->children[index] = (Trie*) calloc (1, sizeof(Trie));
        }

        temp = temp -> children[index];
    }

    temp->flag++;
}
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int count = 0;
    
    int length = strlen(word);
    struct Trie * temp = pTrie;
    for (int i = 0; i < length; i ++)
    {
        // gets the ASCII and minuses it by a ASCII val
        int index = word[i] - 'a';
        if (temp->children[index]== NULL)
        {
           return 0;
        }

        temp = temp -> children[index];
    }

    return temp->flag;
}
// recursion
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie != NULL)
    { 
        for (int i = 0; i < 26; i ++)
        {
            deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

int main(void)
{
    struct Trie *trie = NULL;
    // read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int len = sizeof(pWords) / sizeof(char *);
    for (int i = 0; i < len; i ++) 
    {
        insert(&trie, pWords[i]);
    }

    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);

    if (trie != NULL)
       printf("There is an error in this program\n");

    return 0;
}
