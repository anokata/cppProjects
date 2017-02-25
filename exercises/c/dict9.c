#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 42

char *rus_pronouns1[] = {"Я", "ты", "они", "мы"};
char *eng_pronouns1[] = {"I", "you", "they", "we"};
int pronouns1_count = sizeof(rus_pronouns1)/sizeof(char*);
char *rus_pronouns2[] = {"он", "она"};
char *eng_pronouns2[] = {"he", "she"};
int pronouns2_count = sizeof(rus_pronouns2)/sizeof(char*);

char *rus_verbs[] = {"бегать", "спать", "жить", "читать", "писать", "разговаривать"};
char *eng_verbs[] = {"run", "sleep", "live", "read", "write", "talk"};
int verbs_count = sizeof(rus_verbs)/sizeof(char*);
const static int tries = 3;

struct pronoun {
    char* rus;
    char* eng;
    int face;
};

struct pronoun choose_pronoun() {
    static struct pronoun ruseng;
    int pron_type = rand() % 2;
    ruseng.face = pron_type;
    int pron = 0;
    if (pron_type) {
        pron = rand() % pronouns1_count;
        ruseng.rus = rus_pronouns1[pron];
        ruseng.eng = eng_pronouns1[pron];
    } else {
        pron = rand() % pronouns2_count;
        ruseng.rus = rus_pronouns2[pron];
        ruseng.eng = eng_pronouns2[pron];
    }
    return ruseng;
}

char** choose_verb() {
    static char* ruseng[2];
    int v = rand() % verbs_count;
    *ruseng = rus_verbs[v];
    ruseng[1] = eng_verbs[v];
    return ruseng;
}

struct sentence {
    char rus[MAX];
    char eng[MAX];
};
struct pairs {
    char fst[MAX];
    char efst[MAX];
    char snd[MAX];
    char esnd[MAX];
};
struct sentence make_form(char* form, struct pairs* face) {
    static struct sentence result;
    struct pronoun p = choose_pronoun();
    char** v = choose_verb();
    if (face) {
        if (p.face) {
            sprintf(result.rus, form, p.rus, face->fst, v[0]);
            sprintf(result.eng, form, p.eng, face->efst, v[1]);
        } else {
            sprintf(result.rus, form, p.rus, face->snd, v[0]);
            sprintf(result.eng, form, p.eng, face->esnd, v[1]);
        }
    } else {
        sprintf(result.rus, form, p.rus, v[0]);
        sprintf(result.eng, form, p.eng, v[1]);
    }
    return result;
}

struct sentence make_affirmative() {
    return make_form("%s %s", NULL);
}
struct sentence make_negative() {
    struct pairs neg_do = {" не ", " don't ", " не ", " doesn't "};
    return make_form("%s%s%s", &neg_do);
}
// interrogative? affirmative/negatve
// TODO менять ничего, только мм. только глагол, и форму.  все 9 или рандом.

void guess_one() {
    char ans[MAX];
    struct sentence s;
    int try = tries;
    int ok = 1;
    s = make_negative();

    while (try && ok) {
        printf("Переведите: ");
        printf("%s\n", s.rus);
        fgets(ans, MAX-1, stdin);
        ans[strlen(ans)-1] = 0;
        ok = strcmp(ans, s.eng);
        if (ok == 0) {
            printf("Правильно!\n");
        } else {
            printf("Не правильно\n");
            try--;
            if (!try)
                printf("Правильно: %s\n", s.eng);
        }
    }
}

int main() {
    srand(time(NULL));
    while (1) guess_one();
    return 0;
}
