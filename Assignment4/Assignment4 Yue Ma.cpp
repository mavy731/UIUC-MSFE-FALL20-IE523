//
//  main.cpp
//  Stable Marriage Problem
//
//  Created by Ramavarapu Sreenivas on 8/29/14.
//  Copyright (c) 2014 Ramavarapu Sreenivas. All rights reserved.
//  IE523 HW4
//  Modified by Yue Ma

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class stable_marriage_instance
{
    // Private
    int no_of_couples;
    vector <vector <int> > Preference_of_men;
    vector <vector <int> > Preference_of_women;
    vector <int> match_for_men;
    vector <int> match_for_women;
    
    // private member function: checks if anybody is free in boolean "my_array"
    // returns the index of the first-person who is free in "my_array"
    // if no one is free it returns a -1.
    int anybody_free(vector <bool> my_array)
    {
        // fill the necessary code for this function
        int ans = -1;
        for (int i = 0; i < no_of_couples;i++) {
            if (my_array[i])
                ans = i;
        }

        return ans;
    }
    
    // private member function: if index1 is ranked higher than index2
    // in a preference array called "my_array" it returns "true"; otherwise
    // it returns "false"
    bool rank_check (vector <int> my_array, int index1, int index2)
    {
        // fill the necessary code for this function
        int ans;
        int m, n;
        m = 0;
        n = 0;
        for (int i = 0; i < no_of_couples;i++) {
            if (my_array[i] == index1) {
                m = i;
            }
            if (my_array[i] == index2) {
                n = i;
            }
        }
        if (m < n)
            return true;
        else
            return false;
    }
    
    // private member function: implements the Gale-Shapley algorithm
    void Gale_Shapley()
    {
        vector <bool> is_man_free;
        vector <bool> is_woman_free;
        vector <vector <bool> > has_this_man_proposed_to_this_woman;
        
        int man_index, woman_index;
        
        // initializing everything
        for (int i= 0; i < no_of_couples; i++)
        {
            // do the necessary initialization here
            is_man_free.push_back(true);
            is_woman_free.push_back(true);
            match_for_men.resize(no_of_couples);
            match_for_women.resize(no_of_couples);
            vector <bool> tmp;
            for (int j = 0;j < no_of_couples;j++) {
                tmp.push_back(false);
            }
            has_this_man_proposed_to_this_woman.push_back(tmp);
        }
        
        // Gale-Shapley Algorithm
        while ( (man_index = anybody_free(is_man_free)) >= 0)
        {
            // fill the necessary code here
            int woman_index;
            for (int j = 0;j < no_of_couples; j++) {
                int tmp;
                tmp = Preference_of_men[man_index][j];
                if (!has_this_man_proposed_to_this_woman[man_index][tmp]) {
                    woman_index = tmp;
                    has_this_man_proposed_to_this_woman[man_index][tmp] = true;
                    break;
                }
            }
            if (is_woman_free[woman_index]) {
                match_for_men[man_index] = woman_index;
                match_for_women[woman_index] = man_index;
                is_man_free[man_index] = false;
                is_woman_free[woman_index] = false;
            }
            else {
                int fiance;
                fiance = match_for_women[woman_index];
                if (rank_check(Preference_of_women[woman_index],man_index, fiance)) {
                    match_for_men[man_index] = woman_index;
                    match_for_women[woman_index] = man_index;
                    is_man_free[man_index] = false;
                    is_woman_free[woman_index] = false;
                    is_man_free[fiance] = true;
                    match_for_men[fiance] = 0;
                }
                else {
                    is_man_free[man_index] = true;
                }
            }
        }
    }
    
    // private member function: reads data
    void read_data(int argc, const char * argv[])
    {
        // fill the necessary code here.  The first entry in the input
        // file is the #couples, followed by the preferences of the men
        // and preferences of the women.  Keep in mind all indices start
        // from 0.
        ifstream input_file(argv[1]);
        int m;
           
        if (argc > 1) {
            if (input_file.is_open()) {
                input_file >> m;
                no_of_couples = m;
                cout << "Number of Couples = " << no_of_couples << endl;
                cout << "Preference of Men" << endl;
                cout << "-----------------" << endl;
                for (int i = 0;i < no_of_couples;i++) {
                    vector <int> pref;
                    for (int j = 0; j < no_of_couples;j++) {
                        input_file >> m;
                        pref.push_back(m);
                        cout << pref[j] << " ";
                    }
                    Preference_of_men.push_back(pref);
                    cout << endl;
                }
                cout << "Preference of Women" << endl;
                cout << "-----------------" << endl;
                for (int i = 0;i < no_of_couples;i++) {
                    vector <int> pref;
                    for (int j = 0; j < no_of_couples;j++) {
                        input_file >> m;
                        pref.push_back(m);
                        cout << m << " ";
                    }
                    Preference_of_women.push_back(pref);
                    cout << endl;
                }
            }
        }

    }
    
    // private member function: print solution
    void print_soln()
    {
        // write the appropriate code here
        cout << endl;
        cout << "Matching for Men" << endl;
        for (int i = 0; i < no_of_couples;i++) {
            cout << "Man: " << i << " -> Woman: " << match_for_men[i] << endl;
        }
        cout << endl;
        cout << "Matching for Women" << endl;
        for (int i = 0; i < no_of_couples;i++) {
            cout << "Woman: " << i << " -> Man: " << match_for_women[i] << endl;
            
        }
    }
    
public:
    void solve_it(int argc, const char * argv[])
    {
        read_data(argc, argv);

        Gale_Shapley();

        print_soln();
    }
};

int main(int argc, const char * argv[])
{
    stable_marriage_instance x;
    x.solve_it(argc, argv);
}

