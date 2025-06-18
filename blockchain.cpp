#include <iostream>
#include <string>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

// custom base64 encoding of all alphabets plus . and space as i required them for atleast some better looking data
string base = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. ";
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
    int difficulty;
    unsigned long long int nonce;

    block_structure(string in_transac)
    {
        timestamp = std::time(nullptr);
        transaction = in_transac;
        difficulty = ((in_transac.length() + blockNo) % 32) / 4 + 6;
        next = nullptr;
    }
};

// This is the hashing function. I had to declare this before anything else cuz it was giving error. Hence (5) complete
string hash_function(block_structure *block)
{
    // This hashing function is a very simple function inspired from SHA256 algorithm which i read up before making this
    // This function has 4 parts ->
    // Initial hashes
    vector<unsigned int> hashes(4);
    hashes[0] = 0x12df9d06;
    hashes[1] = 0x71bd5b64;
    hashes[2] = 0x4881feef;
    hashes[3] = 0xca6a7e80;

    string new_transac = to_string(block->blockNo) + to_string(block->timestamp) + to_string(block->nonce) + block->prevHash + block->transaction; // Include all the data of the block to create hashes

    // Stretching input to be able to break it into fixed sized blocks of 256 characters
    int len = new_transac.size() % 256;
    while (len and len < 128 and new_transac.size() < 256)
    {
        new_transac += new_transac;
        len = new_transac.size() % 256;
    }
    new_transac += new_transac.substr(0, 256 - len);
    // Divide into blocks and store it into arrays
    unsigned long long int blocks = new_transac.size() / 256;
    vector<string> arr(blocks);
    for (unsigned long long int i = 0; i < blocks; i++)
        arr[i] = new_transac.substr(i * 256, 256);

    // for each block, there will be 4 4-byte hashes
    auto data_hashes = new unsigned int[blocks][4];
    // convert from string to integer using a custom base64 encoding which is defined by the base variable
    for (auto i = 0; i < blocks; i++)
    {
        auto x = arr[i];
        vector<string> data_arr(4);
        for (int j = 0; j < 4; j++)
        {
            // each block contains 4*32 characters
            // these 32-char chunks will each be converted into a hash for the block
            string data = x.substr(j * 32, 32);
            unsigned int data_hash = 0; // will contain one hash of the block during iteration

            for (int k = 0; k < 4; k++, data_hash <<= 8) // shift the hash 8 bits for new byte
            {
                // each 32-char chunks can be divided into 4 parts
                // each 8-char part will be one byte of the 4-byte hash
                string str = data.substr(k * 8, 8);

                unsigned int data_byte = 0;
                // due to the base selected, each char of the string gives out a 6bit value i.e. a value within 0-63
                // hence we take the value of each char and find if there's parity in it and include that as a bit
                // for each 8 characters, eventually making a byte for that 8 character part.

                for (auto x = str.begin(); x < str.end(); x++, data_byte <<= 1) // shift 1 place
                    data_byte |= findParity(base.find(*x));                     // add that parity bit.

                data_hash |= data_byte;
                // add the new byte to the hash
            }
            data_hashes[i][j] = data_hash;
        }
    }
    // combine all the hashes of the blocks
    for (int i = 0; i < blocks; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // didnt use auto as i couldn't couldn't reassign the variable even when initialized with a dummy function with similar return type and parameters
            unsigned int (*op)(unsigned int, unsigned int);
            // for a bit more randomness of operation
            switch ((i + j) % 3)
            {
            case 0:
            {
                op = [](unsigned int a, unsigned int b) -> unsigned int
                { return a & b; };
                break;
            }
            case 1:
            {
                op = [](unsigned int a, unsigned int b) -> unsigned int
                { return a | b; };
                break;
            }
            case 2:
            {
                op = [](unsigned int a, unsigned int b) -> unsigned int
                { return a ^ b; };
                break;
            }
            }
            hashes[j] = op(hashes[j], data_hashes[i][j]);
        }
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
        // just add it, no need to check
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
        for (unsigned long long int i = 0;; i++)
        {
            block->nonce = i;
            block->hash = hash_function(block);
            auto start = block->hash.begin();
            auto finish = block->hash.end();
            // Proof of work
            // basically the nonce has to be found such that (no. of 0) > block difficulty (taken from bitcoin's PoW definition)
            // the proof of work i have chosen is either letting it validate or it isn't for some reason, theres no inbetween
            // like its going to take a lot of time or
            if (count(start, finish, '0') <= block->difficulty)
                break;
        }
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

    head = add_block_to_chain(genesis, head);
    block_structure *new_block = new block_structure("2nd block");
    head = add_block_to_chain(new_block, head);
    display_blockchain(head);
    char opt = 'y';
    while (opt != 'n')
    {
        cout << "Want to add a node (y/n)? ";
        cin >> opt;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (opt == 'y')
        {
            string dat;
            cout << "Give data to add to blockchain: ";
            getline(cin, dat);
            block_structure *new_block = new block_structure(dat);
            head = add_block_to_chain(new_block, head);
            display_blockchain(head);
        }
    }
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