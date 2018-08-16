#include <fstream>
#include <cerrno>
#include "flbw.h"

int main(int argc, char **argv)
{
    if (argc >= 4)
    {
        FLBW flbw;
        std::string data = argv[3];
        std::string password = argv[2];
        if (strcmp(argv[1], "1") == 0)
        {
            // Encrypt by given parameter.
            std::string rst = flbw.flbw_encrypt(data, password);
            std::cout << rst << std::endl;
            if (flbw.get_error())
                std::cout << flbw.get_message() << std::endl;
            // std::cout << "\nIn: " << std::to_string(flbw.get_execution_time()) << " seconds." << std::endl;
            return (0);
        }
        else if (strcmp(argv[1], "2") == 0)
        {
            // Decrypt by given parameter.
            std::string rst = flbw.flbw_decrypt(data, password);
            std::cout << rst << std::endl;
            if (flbw.get_error())
                std::cout << flbw.get_message() << std::endl;
            // std::cout << "\nIn: " << std::to_string(flbw.get_execution_time()) << " seconds." << std::endl;
            return (0);
        }
        else if (strcmp(argv[1], "3") == 0 || strcmp(argv[1], "4") == 0)
        {
            // Encrypt by given file.
            std::ifstream infile{data};
            std::string file_contents{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};
            if (file_contents.length())
            {
                std::string rst;
                if (strcmp(argv[1], "3") == 0)
                    rst = flbw.flbw_encrypt(file_contents, password);
                else
                    rst = flbw.flbw_decrypt(file_contents, password);
                if (argc >= 5 && rst.length())
                {
                    FILE *fp = fopen(argv[4], "w");
                    if (fp == NULL)
                    {
                        if (errno == EACCES)
                            std::cerr << "While writing result : permission denied" << std::endl;
                        else
                            std::cerr << "While writing result : something went wrong: " << strerror(errno) << std::endl;
                        fclose(fp);
                        return (1);
                    }
                    else
                    {
                        fclose(fp);
                        std::ofstream file;
                        file.open(argv[4]);
                        file << rst;
                        file.close();
                    }
                }
                else
                    std::cout << rst << std::endl;
                if (flbw.get_error())
                    std::cout << flbw.get_message() << std::endl;
                // std::cout << "\nIn: " << std::to_string(flbw.get_execution_time()) << " seconds." << std::endl;
                return (0);
            }
            else
                printf("%s%s%s\n", C_RED, "Empty or invalid file.", C_RESET);
        }
        else
            printf("%s%s%s\n", C_RED, "Invalid mode selected.", C_RESET);
    }
    else
        printf("%s%s%s\n", C_RED, "Please provide the 3 arguments : 1/2, password, text.", C_RESET);
    return (1);
}