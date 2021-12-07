// Copyright 2021 Brian Homoon Jung brianhmj@bu.edu
// Copyright 2021 Landon Kushimi lsk1801@bu.edu

// leave these:
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::vector;
using std::string;
using std::cout;
using std::sort;
using std::cin;


//  your code here.


int choose(int n, int k) {
  if (k == 0) {
    return 1;
  } else {
    return (n * choose(n - 1, k - 1)) / k;
  }
}

class Wedding {
 public:
  vector<string> shuffleFib(string guests) {
    int numGuests = guests.length();
    string firstGuest;
    vector<string> baseCase;
    firstGuest.push_back(guests.at(0));
    baseCase.push_back(firstGuest);
    vector<vector<string>> allSolns;
    allSolns.push_back(baseCase);
    vector<string> tempVec;
    string tempStr;

    for (int i = 1; i < numGuests; i++) {
      for (int e = 0; e < allSolns.at(i - 1).size(); e++) {
        tempStr = allSolns.at(i - 1).at(e) + (guests.at(i));
        tempVec.push_back(tempStr);
      }

      allSolns.push_back(tempVec);
      tempVec = {};

      // add swapped ending characters to the vector
      // 2 iterations before the current one

      if (i == 1) {
        tempStr = string() + guests.at(1) + guests.at(0);
        allSolns.at(1).push_back(tempStr);
      } else {
        for (int z = 0; z < allSolns.at(i - 2).size(); z++) {
          tempStr = allSolns.at(i - 2).at(z) + allSolns.at(i).at(0).at(i)
                    + allSolns.at(i).at(0).at(i - 1);
          allSolns.at(i).push_back(tempStr);
        }
      }
    }

    return allSolns.at(numGuests - 1);
  }


  vector<string> shuffle(string guests) {
    int numGuests = guests.length();
    string firstGuest;
    vector<string> baseCase;
    firstGuest.push_back(guests.at(0));
    baseCase.push_back(firstGuest);
    vector<vector<string>> allSolns;
    allSolns.push_back(baseCase);
    vector<string> tempVec;
    string tempStr;


    // loop through previous vector and append new character

    for (int i = 1; i < numGuests; i++) {
      // cout << "check 1" << std::endl;
      for (int e = 0; e < allSolns.at(i - 1).size(); e++) {
        tempStr = allSolns.at(i - 1).at(e) + (guests.at(i));
        tempVec.push_back(tempStr);
      }

      allSolns.push_back(tempVec);
      tempVec = {};

      // add swapped ending characters to the vector
      // 2 iterations before the current one

      if (i == 1) {
        tempStr = string() + guests.at(1) + guests.at(0);
        allSolns.at(1).push_back(tempStr);
      } else {
        for (int z = 0; z < allSolns.at(i - 2).size(); z++) {
          tempStr = allSolns.at(i - 2).at(z) + allSolns.at(i).at(0).at(i)
                    + allSolns.at(i).at(0).at(i - 1);

          allSolns.at(i).push_back(tempStr);
        }
      }
    }

    // add rotation only if numGuests > 2

    if (numGuests > 2) {
      tempStr = guests;

      // one rotation
      for (int p = 0; p < numGuests; p++) {
        // cout << p << std::endl;
        if (p == 0) {
          tempStr.at(p) = guests.at(numGuests - 1);
          // cout << tempStr << std::endl;
        } else {
          tempStr.at(p) = guests.at(p - 1);
        }
      }
      allSolns.at(numGuests - 1).push_back(tempStr);

      tempStr = guests;

      for (int p = 0; p < numGuests; p++) {
        if (p == numGuests - 1) {
          tempStr.at(p) = guests.at(0);
        } else {
          tempStr.at(p) = guests.at(p + 1);
        }
      }

      allSolns.at(numGuests - 1).push_back(tempStr);
    }

    // account for swapping the two at the end
    // (look for all that start with guests.at(0) and swap the ends)

    if (numGuests > 2) {
      for (int w = 0; w < allSolns.at(numGuests - 1).size(); w++) {
        if (allSolns.at(numGuests - 1).at(w).at(0) == guests.at(0)
            && allSolns.at(numGuests - 1).at(w).at(numGuests - 1)
            == guests.at(numGuests - 1)) {
          tempStr = allSolns.at(numGuests - 1).at(w);
          tempStr.at(0) = allSolns.at(numGuests - 1).at(w).at(numGuests - 1);
          tempStr.at(numGuests - 1) = allSolns.at(numGuests - 1).at(w).at(0);
          allSolns.at(numGuests - 1).push_back(tempStr);
        }
      }
    }

    return allSolns.at(numGuests - 1);
  }
  vector<string> shuffle_barriers(string guests, vector<int> barriers) {
    string dummyString;
    vector<string> subStrings;
    vector<vector<string>> allSubs;
    barriers.push_back(guests.size());
    vector<string> solnStrings;
    int startingIndex = 0;
    int numGuests = guests.size();
    bool flag = false;
    int flagNum = 0;

    if (barriers.at(0) == 0) {
      flag = true;
    }
    if (flag == true) {
      flagNum = 1;
    }

    for (int i = flagNum; i < barriers.size(); i++) {
      for (int x = startingIndex; x < barriers.at(i); x++) {
        dummyString.push_back(guests.at(x));
      }
      startingIndex = barriers.at(i);
      subStrings = shuffleFib(dummyString);
      allSubs.push_back(subStrings);
      dummyString = "";
    }

    dummyString = "";
    vector<string> dummyVec = allSubs.at(0);

    if (flagNum == 1) {
      dummyVec = allSubs.at(0);
      for (int p = 0; p < dummyVec.size(); p++) {
        dummyVec.at(p).insert(0, "|");
      }
    }

    vector<string> newDummy;
    int count = 0;

    // loop through number of barriers,
    // determines which vector we are in
    for (int e = 0; e < (allSubs.size() - 1); e++) {
      for (int x = 0; x < dummyVec.size(); x++) {
        for (int y = 0; y < allSubs.at(e + 1).size(); y++) {
          dummyString = dummyVec.at(x) + "|" + allSubs.at(e + 1).at(y);
          newDummy.push_back(dummyString);
        }
      }
      dummyVec = newDummy;
      newDummy = {};
    }

    // account for swaps

    string tempStr;

    if (numGuests > 2) {
      for (int j = 0; j < dummyVec.size(); j++) {
        if (dummyVec.at(j).at(0) == guests.at(0)
            && dummyVec.at(j).back() == guests.back()) {
          tempStr = dummyVec.at(j);
          tempStr.at(0) = guests.back();
          tempStr.back() = guests.at(0);
          dummyVec.push_back(tempStr);
        }
        tempStr = "";
      }
    }

    return dummyVec;
  }
};







