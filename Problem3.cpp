/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 26/02/2018
*/

#include<bits/stdc++.h>
using namespace std;

// Leitura da tabela
void readFile(){
    FILE *fp;
    fp = fopen("Problem3.in", "r+");
    int c;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            fscanf(fp , "%d", &c );
            table[ "E" + to_string(i+1) ][ "E" + to_string(j+1) ] = c;
        }
    }
}

int main(int argc, char const *argv[])
{
		
	return 0;
}