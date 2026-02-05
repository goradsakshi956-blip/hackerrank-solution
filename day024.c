#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n-1][m-1][k-1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) {
    return document[m-1][k-1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k-1];
}

char**** get_document(char* text) {
    // 1. Allocate for Paragraphs
    char**** doc = malloc(5 * sizeof(char***)); // Max paragraphs usually small
    int p_idx = 0, s_idx = 0, w_idx = 0;
    
    char* p_saveptr;
    char* s_saveptr;
    char* w_saveptr;

    // Use a copy because strtok modifies the string
    char* text_copy = strdup(text);
    
    char* para = strtok_r(text_copy, "\n", &p_saveptr);
    while (para != NULL) {
        doc[p_idx] = malloc(10 * sizeof(char**)); // Max sentences
        s_idx = 0;
        
        char* sent = strtok_r(para, ".", &s_saveptr);
        while (sent != NULL) {
            doc[p_idx][s_idx] = malloc(30 * sizeof(char*)); // Max words
            w_idx = 0;
            
            char* word = strtok_r(sent, " ", &w_saveptr);
            while (word != NULL) {
                doc[p_idx][s_idx][w_idx] = strdup(word);
                w_idx++;
                word = strtok_r(NULL, " ", &w_saveptr);
            }
            s_idx++;
            sent = strtok_r(NULL, ".", &s_saveptr);
        }
        p_idx++;
        para = strtok_r(NULL, "\n", &p_saveptr);
    }
    return doc;
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}