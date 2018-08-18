#include "flbw.h"

FLBW::FLBW(void)
{
    reset();
    _base_array = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ;";
    _base_size = _base_array.length();
    _version = "0.5";
}

/*
 * FLBW extern functions.
 */

std::vector<std::string> FLBW::explode(char delim, std::string const &s)
{
    std::vector<std::string> result;
    std::istringstream iss(s);
    std::size_t found = s.find(delim);

    if (found != std::string::npos)
        for (std::string token; std::getline(iss, token, delim);)
            result.push_back(std::move(token));
    else
        result.push_back(s);
    return (result);
}

std::string FLBW::strtr(std::string &source, std::string &toReplace, std::string &replaceWith)
{
    size_t pos = 0;
    size_t cursor = 0;
    int repLen = toReplace.length();
    std::stringstream builder;
    do
    {
        pos = source.find(toReplace, cursor);

        if (std::string::npos != pos)
        {
            builder << source.substr(cursor, pos - cursor);
            builder << replaceWith;
            cursor = pos + repLen;
        }
    } while (std::string::npos != pos);
    builder << source.substr(cursor);

    return (builder.str());
}

std::string FLBW::str_rot(std::string str, int number)
{
    std::string static letters = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    std::string rep = "";

    number = (int)number % 26;
    if (!number)
        return str;
    if (number < 0)
        number += 26;

    rep = letters.substr(number * 2) + letters.substr(0, number * 2);
    str = strtr(str, letters, rep);
    return str;
}

std::string FLBW::fn_sha1(std::string str)
{
    SHA1 checksum;

    checksum.update(str);
    return (checksum.final());
}

std::string FLBW::fn_sha256(std::string str)
{
    unsigned char digest[SHA256::DIGEST_SIZE];
    memset(digest, 0, SHA256::DIGEST_SIZE);
    SHA256 ctx = SHA256();
    ctx.init();
    ctx.update((unsigned char *)str.c_str(), str.length());
    ctx.final(digest);

    char buf[2 * SHA256::DIGEST_SIZE + 1];
    buf[2 * SHA256::DIGEST_SIZE] = 0;
    for (int i = 0; i < SHA256::DIGEST_SIZE; i++)
        sprintf(buf + i * 2, "%02x", digest[i]);
    return (std::string(buf));
}

std::string FLBW::fn_sha512(std::string str)
{
    unsigned char digest[SHA512::DIGEST_SIZE];
    memset(digest, 0, SHA512::DIGEST_SIZE);
    SHA512 ctx = SHA512();
    ctx.init();
    ctx.update((unsigned char *)str.c_str(), str.length());
    ctx.final(digest);

    char buf[2 * SHA512::DIGEST_SIZE + 1];
    buf[2 * SHA512::DIGEST_SIZE] = 0;
    for (int i = 0; i < SHA512::DIGEST_SIZE; i++)
        sprintf(buf + i * 2, "%02x", digest[i]);
    return (std::string(buf));
}

