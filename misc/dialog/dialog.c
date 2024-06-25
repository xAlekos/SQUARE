#include "dialog.h"

#define NEXT_LINE 2
#define END_OF_DIALOGUE 3 
#define NEW_TALKER 4

int read_line(FILE* dialog_file , dialog_line_t* line, uint8_t talker_flag){
    
    char ch;
    
    if(dialog_file == NULL)
        return 1;

    if(talker_flag)
        fgets(line->talker,50,dialog_file);

    for(int i = 0; i < 1024 ; i++){
        
        ch = fgetc(dialog_file);

        switch (ch)
        {
        case '_': 
            return NEXT_LINE;
            break;
        case '^':
            return END_OF_DIALOGUE;
            break;
        case '&':
            return NEW_TALKER;
            break;
        default:
            line->text[i] = ch;
            break;
        };

    }
    return NEXT_LINE;
}


void read_dialog(dialog_t* dialogue,char* file_path, uint8_t num){

    FILE* dialog_file = fopen(file_path,"r");
    uint8_t n = 0;
    uint8_t end_flag = 0;
    uint8_t talker_flag = 0;
    char ch;

    dialogue->lines = malloc(sizeof(dialog_line_t));
    dialog_line_t* line_pointer = dialogue->lines;
    line_pointer->next = NULL;

    while(((ch = fgetc(dialog_file)) != '*') || n != num)
        n++;

    while(end_flag == 0){
        switch(read_line(dialog_file,line_pointer,talker_flag)){
            
            case NEXT_LINE:
                //printf("next_line\n");
                line_pointer->next = malloc(sizeof(dialog_line_t));
                line_pointer = line_pointer->next;
                line_pointer->next = NULL;
                break;

            case END_OF_DIALOGUE: end_flag = 1;
                printf("EOD\n");
                break;

            default: end_flag = 1;
                //printf("DEFAULT\n");
                break;
        }
    }

}

void print_dialog(dialog_t* dial){

    printf("%s",dial->lines->talker);

    dialog_line_t* pointer = dial->lines;

    while(pointer != NULL){
        
        printf("%s\n",pointer->text);
        pointer = pointer->next;

        printf("-------------------\n");
    }


}


int main(){

dialog_t* dial = malloc(sizeof(dialog_t));
read_dialog(dial,"cosmic_powers",0);
print_dialog(dial);

}