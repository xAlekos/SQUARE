#include "../../utils/utils.h"

typedef struct dialog_line{

char talker[50];
char text[1024];
struct dialog_line* next; 

}dialog_line_t;

typedef struct dialog{

    dialog_line_t* lines;
    uint16_t num;

}dialog_t;

int read_line(FILE* dialog_file, dialog_line_t* line);

void read_dialog(dialog_t* dialogue,char* file_path, uint8_t num);

void free_dialog(dialog_t* dialog);