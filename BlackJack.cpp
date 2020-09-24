// Example program
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//convert string to integer for computation, also JQK to integer
int JQKtoInteger(string num){
	if(num!=""){
	if(num=="J"||num=="Q"||num=="K"){
		return 10;
	}else{
		return stoi(num);
	}
}
}

//class for Card
class Card{
  public:
  		Card(){};
        Card(string Suit, string Number) : Suit(Suit), Number(Number) { };
		string Suit;
		string Number;
  
  public:
  void printCard(){
  	if (Suit.length() || Number.length()){
  		cout<<"Card "<<Suit<<" "<<Number<<endl;
	  }
  }
};

//calculate score using a for loop
int HandScore(Card c[]){
	
	int score = 0;
	
	for (int i=0;i<5;i++){
		
		//bow bow
		if(c[0].Number==c[1].Number){
			return 21;
		}
		
		if( c[0].Number=="1"&& (c[1].Number=="10" || c[1].Number=="J" || c[1].Number=="Q" || c[1].Number=="K")){
			return 21;
		}
		
		if( c[1].Number=="1"&& (c[0].Number=="10" || c[0].Number=="J" || c[0].Number=="Q" || c[0].Number=="K")){
			return 21;
		}
		
		score += JQKtoInteger(c[i].Number);
	}
	
	if(score>21){
		return 0;
	}
		
	return score;
}

//class for Player
class Player{
    public:
        Card hand[5]; //Cant make this work
        bool stopDraw = false;
        
        void showHand(){
        	for(int k=0;k<5;k++){
        		hand[k].printCard();
			}
		}
		
		int computeScore(){
			return HandScore(hand);
		}
        
        
};

int main()
{
    srand(time(0)); //set initial seed, so random differently
    
	vector<Card> deck; //initialize deck of Cards
	
    int i = 0; //vector iterator dont have integer so this is a dirty fix
    int numOfPlayers; //number of players playing, including banker
    int cardCountInDeck=0; //keep track of how many cards had been drawn from deck
    
	const vector<string> suit = {"spade","heart","club","diamond"}; 
	const vector<string> number = {"1","2","3","4","5","6","7","8","9","10","J","Q","K"}; 

	//this iterator creates every single 52 cards
	for(vector <string> :: const_iterator it = suit.cbegin(); it != suit.cend(); ++it){ 
		for(vector <string> :: const_iterator n = number.cbegin(); n != number.cend(); ++n){

    		deck.push_back(Card(*it,*n));
            i++;
		    }
	} 
	
	//randomly shuffle the deck
	random_shuffle(begin(deck), end(deck)); 
	
	//prompt user to input number of players
    cout<<"Hi Sir, how many players are there?: ";
    cin>>numOfPlayers;
    
    //increase 1 because there is banker also
    numOfPlayers++;
    
    //create an array of players
    Player *player[numOfPlayers]; 

	//initialize every player
    for (int i=0;i<numOfPlayers;i++){
    	player[i] = new Player;
	}
    
    //distribute cards
    for (int j=0;j<2;j++){
         for (int i=0;i<numOfPlayers;i++){

             Card& c = deck.at(cardCountInDeck);
             player[i]->hand[j]=c;
             cardCountInDeck++;
             
         }

    }
    
    //Banker Player show hand of cards
    for(int i=0;i<numOfPlayers;i++){
    	if(i==0){
    		cout<<"\nBANKER"<<endl;
		}else{
			cout<<"\nPLAYER "<<i<<endl;
		}
    	player[i]->showHand();	
	}
	
	//array to store scores of players
	int score[numOfPlayers];
	
	//calcualte and store result to array
	for(int i=0;i<numOfPlayers;i++){
		score[i] = player[i]->computeScore();
	}
	
	//to be implemented-drawing cards if score is below 14
	int yes;
	for(int i=2;i<5;i++){
		cout<<"===========Card Drawing Session "<<i<<"=====(1 Yes/ 0 No)=====";
		for(int j=0;j<numOfPlayers;j++){
			if(score[j]!=0){
				if(score[j]!=21){
					
					if(player[j]->stopDraw == false){
						if(j==0){
							cout<<"\nBanker do u want to draw cards? ["<<score[0]<<"] : ";
						}else{
							cout<<"\nPlayer "<<j<<" do u want to draw cards? ["<<score[j]<<"] : ";
						}
						cin>>yes;
						
					if(yes==1){
						
						Card& c = deck.at(cardCountInDeck);
						c.printCard();
			            player[j]->hand[i]=c;
		
			            score[j] = player[j]->computeScore();
			            cout<<"Score now: "<<score[j]<<endl;
			            
			            if(score[0]==0){
							cout<<"Banker is busted\n";
							goto endgame;	            	
						}
			            if(score[j]==0){
							cout<<"Player "<<j<<" is busted\n";
						}
						cardCountInDeck++;
			 
					}else{
						player[j]->stopDraw = true;
					}
										
					}
			
				}
				
			}
		
		}
	}
	
	endgame:
	//displaying results
	for(int i=0;i<numOfPlayers;i++){
		
		if(i==0){ //0 because 0th player is banker
			//show banker score first
			cout<<"\n\n============GAME OVER=============";
			cout<<"\nBANKER Score : "<<score[i]<<endl;
			player[i]->showHand();
			cout<<"==================================";
			
		}else{
			//show player score
			cout<<"\nPlayer "<<i<<" Score : "<<score[i]<<endl;
			player[i]->showHand();
			
			if(score[i]>score[0]){ //if score is higher than banker
				cout<<"Congratz Player "<<i<<"!"<<endl;
			}else if(score[i]==score[0]){
				cout<<"It's a Draw!"<<endl;
			}else{
				cout<<"Better luck next time!"<<endl;
			}
		}		
	}

return 0;
}
