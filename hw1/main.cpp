#include <iostream>
#include "BlockChain.h"
#include "Utilities.h"

enum arguments {
    PROGRAM,
    COMMAND,
    FILE_1,
    FILE_2,
    ARGS_COUNT
};

int main(int argc, char** argv)
{
    if (argc == ARGS_COUNT) {
        const string command = argv[COMMAND];
        ifstream source(argv[FILE_1]);
        if (source.is_open())
        {
            auto* blockChain = new BlockChain();
            *blockChain = BlockChainLoad(source);
            //the target file is the input file
            if (command == "verify") 
            {
                ifstream target(argv[FILE_2]);
                if (target.is_open())
                {
                    bool isVerified = BlockChainVerifyFile(*blockChain, target);
                    std::cout << "Verification " << (isVerified ? "passed" : "failed") << std::endl;
                    blockChain->deleteBlockChain(blockChain);
                }else{
                    blockChain->deleteBlockChain(blockChain);
                    return 1;
                }
            }else{
                //the target file is the output file
                ofstream target(argv[FILE_2]);
                if (target.is_open())
                {
                    if (command == "format") 
                    {
                        BlockChainDump(*blockChain, target);
                    }
                    else if (command == "hash") 
                    {
                        BlockChainDumpHashed(*blockChain, target);
                    }
                    else if (command == "compress") 
                    {
                        BlockChainCompress(*blockChain);
                        BlockChainDump(*blockChain, target);
                    }
                    else 
                    {
                        std::cout << getErrorMessage() << std::endl;
                    }
                    blockChain->deleteBlockChain(blockChain);
                }else{
                    blockChain->deleteBlockChain(blockChain);
                    return 1;
                }
                
            }
        }else{
            std::cout << getErrorMessage() << std::endl;
            return 1;
        }
    } else {
        std::cout << getErrorMessage() << std::endl;
    }
    return 0;
}

