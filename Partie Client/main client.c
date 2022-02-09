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


void menu_Admin()
{
    
    printf("-------------------------------------------vous étes Aministrateur-------------------------------------------\n");
    printf("***************************************************Menu******************************************************\n");
    printf("1-Ajouter un contact \n");
    printf("2-Rechercher un contact \n");
    printf("3-Supprimer un contact \n");
    printf("4-Modifier un contact \n");
    printf("5-Afficher tout les contact \n");
    printf("6-Quitter \n");
    printf("Entrer votre choix : ");
}

void menu_inviter()
{
   
    printf("---------------------------------------------vous étes Utilisateur----------------------------------------------\n");
    printf("****************************************************Menu*********************************************************\n");
    printf("1-Rechercher Un contact \n");
    printf("2-Afficher tous les contact \n");
    printf("3-Quitter \n");
    
}

Contact Ajouter()
{
    Contact C;
    printf("entrer le nom du contact : ");
    fflush(stdin);
    gets(C.nom);
    printf("entrer le prenom du contact : ");
    fflush(stdin);
    gets(C.prenom);
    printf("entrer le email du contact : ");
    fflush(stdin);
    gets(C.email);
    printf("entrer le GSM du contact : ");
    fflush(stdin);
    scanf("%d",&C.GSM);
    printf("entrer le rue du contact : ");
    fflush(stdin);
    gets(C.adr.rue);
    printf("entrer le ville du contact : ");
    fflush(stdin);
    gets(C.adr.ville);
    printf("entrer la pays du contact : ");
    fflush(stdin);
    gets(C.adr.pays);
    return C;
}


Contact sasie_nv()
{
    Contact c ;
           fflush(stdin);
           printf("Entrer le nom modifié : ");
           gets(c.nom);
           
           
    
           printf("Entrer le prenom modifié : ");
           gets(c.prenom);
           fflush(stdin);
           
        
           printf("Entrer l'email modifié : ");
           gets(c.email);
           fflush(stdin);
           
    
           printf("Entrer le GSM modifié : ");
           scanf("%d",&(c.GSM));
           fflush(stdin);
           
           
           printf("Entrer la rue modifiée : ");
           gets(c.adr.rue);
           fflush(stdin);
           
          
           printf("Entrer la ville modifiée : ");
           gets(c.adr.ville);
           fflush(stdin);
           
    
           printf("Entrer le pays modifié : ");
           gets(c.adr.pays);
           fflush(stdin);
          
           
    return c ;
           }
        
    
    

Contact *rechercher(int telephone){
    Contact *c ;
    FILE *f_in=fopen("contact.txt","r");
printf("entrer le numero de telephone du contact voulu chercher : ");
scanf("%d",&telephone);
    while(!feof(f_in)){
        if(fscanf(f_in,"%s %s %s %d %s %s %s",c->nom,c->prenom,c->email,&c->GSM,c->adr.rue,c->adr.ville,c->adr.pays)!=0)
        {
        if(telephone== c->GSM)
        {
            printf("Contact trouvé !!!!\n");
            return c ;
        }
        }
        }
    return NULL;
    }


