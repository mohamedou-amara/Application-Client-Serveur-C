
//--------------------------------------------------- IDOUMOU AMARA MOHAMEDOU ---------------------------------------------------
//--------------------------------------------------- PROJET C AVANCÉE ----------------------------------------------------------

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    char username[20];
    int password;
    
}Login;

typedef struct
{
    char User[20];
    int password;
    char type[20];
}Contenue;

typedef struct
{
    char rue[30];
    char ville[20];
    char pays[20];
}Address;

typedef struct
{
    char nom[20];
    char prenom[20];
    int GSM;
    char email[30];
    Address adr;
}Contact;


Contact *rechercher(char *nom_fich,int telephone){
    Contact *c ;
    FILE *f2=fopen(nom_fich,"r");
    while(!feof(f2))
    {
        fscanf(f2,"%s %s %s %d %s %s %s\n",c->nom,c->prenom,c->email,&c->GSM,c->adr.rue,c->adr.ville,c->adr.pays);
        
        if(telephone == c->GSM)
        {
            return c;
            break;
        }
    }
    fclose(f2);

    return NULL ;
}



void modifier(int telephone , Contact M)
{
    Contact c ;
    FILE *f_in=fopen("contact.txt","r");
    FILE *f_out=fopen("Temp.txt", "a");
    if(f_in!=NULL&&f_out!=NULL){
    while(!feof(f_in)){
        if(fscanf(f_in,"%s %s %s %d %s %s %s\n",c.nom,c.prenom,c.email,&c.GSM,c.adr.rue,c.adr.ville,c.adr.pays)!=0)
        {
        if(telephone!= c.GSM)
            fprintf(f_out,"%s %s %s %d %s %s %s\n",c.nom,c.prenom,c.email,c.GSM,c.adr.rue,c.adr.ville,c.adr.pays);
         if(telephone==c.GSM)
             fprintf(f_out, "%s %s %s %d %s %s %s\n",M.nom,M.prenom,M.email,M.GSM,M.adr.rue,M.adr.ville,M.adr.pays);
           
        }
        }
    
    fclose(f_in);
    fclose(f_out);
    remove("contact.txt");
    rename("Temp.txt", "contact.txt");
    }
    }



void Supprimer(int tel){
 FILE *fin=fopen("contact.txt","r");
 char *nom_res="temp.txt";
 FILE *fout=fopen(nom_res,"a");
 Contact e;
   
    if(fin!=NULL&&fout!=NULL){
    
        while(!feof(fin))
        {
            fscanf(fin,"%s %s %s %d %s %s %s\n",e.nom,e.prenom,e.email,&e.GSM,e.adr.rue,e.adr.ville,e.adr.pays);
          if(e.GSM!=tel)
               fprintf(fout,"%s %s %s %d %s %s %s \n",e.nom,e.prenom,e.email,e.GSM,e.adr.rue,e.adr.ville,e.adr.pays);

        }
        fclose(fin);
        fclose(fout);
        remove("contact.txt");
        rename(nom_res,"contact.txt");
        }
  
}
          

