#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define dim 20
#define dim_v 512


typedef struct stazione{
    int dist, max, v[dim_v];
    struct stazione *p,*sx,*dx;
}stazione;

/*utility functions*/

stazione* cerca_stazione(stazione*,int);

int cerca_veicolo(int[],int);

stazione* trova_penultima_tappa(stazione*,int,int);

int min_numero_tappe(stazione*,int,int);

stazione* succ(stazione*,stazione*);

stazione* min(stazione*);

int max_autonomia(int[]);

void init_array(int[]);

void copy(int[],int[]);

int aggiungi_stazioni_intermedie(stazione*,stazione*[],int,int,int);

stazione* massima_stazione_raggiungibile(stazione*[],int,int,int);

int compare(const void*, const void*);

void libera_mem(stazione*);



/*highway management functions*/

void aggiungi_auto(stazione*);

stazione* aggiungi_stazione(stazione*);

stazione* demolisci_stazione(stazione*);

void rottama_auto(stazione*);

void pianifica_percorso(stazione*);

int pianifica_percorso_dx(stazione*,stazione*,stazione*);

void pianifica_percorso_sx(stazione *a,int dest,stazione *par);



int main(){
    char input[dim];
    int s1, s2;
    stazione *a=NULL;

    while(scanf("%s",input)!=EOF){
        if(!strcmp(input,"aggiungi-stazione")){
            a=aggiungi_stazione(a);
        }else if(!strcmp(input,"aggiungi-auto")){
           aggiungi_auto(a);
        }else if(!strcmp(input,"rottama-auto")){
            rottama_auto(a);
        }else if(!strcmp(input,"demolisci-stazione")){
            a=demolisci_stazione(a);
        }else if(!strcmp(input,"pianifica-percorso")){
            pianifica_percorso(a);
        }
    }

    libera_mem(a);
}

stazione* aggiungi_stazione(stazione *a){
    int dist, num,i, aut,j;
    stazione *pos=NULL, *n=NULL;
    scanf("%d %d",&dist,&num);
    pos=cerca_stazione(a,dist);
    if(pos==NULL || pos->dist!=dist){
        n=malloc(sizeof(stazione));
        if(n){
            n->dist=dist;
            n->max=-1;
            n->sx=NULL;
            n->dx=NULL;
            n->p=NULL;
            init_array(n->v);

            for(i=0;i<num;i++){
                scanf("%d",&aut);
                n->v[i]=aut;
                if(aut>n->max)
                    n->max=aut;      
            }
            
            if(pos!=NULL){
                n->p=pos;
                if(pos->dist>n->dist)
                    pos->sx=n;
                else
                    pos->dx=n;
            }else
                a=n;
            
            printf("aggiunta\n");
        }else
            printf("errore di memoria durante l'aggiunta della stazione\n");
    }else{
        for(i=0;i<num;i++){
            scanf("%d",&aut);
        }
        printf("non aggiunta\n");
    }
    return a;
}

void pianifica_percorso(stazione *a){
    int s1,s2;
    stazione *partenza=NULL,*destinazione=NULL;
    scanf("%d %d",&s1, &s2);
    if(s1==s2){
      printf("%d\n",s1);  
    }else{
        partenza=cerca_stazione(a,s1);
        if(s1<s2){
            destinazione=cerca_stazione(a,s2);
            if(pianifica_percorso_dx(destinazione,partenza,a)==1){
                printf("%d\n",destinazione->dist);
            }else
               printf("nessun percorso\n"); 
        }else if(partenza->dist-partenza->max<=s2){
            printf("%d %d\n",s1,s2);
        }else{
           pianifica_percorso_sx(a,s2,partenza); 
        }
    }   
    
}



