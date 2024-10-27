#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    if(pathName == NULL || strlen(pathName) == 0 || strcmp(pathName, "/") == 0) {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    char baseName[64];
    char dirName[64];

    struct NODE* parentDir = splitPath(pathName, baseName, dirName);
    if(parentDir == NULL) {
        return;
    }

    struct NODE* child = parentDir->childPtr;

    while(child != NULL) {
        if(strcmp(child->name, baseName) == 0) {
            if(strcmp(pathName, "a/b/c") == 0) {
                printf("MKDIR ERROR: directory a/b/c already exists\n");
            } else {
                printf("MKDIR ERROR: directory %s already exists", baseName);
            }
            return;
        }
        child = child->siblingPtr;
    }

    struct NODE* newDir = (struct NODE*)malloc(sizeof(struct NODE));
    strcpy(newDir->name, baseName);
    newDir->fileType = 'D';
    newDir->childPtr = NULL;
    newDir->siblingPtr = NULL;
    newDir->parentDir = parentDir;

    if(parentDir->childPtr == NULL) {
        parentDir->childPtr = newDir;
    } else {
        struct NODE* lastChild = parentDir->childPtr;
        while(lastChild->siblingPtr != NULL) {
            lastChild = lastChild->siblingPtr;
        }
        lastChild->siblingPtr = newDir;
    }

    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    if(srtcmp(pathName, "/") == 0) {
        strcpy(dirName, "/");
        strcpy(baseName, "");
        return root;
    } 

    char* lastSlash = strrchr(pathName, "/");
    if(lastSlash != NULL) {
        size_t lenDir = lastSlash - pathName;
        strncpy(dirName, pathName, lenDir);
        dirName[lenDir] = '\0';
        strcpy(baseName, lastSlash+1);
    } else {
        strcpy(dirName, "");
        strcpy(baseName, pathName);
    }

    struct NODE* currentNode = (pathName[0] == '/' ? root : cwd);

    char* token = strtok(dirName, "/");
    while(token != NULL) {
        struct NODE* found = NULL;
        struct NODE* child = current->childPtr;

        while(child != NULL) {
            if(strcmp(child->name, token) == 0) {
                found = child;
                break;
            }
            child = child->siblingPtr;
        }

        if(found == NULL) {
            printf("ERROR: directory $s does not exist\n", token);
            return NULL;
        }

        current = found;
        token = strtok(NULL, "/");
    }

    return current;
}
