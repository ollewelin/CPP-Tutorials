#include <QCoreApplication>
//https://www.waveshare.com/wiki/Raspberry_Pi_Tutorial_Series:_1-Wire_DS18B20_Sensor
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
//#include <vector>
#include <QVector>
#define ONE_WIRE_DEVICE_PATH "/sys/bus/w1/devices/"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    printf("DS18B20 test program\n");

    char path[50] = ONE_WIRE_DEVICE_PATH;
   // char path[50] = "~/olle";
    printf("%s\n", path);
    char rom[20];
    char rom2[20];
    char buf[100];
    DIR *dirp;
    QVector<QString> rom_vect;
    struct dirent *direntp;
    int fd =-1;
    char *temp;
    float value;
    // These tow lines mount the device:
    system("sudo modprobe w1-gpio");
    system("sudo modprobe w1-therm");
    // Check if /sys/bus/w1/devices/ exists.
    dirp = opendir(path);
    printf("debug test1\n");
    if(dirp == NULL)
    {
        printf("opendir error\n");
        return 1;
    }
    if(dirp == NULL){
        printf("Debug1. FAIL open directory ERROR\n");
    }
    else {
        printf("OK open directory\n");
    }

    // Reads the directories or files in the current directory.
    direntp = readdir(dirp);
   // int cnt_temp_sens = 0;
    while(direntp != NULL)
    {
        // If 28-00000 is the substring of d_name,
        // then copy d_name to rom and print rom.

        if(!(strstr(direntp->d_name,"w")) && !(strstr(direntp->d_name,".")) && !(strstr(direntp->d_name,"..")))
        {
            strcpy(rom,direntp->d_name);
            printf(" rom: %s\n",rom);
            rom_vect.push_back(QString::fromLocal8Bit(rom));
        }
       // cnt_temp_sens++;
        direntp = readdir(dirp);
    }
    closedir(dirp);

    QByteArray rom_string_char_Array;
    for(int i=0;i<rom_vect.size();i++){
        printf("rom_vector size = %d, i=%d\n", rom_vect.size(), i);
        rom_string_char_Array = rom_vect[i].toLatin1();
        const char *str_rom_string_char;//Prepare a char[] array
        str_rom_string_char = rom_string_char_Array.data();
        printf("str_rom_string_char rom:%s\n", str_rom_string_char);
    }
    // Append the String rom and "/w1_slave" to path
    // path becomes to "/sys/bus/w1/devices/28-00000xxxx/w1_slave"
    strcat(path,rom);
    strcat(path,"/w1_slave");
//        printf("rom :%s\n", rom);

    while(1)
    {

        for(int i=0;i<rom_vect.size();i++){

           // printf("rom_vector size = %d, i=%d\n", rom_vect.size(), i);
            rom_string_char_Array = rom_vect[i].toLatin1();
            const char *str_rom_string_char;//Prepare a char[] array
            str_rom_string_char = rom_string_char_Array.data();

            char path_l[50] = ONE_WIRE_DEVICE_PATH;
            strcat(path_l,str_rom_string_char);
            strcat(path_l,"/w1_slave");

            // Open the file in the path.
            fd = open(path_l,O_RDONLY);
            if(fd < 0)
            {
                printf("open error 2\n");
                return 1;
            }
            // Read the file
            int filesize1 = read(fd,buf,sizeof(buf));
            if(filesize1 < 0)
            {
                printf("read error\n");
                return 1;
            }
            // Returns the first index of 't'.
            temp = strchr(buf,'t');
            // Read the string following "t=".
            sscanf(temp,"t=%s",temp);
            // atof: changes string to float.
            value = atof(temp)/1000;
         //   printf("rom :%s\n", rom);
            printf(" temp : %3.3f °C",value);
            printf("   sensor nr %d,  ID:%s\n", i+1, str_rom_string_char);

   //         printf("\n");
            usleep(1);


        }


    }
   // return 0;

    return a.exec();
}


