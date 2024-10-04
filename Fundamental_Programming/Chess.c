#include <stdio.h>
#define C_BLACK   "\e[0;30m"    // Colorized Text Code
#define C_RED     "\e[0;31m"
#define C_GREEN   "\e[0;32m"
#define C_YELLOW  "\e[0;33m"
#define C_BLUE    "\e[0;34m"
#define C_MAGENTA "\e[0;35m"
#define C_CYAN    "\e[0;36m"
#define C_WHITE   "\e[0;37m"
#define C_RESET   "\e[0m"       // Reset Colorized Text to White
#define D_BUG       0           // 1 = Enable, 0 = Disable // Debug...
#define T_START     1           // Starting Turn (Based on Odd and Even number)
#define T_ROTATE    1           // 1 = Enable, 0 = Disable // Turn Rotation...

char location[8][8],below[8][8],above[8][8],input[2],inp1,inp2,tmpselect;
int i1,i2,tmp1,tmp2,turn,gamestatus,error;
int i3,i4,itmp,stuck,stucki,K;

int debug=D_BUG;
int start=T_START;
int rotate=T_ROTATE;

// V prototype
void POSITION(),DISPLAY(),TURN(),ASK(),MOVE(),PAWN(),CASTLE(),BISHOP(),QUEEN(),KING(),HORSE(),TEAMPOSITION(),STUCK(),STUCKI(),INVALID(),XORESET(),PROMOTE(),LINE(),DEBUG(),RECORD();

FILE *fp;

void main(){            // NOT FINISH

    if ((fp=fopen("chess_history_record.dat","a"))==NULL){
         //w=rewrite whole file, a=add in the file, r=read the file, w+=read and write
         puts("File unaccessable");
    }else{fprintf(fp,"\n--------------------------------\n-----Game Start!-----\nB=Blue, O=Orange\n");
    }
    puts("Press Enter to start. Type X anytime to exit program and save record");
    getchar();
    POSITION();
    for(gamestatus=0,turn=start;gamestatus==0;turn=turn+rotate){              // IMPORTANT PART!!! // Remove "turn++" to disable turn rotation
        DISPLAY();
        TURN();
    }

}

void POSITION(){        // FINISH
    for(i1=7;i1>=0;i1--){
        for(i2=0;i2<=7;i2++){
            location[i1][i2]='.';
            below[i1][i2]='.';
            above[i1][i2]='.';
        }
    }
    for(i1=1,i2=0;i2<=7;i2++){
        location[i1][i2]='P';
    }
    for(i1=6,i2=0;i2<=7;i2++){
        location[i1][i2]='P';
    }
    location[0][0]='C'; location[0][7]='C'; // down
    location[7][0]='C'; location[7][7]='C'; // up
    location[0][1]='H'; location[0][6]='H';
    location[7][1]='H'; location[7][6]='H';
    location[0][2]='B'; location[0][5]='B';
    location[7][2]='B'; location[7][5]='B';
    location[0][3]='Q'; location[0][4]='K'; // down up
    location[7][3]='Q'; location[7][4]='K'; // down up

    for(i1=0;i1<=1;i1++){
        for(i2=0;i2<=7;i2++){
            below[i1][i2]=location[i1][i2];
        }
    }
    for(i1=6;i1<=7;i1++){
        for(i2=0;i2<=7;i2++){
            above[i1][i2]=location[i1][i2];
        }
    }
}

void DISPLAY(){         // FINISH
    if(debug!=0){
        DEBUG();
    }
    LINE();
    printf("  0-------------------------------0\n");
    for(i3=7;i3>=0;i3--){
        printf("%-2d|",i3+1);
        for(i4=0;i4<=7;i4++){
            if(below[i3][i4]=='o' && above[i3][i4]!='.'){                            // Attackable (Below's Turn)
                printf(C_RED"%2c "C_RESET,location[i3][i4]);
                printf("|");
            }
            else if(above[i3][i4]=='o' && below[i3][i4]!='.'){                       // Attackable (Above's Team)
                printf(C_RED"%2c "C_RESET,location[i3][i4]);
                printf("|");
            }
            else if(location[i3][i4]==above[i3][i4] && location[i3][i4]!='.'){       // Print Above Team (Yellow)
                printf(C_YELLOW"%2c "C_RESET,location[i3][i4]);
                printf("|");
            }
            else if(location[i3][i4]==below[i3][i4] && location[i3][i4]!='.'){       // Print Below Team (Cyan)
                printf(C_CYAN"%2c "C_RESET,location[i3][i4]);
                printf("|");
            }
            else if(location[i3][i4]=='.'){                                          // Print Blank Area (White)
                printf("%2c ",location[i3][i4]);
                printf("|");
            }
            else if(location[i3][i4]=='x'){                                          // Print Approachable Area ('x' letter)
                printf("%2c ",location[i3][i4]);
                printf("|");
            }
        }
        if(i3!=0){
            printf("\n  |");
            for(i4=0;i4<7;i4++){
                printf("---+");
            }
            printf("---|\n");
        }
        else{
            printf("\n  0-------------------------------0\n");
        }
    }
    printf("%5c%4c%4c%4c%4c%4c%4c%4c\n",'A','B','C','D','E','F','G','H');
    LINE();


    if(turn%2==1){
        puts("Blue's Turn");
    }
    if(turn%2==0){
        puts("Orange's Turn");
    }
}

void TURN(){            // FINISH
    tmp1=0; tmp2=0;                                                        // Value reset for Tmp1, Tmp2
    XORESET();
    puts("Which do you choose? ");
    ASK();
    if(error!=0 || below[i1][i2]=='.' || above[i1][i2]=='.'){
        error=0;
        if(turn%2==1 && below[i1][i2]=='.'){// Invalid Input, Error Detected
            printf("Your input position is invalid.\n");
            TURN();
            return;
        }
        if(turn%2==0 && above[i1][i2]=='.'){
            printf("Your input position is invalid.\n");
            TURN();
            return;
        }
    }
    if(turn%2==1 && error==0 && below[i1][i2]!='.'){                                              // BELOW's TURN + No Invalid Input
        tmp1=i1; tmp2=i2;                                                   // Temporary store recent position.
        MOVE();
    }
    if(turn%2==0 && error==0 && above[i1][i2]!='.'){                                              // ABOVE's TURN + No Invalid Input
        tmp1=i1; tmp2=i2;                                                   // Temporary store recent position.
        MOVE();
    }
}

void ASK(){             // FINISH
    scanf("%s",input);
    if((int)strlen(input)==2){
        inp1=input[1]; inp2=input[0];
        switch(inp1){
            case '1': i1=0; break;
            case '2': i1=1; break;
            case '3': i1=2; break;
            case '4': i1=3; break;
            case '5': i1=4; break;
            case '6': i1=5; break;
            case '7': i1=6; break;
            case '8': i1=7; break;
            default: error++; break;
        }
        switch(inp2){
            case 'a': i2=0; break;
            case 'A': i2=0; break;
            case 'b': i2=1; break;
            case 'B': i2=1; break;
            case 'c': i2=2; break;
            case 'C': i2=2; break;
            case 'd': i2=3; break;
            case 'D': i2=3; break;
            case 'e': i2=4; break;
            case 'E': i2=4; break;
            case 'f': i2=5; break;
            case 'F': i2=5; break;
            case 'g': i2=6; break;
            case 'G': i2=6; break;
            case 'h': i2=7; break;
            case 'H': i2=7; break;
            default: error++; break;
        }
    }
    else if(input[0]=='X' || input[0]=='x') abort();
    else if((int)strlen(input)!=2){
        error++;
    }
}

