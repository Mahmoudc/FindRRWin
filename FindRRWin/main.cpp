//
//  main.cpp
//  FindRRWin
//
//  Created by Mahmoud Chahine on 9/18/22.
//

#include <iostream>
using namespace std;
double getAccountBalance();
int totalTradesTaken();
double getProfitPercent();
double getLossPercent();
int getWinningTrades();
int getLossingTrades();
double getTotalProfitPercent(double, int, double, int, double, int);
int main(int argc, const char * argv[]) {
    int trades=0, win_rate=0, loss_rate=0;
    double profit_percent=0, loss_percent=0, balance=0;
    double profit=0;
    // insert code here...
    balance=getAccountBalance();
    trades=totalTradesTaken();
    //The loop starts here
    while(true)
    {
        profit_percent=getProfitPercent();
        win_rate=getWinningTrades();
        loss_percent=getLossPercent();
        loss_rate=getLossingTrades();
        profit=getTotalProfitPercent(balance, trades, profit_percent, win_rate, loss_percent, loss_rate);
        cout<<"Profit percent: "<<profit<<"%";
        cout<<endl;
        double profit_account=(profit/100)*balance;
        cout<<"\nProfit on account balance $"<<profit_account<<endl;
        cout<<"\nYour profit share for prop firm account: $"<<profit_account*0.80<<endl;
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
    cout<<"Enter your winning percent rate: ";
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
