/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 19/02/2018
*/

#include<bits/stdc++.h>
using namespace std;

int load[2][3][5] = 
{
  { {-1,0,1,0,0} , {0,-1,2,0,0} , {-1,-1,3,0,0} } ,
  { {0,0,1,-1,0} , {0,0,2,0,-1} , {0,0,3,-1,-1} }
};


map< string , string > states;

bool valid( string s )
{
  vector<int> qt(5);

  for (int i = 0; i < 5; i++)
    qt[i] = s[i] - '0';

  for (int i = 0; i < 2; i++)
    if( qt[3*i] && qt[3*i+1] > qt[3*i] )
      return false;

  return true;
}

string toString( vector<int> &values )
{
  string ans = "";
  
  for( auto v : values )
    ans += (v+'0');

  return ans;
}

vector<string> generate_candidates( string &s )
{
  vector<string> candidates;
  vector<int> qt(5);
  vector<int> next_state(5);
  for (int i = 0; i < 5; i++)
    qt[i] = s[i] - '0';

  if( qt[2] == 0 || qt[2] == 4 )
  {
    // Carrega o barco
    for(int j = 0; j < 3 ; ++j)
    {
      for (int i = 0; i < 5 ; ++i)
        next_state[i] = qt[i] + load[ qt[2]>>2 ][ j ][ i ];
      candidates.push_back( toString(next_state) );
    }
  }
  else
  {

  }
  return candidates;
}

void find( string &initial, string &finale )
{
  states[initial] = initial;
  queue<string> q;
  q.push( initial );

  while( !q.empty() )
  {
      string now = q.front(); q.pop();
      vector<string> candidates = generate_candidates( now );
  }

}

int main(int argc, char const *argv[]) {

  string initial_state = "33000" ,finale_state = "00433" ;

  //find( initial_state, finale_state );

  cout << "Inicio " << endl;
  for( auto s : generate_candidates(finale_state) )
  {
    cout << s << endl;
  }

  return 0;
}
