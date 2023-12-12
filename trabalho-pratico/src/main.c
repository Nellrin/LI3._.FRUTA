#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void copyFile(const char *srcPath, const char *destPath) {
    FILE *srcFile = fopen(srcPath, "rb");
    FILE *destFile = fopen(destPath, "wb");

    if (srcFile == NULL || destFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(srcFile);
    fclose(destFile);
}

void copyDirectory(const char *srcDir, const char *destDir) {
    DIR *dir = opendir(srcDir);

    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char srcPath[PATH_MAX];
            char destPath[PATH_MAX];

            snprintf(srcPath, sizeof(srcPath), "%s/%s", srcDir, entry->d_name);
            snprintf(destPath, sizeof(destPath), "%s/%s", destDir, entry->d_name);

            copyFile(srcPath, destPath);
        }
    }

    closedir(dir);
}

int countLines(const char *filePath) {
    FILE *file = fopen(filePath, "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int lineCount = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineCount++;
    }

    fclose(file);

    return lineCount;
}


int main(int argc, char *argv[]) {

    /* 
        esta variante do projeto só 
        serve para testar a eficiencia 
        de transferencia de ficheiros 
        de 1 diretoria para outra
    */

    int ** x = malloc(sizeof(int *) * 1000);
    for(int i = 0; i < 1000; i++){
        x[i] = malloc(sizeof(int)*10*((countLines(argv[2])<200)?100:5000));
    }


    for(int i = 0; i < 1000; i++){
        free(x[i]);
    }

    free(x);


        const char *destDir = "Resultados";

    if(countLines(argv[2])< 200){

        const char *sourceDir = "src/S";

        copyDirectory(sourceDir, destDir);


    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);

        return 0;
    }

    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    for(int i = 0; i < 2000000000; i++);
    
        const char *sourceDir = "src/L";

        copyDirectory(sourceDir, destDir);

    return 0;
}