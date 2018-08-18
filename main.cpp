#include <fstream>
#include <cerrno>
#include "flbw.h"

void show_help()
{
    printf("FLBW encryption algorithm usage :\n\n");
    printf("> For encryption :\n");
    printf("%s\n", "flbw enc password string");
    printf("%s\n", "flbw encf password file.txt [encrypted_destination.txt]");
    printf("%s\n\n", "flbw encbyf passwordfile.txt file.txt [encrypted_destination.txt]");
    printf("> For decryption :\n");
    printf("%s\n", "flbw dec password encryptedstring");
    printf("%s\n", "flbw decf password encryptedfile.txt [decrypted_destination.txt]");
    printf("%s\n", "flbw decbyf passwordfile.txt encryptedfile.txt [decrypted_destination.txt]");
    return;
}

int main(int argc, char **argv)
{
    if (argc >= 4)
    {
        FLBW flbw;
        std::string data = argv[3];
        std::string password = argv[2];
        if (strcmp(argv[1], "enc") == 0)
        {
            // Encrypt a string by string.
            std::string rst = flbw.flbw_encrypt(data, password);
            std::cout << rst << std::endl;
            if (flbw.get_error())
                std::cout << flbw.get_message() << std::endl;
            return (0);
        }
        else if (strcmp(argv[1], "dec") == 0)
        {
            // Decrypt a string by string.
            std::string rst = flbw.flbw_decrypt(data, password);
            std::cout << rst << std::endl;
            if (flbw.get_error())
                std::cout << flbw.get_message() << std::endl;
            return (0);
        }
        else if (strcmp(argv[1], "encf") == 0 || strcmp(argv[1], "decf") == 0 || strcmp(argv[1], "encbyf") == 0 || strcmp(argv[1], "decbyf") == 0)
        {
            // Encrypt a given file by string or a given file.
            std::ifstream infile{data};
            std::string file_contents{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};

            if (strcmp(argv[1], "encbyf") == 0 || strcmp(argv[1], "decbyf") == 0)
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
                if (strcmp(argv[1], "encf") == 0 || strcmp(argv[1], "encbyf") == 0)
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