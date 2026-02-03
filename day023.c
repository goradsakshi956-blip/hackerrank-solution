#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct document Doc;

struct document get_document(char *text) {
    Doc.paragraph_count = 0;

    // count paragraphs
    for (int i = 0; text[i]; i++)
        if (text[i] == '\n')
            Doc.paragraph_count++;
    Doc.paragraph_count++;

    Doc.data = malloc(Doc.paragraph_count * sizeof(struct paragraph));

    char *save_p;
    char *para = strtok_r(text, "\n", &save_p);

    for (int p = 0; p < Doc.paragraph_count; p++) {
        struct paragraph *pg = &Doc.data[p];

        pg->sentence_count = 0;
        for (int i = 0; para[i]; i++)
            if (para[i] == '.' && para[i+1] != '\0')
                pg->sentence_count++;
        pg->sentence_count++;

        pg->data = malloc(pg->sentence_count * sizeof(struct sentence));

        char *save_s;
        char *sent = strtok_r(para, ".", &save_s);

        for (int s = 0; s < pg->sentence_count; s++) {
            struct sentence *st = &pg->data[s];

            st->word_count = 0;
            for (int i = 0; sent[i]; i++)
                if (sent[i] == ' ')
                    st->word_count++;
            st->word_count++;

            st->data = malloc(st->word_count * sizeof(struct word));

            char *save_w;
            char *word = strtok_r(sent, " ", &save_w);

            for (int w = 0; w < st->word_count; w++) {
                st->data[w].data = malloc(strlen(word) + 1);
                strcpy(st->data[w].data, word);
                word = strtok_r(NULL, " ", &save_w);
            }

            sent = strtok_r(NULL, ".", &save_s);
        }

        para = strtok_r(NULL, "\n", &save_p);
    }

    return Doc;
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) {
    return Doc.data[m - 1].data[k - 1];
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(
    struct document Doc, int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}



void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
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

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}