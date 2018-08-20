/*
 * FLBW encryption algorithm. Integrity Benchmark Test Program :
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
    srand(time(NULL));
    clock_t time_start, time_end;
    int nb_strings_generated = 500;
    int strings_max_length = 32768;
    int passwords_max_length = 4096;

    FLBW flbw;
    int random, integrity_ok, integrity_ko;
    std::string hash_start;
    std::string hash_end;
    std::vector<std::string> rst_encrypted, rst_decrypted, hashs_start, hashs_end;
    std::string password;
    std::vector<std::string> passwords, strings;
    std::vector<double> bchm_enc, bchm_dec, integrity;
    double bchm_avg_enc, bchm_avg_dec, bchm_sum, bchm_cps, time_total;
    int bchm_sum_chars;

    integrity_ok = 0;
    integrity_ko = 0;
    time_start = clock();
    strings = {""};
    for (int i = 0; i < nb_strings_generated; i++)
    {
        // Generating random strings.
        strings.push_back(randomString(strings_max_length));
    }

    printf("\n\nFLBW version %s", flbw.get_version().c_str());
    printf("\n\n====\nIntegrity checks:\n====\n\n");

    for (int i = 0; i < strings.size(); i++)
    {
        FLBW flbw_enc;
        FLBW flbw_dec;

        password = randomString(passwords_max_length);
        passwords.push_back(password);
        hash_start = flbw.fn_sha256(strings[i]);

        rst_encrypted.push_back(flbw_enc.flbw_encrypt(strings[i], password));
        bchm_enc.push_back((double)flbw_enc.get_execution_time());

        rst_decrypted.push_back(flbw_dec.flbw_decrypt(rst_encrypted[i], password));
        bchm_dec.push_back((double)flbw_dec.get_execution_time());

        hash_end = flbw_dec.fn_sha256(rst_decrypted[i]);

        hashs_start.push_back(hash_start);
        hashs_end.push_back(hash_end);

        if (hash_start.compare(hash_end) == 0)
        {
            integrity_ok++;
            integrity.push_back(1.0);
            printf("%d> OK.\n", i);
        }
        else
        {
            integrity_ko++;
            integrity.push_back(0.0);
            printf("%d> KO.\n", i);
        }
    }
    time_end = clock();
    time_total = (((double)time_end - (double)time_start) / CLOCKS_PER_SEC);

    printf("\n====\nIntegrity details\n====\n\n");
    for (int i = 0; i < strings.size(); i++)
    {
        bchm_avg_enc += bchm_enc[i];
        bchm_avg_dec += bchm_dec[i];
        if (integrity[i] == 1.0)
        {
            bchm_sum = (bchm_enc[i] + bchm_dec[i]);
            bchm_cps = ((double)strings[i].length() / bchm_sum);
            bchm_sum_chars += strings[i].length();
            //printf("Took %f s. enc., %f s. dec., %f s. enc./dec., for %d characters (avg. of %f cps). \n", bchm_enc[i], bchm_dec[i], bchm_sum, (int)strings[i].length(), bchm_cps);
        }
        else
        {
            //printf("No benchmark for this string as the integrity check failed. \n");
            printf("Integrity check failed (string %d).\nHash start: %s\nHash end: %s\nPassword hash: %s\n\n", i, hashs_start[i].c_str(), hashs_end[i].c_str(), flbw.fn_sha256(passwords[i]).c_str());
        }
    }

    printf("\n====\nResults\n====\n'''\ncps = char per second\n'''\n\n");
    printf("Generated %d strings and passwords.\n", (int)strings.size());
    printf("Encryption time: %f seconds (avg. of %d cps). \n", bchm_avg_enc, (int)((double)bchm_sum_chars / bchm_avg_enc));
    printf("Decryption time: %f seconds (avg. of %d cps). \n", bchm_avg_dec, (int)((double)bchm_sum_chars / bchm_avg_dec));
    printf("Total of %d chars in %f seconds (avg. of %d cps for enc. and dec. sequences).\n", bchm_sum_chars, time_total, (int)((double)bchm_sum_chars / time_total));
    printf("%d OK, %d KO (%.3f %% fail).\n", integrity_ok, integrity_ko, ((double)(integrity_ko * 100) / (double)integrity_ok));
}
