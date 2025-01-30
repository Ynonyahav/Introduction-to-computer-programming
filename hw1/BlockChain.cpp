#include "BlockChain.h"

//****************************************************************************//

void insertData(BlockChain& block, const Transaction& transaction,
    const string& timestamp)
{
    block.transaction = transaction;
    block.timestamp = timestamp;
    block.next = nullptr;
}

//****************************************************************************//

void newBlockHead(BlockChain& head, const Transaction& transaction,
    const string& timestamp)
{
    auto* newBlock = new BlockChain();
    *newBlock = head;
    insertData(head, transaction, timestamp);
    head.next = newBlock;
}

//****************************************************************************//

void newBlockTail(BlockChain& tail, const Transaction& transaction,
    const string& timestamp)
{
    auto* newBlock = new BlockChain();
    insertData(*newBlock, transaction, timestamp);
    tail.next = newBlock;
}

//****************************************************************************//

void BlockChain::deleteBlockChain(const BlockChain* head)
{
    while(head) {
        const BlockChain* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

//****************************************************************************//

int BlockChainGetSize(const BlockChain& blockChain)
{
    int size = 0;
    for (const BlockChain* current = &blockChain;
        current != nullptr && !current->timestamp.empty();
        current = current->next){
        size++;
    }
    return size;
}

//****************************************************************************//

int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name)
{
    if (!BlockChainGetSize(blockChain)) {
        std::cerr << "BlockChain is EMPTY! /Balance" << std::endl;
        return 0;
    }
    int balance = 0;
    for (const BlockChain* current = &blockChain;
        current != nullptr && !current->timestamp.empty();
        current = current->next){
        if (current->transaction.receiver == name){
            balance += current->transaction.value;
        }
        if (current->transaction.sender == name){
            balance -= current->transaction.value;
        }
    }
    return balance;
}

//****************************************************************************//

void BlockChainAppendTransaction(
        BlockChain& blockChain,
        const Transaction& transaction,
        const string& timestamp
)
{
    if (blockChain.timestamp.empty()) {
        insertData(blockChain, transaction, timestamp);
    }
    else{
        newBlockHead(blockChain, transaction, timestamp);
    }
}

//****************************************************************************//

void BlockChainAppendTransaction(
        BlockChain& blockChain,
        unsigned int value,
        const string& sender,
        const string& receiver,
        const string& timestamp
)
{
    const Transaction transaction = {value, sender, receiver};
    BlockChainAppendTransaction(blockChain, transaction, timestamp);
}

//****************************************************************************//

BlockChain BlockChainLoad(ifstream& file)
{
    Transaction transaction;
    string timestamp;
    BlockChain blockChain;
    BlockChain* tail = &blockChain;
    blockChain.next = tail;
    bool first = true;

    while (file  >> transaction.sender >> transaction.receiver
            >> transaction.value >> timestamp) {
        if (first) {
            insertData(blockChain, transaction, timestamp);
            first = false;
        }
        else {
            newBlockTail(*tail, transaction, timestamp);
            tail = tail->next;
        }
    }
    return blockChain;
}

//****************************************************************************//
//TO CHECK: We can assume that the input is correct 
void BlockChainDump(const BlockChain& blockChain, ofstream& file)
{
    int rank = 1;
    file << "BlockChain Info:" << std::endl;
    for (const BlockChain* current = &blockChain;
        current != nullptr && !current->timestamp.empty();
        current = current->next) {
        file << rank << "." << std::endl;
        TransactionDumpInfo(current->transaction, file);
        file << "Transaction timestamp: " << current->timestamp << std::endl;
        rank++;
    }
}

//****************************************************************************//
//TO CHECK: We can assume that the input is correct 
void BlockChainDumpHashed(const BlockChain& blockChain, ofstream& file)
{
    if (BlockChainGetSize(blockChain) == 0){
        std::cerr << "BlockChain is EMPTY! /Hushed" << std::endl;
    }
    const BlockChain* current = &blockChain;
    while(!current->timestamp.empty()) {
        file << TransactionHashedMessage(current->transaction);
        if (current->next == nullptr) break;
        file << std::endl;
        current = current->next;
    }
}

//****************************************************************************//

//Helper function for the next BlockChainVrifyFile function
int CountHashedMessages(std::ifstream& file) {
    //Saves the current cursor position (maybe the cursor isn't on the begining)
    const std::streampos currentPosition = file.tellg();
    int hashedCount = 0;
    string hashedMessage;
    //Reading and counting the lines until eof reached
    while (std::getline(file, hashedMessage)) {
        hashedCount++;
    }
    //Clears the stream eof flag for this file
    file.clear();
    //Moving the cursor to the start position
    file.seekg(currentPosition, std::ios::beg);
    return hashedCount;
}

//****************************************************************************//
//TO CHECK: We can assume that the input is correct 
bool BlockChainVerifyFile(const BlockChain& blockChain, std::ifstream& file)
{
    if(BlockChainGetSize(blockChain) == 0){
        std::cerr << "BlockChain is EMPTY! /Compress" << std::endl;
        return false;
    }
    const int blocksCount = BlockChainGetSize(blockChain);
    const int hashedCount = CountHashedMessages(file);
    if (blocksCount != hashedCount){
        return false;
    }
    if (blocksCount == 0 && hashedCount == 0){
        return true;
    } 

    string hashedMessage;
    for (const BlockChain* current = &blockChain; current != nullptr;
            current = current->next){
        getline(file, hashedMessage);
        if (hashedMessage != TransactionHashedMessage(current->transaction)) {
            return false;
        }
    }
    return true;
}

//****************************************************************************//

void BlockChainCompress(BlockChain& blockChain)
{
    if(BlockChainGetSize(blockChain) == 0){
        std::cerr << "BlockChain is EMPTY! /Compress" << std::endl;
        return;
    }
    for (BlockChain* current = &blockChain;
        current != nullptr && current->next != nullptr;
        current = current->next) {
        while(current->transaction.sender == current->next->transaction.sender &&
            current->transaction.receiver == current->next->transaction.receiver) {
            current->transaction.value += current->next->transaction.value;
            const BlockChain* tempNext = current->next;
            current->next = current->next->next;
            delete tempNext;
            if (current->next == nullptr){
                break;
            } 
        }
    }
}

//****************************************************************************//

//TO CHECK: We can assume that the input is correct 
void BlockChainTransform(BlockChain& blockChain, updateFunction function)
{
    if(BlockChainGetSize(blockChain) == 0){
        std::cerr << "BlockChain is EMPTY! /Transform" << std::endl;
        return;
    }
    for (BlockChain* current = &blockChain;
        current != nullptr && !current->timestamp.empty();
        current = current->next) {
        current->transaction.value = function(current->transaction.value);
    }
}

//****************************************************************************//

unsigned int TimesTwo(const unsigned int value)
{
    return value * 2;
}