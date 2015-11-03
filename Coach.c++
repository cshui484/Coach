// ----------------------------
// projects/coach/Coach.c++
// Copyright (C) 2015
// CS Hui
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <deque>
#include <functional>
#include <map>
#include <climits>
#include <set>
#include <vector>

//include "Coach.h

using namespace std;
	
// -------------
// coach_solve
// -------------

void coach_solve (istream& r, ostream& w) {
    int	n, m;						// n = num of persons, m = number of pairs
    int	a, b;
	int idx = 0;
	int j;
    int n1, n2;						// n1 always < n2
	vector<int>				p2gp;	// peer group each person belongs to, 0 means no preference
	map<int, vector<int>>	gm;		// store group members into group ID
	vector<int>				remain;	// person doesn't have preference
	string	buf = "";				// buffer for printing the result

	r >> n >> m;			
	
	p2gp.reserve(n+1);
	for (int i=0; i<=n; i++) {		// initialize vector of n+1 zeros, entry 0 is not used
		p2gp.push_back(0); }
	
	for (int i=0; i<m; i++) {		// iterate for all input pairs

		r >> a >> b;				// read the pair of numbers
		if (a > b) {				// sort a, b into n1, n2
			n1 = b;
			n2 = a; }
		else {
			n1 = a;
			n2 = b; }

		if ((p2gp[n1] == 0) && (p2gp[n2] == 0)) {		// both have no peer group yet
			p2gp[n1] = n1;
			p2gp[n2] = n1;
			gm[n1].push_back(n2); }
		else if ((p2gp[n1] != 0) && (p2gp[n2] != 0)) {	// both have their peer groups
			if (p2gp[n1] != p2gp[n2]) {					// if not the same group
				w << -1 << endl;						//   no solution
				return; }}
		else if (p2gp[n1] != 0) {						// only n1 has peer group
			if (gm[p2gp[n1]].size() >= 2) {				// too many persons want to be together
				w << -1 << endl;						//   no solution
				return; }
			p2gp[n2] = p2gp[n1];						// add n2 to n1's group
			gm[p2gp[n1]].push_back(n2); }
		else {											// only n2 has peer group
			if (gm[p2gp[n2]].size() >= 2) {				// too many persons want to be together
				w << -1 << endl;						//   no solution
				return; }
			if (n1 > p2gp[n2]) {						// n1 > n2's group ID
				p2gp[n1] = p2gp[n2];					//   add n1 to n2's group
				gm[p2gp[n2]].push_back(n1); }
			else {										// move n2's group to the new n1 group
				p2gp[n1] = n1;
				if (p2gp[n2] != n2) {					// n2 belongs to someone else's group
					p2gp[p2gp[n2]] = n1; }				//   p2gp[n2] -> the 3rd person's ID
				else {									// n2 belongs to his own group
					p2gp[gm[n2][0]] = n1; }				//   gm[n2][0] -> the 3rd person's ID
				p2gp[n2] = n1; }}}

	for (int i=1; i<=n; i++) {							// collect the persons who have no peer group
		if (p2gp[i] == 0) {
			remain.push_back(i); }}

	for (map<int, vector<int>>::iterator it=gm.begin(); it!=gm.end(); it++) {
		int i = it->first;
		if (gm[i].size() == 1) {
			if ((int) remain.size() > idx) {
				j = remain[idx]; 
				idx += 1;
				buf += to_string(i) + ' ' + to_string(gm[i][0]) + ' ' + to_string(j) + '\n'; }
			else {
				w << -1 << endl;
				return; }}
		else {
			buf += to_string(i) + ' ' + to_string(gm[i][0]) + ' ' + to_string(gm[i][1]) + '\n'; }}

	w << buf;
	while ((int) remain.size() > idx) {
		w << remain[idx] << ' ' << remain[idx+1] << ' ' << remain[idx+2] << endl;
		idx += 3;	}
	
}
	
// ----
// main
// ----

int main () {
    using namespace std;
//    cout << "main" << endl;
    coach_solve(cin, cout);
    return 0;}


