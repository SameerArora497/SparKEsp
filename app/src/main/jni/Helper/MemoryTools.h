#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <cinttypes>

#include "obfuscate.h"

FILE *fp;
char *bm = "com.pubg.imobile";

int pid,handle,work=0,iCount=0;

long int ReqAddr[5000],
        strAddr[5000],
        StartAddr[10000],
        EndAddr[10000];

enum{
    All,
    C_ALLOC,
    Anonymous
};

enum{
    DWORD,
    FLOAT
};

int getPID(const char *process_name) {
    int id;
    pid = -1;
    DIR *dir;
    FILE *f;
    char filename[128];
    char cmdline[256];
    struct dirent *entry;
    if (process_name == NULL) {
        return -1;
    }
    dir = opendir("/proc");
    if (dir == NULL) {
        return -1;
    }
    while ((entry = readdir(dir)) != NULL) {
        sscanf(entry->d_name, "%d", &id);
        if (id != 0) {
            sprintf(filename, "/proc/%d/cmdline", id);
            f = fopen(filename, "r");
            if (f) {
                fgets(cmdline, sizeof(cmdline), f);
                fclose(f);
                if (strcmp(process_name, cmdline) == 0) {
                    pid = id;
                    break;
                }
            }
        }
    }
    closedir(dir);
    return pid;
}

