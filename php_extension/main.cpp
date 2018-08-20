#include <phpcpp.h>
#include "flbw_lib/flbw.h"

/**
 *  flbw_encode()
 *  @param  Php::Parameters     the given parameters
 *  @return Php::Value          Param[0] and Param[1] added
 */
Php::Value flbw_encode(Php::Parameters &params)
{
    FLBW flbw;
    std::string data = params[0];
    std::string password = params[1];
    std::string rst;
    int bruteforce_difficulty;

    bruteforce_difficulty = (params[2] != -1) ? std::stoi(params[2]) : 0;
    if (bruteforce_difficulty)
    {
        flbw.set_bruteforce_protection(true);
        flbw.set_bruteforce_difficulty(bruteforce_difficulty);
    }
    else
        flbw.set_bruteforce_protection(false);
    rst = flbw.flbw_encrypt(data, password);
    if (rst.length())
        return (rst);
    else
        return (false);
}

/**
 *  flbw_decode()
 *  @param  Php::Parameters     the given parameters
 *  @return Php::Value          Param[0] and Param[1] added
 */
Php::Value flbw_decode(Php::Parameters &params)
{
    FLBW flbw;
    std::string data = params[0];
    std::string password = params[1];
    std::string rst;
    int bruteforce_difficulty;

    bruteforce_difficulty = (params[2] != -1) ? std::stoi(params[2]) : 0;
    if (bruteforce_difficulty)
    {
        flbw.set_bruteforce_protection(true);
        flbw.set_bruteforce_difficulty(bruteforce_difficulty);
    }
    else
        flbw.set_bruteforce_protection(false);
    rst = flbw.flbw_decrypt(data, password);
    if (rst.length())
        return (rst);
    else
        return (false);
}

extern "C"
{
    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension extension("flbw", "1.0");

        extension.add<flbw_encode>("flbw_encode", {Php::ByVal("data", Php::Type::String),
                                                   Php::ByVal("password", Php::Type::String),
                                                   Php::ByVal("bruteforce_protection", Php::Type::Numeric)});

        extension.add<flbw_decode>("flbw_decode", {Php::ByVal("data", Php::Type::String),
                                                   Php::ByVal("password", Php::Type::String),
                                                   Php::ByVal("bruteforce_protection", Php::Type::Numeric)});

        return extension.module();
    }
}
