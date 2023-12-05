#ifdef _WIN32
    #define STR_TOK_SECURE STR_TOK_SECURE
#else
    #define STR_TOK_SECURE strtok_r
#endif