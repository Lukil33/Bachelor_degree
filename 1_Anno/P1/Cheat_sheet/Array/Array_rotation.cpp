void rotate_array(char word[], int key);

void rotate_array(char word[], int key){
    key=key%strlen(word);
    for(int g=0; g<key; g++){//ripete il ciclo k volte
        int temp;

        for(int i=0; i<strlen(word); i++){//versione che ruota di uno a sinistra
            if(i == 0){
                temp=word[i];
                word[i]=word[i+1];
            }else if(i == strlen(word)-1){
                word[i]=temp;
            }else{
                word[i]=word[i+1];
            }
        }

        for(int i=strlen(word)-1; i>=0; i--){//versione che ruota di uno a destra
            if(i == 0){
                word[i]=temp;
            }else if(i == strlen(word)-1){
                temp=word[i];
                word[i]=word[i-1];
            }else{
                word[i]=word[i-1];
            }
        }
    }
}