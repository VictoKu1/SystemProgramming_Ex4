#include "frequency.h"

int main(int argc, char *argv[])
{
    int i, max;
    max = -1;
    char *w = malloc(1);
    node *root = node_builder('.');
    i = 0;
    w[0] = '*';
    while (w[0] != EOF)
    {
        free(w);
        w = get_word(&i);
        if (w[0] != EOF)
        {
            tree_builder(w, i, root);
            if (i > max)
            {
                max = i;
            }
        } 
    }
    if (argc >= 1)
    {
        printf("%i  %s",argc,argv[0]);
        if (argv[1][0] == 'r')
    {
        Lexicographic_R(root, max);
    }
    }
    else
    {
        Lexicographic(root, max);
    }
    free_tree(root);
    return 0;
}

// read a word from the user and return the word (update the length of the word with the poiner i)

char *get_word(int *i)
{
    char *word = (char *)malloc(sizeof(char) * 51);
    if (word == NULL)
    {
        printf("not enough memory\n");
        exit(-1);
    }
    char c;
    *i = 0;
    int len = 51;
    c = getchar()
    printf("c = %i , v = %i\n",c,v);
    while ((c != ' ') && (c != '\t') && (c != '\n') && (c != 13)&&(c != EOF))
    {
        if (*i >= len)
        {
            len = len*2 ; 
            word = realloc(word, len);
        }
        if (word == NULL)
        {
            printf("not enough memory\n");
            exit(-1);
        }
        word[*i] = c;
        c = getchar();
        ++(*i);
        printf("c = %i \n",c);
    }
    if (c ==EOF){
        word[0] = EOF;
        return word;
    }
    word[*i] = '\0';
    return word;
}

// given a word build a path for it in the tree ( $ is the end of the word)
void tree_builder(char *c, int len, node *root)
{
    int index;
    node *n;
    node *par = root;
    for (size_t i = 0; i < len; i++)
    {
        printf("%c\n", c[i]);
        index = hash_func(c[i]);
        printf("   %i\n", index);
        if (index != -1)
        {
            if (par->children[index] == NULL)
            {
                n = node_builder(c[i]);
                par->children[index] = n;
            }
            else
            {
                n = par->children[index];
            }
            par = n;
        }
    }
    if (par->children[0] == NULL)
    {
        n = node_builder('$');
        par->children[0] = n;
    }
    par->children[0]->count += 1;
}

// build a node that represent the given char
node *node_builder(char c)
{
    node *n = (node *)malloc(sizeof(node));
    if (n == NULL)
    {
        printf("not enough memory\n");
        exit(-1);
    }
    n->count = 0;
    if (c != '.')
    {
        n->letter = c;
    }
    node **_children = (node **)calloc(sizeof(node *), NUM_LETTERS);
    if (_children == NULL)
    {
        printf("not enough memory\n");
        exit(-1);
    }
    n->children = _children;
    return n;
}

// caculate a hash function for the letters
int hash_func(int i)
{
    if (i < 91 && i > 64)
    {
        i = i + 32;
    }
    if (i < 97 || i > 122)
    {
        return -1;
    }
    return i - 96;
}

// reads the tree in a Lexicographic order
void Lexicographic(node *root, int max)
{
    printf("start");
    char w[max];
    for (size_t i = 0; i < NUM_LETTERS; ++i)
    {
        if (root->children[i] != NULL)
        {
            Lexicographic_func(w, root->children[i], 0);
        }
    }
}

// recursive function for tree navigation
void Lexicographic_func(char *w, node *n, int index)
{
    printf("%c",n->letter);
    if (n->letter == '$')
    {
        w[index] = '\0';
        printf("%s %ld\n", w, n->count);
        return;
    }
    w[index] = n->letter;
    for (size_t i = 0; i < NUM_LETTERS; ++i)
    {
        if (n->children[i] != NULL)
        {
            Lexicographic_func(w, n->children[i], index + 1);
        }
    }
    w[index] = '\0';
    return;
}
// reads the tree in a revese Lexicographic order
void Lexicographic_R(node *root, int max)
{
    char w[max];
    for (size_t i = NUM_LETTERS - 1; i > -1; --i)
    {
        if (root->children[i] != NULL)
        {
            Lexicographic_R_func(w, root->children[i], 0);
        }
    }
}
// recursive function for tree navigation
void Lexicographic_R_func(char *w, node *n, int index)
{
    if (n->letter == '$')
    {
        w[index] = '\0';
        printf("%s %ld", w, n->count);
        return;
    }
    w[index] = n->letter;
    for (size_t i = NUM_LETTERS - 1; i > -1; --i)
    {
        if (n->children[i] != NULL)
        {
            Lexicographic_R_func(w, n->children[i], index + 1);
        }
    }
    w[index] = '\0';
    return;
}
void free_tree(node *_node)
{
    if (_node->letter == '$')
    {
        free(_node);
        return;
    }
    for (size_t i = 0; i < NUM_LETTERS; ++i)
    {
        if (_node->children[i] != NULL)
        {
            free_tree(_node->children[i]);
        }
        free(_node->children[i]);
    }
    free(_node->children);
    free(_node);
    return;
}
