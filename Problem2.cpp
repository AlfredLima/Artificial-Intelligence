/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 22/02/2018
*/

#include<bits/stdc++.h>
using namespace std;

struct node {
    string name;
    map< string , vector<string> > edges;

    node(){

    }

    node(string name){
        this->name = name;
    }

};

map< string , node > nodes;

void createNodes(){
    for (int i = 1; i < 15 ; ++i) {
        string name = "E" + to_string(i);
        nodes[ name ] = node(name);
    }
}

void createConnections(){
    // Nós da linha azul
    int blue[] = {1,2,3,4,5,6};
    vector<int> vblue ( blue , blue + sizeof(blue)/ sizeof(int) );

    // Nós da linha amarela
    int yellow[] = {10,2,9,8,5,7};
    vector<int> vyellow ( yellow , yellow + sizeof(yellow)/ sizeof(int) );

    // Nós da linha vermelha
    int red[] = {11,9,3,13};
    vector<int> vred ( red , red + sizeof(red)/ sizeof(int) );

    // Nós da linha verde
    int green[] = {12,8,4,13,14};
    vector<int> vgreen ( green , green + sizeof(green)/ sizeof(int) );

    // Conexões da linha azul
    for (int i = 1; i < vblue.size() ; ++i) {
        string n1 = "E" + to_string( vblue[i-1] );
        string n2 = "E" + to_string( vblue[i] );
        nodes[ n1 ].edges["blue"].push_back( n2 );
        nodes[ n2 ].edges["blue"].push_back( n1 );
    }

    // Conexões da linha amarela
    for (int i = 1; i < vyellow.size() ; ++i) {
        string n1 = "E" + to_string( vyellow[i-1] );
        string n2 = "E" + to_string( vyellow[i] );
        nodes[ n1 ].edges["yellow"].push_back( n2 );
        nodes[ n2 ].edges["yellow"].push_back( n1 );
    }

    // Conexões da linha vermelha
    for (int i = 1; i < vred.size() ; ++i) {
        string n1 = "E" + to_string( vred[i-1] );
        string n2 = "E" + to_string( vred[i] );
        nodes[ n1 ].edges["red"].push_back( n2 );
        nodes[ n2 ].edges["red"].push_back( n1 );
    }

    // Conexões da linha verde
    for (int i = 1; i < vgreen.size() ; ++i) {
        string n1 = "E" + to_string( vgreen[i-1] );
        string n2 = "E" + to_string( vgreen[i] );
        nodes[ n1 ].edges["green"].push_back( n2 );
        nodes[ n2 ].edges["green"].push_back( n1 );
    }

}

int main(){

}