#include "utils/file.h"
#include <string>
#include <string.h>
#include <dirent.h>
#include <vector>

#include <sys/stat.h>

bool is_file(const std::string &path)
{
    struct stat st;
    int ret = stat(path.c_str(),&st);
    return ret>=0 && S_ISREG(st.st_mode);
}

std::vector<std::string> get_files(const std::string &path,const std::string &postfix)
{
    std::vector<std::string> names;

    struct dirent* ent = NULL;
    DIR* dir = opendir(path.c_str());
    while(NULL!=(ent=readdir(dir)))
    {
        std::string full_path = path+"/"+ent->d_name;
        if(is_file(full_path))
        {
            if(postfix==""||strstr(ent->d_name,postfix.c_str())!=NULL)
            {
                names.push_back(ent->d_name);
            }
        }
    }
    closedir(dir);
    return names;
}

