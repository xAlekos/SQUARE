#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define NEXT_LINE 2
#define END_OF_DIALOGUE 3 
#define NEW_TALKER 4

typedef struct dialog_line {
    
    char talker[50];
    char text[1024];
    struct dialog_line* next;

} dialog_line_t;

typedef struct dialog {

    dialog_line_t* lines;

} dialog_t;

int read_line(FILE* dialog_file, dialog_line_t* line, uint8_t talker_flag) {
    char ch;
    int i = 0;

    if (dialog_file == NULL) {
        return 1;
    }

    if (talker_flag) {
        fgets(line->talker, 50, dialog_file);
        line->talker[strcspn(line->talker, "\n")] = '\0';
    }

    while ((ch = fgetc(dialog_file)) != EOF && i < 1024) {
        switch (ch) {
            case '_':
                line->text[i] = '\0';
                return NEXT_LINE;
            case '^':
                line->text[i] = '\0';
                return END_OF_DIALOGUE;
            case '&':
                line->text[i] = '\0';
                return NEW_TALKER;
            default:
                line->text[i++] = ch;
                break;
        }
    }

    line->text[i] = '\0';
    return (ch == EOF) ? END_OF_DIALOGUE : NEXT_LINE;
}

void read_dialog(dialog_t* dialogue, const char* file_path, uint8_t num) {
    
    FILE* dialog_file = fopen(file_path, "r");

    if (dialog_file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }

    uint8_t n = 0;
    uint8_t end_flag = 0;
    uint8_t talker_flag = 1;
    char ch;

    dialogue->lines = malloc(sizeof(dialog_line_t));
    dialog_line_t* line_pointer = dialogue->lines;
    dialog_line_t* tmp_pointer;
    line_pointer->next = NULL;

    while (((ch = fgetc(dialog_file)) != '*') || n != num) {
        if (ch == '*') {
            n++;
        }
        if (ch == EOF) {
            fclose(dialog_file);
            return;
        }
    }

    while (end_flag == 0) {
        int result = read_line(dialog_file, line_pointer, talker_flag);
        talker_flag = (result == NEW_TALKER) ? 1 : 0;

        switch (result) {
            case NEXT_LINE:
                line_pointer->next = malloc(sizeof(dialog_line_t));
                tmp_pointer = line_pointer;
                line_pointer = line_pointer->next;
                strcpy(line_pointer->talker,tmp_pointer->talker);
                line_pointer->next = NULL;
                break;
            case END_OF_DIALOGUE:
                end_flag = 1;
                break;
            case NEW_TALKER:
                line_pointer->next = malloc(sizeof(dialog_line_t));
                line_pointer = line_pointer->next;
                line_pointer->next = NULL;
                break;
        }
    }

    fclose(dialog_file);
}



void free_dialog(dialog_t* dial){

    dialog_line_t* line_pointer;

    while(dial->lines != NULL){
        line_pointer = dial->lines;
        dial->lines = dial->lines->next;
        free(line_pointer);
    }

    free(dial);
}


void print_dialog(dialog_t* dial) {
    dialog_line_t* pointer = dial->lines;

    while (pointer != NULL) {
        if (strlen(pointer->talker) > 0) {
            printf("Talker: %s\n", pointer->talker);
        }
        printf("Text: %s\n", pointer->text);
        pointer = pointer->next;
        printf("-------------------\n");
    }
}



/*
int main() {
    dialog_t* dial = malloc(sizeof(dialog_t));
    read_dialog(dial, "cosmic_powers", 0);
    print_dialog(dial);
    free_dialog(dial);
    return 0;
}
*/