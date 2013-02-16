/**
 * \file reseau.h
 * \brief Fichier de gestion reseau pour l'envoi et reception de scores en ligne.
 * \author Demingeon Cyril
 */

#include <windows.h>
#include <curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//char* url="http://www.faraweb.fr/dk/dk.php";
char* url="http://ogizanagi.fr/dk/dk.php"; // new url

size_t writer( char* ptr, size_t size, size_t nmemb, char **userdata);
int score_send(char* name,char* score);
char* encode(char* a,char* b);
void get_and_display_scores(SDL_Surface *ecran, Menustruct *GestionMenus);

int score_get(){
    CURL *curl;
    CURLcode res;
    FILE* score;
    if( remove( "score.txt" ) != 0 )
        printf( "Error deleting file\n" );
    if((score = fopen( "score.txt", "w+"))==NULL){
        printf("Couldn't open score.txt");
        MessageBox(0,"Couldn't open score.txt", "Error", MB_OK );
        return 1;
    }
    curl = curl_easy_init();//on initialise Curl pour l'envois
    if(curl)//si il est bien initialis�...
    {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, url);//url des scores
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "str=1");
        //specifie the output
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, score);

        /* Perform the request, res will get the return code */
        if((res = curl_easy_perform(curl))!=0){
            printf("Error in request:\n");
            printf("%s",curl_easy_strerror(res));
            MessageBox(0,"Error in request:\nServer Unreachable", "Error", MB_OK );
        }else{
            //si le score � bien �t� envoy�
            //(le r�sultat contient uploaded ou updated)
            printf("Score loaded\n");
            fclose(score);
            return 0;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }else{
        printf("Couldn't load curl");
        MessageBox(0,"Couldn't load curl", "Error", MB_OK );
    }
    fclose(score);
    return 1;
}

int score_send(char* name,char* score)
{
    CURL *curl;
    CURLcode res;
    char* crypted=encode(name,score);
    char data[120]="name=";
    char *buffer = NULL;
    char *Score_Updated = "checksum valid =>Score Updated";
    char *Score_Uploaded = "checksum valid =>Score Uploaded";
    //on construit la requ�te POST
    strcat(data,name);
    strcat(data,"&score=");
    strcat(data,score);
    strcat(data,"&checksum=");
    strcat(data,crypted);
    //affichage de la requete pour le debug ...
    printf("Sending...\n");
    curl = curl_easy_init();//on initialise Curl pour l'envois
    if(curl)//si il est bien initialis�...
    {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, url);//url des scores
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        //specifie the output
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        /* Perform the request, res will get the return code */
        if((res = curl_easy_perform(curl))!=0){
            printf("Error in request:\n");
            printf("%s",curl_easy_strerror(res));
            MessageBox(0,"Error in request, could not upload score", "Error in request", MB_OK );
        }else{
            //si le score � bien �t� envoy�
            //(le r�sultat contient uploaded ou updated)
            printf("Result:\n##################################\n%s\n##################################\n\n",buffer);

            /*if(strcmp(buffer, Score_Updated)!=0 && strcmp(buffer, Score_Uploaded)!=0)//si l'upload n'a pas march�
                MessageBox(0,buffer, "score error", MB_OK );//on affiche une popup d'erreur.
            */
            return 0;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }else{
        MessageBox(0,buffer, "Unable to load curl :S", MB_OK );
    }
    return 1;
}



            //what we write-length     times we write   where we write
size_t writer( char* ptr, size_t size, size_t nmemb, char **userdata)
{
    int length=size*nmemb,i;
    *userdata=(char* ) realloc(userdata,length);
    *userdata=ptr;
    userdata[length]='\0';
    return length;
}



char* encode(char* a,char* b){
    char* swap;
    char tmp,retour[20];
    int i;
    //si a est plus long que b on inverse
    if(strlen(b)>strlen(a)){
        swap=a;
        a=b;
        b=swap;
    }
    /* initialize random seed: */
    srand ( time(NULL) );
    //on remplis de random chars
    for(i=0;i<20;i++){
        tmp=rand()%26+97;
        retour[i]=tmp;
    }
    //on cr�� le checksum
    for(i=0;i<strlen(a);i++){//pour chaque chars du plus grand
        tmp=((int) ((int) a[i]+7)^((int) b[i%strlen(b)]-7))%26+97;//on fait un xor avec quelques chiffres speciaux...
        retour[i%20]=tmp;//on insere dans retour
    }
    retour[20]='\0';//on rajoute le caract�re de fin de chaine
    return retour;
}

void get_and_display_scores(SDL_Surface *ecran, Menustruct *GestionMenus)
{
    FILE* score;
    int numb=0;
    TTF_Font *police= TTF_OpenFont("arial.ttf", 17);
    SDL_Color couleurNoire{0,0,0};

    char name[40];//les nom seront inscrit ici
    unsigned int value;//les scores l�
    char score_char[11];
    score_get();
    if((score = fopen( "score.txt", "r"))==NULL){//on ouvre le fichier des scores
        //MessageBox(0,"Couldn't open score.txt", "Error", MB_OK );
        printf("Couldn't open score.txt");
        return ;
    }
    rewind(score);
    SDL_BlitSurface(GestionMenus->Menu, NULL, ecran, &GestionMenus->positionMenu);
    while(!feof(score)){
        fscanf(score,"%s %u\n", name, &value);
        sprintf(score_char, "%d", value);//converion int to char
        SDL_Surface *Score_surf= TTF_RenderText_Blended(police, score_char, couleurNoire);//on cr�er la structure pour le score
        SDL_Surface *Name= TTF_RenderText_Blended(police, name, couleurNoire);//idem pour le nom
        SDL_Rect positionName{413,231+numb*26.7};
        SDL_Rect positionScore{760,231+numb*26.7};
        numb++;
        SDL_BlitSurface(Name, NULL, ecran, &positionName);
        SDL_BlitSurface(Score_surf, NULL, ecran, &positionScore);
        printf("Player: %s make score: %d\n",name,value);
        SDL_FreeSurface(Score_surf);
        SDL_FreeSurface(Name);
    }
    fclose(score);
}
