#ifndef _FLBW_H_
#define _FLBW_H_

#define C_RED "\x1B[31m"
#define C_GRN "\x1B[32m"
#define C_YEL "\x1B[33m"
#define C_BLU "\x1B[34m"
#define C_MAG "\x1B[35m"
#define C_CYN "\x1B[36m"
#define C_WHT "\x1B[37m"
#define C_RESET "\x1B[0m"

#include "lib/base64/base64.h"
#include "lib/sha512/sha512.h"
#include "lib/sha256/sha256.h"
#include "lib/sha1/sha1.h"
#include <sys/time.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctype.h>
#include <sstream>
#include <stdio.h>
#include <random>
#include <vector>

typedef struct s_de_de_de
{
  double i_f;
  double i_s;
  double i_t;
} t_de_de_de;

class FLBW
{
private:
  std::string _base_array;
  std::string _result_hash;
  std::string _message;
  std::string _version;
  clock_t _time_start, _time_end;
  int _base_size;
  int _error;

  std::string strtr(std::string &source, std::string &toReplace, std::string &replaceWith);
  std::string str_rot(std::string str, int number);
  int rand_vals(int min, int max);
  std::vector<std::string> explode(char delim, std::string const &s);
  bool is_number(const std::string &s);

  std::string flbw_hash(std::string password);
  t_de_de_de ascii_to_10(std::string str);
  std::string generate_array(int key);
  std::string crypt_word(std::string mot, std::string key_arr);
  std::vector<unsigned char> xor_encrypt(std::string str, std::string key);
  std::string xor_decrypt(std::vector<unsigned char> str, std::string key);
  std::string crypt_word_inv(std::string str, std::string key_arr, int key);
  std::string set_error_message(std::string message);
  void reset(void);

public:
  FLBW(void);
  int get_error();
  std::string get_message();
  std::string get_version();
  std::string fn_sha1(std::string str);
  std::string fn_sha256(std::string str);
  std::string fn_sha512(std::string str);
  float get_execution_time(void);
  std::string get_result_hash(void);
  std::string flbw_encrypt(std::string data, std::string password);
  std::string flbw_decrypt(std::string data, std::string password);
};

#endif /* _FLBW_H_ */