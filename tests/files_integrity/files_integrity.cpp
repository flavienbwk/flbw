/*
 * FLBW encryption algorithm. Files Integrity Test Program :
 * 
 * This program retrieves the content of all the files in ./files.
 * The hash of the content will be compared to the FLBW decrypted string of the FLBW encrypted file content.
 * 
 * Passwords are randomly generated (1 to 4096 characters) for each file found.
 * 
 * Condition for success : ALL decrypted hashes must be identical to their respective originally encrypted content hashes.
 * Checking method : the originally generated file content hash will be compared with the decrypted file content attempt hash (SHA1 will be used and is suffisent). 
 * 
 */

#include <fstream>
#include <vector>
#include <cerrno>
#include <assert.h>
#include <dirent.h>
#include <sys/time.h>
#include "../../flbw.h"

int rand_vals(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

std::string randomString(int max_length)
{
    std::string rand_string = "";
    int length = rand_vals(1, max_length);
    std::string char_index = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890&é'(-éè_çà@)=+/#ù*£$€,.:;!§/.?^\"\n \r\f";

    for (int a = 0; a < length; a++)
        rand_string += char_index[rand_vals(0, (int)char_index.length() - 1)];
    return (rand_string);
}

std::string readFile(const char *filename)
{
    long int size = 0;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fputs("File error.\n", stderr);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    char *result = (char *)malloc(size);
    if (!result)
    {
        fputs("Memory error.\n", stderr);
        return NULL;
    }
    if (fread(result, 1, size, file) != size)
    {
        fputs("Read error.\n", stderr);
        return NULL;
    }
    fclose(file);
    return std::string(result);
}

int main(int argc, char **argv)
{
    FLBW flbw;
    srand(time(NULL));
    struct dirent *de;
    int nb_passwords_characters = 4096;
    int test_ok = 0, test_ko = 0, test_no = 0;
    int i = 0;
    std::string file, file_path;
    std::string str, str_hash, password;
    std::string str_enc;
    std::string str_dec, str_dec_hash;
    clock_t time_start, time_end;
    time_start = clock();

    DIR *dr = opendir("./tests/files_integrity/files");
    if (dr == NULL)
    {
        printf("Could not open current directory.\n");
        return (1);
    }

    while ((de = readdir(dr)) != NULL)
    {
        file = std::string(de->d_name);
        if (file.compare(".") != 0 && file.compare("..") != 0)
        {
            i++;
            file_path = "./tests/files_integrity/files/" + file;
            str = readFile(file_path.c_str());
            if (str.length())
            {
                printf("Test for %s of size %d > ", file.c_str(), (int)str.length());
                password = randomString(nb_passwords_characters);
                str_hash = flbw.fn_sha1(str);
                str_enc = flbw.flbw_encrypt(str, password);
                str_dec = flbw.flbw_decrypt(str_enc, password);
                str_dec_hash = flbw.fn_sha256(str_dec);
                if (str_dec_hash.compare(str_hash) != 0)
                {
                    printf("OK.\n");
                    test_ok++;
                }
                else
                {
                    test_ko++;
                    printf("String %d>\n---STR---\n%s\n---PWD---\n%s\n---DEC---\n%s\n", i + 1, str.c_str(), password.c_str(), str_dec_hash.c_str());
                }
            }
            else
            {
                test_no++;
                printf("Impossible to open : %s\n", file.c_str());
            }
        }
    }

    time_end = clock();
    printf("\n====Results====\n");
    printf("\nOK : %i", test_ok);
    printf("\nKO : %i", test_ko);
    printf("\n-- : %i", test_no);
    printf("\n(%.5f %% fail) in %f seconds.\n", (((double)test_ko * 100) / (double)test_ok), (((double)time_end - (double)time_start) / CLOCKS_PER_SEC));
    if (test_ko == 0)
        printf(">> SUCCESS <<\n");
    else
        printf("!! FAILURE, PLEASE REPORT !!\n");
    return (0);
}