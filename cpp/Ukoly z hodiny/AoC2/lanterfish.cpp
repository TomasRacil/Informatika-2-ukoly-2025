#include <iostream>
#include <vector>

using namespace std;

void den(vector<int>& ryby){
    size_t q = ryby.size();
    for (size_t i = 0; i < q; i++)
    {
        if (ryby[i] == 0){
            ryby[i] = 6;
            ryby.push_back(8);
        }
        else{
            --ryby[i];
        }
        //cout << ryby.size();

        for (int ryba : ryby){
        cout << ryba << " ";
        }
        cout << "  konec dne  ";
    }
    
}

int main(){
    vector<int> ryby = {3,4,3,1,2};

    for (int d = 0; d < 5; d++){
        den(ryby);
    }
}