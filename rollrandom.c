#include<stdio.h>
#include<stdlib.h>

int * board;
int size;
int nrand;
int money;

void title(){
	printf("================================================\n");
	printf("!                 ROLL RANDOM                  !\n");
	printf("================================================\n");
}

void help(){
	printf("================================================\n");
	printf("                    HELP                        \n");
	printf("================================================\n");
	printf("* This game is gambling game.\n");
	printf("* You choose how many squares for Board.\n");
	printf("* You choose initial money.\n");
	printf("* In each turns you choose how many numbers you draw.\n");
	printf("* After that you choose squares to bet.\n");
	printf("* If a square is the same number of drawn number then you earn money equivalente to bet multiply to RATE.\n");
	printf("* Let be NR number of drawn numbers and SZ size of board, then : \n");
	printf(" RATE is calculate as RATE = ((1-NR/SZ)*10)+1\n");
	printf("================================================\n");
}

void initBoard(){
	while(1){
		printf("Choose size(minimum 10) of board : ");
		scanf("%d",&size);
		if(size<10){
			continue;
		}
		board = (int *) calloc(size,sizeof(int));
		break;
	}
}

int initMoney(){
	while(1){
		printf("Choose initial money : ");
		scanf("%d",&money);
		if(money>0){
			break;
		}
	}
	
	return money;
}

void showBoard(){
	printf("\n------------------------------\n");
	int i;
	for(i=0;i<size;i++){
		printf("square %d = %d\n",i,board[i]);
	}
	printf("------------------------------\n");
}

void makeBets(){
	printf("Make bets in squares of board.\n");
	int n;
	int b;
	while(1){
		showBoard();
		printf("Money = %d\n",money);
		printf("Write a number of square of board to make bet or -1 to stop bet : ");
		scanf("%d",&n);
		if(n==-1){
			break;
		}
		else if((n<-1)||(n>=size)){
			printf("Invalid Square .....\n");
			continue;
		}
		
		while(1){
			printf("Positive Number for increase bet in square and Negative for decrease.\n");
			printf("Write bet : ");
			scanf("%d",&b);
			if((b<0)&&(board[n]<(-b))){
				printf("Square %d don't have %d money.\n",n,-b);
				continue;
			}
			else if((b>0)&&(money<b)){
				printf("I haven't %d money.\n",b);
				continue;
			}
			board[n]+=b;
			break;
		}
	}
}

void numDrawn(){
	while(1){
		printf("Number of Random Number : ");
		scanf("%d",&nrand);
		if((nrand>0)&&(nrand<=(size/2))){
			break;
		}
	}
}

void earnMoney(){
	float rz = nrand/size;
	float p = ((1-rz)*10)+1;
	printf("Size = %d\n",size);
	printf("Number of Drawn Numbers = %d\n",nrand);
	printf("Rate = %f\n",p);
	int i;
	for(i=0;i<nrand;i++){
		int r = rand()%size;
		printf("Drawn Number %d -> ",r);
		if(board[r]!=0){
			int e = (int) p*board[r];
			printf("You earn %d in square %d.\n",e,r);
			money += e;
		}
		else{
			printf("You earn nothing.\n");
		}
	}
	for(i=0;i<size;i++){
		board[i]=0;
	}
}

void showMoney(int m0){
	float prc = (100*(money/m0))-100;
	printf("\n---------------------------\n");
	printf("Initial Money = %d\n",m0);
	printf("Money = %d\n",money);
	printf("Percentage = %d%%\n",prc);
	printf("---------------------------\n");
}

void new_game(){
	initBoard();
	int m0 = initMoney();

	while(1){
		numDrawn();
		makeBets();
		earnMoney();
		if(money<=0){
			printf("\nYOU LOSE\n");
			break;
		}
		showMoney(m0);
		
		printf("Finish(press 0) ? \n");
		int op;
		scanf("%d",&op);
		if(op==0){
			break;
		}
	}
}

void menu(){
	int op;
	while(1){
		printf("---------------------\n");
		printf("[1] - New Game\n");
		printf("[2] - Help\n");
		printf("[3] - Quit\n");
		printf("---------------------\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				new_game();
				break;
			case 2:
				help();
				break;
			case 3:
				exit(0);
				break;
			default:
				printf("Invalid Option .....\n");
				continue;
		}
	}
}

int main(){
	title();
	menu();
	system("pause");
	return 0;
}