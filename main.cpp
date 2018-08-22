#include <fstream>
#include <cerrno>
#include "flbw.h"

bool is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void show_help()
{
    printf("FLBW encryption algorithm usage :\n\n");
    printf("> For encryption :\n");
    printf("%s\n", "flbw enc[bp 250000] password string");
    printf("%s\n", "flbw encf[bp 250000] password file.txt [encrypted_destination.txt]");
    printf("%s\n\n", "flbw encbyf[bp 250000] passwordfile.txt file.txt [encrypted_destination.txt]");
    printf("> For decryption :\n");
    printf("%s\n", "flbw dec[bp 250000] password encryptedstring");
    printf("%s\n", "flbw decf[bp 250000] password encryptedfile.txt [decrypted_destination.txt]");
    printf("%s\n", "flbw decbyf[bp 250000] passwordfile.txt encryptedfile.txt [decrypted_destination.txt]");
    printf("\nYou can change '250000' by the bruteforce protection value you want.\n");
    return;
}

int main(int argc, char **argv)
{
    if (argc >= 4)
    {
        FLBW flbw;
        std::string data = argv[3];
        std::string password = argv[2];
        std::string choice_o = std::string(argv[1]);
        std::string choice;

        // Bruteforce protection use.
        if (choice_o.length() > 2 && choice_o.substr(choice_o.length() - 2, choice_o.length() - 1).compare("bp") == 0)
        {
            choice = choice_o.substr(0, choice_o.length() - 2);
            flbw.set_bruteforce_protection(true);
            if (argc >= 5)
            {
                if (is_number(argv[2]) && std::stoi(argv[2]) >= 0)
                    flbw.set_bruteforce_difficulty(std::stoi(argv[2]));
                else
                {
                    printf("%sInvalid bruteforce protection difficulty.%s\n\n", C_RED, C_RESET);
                    show_help();
                    return (1);
                }
            }
            else
            {
                printf("%sBruteforce protection difficulty not specified.%s\n\n", C_RED, C_RESET);
                show_help();
                return (1);
            }
        }
        else
        {
            choice = choice_o;
            flbw.set_bruteforce_protection(false);
        }

        // Encryption/Decryption modes.
        if (strcmp(choice.c_str(), "enc") == 0)
        {
            std::string rst = flbw.flbw_encrypt(data, password);
            std::cout << rst << std::endl;
            if (flbw.get_error())
                std::cout << flbw.get_message() << std::endl;
            return (0);
        }
        else if (strcmp(choice.c_str(), "dec") == 0)
        {
            std::string rst = flbw.flbw_decrypt(data, password);
            std::cout << rst << std::endl;
            if (flbw.get_error())
                std::cout << flbw.get_message() << std::endl;
            return (0);
        }
        else if (strcmp(choice.c_str(), "encf") == 0 || strcmp(choice.c_str(), "decf") == 0 || strcmp(choice.c_str(), "encbyf") == 0 || strcmp(choice.c_str(), "decbyf") == 0)
        {
            std::ifstream infile{data};
            std::string file_contents{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};

            if (strcmp(choice.c_str(), "encbyf") == 0 || strcmp(choice.c_str(), "decbyf") == 0)
            {
                std::ifstream file_contents_pwd(argv[2], std::ios::in | std::ios::binary | std::ios::ate);
                if (file_contents_pwd.is_open())
                {
                    file_contents_pwd.seekg(0, std::ios::end);
                    std::streampos size = file_contents_pwd.tellg();
                    char *contents = new char[size];
                    file_contents_pwd.seekg(0, std::ios::beg);
                    file_contents_pwd.read(contents, size);
                    file_contents_pwd.close();
                    password = std::string(contents);
                }
                else
                {
                    printf("%sEmpty or invalid password file.%s\n", C_RED, C_RESET);
                    return (1);
                }
            }

            if (file_contents.length())
            {
                std::string rst;
                if (strcmp(choice.c_str(), "encf") == 0 || strcmp(choice.c_str(), "encbyf") == 0)
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
                return (0);
            }
            else
                printf("%sEmpty or invalid file.%s\n", C_RED, C_RESET);
        }
        else
        {
            printf("%sInvalid mode selected (%s).%s\n\n", C_RED, argv[1], C_RESET);
            show_help();
        }
    }
    else
        show_help();
    return (1);
}