//funzione ricorsiva, per la costruzione del percorso dalla stazione più vicina a quella più lontana
int pianifica_percorso_dx(stazione *dest,stazione *par,stazione *a){
    stazione *rif=NULL;
    if((par->max+par->dist)>=dest->dist){
        printf("%d ",par->dist);
        return 1;
    }
    rif=trova_penultima_tappa(a,dest->dist,par->dist);
    if(rif!=NULL&&pianifica_percorso_dx(rif,par,a)==1){
        printf("%d ",rif->dist);
        return 1;
    }
    return 0;
}

//ritorna la tappa pià vicina ad inizio autostrada in grado di raggiungere direttamente la destinazione corrente
stazione* trova_penultima_tappa(stazione *a,int dest,int par){
    stazione *min=NULL;
    if(a){
        if(a->dist<dest&&a->dist>par&&a->max>=0&&(a->dist+a->max)>=dest){ //ricerca della minima stazione che possa raggiungere la destinazione
            min=trova_penultima_tappa(a->sx,dest,par);
            if(min==NULL)
            min=a;
        }else if(a->dist<=par){   //ricerca nell'albero dell'intervallo delle stazioni percorribili 
            min=trova_penultima_tappa(a->dx,dest,par);
        }else if(a->dist>=dest){
            min=trova_penultima_tappa(a->sx,dest,par);
        }else{
            min=trova_penultima_tappa(a->sx,dest,par);
            if(min==NULL)
            min=trova_penultima_tappa(a->dx,dest,par);
        }
    }
    return min;
}


//ritorna il numero minimo di tappe da percorrere per raggiungere la destinazione
int min_numero_tappe(stazione *a,int par ,int dest){
    if(a){
        if(a->dist>dest&&a->dist<par){
            if(a->max>0)//se è una tappa utile,dal quale ti puoi muovere
                return 1+min_numero_tappe(a->dx,par,dest)+min_numero_tappe(a->sx,par,dest);
            else
                return min_numero_tappe(a->dx,par,dest)+min_numero_tappe(a->sx,par,dest);
        }else if(a->dist<=dest)
            return min_numero_tappe(a->dx,par,dest);
        else if(a->dist>=par)
            return min_numero_tappe(a->sx,par,dest);
    }
    return 0;
}

//par>>dest
void pianifica_percorso_sx(stazione *a,int dest,stazione *par){

    int size=min_numero_tappe(a,par->dist,dest),i,fine,i_max=0;

    stazione *percorso[size],*max,*max_destination,*cur_par,*cur_max_destination;

    //inizializzazione a NULL
    for(i=0;i<size;i++)  
        percorso[i]=NULL;

    aggiungi_stazioni_intermedie(a,percorso,par->dist,dest,0);//int che indica la posizione libera
    qsort(percorso,size,sizeof(stazione*),compare);
    i=0;
    fine=0;
    cur_par=par;//current start
    cur_max_destination=NULL;
    max=NULL;//currennt best choice
    max_destination=NULL;
    while(i<size&&fine>=0){
        if(fine==0){
            if(cur_par->dist-cur_par->max<=percorso[i]->dist){//stazione raggiungibile
                if(max==NULL){
                    max=percorso[i];
                    i_max=i;
                }else if((max->dist-max->max)>=(percorso[i]->dist-percorso[i]->max)){
                    percorso[i_max]=NULL;
                    i_max=i;
                    max=percorso[i];
                    max_destination=NULL;
                }else if(percorso[i]->dist-percorso[i]->max<=dest){
                    max=percorso[i];
                    percorso[i_max]=NULL;
                    i_max=i;
                }else{  //caso in cui il max corrente può si raggiungere distanze maggiori, ma bisogna verificare se questo è davvero necessario così da scegliere tappe più "vicine"
                    cur_max_destination=massima_stazione_raggiungibile(percorso,percorso[i]->dist-percorso[i]->max,size,i+1); //prendo la massima stazione raggiungibile (minima), dalla tappa corrente
                    if(cur_max_destination!=NULL){
                        if(max_destination==NULL)
                            max_destination=massima_stazione_raggiungibile(percorso,max->dist-max->max,size,i_max+1); //faccio lo stesso con il max corrente
                        if((max_destination==NULL) || (max_destination->dist>=cur_max_destination->dist)){ //se la stazione corrente raggiunge le stesse di max, sostituisco
                            max=percorso[i];
                            percorso[i_max]=NULL;
                            i_max=i;
                            max_destination=cur_max_destination;
                        }else  //altrimenti scarto la tappa
                        percorso[i]=NULL;
                    }else //altrimenti scarto la tappa
                    percorso[i]=NULL;
                }
                i++;
            }else if(max!=NULL){ //sostituisco la partenza corrente con il max
                cur_par=max;
                max=NULL;
                max_destination=NULL;
            }else  //non si può raggiungere nessuna stazione dalla partenza, non esiste alcun percorso
            fine=-1;
        }

        if(fine>=0&&cur_par->dist-cur_par->max<=dest){ //verifica che la partenza corrente possa raggiungere direttamente la destinazione
            if(fine==0)
            fine=1;
            percorso[i]=NULL;
            i++;
        }
    }

    if((fine==-1) || (max!=NULL&&max->dist<cur_par->dist&&max->dist-max->max>dest)){
        printf("nessun percorso\n");
    }else{
        i=0;
        printf("%d ",par->dist); //stampa del percorso finale
        while(i<size){
            if(percorso[i]!=NULL)
            printf("%d ",percorso[i]->dist);
            i++;
        }
        printf("%d\n",dest);
    }


}


