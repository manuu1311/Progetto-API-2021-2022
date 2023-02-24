#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int str_length;
int arr_length=0;
char **str_arr=NULL;
int heap=0;
int sorted=0;


typedef struct info{
    char ch;
    int occ;
    int *index;
    int length;
    int num;
}maybe;


//  enter 2 strings, returns 1 if strings are equal, 0 else
int string_equal(char str1[], char str2[]){
    if (strlen(str1)!=strlen(str2)){
        return 0;
    }
    if(strcmp(str1,str2)==0){
        return 1;
    }
    else{
        return 0;
    }
}

int partition(int p, int r){
    char x[str_length+1];
    strcpy(x,str_arr[r]);
    int i=p-1;
    for(int j=p;j<=r-1;j++){
        if(strcmp(str_arr[j],x)<=0){
            i++;
            char tmp[str_length+1];
            strcpy(tmp,str_arr[i]);
            strcpy(str_arr[i],str_arr[j]);
            strcpy(str_arr[j],tmp);
        }
    }
    char tmp[str_length+1];
    strcpy(tmp,str_arr[i+1]);
    strcpy(str_arr[i+1],str_arr[r]);
    strcpy(str_arr[r],tmp);
    return i+1;
}

void quicksort(int p, int r){
    if(p<r){
        int q=partition(p,r);
        quicksort(p,q-1);
        quicksort(q+1,r);
    }
}


//  dynamic insertion of new strings until "+inesrisci_fine"
void new_string(){
    sorted=0;
    int greater;
    if(scanf("%d", &str_length));
    if(str_length<=19){
        greater=20;        
    }
    else{
        greater=str_length+1;
    }
    char *tmp=malloc(greater*sizeof(char));
    if(scanf("%s",tmp));
    while(strcmp(tmp,"+inserisci_fine")!=0){
        arr_length++;
        if(arr_length>heap){
            heap=arr_length*2;
            str_arr=realloc(str_arr,heap*sizeof(char*));
        }
        str_arr[arr_length-1]=malloc(str_length*sizeof(char)+1);
        strncpy(str_arr[arr_length-1],tmp,str_length+1);
        if(scanf("%s",tmp));
    }
    free(tmp);
}


//prints all strings from str_arr
void arr_printer(){
    for(int i=0;i<arr_length;i++){
        printf("%s\n",str_arr[i]);
    }
}

//free memory from str_arr
void str_free(){
    for(int i=0;i<arr_length;i++){
        free(str_arr[i]);
    }
    free(str_arr);
}

void can_be_print(maybe *can_be,int *can_size){
    for(int i=1;i<*can_size;i++){
        printf("%c, occ: %d, length: %d, indexes: ",can_be[i].ch,can_be[i].occ,can_be[i].length);
        for(int j=0;j<can_be[i].length;j++){
            printf("%d ",can_be[i].index[j]);
        }
        printf("\n");
    }
}

char *str_popper(char str1[str_length], char c){
    int j=0;
    char *tmp=malloc(str_length*sizeof(char));
    for(int i=0;i<str_length;i++){
        if(str1[i]!=c){
            tmp[j]=str1[i];
            j++;
        }
    }
    return tmp;
}

void stampa_filtrate(char must_be[str_length+1],char must_not_be[65], maybe *can_be, int *can_size, int val){
    if(val==1 && sorted==0){
        quicksort(0,arr_length-1);
        sorted=1;
    }
    char tmp[str_length+1];
    int num=0;
    for(int i=0;i<arr_length;i++){
        strcpy(tmp,str_arr[i]);
        int check=0;
        for(int j=0;j<str_length;j++){
            if(must_be[j]!='@'){
                if(must_be[j]==tmp[j]){
                    tmp[j]-=46;
                }
                else{
                    check=1;
                    break;
                }
            }
        }
        if(check==1){
            continue;
        }
        for(int k=1;k<*can_size;k++){
            char ch=can_be[k].ch;
            int occ=can_be[k].occ;
            int real_occ=0;
            if(occ>0){
                int redo=0;
                    for(int j=0;j<str_length;j++){
                        if(ch-46==tmp[j]){
                            real_occ++;
                            //tmp[j]='%';
                            if(real_occ==occ){
                            redo=1;
                            break;
                            }
                        }
                    }
                if(redo==0){
                    for(int j=0;j<str_length;j++){
                        if(tmp[j]==ch){
                            real_occ++;
                            tmp[j]='%';
                            if(real_occ==occ){
                                break;
                            }
                        } 
                    }
                }
            }
    
            if(real_occ<occ){
                check=1;
                break;
            }
            for(int t=0;t<can_be[k].length;t++){
                if(str_arr[i][can_be[k].index[t]]==ch){
                check=1;
                break;
                }
            }
        if(check==1){
            break;
        }
    }
    if(check==1){
        continue;
    }
        for(int j=0;j<str_length;j++){
            for(int p=0;p<65;p++){
                if(tmp[j]==must_not_be[p]){
                    check=1;
                    break;
                }
            }
            if(check==1){
                break;
            }
        }
    if(check==1){
        continue;
    }
        if(val==1){
            printf("%s\n",str_arr[i]);
        }
        else{
            num++;
        }
    }
    if(val==0){
        printf("%d\n",num);
    }
}