// MAIN
// everything in your file after here will be
// replaced by this code.

// the rest of this file is code that will be
// used to test the Wedding class.

// it is recommended that you write your own
// test code to help you develop your solution


// show either a single element or all the elements
// in a vector


template<class T>
void show_result(vector<T> v, bool partial = false, int n = 0) {
  sort(v.begin(), v.end());
  cout << v.size() << "\n";
  if (partial) {
    cout << v.at(n) << "\n";
  } else {
    for (auto c : v) {
      for (auto e : c ) cout << e ;
      cout << "\n";
    }
  }
}


void standard_tests() {
  Wedding standard;
  vector<string> res;
  res = standard.shuffle("abc");
  show_result(res);

  res = standard.shuffle("WXYZ");
  show_result(res);


  res = standard.shuffle_barriers("xyz", {0});
  show_result(res);

  res = standard.shuffle("abc");
  show_result(res);

  res = standard.shuffle("abcdefXY");
  show_result(res);

  res = standard.shuffle_barriers("abcDEFxyz", {2, 5, 7});
  show_result(res);

  res = standard.shuffle_barriers("ABCDef", {4});
  show_result(res);

  res = standard.shuffle_barriers("bgywqa", {0, 1, 2, 4, 5});
  show_result(res);

  res = standard.shuffle_barriers("n", {0});
  show_result(res);
  res = standard.shuffle("hi");
  show_result(res);
}


int main(int argc, char const ** argv) {
  Wedding w;

  string asktype;
  string guests;
  int nbar, ind;
  vector<int> barriers;

  cout << "Type quit to exit.\n";
  cout << "Commands:\ntests\ns guests\nb guests n barriers\n";
  cout << "sp guests ind\nbp guests n barriers ind \n";

  while (true) {
    std::cin >> asktype;
    if (asktype == "quit") {
      break;
    } else  if (asktype == "tests") {
      standard_tests();
    } else if (asktype == "s") {
      cin >> guests;
      auto r = w.shuffle(guests);
      show_result(r);
    } else if (asktype == "b") {
      cin >> guests >> nbar;
      barriers.resize(nbar);
      for (int i = 0; i < nbar ; i++)
        cin >> barriers.at(i);
      auto r = w.shuffle_barriers(guests, barriers);
      show_result(r);
    } else if (asktype == "sp") {
      cin >> guests >> ind;
      auto r = w.shuffle(guests);
      show_result(r, true, ind);
    } else if (asktype == "bp") {
      cin >> guests >> nbar;
      barriers.resize(nbar);
      for (int i = 0; i < nbar ; i++)
        cin >> barriers.at(i);
      cin >> ind;
      auto r = w.shuffle_barriers(guests, barriers);
      show_result(r, true, ind);
    }
  }
}
