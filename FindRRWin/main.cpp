//
//  main.cpp
//  FindRRWin
//
//  Created by Mahmoud Chahine on 9/18/22.
//

#include <iostream>
#include <chrono> //For system_clock
#include <random>
#include <iomanip>
using namespace std;
double getAccountBalance();
int totalTradesTaken();
double getProfitPercent();
double getLossPercent();
int getWinningTrades();
int getLossingTrades();
double getTotalProfitPercent(double, int, double, int, double, int);
double randomSimulations(double, int, double, double, int);
int main(int argc, const char * argv[]) {
    int trades=0, win_rate=0, loss_rate=0;
    double profit_percent=0, loss_percent=0, balance=0, current_profit=0;
    int wins=0, losses=0, break_even=0;
    double profit=0;
    int type_program=0;
    // insert code here...
    balance=getAccountBalance();
    trades=totalTradesTaken();
    cout<<"Select program type\n0-To get risk to reward\n1-To backtest random buys and sells given risk to reward\n";
    cin>>type_program;
    
    //The loop starts here
    while(true)
    {
        profit_percent=getProfitPercent();
        if(type_program==0)
            win_rate=getWinningTrades();
        loss_percent=getLossPercent();
        if(type_program==0)
            loss_rate=getLossingTrades();
        if(type_program==0)
        {
            profit=getTotalProfitPercent(balance, trades, profit_percent, win_rate, loss_percent, loss_rate);
            cout<<"Profit percent: "<<profit<<"%";
            cout<<endl;
            double profit_account=(profit/100)*balance;
            cout<<"\nProfit on account balance $"<<profit_account<<endl;
            cout<<"\nYour profit share for prop firm account: $"<<profit_account*0.80<<endl;
        }
        else if(type_program==1)
        {
            int runs=0;
            cout<<"Enter how many times you'd like to simulate results: ";
            cin>>runs;
            double total_profit=0;
            double average_profit=0, average_percent=0;
            bool continues=false;
            double total_balance=balance;
            double current_balance=0;
            int check=0;
            //Check if the user wants continues or seperate results
            cout<<"\nWould you like to have continues or seperate results for each month\n1- For seperate months\n2- For continues\n";
            cin>>check;
            check==1 ? continues=false : continues=true;
            
                //int temp_balance=balance;
                for(int i=0;i<runs;i++)
                {
                    //srand( static_cast<unsigned int>(time(nullptr)));
                    total_profit+=current_profit;
                    if(!continues)
                    {
                        current_profit=randomSimulations(balance, trades, profit_percent, loss_percent, i+1);
                        if(current_profit>0)
                        {
                            wins++;
                        }
                        else if(current_profit<0)
                        {
                            losses++;
                        }
                        else if(current_profit==0)
                        {
                            break_even++;
                        }
                    }
                    if(continues)
                    {
                        current_profit=randomSimulations(total_balance, trades, profit_percent, loss_percent, i+1);
                        current_balance=(current_profit/100)*total_balance;
                        total_balance+=(total_profit/100)+current_balance;
                        
                    
                    }
                       
            
                }
            if(!continues)
            {
                average_percent=total_profit/runs;
                //You can find then the lowest value for losses and mention how many wins and losses total for all the months
                average_profit=(average_percent/100)*((double)balance);
                cout<<"\nYour total wins is: "<<wins<<endl<<"Your total losses is: "<<losses<<endl;
                cout<<"Your total break even is: "<<break_even<<endl;
                wins=0;
                losses=0;
                break_even=0;
                cout<<"Your average profit percent is: "<< fixed << setprecision(2)<<average_percent<<"%"<<endl;
                cout<<"Your average profit on account balance is: $"<< fixed << setprecision(2)<<average_profit<<endl;
                cout<<"Your average profit share for prop firm account is: $"<< fixed << setprecision(2)<<average_profit*0.80<<endl;
            }
            else if(continues)
            {
                cout<<"Your total profit percent is: "<< fixed << setprecision(2)<<total_profit<<"%"<<endl;
                cout<<"Your total profit balance is: $"<< fixed << setprecision(2)<<total_balance<<endl;
                cout<<"Your profit share for prop firm account is: $"<< fixed <<setprecision(2)<<(total_balance-balance)*0.80<<endl;
                total_balance=0;
                current_balance=0;
            }
            }
          
                
            //A function to compute the results
            
        }
       
   
    return 0;
}
double getAccountBalance() {
    double balance=0;
    cout<<"Enter your account balance: ";
    cin>>balance;
    cout<<endl;
    return balance;
}
int totalTradesTaken() {
    int trades=0;
    cout<<"\nHow many trades would you like to place: ";
    cin>>trades;
    cout<<endl;
    return trades;
}
double getProfitPercent() {
    double profitPercent=0;
    cout<<"\nEnter your winning percent rate: ";
    cin>>profitPercent;
    cout<<endl;
    return profitPercent;
}
int getWinningTrades() {
    int win_trades=0;
    cout<<"Enter how many winning trades you have taken: ";
    cin>>win_trades;
    cout<<endl;
    return win_trades;
}
double getLossPercent() {
    double lossPercent=0;
    cout<<"Enter your loss percent rate: ";
    cin>>lossPercent;
    cout<<endl;
    return lossPercent;
}
int getLossingTrades() {
    int loss_trades=0;
    cout<<"Enter how many losing trades you have taken: ";
    cin>>loss_trades;
    cout<<endl;
    return loss_trades;
}
double getTotalProfitPercent(double balance, int tradesTaken, double win_percent, int win_rate, double loss_percent, int loss_rate)
{
    double profit=0;
    int getDaysCycle=win_rate+loss_rate;
    int totalCycles=tradesTaken/getDaysCycle;
    for(int i=0;i<totalCycles;i++)
    {
        profit+=(win_percent*win_rate)-(loss_percent*loss_rate);//calculates the profit on every cycle
    }

    return profit;
}
double randomSimulations(double account_balance, int trades_taken, double profit_percent, double loss_percent, int runs)
{
    double profit=0;
    int win_loss=0;
    //unsigned seed = time(0);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    //uniform_real_distribution<double> distributionDouble(1.0, 10.0); // Set the numbers for double.
    //0-2 because 3 if position is break even
    uniform_int_distribution<int> distributionInteger(0, 2);
    //srand (time(0));
    int wins=0, losses=0, break_even=0;
    for(int i=0;i<trades_taken;i++)
    {
        srand(seed);
        win_loss=distributionInteger(generator);
        if(win_loss==2)
        {
            profit+=0;
            break_even++;
        }
        else if(win_loss==0)
        {
            profit+=profit_percent;
            wins++;
        }
        else if(win_loss==1)
        {
            profit-=loss_percent;
            losses++;
        }
       // cout<<i<<"- "<<win_loss<<endl;
        //Now random number if 1 means win if 0 means loss will figure out the
    }
    //Then display output
    cout<<runs<<"- "<<"Your total wins is: "<<wins<<endl<<"Your total losses is: "<<losses<<endl;
    cout<<"Your total break even is: "<<break_even<<endl;
    cout<<"Profit percent: "<<profit<<"%";
    cout<<endl;
    double profit_account=(profit/100)*account_balance;
    cout<<"Account balance $"<<fixed<<setprecision(2)<<account_balance+profit_account<<endl;
    cout<<"Profit on account balance $"<<fixed<<setprecision(2)<<profit_account<<endl;
    cout<<"Your profit share for prop firm account: $"<<fixed<<setprecision(2)<<profit_account*0.80<<endl<<endl;
    return profit;
}
