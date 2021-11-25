#include "GB_handler.h"
#include "GB_auth.h"
int main()
{
    
    GradeBookHandle gbh;
    Authenticator auth;
    int loginStatus=0;

    while(true)
    {
        loginStatus=auth.authenticate();
        if (loginStatus==-1) break;
        if (loginStatus==0) continue;
        //gbh.input();
        gbh.load("grades.db"); 
        //gbh.store("grades.db"); 
        gbh.display(); 
        break;

    }
}