int main() {
    
    int client;
    Login P;
    Contact C;
    int br=0;
    Contact M;
    Contact *E;
    int x,y,num, restraitement=0;
    int choix ;
   
    client=socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in adress_client;
    memset(&adress_client, '\0', sizeof(adress_client));
    adress_client.sin_family = AF_INET;
    adress_client.sin_port = htons(50000);
    adress_client.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (connect(client, (const struct sockaddr*)&adress_client,sizeof(adress_client))==0)
      printf("etablissement de connexion ..................................\n");
      
      printf("entrer votre Username : ");
      fflush(stdin);
      gets(P.username);
      printf("entrer votre mot de passe : ");
      fflush(stdin);
      scanf("%d",&P.password);
      send( client , &P , sizeof(Login) , 0 );
      recv(client, &x , sizeof(int) , 0);
   
    if(x==1)
    {
        do{
            
            menu_Admin();
            scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                fflush(stdin);
                send(client, &choix, sizeof(int), 0);
                C = Ajouter();
                send(client, &C, sizeof(C), 0);
                recv(client, &restraitement, sizeof(int), 0);
                if(restraitement==1)
                printf("Ajout a été realisé avec succés : \n");
                break;
            case 2 :
                send(client, &choix, sizeof(int), 0);
                printf("entrer le numero de telephone : ");
                scanf("%d",&num);
                send(client ,&num, sizeof(num), 0);
                recv(client,E,sizeof(E),0);
                if(E!=NULL)
                    printf("%s %s %s %d %s %s %s \n",E->nom,E->prenom,E->email,E->GSM,E->adr.rue,E->adr.ville,E->adr.pays);
                else
                    printf("client introuvable !!!!\n");
                break;

            
            case 3 :
                fflush(stdin);
                send(client, &choix, sizeof(int), 0);
                printf("entrer le GSM du contact : ");
                scanf("%d",&y);
                send(client, &y, sizeof(y), 0);
                recv(client, &restraitement, sizeof(int), 0);
                if(restraitement==1)
                printf("la suppression a été realiser avec succes \n");
                break;
                
            case 4 :
                fflush(stdin);
                send(client, &choix, sizeof(int), 0);
                printf("entrer le numero de telephone : ");
                scanf("%d",&num);
                send(client ,&num, sizeof(num), 0);
                M=sasie_nv();
                send(client ,&M, sizeof(Contact), 0);
                recv(client,&restraitement, sizeof(int), 0);
                printf("la modificaation a été realisé avec succeés \n");
                
                break;
                
            case 5:
                fflush(stdin);
                send(client, &choix, sizeof(int), 0);
                while(recv(client, &C, sizeof(Contact), 0)!=-1)
                {
                    
                    printf("%s %s %s %d %s %s %s \n",C.nom,C.prenom,C.email,C.GSM,C.adr.rue,C.adr.ville,C.adr.pays);
                    
                    if(recv(client, &restraitement, sizeof(int), 0)!=-1 && restraitement==1)
                    break;
                }
                printf("l'affichage a été realiser avec succes\n");
                break;
                
            case 6 :
                printf("\n***************************  merci pour votre visite :)  ************************************\n\n");
                break;
                
            default:
                printf("\n**************************** un choix valide s'ils vous plaits :) ***************************** \n");
                break;
        }
        
        }while(choix!=6);
        exit(0);
    }
    
    
    if(x==0)
    {
        do{
             menu_inviter();
             scanf("%d",&choix);
        switch(choix)
        {
            case 1 :
                send(client, &choix, sizeof(int), 0);
                printf("entrer le numero de telephone : ");
                scanf("%d",&num);
                send(client ,&num, sizeof(num), 0);
                recv(client,E,sizeof(E),0);
                if(E!=NULL)
                    printf("%s %s %s %d %s %s %s \n",E->nom,E->prenom,E->email,E->GSM,E->adr.rue,E->adr.ville,E->adr.pays);
                else
                    printf("client introuvable !!!!\n");
                break;
                
            case 2 :
                fflush(stdin);
                send(client, &choix, sizeof(int), 0);
                while(recv(client, &C, sizeof(Contact), 0)!=-1)
                {
                    
                    printf("%s %s %s %d %s %s %s \n",C.nom,C.prenom,C.email,C.GSM,C.adr.rue,C.adr.ville,C.adr.pays);
                    if(recv(client,&br, sizeof(int), 0)!=-1)
                    {
                    if(br==1)
                        break;
                    }
                    fflush(stdin);
                }
                recv(client, &restraitement, sizeof(int), 0);
                if(restraitement==1)
                printf("l'affichage a été realiser avec succes\n");
                break;
                
            case 3 :
                printf("\n***************************  merci pour votre visite :)  ************************************\n\n");
                break;
                
        }
        
        }while(choix!=3);
        exit(0);
    }
    else
    {
        printf("vous ne figurer pas dans notre base de donneés :( \n");
    }
    
    shutdown(client, 2);
    
    return 0;
}