void must_be_init(char must_be[str_length+1]){
    for(int i=0;i<str_length;i++){
        must_be[i]='@';
    }
    must_be[str_length]='\0';
}


void must_not_be_make(char must_not_be[65],char c){
    if((int) c==45){
        must_not_be[63]=c;
    }
    else if((int)c<58){
        must_not_be[(int)c-48]=c;
    }
    else if((int)c<91){
        must_not_be[(int)c-55]=c;
    }
    else if((int)c==95){
        must_not_be[62]=c;
    }
    else{
        must_not_be[(int)c-61]=c;
    }
}

void must_not_be_init(char must_not_be[65]){
    for(int i=0;i<64;i++){
        must_not_be[i]='@';
    }
    must_not_be[64]='\0';
}

void(can_be_init(maybe **might_be,int *can_size)){
    maybe *can_be=*might_be;
    for(int i=1;i<*can_size;i++){
        can_be[i].num=0;
    }
    *might_be=can_be;
}

void can_be_add(maybe **might_be,char crct,int *can_size,int index){
    maybe *can_be=*might_be;
    *can_size+=1;
    can_be=realloc(can_be,*can_size*sizeof(maybe));
    int size=*can_size-1;
    can_be[size].num=1;
    can_be[size].occ=1;
    can_be[size].index=malloc(sizeof(int));
    can_be[size].ch=crct;
    can_be[size].length=1;
    can_be[size].index[can_be[size].length-1]=index;
    *might_be=can_be;
}
//add bond
void can_be_make(maybe **might_be,char crct,int *can_size,int index){
    maybe *can_be=*might_be;
    int check=0;
    for(int i=1;i<*can_size;i++){
        if(can_be[i].ch==crct){
            can_be[i].num++;
            if(can_be[i].num>can_be[i].occ){
                can_be[i].occ=can_be[i].num;
            }
            can_be[i].length++;
            can_be[i].index=realloc(can_be[i].index,can_be[i].length*sizeof(int));
            can_be[i].index[can_be[i].length-1]=index;
            check=1;
            break;      
        }
    }
    if(check==0){
        can_be_add(&can_be,crct,can_size,index);
    }
    *might_be=can_be;
}

void can_be_new(maybe **might_be,char crct, int *can_size){
    maybe *can_be=*might_be;
    *can_size+=1;
    can_be=realloc(can_be,*can_size*sizeof(maybe));
    int size=*can_size-1;
    can_be[size].num=1;
    can_be[size].occ=1;
    can_be[size].ch=crct;
    can_be[size].length=0;
    can_be[size].index=malloc(sizeof(int));
    *might_be=can_be;
}

void can_be_adder(maybe **might_be,char crct, int *can_size){
    maybe *can_be=*might_be;
    int check=0;
    for(int i=1;i<*can_size;i++){
        if(can_be[i].ch==crct){
            can_be[i].num++;
            if(can_be[i].num>can_be[i].occ){
                can_be[i].occ=can_be[i].num;
            }
            check=1;
            break;
        }
    }
    if(check==0){
        can_be_new(&can_be,crct,can_size);
    }
    *might_be=can_be;
}


void can_be_not_new(maybe **might_be,char crct, int *can_size,int index){
    maybe *can_be=*might_be;
    *can_size+=1;
    can_be=realloc(can_be,*can_size*sizeof(maybe));
    int size=*can_size-1;
    can_be[size].num=0;
    can_be[size].occ=0;
    can_be[size].ch=crct;
    can_be[size].length=1;
    can_be[size].index=malloc(sizeof(int));
    can_be[size].index[can_be[size].length-1]=index;
    *might_be=can_be;
}


void can_be_not(maybe **might_be,char crct, int *can_size, int index){
    maybe *can_be=*might_be;
    int check=0;
    for(int i=1;i<*can_size;i++){
        if(can_be[i].ch==crct){
            can_be[i].length++;
            can_be[i].index=realloc(can_be[i].index, can_be[i].length*sizeof(int));
            can_be[i].index[can_be[i].length-1]=index;
            check=1;
            break;
        }
    }
    if(check==0){
        can_be_not_new(&can_be,crct,can_size,index);
    }
    *might_be=can_be;
}


