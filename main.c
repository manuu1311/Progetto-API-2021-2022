#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int str_length;
int arr_length=0;
char **str_arr=NULL;
int heap=0;
int sorted=0;


void max_heapify(int *a,int i,int heapsize){
    int max;
    int l=i*2;
    int r=(i*2)+1;
    if((l<=heapsize) && (strcmp(str_arr[a[l]],str_arr[a[i]])>0)){
        max=l;
    }
    else{
        max=i;
    }
    if((r<=heapsize) && strcmp(str_arr[a[r]],str_arr[a[max]])>0){
        max=r;
    }
    if(max!=i){
        int tmp=a[i];
        a[i]=a[max];
        a[max]=tmp;
        max_heapify(a,max,heapsize);
    }
}

void build_max_heap(int *a,int heapsize,int length){
    heapsize=length;
    for(int i=length/2;i>=0;i--){
        max_heapify(a,i,heapsize);
    }
}

void heapsort(int *a,int length){
    int heapsize=length;
    build_max_heap(a,heapsize,length);
    for(int i=length;i>=1;i--){
        int tmp=a[i];
        a[i]=a[0];
        a[0]=tmp;
        heapsize--;
        max_heapify(a,0,heapsize);        
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

void new_string(){
    sorted=0;
    char *tmp=malloc((str_length+1)*sizeof(char));
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

void new_filter(char **result,char **strings,int len,int val){
    int num=0;
    int skip=0;
    char str[str_length+1];
    char str2[str_length+1];
    int *indexes=NULL;
    int ind_len=0;


    for(int i=0;i<arr_length;i++){
        skip=0;
        for(int l=0;l<len;l++){
            strcpy(str,strings[l]);
            strcpy(str2,str_arr[i]);
            for(int j=0;j<str_length;j++){
                if(result[l][j]=='+'){
                    if(str[j]==str2[j]){
                        str2[j]='#';
                    }
                    else{
                        skip=1;
                        break;
                    }
                }
            }
            if(skip==1){
                break;
            }
            for(int j=0;j<str_length;j++){
                if(result[l][j]=='|'){
                    if(str[j]==str2[j]){
                        skip=1;
                        break;
                    }
                    int check=0;
                    for(int p=0;p<str_length;p++){
                        if((str[j]==str2[p]) && str[p]!=str2[p]){
                            str2[p]='#';
                            check=1;
                            break;
                        }
                    }
                    if(check==0){
                        skip=1;
                        break;
                    }

                }
            }
            if(skip==1){
                break;
            }
            for(int j=0;j<str_length;j++){
                if(result[l][j]=='/'){
                    for(int p=0;p<str_length;p++){
                        if(str[j]==str2[p]){
                            skip=1;
                            break;
                        }
                    }
                }
                if(skip==1){
                    break;
                }
            }
            if(skip==1){
                break;
            }
        }
        if(skip==0){
            if(val==1){
                ind_len++;
                indexes=realloc(indexes,ind_len*sizeof(int));
                indexes[ind_len-1]=i;
            }
            else{
                num++;
            }
            
        }
    }
    if(val==0){
        printf("%d\n",num);
    }
    else{
        heapsort(indexes,ind_len-1);
        for(int k=0;k<ind_len;k++){
            printf("%s\n",str_arr[indexes[k]]);
        }
        free(indexes);
    }
    
}



int filter(char result[str_length+1],char str[str_length+1],char str2[str_length+1]){
    for(int j=0;j<str_length;j++){
        if(result[j]=='+'){
            if(str[j]==str2[j]){
                str2[j]='#';
            }
            else{
                return 0;
            }
        }
    }
    for(int j=0;j<str_length;j++){
        if(result[j]=='|'){
            if(str[j]==str2[j]){
                return 0;
            }
            int check=0;
            for(int p=0;p<str_length;p++){
                if((str[j]==str2[p]) && str[p]!=str2[p]){
                    str2[p]='#';
                    check=1;
                    break;
                }
            }
            if(check==0){
                return 0;
            }

        }
    }
    for(int j=0;j<str_length;j++){
        if(result[j]=='/'){
            for(int p=0;p<str_length;p++){
                if(str[j]==str2[p]){
                    return 0;
                }
            }
        }
    }
    return 1;
}


int string_compare(char str1[str_length+1],char str2[str_length+1],char result[str_length+1]){
    int num=0;
    for(int i=0;i<str_length;i++){
        if(str1[i]==str2[i]){
            str1[i]='*';
            str2[i]='+';
            result[i]='+';
        }
    }
    int not_found=0;

    for(int i=0;i<str_length;i++){
        for(int j=0;j<str_length;j++){
            if(str2[i]=='+'){
                not_found=1;
                break;
            }
            if(str2[i]==str1[j]){
                result[i]='|';
                str2[i]='|';
                str1[j]='|';
                num=-1;
                not_found=1;
                break;
            }
        }
        if(not_found==0){
            result[i]='/';
            str2[i]='/';
            num=-1;
        }
        not_found=0;
    }
    return num;
}

void arr_free(char **str,int length){
    for(int i=0;i<length;i++){
        free(str[i]);
    }
    free(str);
}


void nuova_partita(){
    int size=0;
    char **res_arr=NULL;
    char **strings=NULL;
    int found=1;
    int k;
    char result[str_length+1];
    result[str_length]='\0';
    char c[str_length+1];
    char comparer[str_length+1];
    char tmp[str_length+1];
    int i=0;
    char f_str[str_length+1];
    if(scanf("%s",comparer));
    if(scanf("%d",&k));
    while(i<k){
        if(scanf("%s",c));
        if(strcmp(c,"+stampa_filtrate")==0){
            if(sorted==0){
                sorted=1;
            }
            
            new_filter(res_arr,strings,size,1);
        }
        else if(strcmp(c,"+inserisci_inizio")==0){
            new_string();
        }     
        else{
            found=1;
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
                strcpy(f_str,c);
                if(string_compare(tmp,c,result)==0){
                    printf("ok\n");
                    found=0;
                    break;
                }
                size++;
                strings=realloc(strings,size*sizeof(char*));
                res_arr=realloc(res_arr,size*sizeof(char*));
                printf("%s\n",result);
                strings[size-1]=malloc(str_length+1);
                res_arr[size-1]=malloc(str_length+1);
                strcpy(res_arr[size-1],result);
                strcpy(strings[size-1],f_str);
                new_filter(res_arr,strings,size,0);
                i++;
            }
        }
    }
    if(found==1){
        printf("ko\n");
    }
    arr_free(res_arr,size);
    arr_free(strings,size);
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
