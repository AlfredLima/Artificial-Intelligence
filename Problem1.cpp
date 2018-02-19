/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 19/02/2018
*/

#include<bits/stdc++.h>
using namespace std;

unordered_map< string , string > states;

bool valid( string state )
{
  vector<int> qt(5);

  for (int i = 0; i < 5; i++)
    qt[i] = state[i] - '0';

  for (int i = 0; i < 2; i++)
    if( qt[3*i] && qt[3*i+1] > qt[3*i] )
      return false;

  return true;
}

vector<string> generate_candites( string s )
{
  
}

void find( string initial, string finale )
{
  states[initial] = initial;
  queue<string> q;
  q.push_back( initial );

  while( !q.empty() )
  {
      string now = q.front(); q.pop_front();
      vector<string> candites = generate_candites( now );
  }

}

int main(int argc, char const *argv[]) {

  string initial_state = "33000" ,finale_state = "00433" ;

  find( initial_state, finale_state );

  return 0;
}