//   compares 2 strings, returns string res, where res[i]='+' if str1[i]=str2[i], 
//   res[i]='|' if str2[i]=str1[j],j!=i, res[i]='/' if str[2]!=str1[j]
//   modifies str2, leaving only indexes where res[i]=|
char *string_compare(char str1[str_length+1],char str2[str_length+1],char must_be[str_length+1],char must_not_be[65],maybe **might_be,int *can_size){
    maybe *can_be=*might_be;
    can_be_init(&can_be,can_size);
    char *res;
    res=malloc((str_length+1)*sizeof(char));
    for(int i=0;i<str_length;i++){
        if(str1[i]==str2[i]){
            can_be_adder(&can_be,str2[i],can_size);
            must_be[i]=str2[i];
            str1[i]='*';
            str2[i]='+';
            res[i]='+';
        }
    }
    int not_found=0;

    for(int i=0;i<str_length;i++){
        for(int j=0;j<str_length;j++){
            if(str2[i]=='+'){
                not_found=1;
                //can_be_print(can_be,can_size);
                break;
            }
            if(str2[i]==str1[j]){
                can_be_make(&can_be,str2[i],can_size,i);
                //can_be_print(can_be,can_size);
                res[i]='|';
                str2[i]='|';
                str1[j]='|';
                not_found=1;
                break;
            }
        }
        if(not_found==0){
            must_not_be_make(must_not_be,str2[i]);
            can_be_not(&can_be,str2[i],can_size,i);
            res[i]='/';
            str2[i]='/';
        }
        not_found=0;
    }
    *might_be=can_be;
    res[str_length]='\0';
    return res;
}

void can_be_free(maybe *can_be,int can_size){
    for(int i=1;i<can_size;i++){
        free(can_be[i].index);
    }
    free(can_be);
}

void can_be_equalizer(maybe **can_be, int *can_size){
    maybe *might_be=*can_be;
    for(int i=1;i<*can_size;i++){
        might_be[i].num=0;
    }
    *can_be=might_be;
}

void can_be_prova(maybe **can_be,int *can_size){
    maybe *might_be=*can_be;
    printf("Num:\n");
    for(int i=1;i<*can_size;i++){
        printf("%d\n",might_be[i].num);
    }
    printf("Fine num\n");
}

//event:nuova_partita
void nuova_partita(){
    int found=0;
    int k;
    char *result=malloc((str_length+1)*sizeof(char));
    char c[str_length+1];
    char comparer[str_length+1];
    if(scanf("%s",comparer));
    if(scanf("%d",&k));
    char must_be[str_length+1];
    char must_not_be[65];
    maybe *can_be=NULL;
    int can_size=1;
    can_be=realloc(can_be,can_size*sizeof(maybe));
    can_be[0].ch='#';
    must_not_be_init(must_not_be);
    must_be_init(must_be);
    char tmp[str_length+1];
    int i=0;
    while(i<k){
        if(scanf("%s",c));
        if(strcmp(c,"+stampa_filtrate")==0){
            stampa_filtrate(must_be,must_not_be,can_be,&can_size,1);
        }
        else if(strcmp(c,"+inserisci_inizio")==0){
            new_string();
        }     
        else{
            found=0;
            int check=0;
            for(int l=0;l<arr_length;l++){
                if(strcmp(c,str_arr[l])==0){
                    check=1;
                    break;
                }
            }
            if(check==0){
                printf("not_exists\n");
            }
            if(check==1){
                strcpy(tmp,comparer);
                //can_be_equalizer(&can_be,&can_size);
                result=string_compare(tmp,c,must_be,must_not_be,&can_be,&can_size);
                for(int m=0;m<str_length;m++){
                    if(result[m]!='+'){
                        found=1;
                        break;
                    }
                }
                if(found==0){
                    printf("ok\n");
                    break;
                }
                printf("%s\n",result);
                stampa_filtrate(must_be,must_not_be,can_be,&can_size,0);
                free(result);
                i++;
            }
        }
    }
    if(found==1){
        printf("ko\n");
    }
    else{
        free(result);
    }
    can_be_free(can_be,can_size);
}

int main(){
    if(scanf("%d", &str_length));
    char tmp[str_length+1];
    while(1){
        if(scanf("%s",tmp)==-1){
            return 0;
        }
        if(strcmp(tmp,"+nuova_partita")==0){
            nuova_partita();
        }
        else if(strcmp(tmp,"+inserisci_inizio")==0){
            new_string();
        }
        else{
            arr_length++;
            if(arr_length>=heap){
                heap=arr_length*2;
                str_arr=realloc(str_arr,heap*sizeof(char*));
            }
            str_arr[arr_length-1]=malloc((str_length+1)*sizeof(char)+1);
            strcpy(str_arr[arr_length-1],tmp);
        }
                
    }
    return 0;

}

