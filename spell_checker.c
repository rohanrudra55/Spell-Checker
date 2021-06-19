#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TOTAL 194433 //Total number of words in the file

char *words[TOTAL];
int slno[26];
static int turn=0;

void load_dictionary();
void input();
void search(char *letter,int length);
void display(char* word_to_display,int size_of_word);

int main(){
    load_dictionary();
    printf("Enter any sentence which ends with a '.' and send '<' to exit\nNOTE: IT'S STILL UNDER MODIFICATIONS SO IT'S CAPABILITIES ARE LIMITED\n");
    input();    
    return 0;
}
void input(){
    printf(">>>");
	char* sentence=(char*)calloc(10,sizeof(char));
	int position=0,start=-1;
	while(1){
		if(position>10) //Reallocating if the size exceds
			sentence=realloc(sentence,1*sizeof(char));
		scanf("%c",&sentence[position]);
        if(sentence[position]=='<')
			exit(0);
		if(sentence[position]==' ' && sentence[position-1]==' ') // Skipping the excess spaces
			continue;
		if(sentence[position]==' '||sentence[position]=='.'){ // words extracting.
            // if(sentence[start+1]>64&&sentence[start+1]<91 || sentence[start+1]>96 && sentence[start+1]<123)
            if(sentence[start+1]>96 && sentence[start+1]<123){
			    search(&sentence[start+1],(position-start)); //Passing the word
            }
            start=position;
		}
		if(sentence[position]=='.')
			break;
		position++;
	}if(turn==0)
        printf("No error found\n");

    free(sentence);

}
void search(char *letter,int length){
    int position=-1,left=0,right=26,middle=right/2;
    while(left<=right){
        position=slno[middle];
        char l=((char)(*words[position]));
        if(l==letter[0])
            break;
        else if(l>letter[0])
            right=middle-1;
        else
            left=middle+1;
        middle=(right+left)/2;
    }//Index search

    int location=position,flag=0,i=1;
    length=length-1;
    if(position!=-1 && length!=1){
        while(1){
            char* word=(words[position]);
            int compare=strncmp((letter),word,(i+1));
            if(compare==0){
                if(i+1 ==length){
                    flag=1;
                    break;
                }
                i++;
            }
            if(compare<0)
                break;
            if(position==slno[location+1])
                break;
            position++;
            }
        
        // printf("%d\n",flag);
        if(flag==0){
                if(turn ==0){
                    turn++;
                    printf("\nCheck the spelling of:\n");
                    }
                printf("\t\t\t%d) ",turn++);
                display(letter,length);
            }
    }
}
void load_dictionary(){
    FILE *dictionary;
    dictionary=fopen("english3.txt","r");
    if(dictionary==NULL){
        puts("File not found!\n");
        exit(0);
    }
    char word[80];
    int i=0,alpha=97;
    while ( fgets ( word, 80, dictionary ) != NULL ) {
        int length=strlen(word);
        char *flag=malloc(length+1);
        strcpy(flag,word);
        words[i]=flag;
        if(*flag==alpha){
            slno[alpha-97]=i;
            alpha++;
        }
        i++;
    }
    printf("File loaded\n");
    fclose ( dictionary ) ;
}
void display(char* word_to_display,int size_of_word){
    for(int i=0;i<=size_of_word;i++){
        if(word_to_display[i]!='.'&& word_to_display[i]!=' ')
            printf("%c",word_to_display[i]);
    }
    printf("\n");
}