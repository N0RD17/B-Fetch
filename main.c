#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // POSIX API

void getOS()
{
   char* buffer = NULL;
   size_t len = 0;

   FILE* file = fopen("/etc/lsb-release", "r");
   // Check if file is opened successfully
   if(file == NULL){
      perror("Error opening file!");
      return;
   }

   if(getline(&buffer, &len, file) != -1){
      size_t strLen = strlen(buffer);
      memmove(buffer, buffer + 12, strLen - 12 + 1);

      strLen -= 12;

      // Truncate string
      buffer[strLen - 2] = '\0';
      printf("\tOS: %s\n", buffer);
   } else {
      puts("Error reading file or file is empty\n");
      free(buffer);
      fclose(file); // Close file before returning
      return;
   }

   fclose(file);

   // Release allocated memory
   free(buffer);
}

void getPC()
{
   char* TheFileContents = NULL;
   size_t sizeFile = 0;
   FILE* hostFile = fopen("/etc/hostname", "r");
   if(hostFile == NULL) {
      perror("Error opening file");
      exit(1);
   }

   fseek(hostFile, 0, SEEK_END);
   sizeFile = ftell(hostFile);
   fseek(hostFile, 0, SEEK_SET);

   // +1 for null terminator
   TheFileContents = (char*)malloc(sizeFile + 1);

   fread(TheFileContents, 1, sizeFile, hostFile);

   TheFileContents[sizeFile] = '\0';

   printf("@%s", TheFileContents);

   free(TheFileContents);
   TheFileContents = NULL;
   fclose(hostFile);
}

int main()
{

   
   printf("\t%s", getlogin());
   getPC();
   puts("\t---------------------------");
   getOS();
   return 0;
}