//data un array di stazioni, ritorna la stazione raggiungibile più vicina ad inizio autostrada
stazione* massima_stazione_raggiungibile(stazione *p[],int dist,int size,int i){
    stazione *min=NULL;
    while(i<size&&dist<=p[i]->dist){
        min=p[i];
        i++;
    }
    return min;
}


//in maniera ricorsiva, popola l'array con le sole stazione che si trovano tra partenza e destinazione
int aggiungi_stazioni_intermedie(stazione *a,stazione *p[],int par,int dest,int i){

    if(a){
        if(a->dist>dest&&a->dist<par){
            if(a->max>0){
            if(p[i]==NULL){
            p[i]=a;
            i=i+1;
            }else{
                while(p[i]!=NULL)
                i=i+1;
                p[i]=a;
                i=i+1;
            }}
            aggiungi_stazioni_intermedie(a->sx,p,par,dest,i);
            aggiungi_stazioni_intermedie(a->dx,p,par,dest,i);
        }else if(a->dist>=par)
        aggiungi_stazioni_intermedie(a->sx,p,par,dest,i);
        else  if(a->dist<=dest)
        aggiungi_stazioni_intermedie(a->dx,p,par,dest,i);
    }
    return i;
}


void aggiungi_auto(stazione *a){
    int dist, aut, i;
    stazione *s=NULL;

    scanf("%d %d",&dist,&aut);
    
    s=cerca_stazione(a,dist);
    if(s!=NULL&&s->dist==dist){//se la stazione esiste
        i=0;
        while(s->v[i]!=-1)
            i++;
        s->v[i]=aut;
        if(aut>s->max)
            s->max=aut;
        printf("aggiunta\n");
    }else
        printf("non aggiunta\n");
}

void rottama_auto(stazione *a){
    stazione *s=NULL;
    int canc,j;
    int dist, aut;

    scanf("%d %d",&dist,&aut);
    
    s=cerca_stazione(a,dist);
    if(s&&s->dist==dist){
        canc=cerca_veicolo(s->v,aut);
        if(canc>=0){
            s->v[canc]=-1;
            if(aut==s->max)
                s->max=max_autonomia(s->v);
            printf("rottamata\n");
        }else
            printf("non rottamata\n");
    }else
        printf("non rottamata\n");
}

