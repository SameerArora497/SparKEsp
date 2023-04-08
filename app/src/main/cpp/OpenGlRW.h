#ifndef RESOURCE1_OPENGLRW_H
#define RESOURCE1_OPENGLRW_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#define MAX 256

using namespace std;

int replace_line(const std::string Dirpatch, const char *fname, const char *oldline, const char *newline) {

    int done = 0;
    std::string fp = std::string(Dirpatch + "func.txt");
    FILE *newfp = fopen(fp.c_str(), "a");
    if (newfp != NULL) {
        FILE *oldfp = fopen(fname, "r");
        if (oldfp != NULL) {
            ssize_t read;
            size_t len = 0;
            char *line = NULL;
            while ((read = getline(&line, &len, oldfp)) != -1) {
                if (strstr(line, oldline) == NULL)
                    fprintf(newfp, "%s", line);
                else
                    fprintf(newfp, "%s", newline);
            }
            fclose(oldfp);
            if (line)
                free(line);
            done = 1;
        }
        fclose(newfp);
        remove(fname);
        rename(fp.c_str(), fname);
        return done;
    }

    return 0;
}

string combine2text(const std::string str, const std::string str2){
    return std::string(str + str2);
}

void write(const std::string dirpatch, const std::string fname, char newln[MAX], int lno)
{
    std::string fp = std::string(dirpatch + fname);
    FILE *fptr1, *fptr2;
    int linectr = 0;
    char str[MAX];
    char temp[] = "test.txt";
    std::string fp2 = std::string(dirpatch + temp);

    fptr1 = fopen(fp.c_str(), "r");
    if (!fptr1)
    {
        printf("Unable to open the input file!!\n");
    }
    fptr2 = fopen(fp2.c_str(), "w");
    if (!fptr2)
    {
        printf("Unable to open to write!!\n");
        fclose(fptr1);
    }

    lno++;

    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1))
        {
            linectr++;
            if (linectr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
            else
            {
                fprintf(fptr2, "%s\n", newln);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fp.c_str());
    rename(fp2.c_str(), fp.c_str());
}

void writeInt(const std::string dirpatch, const std::string fname, int newln, int lno)
{
    std::string fp = std::string(dirpatch + fname);
    FILE *fptr1, *fptr2;
    int linectr = 0;
    char str[MAX];
    char temp[] = "test.txt";
    std::string fp2 = std::string(dirpatch + temp);

    fptr1 = fopen(fp.c_str(), "r");
    if (!fptr1)
    {
        printf("Unable to open the input file!!\n");
    }
    fptr2 = fopen(fp2.c_str(), "w");
    if (!fptr2)
    {
        printf("Unable to open to write!!\n");
        fclose(fptr1);
    }

    lno++;

    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1))
        {
            linectr++;
            if (linectr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
            else
            {
                fprintf(fptr2, "%d\n", newln);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fp.c_str());
    rename(fp2.c_str(), fp.c_str());
}

void writeFLoat(const std::string dirpatch, const std::string fname, float newln, int lno)
{
    std::string fp = std::string(dirpatch + fname);
    FILE *fptr1, *fptr2;
    int linectr = 0;
    char str[MAX];
    char temp[] = "test.txt";
    std::string fp2 = std::string(dirpatch + temp);

    fptr1 = fopen(fp.c_str(), "r");
    if (!fptr1)
    {
        printf("Unable to open the input file!!\n");
    }
    fptr2 = fopen(fp2.c_str(), "w");
    if (!fptr2)
    {
        printf("Unable to open to write!!\n");
        fclose(fptr1);
    }

    lno++;

    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1))
        {
            linectr++;
            if (linectr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
            else
            {
                fprintf(fptr2, "%f\n", newln);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fp.c_str());
    rename(fp2.c_str(), fp.c_str());
}

std::fstream & GotoLine(std::fstream & file, unsigned int num)
{
    file.seekg(std::ios::beg);
    for (int i = 0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
    }
    return file;
}

int getInt(const std::string Dirpatch, const std::string fileName, int lineNumber) {
    std::string fp = std::string(Dirpatch + fileName);
    fstream file(fp.c_str());
    GotoLine(file, lineNumber);
    string line;
    file >> line;
    return stoi(line);
}

float getFloat(const std::string Dirpatch, const std::string fileName, int lineNumber) {
    std::string fp = std::string(Dirpatch + fileName);
    fstream file(fp.c_str());
    GotoLine(file, lineNumber);
    string line;
    file >> line;
    return stof(line);
}

bool getBool(const std::string Dirpatch, const std::string fileName, int lineNumber) {
    std::string fp = std::string(Dirpatch + fileName);
    fstream file(fp.c_str());
    GotoLine(file, lineNumber);
    string line;
    file >> line;
    return stoi(line);
}

void saveDataLoop2(bool blFun[], const std::string Dirpatch, const std::string fileName, int size, int val) {
    for(int i=0; i< size; i++){
        writeInt(Dirpatch, fileName,val, i);
        blFun[i] = val;
    }
}

void ColorSetting2(bool blFun[], const std::string Dirpatch, const std::string fileName, int size, ImColor clrFun[], ImColor clr){
    for(int i=0; i< size; i++){
        if (blFun[i]) {
            clrFun[i] = clr;
            writeInt(Dirpatch, fileName, clr, i);
        }
    }
}

bool readDataBool2(const std::string Dirpatch, std::string fileName, int pos){
    if (getInt(Dirpatch, fileName, pos) == 1){
        return true;
    } else {
        return false;
    }
}

void readDataColorLoop2(bool blFun[], const std::string Dirpatch, const std::string fileName1, const std::string fileName2, int size, ImColor clrFun[]){
    for (int i = 1; i < size + 1; i++) {
        blFun[i-1] = readDataBool2(Dirpatch, fileName1, i);
        if (blFun[i-1]){
            if (getInt(Dirpatch, fileName2, i) != 0){
                clrFun[i-1] = getInt(Dirpatch, fileName2, i);
            } else {
                clrFun[i-1] = ImColor(248,184,216, 255);
            }
        } else {
            clrFun[i-1] = ImColor(248,184,216, 255);
        }
    }
}

bool fileExit(const std::string fileName){
    struct stat buf;
    if(stat(fileName.c_str(), &buf) != -1){
        return true;
    }
    return false;
}

bool readDataBool(std::string fileName){
    string line;
    ifstream myfile (Dirpatch + fileName +".ini");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line == "1") {
                return true;
            } else {
                return false;
            }
        }
        myfile.close();
    }
}

