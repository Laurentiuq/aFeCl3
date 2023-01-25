#include <bits/stdc++.h>

#define IMP 0
#define LOSE 1
#define DRAW 2
#define WIN 3
using namespace std;


//ifstream in("maxflow.in");
//ofstream out("maxflow.out");
ifstream in("xsizero.in");
ofstream out("xsizero.out");

const int MAXN = 20005;

char m[3][3];
int states[MAXN];


// in ce stare se afla tabla/cate casute sunt completate
int calcState() {
    int l, c, ans, pow;

    pow = 1;
    ans = 0;
    for ( l = 0; l < 3; l++ ) {
        for ( c = 0; c < 3; c++ ) {
            ans = ans + m[l][c] * pow;
            pow *= 3;
        }
    }

    return ans;
}

int precalc(int remainingSq, int whoMoves) {
    int currentState, other, finalState, c, l, x;

    if ( whoMoves == 1 )
        other = 2;
    else
        other = 1;

    finalState = IMP;
	// verific daca pe linii si pe coloane poate sa castige X
    for ( c = 0; c < 3; c++ ) {
        if ( m[0][c] == m[1][c] && m[0][c] == m[2][c] && m[0][c] != 0 ) {
            finalState = m[0][c];
        }
        if ( m[c][0] == m[c][1] && m[c][0] == m[c][2] && m[c][0] != 0 ) {
            finalState = m[c][0];
        }
    }
	// verific daca pe diagonale poate sa castige X
    if ( m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[0][0] != 0 )
        finalState = m[2][2];
    if ( m[0][2] == m[1][1] && m[0][2] == m[2][0] && m[0][2] != 0 )
        finalState = m[2][0];

	// daca nu mai sunt mutari si avem o stare invalida inseamna remiza
    if ( finalState == IMP && remainingSq == 0 ) {
        finalState = DRAW;
		
    } 
	// altfel castiga X
	else {
        if ( finalState == other ) {
            finalState = WIN;
        }
    }

	// daca tabla nu este inca completa apelam recursiv
    currentState = calcState();
    if ( !finalState ) {
        finalState = 3;
        for ( l = 0; l < 3; l++ ) {
            for ( c = 0; c < 3; c++ ) {
                if ( m[l][c] == 0 ) {
                    m[l][c] = whoMoves;
                    x = precalc(remainingSq - 1, other);
                    finalState = min(finalState, x);
                    m[l][c] = 0;
                }
            }
        }
    }
	
	// daca avem un numar impar de castue completate si suntem intr-o stare finala inseamna ce se mai pot completa
	// "complementar" cu X si 0 cele doua casute si tabla o sa fie completa( 7 sunt deja completate)
	// altfel inseamna ca am ajuns la starea finala cu 9 casute
    if ( finalState % 2 == 1 )
        states[currentState] = (finalState + 2) % 4;
    else
        states[currentState] = finalState;

    return states[currentState];
}

int main() {

    int l, c, i, state, nrBlocks;
    char ch;

    precalc(9, 2);

	// citirea si afisarea rezultatelor
    in.get(ch);
    i = 1;
    while ( ch == '.' || ch == 'X' || ch == '0' ) {
        nrBlocks = 0;
        for ( l = 0; l < 3; l++ ) {
            for ( c = 0; c < 3; c++ ) {
                if ( ch == '.' ) {
                    m[l][c] = 0;
                } else {
					// cate sunt deja completate
                    nrBlocks++;
                    if ( ch == '0' ) {
                        m[l][c] = 1;
                    } else {
                        m[l][c] = 2;
                    }
                }
                in.get(ch);
            }
            in.get(ch);
        }

        out<< "Testul #"<< i << ": ";
        state = calcState();
        if ( states[state] == 0 ) {
            out<<"invalid\n";
        } else if ( states[state] == 1 ) {
			// daca nr de casute deja completate e par si ne aflam in 
            if ( nrBlocks % 2 == 0 )
                out << "lose\n";
            else
                out << "win\n";
        } 
		else if ( states[state] == 2 ) {
            out<<"draw\n";
        } else {
            if ( nrBlocks % 2 == 0 )
                out<<"win\n";
            else
                out<<"lose\n";
        }
        i++;
    }

    return 0;
}