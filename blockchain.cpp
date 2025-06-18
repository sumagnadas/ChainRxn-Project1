#include <iostream>
#include <string>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;
string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. ";
/*
    Overall structure:
    1) block structure (struct or class)
    2) Create a new block (but not add it)
    3) Add the newly minted block
    4) print the entire chain
    5) get a hashing function to create a hash

    Feel fee to change the function parameters as per your requirement

*/
int findParity(int x)
{
    int parity = 0;
    while (x)
    {
        parity = !parity;
        x >>= 1;
    }
    return parity;
}
// I have gone with a class but you can do the same by using struct
// Only you would have to create a function "create_block" to, well, create new blocks but not add them to the chain
class block_structure
{
public:
    unsigned long long int blockNo;
    time_t timestamp;
    string transaction;
    string prevHash;
    string hash;
    block_structure *next;
    unsigned long long int nonce;

    block_structure(string in_transac)
    {
        timestamp = std::time(nullptr);
        transaction = in_transac;
        next = nullptr;
    }
};

// This is the hashing function. I had to declare this before anything else cuz it was giving error. Hence (5) complete
string hash_function(block_structure *block) //,string prevHash,string hash,unsigned long long int nonce)
{
    vector<unsigned int> hashes(4);
    hashes[0] = 0x12df9d06;
    hashes[1] = 0x71bd5b64;
    hashes[2] = 0x4881feef;
    hashes[3] = 0xca6a7e80;
    string new_transac = to_string(block->blockNo) + to_string(block->timestamp) + block->prevHash + block->transaction + to_string(block->nonce);
    int len = new_transac.size() % 256;
    while (len and len < 128 and new_transac.size() < 256)
    {
        new_transac += new_transac;
        len = new_transac.size() % 256;
    }
    new_transac += new_transac.substr(0, 256 - len);
    unsigned long long int blocks = new_transac.size() / 256;
    vector<string> arr(blocks);
    for (unsigned long long int i = 0; i < blocks; i++)
    {
        arr[i] = new_transac.substr(i * 256, 256);
    }
    auto data_hashes = new unsigned int[blocks][4];
    for (auto i = 0; i < blocks; i++)
    {
        auto x = arr[i];
        vector<string> data_arr(4);
        for (int j = 0; j < 4; j++)
        {
            string data = x.substr(j * 32, 32);
            unsigned int data_hash = 0;
            for (int k = 0; k < 4; k++)
            {
                string str = data.substr(k * 8, 8);

                unsigned int data_byte = 0;
                for (auto x : str)
                {
                    data_byte |= findParity(chars.find(x));
                    data_byte <<= 1;
                }
                data_hash |= data_byte;
                data_hash <<= 8;
            }
            data_hashes[i][j] = data_hash;
        }
    }
    for (int i = 0; i < blocks; i++)
    {
        for (int j = 0; j < 4; j++)
            hashes[j] ^= data_hashes[i][j];
    }
    char new_hash[35];
    sprintf(new_hash, "0x%08x%08x%08x%08x", hashes[0], hashes[1], hashes[2], hashes[3]);
    return new_hash;
}

block_structure *add_block_to_chain(block_structure *block, block_structure *head)
{

    // this function adds the new block to blockchain
    // JUST A GOOD LONG NOTE:
    // Since i have used a class above, when i create an object with in the class, i am automatically creating a new block
    // The only thing that is left to do is add it hence there would be no apparent "create_block" function
    if (head == nullptr)
    {
        head = block;
        block->hash = hash_function(block);
    }
    else
    {
        block_structure *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        block->prevHash = temp->hash;
        block->blockNo = temp->blockNo + 1;
        unsigned long long int nonce = rand();
        block->hash = hash_function(block);
        block->nonce = nonce;
        temp->next = block;
    }
    return head;
}

void display_blockchain(block_structure *head)
{

    // This function lists out all the blocks in over blockchain by visiting it one after the next

    block_structure *temp = head;
    while (temp != NULL)
    {
        cout << "******************************************\n";
        cout << "Block No: " << temp->blockNo << endl;
        cout << "Previous block's hash: " << temp->prevHash << endl;
        cout << "This block's hash: " << temp->hash << endl;
        cout << "Transaction encased: " << temp->transaction << endl;
        cout << "Nonce: " << temp->nonce << endl;
        cout << "Time of creation: " << ctime(&(temp->timestamp)) << endl;

        // See that that we have used ctime and time_t in this case. Search this throughly before using it!
        temp = temp->next;
    }
    return;
}
void del_blockchain(block_structure *head)
{
    block_structure *temp = head;

    while (temp != NULL)
    {
        auto next = temp->next;
        delete temp;
        temp = next;
    }
}

block_structure *head = nullptr;
int main()
{
    block_structure *genesis = new block_structure("First block");
    genesis->prevHash = string("0x12df9d0671bd5b644881feefca6a7e80");
    genesis->nonce = 1234;
    genesis->blockNo = 0;
    // cout << hash_function("1abracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichuabracadabragiliglichu") << endl;
    head = add_block_to_chain(genesis, head);
    block_structure *new_block = new block_structure("2nd block");
    head = add_block_to_chain(new_block, head);
    display_blockchain(head);
    // over here goes how the chain is to interact with the user
    // write some code over here to do the following:
    //  [in short, just call the functions that lead to these tasks]
    //  1) create the 1st block of blockchain (genesis block) and subsequent blocks
    //      (a) Remember to take the transaction from the user and pass it on to the block

    //  2) add them to the chain

    //  3) print the entire chain with the block no, transaction that it holds, and when it was made

    // RECOMMENDED BUT ENTIRELY OPTIONAL:
    //      delete the chain so as to cleanly free up memory
    del_blockchain(head);

    return 0;
}