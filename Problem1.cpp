/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 19/02/2018
*/

#include<bits/stdc++.h>
using namespace std;


// Distribuição
// ||Canibais E||Missionarios E||Canibais B||Missionarios B||Canibais D||Missionarios D||Lado do rio||

int load[2][5][6] = 
{
  { {-1,0,1,0,0,0} , {-2,0,2,0,0,0} , {0,-1,0,1,0,0} , {0,-2,0,2,0,0} , {-1,-1,1,1,0,0} } ,
  { {0,0,1,0,-1,0} , {0,0,2,0,-2,0} , {0,0,0,1,0,-1} , {0,0,0,2,0,-2} , {0,0,1,1,-1,-1} }
};

map< string , string > states;

bool valid( vector<int> &state )
{
  for( auto s : state )
    if( s < 0 ) return false;

  if( state[0] > state[1] ) return false;

  if( state[4] > state[5] ) return false;
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
  vector<int> qt(7);
  vector<int> next_state(7);
  for (int i = 0; i < 7; i++)
    qt[i] = s[i] - '0';

  if( qt[2] + qt[3] == 0 )
  {
    // Carrega o barco
    next_state[ 6 ] = 1 - qt[ 6 ];
    for (int i = 0; i < 5 ; ++i) {
      for( int j = 0 ; j < 6 ; ++j ) {
        next_state[j] = qt[j] + load[ qt[6] ][ i ][ j ];
      }
      if( valid(next_state) )
        candidates.push_back( toString(next_state) );
    }
  }
  else
  {
    // Descarrega o barco
    for (int i = 0 ; i < 7 ; ++i )
      next_state[i] = qt[i];

    next_state[ 4*qt[6] ] += next_state[ 2 ];
    next_state[ 2 ] -= next_state[ 2 ];
    next_state[ 4*qt[6] + 1 ] += next_state[ 3 ];
    next_state[ 3 ] -= next_state[ 3 ];

    candidates.push_back( toString(next_state) );
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
    cout << "Analisando: " << now << endl;    
    if( now == finale ) break;
    vector<string> candidates = generate_candidates( now );
    for ( auto next : candidates )
    {
      if( !states.count(next) )
      {
        states[next] = now;
        q.push( next );    
      }
    }
  }

  string s = finale;
  stack<string> print;
  do
  {
    print.push( s );
    s = states[s];
  }
  while( initial != s );

  cout << initial;  
  while( !print.empty() ){
    cout << " -> " << print.top();
    print.pop();
  }
  cout << endl;

}

void testLoad()
{
  vector<string> vs;
  vs.push_back( "3300000" );
  vs.push_back( "3300001" );
  vs.push_back( "0000331" );
  vs.push_back( "0000330" );

  for (int i = 0; i < vs.size() ; ++i)
  {
    cout << "Analisando " << vs[i] << ":";
    for( auto s : generate_candidates( vs[i]) )
      cout << " " << s;
    cout << endl;
  }

}

void testDownload()
{
  vector<string> vs;
  vs.push_back( "2310001" );
  vs.push_back( "1320001" );
  vs.push_back( "2211001" );

  vs.push_back( "0010230" );
  vs.push_back( "0020130" );
  vs.push_back( "0011220" );

  for (int i = 0; i < vs.size() ; ++i)
  {
    cout << "Analisando " << vs[i] << ":";
    for( auto s : generate_candidates( vs[i]) )
      cout << " " << s;
    cout << endl;
  }

}

int main(int argc, char const *argv[]) {

  string initial_state = "3300000" ,finale_state = "0000331" ;
  
  find( initial_state, finale_state );

  //testLoad();
  //testDownload();

  return 0;
}
