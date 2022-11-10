//
//  main.cpp
//  test
//
//  Created by Houtong Lei on 2021/6/3.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    struct dirent *dirp;
    char path[] = "/Volumes/THL/未命名文件夹/2/highway/in";
    char file[100];
    DIR* dir = opendir(path);
    while ((dirp = readdir(dir)) != nullptr)
        if (dirp->d_type == DT_REG) {
            strcpy(file, path);
            strcat(file, "/");
            strcat(file, dirp->d_name);
            printf("%s\n", file);
            stdin = fopen(file, "r");
        }
    
    closedir(dir);
    return 0;
}
