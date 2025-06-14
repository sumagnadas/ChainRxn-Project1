#include<iostream>
#include<string>
#include<ctime>
using namespace std;

/*
    Overall structure:
    1) block structure (struct or class)
    2) Create a new block (but not add it)
    3) Add the newly minted block
    4) print the entire chain
    5) get a hashing function to create a hash

    Feel fee to change the function parameters as per your requirement

*/

// This is the hashing function. I had to declare this before anything else cuz it was giving error. Hence (5) complete
string hash_function(string transac){
    string hash = "0x";
    
    // over here there will be the logic for making a hash function
    // feel free to do anything over here
    // and all hashes are supposed to begin with a '0x'

    return hash;
}

// I have gone with a class but you can do the same by using struct
// Only you would have to create a function "create_block" to, well, create new blocks but not add them to the chain
class block_structure{
public:
    int blockNo;
    time_t timestamp;
    string transaction;
    string prevHash;
    string hash;
    block_structure* next;

    block_structure(string in_transac){
        timestamp = std::time(nullptr);
        transaction = in_transac;
        next = NULL;
    }

};


block_structure* add_block_to_chain(block_structure* block, block_structure* head){
   
    // this function adds the new block to blockchain
    // JUST A GOOD LONG NOTE:
        // Since i have used a class above, when i create an object with in the class, i am automatically creating a new block
        // The only thing that is left to do is add it hence there would be no apparent "create_block" function

    return head;
}


void display_blockchain(block_structure* head){

    //This function lists out all the blocks in over blockchain by visiting it one after the next

    block_structure* temp = head;
    while(temp != NULL){
        cout << "******************************************\n";
        cout << "Block No: " << temp->blockNo << endl;
        cout << "Transaction encased: " << temp->transaction << endl;
        cout << "Time of creation: " << ctime(&(temp->timestamp)) << endl;
        
        // See that that we have used ctime and time_t in this case. Search this throughly before using it!
        
        temp = temp->next;
    }
    return;
}


int main(){

    // over here goes how the chain is to interact with the user
    // write some code over here to do the following:
    //  [in short, just call the functions that lead to these tasks]
    //  1) create the 1st block of blockchain (genesis block) and subsequent blocks
    //      (a) Remember to take the transaction from the user and pass it on to the block

    //  2) add them to the chain

    //  3) print the entire chain with the block no, transaction that it holds, and when it was made  

    // RECOMMENDED BUT ENTIRELY OPTIONAL:
    //      delete the chain so as to cleanly free up memory

    return 0;
}