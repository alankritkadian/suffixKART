#include <bits/stdc++.h>
#include <string.h>
#include "Suffix_tree.h"
#include "PatternSearch.h"
#include "bloom.hpp"
#include "BK_Tree.hpp"
using namespace std;
int main(void)
{
    vector<string> Items;
    bool bitarray[1000] = {false};
    int arrSize = 1000;
    int pos[100];
    BkNode* RootNode;
    string s1 = "";
    label:
    ofstream outputFile("output.txt", ios::app);
    outputFile << "Welcome to the grocery Store! ";
    outputFile<<"Please choose -1 for consumer end -2 for seller end -3 exit\n";
    outputFile.flush();
    int x;
    cin >> x;
    if (x == 1)
    {
        string name, item = "";
        outputFile << "Please enter your name: \n";
        outputFile.flush();
        cin >> name;
        int l = name.length();
        outputFile << "Enter items you want(enter \"end\" when you're done): \n";
        outputFile.flush();
        while (item != "end")
        {
            cin >> item;
            if (item != "end")
            {
                RootNode = ReturnBNode();
                vector<string> match = getSimilarWords(*RootNode, item);
                int found = 0;
                for (auto x : match)
                    if(x==item) found = 1;
                if(!found&&!match.empty()){
                    outputFile<<"It seems you mispelled. Enter the Index of the one you want from following Items: ";
                    for (auto x : match)
                        outputFile<<x<<" ";
                    outputFile<<endl;
                    outputFile.flush();
                    int index;cin>>index;
                    item = match[index-1];
                }else if(match.empty()){
                    outputFile<<"No such item or closely spelled item found.\n";
                    outputFile.flush();
                }   
                if(!match.empty()){    
                    outputFile << "Item Found! \n";   
                    outputFile.flush();      
                    s1.append(name + to_string(l));
                    s1.append(item);
                }
            }

        }
        outputFile << "Thank you " << name << '!' << endl;
        outputFile.flush();
        // outputFile << s1 << endl;
        outputFile.close();
        goto label;
    }
    else if (x == 2)
    {
        outputFile << "Please choose an operation: -1 for Updating Item -2 for Searching Item\n";
        outputFile.flush();
        int op2;
        cin >> op2;
        if (op2 == 1)
        {
            string s2;
            outputFile << "Please enter the Item name: \n";
            outputFile.flush();
            cin >> s2;
            if (insert(bitarray, arrSize, s2))
            {
                Items.push_back(s2);
                BkNode NodeOp2 = createNode(Items.at(Items.size()-1));
                RootNode = ReturnBNode();
                addNode(*RootNode,NodeOp2);
            }
        }
        else if (op2 == 2)
        {
            s1 += "$";
            int z = s1.size();
            char Text[z];  
            char temp[50];
            for (int i = 0; i < z; i++)
                Text[i] = s1[i];
            buildSuffixTree(Text); 
            outputFile<<"-1 To display Reciept -2 To Search \n";
            outputFile.flush();
            int h;cin>>h;
            string hero;
            if(h==2){
                outputFile<<"Enter the Item to be Searched: \n";
                outputFile.flush();
                cin>>hero;
            }
            for(auto x:Items){
                if(h==2) x = hero;
                int y = 0; 
                z = x.length();
                char Temp2[z+1];
                for(int i=0;i<z;i++) Temp2[i] = x[i]; 
                Temp2[z] = '\0';           
                SNode *root = returnRoot();
                checkForSubString(Temp2, root, Text,pos);
                outputFile<<"The Following have ordered "<<x<<": ";
                while(pos[y]!=-1){
                    // outputFile<<Text[pos[y]-1]<<" ";
                    int num = Text[pos[y]-1]-48;
                    int num2 = Text[pos[y]-2]-48;
                    // outputFile<<num<<" "<<num2<<" ";
                    int found = 0;
                    if(num2>=0&&num2<=9){
                        found = 1;
                        num = 10*(Text[pos[y]-2]-48)+(Text[pos[y]-1]-48);
                    }
                    // outputFile<<num<<" ";
                    for(int g = pos[y]-1-found-num;g<pos[y]-1-found;g++){
                        outputFile<<Text[g];
                    }
                    outputFile<<" ";
                    y++;
                }
                outputFile<<endl;
                outputFile.flush();
                if(h==2) break;
            }
            s1.pop_back();
            // pos[0] = -1;
        }
        outputFile.close();
        goto label;
    }
    return 0;
}