uintptr_t get_module_base(const char* module) {
    FILE *fp;
    uintptr_t addr = 0;
    char filename[40], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    fp = fopen(filename, "rt");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer,module)) {
                addr = (uintptr_t) strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

void Write(uintptr_t address,int value) {
    pwrite64(handle, (void*)&value, sizeof(value), address);
}

void Bypass(){
    pid = getPID(bm);
    char lj[64];
    sprintf(lj,"/proc/%d/mem", pid);
    handle = open(lj, O_RDWR);
    long int LibTerSafe = get_module_base("libanogs.so");
    while (!LibTerSafe){
        sleep(1);
        LibTerSafe = get_module_base("libanogs.so");
    }
    Write(LibTerSafe + 0x99d60,-721215457);
    Write(LibTerSafe + 0x99c30,-698416192);
    Write(LibTerSafe + 0x9a550,-698416192);

    Write(LibTerSafe + 0x831098,-721215457);
    Write(LibTerSafe + 0x83103C,-721215457);
    Write(LibTerSafe + 0x8310E8,-721215457);
    Write(LibTerSafe + 0x836E70,-721215457);
    Write(LibTerSafe + 0x836E08,-721215457);
    Write(LibTerSafe + 0x836DF0,-721215457);
    Write(LibTerSafe + 0x836DC0,-721215457);
    Write(LibTerSafe + 0x836D00,-721215457);
    Write(LibTerSafe + 0x836CEC,-721215457);
    Write(LibTerSafe + 0x836CA4,-721215457);
    Write(LibTerSafe + 0x836C90,-721215457);
    Write(LibTerSafe + 0x836C88,-721215457);
    Write(LibTerSafe + 0x836C70,-721215457);
    Write(LibTerSafe + 0x836C2C,-721215457);
    Write(LibTerSafe + 0x836C10,-721215457);
    Write(LibTerSafe + 0x836BCC,-721215457);
    Write(LibTerSafe + 0x836B24,-721215457);
    Write(LibTerSafe + 0x835E34,-721215457);
    Write(LibTerSafe + 0x835DD4,-721215457);
    Write(LibTerSafe + 0x835D88,-721215457);
    Write(LibTerSafe + 0x8352F8,-721215457);
    Write(LibTerSafe + 0x8352C8,-721215457);
    Write(LibTerSafe + 0x836C90,-721215457);
    Write(LibTerSafe + 0x83503C,-721215457);
    Write(LibTerSafe + 0x831108,-721215457);
    Write(LibTerSafe + 0x831010,-721215457);
    Write(LibTerSafe + 0x83103C,-721215457);
    Write(LibTerSafe + 0x8310E8,-721215457);
    Write(LibTerSafe + 0x831120,-721215457);
    Write(LibTerSafe + 0x831158,-721215457);
    Write(LibTerSafe + 0x833F44,-721215457);
    Write(LibTerSafe + 0x834C48,-721215457);
    Write(LibTerSafe + 0x834D68,-721215457);
    Write(LibTerSafe + 0x834E10,-721215457);
    Write(LibTerSafe + 0x834E40,-721215457);
    Write(LibTerSafe + 0x834ED0,-721215457);
    Write(LibTerSafe + 0x834EA0,-721215457);
    Write(LibTerSafe + 0x834F00,-721215457);
    Write(LibTerSafe + 0x834F38,-721215457);
    Write(LibTerSafe + 0x834FDC,-721215457);
    Write(LibTerSafe + 0x834FF4,-721215457);
    return;
}

void inilize(){
    pid = getPID(bm);
    char filename[32];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    fp = fopen(filename, "r");
    char lj[64];
    sprintf(lj,"/proc/%d/mem",pid);
    handle = open(lj,O_RDWR);
    if (handle == -1){
        puts("Failed to get memory!\n");
    }
}

void readMemory_All(){
    char line[512];
    char tmpname[64];
    long int tmpbase,tmpend;
    while (fgets(line, sizeof line, fp)) {
        if (sscanf(line,"%" PRIXPTR "-%" PRIXPTR " %*s %*s %*s %*s %s", &tmpbase, &tmpend, tmpname) > 0) {
            if (strstr(line,"rw") && strlen(line) >= 47 && !strstr(tmpname,"/data/app/") && !strstr(tmpname,"[stack]")
                && !strstr(tmpname,"/dev/ashmem/")  && !strstr(tmpname,"[heap]")){
                StartAddr[work] = tmpbase;
                EndAddr[work] = tmpend;
                work++;
            }
        } else {
            break;
        }
    }
    fclose(fp);
}

void readMemory_CAlloc(){
    char line[512];
    char tmpname[64];
    long int tmpbase,tmpend;
    while (fgets(line, sizeof line, fp)) {
        if (sscanf(line,"%" PRIXPTR "-%" PRIXPTR " %*s %*s %*s %*s %s", &tmpbase, &tmpend, tmpname) > 0) {
            if (strstr(line,"rw") && strstr(tmpname,"[anon:libc_malloc]") || strstr(tmpname,"[anon:scudo:primary]")){
                StartAddr[work] = tmpbase;
                EndAddr[work] = tmpend;
                work++;
            }
        } else {
            break;
        }
    }
    fclose(fp);
}

void readMemory_Anonymous(){
    char line[512];
    long int tmpbase,tmpend;
    while (fgets(line, sizeof line, fp)) {
        if (sscanf(line,"%" PRIXPTR "-%" PRIXPTR " %*s %*s %*s %*s", &tmpbase, &tmpend) > 0) {
            if (strstr(line,"rw-p") && strlen(line)<47){
                StartAddr[work] = tmpbase;
                EndAddr[work] = tmpend;
                work++;
            }
        } else {
            break;
        }
    }
    fclose(fp);
}

void SelectMemory(int MemorySearch){
    switch(MemorySearch){
        case 0:
            readMemory_All();
            break;
        case 1:
            readMemory_CAlloc();
            break;
        case 2:
            readMemory_Anonymous();
            break;
    }
}

void MemorySearch_Dword(int value){
    int buff[1024] = {0};
    long int addr;
    for(int i=0;i<work;i++){
        long int c=(EndAddr[i]-StartAddr[i])/4096;
        for (int j=0;j<c;j++){
            addr = StartAddr[i]+j*4096;
            pread64(handle,buff,0x1000,addr);
            for (int k=0;k<1024;k++) {
                if (buff[k] == value) {
                    ReqAddr[iCount] = addr+k*4;
                    iCount++;
                }
            }
        }
    }
}

void MemorySearch_Float(float value){
    float buff[1024] = {0};
    long int addr;
    for(int i=0;i<work;i++){
        long int c=(EndAddr[i]-StartAddr[i])/4096;
        for (int j=0;j<c;j++){
            addr = StartAddr[i]+j*4096;
            pread64(handle,buff,0x1000,addr);
            for (int k=0;k<1024;k++) {
                if (buff[k] == value) {
                    ReqAddr[iCount] = addr+k*4;
                    iCount++;
                }
            }
        }
    }
}

void MemorySearch(char *value,int type){
    switch (type) {
        case 0:
            MemorySearch_Dword(atoi(value));
            break;
        case 1:
            MemorySearch_Float(atof(value));
            break;
    }
}

void MemoryOffset_Float(float value,long int offset){
    float buff[4];
    int v=0;
    for(int i=0;i<iCount;i++){
        pread64(handle,buff,4,ReqAddr[i]+offset);
        if (buff[0] == value) {
            strAddr[v] = ReqAddr[i];
            v++;
        }
    }
    memcpy(ReqAddr, strAddr, 4*(sizeof(strAddr)/sizeof(*strAddr)));
    iCount = v;
}

void MemoryOffset_Dword(int value,long int offset){
    int buff[4];
    int v=0;
    for(int i=0;i<iCount;i++){
        pread64(handle,buff,4,ReqAddr[i]+offset);
        if (buff[0] == value) {
            strAddr[v] = ReqAddr[i];
            v++;
        }
    }
    memcpy(ReqAddr, strAddr, 4*(sizeof(strAddr)/sizeof(*strAddr)));
    iCount = v;
}

void MemoryOffset(char *value,long int offset,int tyoe){
    switch (tyoe) {
        case 0:
            MemoryOffset_Dword(atoi(value),offset);
            break;
        case 1:
            MemoryOffset_Float(atof(value),offset);
            break;
    }
}

void MemoryWrite_Float(float value){
    for(int i=0;i<iCount;i++){
        pwrite64(handle,&value,4,ReqAddr[i]);
    }
}

void MemoryWrite_Dword(int value){
    for(int i=0;i<iCount;i++){
        pwrite64(handle,&value,4,ReqAddr[i]);
    }
}

void MemoryWrite(char *value,int type){
    switch (type) {
        case 0:
            MemoryWrite_Dword(atoi(value));
            break;
        case 1:
            MemoryWrite_Float(atof(value));
            break;
    }
}

void MemoryWrite_com_Dword(int value,long int offset){
    for(int i=0;i<iCount;i++){
        pwrite64(handle,&value,4,ReqAddr[i]+offset);
    }
}

void MemoryWrite_com_Float(float value,long int offset){
    for(int i=0;i<iCount;i++){
        pwrite64(handle,&value,4,ReqAddr[i]+offset);
    }
}

void MemoryWrite_com(char *value,long int offset,int type){
    switch (type) {
        case 0:
            MemoryWrite_com_Dword(atoi(value),offset);
            break;
        case 1:
            MemoryWrite_com_Float(atof(value),offset);
            break;
    }
}

void clearResults(){
    work = 0;
    iCount = 0;
    inilize();
}