void MOVE(){            // NOT FINISH
    switch(location[i1][i2]){
        case 'P': tmpselect='P'; PAWN(); break;
        case 'C': tmpselect='C'; CASTLE(); break;
        case 'H': tmpselect='H'; HORSE(); break;
        case 'B': tmpselect='B'; BISHOP(); break;
        case 'Q': tmpselect='Q'; QUEEN();break;
        case 'K': tmpselect='K'; KING();break;
        default: puts("Unexpected Error"); TURN(); break;           // Less likely to happen.
    }
}

void PAWN(){            // NOT FINISH
    if(turn%2==1){
        if(above[i1+1][i2+1]=='.' && above[i1+1][i2-1]=='.' && above[i1+1][i2]!='.' || below[i1+1][i2]!='.'){
            STUCK();
        }
        else{
            if(above[i1+1][i2]=='.' && below[i1+1][i2]=='.'){
                location[i1+1][i2]='x';
                if(above[i1+2][i2]=='.' && below[i1+2][i2]=='.' && i1==1){
                    location[i1+2][i2]='x';
                }
            }
            if(above[i1+1][i2+1]!='.' || above[i1+1][i2-1]!='.'){
                if(above[i1+1][i2+1]!='.' && i2!=7){
                    below[i1+1][i2+1]='o';
                }
                if(above[i1+1][i2-1]!='.' && i2!=0){
                    below[i1+1][i2-1]='o';
                }
            }
        }
        if(stuck==0){
            DISPLAY();
            printf("[%c] To where? \n",tmpselect);
            ASK();
            while(location[i1][i2]!='x' && below[i1][i2]!='o'){
                INVALID();
            }
            if(location[i1][i2]=='x' || below[i1][i2]=='o'){
                TEAMPOSITION();
            }
        }
    }
    if(turn%2==0){
        if(below[i1-1][i2-1]=='.' && below[i1-1][i2+1]=='.' && below[i1-1][i2]!='.' || above[i1-1][i2]!='.'){
            STUCK();
        }
        else{
            if(below[i1-1][i2]=='.' && above[i1-1][i2]=='.'){
                location[i1-1][i2]='x';
                if(below[i1-2][i2]=='.' && above[i1-2][i2]=='.' && i1==6){
                    location[i1-2][i2]='x';
                }
            }
            if(below[i1-1][i2-1]!='.' || below[i1-1][i2+1]!='.'){
                if(below[i1-1][i2-1]!='.' && i2!=0){
                    above[i1-1][i2-1]='o';
                }
                if(below[i1-1][i2+1]!='.' && i2!=7){
                    above[i1-1][i2+1]='o';
                }
            }
        }
        if(stuck==0){
            DISPLAY();
            printf("[%c] To where? \n",tmpselect);
            ASK();
            while(location[i1][i2]!='x' && above[i1][i2]!='o'){
                INVALID();
            }
            if(location[i1][i2]=='x' || above[i1][i2]=='o')
                TEAMPOSITION();
        }
    }
}

void CASTLE(){
    if(turn%2==1){
        if(below[i1+1][i2]=='.' && i1<7 ||
           below[i1-1][i2]=='.' && i1>0 ||
           below[i1][i2+1]=='.' && i2<7 ||
           below[i1][i2-1]=='.' && i2>0){
            if(i1<7){
                for(i3=i1+1,itmp=0;i3<=7 && itmp==0;i3++){       // Checking Upward                           // Could Possibly have a bug. (on i3<=7)
                    if(above[i3][i2]!='.' || below[i3][i2]!='.'){
                        itmp++;
                        if(above[i3][i2]!='.'){
                            below[i3][i2]='o';
                        }
                    }
                    else if(above[i3][i2]=='.' && below[i3][i2]=='.'){
                        location[i3][i2]='x';
                    }
                }
            }
            if(i1>0){
                for(i3=i1-1,itmp=0;i3>=0 && itmp==0;i3--){      // Checking Under
                    if(above[i3][i2]!='.' || below[i3][i2]!='.'){
                        itmp++;
                        if(above[i3][i2]!='.'){
                            below[i3][i2]='o';
                        }
                    }
                    else if(above[i3][i2]=='.' && below[i3][i2]=='.'){
                        location[i3][i2]='x';
                    }
                }
            }
            if(i2<7){
                for(i3=i2+1,itmp=0;i3<=7 && itmp==0;i3++){      // Checking Right
                    if(above[i1][i3]!='.' || below[i1][i3]!='.'){
                        itmp++;
                        if(above[i1][i3]!='.'){
                            below[i1][i3]='o';
                        }
                    }
                    else if(above[i1][i3]=='.' && below[i1][i3]=='.'){
                        location[i1][i3]='x';
                    }
                }
            }
            if(i2>0){
                for(i3=i2-1,itmp=0;i3>=0 && itmp==0;i3--){      // Checking Right
                    if(above[i1][i3]!='.' || below[i1][i3]!='.'){
                        itmp++;
                        if(above[i1][i3]!='.'){
                            below[i1][i3]='o';
                        }
                    }
                    else if(above[i1][i3]=='.' && below[i1][i3]=='.'){
                        location[i1][i3]='x';
                    }
                }
            }
        }
        else{
            STUCK();
        }
        DISPLAY();
        printf("[%c] To where? \n",tmpselect);
        ASK();
        while(location[i1][i2]!='x' && below[i1][i2]!='o'){
            INVALID();
        }
        if(location[i1][i2]=='x' || below[i1][i2]=='o'){
            TEAMPOSITION();
        }
    }
    if(turn%2==0){
        if(above[i1+1][i2]=='.' && i1<7 ||
           above[i1-1][i2]=='.' && i1>0 ||
           above[i1][i2+1]=='.' && i2<7 ||
           above[i1][i2-1]=='.' && i2>0){
            if(i1<7){
                for(i3=i1+1,itmp=0;i3<=7 && itmp==0;i3++){       // Checking Upward                           // Could Possibly have a bug. (on i3<=7)
                    if(above[i3][i2]!='.' || below[i3][i2]!='.'){
                        itmp++;
                        if(below[i3][i2]!='.'){
                            above[i3][i2]='o';
                        }
                    }
                    else if(above[i3][i2]=='.' && below[i3][i2]=='.'){
                        location[i3][i2]='x';
                    }
                }
            }
            if(i1>0){
                for(i3=i1-1,itmp=0;i3>=0 && itmp==0;i3--){      // Checking Under
                    if(above[i3][i2]!='.' || below[i3][i2]!='.'){
                        itmp++;
                        if(below[i3][i2]!='.'){
                            above[i3][i2]='o';
                        }
                    }
                    else if(above[i3][i2]=='.' && below[i3][i2]=='.'){
                        location[i3][i2]='x';
                    }
                }
            }
            if(i2<7){
                for(i3=i2+1,itmp=0;i3<=7 && itmp==0;i3++){      // Checking Right
                    if(above[i1][i3]!='.' || below[i1][i3]!='.'){
                        itmp++;
                        if(below[i1][i3]!='.'){
                            above[i1][i3]='o';
                        }
                    }
                    else if(above[i1][i3]=='.' && below[i1][i3]=='.'){
                        location[i1][i3]='x';
                    }
                }
            }
            if(i2>0){
                for(i3=i2-1,itmp=0;i3>=0 && itmp==0;i3--){      // Checking Right
                    if(above[i1][i3]!='.' || below[i1][i3]!='.'){
                        itmp++;
                        if(below[i1][i3]!='.'){
                            above[i1][i3]='o';
                        }
                    }
                    else if(above[i1][i3]=='.' && below[i1][i3]=='.'){
                        location[i1][i3]='x';
                    }
                }
            }
        }
        else{
            STUCK();
        }
        DISPLAY();
        printf("[%c] To where? \n",tmpselect);
        ASK();
        while(location[i1][i2]!='x' && above[i1][i2]!='o'){
            INVALID();
        }
        if(location[i1][i2]=='x' || above[i1][i2]=='o'){
            TEAMPOSITION();
        }
    }
}