//ritorna il riferimento della stazione se esiste,altrimenti l'eventuale stazione padre
stazione* cerca_stazione(stazione* a, int dist) {
    stazione* pre = NULL;
    stazione* cur = a;

    while (cur != NULL && cur->dist != dist) {
        pre = cur;
        if (cur->dist > dist)
            cur = cur->sx;
        else if (cur->dist < dist)
            cur = cur->dx;
    }

    if (cur != NULL)
        pre = cur;

    return pre;
}



stazione* demolisci_stazione(stazione *a){
    int dist,j;
    stazione *pos=NULL,*succ=NULL;
    scanf("%d",&dist);
    
    pos=cerca_stazione(a,dist);
    if(pos!=NULL&&pos->dist==dist){
        if(pos->sx==NULL&&pos->dx==NULL){

            if(pos->p==NULL)
                a=NULL;
            else if(pos->p->dist>pos->dist)
                pos->p->sx=NULL;
            else
                pos->p->dx=NULL;

            free(pos);

        }else if(pos->dx!=NULL&&pos->sx==NULL){

            if(pos->p==NULL){
                a=pos->dx;
                a->p=NULL;
            }else{

                if(pos->p->dist>pos->dist)
                    pos->p->sx=pos->dx;
                else
                    pos->p->dx=pos->dx;

                pos->dx->p=pos->p;
            }

            free(pos);
        }else if(pos->dx==NULL&&pos->sx!=NULL){

            if(pos->p==NULL){
                a=pos->sx;
                a->p=NULL;
            }else{
                if(pos->p->dist>pos->dist)
                    pos->p->sx=pos->sx;
                else
                    pos->p->dx=pos->sx;
                pos->sx->p=pos->p;
            }
            free(pos);
        }else{//caso nodo da cnacellare ha due figli
            succ=min(pos->dx);//sostituzione del nodo
            if(succ->p==pos){
            pos->dx=succ->dx;//al piu ha il figlio dx poiche è min
            if(succ->dx)
            succ->dx->p=pos;
            }else{
            succ->p->sx=succ->dx;
            if(succ->dx)
            succ->dx->p=succ->p;
            }
           // printf(" %d",succ->p->dist);
            pos->dist=succ->dist;
            pos->max=succ->max;
            copy(pos->v,succ->v);
            free(succ);
        }
        printf("demolita\n");
    }else
    printf("non demolita\n");
    return a;
}
int cerca_veicolo(int v[],int aut){
    int i=0;
    while(i<dim_v&&v[i]!=aut){
        i++;
    }
    if(i<512)
    return i;
    return -1;
}

void copy(int d[],int p[]){
    int i=0;
    while(i<dim_v){
        d[i]=p[i];
        i++;
    }
}


void init_array(int v[]){
    int i=0;
    while(i<512){
        v[i]=-1;
        i++;
    }
}


//ritorna il successore se esiste
stazione* succ(stazione *a,stazione *n){
    stazione *suc=NULL,*cur=NULL,*pre=NULL;
    if(n->dx)
    suc=min(n->dx);
    else{
        cur=n->p;
        pre=n;
        while(cur&&pre==cur->dx){
            pre=cur;
            cur=cur->p;
        }
        suc=cur;
    }
    return suc;
}

//ritorna il minimo di un albero
stazione* min(stazione *a){
    stazione *min=NULL;
    while(a!=NULL){
        min=a;
        a=a->sx;
    }
    return min;
}

int max_autonomia(int v[]){
    int max=-1,i=0;
    while(i<512){
        if(v[i]>max)
        max=v[i];
        i++;
    }
    return max;
}



void libera_mem(stazione *a){
    if(a!=NULL){
        libera_mem(a->sx);
        libera_mem(a->dx);
        free(a);
    }
}

int compare(const void *a, const void *b) {
    const struct stazione *elem1 = *(const struct stazione **)a;
    const struct stazione *elem2 = *(const struct stazione **)b;

    if (elem1->dist < elem2->dist) {
        return 1;//ordine decrescente
    } else if (elem1->dist > elem2->dist) {
        return -1;
    }
    return 0;
}