//Write
void saveData(std::string fileName, int val){
    ofstream myfile (Dirpatch + fileName +".ini");
    if (myfile.is_open()) {
        myfile << val;
        myfile.close();
    } else {
        cout << "Unable to open file";
    }
}

void saveDataLoop(const char *strFun[], bool blFun[], int size, int val){
    for(int i=0; i< size; i++){
        saveData(strFun[i], val);
        blFun[i] = readDataBool(strFun[i]);
    }
}

void saveDataColor(std::string fileName, ImColor val){
    FILE *ColorSave = nullptr;
    std::string fl = std::string(Dirpatch + fileName +"Clr.ini");
    if (ColorSave == nullptr) {
        ColorSave = fopen(fl.c_str(), "wb+");
    }
    fseek(ColorSave, 0, SEEK_SET);
    fwrite(&val, sizeof(ImColor), 1, ColorSave);
    fflush(ColorSave);
    fsync(fileno(ColorSave));
}

void ColorSetting(const char *strFun[], int size, ImColor clrFun[], ImColor clr){
    for(int i=0; i< size; i++){
        if (fileExit(Dirpatch + strFun[i] + ".ini")) {
            if (readDataBool(strFun[i])) {
                //if (ImGui::ColorEdit4(strFun[i], (float *) &clrFun[i],
                //                      ImGuiColorEditFlags_AlphaBar)) {
                clrFun[i] = clr;
                    saveDataColor(strFun[i], clrFun[i]);
                //}
            }
        }
    }
}

//Read
int readDataInt(std::string fileName){
    string line;
    ifstream myfile (Dirpatch + fileName +".ini");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            return stoi(line);
        }
        myfile.close();
    }
}

ImColor readDataColor(std::string fileName, ImColor val){
    FILE *ColorSave = nullptr;
    std::string fl = std::string(Dirpatch + fileName +"Clr.ini");
    if (ColorSave == nullptr) {
        ColorSave = fopen(fl.c_str(), "rb+");
    }
    fseek(ColorSave, 0, SEEK_SET);
    fread(&val, sizeof(ImColor), 1, ColorSave);
    return val;
}

void readDataColorLoop(const char *strFun[], int size, bool blFun[], ImColor clrFun[]){
    for (int i = 0; i < size; i++) {
        if (fileExit(Dirpatch + strFun[i] + ".ini")) {
            blFun[i] = readDataBool(strFun[i]);
            if (blFun[i]){
                if (fileExit(Dirpatch + strFun[i] + "Clr.ini")) {
                    clrFun[i] = readDataColor(strFun[i], clrFun[i]);
                } else {
                    clrFun[i] = ImColor(248,184,216, 255);
                }
            } else {
                clrFun[i] = ImColor(248,184,216, 255);
            }
        } else {
            saveData(strFun[i], 0);
            clrFun[i] = ImColor(248,184,216, 255);
        }
    }
}

void BoolLoop(const char *strFun[], bool blFun[], int size, bool val, ImColor clrFun[]){
    for(int i=0; i< size; i++){
        blFun[i] = val;
        if (!val){
            if (fileExit(Dirpatch + strFun[i] + ".ini")) {
                blFun[i] = readDataBool(strFun[i]);
                clrFun[i] = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
            }
        }
    }
}

void BoolLoopDraw(const char *strFun[], bool blFun[], int size){
    for(int i=0; i< size; i++){
        if (fileExit(Dirpatch + strFun[i] + ".ini")) {
            blFun[i] = readDataBool(strFun[i]);
        }
    }
}

bool charEquals(const char *firstSTR, const char * secondSTR){
    if (strcmp(firstSTR, secondSTR) == 0) {
        return true;
    } else {
        return false;
    }
}

bool isPartOf(const char* w1, const char* w2) {
    int i=0;
    int j=0;
    for(i;i < strlen(w1); i++) {
        if(w1[i] == w2[j]) {
            j++;
        }
    }

    if(strlen(w2) == j)
        return true;
    else
        return false;
}

#endif