void BISHOP(){
    if(turn%2==1){
        if(below[i1-1][i2-1]=='.' || below[i1-1][i2+1]=='.' || below[i1+1][i2-1]=='.' || below[i1+1][i2+1]=='.'){
            for(i3=i1+1,i4=i2+1,itmp=0;i3<=7 && i4<=7 && itmp==0;i3++,i4++){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(above[i3][i4]!='.'){
                        below[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1+1,i4=i2-1,itmp=0;i3<=7 && i4>=0 && itmp==0;i3++,i4--){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(above[i3][i4]!='.'){
                        below[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1-1,i4=i2+1,itmp=0;i3>=0 && i4<=7 && itmp==0;i3--,i4++){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(above[i3][i4]!='.'){
                        below[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1-1,i4=i2-1,itmp=0;i3>=0 && i4>=0 && itmp==0;i3--,i4--){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(above[i3][i4]!='.'){
                        below[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
        }
        else{
            STUCK();
        }
        DISPLAY();
        printf("[%c] To where? \n",tmpselect);
        ASK();
        while(location[i1][i2]!='x' && below[i1][i2]!='o'){
            INVALID();
        }
        if(location[i1][i2]=='x' || below[i1][i2]=='o'){
            TEAMPOSITION();
        }
    }
    if(turn%2==0){
        if(above[i1-1][i2-1]=='.' || above[i1-1][i2+1]=='.' || above[i1+1][i2-1]=='.' || above[i1+1][i2+1]=='.'){
            for(i3=i1+1,i4=i2+1,itmp=0;i3<=7 && i4<=7 && itmp==0;i3++,i4++){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(below[i3][i4]!='.'){
                        above[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1+1,i4=i2-1,itmp=0;i3<=7 && i4>=0 && itmp==0;i3++,i4--){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(below[i3][i4]!='.'){
                        above[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1-1,i4=i2+1,itmp=0;i3>=0 && i4<=7 && itmp==0;i3--,i4++){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(below[i3][i4]!='.'){
                        above[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1-1,i4=i2-1,itmp=0;i3>=0 && i4>=0 && itmp==0;i3--,i4--){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(below[i3][i4]!='.'){
                        above[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
        }
        else{
            STUCK();
        }
        DISPLAY();
        printf("[%c] To where? \n",tmpselect);
        ASK();
        while(location[i1][i2]!='x' && above[i1][i2]!='o'){
            INVALID();
        }
        if(location[i1][i2]=='x' || above[i1][i2]=='o'){
            TEAMPOSITION();
        }
    }
}

void QUEEN(){
    if(turn%2==1){
        if(below[i1+1][i2]=='.' && i1<7 ||
           below[i1-1][i2]=='.' && i1>0 ||
           below[i1][i2+1]=='.' && i2<7 ||
           below[i1][i2-1]=='.' && i2>0 ||
           below[i1-1][i2-1]=='.' ||
           below[i1-1][i2+1]=='.' ||
           below[i1+1][i2-1]=='.' ||
           below[i1+1][i2+1]=='.'){
            if(i1<7){
                for(i3=i1+1,itmp=0;i3<=7 && itmp==0;i3++){       // Checking Upward                           // Could Possibly have a bug. (on i3<=7)
                    if(above[i3][i2]!='.' || below[i3][i2]!='.'){
                        itmp++;
                        if(above[i3][i2]!='.'){
                            below[i3][i2]='o';
                        }
                    }
                    else if(above[i3][i2]=='.' && below[i3][i2]=='.'){
                        location[i3][i2]='x';
                    }
                }
            }
            if(i1>0){
                for(i3=i1-1,itmp=0;i3>=0 && itmp==0;i3--){      // Checking Under
                    if(above[i3][i2]!='.' || below[i3][i2]!='.'){
                        itmp++;
                        if(above[i3][i2]!='.'){
                            below[i3][i2]='o';
                        }
                    }
                    else if(above[i3][i2]=='.' && below[i3][i2]=='.'){
                        location[i3][i2]='x';
                    }
                }
            }
            if(i2<7){
                for(i3=i2+1,itmp=0;i3<=7 && itmp==0;i3++){      // Checking Right
                    if(above[i1][i3]!='.' || below[i1][i3]!='.'){
                        itmp++;
                        if(above[i1][i3]!='.'){
                            below[i1][i3]='o';
                        }
                    }
                    else if(above[i1][i3]=='.' && below[i1][i3]=='.'){
                        location[i1][i3]='x';
                    }
                }
            }
            if(i2>0){
                for(i3=i2-1,itmp=0;i3>=0 && itmp==0;i3--){      // Checking Right
                    if(above[i1][i3]!='.' || below[i1][i3]!='.'){
                        itmp++;
                        if(above[i1][i3]!='.'){
                            below[i1][i3]='o';
                        }
                    }
                    else if(above[i1][i3]=='.' && below[i1][i3]=='.'){
                        location[i1][i3]='x';
                    }
                }
            }

            for(i3=i1+1,i4=i2+1,itmp=0;i3<=7 && i4<=7 && itmp==0;i3++,i4++){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(above[i3][i4]!='.'){
                        below[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1+1,i4=i2-1,itmp=0;i3<=7 && i4>=0 && itmp==0;i3++,i4--){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(above[i3][i4]!='.'){
                        below[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1-1,i4=i2+1,itmp=0;i3>=0 && i4<=7 && itmp==0;i3--,i4++){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(above[i3][i4]!='.'){
                        below[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1-1,i4=i2-1,itmp=0;i3>=0 && i4>=0 && itmp==0;i3--,i4--){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(above[i3][i4]!='.'){
                        below[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
        }
        else{
            STUCK();
        }
        DISPLAY();
        printf("[%c] To where? \n",tmpselect);
        ASK();
        while(location[i1][i2]!='x' && below[i1][i2]!='o'){
            INVALID();
        }
        if(location[i1][i2]=='x' || below[i1][i2]=='o'){
            TEAMPOSITION();
        }
    }
    if(turn%2==0){
        if(above[i1+1][i2]=='.' && i1<7 ||
           above[i1-1][i2]=='.' && i1>0 ||
           above[i1][i2+1]=='.' && i2<7 ||
           above[i1][i2-1]=='.' && i2>0 ||
           above[i1-1][i2-1]=='.' ||
           above[i1-1][i2+1]=='.' ||
           above[i1+1][i2-1]=='.' ||
           above[i1+1][i2+1]=='.'){
            if(i1<7){
                for(i3=i1+1,itmp=0;i3<=7 && itmp==0;i3++){       // Checking Upward                           // Could Possibly have a bug. (on i3<=7)
                    if(above[i3][i2]!='.' || below[i3][i2]!='.'){
                        itmp++;
                        if(below[i3][i2]!='.'){
                            above[i3][i2]='o';
                        }
                    }
                    else if(above[i3][i2]=='.' && below[i3][i2]=='.'){
                        location[i3][i2]='x';
                    }
                }
            }
            if(i1>0){
                for(i3=i1-1,itmp=0;i3>=0 && itmp==0;i3--){      // Checking Under
                    if(above[i3][i2]!='.' || below[i3][i2]!='.'){
                        itmp++;
                        if(below[i3][i2]!='.'){
                            above[i3][i2]='o';
                        }
                    }
                    else if(above[i3][i2]=='.' && below[i3][i2]=='.'){
                        location[i3][i2]='x';
                    }
                }
            }
            if(i2<7){
                for(i3=i2+1,itmp=0;i3<=7 && itmp==0;i3++){      // Checking Right
                    if(above[i1][i3]!='.' || below[i1][i3]!='.'){
                        itmp++;
                        if(below[i1][i3]!='.'){
                            above[i1][i3]='o';
                        }
                    }
                    else if(above[i1][i3]=='.' && below[i1][i3]=='.'){
                        location[i1][i3]='x';
                    }
                }
            }
            if(i2>0){
                for(i3=i2-1,itmp=0;i3>=0 && itmp==0;i3--){      // Checking Right
                    if(above[i1][i3]!='.' || below[i1][i3]!='.'){
                        itmp++;
                        if(below[i1][i3]!='.'){
                            above[i1][i3]='o';
                        }
                    }
                    else if(above[i1][i3]=='.' && below[i1][i3]=='.'){
                        location[i1][i3]='x';
                    }
                }
            }
            // from BISHOP
            for(i3=i1+1,i4=i2+1,itmp=0;i3<=7 && i4<=7 && itmp==0;i3++,i4++){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(below[i3][i4]!='.'){
                        above[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1+1,i4=i2-1,itmp=0;i3<=7 && i4>=0 && itmp==0;i3++,i4--){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(below[i3][i4]!='.'){
                        above[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1-1,i4=i2+1,itmp=0;i3>=0 && i4<=7 && itmp==0;i3--,i4++){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(below[i3][i4]!='.'){
                        above[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
            for(i3=i1-1,i4=i2-1,itmp=0;i3>=0 && i4>=0 && itmp==0;i3--,i4--){
                if(above[i3][i4]!='.' || below[i3][i4]!='.'){
                    itmp++;
                    if(below[i3][i4]!='.'){
                        above[i3][i4]='o';
                    }
                }
                    if(above[i3][i4]=='.' && below[i3][i4]=='.'){
                    location[i3][i4]='x';
                }
            }
        }
        else{
            STUCK();
        }
        DISPLAY();
        printf("[%c] To where? \n",tmpselect);
        ASK();
        while(location[i1][i2]!='x' && above[i1][i2]!='o'){
            INVALID();
        }
        if(location[i1][i2]=='x' || above[i1][i2]=='o'){
            TEAMPOSITION();
        }
    }

}

void KING(){
    if(turn%2==1){
        switch(i1){
        case 7:
            switch(i2){
                case 0://
                    if(below[i1][i2+1]!='.' && below[i1-1][i2+1]!='.' && below[i1-1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1-1,i1-1};
                        int count_i2[] = {i2+1,i2+1,i2};
                        for(int i=0;i<3;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){
                                below[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                case 7://
                    if(below[i1][i2-1]!='.' && below[i1-1][i2-1]!='.' && below[i1-1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1-1,i1-1};
                        int count_i2[] = {i2-1,i2-1,i2};
                        for(int i=0;i<3;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){
                                below[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                default:// ͺ
                    if(below[i1][i2-1]!='.' && below[i1-1][i2-1]!='.' && below[i1-1][i2]!='.' && below[i1-1][i2+1]!='.' && below[i1][i2+1]){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1-1,i1-1,i1-1,i1};
                        int count_i2[] = {i2-1,i2-1,i2,i2+1,i2+1};
                        for(int i=0;i<5;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){
                                below[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                break;
            }
            break;
        case 0:
            switch(i2){
                case 0://     ҧ
                    if(below[i1+1][i2]!='.' && below[i1+1][i2+1]!='.' && below[i1][i2+1]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1+1,i1+1,i1};
                        int count_i2[] = {i2,i2+1,i2+1};
                        for(int i=0;i<3;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){
                                below[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                case 7://     ҧ
                    if(below[i1][i2-1]!='.' && below[i1+1][i2-1]!='.' && below[i1+1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1+1,i1+1};
                        int count_i2[] = {i2-1,i2-1,i2};
                        for(int i=0;i<3;i++){
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                    }
                break;
                default:// ͺ  ҧ
                    if(below[i1][i2-1]!='.' && below[i1+1][i2-1]!='.' && below[i1+1][i2]!='.' && below[i1+1][i2+1]!='.' && below[i1][i2+1]!='.'){
                        STUCK();
                    }
                    else{
                        for(i3=i1+1;i3>=i1;i3--){
                            for(i4=i2-1;i4<=i2+1;i4++){
                                if(below[i3][i4] == '.' && above[i3][i4]== '.'){
                                    location[i3][i4] = 'x';
                                }
                                else if(below[i3][i4] != '.'){

                                }
                                else if(above[i3][i4] != '.'){
                                    below[i3][i4] = 'o';
                                }
                            }
                        }
                    }
                    break;
            break;
        }
        default:
            switch(i2){
                case 0:// ͺ
                    if(below[i1+1][i2]!='.' && below[i1+1][i2+1]!='.' && below[i1][i2+1]!='.' && below[i1-1][i2+1]!='.' && below[i1-1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1+1,i1+1,i1,i1-1,i1-1};
                        int count_i2[] = {i2,i2+1,i2+1,i2+1,i2};
                        for(int i=0;i<5;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){
                                below[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                case 7:// ͺ
                    if(below[i1+1][i2]!='.' && below[i1+1][i2-1]!='.' && below[i1][i2-1]!='.' && below[i1-1][i2-1]!='.' && below[i1-1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1+1,i1+1,i1,i1-1,i1-1};
                        int count_i2[] = {i2,i2-1,i2-1,i2-1,i2};
                        for(int i=0;i<5;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){
                                below[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                default://normal move
                    if(below[i1+1][i2-1]!='.' && below[i1][i2-1]!='.' && below[i1-1][i2-1]!='.' && below[i1-1][i2]!='.' && below[i1-1][i2+1]!='.' && below[i1][i2+1]!='.' && below[i1+1][i2+1]!='.' && below[i1+1][i2]!='.' ){
                        STUCK();
                        break;
                    }
                    else{
                        int count_i1[] = {i1+1,i1,i1-1,i1-1,i1-1,i1,i1+1,i1+1};
                        int count_i2[] = {i2-1,i2-1,i2-1,i2,i2+1,i2+1,i2+1,i2};
                        for(int i=0;i<8;i++){
                                    if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                        location[count_i1[i]][count_i2[i]] = 'x';
                                    }
                                    else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    }
                                    else if(above[count_i1[i]][count_i2[i]] != '.'){
                                        below[count_i1[i]][count_i2[i]] = 'o';
                                    }
                        }
                    }
                    break;
            }
            break;
        }
        if(stuck==0){
            DISPLAY();
            printf("[%c] To where? \n",tmpselect);
            ASK();
            while(location[i1][i2]!='x' && below[i1][i2]!='o'){
                INVALID();
            }
            if(location[i1][i2]=='x' || below[i1][i2]=='o'){
                TEAMPOSITION();
            }
        }
    }

    if(turn%2==0){
        switch(i1){
        case 7:
            switch(i2){
                case 0://
                    if(above[i1][i2+1]!='.' && above[i1-1][i2+1]!='.' && above[i1-1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1-1,i1-1};
                        int count_i2[] = {i2+1,i2+1,i2};
                        for(int i=0;i<3;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                case 7://
                    if(above[i1][i2-1]!='.' && above[i1-1][i2-1]!='.' && above[i1-1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1-1,i1-1};
                        int count_i2[] = {i2-1,i2-1,i2};
                        for(int i=0;i<3;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                default:// ͺ
                    if(above[i1][i2-1]!='.' && above[i1-1][i2-1]!='.' && above[i1-1][i2]!='.' && above[i1-1][i2+1]!='.' && above[i1][i2+1]){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1-1,i1-1,i1-1,i1};
                        int count_i2[] = {i2-1,i2-1,i2,i2+1,i2+1};
                        for(int i=0;i<5;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
            }
            break;
        case 0:
            switch(i2){
                case 0://     ҧ
                    if(above[i1+1][i2]!='.' && above[i1+1][i2+1]!='.' && above[i1][i2+1]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1+1,i1+1,i1};
                        int count_i2[] = {i2,i2+1,i2+1};
                        for(int i=0;i<3;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                case 7://     ҧ
                    if(above[i1][i2-1]!='.' && above[i1+1][i2-1]!='.' && above[i1+1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1+1,i1+1};
                        int count_i2[] = {i2-1,i2-1,i2};
                        for(int i=0;i<3;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                default:// ͺ  ҧ
                    if(above[i1][i2-1]!='.' && above[i1+1][i2-1]!='.' && above[i1+1][i2]!='.' && above[i1+1][i2+1]!='.' && above[i1][i2+1]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1,i1+1,i1+1,i1+1,i1};
                        int count_i2[] = {i2-1,i2-1,i2,i2+1,i2+1};
                        for(int i=0;i<5;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
            break;
        }
        default:
            switch(i2){
                case 0:// ͺ
                    if(above[i1+1][i2]!='.' && above[i1+1][i2+1]!='.' && above[i1][i2+1]!='.' && above[i1-1][i2+1]!='.' && above[i1-1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1+1,i1+1,i1,i1-1,i1-1};
                        int count_i2[] = {i2,i2+1,i2+1,i2+1,i2};
                        for(int i=0;i<5;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                case 7:// ͺ
                    if(above[i1+1][i2]!='.' && above[i1+1][i2-1]!='.' && above[i1][i2-1]!='.' && above[i1-1][i2-1]!='.' && above[i1-1][i2]!='.'){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1+1,i1+1,i1,i1-1,i1-1};
                        int count_i2[] = {i2,i2-1,i2-1,i2-1,i2};
                        for(int i=0;i<5;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                    break;
                default:
                    if(above[i1+1][i2-1]!='.' && above[i1][i2-1]!='.' && above[i1-1][i2-1]!='.' && above[i1-1][i2]!='.' && above[i1-1][i2+1]!='.' && above[i1][i2+1]!='.' && above[i1+1][i2+1]!='.' && above[i1+1][i2]!='.' ){
                        STUCK();
                    }
                    else{
                        int count_i1[] = {i1+1,i1,i1-1,i1-1,i1-1,i1,i1+1,i1+1};
                        int count_i2[] = {i2-1,i2-1,i2-1,i2,i2+1,i2+1,i2+1,i2};
                        for(int i=0;i<8;i++){
                            if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]]== '.'){
                                location[count_i1[i]][count_i2[i]] = 'x';
                            }
                            else if(above[count_i1[i]][count_i2[i]] != '.'){

                            }
                            else if(below[count_i1[i]][count_i2[i]] != '.'){
                                above[count_i1[i]][count_i2[i]] = 'o';
                            }
                        }
                    }
                break;

            }

        }
        if(stuck==0){
            DISPLAY();
            printf("[%c] To where? \n",tmpselect);
            ASK();
            while(location[i1][i2]!='x' && below[i1][i2]!='o'){
                INVALID();
            }
            if(location[i1][i2]=='x' || below[i1][i2]=='o'){
                TEAMPOSITION();
            }
        }
    }
}

void HORSE(){
    if(turn%2==1){
        switch(i1){
            case 7 :
                switch(i2){
                    case 0://
                        if(below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-1,i1-2};
                            int count_i2[] = {i2+2,i2+1};
                            for(int i=0;i<2;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:
                        if(below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.' && below[i1-2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-1,i1-2,i1-2};
                            int count_i2[] = {i2+2,i2+1,i2-1};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:
                        if(below[i1-2][i2+1]!='.' && below[i1-2][i2-1]!='.' && below[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-2,i1-2,i1-1};
                            int count_i2[] = {i2+1,i2-1,i2-2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7://
                        if(below[i1-2][i2-1]!='.' && below[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-2,i1-1};
                            int count_i2[] = {i2-1,i2-2};
                            for(int i=0;i<2;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default:
                        if(below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.' && below[i1-2][i2-1]!='.' && below[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-1,i1-2,i1-2,i1-1};
                            int count_i2[] = {i2+2,i2+1,i2-1,i2-2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    }
                break;
            case 6:
                switch(i2){
                    case 0:
                        if(below[i1+1][i2+2]!='.' && below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+1,i1-1,i1-2};
                            int count_i2[] = {i2+2,i2+2,i2+1};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:
                        if(below[i1+1][i2+2]!='.' && below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.' && below[i1-2][i2-1]!='.'){
                            STUCK();
                        }
                         else{
                            int count_i1[] = {i1+1,i1-1,i1-2,i1-2};
                            int count_i2[] = {i2+2,i2+2,i2+1,i2-1};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:
                        if(below[i1-2][i2+1]!='.' && below[i1-2][i2-1]!='.' && below[i1-1][i2-2]!='.' && below[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                         else{
                            int count_i1[] = {i1-2,i1-2,i1-1,i1+1};
                            int count_i2[] = {i2+1,i2-1,i2-2,i2-2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7:
                        if(below[i1-2][i2-1]!='.' && below[i1-1][i2-2]!='.' && below[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                         else{
                            int count_i1[] = {i1-2,i1-1,i1+1};
                            int count_i2[] = {i2-1,i2-2,i2-2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default:// ͺ  -1
                        if(below[i1+1][i2+2]!='.' && below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.' && below[i1-2][i2-1]!='.' && below[i1-1][i2-2]!='.' && below[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-2,i1-1,i1+1};
                            int count_i2[] = {i2-1,i2-2,i2-2};
                            for(int i=0;i<6;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                }
                break;
            case 1:
                switch(i2){
                    case 0:
                        if(below[i1+2][i2+1]!='.' && below[i1+1][i2+2]!='.' && below[i1-1][i2+2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1};
                            int count_i2[] = {i2+1,i2+2,i2+2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:
                        if(below[i1+2][i2-1]!='.' && below[i1+2][i2+1]!='.' && below[i1+1][i2+2]!='.' && below[i1-1][i2+2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1,i1-1};
                            int count_i2[] = {i2-1,i2+1,i2+2,i2+2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:
                        if(below[i1+2][i2+1]!='.' && below[i1+2][i2-1]!='.' && below[i1+1][i2-2]!='.' && below[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1,i1-1};
                            int count_i2[] = {i2+1,i2-1,i2-2,i2-2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7:
                        if(below[i1+2][i2-1]!='.' && below[i1+1][i2-2]!='.' && below[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1};
                            int count_i2[] = {i2-1,i2-2,i2-2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default:// ͺ  ҧ+1
                        if(below[i1-1][i2+2]!='.' && below[i1+1][i2+2]!='.' && below[i1+2][i2+1]!='.' && below[i1+2][i2-1]!='.' && below[i1+1][i2-2]!='.' && below[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-1,i1+1,i1+2,i1+2,i1+1,i1-1};
                            int count_i2[] = {i2+2,i2+2,i2+1,i2-1,i2-2,i2-2};
                            for(int i=0;i<6;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                }
                break;
            case 0:
                switch(i2){
                    case 0://     ҧ
                        if(below[i1+2][i2+1]!='.' && below[i1+1][i2+2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1};
                            int count_i2[] = {i2+1,i2+2};
                            for(int i=0;i<2;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:
                        if(below[i1+1][i2+2]!='.' && below[i1+2][i2+1]!='.' && below[i1+2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+1,i1+2,i1+2};
                            int count_i2[] = {i2+2,i2+1,i2-1};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:
                        if(below[i1+2][i2+1]!='.' && below[i1+2][i2-1]!='.' && below[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1};
                            int count_i2[] = {i2+1,i2-1,i2-2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7://     ҧ
                        if(below[i1+2][i2-1]!='.' && below[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1};
                            int count_i2[] = {i2-1,i2-2};
                            for(int i=0;i<2;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default:// ͺ  ҧ
                        if(below[i1+2][i2-1]!='.' && below[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+1,i1+2,i1+2,i1+1};
                            int count_i2[] = {i2+2,i2+1,i2-1,i2-2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                }
                break;
            default:
                switch(i2){
                    case 0:// ͺ
                        if(below[i1+2][i2+1]!='.' && below[i1+1][i2+2]!='.' && below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1,i1-2};
                            int count_i2[] = {i2+1,i2+2,i2+2,i2+1};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:// ͺ    +1
                        if(below[i1+2][i2-1]!='.' && below[i1+2][i2+1]!='.' && below[i1+1][i2+2]!='.' && below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.' && below[i1-2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1,i1-1,i1-2,i1-2};
                            int count_i2[] = {i2-1,i2+1,i2+2,i2+2,i2+1,i2-1};
                            for(int i=0;i<6;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:// ͺ   -1
                        if(below[i1+2][i2+1]!='.' && below[i1+2][i2-1]!='.' && below[i1+1][i2-2]!='.' && below[i1-1][i2-2]!='.' && below[i1-2][i2-1]!='.' && below[i1-2][i2+1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1,i1-1,i1-2,i1-2};
                            int count_i2[] = {i2+1,i2-1,i2-2,i2-2,i2-1,i2+1};
                            for(int i=0;i<6;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7:// ͺ
                        if(below[i1+2][i2-1]!='.' && below[i1+1][i2-2]!='.' && below[i1-1][i2-2]!='.' && below[i1-2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1,i1-2};
                            int count_i2[] = {i2-1,i2-2,i2-2,i2-1};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default://normal move
                        if(below[i1+2][i2+1]!='.' && below[i1+1][i2+2]!='.' && below[i1-1][i2+2]!='.' && below[i1-2][i2+1]!='.' && below[i1-2][i2-1]!='.' && below[i1-1][i2-2]!='.' && below[i1+1][i2-2]!='.' && below[i1+2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1,i1-2,i1-2,i1-1,i1+1,i1+2};
                            int count_i2[] = {i2+1,i2+2,i2+2,i2+1,i2-1,i2-2,i2-2,i2-1};
                            for(int i=0;i<8;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){
                                    below[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                }
                break;
        }
        if(stuck==0){
            DISPLAY();
            printf("[%c] To where? \n",tmpselect);
            ASK();
            while(location[i1][i2]!='x' && below[i1][i2]!='o'){
                INVALID();
            }
            if(location[i1][i2]=='x' || below[i1][i2]=='o'){
                TEAMPOSITION();
            }
        }
    }
    if(turn%2==0){
        switch(i1){
            case 7 :
                switch(i2){
                    case 0://
                        if(above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-1,i1-2};
                            int count_i2[] = {i2+2,i2+1};
                            for(int i=0;i<2;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:
                        if(above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.' && above[i1-2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-1,i1-2,i1-2};
                            int count_i2[] = {i2+2,i2+1,i2-1};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:
                        if(above[i1-2][i2+1]!='.' && above[i1-2][i2-1]!='.' && above[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-2,i1-2,i1-1};
                            int count_i2[] = {i2+1,i2-1,i2-2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7://
                        if(above[i1-2][i2-1]!='.' && above[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-2,i1-1};
                            int count_i2[] = {i2-1,i2-2};
                            for(int i=0;i<2;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default:// ͺ
                        if(above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.' && above[i1-2][i2-1]!='.' && above[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-1,i1-2,i1-2,i1-1};
                            int count_i2[] = {i2+2,i2+1,i2-1,i2-2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    }
                break;
            case 6:
                switch(i2){
                    case 0:
                        if(above[i1+1][i2+2]!='.' && above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+1,i1-1,i1-2};
                            int count_i2[] = {i2+2,i2+2,i2+1};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:
                        if(above[i1+1][i2+2]!='.' && above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.' && above[i1-2][i2-1]!='.'){
                            STUCK();
                        }
                         else{
                            int count_i1[] = {i1+1,i1-1,i1-2,i1-2};
                            int count_i2[] = {i2+2,i2+2,i2+1,i2-1};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:
                        if(above[i1-2][i2+1]!='.' && above[i1-2][i2-1]!='.' && above[i1-1][i2-2]!='.' && above[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                         else{
                            int count_i1[] = {i1-2,i1-2,i1-1,i1+1};
                            int count_i2[] = {i2+1,i2-1,i2-2,i2-2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7:
                        if(above[i1-2][i2-1]!='.' && above[i1-1][i2-2]!='.' && above[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                         else{
                            int count_i1[] = {i1-2,i1-1,i1+1};
                            int count_i2[] = {i2-1,i2-2,i2-2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default:// ͺ  -1
                        if(above[i1+1][i2+2]!='.' && above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.' && above[i1-2][i2-1]!='.' && above[i1-1][i2-2]!='.' && above[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-2,i1-1,i1+1};
                            int count_i2[] = {i2-1,i2-2,i2-2};
                            for(int i=0;i<6;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                }
                break;
            case 1:
                switch(i2){
                    case 0:
                        if(above[i1+2][i2+1]!='.' && above[i1+1][i2+2]!='.' && above[i1-1][i2+2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1};
                            int count_i2[] = {i2+1,i2+2,i2+2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:
                        if(above[i1+2][i2-1]!='.' && above[i1+2][i2+1]!='.' && above[i1+1][i2+2]!='.' && above[i1-1][i2+2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1,i1-1};
                            int count_i2[] = {i2-1,i2+1,i2+2,i2+2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:
                        if(above[i1+2][i2+1]!='.' && above[i1+2][i2-1]!='.' && above[i1+1][i2-2]!='.' && above[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1,i1-1};
                            int count_i2[] = {i2+1,i2-1,i2-2,i2-2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7:
                        if(above[i1+2][i2-1]!='.' && above[i1+1][i2-2]!='.' && above[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1};
                            int count_i2[] = {i2-1,i2-2,i2-2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default:// ͺ  ҧ+1
                        if(above[i1-1][i2+2]!='.' && above[i1+1][i2+2]!='.' && above[i1+2][i2+1]!='.' && above[i1+2][i2-1]!='.' && above[i1+1][i2-2]!='.' && above[i1-1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1-1,i1+1,i1+2,i1+2,i1+1,i1-1};
                            int count_i2[] = {i2+2,i2+2,i2+1,i2-1,i2-2,i2-2};
                            for(int i=0;i<6;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                }
                break;
            case 0:
                switch(i2){
                    case 0://     ҧ
                        if(below[i1+2][i2+1]!='.' && below[i1+1][i2+2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1};
                            int count_i2[] = {i2+1,i2+2};
                            for(int i=0;i<2;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:
                        if(above[i1+1][i2+2]!='.' && above[i1+2][i2+1]!='.' && above[i1+2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+1,i1+2,i1+2};
                            int count_i2[] = {i2+2,i2+1,i2-1};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:
                        if(above[i1+2][i2+1]!='.' && above[i1+2][i2-1]!='.' && above[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1};
                            int count_i2[] = {i2+1,i2-1,i2-2};
                            for(int i=0;i<3;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7://     ҧ
                        if(above[i1+2][i2-1]!='.' && above[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1};
                            int count_i2[] = {i2-1,i2-2};
                            for(int i=0;i<2;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default:// ͺ  ҧ
                        if(above[i1+2][i2-1]!='.' && above[i1+1][i2-2]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+1,i1+2,i1+2,i1+1};
                            int count_i2[] = {i2+2,i2+1,i2-1,i2-2};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                }
                break;
            default:
                switch(i2){
                    case 0:// ͺ
                        if(above[i1+2][i2+1]!='.' && above[i1+1][i2+2]!='.' && above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1,i1-2};
                            int count_i2[] = {i2+1,i2+2,i2+2,i2+1};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 1:// ͺ    +1
                        if(above[i1+2][i2-1]!='.' && above[i1+2][i2+1]!='.' && above[i1+1][i2+2]!='.' && above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.' && above[i1-2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1,i1-1,i1-2,i1-2};
                            int count_i2[] = {i2-1,i2+1,i2+2,i2+2,i2+1,i2-1};
                            for(int i=0;i<6;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 6:// ͺ   -1
                        if(above[i1+2][i2+1]!='.' && above[i1+2][i2-1]!='.' && above[i1+1][i2-2]!='.' && above[i1-1][i2-2]!='.' && above[i1-2][i2-1]!='.' && above[i1-2][i2+1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+2,i1+1,i1-1,i1-2,i1-2};
                            int count_i2[] = {i2+1,i2-1,i2-2,i2-2,i2-1,i2+1};
                            for(int i=0;i<6;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    case 7:// ͺ
                        if(above[i1+2][i2-1]!='.' && above[i1+1][i2-2]!='.' && above[i1-1][i2-2]!='.' && above[i1-2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1,i1-2};
                            int count_i2[] = {i2-1,i2-2,i2-2,i2-1};
                            for(int i=0;i<4;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                    default: //normal move
                        if(above[i1+2][i2+1]!='.' && above[i1+1][i2+2]!='.' && above[i1-1][i2+2]!='.' && above[i1-2][i2+1]!='.' && above[i1-2][i2-1]!='.' && above[i1-1][i2-2]!='.' && above[i1+1][i2-2]!='.' && above[i1+2][i2-1]!='.'){
                            STUCK();
                        }
                        else{
                            int count_i1[] = {i1+2,i1+1,i1-1,i1-2,i1-2,i1-1,i1+1,i1+2};
                            int count_i2[] = {i2+1,i2+2,i2+2,i2+1,i2-1,i2-2,i2-2,i2-1};
                            for(int i=0;i<8;i++){
                                if(below[count_i1[i]][count_i2[i]] == '.' && above[count_i1[i]][count_i2[i]] == '.'){
                                    location[count_i1[i]][count_i2[i]] = 'x';
                                }
                                else if(above[count_i1[i]][count_i2[i]] != '.'){

                                }
                                else if(below[count_i1[i]][count_i2[i]] != '.'){
                                    above[count_i1[i]][count_i2[i]] = 'o';
                                }
                            }
                        }
                        break;
                }
                break;
        }



        if(stuck==0){
            DISPLAY();
            printf("[%c] To where? \n",tmpselect);
            ASK();
            while(location[i1][i2]!='x' && below[i1][i2]!='o'){
                INVALID();
            }
            if(location[i1][i2]=='x' || below[i1][i2]=='o'){
                TEAMPOSITION();
            }
        }
    }
}

void TEAMPOSITION(){    // NOT FINISH                                          // Convert Team[][] into Location[][]
    stuck=0; stucki=0;
    if(turn%2==1){  //below blue
        below[i1][i2]=tmpselect;
        below[tmp1][tmp2]='.';
        above[i1][i2]='.';
        location[i1][i2]=below[i1][i2];
        location[tmp1][tmp2]=below[tmp1][tmp2];
        if(below[7][i2]=='P'){                                      // Pawn reaches otherside. (Promote)
            PROMOTE();
            below[i1][i2]=inp1;
            location[i1][i2]=below[i1][i2];
        }
        switch(i2){
        case 0: inp2='A'; break;
        case 1: inp2='B'; break;
        case 2: inp2='C'; break;
        case 3: inp2='D'; break;
        case 4: inp2='E'; break;
        case 5: inp2='F'; break;
        case 6: inp2='G'; break;
        case 7: inp2='H'; break;
        default: printf("Error"); break;
        }
        switch(tmp2){
        case 0: inp1='A'; break;
        case 1: inp1='B'; break;
        case 2: inp1='C'; break;
        case 3: inp1='D'; break;
        case 4: inp1='E'; break;
        case 5: inp1='F'; break;
        case 6: inp1='G'; break;
        case 7: inp1='H'; break;
        default: printf("Error"); break;
        }
        if ((fp=fopen("chess_history_record.dat","a"))==NULL){
         //w=rewrite whole file, a=add in the file, r=read the file, w+=read and write
         puts("File unaccessable");
        }else{fprintf(fp,"\nTurn %2d[B] = [%c] %c%d to %c%d",turn,tmpselect,inp1,tmp1+1,inp2,i1+1);
        }
        for(i3=7,K=0;i3>=0 && K==0;i3--){
            for(i4=0;i4<=7;i4++){
                if(above[i3][i4]=='K'){
                    K++;
                }
            }
        }
        if(K==0){
            gamestatus++;
            LINE();
            puts("Blue Team Win!!!");
        }
    }

    if(turn%2==0){  //above orange
        above[i1][i2]=tmpselect;
        above[tmp1][tmp2]='.';
        below[i1][i2]='.';
        location[i1][i2]=above[i1][i2];
        location[tmp1][tmp2]=above[tmp1][tmp2];
        if(above[0][i2]=='P'){                                      // Pawn reaches otherside. (Promote)
            PROMOTE();
            above[i1][i2]=inp1;
            location[i1][i2]=above[i1][i2];
        }
        switch(i2){
        case 0: inp2='A'; break;
        case 1: inp2='B'; break;
        case 2: inp2='C'; break;
        case 3: inp2='D'; break;
        case 4: inp2='E'; break;
        case 5: inp2='F'; break;
        case 6: inp2='G'; break;
        case 7: inp2='H'; break;
        default: printf("Error"); break;
        }
        switch(tmp2){
        case 0: inp1='A'; break;
        case 1: inp1='B'; break;
        case 2: inp1='C'; break;
        case 3: inp1='D'; break;
        case 4: inp1='E'; break;
        case 5: inp1='F'; break;
        case 6: inp1='G'; break;
        case 7: inp1='H'; break;
        default: printf("Error"); break;
        }
        if ((fp=fopen("chess_history_record.dat","a"))==NULL){
         //w=rewrite whole file, a=add in the file, r=read the file, w+=read and write
         puts("File unaccessable");
        }else{fprintf(fp,"\nTurn %2d[O] = [%c] %c%d to %c%d",turn,tmpselect,inp1,tmp1+1,inp2,i1+1);
        }
        for(i3=7,K=0;i3>=0 && K==0;i3--){
            for(i4=0;i4<=7;i4++){
                if(below[i3][i4]=='K'){
                    K++;
                }
            }
        }
        if(K==0){
            gamestatus++;
            LINE();
            puts("Orange Team Win!!!");
        }
    }
    XORESET();
}

void STUCK(){
    stuck++;
    printf("Your character have no where to go, Please choose other.\n");
    TURN();
}

void STUCKI(){
    for(stucki=0,i3=7 && stucki!=0;i3>=0;i3--){
        for(i4=0;i4<=7 && stucki!=0;i4++){
            if(location[i3][i4]=='x' || below[i3][i4]=='o' || above[i3][i4]=='o'){
                stucki++;
            }
        }
    }
}

void INVALID(){
    STUCKI();
    if(stucki==0){
        puts("Unexpected Error.");
        TURN();
    }
    else{
        puts("Your input position is invalid.");
        puts("To whereaaa?");
        ASK();
    }

}

void XORESET(){         // FINISH                                                   // Reset 'X' 'O' mark.
    for(i1=7;i1>=0;i1--){
        for(i2=0;i2<=7;i2++){
            if(location[i1][i2]=='x'){
                    location[i1][i2]='.';
                }
            if(below[i1][i2]=='o'){
                below[i1][i2]='.';
            }
            if(above[i1][i2]=='o'){
                above[i1][i2]='.';
            }
        }
    }
}

void PROMOTE(){         // FINISH
    for(i3=i1;i3>=0;i3--){                                   // Reset red color.
        for(i4=0;i4<=7;i4++){
            if(below[i3][i4]=='o'){
                below[i3][i4]='.';
            }
            if(above[i3][i4]=='o'){
                above[i3][i4]='.';
            }
        }
    }
    DISPLAY();
    i3=0;
    while(i3==0){
        puts("What character do you want your pawn to be? (C,H,B,Q)");
        scanf("%s",input);
        if(strlen(input)==1){
            input[0]=toupper(input[0]);
            switch(input[0]){
                case 'C': inp1,input[0]; i3++; break;
                case 'H': inp1=input[0]; i3++; break;
                case 'B': inp1=input[0]; i3++; break;
                case 'Q': inp1=input[0]; i3++; break;
                case 'X': abort(); break;
                default: puts("Error"); PROMOTE(); break;
            }
        }
        else{
            puts("Your input position is invalid.");
        }
    }
    if ((fp=fopen("chess_history_record.dat","a"))==NULL){
    //w=rewrite whole file, a=add in the file, r=read the file, w+=read and write
    puts("File unaccessable");
    }else{fprintf(fp,"\nPromoted (%c>%c):",tmpselect,inp1);
    }
}

void LINE(){            // FINISH
    for(i3=0;i3<=40;i3++){
        printf("-");
    }
    puts("");
}

void DEBUG(){
    LINE();
    for(i3=7;i3>=0;i3--){
        for(i4=0;i4<=7;i4++){
            if(above[i3][i4]=='o'){
                printf(C_RED"%c "C_RESET,above[i3][i4]);
            }
            else if(above[i3][i4]!='.'){
                printf(C_YELLOW"%c "C_RESET,above[i3][i4]);
            }
            else{
                printf("%c ",above[i3][i4]);
            }
        }
        puts("");
    }
    puts("");

    LINE();
    for(i3=7;i3>=0;i3--){
        for(i4=0;i4<=7;i4++){
            if(below[i3][i4]=='o'){
                printf(C_RED"%c "C_RESET,below[i3][i4]);
            }
            else if(below[i3][i4]!='.'){
                printf(C_CYAN"%c "C_RESET,below[i3][i4]);
            }
            else{
                printf("%c ",below[i3][i4]);
            }
        }
        puts("");
    }
    puts("");
}
