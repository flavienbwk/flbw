/*
 * FLBW encryption algorithm. Random Attack Test Program :
 * 
 * For a sequence of 50 randomly generated strings (between 1 & 16384 characters), generating and checking decryption for 500 test passwords (between 1 & 4096 characters).
 * 
 * The strings generated will for each, be encrypted with one randomly generated password. 
 * This password will be compared to the test passwords used to try to decrypt the string and they'll be ignored if they are the same. 
 * 
 * Condition for success : NO test password must be able to decrypt the encrypted strings.
 * Checking method : the originally generated string hash will be compared with the decrypted string attempt hash (SHA1 will be used and is suffisent). 
 * 
 */

#include <fstream>
#include <vector>
#include <cerrno>
#include <sys/time.h>
#include "../flbw.h"

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

int main(int argc, char **argv)
{
    FLBW flbw;
    srand(time(NULL));
    int md_indicator = 100;
    int nb_strings = 50;
    int nb_passwords = 500;
    int nb_strings_characters = 16384;
    int nb_passwords_characters = 4096;
    int test_ok = 0, test_ko = 0, test_no = 0;
    int a, i;
    std::string master_password = "I am just a password !";
    std::string master_password_hash = flbw.fn_sha256(master_password);
    std::string str, str_hash, password, password_hash;
    std::string str_enc;
    std::string str_dec, str_dec_hash;
    clock_t time_start, time_end;
    time_start = clock();

    for (i = 0; i < nb_strings; i++)
    {
        str = randomString(nb_strings_characters);
        str_hash = flbw.fn_sha256(str);
        str_enc = flbw.flbw_encrypt(str, master_password);

        for (a = 0; a < nb_passwords; a++)
        {
            password = randomString(nb_passwords_characters);
            password_hash = flbw.fn_sha256(password);
            if (password_hash.compare(master_password_hash) != 0)
            {
                str_dec = flbw.flbw_encrypt(str_enc, password);
                str_dec_hash = flbw.fn_sha256(str_dec);
                if (str_dec_hash.compare(str_hash) != 0)
                {
                    test_ok++;
                    //std::cout << "OK." << std::endl;
                }
                else
                {
                    test_ko++;
                    printf("\nString %d>%d>\n---STR---\n%s\n---PWD---\n%s\n---DEC---\n%s", i + 1, a, str.c_str(), password.c_str(), str_dec_hash.c_str());
                }
            }
            else
            {
                test_no++;
                std::cout << "--. same passwords." << std::endl;
            }
            if (a % md_indicator == 0)
                printf("String %d> password attempt %d\n", i + 1, a);
        }
        printf("String %d> password attempt %d reached.\n", i + 1, a);
        printf("\n");
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
}