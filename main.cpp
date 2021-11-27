#include "GB_handler.h"
#include "GB_auth.h"
int main()
{
    // instantiating the database and authentication class    
    GradeBookHandle gbh;
    Authenticator auth;
    int loginStatus=0;

    loginStatus=auth.authenticate();
    if (loginStatus!=-1) gbh.uMenu();

}

