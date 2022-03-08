#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>



int  print_if_dir_NULL(DIR *dir, char*path)// определяет, есть ли директории внутри директории
{
        struct dirent * direntt;
        
        struct stat st;
        char buff[1024];

        while(direntt = readdir(dir))
        {
                strcpy(buff, path);
                strcat(buff,"/");
                strcat(buff, direntt->d_name);
                
                stat(buff, &st);
              
                if(strcmp(direntt->d_name, ".") && strcmp(direntt->d_name, "..") && (st.st_mode & S_IFMT)==S_IFDIR) //если в директория не "." и "..", то значит проверяемая директория имеет директории
                {
                        return 0;
                        
                }
    }
    return 1;
    }



int main(int argc, char *argv[])
{
        struct dirent * dirent;
        struct stat st;
        char buff[1024];
        char path[1024];
        DIR *dir;
        DIR *dirr;

        if (argc > 1)
        {
                if (!chdir(argv[1]))//если выбранный директория существует
                {
                        dir = opendir(".");
			if (dir==NULL) {perror("Cant open Dir"); return 1;}
                        getcwd (path,256);
                        while(dirent = readdir(dir))
                        {

                                strcpy(buff, path);
                                strcat(buff, "/");
                                strcat(buff, dirent->d_name);
                                stat(buff, &st);
                                if (S_ISDIR(st.st_mode))
                                {
                                        dirr = opendir(buff);//переход в директорию на проверку, есть ли в нем директории
					if (dirr==NULL) perror("Cant open dir(not critical)");
                                        else
					{if (print_if_dir_NULL (dirr, buff)) printf ("%s \n",dirent->d_name);
                                        closedir (dirr);}
                                        chdir(".."); //возвращение в исходную
                                }



                        }
                closedir(dir);
                }
                else
                {
                        perror("ERROR: Dir enter incorrectly");
                        return 1;

                }
        }
        else
        {
                perror("ERROR: Dir must be defined");
                return 1;
        }
}