int FLBW::rand_vals(int min, int max)
{
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

bool FLBW::is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

/*
 * FLBW intern functions.
 */

void FLBW::reset(void)
{
    _time_start = clock();
    _time_end = clock();
    _result_hash = "0000000000000000000000000000000000000000";
    _error = 0;
    _message = "";
}

std::string FLBW::get_version()
{
    return (_version);
}

int FLBW::get_error()
{
    return (_error);
}

std::string FLBW::set_error_message(std::string message)
{
    _error = 1;
    _message = std::string(C_RED) + message + std::string(C_RESET);
    return (_message);
}

std::string FLBW::get_message()
{
    return (_message);
}

std::string FLBW::flbw_hash(std::string password)
{
    std::string step = fn_sha512(str_rot("flbw" + password, 5));
    step = str_rot(step, 42);
    return fn_sha512(step + '%');
}

t_de_de_de FLBW::ascii_to_10(std::string str)
{
    double sum = 0.0;
    t_de_de_de v_return;

    for (int i = 0; i < str.length(); i++)
        sum += (double)((int)str[i] - 48);
    v_return.i_f = sum;
    v_return.i_s = (sum / (double)str.length());
    v_return.i_t = (v_return.i_s * v_return.i_f);
    return (v_return);
}

std::string FLBW::generate_array(int key)
{
    std::string rpl = "";
    int i = 0;
    int np = 0;

    for (i = 0; i < _base_size; i++)
        if (i + key < _base_size)
            rpl += _base_array[i + key];
        else
        {
            np = abs(_base_size - i - key);
            rpl += _base_array[np];
        }
    return (rpl);
}

std::string FLBW::crypt_word(std::string str, std::string key_arr)
{
    std::string me = "";
    int a = 0;
    bool eb = false;

    if (key_arr.length() != _base_size)
    {
        set_error_message("Array error in crypt_word. Please report this bug.");
        exit;
    }
    for (int i = 0, l = str.length(); i < l; i++)
    {
        a = 0;
        eb = false;
        while (str[i] != _base_array[a] && eb != true)
            if (((i + 1) > (str.length() - 1)) || ((a + 1) > (key_arr.length() - 1)))
                eb = true;
            else
                a++;
        me += (str[i] == _base_array[a]) ? key_arr[a] : str[i];
    }
    return (me);
}

std::vector<unsigned char> FLBW::xor_encrypt(std::string str, std::string key)
{
    std::vector<unsigned char> r(str.length());
    for (size_t i = 0; i < str.length(); ++i)
        r[i] = str[i] ^ key[i % key.length()];
    return (r);
}

std::string FLBW::xor_decrypt(std::vector<unsigned char> str, std::string key)
{
    std::string rst;

    for (int i = 0; i != str.size(); i++)
    {
        rst += str[i] ^ key[i % key.length()];
    }
    return (rst);
}

std::string FLBW::crypt_word_inv(std::string str, std::string key_arr, int key)
{
    std::string rst = "";
    int a = 0;
    bool eb = false;
    const char *find;
    int index;

    if (key_arr.length() != _base_size)
    {
        set_error_message("Array error in crypt_word_inv. Please report this bug.");
        return (rst);
    }

    for (int i = 0, l = str.length(); i < l; i++)
    {
        a = 0;
        eb = false;
        while (str[i] != key_arr[a] && eb != true)
            if (((i + 1) > (str.length() - 1)) || ((a + 1) > (key_arr.length() - 1)))
                eb = true;
            else
                a++;
        if (str[i] == key_arr[a])
            rst += _base_array[a];
        else
        {
            if (_base_array.find(str[i]) != std::string::npos)
            {

                find = strchr(key_arr.c_str(), str[i]);
                index = (int)(find - key_arr.c_str());
                rst += _base_array[index];
            }
            else
                rst += str[i];
        }
    }
    return (rst);
}

float FLBW::get_execution_time(void)
{
    return (((float)_time_end - (float)_time_start) / CLOCKS_PER_SEC);
}

std::string FLBW::get_result_hash(void)
{
    return (_result_hash);
}

std::string FLBW::flbw_encrypt(std::string data, std::string password)
{
    reset();
    Base64 base64;
    int key = rand_vals(1, 61);
    int stm = 0;
    std::vector<unsigned char> rst_b;
    std::string rst = "";
    std::string step = "";

    if (data.length())
    {
        password = flbw_hash(password);
        t_de_de_de atod = ascii_to_10(password);
        std::string aotd_pass = fn_sha256(std::to_string(atod.i_t));
        std::string key_a = generate_array(key);
        std::vector<std::string> sst = explode(' ', data);
        for (int i = 0; i < sst.size(); i++)
            if (stm != 0 || stm != sst.size())
                step += crypt_word(sst[i] + " ", key_a);
            else
            {
                step = crypt_word(sst[i], key_a);
                stm++;
            }
        step = step.substr(0, step.size() - 1);
        std::string needle = std::to_string(key) + ";" + step;
        rst_b = xor_encrypt(needle, password);
        unsigned char *rst_b_c = (unsigned char *)malloc(sizeof(rst_b) * rst_b.size());
        for (int i = 0; i < rst_b.size(); i++)
            rst_b_c[i] = (unsigned char)rst_b[i];
        rst = base64.base64_encode(rst_b_c, rst_b.size());
        _result_hash = fn_sha1(rst);
    }
    else
        set_error_message("Can't cipher empty data.");
    _time_end = clock();
    return (rst);
}

std::string FLBW::flbw_decrypt(std::string data, std::string password)
{
    reset();
    Base64 base64;
    std::string key_a;
    std::string rst = "";
    _time_start = clock();

    if (data.length())
    {
        password = flbw_hash(password);
        t_de_de_de atod = ascii_to_10(password);
        std::string aotd_pass = fn_sha256(std::to_string(atod.i_t));
        std::vector<unsigned char> str_b = base64.base64_decode(data);
        std::string str;
        str = xor_decrypt(str_b, password);
        std::size_t found = str.find(";");
        if (found != std::string::npos)
        {
            std::vector<std::string> sst = explode(';', str);
            if (sst.size() >= 2 && is_number(sst[0]))
            {
                int key = std::stoi(sst[0]);
                std::string right = "";
                if (sst.size() > 2)
                    for (int i = 1; i < sst.size(); i++)
                        if (sst.size() - 1 == i)
                            right += sst[i];
                        else
                            right += sst[i] + ';';
                else
                    right = sst[1];
                key_a = generate_array(key);
                if (key_a.length())
                {
                    rst = crypt_word_inv(right, key_a, key);
                    _result_hash = fn_sha1(rst);
                }
                else
                    rst = "";
            }
            else
                set_error_message("Invalid decode : wrong password suspected.");
        }
        else
            set_error_message("Wrong password.");
    }
    else
        set_error_message("Can't decipher empty data.");
    _time_end = clock();
    return (rst);
}