#include <iostream>
#include <limits>
#include <stdlib.h>

#define X 1
#define O 2
#define INF 1000000

using namespace std;

bool vinto = false;
int G[9] = {0, 0, 0,
            0, 0, 0,
            0, 0, 0};

void mostra_pos(){
    cout << "\n position indeces: ";
    for(int i=0; i<3; i++){
        cout << "\n ";
        for(int j=0; j<3; j++){
            cout << i*3 + j + 1 << " ";
        }
    }
    cout << "\n";
}

void stampa_G(){
    cout << "\n\n";
    for(int i=0; i<3; i++){
        cout << "\n ";
        for(int j=0; j<3; j++){
            if(G[i*3 + j] == 1)
                cout << "X ";
            else if(G[i*3 + j] == 2)
                cout << "O ";
            else
                cout << ". ";
        }
    }
    cout << "\n\n";
}

bool controlla_vittoria(){
    for(int i=0; i<3; i++)
        if(G[i] == G[i+3] && G[i] == G[i+6] && G[i] != 0)
            return true;

    for(int i=0; i<9; i += 3)
        if(G[i] == G[i+1] && G[i] == G[i+2] && G[i] != 0)
            return true;

    if(G[0] == G[4] && G[0] == G[8] && G[0] != 0)
        return true;

    if(G[2] == G[4] && G[2] == G[6] && G[2] != 0)
        return true;

    return false;
}

void turno_giocatore(){
    mostra_pos();
    cout << "\n It's your turn\n choose a position: ";
    int pos;
    cin >> pos;
    while(pos > 9 || pos < 1 || G[pos - 1] != 0){
        cout << " choose another position: ";
        cin >> pos;
    }
    pos--;
    G[pos] = X;
}

long long int ric(bool pc){
    if(controlla_vittoria()){
        if(pc) return -1;
        else return 1;
    }
    long long int tot;
    if(pc){
        tot = -INF;
        for(int i=0; i<9; i++){
            if(G[i] == 0){
                G[i] = O;
                tot = max(ric(false), tot);
                G[i] = 0;
            }
        }
    }
    else{
        tot = INF;
        for(int i=0; i<9; i++){
            if(G[i] == 0){
                G[i] = X;
                tot = min(ric(true), tot);
                G[i] = 0;
            }
        }
    }
    if(tot == INF || tot == -INF) tot = 0;
    return tot;
}

void turno_pc(){
    long long int res[9] = {-LONG_MIN, -LONG_MIN, -LONG_MIN, -LONG_MIN, -LONG_MIN, -LONG_MIN, -LONG_MIN, -LONG_MIN, -LONG_MIN};
    for(int i= 0; i<9; i++){
        if(G[i] == 0){
            G[i] = O;
            if(controlla_vittoria()) return;
            else res[i] = ric(false);
            G[i] = 0;
        }
    }
    int ret;
    long long int maxi = -LONG_MIN;
    for(int i = 0; i < 9; i++)
        if(res[i] != -LONG_MIN)
            if(res[i] > maxi)
                maxi = res[i], ret = i;

    G[ret] = O;
}

int main()
{
    stampa_G();
    turno_giocatore();
    for(int i=0; i<4; i++){
        turno_pc();
        if(controlla_vittoria()){
            system("cls");
            cout << "\n You lost!";
            stampa_G();
            system("pause");
            return 0;
        }

        system("cls");
        stampa_G();
        turno_giocatore();
        if(controlla_vittoria()){
            system("cls");
            cout << "\n You won!";
            stampa_G();
            system("pause");
            return 0;
        }
    }
    system("cls");
    cout << "\n Tie!";
    stampa_G();
    system("pause");
    return 0;
}
