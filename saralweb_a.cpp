/*
================================================================
Create a input file in same folder which is containing this code.
Run the code.
Check the output file in the same folder.

================================================================
As the problem is a little bit open ended, I am assuming some things:-
    1. The words containing "'" are not allowed.
        Example didn't, couldn't etc.
    2. Down and down are considered to be different and have a common substring "own" only.

================================================================S
Algorithm
1. Break the given sentence into words and then store these words in a vecor string
2. Make a output storing data structure as vector<pair<string, vector<string>>> which stores 'the common substring'
    and 'the words containing this substring' in a pair.
3. For each word check wether it shares a common substring with another word or not.
    3.1. If yes, then find the common substring(having length>=4)and check wether it exist in result or not:-
        3.1.1. If common substring exist in result, then add current word.
        3.1.2. If don't exist, then create a new tuple having common substring in result's first argument
    3.2 If no, then create a new tuple having word in result's first argument

4. Print the second attribute of result and its size.
*/

#include<bits/stdc++.h>
using namespace std;

// checker function returns true if character c is alphabet(small or large) else false
bool checker(char c)
{
    if(c>=65 && c<=90)  return true;
    else if(c>=97 && c<=122)    return true;
    else
    {
        return false;
    }
}

// function to find the longest common substring
string find_com(string s1, string s2)
{
    string result = "";
    for(int i=0; i<s1.length(); i++)
    {
        for(int j=0; j<s2.length(); j++)
        {
            int k=0;
            string temp;

            while((i+k)<s1.length() && (j+k)<s2.length() && s1[i+k]==s2[j+k])
            {
                temp.push_back(s1[i+k]);
                k++;
            }

            if(result.length() < temp.length()) result = temp;
        }
    }

    return result;
}

bool checking_count(string s, vector<string>& store)
{
    // if(store.empty()) return true;
    for(int i=0; i<store.size(); i++)
    {
        if(store[i] == s)   return false;
    }
    return true;
}

int32_t main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

   //taking inputs
    string input;
    getline(cin, input);

    vector<string> v_input;

    //breaking input sentence into words and then storing those words in a vector string
    string temp;
    for(int i=0; i<input.length(); i++)
    {
        if(checker(input[i]))
        {
            temp.push_back(input[i]);
        }
        else{
            if(!temp.empty())    v_input.push_back(temp);
            temp = "";
        }
        if(!temp.empty() && i==input.length()-1)
        {
            v_input.push_back(temp);
        }
    }

    //our output storing data structure
    vector<pair<string, vector<string>>> result;

    for(int i=0; i<v_input.size(); i++)
    {
        vector<string> result_second = {v_input[i]};

        if(v_input[i].length()<4)
        {
            bool check2 = false;
            for(auto &y: result)
            {
                if(y.first==v_input[i])
                {
                    y.second.push_back(v_input[i]);
                    check2 = true;
                    break;
                }
            }
            if(!check2)   result.push_back({v_input[i], result_second});
        }
        else
        {
            vector<string> double_count_preventer;
            bool check1 = true;
            for(int j=0; j<v_input.size(); j++)
            {
                if(i==j)    continue;
                string common = find_com(v_input[i], v_input[j]);
                

                if(common.length()>=4)
                {
                    check1 = false;
                    if(checking_count(common, double_count_preventer))
                    {
                        bool check2 = true;
                        for(auto &y: result)
                        {
                            if(y.first==common)
                            {
                                y.second.push_back(v_input[i]);
                                check2 = false;
                                //for a given common string a word must make only one entry
                                double_count_preventer.push_back(common); 
                                break;
                            }
                        }
                        if(check2)
                        {
                            result.push_back({common, result_second});
                            //for a given common string a word must make only one entry
                            double_count_preventer.push_back(common); 
                        }
                    }
                }

            }
            if(check1) result.push_back({v_input[i], result_second});
        }
    }


    for(auto &x: result)
    {
        // cout<<"1. "<<x.first<<endl<<"2. ";
        for(int i=0; i<x.second.size(); i++)   cout<<x.second[i]<<" ";
        cout<<": "<<x.second.size()<<endl;
    }


    return 0;
}