int main() {
   
    int serveur;
    int sock_nv;
    int x,y,num,br;
    int choix;
    int traitement = 0;
    Login P;
    Contact C;
    Contact M;
    Contenue R ;
    Contact *E;
    FILE *f1,*f2;
    f1=fopen("Login.txt","r");
    f2=fopen("contact.txt","a");
//    char CH[100] = "verifier votre login ou mot de passe :) ";
     
    printf("\n\n============================================** Le serveur **===========================================\n");

    serveur = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(50000);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (bind(serveur, (struct sockaddr*)&server_address, sizeof(struct sockaddr))>=0)
    
        printf(" \n Serveur attacher ..................... \n");
    
    
    if(listen(serveur,0)==0)
        printf("\n en attente des demande de connection ......................... \n");
   
    
        
    struct sockaddr_in adress_client;
    socklen_t size = sizeof(adress_client);
    sock_nv = accept(serveur, (struct sockaddr*) &adress_client , &size);
     printf("\n Client accepteé .............................................. \n ");
   
    recv(sock_nv, &P , sizeof(Login), 0);
    
   printf("\n le client : %s \n ",P.username);
    
           
   
           
    if(fscanf(f1,"%s %d %s\n",R.User,&R.password,R.type)!=0)
    {
        
        if((strcmp(R.User,P.username)== 0) && (R.password == P.password) && (strcmp(R.type,"Admin") == 0))
        {
            
            x=1;
            printf(" \n ********************************** Admin a accedè ********************************************* \n");
            send(sock_nv, &x, sizeof(x), 0);
            
            do{
                if(recv(sock_nv, &choix, sizeof(int),0)!=-1){

            switch(choix)
            {
                        
                case 1 :
                    printf("le choix de l'utilisateur : %d \n",choix);
                    if((recv(sock_nv,&C, sizeof(Contact),0))>=0)
                    {
                    f2=fopen("contact.txt","a");
                    fprintf(f2,"%s %s %s %d %s %s %s\n",C.nom,C.prenom,C.email,C.GSM,C.adr.rue,C.adr.ville,C.adr.pays);
                    fclose(f2);
                    traitement = 1;
                    send(sock_nv, &traitement, sizeof(int), 0);
                   }
                    break;

                case 2 :
                    printf("le choix de l'utilisateur : %d \n",choix);
                    recv(sock_nv, &num, sizeof(num), 0);
                    E=rechercher("contact.txt",num);
                    send(sock_nv, &E, sizeof(E), 0);
                    break;
                    
                case 3 :
                    printf("le choix de l'utilisateur : %d \n",choix);
                     recv(sock_nv, &y, sizeof(y), 0);
                     Supprimer(y);
                     traitement=1;
                    send(sock_nv,&traitement,sizeof(int),0);
                    break;
                    
                case 4:
                    printf("le choix de l'utilisateur : %d \n",choix);
                    recv(sock_nv, &num, sizeof(num), 0);
                    recv(sock_nv, &M , sizeof(Contact), 0);
                    
                    modifier(num,M);
                    traitement=1;
                    send(sock_nv,&traitement,sizeof(int) ,0);
                    
                    break;
                case 5 :
                    printf("le choix de l'utilisateur : %d \n",choix);
                    f2=fopen("contact.txt", "r");
                    if(f2!=NULL)
                    {
                    while(!feof(f2))
                    {
                        fscanf(f2,"%s %s %s %d %s %s %s\n",C.nom,C.prenom,C.email,&C.GSM,C.adr.rue,C.adr.ville,C.adr.pays);
                        send(sock_nv, &C, sizeof(Contact), 0);
                        
                    }
                    fclose(f2);
                    }
                    
                    traitement =1;
                    send(sock_nv, &traitement, sizeof(int), 0);
                     break;

                case 6:
                    printf("le choix de l'utilisateur : %d \n",choix);
                    printf("\n au revoire \n");
                    break;
                    
                default:
                    printf("choix valide s'il vous plais");
                    break;
                    
                }
                    
                }
                
            
                
            }while(choix!=6);
            
           
            exit(0);
        }
        
        else if (strcmp(R.User,P.username)== 0 && R.password == P.password && strcmp(R.type , "invite") == 0)
        {
            x=0;
            printf("************************************* invité a acceder ******************************************** \n");
            send(sock_nv, &x, sizeof(x), 0);
            do{
                if(recv(sock_nv, &choix, sizeof(int),0)!=-1)
                    switch(choix)
                    {
                        case 1 :
                            printf("le choix de l'utilisateur : %d \n",choix);
                            recv(sock_nv, &num, sizeof(num), 0);
                            E=rechercher("contact.txt",num);
                            send(sock_nv, &E, sizeof(E), 0);
                            break;
                        case 2 :
                            printf("le choix de l'utilisateur : %d \n",choix);
                            f2=fopen("contact.txt", "r");
                            if(f2!=NULL)
                            {
                            while(!feof(f2))
                            {
                                fscanf(f2,"%s %s %s %d %s %s %s\n",C.nom,C.prenom,C.email,&C.GSM,C.adr.rue,C.adr.ville,C.adr.pays);
                                send(sock_nv, &C, sizeof(Contact), 0);
                            }
                            fclose(f2);
                                br=1;
                                send(sock_nv,&br,sizeof(int) ,0);
                            }
                            traitement =1;
                            send(sock_nv, &traitement, sizeof(int), 0);
                             break;
                        case 3 :
                            printf("le choix de l'utilisateur : %d \n",choix);
                            printf("\n****************************** client est deconnecter ***********************************\n");
                            break;
                            
                    }
                    } while(choix!=3);
            exit(0);
        }
        
    }
    fclose(f1);
    shutdown(sock_nv, 2);
    return 0;
}
